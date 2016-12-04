#include "Header.h"

SUPERSOUL SearchSS(int index)
{
	int count = 0x10, Ecount = 0;
	SUPERSOUL Data;
	uint8_t check = (uint8_t)SSIDBData[count];

	while (check != index)
	{
		count += 45 * 0x10;
		check = (uint8_t)SSIDBData[count];
	}

	Data.ID = count;
	Data.Rarity = count + 2;
	Data.Ki_BlastType = count + 32;
	while(Ecount < 3)
	{
		Data.Effect[Ecount] = count + 48 + (Ecount * 16 * 14);    // brackets section is for each effect offset
		Data.Trigger[Ecount] = count + 52 + (Ecount * 16 * 14);
		Data.TriggerConditions1[Ecount] = count + 64 +(Ecount * 16 * 14);
		Data.TriggerConditions2[Ecount] = count + 68 + (Ecount * 16 * 14);
		Data.TriggerConditions3[Ecount] = count + 72 + (Ecount * 16 * 14);
		Data.EffectAmount[Ecount] = count + 96 + (Ecount * 16 * 14);
		Data.Target[Ecount] = count + 140 + (Ecount * 16 * 14);
		Data.Flag[Ecount] = count + 56 + (Ecount * 16 * 14);
		Data.Timer[Ecount] = count + 60 + (Ecount * 16 * 14);
		Data.Health[Ecount] = count + 144 + (Ecount * 16 * 14);
		Data.Ki[Ecount] = count + 148 + (Ecount * 16 * 14);
		Data.Ki_RegenRate[Ecount] = count + 152 + (Ecount * 16 * 14);
		Data.Stamina[Ecount] = count + 156 + (Ecount * 16 * 14);
		Data.Stamina_RegenRate[Ecount] = count + 160 + (Ecount * 16 * 14);
		Data.Ground_Speed[Ecount] = count + 168 + (Ecount * 16 * 14);
		Data.Flight_Speed[Ecount] = count + 172 + (Ecount * 16 * 14);
		Data.Boost_Speed[Ecount] = count + 176 + (Ecount * 16 * 14);
		Data.Dash_Speed[Ecount] = count + 180 + (Ecount * 16 * 14);
		Data.Basic_Attack[Ecount] = count + 184 + (Ecount * 16 * 14);
		Data.Ki_Blast[Ecount] = count + 188 + (Ecount * 16 * 14);
		Data.Strike_Super[Ecount] = count + 192 + (Ecount * 16 * 14);
		Data.Ki_Blast_Super[Ecount] = count + 196 + (Ecount * 16 * 14);
		Data.Basic_Attack_Dmg[Ecount] = count + 200 + (Ecount * 16 * 14);
		Data.Ki_Blast_Dmg[Ecount] = count + 204 + (Ecount * 16 * 14);
		Data.Strike_Super_Dmg[Ecount] = count + 208 +(Ecount * 16 * 14);
		Data.Ki_Blast_Super_Dmg[Ecount] = count + 212 +(Ecount * 16 * 14);
		Data.Revive_Speed[Ecount] = count + 216 + (Ecount * 16 * 14);
		Ecount++;
	}

	return Data;
}

void LoadEffect()
{
	openFile("Data/Super Soul Effect.ini", SSEffectSetting);
	std::istringstream TempStream(SSEffectSetting);
	std::string TempString;
	int CTempHexID;
	char CTempValue[105] = { NULL };

	while (std::getline(TempStream, TempString))
	{

		int count = 0, posSet = 0, max = TempString.size();
		std::stringstream HexID;
		char CHexID[2] = { NULL };
		while (count <= max)
		{
			if (TempString[count] != ' ')
			{
				CHexID[count] = TempString[count];
				count++;
			}
			else
			{
				HexID << std::hex << CHexID;
				HexID >> CTempHexID;
				posSet = count;
				count += 3;
				posSet = count;
				break;
			}
		}
		while (count <= max)
		{
			if (TempString[count] != ';')
			{
				CTempValue[count - posSet] = TempString[count];
				count++;
			}
			else
			{
				break;
			}
		}
		SSEffectID[SSEffectCount].HexID = CTempHexID;
		SSEffectID[SSEffectCount].EffectName = CTempValue;
#ifdef _DEBUG
		std::cout << SSEffectID[SSEffectCount].HexID << " - " << SSEffectID[SSEffectCount].EffectName << std::endl;
#endif
		memset(CTempValue, 0, strlen(CTempValue));
		SSEffectCount++;
	}
}

void LoadEffectAmount()
{

	openFile("Data/Super Soul Effect Amount.ini", SSEffectAmountSetting);
	std::istringstream TempStream(SSEffectAmountSetting);
	std::string TempString;

	while (std::getline(TempStream, TempString))
	{
		char CTempName[50] = { NULL };
		char CHexID1[2] = { NULL }, CHexID2[2] = { NULL }, CHexID3[2] = { NULL }, CHexID4[2] = { NULL };
		std::stringstream HexID1, HexID2, HexID3, HexID4;
		int count = 0, countHex = 0, posSet = 0, max = TempString.size(), CTempHexID1, CTempHexID2, CTempHexID3, CTempHexID4;
		while (count <= max)
		{
			if (countHex < 2)
			{
				CHexID1[count - posSet] = TempString[count];
				count++;
				countHex++;
			}
			else
			{
				HexID1 << std::hex << CHexID1;
				HexID1 >> CTempHexID1;
				posSet = count;
				countHex = 0;
				break;
			}
		}
		while (count <= max)
		{
			if (countHex < 2)
			{
				CHexID2[count - posSet] = TempString[count];
				count++;
				countHex++;
			}
			else
			{
				HexID2 << std::hex << CHexID2;
				HexID2 >> CTempHexID2;
				posSet = count;
				countHex = 0;
				break;
			}
		}
		while (count <= max)
		{
			if (countHex < 2)
			{
				CHexID3[count - posSet] = TempString[count];
				count++;
				countHex++;
			}
			else
			{
				HexID3 << std::hex << CHexID3;
				HexID3 >> CTempHexID3;
				posSet = count;
				countHex = 0;
				break;
			}
		}
		while (count <= max)
		{
			if (countHex < 2)
			{
				CHexID4[count - posSet] = TempString[count];
				count++;
				countHex++;
			}
			else
			{
				HexID4 << std::hex << CHexID4;
				HexID4 >> CTempHexID4;
				count += 3;
				posSet = count;
				countHex = 0;
				break;
			}
		}
		while (count <= max)
		{
			if (TempString[count] != ';')
			{

				CTempName[count - posSet] = TempString[count];
				count++;
			}
			else
			{
				break;
			}
		}
		SSEAID[SSEffectAmountCount].HexID1 = CTempHexID1;
		SSEAID[SSEffectAmountCount].HexID2 = CTempHexID2;
		SSEAID[SSEffectAmountCount].HexID3 = CTempHexID3;
		SSEAID[SSEffectAmountCount].HexID4 = CTempHexID4;
		SSEAID[SSEffectAmountCount].Amount = CTempName;
#ifdef _DEBUG
		std::cout << SSEAID[SSEffectAmountCount].HexID1 << std::hex << SSEAID[SSEffectAmountCount].HexID2 <<
			SSEAID[SSEffectAmountCount].HexID3 << std::hex << SSEAID[SSEffectAmountCount].HexID4 << " - " << 
			SSEAID[SSEffectAmountCount].Amount << std::endl;
#endif
		SSEffectAmountCount++;
		//memset(CTempName, 0, strlen(CTempName));
	}
}

void LoadTrigger()
{
	openFile("Data/Super Soul Trigger.ini", SSTriggerSetting);
	std::istringstream TempStream(SSTriggerSetting);
	std::string TempString;
	int CTempHexID;
	char CTempValue[105] = { NULL };

	while (std::getline(TempStream, TempString))
	{

		int count = 0, posSet = 0, max = TempString.size();
		std::stringstream HexID;
		char CHexID[2] = { NULL };
		while (count <= max)
		{
			if (TempString[count] != ' ')
			{
				CHexID[count] = TempString[count];
				count++;
			}
			else
			{
				HexID << std::hex << CHexID;
				HexID >> CTempHexID;
				posSet = count;
				count += 3;
				posSet = count;
				break;
			}
		}
		while (count <= max)
		{
			if (TempString[count] != ';')
			{
				CTempValue[count - posSet] = TempString[count];
				count++;
			}
			else
			{
				break;
			}
		}
		SSTriggerID[SSTriggerCount].HexID = CTempHexID;
		SSTriggerID[SSTriggerCount].Trigger = CTempValue;
#ifdef _DEBUG
		std::cout << SSTriggerID[SSTriggerCount].HexID << " - " << SSTriggerID[SSTriggerCount].Trigger << std::endl;
#endif
		memset(CTempValue, 0, strlen(CTempValue));
		SSTriggerCount++;
	}
}

void LoadTC()
{
	openFile("Data/Super Soul Trigger Condition.ini", SSTCSetting);
	std::istringstream TempStream(SSTCSetting);
	std::string TempString;

	while (std::getline(TempStream, TempString))
	{
		char CTempName[50] = { NULL }, CHexID1[2] = { NULL }, CHexID2[2] = { NULL };
		std::stringstream HexID1, HexID2;
		int count = 0, countHex = 0, posSet = 0, max = TempString.size(), CTempHexID1, CTempHexID2;

		while (count <= max)
		{
			if (countHex < 2)
			{
				CHexID1[count - posSet] = TempString[count];
				count++;
				countHex++;
			}
			else
			{
				HexID1 << std::hex << CHexID1;
				HexID1 >> CTempHexID1;
				posSet = count;
				countHex = 0;
				break;
			}
		}
		while (count <= max)
		{
			if (countHex < 2)
			{
				CHexID2[count - posSet] = TempString[count];
				count++;
				countHex++;
			}
			else
			{
				HexID2 << std::hex << CHexID2;
				HexID2 >> CTempHexID2;
				count += 3;
				posSet = count;
				break;
			}
		}
		while (count <= max)
		{
			if (TempString[count] != ';')
			{

				CTempName[count - posSet] = TempString[count];
				count++;
			}
			else
			{
				break;
			}
		}

		SSTCID[SSTCCount].HexID1 = CTempHexID1;
		SSTCID[SSTCCount].HexID2 = CTempHexID2;
		SSTCID[SSTCCount].TCName = CTempName;
#ifdef _DEBUG
		std::cout << std::hex << SSTCID[SSTCCount].HexID1 << std::hex << SSTCID[SSTCCount].HexID2 <<
			" - " << SSTCID[SSTCCount].TCName << std::endl;
#endif
		SSTCCount++;
		//memset(CTempName, 0, strlen(CTempName));
	}
}

int SearchEffectID(int index)
{
	int count = 0;
	uint8_t check = SSIDBData[index];

	while (check != SSEffectID[count].HexID)
	{
		if (count > 0 && SSEffectID[count].HexID == 0) return count;
		count++;
	}
	return count;
}

int SearchEffectAmountID(int index)
{
	int count = 0;
	uint8_t check1 = SSIDBData[index], check2 = SSIDBData[index + 1], check3 = SSIDBData[index + 2], check4 = SSIDBData[index + 3];

	while (check1 != SSEAID[count].HexID1 && check2 != SSEAID[count].HexID2 && check3 != SSEAID[count].HexID3	&& check4 != SSEAID[count].HexID4)
	{
		if (count > 0 && SSEAID[count].HexID1 == 0x11 && SSEAID[count].HexID2 == 0x11 && SSEAID[count].HexID3 == 0x11 
			&& SSEAID[count].HexID4 == 0x11) return count;
		count++;
	}
	return count;
}

int SearchFlagID(int index)
{
	int count = 0;
	uint8_t check = SSIDBData[index];

	while (check != SSSetting.Flag[count])
	{
		if (count > 0 && SSSetting.Flag[count] == 0) return count;
		count++;
	}
	return count;
}

int SearchTriggerID(int index)
{
	int count = 0;
	uint8_t check = SSIDBData[index];

	while (check != SSTriggerID[count].HexID)
	{
		if (count > 0 && SSTriggerID[count].HexID == 0) return count;
		count++;
	}
	return count;
}

int SearchTimerID(int index)
{
	int count = 0;
	uint8_t check1 = SSIDBData[index + 2], check2 = SSIDBData[index + 3];

	while (check1 != SSSetting.TimerID1[count] || check2 != SSSetting.TimerID2[count])
	{
		if (count > 0 && SSSetting.TimerID1[count] == 0 && SSSetting.TimerID2[count] == 0) return count;
		count++;
	}
	return count;
}

int SearchTargetID(int index)
{
	int count = 0;
	uint8_t check = SSIDBData[index];

	while (check != SSSetting.Target[count])
	{
		if (count > 0 && SSSetting.Target[count] == 0) return count;
		count++;
	}
	return count;
}

int SearchTCID(int index)
{
	int count = 0;
	uint8_t check1 = SSIDBData[index + 2], check2 = SSIDBData[index + 3];

	while (check1 != SSTCID[count].HexID1 || check2 != SSTCID[count].HexID2)
	{
		if (count > 0 && SSTCID[count].HexID1 == 0 && SSTCID[count].HexID2 == 0) return count;
		count++;
	}
	return count;
}

void SetSoul()
{

}