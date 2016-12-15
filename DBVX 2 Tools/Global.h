#pragma once
#include "Header.h"
extern std::string AuraData, CusData, AuraSetting, CharSetting, CostumeSetting, SSkillSetting, USkillSetting, ASkillSetting, ESkillSetting;
extern std::string NameMSGData, DescMSGData, SSIDBData, SSEffectSetting, SSEffectAmountSetting, SSTriggerSetting, SSTCSetting;
extern char AuraFile[MAX_PATH], CusFile[MAX_PATH], NameMsgFile[MAX_PATH], DescMsgFile[MAX_PATH], SSIDBFile[MAX_PATH];
extern int AuraCount; //Use as counter for amount of Auras that are read in and to load in Combo box
extern int CharCount; //Use as counter for amount of Characters read in
extern int MSGCount, SSEffectCount, SSEffectAmountCount, SSTriggerCount, SSTCCount;
extern HINSTANCE g_hInst;
extern HWND hwnd;
extern HWND hwndTab ,hwndDisplay[5];
extern HWND hComboCheck[3]; //Used to check combo box so when character change costime box can be set appropriatley
extern int ActiveTab, PrevEffectTab;
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
	int startLength;
	int endLength;
	int stringStartID1;
	int stringStartID2;
};
struct SUPERSOUL
{
	int ID;
	int Rarity;
	int Activate;
	int Price;
	int Ki_BlastType;
	int Effect[3] = { 0 };
	int Trigger[3] = { 0 };
	int Flag[3] = { 0 };
	int Timer[3] = { 0 };
	int TriggerConditions1[3] = { 0 }, TriggerConditions2[3] = { 0 }, TriggerConditions3[3] = { 0 }, TriggerConditions4[3] = { 0 };
	int TriggerConditions5[3] = { 0 };
	int EffectAmount[3] = { 0 };
	int Target[3] = { 0 };
	int Health[3] = { 0 }, Ki[3] = { 0 }, Ki_RegenRate[3] = { 0 }, Stamina[3] = { 0 }, Stamina_RegenRate[3] = { 0 }, Ground_Speed[3] = { 0 };
	int Flight_Speed[3] = { 0 }, Boost_Speed[3] = { 0 }, Dash_Speed[3] = { 0 }, Basic_Attack[3] = { 0 };
	int Ki_Blast[3] = { 0 }, Strike_Super[3] = { 0 }, Ki_Blast_Super[3] = { 0 }, Basic_Attack_Dmg[3] = { 0 }, Ki_Blast_Dmg[3] = { 0 };
	int Strike_Super_Dmg[3] = { 0 }, Ki_Blast_Super_Dmg[3] = { 0 }, Revive_Speed[3] = { 0 };
};
struct SUPERSOULSETTING
{
	int Flag[6];
	int TimerID1[6];
	int TimerID2[6];
	int Target[3];
};
struct SSEFFECT
{
	int HexID;
    std::string EffectName;
};
struct SSEFFECTAMOUNT
{
	uint8_t HexID1;
	uint8_t HexID2;
	uint8_t HexID3;
	uint8_t HexID4;
	std::string Amount;
};
struct SSTRIGGER
{
	int HexID;
	std::string Trigger;
};
struct SSTC
{
	int HexID1;
	int HexID2;
	std::string TCName;
};

extern AURA AuraID[50];
extern CHARACTER CharID[150];
extern SKILL SSkillID[400], USkillID[400], ASkillID[50], ESkillID[200]; //Super, Ultimate, Awokenn Eavasive Skill variable made from skill struct
extern MSGDATA NameMSGID[300], DescMSGID[300];
extern SUPERSOUL SSData; //Stores offset of each elements first value
extern SUPERSOUL SSCurEffect; // the index value from the list of each effect value
extern SUPERSOULSETTING SSSetting;
extern SSEFFECT SSEffectID[50];
extern SSEFFECTAMOUNT SSEAID[50];
extern SSTRIGGER SSTriggerID[50];
extern SSTC SSTCID[50];