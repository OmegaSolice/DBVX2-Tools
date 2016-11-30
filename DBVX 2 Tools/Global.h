#pragma once
#include "Header.h"
extern std::string AuraData, CusData, AuraSetting, CharSetting, CostumeSetting, SSkillSetting, USkillSetting, ASkillSetting, ESkillSetting;
extern std::string NameMSGData, DescMSGData;
extern char AuraFile[MAX_PATH], CusFile[MAX_PATH], NameMsgFile[MAX_PATH], DescMsgFile[MAX_PATH];
extern int AuraCount; //Use as counter for amount of Auras that are read in and to load in Combo box
extern int CharCount; //Use as counter for amount of Characters read in
extern int MSGCount;
extern HINSTANCE g_hInst;
extern HWND hwnd;
extern HWND hwndTab ,hwndDisplay[5];
extern HWND hComboCheck[3]; //Used to check combo box so when character change costime box can be set appropriatley
extern int ActiveTab;
struct AURA
{
	int HexID;
	std::string skillName;
};
struct COSTUME
{
	int ID;
	std::string Name;
};
struct CHARACTER
{
	int HexID;
	std::string Name;
	COSTUME List[32];
};
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
};

extern AURA AuraID[50];
extern CHARACTER CharID[150];
extern SKILL SSkillID[400], USkillID[400], ASkillID[50], ESkillID[200]; //Super, Ultimate, Awokenn Eavasive Skill variable made from skill struct
extern MSGDATA NameMSGID[300], DescMSGID[300];