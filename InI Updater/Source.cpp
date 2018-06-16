#include <windows.h>
#include "resource.h"
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <windows.h>
#include <shobjidl.h>
#include "resource.h"
#include "../DBVX 2 Tools/Files.h"
#include "../DBVX 2 Tools/Winapi.h"

struct SKILL
{
	std::string RefID;
	int HexID1;
	int HexID2;
	std::string RefCode;
	std::string Name;
};
struct MSGDATA
{
	int ID;
	std::string NameID;
	std::string Info;
	int startLength;
	int endLength;
	int stringStartID1;
	int stringStartID2;
};
struct AURA
{
	int HexID;
	std::string skillName;
};

HWND hwnd;
char IniFileName[20][MAX_PATH], FileName[20][MAX_PATH], FolderPath[MAX_PATH];
std::string Data[20], IniData[20];

void LoadMSG(std::string MSGData, MSGDATA *MSGInfo, int *MSGAmount);
int LoadSkill(char File[MAX_PATH], std::string &Setting, SKILL *Skill);
int LoadAura(char File[MAX_PATH], std::string &AuraSetting, AURA *AuraID);
BOOL CALLBACK DialogProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	

	hwnd = CreateDialog(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DialogProc);

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd); 

    MSG Msg;

	while (GetMessage(&Msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
	return Msg.wParam;
}

void UpdateIni()
{
	int SuperStart = (uint8_t)Data[0][0x28] + ((uint8_t)Data[0][0x29] * 0x100), 
		UltStart = (uint8_t)Data[0][0x2c] + ((uint8_t)Data[0][0x2d] * 0x100),
		EscStart = (uint8_t)Data[0][0x30] + ((uint8_t)Data[0][0x31] * 0x100), 
		AwkStart = (uint8_t)Data[0][0x3c] + ((uint8_t)Data[0][0x3d] * 0x100),
		c, check1, check2, found = 0, SMSGAmount, UMSGAmount, EMSGAmount, AMSGAmount;
	SKILL SSkillID[1000], USkillID[1000], ESkillID[1000], ASkillID[1000];
	MSGDATA SMSG[1000], UMSG[1000], EMSG[1000], AMSG[1000];
	AURA AuraID[500];
	
	int SSkillCount = LoadSkill("Data/Super Skill ID.ini", IniData[0], SSkillID);
	int USkillCount = LoadSkill("Data/Ultimate Skill ID.ini", IniData[1], USkillID);
	int ESkillCount = LoadSkill("Data/Evasive Skill ID.ini", IniData[2], ESkillID);
	int ASkillCount = LoadSkill("Data/Awoken Skill ID.ini", IniData[3], ASkillID);
	int AuraCount = LoadAura("Data/Aura ID.ini", IniData[4], AuraID);

	LoadMSG(Data[1], SMSG, &SMSGAmount);
	LoadMSG(Data[2], UMSG, &UMSGAmount);
	LoadMSG(Data[3], EMSG, &EMSGAmount);
	LoadMSG(Data[4], AMSG, &AMSGAmount);

	c = SuperStart;
	for (int i = 0; i < (uint8_t)Data[0][0x10] + ((uint8_t)Data[0][0x11] * 0x100); i++)
	{
		check1 = (uint8_t)Data[0][c + 0x08], check2 = (uint8_t)Data[0][c + 0x09];
		for (int j = 0; j < SSkillCount; j++)
		{
			if (check1 == SSkillID[j].HexID1 && check2 == SSkillID[j].HexID2)
				found = 1;
		}

		if (found == 1)
			found = 0;
		else
		{
			std::string ins;
			int num = check1 + (check2 * 0x100);
			char sname[4], temp[20];
			sname[0] = Data[0][c], sname[1] = Data[0][c + 1], sname[2] = Data[0][c + 2], sname[3] = '\0';
			sprintf(temp, "%.4d", num);
			ins.append(temp), ins.append(" - ");
			sprintf(temp, "%.2x", check1);
			ins.append(temp);
			sprintf(temp, "%.2x", check2);
			ins.append(temp), ins.append(" - ");
			ins.append(sname), ins.append(" - ");


			for (int k = 0; k < SMSGAmount; k++)
			{
				char checkIDC[5];
				int len = strlen(SMSG[k].NameID.c_str());
				checkIDC[0] = SMSG[k].NameID.c_str()[len - 4], checkIDC[1] = SMSG[k].NameID.c_str()[len - 3],
					checkIDC[2] = SMSG[k].NameID.c_str()[len - 2], checkIDC[3] = SMSG[k].NameID.c_str()[len - 1];
				int checkID = atoi(checkIDC);
				if (num == checkID)
				{
					ins.append(SMSG[k].Info);
				}
			}
			ins.append(";");
			IniData[0].append("\r\n");
			IniData[0].append(ins);
		}

		c += 68;
	}

	saveFile("Data/Super Skill ID.ini", IniData[0]);

	c = UltStart;
	for (int i = 0; i < (uint8_t)Data[0][0x14] + ((uint8_t)Data[0][0x15] * 0x100); i++)
	{
		check1 = (uint8_t)Data[0][c + 0x08], check2 = (uint8_t)Data[0][c + 0x09];
		for (int j = 0; j < USkillCount; j++)
		{
			if (check1 == USkillID[j].HexID1 && check2 == USkillID[j].HexID2)
				found = 1;
		}

		if (found == 1)
			found = 0;
		else
		{
			std::string ins;
			int num = check1 + (check2 * 0x100);
			char sname[4], temp[20];
			sname[0] = Data[0][c], sname[1] = Data[0][c + 1], sname[2] = Data[0][c + 2], sname[3] = '\0';
			sprintf(temp, "%.4d", num);
			ins.append(temp), ins.append(" - ");
			sprintf(temp, "%.2x", check1);
			ins.append(temp);
			sprintf(temp, "%.2x", check2);
			ins.append(temp), ins.append(" - ");
			ins.append(sname), ins.append(" - ");


			for (int k = 0; k < UMSGAmount; k++)
			{
				char checkIDC[5];
				int len = strlen(UMSG[k].NameID.c_str());
				checkIDC[0] = UMSG[k].NameID.c_str()[len - 4], checkIDC[1] = UMSG[k].NameID.c_str()[len - 3],
					checkIDC[2] = UMSG[k].NameID.c_str()[len - 2], checkIDC[3] = UMSG[k].NameID.c_str()[len - 1];
				int checkID = atoi(checkIDC);
				if ((num - 5000) == checkID)
				{
					ins.append(UMSG[k].Info);
				}
			}
			ins.append(";");
			IniData[1].append("\r\n");
			IniData[1].append(ins);
		}

		c += 68;
	}

	saveFile("Data/Ultimate Skill ID.ini", IniData[1]);

	c = EscStart;
	for (int i = 0; i < (uint8_t)Data[0][0x18] + ((uint8_t)Data[0][0x19] * 0x100); i++)
	{
		check1 = (uint8_t)Data[0][c + 0x08], check2 = (uint8_t)Data[0][c + 0x09];
		for (int j = 0; j < ESkillCount; j++)
		{
			if (check1 == ESkillID[j].HexID1 && check2 == ESkillID[j].HexID2)
				found = 1;
		}

		if (found == 1)
			found = 0;
		else
		{
			std::string ins;
			int num = check1 + (check2 * 0x100);
			char sname[4], temp[20];
			sname[0] = Data[0][c], sname[1] = Data[0][c + 1], sname[2] = Data[0][c + 2], sname[3] = '\0';
			sprintf(temp, "%.4d", num);
			ins.append(temp), ins.append(" - ");
			sprintf(temp, "%.2x", check1);
			ins.append(temp);
			sprintf(temp, "%.2x", check2);
			ins.append(temp), ins.append(" - ");
			ins.append(sname), ins.append(" - ");


			for (int k = 0; k < EMSGAmount; k++)
			{
				char checkIDC[5];
				int len = strlen(EMSG[k].NameID.c_str());
				checkIDC[0] = EMSG[k].NameID.c_str()[len - 4], checkIDC[1] = EMSG[k].NameID.c_str()[len - 3],
					checkIDC[2] = EMSG[k].NameID.c_str()[len - 2], checkIDC[3] = EMSG[k].NameID.c_str()[len - 1];
				int checkID = atoi(checkIDC);
				if (num == checkID)
				{
					ins.append(EMSG[k].Info);
				}
			}
			ins.append(";");
			IniData[2].append("\r\n");
			IniData[2].append(ins);
		}

		c += 68;
	}

	saveFile("Data/Evasive Skill ID.ini", IniData[2]);

	c = AwkStart;
	for (int i = 0; i < (uint8_t)Data[0][0x24] + ((uint8_t)Data[0][0x25] * 0x100); i++)
	{
		check1 = (uint8_t)Data[0][c + 0x08], check2 = (uint8_t)Data[0][c + 0x09];
		for (int j = 0; j < ASkillCount; j++)
		{
			if (check1 == ASkillID[j].HexID1 && check2 == ASkillID[j].HexID2)
				found = 1;
		}

		if (found == 1)
			found = 0;
		else
		{
			std::string ins;
			int num = check1 + (check2 * 0x100);
			char sname[4], temp[20];
			sname[0] = Data[0][c], sname[1] = Data[0][c + 1], sname[2] = Data[0][c + 2], sname[3] = '\0';
			sprintf(temp, "%.4d", num);
			ins.append(temp), ins.append(" - ");
			sprintf(temp, "%.2x", check1);
			ins.append(temp);
			sprintf(temp, "%.2x", check2);
			ins.append(temp), ins.append(" - ");
			ins.append(sname), ins.append(" - ");
			ins.append(AMSG[i].Info);
			//ins.append(";");
			IniData[3].append("\r\n");
			IniData[3].append(ins);
		}


		c += 68;
	}

	saveFile("Data/Awoken Skill ID.ini", IniData[3]);

	for(int i = Data[5][0x0c]; i < Data[5][0x08] * 0x10; i = i + 0x10)
	{
		check1 = (uint8_t)Data[5][i];
		for (int j = 0; j < AuraCount;j++)
		{
			if (check1 == AuraID[j].HexID)
			{
				found = 1;
			}
		}

		if (found == 1)
			found = 0;
		else
		{
			std::string ins;
			int num = check1;
			char temp[20];
			sprintf(temp, "%.2x", num);
			ins.append(temp), ins.append(" - ");
			ins.append("New Aura");
			ins.append(";");
			IniData[4].append("\r\n");
			IniData[4].append(ins);
		}
	}
	saveFile("Data/Aura ID.ini", IniData[4]);
}

void LoadMSG(std::string MSGData, MSGDATA *MSGInfo, int *MSGAmount)
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
		IDCount += 4;
		count++;
	}
	*MSGAmount = count;
}


int LoadSkill(char File[MAX_PATH], std::string &SkillSetting, SKILL *SkillID)
{
	SkillSetting.clear();
	int check = openFile(File, SkillSetting);
	SetWindowTextA(GetDlgItem(hwnd, IDC_EDITERR1), "Failed to open ini");
	std::istringstream TempStream(SkillSetting);
	std::string TempString;
	int SkillCount = 1;

	while (std::getline(TempStream, TempString))
	{
		char CTempRefID[100] = { NULL }, CTempRefCode[10] = { NULL }, CTempName[50] = { NULL };
		char CHexID1[2] = { NULL }, CHexID2[2] = { NULL };
		std::stringstream HexID1, HexID2;
		int count = 0, countHex = 0, posSet = 0, max = TempString.size(), CTempHexID1, CTempHexID2;
		while (count <= max)
		{
			if (TempString[count] != ' ')
			{
				CTempRefID[count] = TempString[count];
				count++;
			}
			else
			{
				count += 3;
				posSet += count;
				break;
			}
		}
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
			if (TempString[count] != ' ')
			{
				CTempRefCode[count - posSet] = TempString[count];

				count++;
			}
			else
			{
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
		SkillID[SkillCount - 1].RefID = CTempRefID;
		SkillID[SkillCount - 1].HexID1 = CTempHexID1;
		SkillID[SkillCount - 1].HexID2 = CTempHexID2;
		SkillID[SkillCount - 1].RefCode = CTempRefCode;
		SkillID[SkillCount - 1].Name = CTempName;
#ifdef _DEBUG
		std::cout << SkillID[SkillCount].RefID << " - " << std::hex << SkillID[SkillCount].HexID1 << std::hex << SkillID[SkillCount].HexID2 <<
			" - " << SkillID[SkillCount].RefCode << " - " << SkillID[SkillCount].Name << std::endl;
#endif
		SkillCount++;
		//memset(CTempName, 0, strlen(CTempName));
	}
	return SkillCount;
}

int LoadAura(char File[MAX_PATH], std::string &AuraSetting, AURA *AuraID)
{
	AuraSetting.clear();
	openFile("Data/Aura ID.ini", AuraSetting);
	std::istringstream TempStream(AuraSetting);
	std::string TempString;
	int CTempHexID, AuraCount = 0;
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
		AuraID[AuraCount].HexID = CTempHexID;
		AuraID[AuraCount].skillName = CTempValue;
#ifdef _DEBUG
		std::cout << AuraID[AuraCount].HexID << " - " << AuraID[AuraCount].skillName << std::endl;
#endif
		memset(CTempValue, 0, strlen(CTempValue));
		AuraCount++;
	}
	return AuraCount;
}

BOOL CALLBACK DialogProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg) {
	case WM_INITDIALOG:
	{

		break;
	}
	case WM_COMMAND:
		switch (wParam)
		{
		case IDC_BUTTON1:
		{
			memset(FolderPath, 0, MAX_PATH);
			getFolderPath(hDlg, FolderPath);
			SetWindowTextA(GetDlgItem(hDlg, IDC_EDIT1), FolderPath);
		}
		break;
		case IDC_BUTTON2:
		{
			char Name[10][100] = { "system\\custom_skill.cus", "msg\\proper_noun_skill_spa_name_en.msg", 
				"msg\\proper_noun_skill_ult_name_en.msg", "msg\\proper_noun_skill_esc_name_en.msg", 
				"msg\\proper_noun_skill_met_name_en.msg", "system\\aura_setting.aur"};
			memset(FileName, 0, sizeof(FileName[0][0]) * 20 * MAX_PATH);
			for (int i = 0; i < 6; i++)
			{
				Data[i].clear();
				GetWindowTextA(GetDlgItem(hDlg, IDC_EDIT1), FileName[i], MAX_PATH);
				strcat_s(FileName[i], "\\");
				strcat_s(FileName[i], Name[i]);
				openFile(FileName[i], Data[i]);
				//saveFile(FileName[i], Data[i]);
			}

			UpdateIni();

			SetWindowTextA(GetDlgItem(hDlg, IDC_EDITERR1), "Finish Updating ini's");
		}
		}
		break;

	case WM_CLOSE:
		DestroyWindow(hDlg);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return FALSE;
}