#include "Header.h"

void LoadMSG(std::string MSGData, MSGDATA *MSGInfo)
{
	int count = 0, DataCount1, DataCount2, NameCount = 0, stop, stringPosCount, LengthCount, IDCount;
	char TempName[300] = { NULL }, TempInfo[300] = { NULL };

	DataCount1 = (uint8_t)MSGData[(uint8_t)MSGData[0x0c]] + ((uint8_t)MSGData[(uint8_t)MSGData[0x0c] + 1] * 0x100);
	stringPosCount = (uint8_t)MSGData[0x1c] + ((uint8_t)MSGData[0x1d] * 0x100);
	DataCount2 = (uint8_t)MSGData[stringPosCount] + ((uint8_t)MSGData[stringPosCount + 1] * 0x100);
	LengthCount = stringPosCount + 4;
	stop = DataCount2 - 2;
	IDCount = (uint8_t)MSGData[0x10] + ((uint8_t)MSGData[0x11] * 0x100);

	while (DataCount1 <= stop)
	{
		MSGInfo[count].ID = (uint8_t)MSGData[IDCount];
		while (MSGData[DataCount1] != 00)
		{
			TempName[NameCount] = MSGData[DataCount1];
			NameCount++;
			DataCount1 += 2;
		}
		MSGInfo[count].NameID = TempName;
		NameCount = 0;
		DataCount1 += 2;

		while (MSGData[DataCount2] != 00)
		{
			if (MSGData[DataCount2] == '\n')
			{
				TempInfo[NameCount] = '\r';
				NameCount++;
				DataCount2 += 2;
				TempInfo[NameCount] = '\n';
				NameCount++;
			}
			if (MSGData[DataCount2] != '&')
			{
				TempInfo[NameCount] = MSGData[DataCount2];
				NameCount++;
				DataCount2 += 2;
			}
			else
			{
				TempInfo[NameCount] = '\'';
				NameCount++;
				DataCount2 += 12;
			}

		}
		MSGInfo[count].Info = TempInfo;
		NameCount = 0;
		DataCount2 += 2;

		MSGInfo[count].stringStartID1 = MSGData[stringPosCount + 1];
		MSGInfo[count].stringStartID2 = MSGData[stringPosCount];
		stringPosCount += 0x10;

		MSGInfo[count].startLength = MSGData[LengthCount];
		MSGInfo[count].endLength = MSGData[LengthCount + 4];
		LengthCount += 0x10;

		memset(TempName, 0, sizeof(TempName));
		memset(TempInfo, 0, sizeof(TempInfo));
#ifdef _DEBUG
		std::cout << MSGInfo[count].ID << " - " << MSGInfo[count].NameID << " - " << MSGInfo[count].Info << "\n";
#endif
		IDCount+= 4;
		count++;
	}
	MSGCount = count;
}

void NormalizeMSG(std::string &NewString)
{
	int count = 0;
	char Apos[] = { "&apos;" };
	std::string NewTemp;
	size_t size = strlen(NewString.c_str()) * 2 - 1;

	if (NewString.empty()) return;

	while (count <= (int)NewString.size())
	{
		if (NewString[count] == '\r')
		{
			NewString.erase(count, 1);
		}
		if(NewString[count] == '\'')
		{
			NewString.insert(count,  Apos);
			count += 6;
			NewString.erase(count, 1);
		}
		else
			count++;
	}
	NewTemp.resize(size);
	count = 0;

	while (count <= size)
	{
		if (count == 0)
		{
			NewTemp[count] = NewString[count];
		}
		else
		{
			NewTemp[count] = NewString[count - (count/2)];
		}
		count += 2;
	}

	NewString.erase();
	NewString = NewTemp;
}

int SetMSG(std::string OTemp, std::string NTemp, int index, std::string &MSGData, MSGDATA* MSGID )
{
	int count = 0, size, NewSize, OldSize, HexNumTemp = 0, stringLengthPos;
	char CTemp[10], Temp1[4], Temp2[4];
	std::stringstream HexNum;
	stringLengthPos = (uint8_t)MSGData[0x1c] + ((uint8_t)MSGData[0x1d] * 0x100);

	NewSize = strlen(NTemp.c_str());
	OldSize = strlen(OTemp.c_str());
	NormalizeMSG(NTemp);
	NormalizeMSG(OTemp);
	size = OTemp.size();
	if (OTemp.empty())
	{
		count = (uint8_t)MSGID[index].stringStartID1 * 0x100;
		count += (uint8_t)MSGID[index].stringStartID2;
	}
	else
	{
		count = MSGData.find(OTemp);
	}
	if (count == -1)  return -1; 
	MSGData.erase(count, size);
	MSGData.insert(count, NTemp);
	std::string Filler; Filler.resize(4);
	MSGData.insert(MSGData.size() - 1, Filler);
	NewSize = NewSize - OldSize;
	MSGData[(stringLengthPos + 4) + (index * 16)] = MSGID[index].startLength + NewSize;
	MSGData[(stringLengthPos + 8) + (index * 16)] = MSGID[index].endLength + (NewSize * 2);

	count = index + 1;
	while (count < MSGCount)
	{
		int TempID1 = 0, TempID2 = 0;
		HexNumTemp = 0;
		HexNum.clear();
		memset(CTemp, 0, 10);
		memset(Temp1, 0, 4);
		memset(Temp2, 0, 4);

		HexNumTemp = (uint8_t)MSGID[count].stringStartID1 * 0x100;
		HexNumTemp += (uint8_t)MSGID[count].stringStartID2;
		
		HexNumTemp += NewSize * 2;
		sprintf(CTemp, "%x", HexNumTemp);

		Temp1[0] = CTemp[0], Temp1[1] = CTemp[1];
		Temp2[0] = CTemp[2], Temp2[1] = CTemp[3];

		HexNum << std::hex << Temp1;
		HexNum >> TempID1;
		HexNum.clear();
		HexNum << std::hex << Temp2;
		HexNum >> TempID2;

		MSGData[stringLengthPos + (count * 16)] = TempID2;
		MSGData[(stringLengthPos + 1) + (count * 16)] = TempID1;
		count++;
	}

	return 0;
}