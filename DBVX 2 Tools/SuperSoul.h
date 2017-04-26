#pragma once
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
SUPERSOUL SearchIDB(int index, std::string IDBData);
void LoadEffect();
void LoadEffectAmount();
void LoadTrigger();
void LoadTC();
int SearchEffectID(int index);
int SearchEffectAmountID(int index, std::string IDBData);
int SearchFlagID(int index);
int SearchTriggerID(int index);
int SearchTimerID(int index);
int SearchTargetID(int index);
int SearchTCID(int index);
void SetSoul(HWND hDlg);
void DisplayEffect(HWND hDlg, int TabNum);
void GetCurEffect(HWND hDlg, int TabNum);
void SetAllCurEffect();
//void IDBSetup();