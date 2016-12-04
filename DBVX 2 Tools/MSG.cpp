#include "Header.h"

void LoadMSG(std::string MSGData, MSGDATA *MSGInfo, int mode)
{
	int count = 0, DataCount1 = 0x2464, DataCount2 = 0x39D2, NameCount = 0, stop;
	char TempName[300] = { NULL }, TempInfo[300] = { NULL };
	if (mode == 0) stop = 0x39CF; else { stop = 0x4067; DataCount2 = 0x406A; }


	while (DataCount1 <= stop)
	{
		MSGInfo[count].ID = count;
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
		memset(TempName, 0, sizeof(TempName));
		memset(TempInfo, 0, sizeof(TempInfo));
#ifdef _DEBUG
		std::cout << MSGInfo[count].ID << " - " << MSGInfo[count].NameID << " - " << MSGInfo[count].Info << "\n";
#endif
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