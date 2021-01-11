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
#include <filesystem>
#include "resource.h"
#include "../DBVX 2 Tools/Files.h"
#include "../DBVX 2 Tools/Winapi.h"
#include "../DBVX 2 Tools/Aura.h"
#include "../DBVX 2 Tools/Skill.h"
#include "../DBVX 2 Tools/MSGCS.h"
#include <vcclr.h> 

HWND hwnd;
char IniFileName[20][MAX_PATH], FileName[20][MAX_PATH], FolderPath[MAX_PATH];
std::string CusData, AurData, CmsData;
int SMSGAmount, UMSGAmount, EMSGAmount, AMSGAmount, CNMSGAmount, CCMSGAmount, SSMSGAmount;
ref class MSGList
{
public:
	static XV2Lib::MSG ^SuperMSG, ^UltimateMSG, ^EvasiveMSG, ^AwakenMSG, ^CharacterNameMSG, ^CharacterCostumeMSG, ^SuperSoulMSG;
};


BOOL CALLBACK DialogProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
void LoadAura(AURA* AuraID, int& AuraCount, std::string& AuraSetting);

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
	std::string IniData;
	int SuperStart = (uint8_t)CusData[0x28] + ((uint8_t)CusData[0x29] * 0x100) + ((uint8_t)CusData[0x2a] * 0x10000),
		UltStart = (uint8_t)CusData[0x2c] + ((uint8_t)CusData[0x2d] * 0x100) + ((uint8_t)CusData[0x2e] * 0x10000),
		EscStart = (uint8_t)CusData[0x30] + ((uint8_t)CusData[0x31] * 0x100) + ((uint8_t)CusData[0x32] * 0x10000),
		AwkStart = (uint8_t)CusData[0x3c] + ((uint8_t)CusData[0x3d] * 0x100) + ((uint8_t)CusData[0x3e] * 0x10000);

	for (int i = SuperStart; i < UltStart; i += 0x44)
	{
		std::string ins, tempString;
		char sname[4], temp[20];
		int ID1 = (uint8_t)CusData[i + 0x08], ID2 = (uint8_t)CusData[i + 0x09], num = ID1 + (ID2 * 0x100);
		
		sname[0] = CusData[i], sname[1] = CusData[i + 1], sname[2] = CusData[i + 2], sname[3] = '\0';
		sprintf(temp, "%.4d", num);
		ins.append(temp), ins.append(" - ");
		sprintf(temp, "%.2x", ID1);
		ins.append(temp);
		sprintf(temp, "%.2x", ID2);
		ins.append(temp), ins.append(" - ");
		ins.append(sname), ins.append(" - ");
		tempString = MarshalString(MSGList::SuperMSG->FindByPart((num).ToString()));
		ins.append(tempString);
		ins.append(";");

		IniData.append(ins);
		IniData.append("\r\n");
	}
	saveFile("Data/Super Skill ID.ini", IniData);

	IniData.clear();
	for (int i = UltStart; i < EscStart; i += 0x44)
	{
		std::string ins, tempString;
		String^ prefix = "ult_";
		char sname[4], temp[20];
		int ID1 = (uint8_t)CusData[i + 0x08], ID2 = (uint8_t)CusData[i + 0x09], num = ID1 + (ID2 * 0x100);

		sname[0] = CusData[i], sname[1] = CusData[i + 1], sname[2] = CusData[i + 2], sname[3] = '\0';
		sprintf(temp, "%.4d", num);
		ins.append(temp), ins.append(" - ");
		sprintf(temp, "%.2x", ID1);
		ins.append(temp);
		sprintf(temp, "%.2x", ID2);
		ins.append(temp), ins.append(" - ");
		ins.append(sname), ins.append(" - ");
		if ((num - 5000) < 10)
			prefix += "000";
		else
			if ((num - 5000) >= 10 && (num - 5000 < 100))
				prefix += "00";
			else
				if ((num - 5000) >= 100 && (num - 5000 < 1000))
					prefix += "0";
		tempString = MarshalString(MSGList::UltimateMSG->Find(prefix+(num - 5000).ToString()));
		ins.append(tempString);
		ins.append(";");

		IniData.append(ins);
		IniData.append("\r\n");
	}
	saveFile("Data/Ultimate Skill ID.ini", IniData);

	IniData.clear();
	for (int i = EscStart; i < AwkStart; i += 0x44)
	{
		std::string ins, tempString;
		char sname[4], temp[20];
		int ID1 = (uint8_t)CusData[i + 0x08], ID2 = (uint8_t)CusData[i + 0x09], num = ID1 + (ID2 * 0x100);

		sname[0] = CusData[i], sname[1] = CusData[i + 1], sname[2] = CusData[i + 2], sname[3] = '\0';
		sprintf(temp, "%.4d", num);
		ins.append(temp), ins.append(" - ");
		sprintf(temp, "%.2x", ID1);
		ins.append(temp);
		sprintf(temp, "%.2x", ID2);
		ins.append(temp), ins.append(" - ");
		ins.append(sname), ins.append(" - ");
		tempString = MarshalString(MSGList::EvasiveMSG->FindByPart((num - 10000).ToString()));
		ins.append(tempString);
		ins.append(";");

		IniData.append(ins);
		IniData.append("\r\n");
	}
	saveFile("Data/Evasive Skill ID.ini", IniData);

	IniData.clear();
	int end = CusData.find("CAR_");
	for (int i = AwkStart; i < end; i += 0x44)
	{
		std::string ins, tempString;
		char sname[4], temp[20];
		int ID1 = (uint8_t)CusData[i + 0x08], ID2 = (uint8_t)CusData[i + 0x09], num = ID1 + (ID2 * 0x100);

		sname[0] = CusData[i], sname[1] = CusData[i + 1], sname[2] = CusData[i + 2], sname[3] = '\0';
		sprintf(temp, "%.4d", num);
		ins.append(temp), ins.append(" - ");
		sprintf(temp, "%.2x", ID1);
		ins.append(temp);
		sprintf(temp, "%.2x", ID2);
		ins.append(temp), ins.append(" - ");
		ins.append(sname), ins.append(" - ");
		tempString = MarshalString(MSGList::AwakenMSG->FindByPart((num - 25000).ToString()));
		ins.append(tempString);
		ins.append(";");

		IniData.append(ins);
		IniData.append("\r\n");
	}
	saveFile("Data/Awoken Skill ID.ini", IniData);

	IniData.clear();
	int found = 0, check1, AuraCount = 0;
	AURA AuraID[500];
	LoadAura(AuraID, AuraCount, IniData);
	for (int i = AurData[0x0c]; i < AurData[0x08] * 0x10; i = i + 0x10)
	{
		check1 = (uint8_t)AurData[i];
		for (int j = 0; j < AuraCount; j++)
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

			IniData.append(ins);
			IniData.append("\r\n");
		}
	}
	saveFile("Data/Aura ID.ini", IniData);

	IniData.clear();
	for (int i = 0; i < SSMSGAmount; i++)
	{
		std::string ins, tempString;
		char temp[5];

		sprintf(temp, "%.2x", i);
		ins.append(temp), ins.append(" - ");
		tempString = MarshalString(MSGList::SuperSoulMSG->Find(i));
		ins.append(tempString);
		ins.append(";");
		if (tempString.compare("") == 0) continue;

		IniData.append(ins);
		IniData.append("\r\n");
	}
	saveFile("Data/Super Soul ID.ini", IniData);

	IniData.clear();
	std::string CostumeIniData;
	int cEnd = ((uint8_t)CmsData[0x08] + ((uint8_t)CmsData[0x09] *  0x100)) * 0x54;
	for (size_t i = (uint8_t)CmsData[0x0c]; i < cEnd; i += 0x54)
	{
		std::string ins, costumeIns, tempString, costumeTempString;
		char sname[4], temp[4];
		int ID = (uint8_t)CmsData[i];

		sprintf(temp, "%.2x", ID);
		ins.append(temp), ins.append(" - ");
		sname[0] = CmsData[i + 4], sname[1] = CmsData[i + 5], sname[2] = CmsData[i + 6], sname[3] = '\0';
		if (ID >= 0x64 && ID <= 0x6b)
		{
			switch (ID)
			{
			case 0x64:
				tempString = "Human Male";
				costumeTempString = "64 - 00 - Human Male;\r\n64 - 00 - Human Male 0: Small & Slim;\r\n64 - 01 - Human Male 1: Small & Normal;\r\n64 - 02 - Human Male 2: Small & Fat;\r\n",
					costumeTempString += "64 - 03 - Human Male 3: Medium & Slim;\r\n64 - 04 - Human Male 4: Medium & Normal;\r\n64 - 05 - Human Male 5: Medium & Fat;\r\n64 - 06 - Human Male 6: Tall & Slim;\r\n",
					costumeTempString += "64 - 07 - Human Male 7: Tall & Normal;\r\n64 - 08 - Human Male 8: Tall & Fat;\r\n64 - 09 - Human Male 9: Taller & Slim;\r\n64 - 0a - Human Male 10: Taller & Normal;\r\n",
					costumeTempString += "64 - 0b - Human Male 11: Taller & Fat; \r\n";
				break;
			case 0x65:
				tempString = "Human Female";
				costumeTempString = "65 - 00 - Human Female;\r\n65 - 00 - Human Female 0: Small & Slim;\r\n65 - 01 - Human Female 1: Small & Normal;\r\n65 - 02 - Human Female 2: Small & Fat;\r\n",
					costumeTempString += "65 - 03 - Human Female 3: Medium & Slim;\r\n65 - 04 - Human Female 4: Medium & Normal;\r\n65 - 05 - Human Female 5: Medium & Fat;\r\n",
					costumeTempString += "65 - 06 - Human Female 6: Tall & Slim;\r\n65 - 07 - Human Female 7: Tall & Normal;\r\n65 - 08 - Human Female 8: Tall & Fat; \r\n",
					costumeTempString += "65 - 09 - Human Female 9: Taller & Slim;\r\n65 - 0a - Human Female 10: Taller & Normal; \r\n65 - 0b - Human Female 11: Taller & Fat;\r\n";
				break;
			case 0x66:
				tempString = "Saiyan Male";
				costumeTempString = "66- 00 - Saiyan Male;\r\n66- 00 - Saiyan Male 0: Small & Slim;\r\n66- 01 - Saiyan Male 1: Small & Normal;\r\n66- 02 - Saiyan Male 2: Small & Fat;\r\n",
					costumeTempString += "66- 03 - Saiyan Male 3: Medium & Slim;\r\n66- 04 - Saiyan Male 4: Medium & Normal;\r\n66- 05 - Saiyan Male 5: Medium & Fat;\r\n",
					costumeTempString += "66- 06 - Saiyan Male 6: Tall & Slim;\r\n66- 07 - Saiyan Male 7: Tall & Normal;\r\n66- 08 - Saiyan Male 8: Tall & Fat; \r\n",
					costumeTempString += "66- 09 - Saiyan Male 9: Taller & Slim;\r\n66- 0a - Saiyan Male 10: Taller & Normal; \r\n66- 0b - Saiyan Male 11: Taller & Fat;\r\n";
				break;
			case 0x67: 
				tempString = "Saiyan Female";
				costumeTempString = "67 - 00 - Saiyan Female;\r\n67 - 00 - Saiyan Female 0: Small & Slim;\r\n67 - 01 - Saiyan Female 1: Small & Normal;\r\n67 - 02 - Saiyan Female 2: Small & Fat;\r\n",
					costumeTempString += "67 - 03 - Saiyan Female 3: Medium & Slim;\r\n67 - 04 - Saiyan Female 4: Medium & Normal;\r\n67 - 05 - Saiyan Female 5: Medium & Fat;\r\n",
					costumeTempString += "67 - 06 - Saiyan Female 6: Tall & Slim;\r\n67 - 07 - Saiyan Female 7: Tall & Normal;\r\n67 - 08 - Saiyan Female 8: Tall & Fat; \r\n",
					costumeTempString += "67 - 09 - Saiyan Female 9: Taller & Slim;\r\n67 - 0a - Saiyan Female 10: Taller & Normal; \r\n67 - 0b - Saiyan Female 11: Taller & Fat;\r\n";
				break;
			case 0x68:
				tempString = "Namekian";
				costumeTempString = "68- 00 - Namekian;\r\n68- 00 - Namekian 0: Small & Slim;\r\n68- 01 - Namekian 1: Small & Normal;\r\n68- 02 - Namekian 2: Small & Fat;\r\n",
					costumeTempString += "68- 03 - Namekian 3: Medium & Slim;\r\n68- 04 - Namekian 4: Medium & Normal;\r\n68- 05 - Namekian 5: Medium & Fat;\r\n",
					costumeTempString += "68- 06 - Namekian 6: Tall & Slim;\r\n68- 07 - Namekian 7: Tall & Normal;\r\n68- 08 - Namekian 8: Tall & Fat; \r\n",
					costumeTempString += "68- 09 - Namekian 9: Taller & Slim;\r\n68- 0a - Namekian 10: Taller & Normal; \r\n68- 0b - Namekian 11: Taller & Fat;\r\n";
				break;
			case 0x69:
				tempString = "Frieza Race";
				costumeTempString = "69- 00 - Frieza Race;\r\n69- 00 - Frieza Race 0: Small & Slim;\r\n69- 01 - Frieza Race 1: Small & Normal;\r\n69- 02 - Frieza Race 2: Small & Fat;\r\n",
					costumeTempString += "69- 03 - Frieza Race 3: Medium & Slim;\r\n69- 04 - Frieza Race 4: Medium & Normal;\r\n69- 05 - Frieza Race 5: Medium & Fat;\r\n",
					costumeTempString += "69- 06 - Frieza Race 6: Tall & Slim;\r\n69- 07 - Frieza Race 7: Tall & Normal;\r\n69- 08 - Frieza Race 8: Tall & Fat; \r\n",
					costumeTempString += "69- 09 - Frieza Race 9: Taller & Slim;\r\n69- 0a - Frieza Race 10: Taller & Normal;\r\n69- 0b - Frieza Race 11: Taller & Fat;\r\n";
				break;
			case 0x6a: 
				tempString = "Majin Male";
				costumeTempString = "6a- 00 - Majin Male;\r\n6a- 00 - Majin Male 0: Small & Slim;\r\n6a- 01 - Majin Male 1: Small & Normal;\r\n6a- 02 - Majin Male 2: Small & Fat;\r\n",
					costumeTempString += "6a- 03 - Majin Male 3: Medium & Slim;\r\n6a- 04 - Majin Male 4: Medium & Normal;\r\n6a- 05 - Majin Male 5: Medium & Fat;\r\n",
					costumeTempString += "6a- 06 - Majin Male 6: Tall & Slim;\r\n6a- 07 - Majin Male 7: Tall & Normal;\r\n6a- 08 - Majin Male 8: Tall & Fat; \r\n",
					costumeTempString += "6a- 09 - Majin Male 9: Taller & Slim;\r\n6a- 0a - Majin Male 10: Taller & Normal;\r\n6a- 0b - Majin Male 11: Taller & Fat;\r\n";
				break;
			case 0x6b:
				tempString = "Majin Female";
				costumeTempString = "6b - 00 - Majin Female;\r\n6b - 00 - Majin Female 0: Small & Slim;\r\n6b - 01 - Majin Female 1: Small & Normal;\r\n6b - 02 - Majin Female 2: Small & Fat;\r\n",
					costumeTempString += "6b - 03 - Majin Female 3: Medium & Slim;\r\n6b - 04 - Majin Female 4: Medium & Normal;\r\n6b - 05 - Majin Female 5: Medium & Fat;\r\n",
					costumeTempString += "6b - 06 - Majin Female 6: Tall & Slim;\r\n6b - 07 - Majin Female 7: Tall & Normal;\r\n6b - 08 - Majin Female 8: Tall & Fat; \r\n",
					costumeTempString += "6b - 09 - Majin Female 9: Taller & Slim;\r\n6b - 0a - Majin Female 10: Taller & Normal;\r\n6b - 0b - Majin Female 11: Taller & Fat;\r\n";
				break;
			default:
				break;
			}
		}
		else
		{
			tempString = MarshalString(MSGList::CharacterNameMSG->FindByPart((gcnew String(sname))));
			if (tempString.empty()) tempString = "Unknown";
			List<String^>^ tempList = MSGList::CharacterCostumeMSG->FindAllByPart((gcnew String(sname)));
			if(tempList->Count > 0)
			{
				char tempCID[4];
				for (int i = 0; i < tempList->Count; i += 1)
				{
					costumeTempString.append(temp), costumeTempString.append(" - ");
					sprintf(tempCID, "%.2x", i);
					costumeTempString.append(tempCID), costumeTempString.append(" - ");
					costumeTempString.append(MarshalString(tempList[i]));
					costumeTempString.append(";\r\n");
				}
			}
			else
			{
				costumeIns.append(temp), costumeIns.append(" - ");
				costumeIns.append("00 - Unknown;\r\n");
			}
		}
		ins.append(tempString), ins.append(";");
		costumeIns.append(costumeTempString);

		IniData.append(ins);
		IniData.append("\r\n");
		CostumeIniData.append(costumeIns);
	}
	saveFile("Data/Character ID.ini", IniData);
	saveFile("Data/Costume ID.ini", CostumeIniData);
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
			//getFolderPath(hDlg, FolderPath);
			getFolderPath(FolderPath);
			SetWindowTextA(GetDlgItem(hDlg, IDC_EDIT1), FolderPath);
		}
		break;
		case IDC_BUTTON2:
		{
			char Name[10][100] = { "system/custom_skill.cus", "system/aura_setting.aur", "system/char_model_spec.cms", "msg/proper_noun_skill_spa_name_en.msg", "msg/proper_noun_skill_ult_name_en.msg", 
				"msg/proper_noun_skill_esc_name_en.msg", "msg/proper_noun_skill_met_name_en.msg", "msg/proper_noun_character_name_en.msg", "msg/proper_noun_variation_name_en.msg", "msg/proper_noun_talisman_name_en.msg" };
			memset(FileName, 0, sizeof(FileName[0][0]) * 20 * MAX_PATH);
			for (int i = 0; i < 10; i++)
			{
				GetWindowTextA(GetDlgItem(hDlg, IDC_EDIT1), FileName[i], MAX_PATH);
				strcat_s(FileName[i], "/");
				strcat_s(FileName[i], Name[i]);
			}

			std::string errorMessage;
			bool fileNotFound = false;
			for (int i = 0; i < 10; i++)
			{
				if(	!std::filesystem::exists(FileName[i]))
				{ 
					fileNotFound = true;
					errorMessage.append(std::string(FileName[i]) + " not found\n");
				}
			}

			if (fileNotFound)
			{
				errorMessage.append("Canceling Ini Update, Ensure correct follder is selected and all required msg and system files present");
				MessageBoxA(NULL, errorMessage.c_str(), "Error", MB_ICONERROR);
				break;
			}

			openFile(FileName[0], CusData);
			openFile(FileName[1], AurData);
			openFile(FileName[2], CmsData);
		
			MSGList::SuperMSG = MSG_Read(FileName[3], &SMSGAmount);
			MSGList::UltimateMSG = MSG_Read(FileName[4], &UMSGAmount);
			MSGList::EvasiveMSG = MSG_Read(FileName[5], &EMSGAmount);
			MSGList::AwakenMSG = MSG_Read(FileName[6], &AMSGAmount);
			MSGList::CharacterNameMSG = MSG_Read(FileName[7], &CNMSGAmount);
			MSGList::CharacterCostumeMSG = MSG_Read(FileName[8], &CCMSGAmount);
			MSGList::SuperSoulMSG = MSG_Read(FileName[9], &SSMSGAmount);

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

void LoadAura(AURA* AuraID, int &AuraCount, std::string &AuraSetting)
{
	openFile("Data/Aura ID.ini", AuraSetting);
	std::istringstream TempStream(AuraSetting);
	std::string TempString;
	int CTempHexID;
	char CTempValue[105] = { NULL };

	;
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
}
