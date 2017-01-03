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
	Data.Activate = count + 10;
	Data.Price = count + 16;
	Data.Ki_BlastType = count + 32;
	while(Ecount < 3)
	{
		Data.Effect[Ecount] = count + 48 + (Ecount * 16 * 14);    // brackets section is for each effect offset
		Data.Trigger[Ecount] = count + 52 + (Ecount * 16 * 14);
		Data.TriggerConditions1[Ecount] = count + 64 +(Ecount * 16 * 14);
		Data.TriggerConditions2[Ecount] = count + 68 + (Ecount * 16 * 14);
		Data.TriggerConditions3[Ecount] = count + 72 + (Ecount * 16 * 14);
		Data.TriggerConditions4[Ecount] = count + 76 + (Ecount * 16 * 14);
		Data.TriggerConditions5[Ecount] = count + 80 + (Ecount * 16 * 14);
		Data.EffectAmount[Ecount] = count + 96 + (Ecount * 16 * 14);
		Data.Target[Ecount] = count + 140 + (Ecount * 16 * 14);
		Data.Flag[Ecount] = count + 56 + (Ecount * 16 * 14);
		Data.Timer[Ecount] = count + 60 + (Ecount * 16 * 14);
		Data.Health[Ecount] = count + 144 + (Ecount * 16 * 14);
		Data.Ki[Ecount] = count + 148 + (Ecount * 16 * 14);
		Data.Ki_RegenRate[Ecount] = count + 152 + (Ecount * 16 * 14);
		Data.Stamina[Ecount] = count + 156 + (Ecount * 16 * 14);
		Data.Stamina_RegenRate[Ecount] = count + 160 + (Ecount * 16 * 14);
		Data.Ground_Speed[Ecount] = count + 172 + (Ecount * 16 * 14);
		Data.Flight_Speed[Ecount] = count + 176 + (Ecount * 16 * 14);
		Data.Boost_Speed[Ecount] = count + 180 + (Ecount * 16 * 14);
		Data.Dash_Speed[Ecount] = count + 184 + (Ecount * 16 * 14);
		Data.Basic_Attack[Ecount] = count + 188 + (Ecount * 16 * 14);
		Data.Ki_Blast[Ecount] = count + 192 + (Ecount * 16 * 14);
		Data.Strike_Super[Ecount] = count + 196 + (Ecount * 16 * 14);
		Data.Ki_Blast_Super[Ecount] = count + 200 + (Ecount * 16 * 14);
		Data.Basic_Attack_Dmg[Ecount] = count + 204 + (Ecount * 16 * 14);
		Data.Ki_Blast_Dmg[Ecount] = count + 208 + (Ecount * 16 * 14);
		Data.Strike_Super_Dmg[Ecount] = count + 212 +(Ecount * 16 * 14);
		Data.Ki_Blast_Super_Dmg[Ecount] = count + 216 +(Ecount * 16 * 14);
		Data.Revive_Speed[Ecount] = count + 240 + (Ecount * 16 * 14);
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

	while (check1 != SSEAID[count].HexID1 || check2 != SSEAID[count].HexID2 || check3 != SSEAID[count].HexID3 || check4 != SSEAID[count].HexID4)
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
		if (count > 0 && SSTCID[count].HexID1 == 0x11 && SSTCID[count].HexID2 == 0x11) return count;
		count++;
	}
	return count;
}

void SetSoul(HWND hDlg)
{
	int index, count = 0;
	HWND hTemp;
	char CTemp[200];
	std::string NTemp, OTemp;

	hTemp = GetDlgItem(hDlg, IDC_EDIT1);
	GetWindowTextA(hTemp, CTemp, GetWindowTextLength(hTemp) + 1);
	hTemp = GetDlgItem(hDlg, IDC_COMBO1);
	index = SendMessage(hTemp, CB_GETCURSEL, 0, 0);
	NTemp = CTemp;
	if (index != -1)
	{
		OTemp = NameMSGID[index].Info;
		SetMSG(OTemp, NTemp, index, NameMSGData, NameMSGID);
		LoadMSG(NameMSGData, NameMSGID);
	}
	else
	{
		SetWindowText(GetDlgItem(hDlg, IDC_EDITERROR1), L"No Name MSG Loaded");
	}

	if (!DescMSGData.empty())
	{
		char CInput[10];
		std::stringstream HexNum;

		GetWindowTextA(GetDlgItem(hDlg, IDC_EDIT3), CInput, 4);
		hTemp = GetDlgItem(hDlg, IDC_EDIT2);
		HexNum << std::hex << CInput;
		HexNum >> index;
	}
	else index = -1;

	hTemp = GetDlgItem(hDlg, IDC_EDIT2);
	GetWindowTextA(hTemp, CTemp, GetWindowTextLength(hTemp) + 1);
	NTemp = CTemp;
	
	if (index != -1)
	{
		OTemp = DescMSGID[index].Info;
		SetMSG(OTemp, NTemp, index, DescMSGData, DescMSGID);
		LoadMSG(DescMSGData, DescMSGID);
	}
	else
	{
		SetWindowText(GetDlgItem(hDlg, IDC_EDITERROR2), L"No Description MSG Loaded");
	}

	if (!SSIDBData.empty())
	{
		hTemp = GetDlgItem(hwndDisplay[2], IDC_EDIT4);
		index = SendMessage(hTemp, CB_GETCURSEL, 0, 0);
		GetWindowTextA(hTemp, CTemp, 2);
		SSIDBData[SSData.Rarity] = CTemp[0] - '0';
		hTemp = GetDlgItem(hwndDisplay[2], IDC_COMBO2);
		SSIDBData[SSData.Ki_BlastType] = SendMessage(hTemp, CB_GETCURSEL, 0, 0);
		hTemp = GetDlgItem(hwndDisplay[2], IDC_COMBO3);
		index = SendMessage(hTemp, CB_GETCURSEL, 0, 0);
		hTemp = GetDlgItem(hwndDisplay[2], IDC_EDIT6);

		char NumTemp[5], HexTemp[5];

		GetWindowTextA(hTemp, NumTemp, 5);
		sprintf(HexTemp, "%.4x", atoi(NumTemp));
		
		std::stringstream HexNum;
		char Temp1[2], Temp2[2];
		int TempID1, TempID2;

		Temp1[0] = HexTemp[0], Temp1[1] = HexTemp[1];
		Temp2[0] = HexTemp[2], Temp2[1] = HexTemp[3];

		HexNum << std::hex << Temp1;
		HexNum >> TempID1;
		HexNum.str(std::string());
		HexNum.clear();
		HexNum << std::hex << Temp2;
		HexNum >> TempID2;

		SSIDBData[SSData.Price + 1] = TempID1;
		SSIDBData[SSData.Price] = TempID2;

		SSIDBData[SSData.Activate] = -1;
		SSIDBData[SSData.Activate + 1] = -1;
		SSIDBData[SSData.Activate + 14] = -1;

		count = 0;

		while (count < 3)
		{
			SSIDBData[SSData.Effect[count]] = SSEffectID[SSCurEffect.Effect[count]].HexID;
			SSIDBData[SSData.Effect[count ] + 1] = 0;
			SSIDBData[SSData.Effect[count ] + 2] = 0;
			SSIDBData[SSData.Effect[count ] + 3] = 0;

			SSIDBData[SSData.EffectAmount[count]] = SSEAID[SSCurEffect.EffectAmount[count]].HexID1;
			SSIDBData[SSData.EffectAmount[count] + 1] = SSEAID[SSCurEffect.EffectAmount[count]].HexID2;
			SSIDBData[SSData.EffectAmount[count] + 2] = SSEAID[SSCurEffect.EffectAmount[count]].HexID3;
			SSIDBData[SSData.EffectAmount[count] + 3] = SSEAID[SSCurEffect.EffectAmount[count]].HexID4;

			SSIDBData[SSData.Flag[count]] = SSSetting.Flag[SSCurEffect.Flag[count]];
			if (SSSetting.Flag[SSCurEffect.Flag[count]] == 0xff)
			{
				SSIDBData[SSData.Flag[count] + 1] = 0xff;
				SSIDBData[SSData.Flag[count] + 2] = 0xff;
				SSIDBData[SSData.Flag[count] + 3] = 0xff;
			}
			else
			{
				SSIDBData[SSData.Flag[count] + 1] = 0x00;
				SSIDBData[SSData.Flag[count] + 2] = 0x00;
				SSIDBData[SSData.Flag[count] + 3] = 0x00;
			}

			SSIDBData[SSData.Trigger[count]] = SSTriggerID[SSCurEffect.Trigger[count]].HexID;
			SSIDBData[SSData.Trigger[count] + 1] = 0;
			SSIDBData[SSData.Trigger[count] + 2] = 0;
			SSIDBData[SSData.Trigger[count] + 3] = 0;

			SSIDBData[SSData.Target[count]] = SSSetting.Target[SSCurEffect.Target[count]];

			SSIDBData[SSData.TriggerConditions1[count] + 2] = SSTCID[SSCurEffect.TriggerConditions1[count]].HexID1;
			SSIDBData[SSData.TriggerConditions1[count] + 3] = SSTCID[SSCurEffect.TriggerConditions1[count]].HexID2;

			SSIDBData[SSData.TriggerConditions2[count] + 2] = SSTCID[SSCurEffect.TriggerConditions2[count]].HexID1;
			SSIDBData[SSData.TriggerConditions2[count] + 3] = SSTCID[SSCurEffect.TriggerConditions2[count]].HexID2;

			SSIDBData[SSData.TriggerConditions3[count] + 2] = SSTCID[SSCurEffect.TriggerConditions3[count]].HexID1;
			SSIDBData[SSData.TriggerConditions3[count] + 3] = SSTCID[SSCurEffect.TriggerConditions3[count]].HexID2;

			SSIDBData[SSData.TriggerConditions4[count] + 2] = SSTCID[SSCurEffect.TriggerConditions4[count]].HexID1;
			SSIDBData[SSData.TriggerConditions4[count] + 3] = SSTCID[SSCurEffect.TriggerConditions4[count]].HexID2;

			SSIDBData[SSData.TriggerConditions5[count] + 2] = SSTCID[SSCurEffect.TriggerConditions5[count]].HexID1;
			SSIDBData[SSData.TriggerConditions5[count] + 3] = SSTCID[SSCurEffect.TriggerConditions5[count]].HexID2;

			SSIDBData[SSData.Timer[count] + 2] = SSSetting.TimerID1[SSCurEffect.Timer[count]];
			SSIDBData[SSData.Timer[count] + 3] = SSSetting.TimerID2[SSCurEffect.Timer[count]];

			SSIDBData[SSData.Health[count]] = SSEAID[SSCurEffect.Health[count]].HexID1;
			SSIDBData[SSData.Health[count] + 1] = SSEAID[SSCurEffect.Health[count]].HexID2;
			SSIDBData[SSData.Health[count] + 2] = SSEAID[SSCurEffect.Health[count]].HexID3;
			SSIDBData[SSData.Health[count] + 3] = SSEAID[SSCurEffect.Health[count]].HexID4;

			SSIDBData[SSData.Ki[count]] = SSEAID[SSCurEffect.Ki[count]].HexID1;
			SSIDBData[SSData.Ki[count] + 1] = SSEAID[SSCurEffect.Ki[count]].HexID2;
			SSIDBData[SSData.Ki[count] + 2] = SSEAID[SSCurEffect.Ki[count]].HexID3;
			SSIDBData[SSData.Ki[count] + 3] = SSEAID[SSCurEffect.Ki[count]].HexID4;

			SSIDBData[SSData.Ki_RegenRate[count]] = SSEAID[SSCurEffect.Ki_RegenRate[count]].HexID1;
			SSIDBData[SSData.Ki_RegenRate[count] + 1] = SSEAID[SSCurEffect.Ki_RegenRate[count]].HexID2;
			SSIDBData[SSData.Ki_RegenRate[count] + 2] = SSEAID[SSCurEffect.Ki_RegenRate[count]].HexID3;
			SSIDBData[SSData.Ki_RegenRate[count] + 3] = SSEAID[SSCurEffect.Ki_RegenRate[count]].HexID4;

			SSIDBData[SSData.Stamina[count]] = SSEAID[SSCurEffect.Stamina[count]].HexID1;
			SSIDBData[SSData.Stamina[count] + 1] = SSEAID[SSCurEffect.Stamina[count]].HexID2;
			SSIDBData[SSData.Stamina[count] + 2] = SSEAID[SSCurEffect.Stamina[count]].HexID3;
			SSIDBData[SSData.Stamina[count] + 3] = SSEAID[SSCurEffect.Stamina[count]].HexID4;

			SSIDBData[SSData.Stamina_RegenRate[count]] = SSEAID[SSCurEffect.Stamina_RegenRate[count]].HexID1;
			SSIDBData[SSData.Stamina_RegenRate[count] + 1] = SSEAID[SSCurEffect.Stamina_RegenRate[count]].HexID2;
			SSIDBData[SSData.Stamina_RegenRate[count] + 2] = SSEAID[SSCurEffect.Stamina_RegenRate[count]].HexID3;
			SSIDBData[SSData.Stamina_RegenRate[count] + 3] = SSEAID[SSCurEffect.Stamina_RegenRate[count]].HexID4;

			SSIDBData[SSData.Ground_Speed[count]] = SSEAID[SSCurEffect.Ground_Speed[count]].HexID1;
			SSIDBData[SSData.Ground_Speed[count] + 1] = SSEAID[SSCurEffect.Ground_Speed[count]].HexID2;
			SSIDBData[SSData.Ground_Speed[count] + 2] = SSEAID[SSCurEffect.Ground_Speed[count]].HexID3;
			SSIDBData[SSData.Ground_Speed[count] + 3] = SSEAID[SSCurEffect.Ground_Speed[count]].HexID4;

			SSIDBData[SSData.Flight_Speed[count]] = SSEAID[SSCurEffect.Flight_Speed[count]].HexID1;
			SSIDBData[SSData.Flight_Speed[count] + 1] = SSEAID[SSCurEffect.Flight_Speed[count]].HexID2;
			SSIDBData[SSData.Flight_Speed[count] + 2] = SSEAID[SSCurEffect.Flight_Speed[count]].HexID3;
			SSIDBData[SSData.Flight_Speed[count] + 3] = SSEAID[SSCurEffect.Flight_Speed[count]].HexID4;

			SSIDBData[SSData.Boost_Speed[count]] = SSEAID[SSCurEffect.Boost_Speed[count]].HexID1;
			SSIDBData[SSData.Boost_Speed[count] + 1] = SSEAID[SSCurEffect.Boost_Speed[count]].HexID2;
			SSIDBData[SSData.Boost_Speed[count] + 2] = SSEAID[SSCurEffect.Boost_Speed[count]].HexID3;
			SSIDBData[SSData.Boost_Speed[count] + 3] = SSEAID[SSCurEffect.Boost_Speed[count]].HexID4;

			SSIDBData[SSData.Dash_Speed[count]] = SSEAID[SSCurEffect.Dash_Speed[count]].HexID1;
			SSIDBData[SSData.Dash_Speed[count] + 1] = SSEAID[SSCurEffect.Dash_Speed[count]].HexID2;
			SSIDBData[SSData.Dash_Speed[count] + 2] = SSEAID[SSCurEffect.Dash_Speed[count]].HexID3;
			SSIDBData[SSData.Dash_Speed[count] + 3] = SSEAID[SSCurEffect.Dash_Speed[count]].HexID4;

			SSIDBData[SSData.Basic_Attack[count]] = SSEAID[SSCurEffect.Basic_Attack[count]].HexID1;
			SSIDBData[SSData.Basic_Attack[count] + 1] = SSEAID[SSCurEffect.Basic_Attack[count]].HexID2;
			SSIDBData[SSData.Basic_Attack[count] + 2] = SSEAID[SSCurEffect.Basic_Attack[count]].HexID3;
			SSIDBData[SSData.Basic_Attack[count] + 3] = SSEAID[SSCurEffect.Basic_Attack[count]].HexID4;

			SSIDBData[SSData.Ki_Blast[count]] = SSEAID[SSCurEffect.Ki_Blast[count]].HexID1;
			SSIDBData[SSData.Ki_Blast[count] + 1] = SSEAID[SSCurEffect.Ki_Blast[count]].HexID2;
			SSIDBData[SSData.Ki_Blast[count] + 2] = SSEAID[SSCurEffect.Ki_Blast[count]].HexID3;
			SSIDBData[SSData.Ki_Blast[count] + 3] = SSEAID[SSCurEffect.Ki_Blast[count]].HexID4;

			SSIDBData[SSData.Strike_Super[count]] = SSEAID[SSCurEffect.Strike_Super[count]].HexID1;
			SSIDBData[SSData.Strike_Super[count] + 1] = SSEAID[SSCurEffect.Strike_Super[count]].HexID2;
			SSIDBData[SSData.Strike_Super[count] + 2] = SSEAID[SSCurEffect.Strike_Super[count]].HexID3;
			SSIDBData[SSData.Strike_Super[count] + 3] = SSEAID[SSCurEffect.Strike_Super[count]].HexID4;

			SSIDBData[SSData.Ki_Blast_Super[count]] = SSEAID[SSCurEffect.Ki_Blast_Super[count]].HexID1;
			SSIDBData[SSData.Ki_Blast_Super[count] + 1] = SSEAID[SSCurEffect.Ki_Blast_Super[count]].HexID2;
			SSIDBData[SSData.Ki_Blast_Super[count] + 2] = SSEAID[SSCurEffect.Ki_Blast_Super[count]].HexID3;
			SSIDBData[SSData.Ki_Blast_Super[count] + 3] = SSEAID[SSCurEffect.Ki_Blast_Super[count]].HexID4;

			SSIDBData[SSData.Basic_Attack_Dmg[count]] = SSEAID[SSCurEffect.Basic_Attack_Dmg[count]].HexID1;
			SSIDBData[SSData.Basic_Attack_Dmg[count] + 1] = SSEAID[SSCurEffect.Basic_Attack_Dmg[count]].HexID2;
			SSIDBData[SSData.Basic_Attack_Dmg[count] + 2] = SSEAID[SSCurEffect.Basic_Attack_Dmg[count]].HexID3;
			SSIDBData[SSData.Basic_Attack_Dmg[count] + 3] = SSEAID[SSCurEffect.Basic_Attack_Dmg[count]].HexID4;

			SSIDBData[SSData.Ki_Blast_Dmg[count]] = SSEAID[SSCurEffect.Ki_Blast_Dmg[count]].HexID1;
			SSIDBData[SSData.Ki_Blast_Dmg[count] + 1] = SSEAID[SSCurEffect.Ki_Blast_Dmg[count]].HexID2;
			SSIDBData[SSData.Ki_Blast_Dmg[count] + 2] = SSEAID[SSCurEffect.Ki_Blast_Dmg[count]].HexID3;
			SSIDBData[SSData.Ki_Blast_Dmg[count] + 3] = SSEAID[SSCurEffect.Ki_Blast_Dmg[count]].HexID4;

			SSIDBData[SSData.Strike_Super_Dmg[count]] = SSEAID[SSCurEffect.Strike_Super_Dmg[count]].HexID1;
			SSIDBData[SSData.Strike_Super_Dmg[count] + 1] = SSEAID[SSCurEffect.Strike_Super_Dmg[count]].HexID2;
			SSIDBData[SSData.Strike_Super_Dmg[count] + 2] = SSEAID[SSCurEffect.Strike_Super_Dmg[count]].HexID3;
			SSIDBData[SSData.Strike_Super_Dmg[count] + 3] = SSEAID[SSCurEffect.Strike_Super_Dmg[count]].HexID4;

			SSIDBData[SSData.Ki_Blast_Super_Dmg[count]] = SSEAID[SSCurEffect.Ki_Blast_Super_Dmg[count]].HexID1;
			SSIDBData[SSData.Ki_Blast_Super_Dmg[count] + 1] = SSEAID[SSCurEffect.Ki_Blast_Super_Dmg[count]].HexID2;
			SSIDBData[SSData.Ki_Blast_Super_Dmg[count] + 2] = SSEAID[SSCurEffect.Ki_Blast_Super_Dmg[count]].HexID3;
			SSIDBData[SSData.Ki_Blast_Super_Dmg[count] + 3] = SSEAID[SSCurEffect.Ki_Blast_Super_Dmg[count]].HexID4;

			SSIDBData[SSData.Revive_Speed[count]] = SSEAID[SSCurEffect.Revive_Speed[count]].HexID1;
			SSIDBData[SSData.Revive_Speed[count] + 1] = SSEAID[SSCurEffect.Revive_Speed[count]].HexID2;
			SSIDBData[SSData.Revive_Speed[count] + 2] = SSEAID[SSCurEffect.Revive_Speed[count]].HexID3;
			SSIDBData[SSData.Revive_Speed[count] + 3] = SSEAID[SSCurEffect.Revive_Speed[count]].HexID4;
			count++;
		}
	}
	else
	{
		SetWindowText(GetDlgItem(hDlg, IDC_EDITERROR3), L"No IDB Loaded");
	}
}

void DisplayEffect(HWND hDlg, int TabNum)
{
	HWND hTemp;

	hTemp = GetDlgItem(hDlg, IDC_COMBO3);
	SendMessage(hTemp, CB_SETCURSEL, SSCurEffect.Effect[TabNum], 0);
	hTemp = GetDlgItem(hDlg, IDC_COMBO4);
	SendMessage(hTemp, CB_SETCURSEL, SSCurEffect.EffectAmount[TabNum], 0);
	hTemp = GetDlgItem(hDlg, IDC_COMBO5);
	SendMessage(hTemp, CB_SETCURSEL, SSCurEffect.Flag[TabNum], 0);
	hTemp = GetDlgItem(hDlg, IDC_COMBO6);
	SendMessage(hTemp, CB_SETCURSEL, SSCurEffect.Trigger[TabNum], 0);
	hTemp = GetDlgItem(hDlg, IDC_COMBO7);
	SendMessage(hTemp, CB_SETCURSEL, SSCurEffect.Target[TabNum], 0);
	hTemp = GetDlgItem(hDlg, IDC_COMBO8);
	SendMessage(hTemp, CB_SETCURSEL, SSCurEffect.TriggerConditions1[TabNum], 0);
	hTemp = GetDlgItem(hDlg, IDC_COMBO9);
	SendMessage(hTemp, CB_SETCURSEL, SSCurEffect.TriggerConditions2[TabNum], 0);
	hTemp = GetDlgItem(hDlg, IDC_COMBO10);
	SendMessage(hTemp, CB_SETCURSEL, SSCurEffect.TriggerConditions3[TabNum], 0);
	hTemp = GetDlgItem(hDlg, IDC_COMBO30);
	SendMessage(hTemp, CB_SETCURSEL, SSCurEffect.TriggerConditions4[TabNum], 0);
	hTemp = GetDlgItem(hDlg, IDC_COMBO31);
	SendMessage(hTemp, CB_SETCURSEL, SSCurEffect.TriggerConditions5[TabNum], 0);
	hTemp = GetDlgItem(hDlg, IDC_COMBO29);
	SendMessage(hTemp, CB_SETCURSEL, SSCurEffect.Timer[TabNum], 0);
	hTemp = GetDlgItem(hDlg, IDC_COMBO11);
	SendMessage(hTemp, CB_SETCURSEL, SSCurEffect.Health[TabNum], 0);
	hTemp = GetDlgItem(hDlg, IDC_COMBO12);
	SendMessage(hTemp, CB_SETCURSEL, SSCurEffect.Ki[TabNum], 0);
	hTemp = GetDlgItem(hDlg, IDC_COMBO13);
	SendMessage(hTemp, CB_SETCURSEL, SSCurEffect.Ki_RegenRate[TabNum], 0);
	hTemp = GetDlgItem(hDlg, IDC_COMBO14);
	SendMessage(hTemp, CB_SETCURSEL, SSCurEffect.Stamina[TabNum], 0);
	hTemp = GetDlgItem(hDlg, IDC_COMBO15);
	SendMessage(hTemp, CB_SETCURSEL, SSCurEffect.Stamina_RegenRate[TabNum], 0);
	hTemp = GetDlgItem(hDlg, IDC_COMBO16);
	SendMessage(hTemp, CB_SETCURSEL, SSCurEffect.Ground_Speed[TabNum], 0);
	hTemp = GetDlgItem(hDlg, IDC_COMBO17);
	SendMessage(hTemp, CB_SETCURSEL, SSCurEffect.Flight_Speed[TabNum], 0);
	hTemp = GetDlgItem(hDlg, IDC_COMBO18);
	SendMessage(hTemp, CB_SETCURSEL, SSCurEffect.Boost_Speed[TabNum], 0);
	hTemp = GetDlgItem(hDlg, IDC_COMBO19);
	SendMessage(hTemp, CB_SETCURSEL, SSCurEffect.Dash_Speed[TabNum], 0);
	hTemp = GetDlgItem(hDlg, IDC_COMBO21);
	SendMessage(hTemp, CB_SETCURSEL, SSCurEffect.Basic_Attack[TabNum], 0);
	hTemp = GetDlgItem(hDlg, IDC_COMBO22);
	SendMessage(hTemp, CB_SETCURSEL, SSCurEffect.Ki_Blast[TabNum], 0);
	hTemp = GetDlgItem(hDlg, IDC_COMBO23);
	SendMessage(hTemp, CB_SETCURSEL, SSCurEffect.Strike_Super[TabNum], 0);
	hTemp = GetDlgItem(hDlg, IDC_COMBO24);
	SendMessage(hTemp, CB_SETCURSEL, SSCurEffect.Ki_Blast_Super[TabNum], 0);
	hTemp = GetDlgItem(hDlg, IDC_COMBO25);
	SendMessage(hTemp, CB_SETCURSEL, SSCurEffect.Basic_Attack_Dmg[TabNum], 0);
	hTemp = GetDlgItem(hDlg, IDC_COMBO26);
	SendMessage(hTemp, CB_SETCURSEL, SSCurEffect.Ki_Blast_Dmg[TabNum], 0);
	hTemp = GetDlgItem(hDlg, IDC_COMBO27);
	SendMessage(hTemp, CB_SETCURSEL, SSCurEffect.Strike_Super_Dmg[TabNum], 0);
	hTemp = GetDlgItem(hDlg, IDC_COMBO28);
	SendMessage(hTemp, CB_SETCURSEL, SSCurEffect.Ki_Blast_Super_Dmg[TabNum], 0);
	hTemp = GetDlgItem(hDlg, IDC_COMBO20);
	SendMessage(hTemp, CB_SETCURSEL, SSCurEffect.Revive_Speed[TabNum], 0);
}

void GetCurEffect(HWND hDlg, int TabNum)
{
	HWND hTemp;

	hTemp = GetDlgItem(hDlg, IDC_COMBO3);
	SSCurEffect.Effect[TabNum] = SendMessage(hTemp, CB_GETCURSEL, 0, 0);
	hTemp = GetDlgItem(hDlg, IDC_COMBO4);
	SSCurEffect.EffectAmount[TabNum] = SendMessage(hTemp, CB_GETCURSEL, 0, 0);
	hTemp = GetDlgItem(hDlg, IDC_COMBO5);
	SSCurEffect.Flag[TabNum] = SendMessage(hTemp, CB_GETCURSEL, 0, 0);
	hTemp = GetDlgItem(hDlg, IDC_COMBO6);
	SSCurEffect.Trigger[TabNum] = SendMessage(hTemp, CB_GETCURSEL, 0, 0);
	hTemp = GetDlgItem(hDlg, IDC_COMBO7);
	SSCurEffect.Target[TabNum] = SendMessage(hTemp, CB_GETCURSEL, 0, 0);
	hTemp = GetDlgItem(hDlg, IDC_COMBO8);
	SSCurEffect.TriggerConditions1[TabNum] = SendMessage(hTemp, CB_GETCURSEL, 0, 0);
	hTemp = GetDlgItem(hDlg, IDC_COMBO9);
	SSCurEffect.TriggerConditions2[TabNum] = SendMessage(hTemp, CB_GETCURSEL, 0, 0);
	hTemp = GetDlgItem(hDlg, IDC_COMBO10);
	SSCurEffect.TriggerConditions3[TabNum] = SendMessage(hTemp, CB_GETCURSEL, 0, 0);
	hTemp = GetDlgItem(hDlg, IDC_COMBO30);
	SSCurEffect.TriggerConditions4[TabNum] = SendMessage(hTemp, CB_GETCURSEL, 0, 0);
	hTemp = GetDlgItem(hDlg, IDC_COMBO31);
	SSCurEffect.TriggerConditions5[TabNum] = SendMessage(hTemp, CB_GETCURSEL, 0, 0);
	hTemp = GetDlgItem(hDlg, IDC_COMBO29);
	SSCurEffect.Timer[TabNum] = SendMessage(hTemp, CB_GETCURSEL, 0, 0);
	hTemp = GetDlgItem(hDlg, IDC_COMBO11);
	SSCurEffect.Health[TabNum] = SendMessage(hTemp, CB_GETCURSEL, 0, 0);
	hTemp = GetDlgItem(hDlg, IDC_COMBO12);
	SSCurEffect.Ki[TabNum] = SendMessage(hTemp, CB_GETCURSEL, 0, 0);
	hTemp = GetDlgItem(hDlg, IDC_COMBO13);
	SSCurEffect.Ki_RegenRate[TabNum] = SendMessage(hTemp, CB_GETCURSEL, 0, 0);
	hTemp = GetDlgItem(hDlg, IDC_COMBO14);
	SSCurEffect.Stamina[TabNum] = SendMessage(hTemp, CB_GETCURSEL, 0, 0);
	hTemp = GetDlgItem(hDlg, IDC_COMBO15);
	SSCurEffect.Stamina_RegenRate[TabNum] = SendMessage(hTemp, CB_GETCURSEL, 0, 0);
	hTemp = GetDlgItem(hDlg, IDC_COMBO16);
	SSCurEffect.Ground_Speed[TabNum] = SendMessage(hTemp, CB_GETCURSEL, 0, 0);
	hTemp = GetDlgItem(hDlg, IDC_COMBO17);
	SSCurEffect.Flight_Speed[TabNum] = SendMessage(hTemp, CB_GETCURSEL, 0, 0);
	hTemp = GetDlgItem(hDlg, IDC_COMBO18);
	SSCurEffect.Boost_Speed[TabNum] = SendMessage(hTemp, CB_GETCURSEL, 0, 0);
	hTemp = GetDlgItem(hDlg, IDC_COMBO19);
	SSCurEffect.Dash_Speed[TabNum] = SendMessage(hTemp, CB_GETCURSEL, 0, 0);
	hTemp = GetDlgItem(hDlg, IDC_COMBO21);
	SSCurEffect.Basic_Attack[TabNum] = SendMessage(hTemp, CB_GETCURSEL, 0, 0);
	hTemp = GetDlgItem(hDlg, IDC_COMBO22);
	SSCurEffect.Ki_Blast[TabNum] = SendMessage(hTemp, CB_GETCURSEL, 0, 0);
	hTemp = GetDlgItem(hDlg, IDC_COMBO23);
	SSCurEffect.Strike_Super[TabNum] = SendMessage(hTemp, CB_GETCURSEL, 0, 0);
	hTemp = GetDlgItem(hDlg, IDC_COMBO24);
	SSCurEffect.Ki_Blast_Super[TabNum] = SendMessage(hTemp, CB_GETCURSEL, 0, 0);
	hTemp = GetDlgItem(hDlg, IDC_COMBO25);
	SSCurEffect.Basic_Attack_Dmg[TabNum] = SendMessage(hTemp, CB_GETCURSEL, 0, 0);
	hTemp = GetDlgItem(hDlg, IDC_COMBO26);
	SSCurEffect.Ki_Blast_Dmg[TabNum] = SendMessage(hTemp, CB_GETCURSEL, 0, 0);
	hTemp = GetDlgItem(hDlg, IDC_COMBO27);
	SSCurEffect.Strike_Super_Dmg[TabNum] = SendMessage(hTemp, CB_GETCURSEL, 0, 0);
	hTemp = GetDlgItem(hDlg, IDC_COMBO28);
	SSCurEffect.Ki_Blast_Super_Dmg[TabNum] = SendMessage(hTemp, CB_GETCURSEL, 0, 0);
	hTemp = GetDlgItem(hDlg, IDC_COMBO20);
	SSCurEffect.Revive_Speed[TabNum] = SendMessage(hTemp, CB_GETCURSEL, 0, 0);
}

void SetAllCurEffect()
{
	int TabNum = 0;

	while (TabNum < 3)
	{
		SSCurEffect.Effect[TabNum] = SearchEffectID(SSData.Effect[TabNum]);
		SSCurEffect.EffectAmount[TabNum] = SearchEffectAmountID(SSData.EffectAmount[TabNum]);
		SSCurEffect.Flag[TabNum] = SearchFlagID(SSData.Flag[TabNum]);
		SSCurEffect.Trigger[TabNum] = SearchTriggerID(SSData.Trigger[TabNum]);
		SSCurEffect.Target[TabNum] = SearchTargetID(SSData.Target[TabNum]);
		SSCurEffect.TriggerConditions1[TabNum] = SearchTCID(SSData.TriggerConditions1[TabNum]);
		SSCurEffect.TriggerConditions2[TabNum] = SearchTCID(SSData.TriggerConditions2[TabNum]);
		SSCurEffect.TriggerConditions3[TabNum] = SearchTCID(SSData.TriggerConditions3[TabNum]);
		SSCurEffect.TriggerConditions4[TabNum] = SearchTCID(SSData.TriggerConditions4[TabNum]);
		SSCurEffect.TriggerConditions5[TabNum] = SearchTCID(SSData.TriggerConditions5[TabNum]);
		SSCurEffect.Timer[TabNum] = SearchTimerID(SSData.Timer[TabNum]);
		SSCurEffect.Health[TabNum] = SearchEffectAmountID(SSData.Health[TabNum]);
		SSCurEffect.Ki[TabNum] = SearchEffectAmountID(SSData.Ki[TabNum]);
		SSCurEffect.Ki_RegenRate[TabNum] = SearchEffectAmountID(SSData.Ki_RegenRate[TabNum]);
		SSCurEffect.Stamina[TabNum] = SearchEffectAmountID(SSData.Stamina[TabNum]);
		SSCurEffect.Stamina_RegenRate[TabNum] = SearchEffectAmountID(SSData.Stamina_RegenRate[TabNum]);
		SSCurEffect.Ground_Speed[TabNum] = SearchEffectAmountID(SSData.Ground_Speed[TabNum]);
		SSCurEffect.Flight_Speed[TabNum] = SearchEffectAmountID(SSData.Flight_Speed[TabNum]);
		SSCurEffect.Boost_Speed[TabNum] = SearchEffectAmountID(SSData.Boost_Speed[TabNum]);
		SSCurEffect.Dash_Speed[TabNum] = SearchEffectAmountID(SSData.Dash_Speed[TabNum]);
		SSCurEffect.Basic_Attack[TabNum] = SearchEffectAmountID(SSData.Basic_Attack[TabNum]);
		SSCurEffect.Ki_Blast[TabNum] = SearchEffectAmountID(SSData.Ki_Blast[TabNum]);
		SSCurEffect.Strike_Super[TabNum] = SearchEffectAmountID(SSData.Strike_Super[TabNum]);
		SSCurEffect.Ki_Blast_Super[TabNum] = SearchEffectAmountID(SSData.Ki_Blast_Super[TabNum]);
		SSCurEffect.Basic_Attack_Dmg[TabNum] = SearchEffectAmountID(SSData.Basic_Attack_Dmg[TabNum]);
		SSCurEffect.Ki_Blast_Dmg[TabNum] = SearchEffectAmountID(SSData.Ki_Blast_Dmg[TabNum]);
		SSCurEffect.Strike_Super_Dmg[TabNum] = SearchEffectAmountID(SSData.Strike_Super_Dmg[TabNum]);
		SSCurEffect.Ki_Blast_Super_Dmg[TabNum] = SearchEffectAmountID(SSData.Ki_Blast_Super_Dmg[TabNum]);
		SSCurEffect.Revive_Speed[TabNum] = SearchEffectAmountID(SSData.Revive_Speed[TabNum]);

		TabNum++;
	}
}

void IDBSetup()
{

	if (!SSIDBData.empty())
	{
		int count = 0x15190, InsertTotal = 0, ID = 0x78;
		std::string InsertValue;
		InsertValue.resize(45 * 16);
		InsertValue[8] = 9, InsertValue[0x0a] = 0xff, InsertValue[0x0b] = 0xff, InsertValue[0x0c] = 0xff, InsertValue[0x0d] = 0xf7, 
        InsertValue[0x0e] = 0xff, InsertValue[0x0f] = 0xff,InsertValue[0x18] = 0xff, 
			InsertValue[0x38] = 0x01, InsertValue[0x3e] = 0x80, InsertValue[0x3f] = 0xbf, InsertValue[0x42] = 0x80,
			InsertValue[0x43] = 0xbf, InsertValue[0x46] = 0x80, InsertValue[0x47] = 0xbf, InsertValue[0x4a] = 0x80, InsertValue[0x4b] = 0xbf,
			InsertValue[0x4e] = 0x80, InsertValue[0x4f] = 0xbf, InsertValue[0x52] = 0x80, InsertValue[0x53] = 0xbf, InsertValue[0x56] = 0x80,
			InsertValue[0x57] = 0xbf, InsertValue[0x58] = 0xff, InsertValue[0x59] = 0xff, InsertValue[0x5a] = 0xff, InsertValue[0x5b] = 0xff,
			InsertValue[0x5c] = 0xff, InsertValue[0x5d] = 0xff, InsertValue[0x5e] = 0xff, InsertValue[0x5f] = 0xff,
			InsertValue[0x7c] = 0x46, InsertValue[0x84] = 0x47, InsertValue[0x88] = 0xff, InsertValue[0x89] = 0xff, InsertValue[0x8a] = 0xff,
			InsertValue[0x8b] = 0xff;
		InsertValue[(14 * 16) + 0x38] = 0x01, InsertValue[(14 * 16) + 0x3e] = 0x80, InsertValue[(14 * 16) + 0x3f] = 0xbf,
			InsertValue[(14 * 16) + 0x42] = 0x80, InsertValue[(14 * 16) + 0x43] = 0xbf, InsertValue[(14 * 16) + 0x46] = 0x80,
			InsertValue[(14 * 16) + 0x47] = 0xbf, InsertValue[(14 * 16) + 0x4a] = 0x80, InsertValue[(14 * 16) + 0x4b] = 0xbf,
			InsertValue[(14 * 16) + 0x4e] = 0x80, InsertValue[(14 * 16) + 0x4f] = 0xbf, InsertValue[(14 * 16) + 0x52] = 0x80,
			InsertValue[(14 * 16) + 0x53] = 0xbf, InsertValue[(14 * 16) + 0x56] = 0x80, InsertValue[(14 * 16) + 0x57] = 0xbf,
			InsertValue[(14 * 16) + 0x58] = 0xff, InsertValue[(14 * 16) + 0x59] = 0xff, InsertValue[(14 * 16) + 0x5a] = 0xff,
			InsertValue[(14 * 16) + 0x5b] = 0xff, InsertValue[(14 * 16) + 0x5c] = 0xff, InsertValue[(14 * 16) + 0x5d] = 0xff,
			InsertValue[(14 * 16) + 0x5e] = 0xff, InsertValue[(14 * 16) + 0x5f] = 0xff, InsertValue[(14 * 16) + 0x7c] = 0x46,
			InsertValue[(14 * 16) + 0x84] = 0x47, InsertValue[(14 * 16) + 0x88] = 0xff, InsertValue[(14 * 16) + 0x89] = 0xff,
			InsertValue[(14 * 16) + 0x8a] = 0xff, InsertValue[(14 * 16) + 0x8b] = 0xff; InsertValue[(14 * 16) + 0x38] = 0x01,
			InsertValue[(14 * 16) + 0x3e] = 0x80, InsertValue[(14 * 16) + 0x3f] = 0xbf;
		InsertValue[(2 * 14 * 16) + 0x38] = 0x01, InsertValue[(2 * 14 * 16) + 0x3e] = 0x80, InsertValue[(2 * 14 * 16) + 0x3f] = 0xbf,
			InsertValue[(2 * 14 * 16) + 0x42] = 0x80, InsertValue[(2 * 14 * 16) + 0x43] = 0xbf, InsertValue[(2 * 14 * 16) + 0x46] = 0x80,
			InsertValue[(2 * 14 * 16) + 0x47] = 0xbf, InsertValue[(2 * 14 * 16) + 0x4a] = 0x80, InsertValue[(2 * 14 * 16) + 0x4b] = 0xbf,
			InsertValue[(2 * 14 * 16) + 0x4e] = 0x80, InsertValue[(2 * 14 * 16) + 0x4f] = 0xbf, InsertValue[(2 * 14 * 16) + 0x52] = 0x80,
			InsertValue[(2 * 14 * 16) + 0x53] = 0xbf, InsertValue[(2 * 14 * 16) + 0x56] = 0x80, InsertValue[(2 * 14 * 16) + 0x57] = 0xbf,
			InsertValue[(2 * 14 * 16) + 0x58] = 0xff, InsertValue[(2 * 14 * 16) + 0x59] = 0xff, InsertValue[(2 * 14 * 16) + 0x5a] = 0xff,
			InsertValue[(2 * 14 * 16) + 0x5b] = 0xff, InsertValue[(2 * 14 * 16) + 0x5c] = 0xff, InsertValue[(2 * 14 * 16) + 0x5d] = 0xff,
			InsertValue[(2 * 14 * 16) + 0x5e] = 0xff, InsertValue[(2 * 14 * 16) + 0x5f] = 0xff,
			InsertValue[(2 * 14 * 16) + 0x7c] = 0x46, InsertValue[(2 * 14 * 16) + 0x84] = 0x47, InsertValue[(2 * 14 * 16) + 0x88] = 0xff,
			InsertValue[(2 * 14 * 16) + 0x89] = 0xff, InsertValue[(2 * 14 * 16) + 0x8a] = 0xff, InsertValue[(2 * 14 * 16) + 0x8b] = 0xff;

			

		 if ((uint8_t)SSIDBData[0x08] < 0xd2)
		 {

			 while (InsertTotal < 51)
			 {
				 InsertValue[0] = ID, InsertValue[2] = 1, InsertValue[4] = ID, InsertValue[6] = ID;
				 SSIDBData.insert(count, InsertValue);
				 ID += 1;
				 InsertTotal += 1;
				 count += 45 * 16;
			 }

			 SSIDBData[0x8] = (uint8_t)SSIDBData[0x8] + InsertTotal;
			 saveFile(SSIDBFile, SSIDBData);
		 }
	}
}
