#pragma once
SUPERSOUL SearchSS(int index);
void LoadEffect();
void LoadEffectAmount();
void LoadTrigger();
void LoadTC();
int SearchEffectID(int index);
int SearchEffectAmountID(int index);
int SearchFlagID(int index);
int SearchTriggerID(int index);
int SearchTimerID(int index);
int SearchTargetID(int index);
int SearchTCID(int index);
void SetSoul(HWND hDlg);
void DisplayEffect(HWND hDlg, int TabNum);
void GetCurEffect(HWND hDlg, int TabNum);
void SetAllCurEffect();