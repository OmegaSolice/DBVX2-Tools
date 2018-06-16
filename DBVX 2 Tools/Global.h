#pragma once
#include "Header.h"
extern std::string AuraData, CusData, AuraSetting, CharSetting, CostumeSetting, SSkillSetting, USkillSetting, ASkillSetting, ESkillSetting;
extern std::string SSIDBData, PSCData, SSEffectSetting, SSEffectAmountSetting, SSTriggerSetting, SSTCSetting;
extern std::string SoulSetting, CSIDBData[4];
extern char AuraFile[MAX_PATH], CusFile[MAX_PATH], NameMsgFile[MAX_PATH], DescMsgFile[MAX_PATH], SSIDBFile[MAX_PATH], PscFile[MAX_PATH];
extern char NameMsgFile1[MAX_PATH], DescMsgFile1[MAX_PATH], CSIDBFile[4][MAX_PATH];
extern int AuraCount; //Use as counter for amount of Auras that are read in and to load in Combo box
extern int CharCount; //Use as counter for amount of Characters read in
extern int MSGCount, SSEffectCount, SSEffectAmountCount, SSTriggerCount, SSTCCount, SoulCount, PSCCosCount, MSGCount1;
extern HINSTANCE g_hInst;
extern HWND hwnd;
extern HWND hwndTab ,hwndDisplay[5];
extern HWND hComboCheck[5]; //Used to check combo box so when character change costime box can be set appropriatley
extern int PrevEffectTab, PrevCostumeTab;
extern AURA AuraID[100];
extern CHARACTER CharID[200];
extern SKILL SSkillID[400], USkillID[400], ASkillID[50], ESkillID[200]; //Super, Ultimate, Awokenn Eavasive Skill variable made from skill struct;
extern SUPERSOUL SSData, CSData[4]; //Stores offset of each elements first value
extern SUPERSOUL SSCurEffect; // the index value from the list of each effect value
extern SUPERSOULSETTING SSSetting;
extern SSEFFECT SSEffectID[50];
extern SSEFFECTAMOUNT SSEAID[50];
extern SSTRIGGER SSTriggerID[50];
extern SSTC SSTCID[50];
extern STATHEADER HStat[200];
extern STAT Stats[500];
extern SOULLIST SuperSoulID[215];