#include "Header.h"

void LoadSoulList()
{
	openFile("Data/Super Soul ID.ini", SoulSetting);
	std::istringstream TempStream(SoulSetting);
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
		SuperSoulID[SoulCount].HexID = CTempHexID;
		SuperSoulID[SoulCount].Name = CTempValue;
#ifdef _DEBUG
		std::cout << SuperSoulID[SoulCount].HexID << " - " << SuperSoulID[SoulCount].Name << std::endl;
#endif
		memset(CTempValue, 0, strlen(CTempValue));
		SoulCount++;
	}
}

void LoadPSC(STATHEADER *HData, STAT *Data, std::string PSCData)
{
	int count = 0, offset = 0x10;
	std::string CHex;
	CHex.resize(10);

	HData[count].CharHexID = (uint8_t)PSCData[offset];
	HData[count].CostumeAmount = (uint8_t)PSCData[offset + 4];
	count += 1, offset += 12;

	while (PSCData[offset] != 00)
	{
		HData[count].CharHexID = (uint8_t)PSCData[offset];
		HData[count].CostumeAmount = (uint8_t)PSCData[offset + 4];
		PSCCosCount += (uint8_t)PSCData[offset + 4];

		count += 1, offset += 12;
	}
	count = 0;

	while (count < PSCCosCount)
	{
		Data[count].Offset = offset;
		Data[count].CostumeID = PSCData[offset];
		Data[count].Camera_Position = PSCData[offset + 8];
		CHex[0] = PSCData[offset + 20], CHex[1] = PSCData[offset + 21], CHex[2] = PSCData[offset + 22], CHex[3] = PSCData[offset + 23];
		Data[count].Health = HextoFloat(CHex);//20
		CHex[0] = PSCData[offset + 28], CHex[1] = PSCData[offset + 29], CHex[2] = PSCData[offset + 30], CHex[3] = PSCData[offset + 31];
		Data[count].Ki = HextoFloat(CHex); //28
		CHex[0] = PSCData[offset + 32], CHex[1] = PSCData[offset + 33], CHex[2] = PSCData[offset + 34], CHex[3] = PSCData[offset + 35];
		Data[count].Ki_Recharge = HextoFloat(CHex); //32
		CHex[0] = PSCData[offset + 48], CHex[1] = PSCData[offset + 49], CHex[2] = PSCData[offset + 50], CHex[3] = PSCData[offset + 51];
		Data[count].Stamina = HextoFloat(CHex); //48
		CHex[0] = PSCData[offset + 52], CHex[1] = PSCData[offset + 53], CHex[2] = PSCData[offset + 54], CHex[3] = PSCData[offset + 55];
		Data[count].Stamina_RechargeM = HextoFloat(CHex); //52
		CHex[0] = PSCData[offset + 56], CHex[1] = PSCData[offset + 57], CHex[2] = PSCData[offset + 58], CHex[3] = PSCData[offset + 59];
		Data[count].Stamina_RechargeA = HextoFloat(CHex); //56
		CHex[0] = PSCData[offset + 60], CHex[1] = PSCData[offset + 61], CHex[2] = PSCData[offset + 62], CHex[3] = PSCData[offset + 63];
		Data[count].Stamina_RechargeG = HextoFloat(CHex); //60
		CHex[0] = PSCData[offset + 64], CHex[1] = PSCData[offset + 65], CHex[2] = PSCData[offset + 66], CHex[3] = PSCData[offset + 67];
		Data[count].Stamina_Drain1 = HextoFloat(CHex); //64
		CHex[0] = PSCData[offset + 68], CHex[1] = PSCData[offset + 69], CHex[2] = PSCData[offset + 70], CHex[3] = PSCData[offset + 71];
		Data[count].Stamina_Drain2 = HextoFloat(CHex); //68
		CHex[0] = PSCData[offset + 76], CHex[1] = PSCData[offset + 77], CHex[2] = PSCData[offset + 78], CHex[3] = PSCData[offset + 79];
		Data[count].Basic_Attack = HextoFloat(CHex); //76
		CHex[0] = PSCData[offset + 80], CHex[1] = PSCData[offset + 81], CHex[2] = PSCData[offset + 82], CHex[3] = PSCData[offset + 83];
		Data[count].Ki_Blast = HextoFloat(CHex); //80
		CHex[0] = PSCData[offset + 84], CHex[1] = PSCData[offset + 85], CHex[2] = PSCData[offset + 86], CHex[3] = PSCData[offset + 87];
		Data[count].Strike_Super = HextoFloat(CHex); //84
		CHex[0] = PSCData[offset + 88], CHex[1] = PSCData[offset + 89], CHex[2] = PSCData[offset + 90], CHex[3] = PSCData[offset + 91];
		Data[count].Ki_BlastSuper = HextoFloat(CHex); //88
		CHex[0] = PSCData[offset + 92], CHex[1] = PSCData[offset + 93], CHex[2] = PSCData[offset + 94], CHex[3] = PSCData[offset + 95];
		Data[count].Basic_Def = HextoFloat(CHex); //92
		CHex[0] = PSCData[offset + 96], CHex[1] = PSCData[offset + 97], CHex[2] = PSCData[offset + 98], CHex[3] = PSCData[offset + 99];
		Data[count].Ki_Blast_Def = HextoFloat(CHex); //96
		CHex[0] = PSCData[offset + 100], CHex[1] = PSCData[offset + 101], CHex[2] = PSCData[offset + 102], CHex[3] = PSCData[offset + 103];
		Data[count].Strike_Super_Def = HextoFloat(CHex); //100
		CHex[0] = PSCData[offset + 104], CHex[1] = PSCData[offset + 105], CHex[2] = PSCData[offset + 106], CHex[3] = PSCData[offset + 107];
		Data[count].Ki_BlastSuper_Def = HextoFloat(CHex); //104
		CHex[0] = PSCData[offset + 108], CHex[1] = PSCData[offset + 109], CHex[2] = PSCData[offset + 110], CHex[3] = PSCData[offset + 111];
		Data[count].Ground_Speed = HextoFloat(CHex); //108
		CHex[0] = PSCData[offset + 112], CHex[1] = PSCData[offset + 113], CHex[2] = PSCData[offset + 114], CHex[3] = PSCData[offset + 115];
		Data[count].Air_Speed = HextoFloat(CHex); //112
		CHex[0] = PSCData[offset + 116], CHex[1] = PSCData[offset + 117], CHex[2] = PSCData[offset + 118], CHex[3] = PSCData[offset + 119];
		Data[count].Boost_Speed = HextoFloat(CHex); //116
		CHex[0] = PSCData[offset + 120], CHex[1] = PSCData[offset + 121], CHex[2] = PSCData[offset + 122], CHex[3] = PSCData[offset + 123];
		Data[count].Dash_Distance = HextoFloat(CHex); //120
		CHex[0] = PSCData[offset + 128], CHex[1] = PSCData[offset + 129], CHex[2] = PSCData[offset + 130], CHex[3] = PSCData[offset + 131];
		Data[count].Reinforcement_Skill_Duration = HextoFloat(CHex); //128
		CHex[0] = PSCData[offset + 136], CHex[1] = PSCData[offset + 137], CHex[2] = PSCData[offset + 138], CHex[3] = PSCData[offset + 139];
		Data[count].RevivalHP = HextoFloat(CHex); //136
		CHex[0] = PSCData[offset + 144], CHex[1] = PSCData[offset + 145], CHex[2] = PSCData[offset + 146], CHex[3] = PSCData[offset + 147];
		Data[count].Reviving_Speed = HextoFloat(CHex); //144
		Data[count].Super_Soul = PSCData[offset + 180]; //180

		count++, offset += 0xc4;
	}

	return;
}

void DisplayStat(int index, HWND hDlg, STAT *Data)
{
	HWND hTemp;
	char Text[30];

	hTemp = GetDlgItem(hDlg, IDC_EDIT1);
	sprintf (Text, "%d", Data[index].Camera_Position);
	SetWindowTextA(hTemp, Text);
	hTemp = GetDlgItem(hDlg, IDC_EDIT2);
	sprintf(Text, "%f", Data[index].Health);
	SetWindowTextA(hTemp, Text);
	hTemp = GetDlgItem(hDlg, IDC_EDIT3);
	sprintf(Text, "%f", Data[index].Ki);
	SetWindowTextA(hTemp, Text);
	hTemp = GetDlgItem(hDlg, IDC_EDIT4);
	sprintf(Text, "%f", Data[index].Ki_Recharge);
	SetWindowTextA(hTemp, Text);
	hTemp = GetDlgItem(hDlg, IDC_EDIT5);
	sprintf(Text, "%f", Data[index].Stamina);
	SetWindowTextA(hTemp, Text);
	hTemp = GetDlgItem(hDlg, IDC_EDIT6);
	sprintf(Text, "%f", Data[index].Stamina_RechargeM);
	SetWindowTextA(hTemp, Text);
	hTemp = GetDlgItem(hDlg, IDC_EDIT7);
	sprintf(Text, "%f", Data[index].Stamina_RechargeA);
	SetWindowTextA(hTemp, Text);
	hTemp = GetDlgItem(hDlg, IDC_EDIT8);
	sprintf(Text, "%f", Data[index].Stamina_RechargeG);
	SetWindowTextA(hTemp, Text);
	hTemp = GetDlgItem(hDlg, IDC_EDIT9);
	sprintf(Text, "%f", Data[index].Stamina_Drain1);
	SetWindowTextA(hTemp, Text);
	hTemp = GetDlgItem(hDlg, IDC_EDIT10);
	sprintf(Text, "%f", Data[index].Stamina_Drain2);
	SetWindowTextA(hTemp, Text);
	hTemp = GetDlgItem(hDlg, IDC_EDIT11);
	sprintf(Text, "%f", Data[index].Basic_Attack);
	SetWindowTextA(hTemp, Text);
	hTemp = GetDlgItem(hDlg, IDC_EDIT12);
	sprintf(Text, "%f", Data[index].Ki_Blast);
	SetWindowTextA(hTemp, Text);
	hTemp = GetDlgItem(hDlg, IDC_EDIT13);
	sprintf(Text, "%f", Data[index].Strike_Super);
	SetWindowTextA(hTemp, Text);
	hTemp = GetDlgItem(hDlg, IDC_EDIT14);
	sprintf(Text, "%f", Data[index].Ki_BlastSuper);
	SetWindowTextA(hTemp, Text);
	hTemp = GetDlgItem(hDlg, IDC_EDIT15);
	sprintf(Text, "%f", Data[index].Basic_Def);
	SetWindowTextA(hTemp, Text);
	hTemp = GetDlgItem(hDlg, IDC_EDIT16);
	sprintf(Text, "%f", Data[index].Ki_Blast_Def);
	SetWindowTextA(hTemp, Text);
	hTemp = GetDlgItem(hDlg, IDC_EDIT17);
	sprintf(Text, "%f", Data[index].Strike_Super_Def);
	SetWindowTextA(hTemp, Text);
	hTemp = GetDlgItem(hDlg, IDC_EDIT18);
	sprintf(Text, "%f", Data[index].Ki_BlastSuper_Def);
	SetWindowTextA(hTemp, Text);
	hTemp = GetDlgItem(hDlg, IDC_EDIT19);
	sprintf(Text, "%f", Data[index].Ground_Speed);
	SetWindowTextA(hTemp, Text);
	hTemp = GetDlgItem(hDlg, IDC_EDIT20);
	sprintf(Text, "%f", Data[index].Air_Speed);
	SetWindowTextA(hTemp, Text);
	hTemp = GetDlgItem(hDlg, IDC_EDIT21);
	sprintf(Text, "%f", Data[index].Boost_Speed);
	SetWindowTextA(hTemp, Text);
	hTemp = GetDlgItem(hDlg, IDC_EDIT22);
	sprintf(Text, "%f", Data[index].Dash_Distance);
	SetWindowTextA(hTemp, Text);
	hTemp = GetDlgItem(hDlg, IDC_EDIT23);
	sprintf(Text, "%f", Data[index].Reinforcement_Skill_Duration);
	SetWindowTextA(hTemp, Text);
	hTemp = GetDlgItem(hDlg, IDC_EDIT24);
	sprintf(Text, "%f", Data[index].RevivalHP);
	SetWindowTextA(hTemp, Text);
	hTemp = GetDlgItem(hDlg, IDC_EDIT25);
	sprintf(Text, "%f", Data[index].Reviving_Speed);
	SetWindowTextA(hTemp, Text);
	hTemp = GetDlgItem(hDlg, IDC_COMBO3);
	SendMessage(hTemp, CB_SETCURSEL, Data[index].Super_Soul, 0);
}

void SetStat(HWND hDlg, int index, STAT *Data)
{
	HWND hTemp;
	char Text[10];
	int SSIndex  = 0;

	hTemp = GetDlgItem(hDlg, IDC_EDIT1);
	GetWindowTextA(hTemp, Text, 10);
	Data[index].Camera_Position = atoi(Text);
	hTemp = GetDlgItem(hDlg, IDC_EDIT2);
	GetWindowTextA(hTemp, Text, 10);
	Data[index].Health = atof(Text);
	hTemp = GetDlgItem(hDlg, IDC_EDIT3);
	GetWindowTextA(hTemp, Text, 10);
	Data[index].Ki = atof(Text);
	hTemp = GetDlgItem(hDlg, IDC_EDIT4);
	GetWindowTextA(hTemp, Text, 10);
	Data[index].Ki_Recharge = atof(Text);
	hTemp = GetDlgItem(hDlg, IDC_EDIT5);
	GetWindowTextA(hTemp, Text, 10);
	Data[index].Stamina = atof(Text);
	hTemp = GetDlgItem(hDlg, IDC_EDIT6);
	GetWindowTextA(hTemp, Text, 10);
	Data[index].Stamina_RechargeM = atof(Text);
	hTemp = GetDlgItem(hDlg, IDC_EDIT7);
	GetWindowTextA(hTemp, Text, 10);
	Data[index].Stamina_RechargeA = atof(Text);
	hTemp = GetDlgItem(hDlg, IDC_EDIT8);
	GetWindowTextA(hTemp, Text, 10);
	Data[index].Stamina_RechargeG = atof(Text);
	hTemp = GetDlgItem(hDlg, IDC_EDIT9);
	GetWindowTextA(hTemp, Text, 10);
	Data[index].Stamina_Drain1 = atof(Text);
	hTemp = GetDlgItem(hDlg, IDC_EDIT10);
	GetWindowTextA(hTemp, Text, 10);
	Data[index].Stamina_Drain2 = atof(Text);
	hTemp = GetDlgItem(hDlg, IDC_EDIT11);
	GetWindowTextA(hTemp, Text, 10);
	Data[index].Basic_Attack = atof(Text);
	hTemp = GetDlgItem(hDlg, IDC_EDIT12);
	GetWindowTextA(hTemp, Text, 10);
	Data[index].Ki_Blast = atof(Text);
	hTemp = GetDlgItem(hDlg, IDC_EDIT13);
	GetWindowTextA(hTemp, Text, 10);
	Data[index].Strike_Super = atof(Text);
	hTemp = GetDlgItem(hDlg, IDC_EDIT14);
	GetWindowTextA(hTemp, Text, 10);
	Data[index].Ki_BlastSuper = atof(Text);
	hTemp = GetDlgItem(hDlg, IDC_EDIT15);
	GetWindowTextA(hTemp, Text, 10);
	Data[index].Basic_Def = atof(Text);
	hTemp = GetDlgItem(hDlg, IDC_EDIT16);
	GetWindowTextA(hTemp, Text, 10);
	Data[index].Ki_Blast_Def = atof(Text);
	hTemp = GetDlgItem(hDlg, IDC_EDIT17);
	GetWindowTextA(hTemp, Text, 10);
	Data[index].Strike_Super_Def = atof(Text);
	hTemp = GetDlgItem(hDlg, IDC_EDIT18);
	GetWindowTextA(hTemp, Text, 10);
	Data[index].Ki_BlastSuper_Def = atof(Text);
	hTemp = GetDlgItem(hDlg, IDC_EDIT19);
	GetWindowTextA(hTemp, Text, 10);
	Data[index].Ground_Speed = atof(Text);
	hTemp = GetDlgItem(hDlg, IDC_EDIT20);
	GetWindowTextA(hTemp, Text, 10);
	Data[index].Air_Speed = atof(Text);
	hTemp = GetDlgItem(hDlg, IDC_EDIT21);
	GetWindowTextA(hTemp, Text, 10);
	Data[index].Boost_Speed = atof(Text);
	hTemp = GetDlgItem(hDlg, IDC_EDIT22);
	GetWindowTextA(hTemp, Text, 10);
	Data[index].Dash_Distance = atof(Text);
	hTemp = GetDlgItem(hDlg, IDC_EDIT23);
	GetWindowTextA(hTemp, Text, 10);
	Data[index].Reinforcement_Skill_Duration = atof(Text);
	hTemp = GetDlgItem(hDlg, IDC_EDIT24);
	GetWindowTextA(hTemp, Text, 10);
	Data[index].RevivalHP = atof(Text);
	hTemp = GetDlgItem(hDlg, IDC_EDIT25);
	GetWindowTextA(hTemp, Text, 10);
	Data[index].Reviving_Speed = atof(Text);
	hTemp = GetDlgItem(hDlg, IDC_COMBO3);
	SSIndex = SendMessage(hTemp, CB_GETCURSEL, 0, 0);
	Data[index].Super_Soul = SSIndex;
}

void SetAllStat(HWND hDlg, STAT *Data)
{
	HWND hTemp;
	LRESULT IncludeCAC, IncludeSS;
	char Text[10];
	int SSIndex = 0, CACIndexCheck = 0, count = 0, index = 0, maxChar = 0;

	while (HStat[count].CharHexID != 0x64) //find human male offset, to allow easy excemption of all CaC from set all  
	{
		CACIndexCheck += HStat[count].CostumeAmount;
		count++;
	}
	count = 0;
	while (count < CharCount) //calculate amount of char and costume; 
	{
		maxChar += HStat[count].CostumeAmount;
		count++;
	}
	IncludeCAC = SendMessage(GetDlgItem(hDlg, IDC_CHECK1), BM_GETCHECK, 0, 0);
	IncludeSS = SendMessage(GetDlgItem(hDlg, IDC_CHECK2), BM_GETCHECK, 0, 0);

	while (index < maxChar)
	{
		if (index >= CACIndexCheck && index <= (CACIndexCheck + 96) && IncludeCAC == BST_UNCHECKED) { index++; continue; }

		hTemp = GetDlgItem(hDlg, IDC_EDIT1);
		GetWindowTextA(hTemp, Text, 10);
		Data[index].Camera_Position = atoi(Text);
		hTemp = GetDlgItem(hDlg, IDC_EDIT2);
		GetWindowTextA(hTemp, Text, 10);
		Data[index].Health = atof(Text);
		hTemp = GetDlgItem(hDlg, IDC_EDIT3);
		GetWindowTextA(hTemp, Text, 10);
		Data[index].Ki = atof(Text);
		hTemp = GetDlgItem(hDlg, IDC_EDIT4);
		GetWindowTextA(hTemp, Text, 10);
		Data[index].Ki_Recharge = atof(Text);
		hTemp = GetDlgItem(hDlg, IDC_EDIT5);
		GetWindowTextA(hTemp, Text, 10);
		Data[index].Stamina = atof(Text);
		hTemp = GetDlgItem(hDlg, IDC_EDIT6);
		GetWindowTextA(hTemp, Text, 10);
		Data[index].Stamina_RechargeM = atof(Text);
		hTemp = GetDlgItem(hDlg, IDC_EDIT7);
		GetWindowTextA(hTemp, Text, 10);
		Data[index].Stamina_RechargeA = atof(Text);

		hTemp = GetDlgItem(hDlg, IDC_EDIT8);
		GetWindowTextA(hTemp, Text, 10);
		Data[index].Stamina_RechargeG = atof(Text);
		hTemp = GetDlgItem(hDlg, IDC_EDIT9);
		GetWindowTextA(hTemp, Text, 10);
		Data[index].Stamina_Drain1 = atof(Text);
		hTemp = GetDlgItem(hDlg, IDC_EDIT10);
		GetWindowTextA(hTemp, Text, 10);
		Data[index].Stamina_Drain2 = atof(Text);
		hTemp = GetDlgItem(hDlg, IDC_EDIT11);
		GetWindowTextA(hTemp, Text, 10);
		Data[index].Basic_Attack = atof(Text);
		hTemp = GetDlgItem(hDlg, IDC_EDIT12);
		GetWindowTextA(hTemp, Text, 10);
		Data[index].Ki_Blast = atof(Text);
		hTemp = GetDlgItem(hDlg, IDC_EDIT13);
		GetWindowTextA(hTemp, Text, 10);
		Data[index].Strike_Super = atof(Text);
		hTemp = GetDlgItem(hDlg, IDC_EDIT14);
		GetWindowTextA(hTemp, Text, 10);
		Data[index].Ki_BlastSuper = atof(Text);
		hTemp = GetDlgItem(hDlg, IDC_EDIT15);
		GetWindowTextA(hTemp, Text, 10);
		Data[index].Basic_Def = atof(Text);
		hTemp = GetDlgItem(hDlg, IDC_EDIT16);
		GetWindowTextA(hTemp, Text, 10);
		Data[index].Ki_Blast_Def = atof(Text);
		hTemp = GetDlgItem(hDlg, IDC_EDIT17);
		GetWindowTextA(hTemp, Text, 10);
		Data[index].Strike_Super_Def = atof(Text);
		hTemp = GetDlgItem(hDlg, IDC_EDIT18);
		GetWindowTextA(hTemp, Text, 10);
		Data[index].Ki_BlastSuper_Def = atof(Text);
		hTemp = GetDlgItem(hDlg, IDC_EDIT19);
		GetWindowTextA(hTemp, Text, 10);
		Data[index].Ground_Speed = atof(Text);
		hTemp = GetDlgItem(hDlg, IDC_EDIT20);
		GetWindowTextA(hTemp, Text, 10);
		Data[index].Air_Speed = atof(Text);
		hTemp = GetDlgItem(hDlg, IDC_EDIT21);
		GetWindowTextA(hTemp, Text, 10);
		Data[index].Boost_Speed = atof(Text);
		hTemp = GetDlgItem(hDlg, IDC_EDIT22);
		GetWindowTextA(hTemp, Text, 10);
		Data[index].Dash_Distance = atof(Text);
		hTemp = GetDlgItem(hDlg, IDC_EDIT23);
		GetWindowTextA(hTemp, Text, 10);
		Data[index].Reinforcement_Skill_Duration = atof(Text);
		hTemp = GetDlgItem(hDlg, IDC_EDIT24);
		GetWindowTextA(hTemp, Text, 10);
		Data[index].RevivalHP = atof(Text);
		hTemp = GetDlgItem(hDlg, IDC_EDIT25);
		GetWindowTextA(hTemp, Text, 10);
		Data[index].Reviving_Speed = atof(Text);
		if (IncludeSS == BST_CHECKED)
		{
			hTemp = GetDlgItem(hDlg, IDC_COMBO3);
			SSIndex = SendMessage(hTemp, CB_GETCURSEL, 0, 0);
			Data[index].Super_Soul = SSIndex;
		}
		
		index++;
	}
}

void SetAllCheckStat(HWND hDlg, STAT *Data)
{
	HWND hTemp;
	LRESULT IncludeCAC, IncludeSS;
	char Text[10];
	int SSIndex = 0, CACIndexCheck = 0, count = 0, index = 0, StatCheck[25], maxChar = 0;

	while (HStat[count].CharHexID != 0x64) //find human male offset, to allow easy excemption of all CaC from set all  
	{
		CACIndexCheck += HStat[count].CostumeAmount;
		count++;
	}
	count = 0;
	while (count < CharCount) //calculate amount of char and costume; 
	{
		maxChar += HStat[count].CostumeAmount;
		count++;
	}
	IncludeCAC = SendMessage(GetDlgItem(hDlg, IDC_CHECK1), BM_GETCHECK, 0, 0);
	IncludeSS = SendMessage(GetDlgItem(hDlg, IDC_CHECK2), BM_GETCHECK, 0, 0);

	for (int i = 0; i < 25; i++)
	{
		StatCheck[i] = SendMessage(GetDlgItem(hDlg, IDC_CHECK3 + i), BM_GETCHECK, 0, 0);
	}

	while (index < maxChar)
	{
		if (index >= CACIndexCheck && index <= (CACIndexCheck + 96) && IncludeCAC == BST_UNCHECKED) { index++; continue; }

		if (StatCheck[0] == BST_CHECKED)
		{
			hTemp = GetDlgItem(hDlg, IDC_EDIT1);
			GetWindowTextA(hTemp, Text, 10);
			Data[index].Camera_Position = atoi(Text);
		}
		if (StatCheck[1] == BST_CHECKED)
		{
			hTemp = GetDlgItem(hDlg, IDC_EDIT2);
			GetWindowTextA(hTemp, Text, 10);
			Data[index].Health = atof(Text);
		}
		if (StatCheck[2] == BST_CHECKED)
		{
			hTemp = GetDlgItem(hDlg, IDC_EDIT3);
			GetWindowTextA(hTemp, Text, 10);
			Data[index].Ki = atof(Text);
		}
		if (StatCheck[3] == BST_CHECKED)
		{
			hTemp = GetDlgItem(hDlg, IDC_EDIT4);
			GetWindowTextA(hTemp, Text, 10);
			Data[index].Ki_Recharge = atof(Text);
		}
		if (StatCheck[4] == BST_CHECKED)
		{
			hTemp = GetDlgItem(hDlg, IDC_EDIT5);
			GetWindowTextA(hTemp, Text, 10);
			Data[index].Stamina = atof(Text);
		}
		if (StatCheck[5] == BST_CHECKED)
		{
			hTemp = GetDlgItem(hDlg, IDC_EDIT6);
			GetWindowTextA(hTemp, Text, 10);
			Data[index].Stamina_RechargeM = atof(Text);
		}
		if (StatCheck[6] == BST_CHECKED)
		{
			hTemp = GetDlgItem(hDlg, IDC_EDIT7);
			GetWindowTextA(hTemp, Text, 10);
			Data[index].Stamina_RechargeA = atof(Text);
		}
		if (StatCheck[7] == BST_CHECKED)
		{
			hTemp = GetDlgItem(hDlg, IDC_EDIT8);
			GetWindowTextA(hTemp, Text, 10);
			Data[index].Stamina_RechargeG = atof(Text);
		}
		if (StatCheck[8] == BST_CHECKED)
		{
			hTemp = GetDlgItem(hDlg, IDC_EDIT9);
			GetWindowTextA(hTemp, Text, 10);
			Data[index].Stamina_Drain1 = atof(Text);
		}
		if (StatCheck[9] == BST_CHECKED)
		{
			hTemp = GetDlgItem(hDlg, IDC_EDIT10);
			GetWindowTextA(hTemp, Text, 10);
			Data[index].Stamina_Drain2 = atof(Text);
		}
		if (StatCheck[10] == BST_CHECKED)
		{
			hTemp = GetDlgItem(hDlg, IDC_EDIT11);
			GetWindowTextA(hTemp, Text, 10);
			Data[index].Basic_Attack = atof(Text);
		}
		if (StatCheck[11] == BST_CHECKED)
		{
			hTemp = GetDlgItem(hDlg, IDC_EDIT12);
			GetWindowTextA(hTemp, Text, 10);
			Data[index].Ki_Blast = atof(Text);
		}
		if (StatCheck[12] == BST_CHECKED)
		{
			hTemp = GetDlgItem(hDlg, IDC_EDIT13);
			GetWindowTextA(hTemp, Text, 10);
			Data[index].Strike_Super = atof(Text);
		}
		if (StatCheck[13] == BST_CHECKED)
		{
			hTemp = GetDlgItem(hDlg, IDC_EDIT14);
			GetWindowTextA(hTemp, Text, 10);
			Data[index].Ki_BlastSuper = atof(Text);
		}
		if (StatCheck[14] == BST_CHECKED)
		{
			hTemp = GetDlgItem(hDlg, IDC_EDIT15);
			GetWindowTextA(hTemp, Text, 10);
			Data[index].Basic_Def = atof(Text);
		}
		if (StatCheck[15] == BST_CHECKED)
		{
			hTemp = GetDlgItem(hDlg, IDC_EDIT16);
			GetWindowTextA(hTemp, Text, 10);
			Data[index].Ki_Blast_Def = atof(Text);
		}
		if (StatCheck[16] == BST_CHECKED)
		{
			hTemp = GetDlgItem(hDlg, IDC_EDIT17);
			GetWindowTextA(hTemp, Text, 10);
			Data[index].Strike_Super_Def = atof(Text);
		}
		if (StatCheck[17] == BST_CHECKED)
		{
			hTemp = GetDlgItem(hDlg, IDC_EDIT18);
			GetWindowTextA(hTemp, Text, 10);
			Data[index].Ki_BlastSuper_Def = atof(Text);
		}
		if (StatCheck[18] == BST_CHECKED)
		{
			hTemp = GetDlgItem(hDlg, IDC_EDIT19);
			GetWindowTextA(hTemp, Text, 10);
			Data[index].Ground_Speed = atof(Text);
		}
		if (StatCheck[19] == BST_CHECKED)
		{
			hTemp = GetDlgItem(hDlg, IDC_EDIT20);
			GetWindowTextA(hTemp, Text, 10);
			Data[index].Air_Speed = atof(Text);
		}
		if (StatCheck[20] == BST_CHECKED)
		{
			hTemp = GetDlgItem(hDlg, IDC_EDIT21);
			GetWindowTextA(hTemp, Text, 10);
			Data[index].Boost_Speed = atof(Text);
		}
		if (StatCheck[21] == BST_CHECKED)
		{
			hTemp = GetDlgItem(hDlg, IDC_EDIT22);
			GetWindowTextA(hTemp, Text, 10);
			Data[index].Dash_Distance = atof(Text);
		}
		if (StatCheck[22] == BST_CHECKED)
		{
			hTemp = GetDlgItem(hDlg, IDC_EDIT23);
			GetWindowTextA(hTemp, Text, 10);
			Data[index].Reinforcement_Skill_Duration = atof(Text);
		}
		if (StatCheck[23] == BST_CHECKED)
		{
			hTemp = GetDlgItem(hDlg, IDC_EDIT24);
			GetWindowTextA(hTemp, Text, 10);
			Data[index].RevivalHP = atof(Text);
		}
		if (StatCheck[24] == BST_CHECKED)
		{
			hTemp = GetDlgItem(hDlg, IDC_EDIT25);
			GetWindowTextA(hTemp, Text, 10);
			Data[index].Reviving_Speed = atof(Text);
		}
		if (IncludeSS == BST_CHECKED)
		{
			hTemp = GetDlgItem(hDlg, IDC_COMBO3);
			SSIndex = SendMessage(hTemp, CB_GETCURSEL, 0, 0);
			Data[index].Super_Soul = SSIndex;
		}

		index++;
	}
}


void SetPSCData(STAT *Data)
{
	int index = 0, Offset = 0;

	while (index < PSCCosCount)
	{
		Offset = Data[index].Offset;
		PSCData[Offset + 8] = Data[index].Camera_Position;
		PSCData.erase(Offset + 20, 4);
		PSCData.insert(Offset + 20, FloattoHex(Data[index].Health));
		PSCData.erase(Offset + 28, 4);
		PSCData.insert(Offset + 28, FloattoHex(Data[index].Ki));
		PSCData.erase(Offset + 32, 4);
		PSCData.insert(Offset + 32, FloattoHex(Data[index].Ki_Recharge));
		PSCData.erase(Offset + 48, 4);
		PSCData.insert(Offset + 48, FloattoHex(Data[index].Stamina));
		PSCData.erase(Offset + 52, 4);
		PSCData.insert(Offset + 52, FloattoHex(Data[index].Stamina_RechargeM));
		PSCData.erase(Offset + 56, 4);
		PSCData.insert(Offset + 56, FloattoHex(Data[index].Stamina_RechargeA));
		PSCData.erase(Offset + 60, 4);
		PSCData.insert(Offset + 60, FloattoHex(Data[index].Stamina_RechargeG));
		PSCData.erase(Offset + 64, 4);
		PSCData.insert(Offset + 64, FloattoHex(Data[index].Stamina_Drain1));
		PSCData.erase(Offset + 68, 4);
		PSCData.insert(Offset + 68, FloattoHex(Data[index].Stamina_Drain2));
		PSCData.erase(Offset + 76, 4);
		PSCData.insert(Offset + 76, FloattoHex(Data[index].Basic_Attack));
		PSCData.erase(Offset + 80, 4);
		PSCData.insert(Offset + 80, FloattoHex(Data[index].Ki_Blast));
		PSCData.erase(Offset + 84, 4);
		PSCData.insert(Offset + 84, FloattoHex(Data[index].Strike_Super));
		PSCData.erase(Offset + 88, 4);
		PSCData.insert(Offset + 88, FloattoHex(Data[index].Ki_BlastSuper));
		PSCData.erase(Offset + 92, 4);
		PSCData.insert(Offset + 92, FloattoHex(Data[index].Basic_Def));
		PSCData.erase(Offset + 96, 4);
		PSCData.insert(Offset + 96, FloattoHex(Data[index].Ki_Blast_Def));
		PSCData.erase(Offset + 100, 4);
		PSCData.insert(Offset + 100, FloattoHex(Data[index].Strike_Super_Def));
		PSCData.erase(Offset + 104, 4);
		PSCData.insert(Offset + 104, FloattoHex(Data[index].Ki_BlastSuper_Def));
		PSCData.erase(Offset + 108, 4);
		PSCData.insert(Offset + 108, FloattoHex(Data[index].Ground_Speed));
		PSCData.erase(Offset + 112, 4);
		PSCData.insert(Offset + 112, FloattoHex(Data[index].Air_Speed));
		PSCData.erase(Offset + 116, 4);
		PSCData.insert(Offset + 116, FloattoHex(Data[index].Boost_Speed));
		PSCData.erase(Offset + 120, 4);
		PSCData.insert(Offset + 120, FloattoHex(Data[index].Dash_Distance));
		PSCData.erase(Offset + 128, 4);
		PSCData.insert(Offset + 128, FloattoHex(Data[index].Reinforcement_Skill_Duration));
		PSCData.erase(Offset + 136, 4);
		PSCData.insert(Offset + 136, FloattoHex(Data[index].RevivalHP));
		PSCData.erase(Offset + 144, 4);
		PSCData.insert(Offset + 144, FloattoHex(Data[index].Reviving_Speed));
		PSCData[Offset + 180] = Data[index].Super_Soul;
		index++;
	}
}
