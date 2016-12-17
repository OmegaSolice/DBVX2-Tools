#include "Header.h"

char FileName[MAX_PATH];
std::string AuraData, CusData, AuraSetting, CharSetting, CostumeSetting, SSkillSetting, USkillSetting, ASkillSetting, ESkillSetting;
std::string NameMSGData, DescMSGData, SSIDBData, PSCData, SSEffectSetting, SSEffectAmountSetting, SSTriggerSetting, SSTCSetting;
std::string SoulSetting;
char AuraFile[MAX_PATH], CusFile[MAX_PATH], NameMsgFile[MAX_PATH], DescMsgFile[MAX_PATH], SSIDBFile[MAX_PATH], PscFile[MAX_PATH];
int AuraCount = 0, CharCount = 0, MSGCount = 0, SSEffectCount = 0, SSEffectAmountCount,SSTriggerCount = 0, SSTCCount = 0, SoulCount = 0;
int PSCCosCount = 0;
AURA AuraID[50];
CHARACTER CharID[150];
SKILL SSkillID[400], USkillID[400], ASkillID[50],  ESkillID[200];
MSGDATA NameMSGID[300], DescMSGID[300];
SUPERSOUL SSData;
SUPERSOUL SSCurEffect;
SUPERSOULSETTING SSSetting;
SSEFFECT SSEffectID[50];
SSEFFECTAMOUNT SSEAID[50];
SSTRIGGER SSTriggerID[50];
SSTC SSTCID[50];
STATHEADER HStat[200];
STAT Stats[500];
SOULLIST SuperSoulID[215];
HINSTANCE g_hInst;
HWND hwnd;
HWND hwndTab, hwndDisplay[5];
HWND hComboCheck[4] = { NULL };
int ActiveTab = 0, PrevEffectTab = 0;
