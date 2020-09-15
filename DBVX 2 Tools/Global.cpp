#include "Header.h"

char FileName[MAX_PATH];
std::string AuraData, AuraSetupData, CusData, AuraSetting, CharSetting, CostumeSetting, SSkillSetting, USkillSetting, ASkillSetting, ESkillSetting;
std::string SSIDBData, PSCData, SSEffectSetting, SSEffectAmountSetting, SSTriggerSetting, SSTCSetting;
std::string SoulSetting, CSIDBData[4];
char AuraFile[MAX_PATH], CusFile[MAX_PATH], NameMsgFile[MAX_PATH], DescMsgFile[MAX_PATH], SSIDBFile[MAX_PATH], PscFile[MAX_PATH];
char NameMsgFile1[MAX_PATH], DescMsgFile1[MAX_PATH], CSIDBFile[4][MAX_PATH];
int AuraCount = 0, CharCount = 0, MSGCount = 0, SSEffectCount = 0, SSEffectAmountCount,SSTriggerCount = 0, SSTCCount = 0, SoulCount = 0;
int PSCCosCount = 0, MSGCount1 = 0;
int PrevEffectTab = 0, PrevCostumeTab = 0;
AURA AuraID[100];
CHARACTER CharID[1000];
SKILL SSkillID[1000], USkillID[1000], ASkillID[500],  ESkillID[800];
SUPERSOUL SSData, CSData[4];
SUPERSOUL SSCurEffect;
SUPERSOULSETTING SSSetting;
SSEFFECT SSEffectID[50];
SSEFFECTAMOUNT SSEAID[50];
SSTRIGGER SSTriggerID[50];
SSTC SSTCID[50];
STATHEADER HStat[500];
STAT Stats[1000];
SOULLIST SuperSoulID[500];
HINSTANCE g_hInst;
HWND hwnd;
HWND hwndTab, hwndDisplay[5];
HWND hComboCheck[5] = { NULL };
