#include "Header.h"

char FileName[MAX_PATH];
std::string AuraData, CusData, AuraSetting, CharSetting, CostumeSetting, SSkillSetting, USkillSetting, ASkillSetting, ESkillSetting;
char AuraFile[MAX_PATH], CusFile[MAX_PATH];
int AuraCount = 0;
int CharCount = 0;
AURA AuraID[50];
CHARACTER CharID[150];
SKILL SSkillID[400], USkillID[400], ASkillID[50],  ESkillID[200];
HINSTANCE g_hInst;
HWND hwnd;
HWND hwndTab, hwndDisplay[5];
HWND hComboCheck[3] = { NULL };
int ActiveTab = 0;
