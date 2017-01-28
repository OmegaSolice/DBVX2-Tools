#pragma once
struct STATHEADER
{
	int CharHexID;
	int CostumeAmount;
};
struct STAT
{
	int Offset;
	int CostumeID;
	int Camera_Position;
	float Health, Ki, Ki_Recharge, Stamina, Stamina_RechargeM, Stamina_RechargeA, Stamina_RechargeG, Stamina_Drain1, Stamina_Drain2;
	float Basic_Attack, Ki_Blast, Strike_Super, Ki_BlastSuper, Basic_Def, Ki_Blast_Def, Strike_Super_Def, Ki_BlastSuper_Def;
	float Ground_Speed, Air_Speed, Boost_Speed, Dash_Distance, Reinforcement_Skill_Duration, RevivalHP, Reviving_Speed;
	int Super_Soul;
};
struct SOULLIST
{
	int HexID;
	std::string Name;
};
void LoadSoulList();
void LoadPSC(STATHEADER *HData, STAT *Data, std::string PSCData);
float HextoFloat(std::string Hex);
std::string FloattoHex(float floatNum);
void DisplayStat(int index, HWND hDlg, STAT *Data);
void SetStat(HWND hDlg, int index, STAT *Data);
void SetAllStat(HWND hDlg, STAT *Data);
void SetPSCData(STAT *Data);
