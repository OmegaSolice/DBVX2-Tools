#include "Header.h"

void DisplayCostumeStat(HWND hDlg, int TabNum)
{
	HWND hTemp;
	wchar_t Temp[10];
	char Text[30];
	std::string CHex;
	CHex.resize(10);
	float Hex;

	if (CSData[TabNum].Rarity == 0)
	{
		sprintf(Text, "%f", 0);
		hTemp = GetDlgItem(hDlg, IDC_EDIT4);
		SetWindowTextA(hTemp, Text);
		for (int i; i < 18; i++)
		{
			hTemp = GetDlgItem(hDlg, IDC_EDIT6 + i);
			SetWindowTextA(hTemp, Text);
		}
		return;
	}

	hTemp = GetDlgItem(hDlg, IDC_EDIT4);
	wsprintfW(Temp, L"%d", CSIDBData[TabNum][CSData[TabNum].Rarity]);
	SetWindowText(hTemp, Temp);
	hTemp = GetDlgItem(hDlg, IDC_EDIT6);
	char CPrice[5];
	int Price;
	Price = ((uint8_t)CSIDBData[TabNum][CSData[TabNum].Price + 3] * 0x10000) + ((uint8_t)CSIDBData[TabNum][CSData[TabNum].Price + 2] * 0x1000)
		+ ((uint8_t)CSIDBData[TabNum][CSData[TabNum].Price + 1] * 0x100) + (uint8_t)CSIDBData[TabNum][CSData[TabNum].Price];
	sprintf(CPrice, "%d", Price);
	SetWindowTextA(hTemp, CPrice);

	hTemp = GetDlgItem(hDlg, IDC_EDIT7);
	CHex[0] = CSIDBData[TabNum][CSData[TabNum].Health[0]], CHex[1] = CSIDBData[TabNum][CSData[TabNum].Health[0] + 1], 
		CHex[2] = CSIDBData[TabNum][CSData[TabNum].Health[0] + 2], CHex[3] = CSIDBData[TabNum][CSData[TabNum].Health[0] + 3];
	Hex = HextoFloat(CHex);
	sprintf(Text, "%f", Hex);
	SetWindowTextA(hTemp, Text);
	hTemp = GetDlgItem(hDlg, IDC_EDIT8);
	CHex[0] = CSIDBData[TabNum][CSData[TabNum].Ki[0]], CHex[1] = CSIDBData[TabNum][CSData[TabNum].Ki[0] + 1],
		CHex[2] = CSIDBData[TabNum][CSData[TabNum].Ki[0] + 2], CHex[3] = CSIDBData[TabNum][CSData[TabNum].Ki[0] + 3];
	Hex = HextoFloat(CHex);
	sprintf(Text, "%f", Hex);
	SetWindowTextA(hTemp, Text);
	hTemp = GetDlgItem(hDlg, IDC_EDIT9);
	CHex[0] = CSIDBData[TabNum][CSData[TabNum].Ki_RegenRate[0]], CHex[1] = CSIDBData[TabNum][CSData[TabNum].Ki_RegenRate[0] + 1],
		CHex[2] = CSIDBData[TabNum][CSData[TabNum].Ki_RegenRate[0] + 2], CHex[3] = CSIDBData[TabNum][CSData[TabNum].Ki_RegenRate[0] + 3];
	Hex = HextoFloat(CHex);
	sprintf(Text, "%f", Hex);
	SetWindowTextA(hTemp, Text);
	hTemp = GetDlgItem(hDlg, IDC_EDIT10);
	CHex[0] = CSIDBData[TabNum][CSData[TabNum].Stamina[0]], CHex[1] = CSIDBData[TabNum][CSData[TabNum].Stamina[0] + 1],
		CHex[2] = CSIDBData[TabNum][CSData[TabNum].Stamina[0] + 2], CHex[3] = CSIDBData[TabNum][CSData[TabNum].Stamina[0] + 3];
	Hex = HextoFloat(CHex);
	sprintf(Text, "%f", Hex);
	SetWindowTextA(hTemp, Text);
	hTemp = GetDlgItem(hDlg, IDC_EDIT11);
	CHex[0] = CSIDBData[TabNum][CSData[TabNum].Stamina_RegenRate[0]], CHex[1] = CSIDBData[TabNum][CSData[TabNum].Stamina_RegenRate[0] + 1],
		CHex[2] = CSIDBData[TabNum][CSData[TabNum].Stamina_RegenRate[0] + 2], CHex[3] = CSIDBData[TabNum][CSData[TabNum].Stamina_RegenRate[0] + 3];
	Hex = HextoFloat(CHex);
	sprintf(Text, "%f", Hex);
	SetWindowTextA(hTemp, Text);
	hTemp = GetDlgItem(hDlg, IDC_EDIT12);
	CHex[0] = CSIDBData[TabNum][CSData[TabNum].Ground_Speed[0]], CHex[1] = CSIDBData[TabNum][CSData[TabNum].Ground_Speed[0] + 1],
		CHex[2] = CSIDBData[TabNum][CSData[TabNum].Ground_Speed[0] + 2], CHex[3] = CSIDBData[TabNum][CSData[TabNum].Ground_Speed[0] + 3];
	Hex = HextoFloat(CHex);
	sprintf(Text, "%f", Hex);
	SetWindowTextA(hTemp, Text);
	hTemp = GetDlgItem(hDlg, IDC_EDIT13);
	CHex[0] = CSIDBData[TabNum][CSData[TabNum].Flight_Speed[0]], CHex[1] = CSIDBData[TabNum][CSData[TabNum].Flight_Speed[0] + 1],
		CHex[2] = CSIDBData[TabNum][CSData[TabNum].Flight_Speed[0] + 2], CHex[3] = CSIDBData[TabNum][CSData[TabNum].Flight_Speed[0] + 3];
	Hex = HextoFloat(CHex);
	sprintf(Text, "%f", Hex);
	SetWindowTextA(hTemp, Text);
	hTemp = GetDlgItem(hDlg, IDC_EDIT14);
	CHex[0] = CSIDBData[TabNum][CSData[TabNum].Boost_Speed[0]], CHex[1] = CSIDBData[TabNum][CSData[TabNum].Boost_Speed[0] + 1],
		CHex[2] = CSIDBData[TabNum][CSData[TabNum].Boost_Speed[0] + 2], CHex[3] = CSIDBData[TabNum][CSData[TabNum].Boost_Speed[0] + 3];
	Hex = HextoFloat(CHex);
	sprintf(Text, "%f", Hex);
	SetWindowTextA(hTemp, Text);
	hTemp = GetDlgItem(hDlg, IDC_EDIT15);
	CHex[0] = CSIDBData[TabNum][CSData[TabNum].Dash_Speed[0]], CHex[1] = CSIDBData[TabNum][CSData[TabNum].Dash_Speed[0] + 1],
		CHex[2] = CSIDBData[TabNum][CSData[TabNum].Dash_Speed[0] + 2], CHex[3] = CSIDBData[TabNum][CSData[TabNum].Dash_Speed[0] + 3];
	Hex = HextoFloat(CHex);
	sprintf(Text, "%f", Hex);
	SetWindowTextA(hTemp, Text);
	hTemp = GetDlgItem(hDlg, IDC_EDIT16);
	CHex[0] = CSIDBData[TabNum][CSData[TabNum].Basic_Attack[0]], CHex[1] = CSIDBData[TabNum][CSData[TabNum].Basic_Attack[0] + 1],
		CHex[2] = CSIDBData[TabNum][CSData[TabNum].Basic_Attack[0] + 2], CHex[3] = CSIDBData[TabNum][CSData[TabNum].Basic_Attack[0] + 3];
	Hex = HextoFloat(CHex);
	sprintf(Text, "%f", Hex);
	SetWindowTextA(hTemp, Text);
	hTemp = GetDlgItem(hDlg, IDC_EDIT17);
	CHex[0] = CSIDBData[TabNum][CSData[TabNum].Ki_Blast[0]], CHex[1] = CSIDBData[TabNum][CSData[TabNum].Ki_Blast[0] + 1],
		CHex[2] = CSIDBData[TabNum][CSData[TabNum].Ki_Blast[0] + 2], CHex[3] = CSIDBData[TabNum][CSData[TabNum].Ki_Blast[0] + 3];
	Hex = HextoFloat(CHex);
	sprintf(Text, "%f", Hex);
	SetWindowTextA(hTemp, Text);
	hTemp = GetDlgItem(hDlg, IDC_EDIT18);
	CHex[0] = CSIDBData[TabNum][CSData[TabNum].Strike_Super[0]], CHex[1] = CSIDBData[TabNum][CSData[TabNum].Strike_Super[0] + 1],
		CHex[2] = CSIDBData[TabNum][CSData[TabNum].Strike_Super[0] + 2], CHex[3] = CSIDBData[TabNum][CSData[TabNum].Strike_Super[0] + 3];
	Hex = HextoFloat(CHex);
	sprintf(Text, "%f", Hex);
	SetWindowTextA(hTemp, Text);
	hTemp = GetDlgItem(hDlg, IDC_EDIT19);
	CHex[0] = CSIDBData[TabNum][CSData[TabNum].Ki_Blast_Super[0]], CHex[1] = CSIDBData[TabNum][CSData[TabNum].Ki_Blast_Super[0] + 1],
		CHex[2] = CSIDBData[TabNum][CSData[TabNum].Ki_Blast_Super[0] + 2], CHex[3] = CSIDBData[TabNum][CSData[TabNum].Ki_Blast_Super[0] + 3];
	Hex = HextoFloat(CHex);
	sprintf(Text, "%f", Hex);
	SetWindowTextA(hTemp, Text);
	hTemp = GetDlgItem(hDlg, IDC_EDIT20);
	CHex[0] = CSIDBData[TabNum][CSData[TabNum].Basic_Attack_Dmg[0]], CHex[1] = CSIDBData[TabNum][CSData[TabNum].Basic_Attack_Dmg[0] + 1],
		CHex[2] = CSIDBData[TabNum][CSData[TabNum].Basic_Attack_Dmg[0] + 2], CHex[3] = CSIDBData[TabNum][CSData[TabNum].Basic_Attack_Dmg[0] + 3];
	Hex = HextoFloat(CHex);
	sprintf(Text, "%f", Hex);
	SetWindowTextA(hTemp, Text);
	hTemp = GetDlgItem(hDlg, IDC_EDIT21);
	CHex[0] = CSIDBData[TabNum][CSData[TabNum].Ki_Blast_Dmg[0]], CHex[1] = CSIDBData[TabNum][CSData[TabNum].Ki_Blast_Dmg[0] + 1],
		CHex[2] = CSIDBData[TabNum][CSData[TabNum].Ki_Blast_Dmg[0] + 2], CHex[3] = CSIDBData[TabNum][CSData[TabNum].Ki_Blast_Dmg[0] + 3];
	Hex = HextoFloat(CHex);
	sprintf(Text, "%f", Hex);
	SetWindowTextA(hTemp, Text);
	hTemp = GetDlgItem(hDlg, IDC_EDIT22);
	CHex[0] = CSIDBData[TabNum][CSData[TabNum].Strike_Super_Dmg[0]], CHex[1] = CSIDBData[TabNum][CSData[TabNum].Strike_Super_Dmg[0] + 1],
		CHex[2] = CSIDBData[TabNum][CSData[TabNum].Strike_Super_Dmg[0] + 2], CHex[3] = CSIDBData[TabNum][CSData[TabNum].Strike_Super_Dmg[0] + 3];
	Hex = HextoFloat(CHex);
	sprintf(Text, "%f", Hex);
	SetWindowTextA(hTemp, Text);
	hTemp = GetDlgItem(hDlg, IDC_EDIT23);
	CHex[0] = CSIDBData[TabNum][CSData[TabNum].Ki_Blast_Super_Dmg[0]], CHex[1] = CSIDBData[TabNum][CSData[TabNum].Ki_Blast_Super_Dmg[0] + 1],
		CHex[2] = CSIDBData[TabNum][CSData[TabNum].Ki_Blast_Super_Dmg[0] + 2], CHex[3] = CSIDBData[TabNum][CSData[TabNum].Ki_Blast_Super_Dmg[0] + 3];
	Hex = HextoFloat(CHex);
	sprintf(Text, "%f", Hex);
	SetWindowTextA(hTemp, Text);
	hTemp = GetDlgItem(hDlg, IDC_EDIT24);
	CHex[0] = CSIDBData[TabNum][CSData[TabNum].Revive_Speed[0]], CHex[1] = CSIDBData[TabNum][CSData[TabNum].Revive_Speed[0] + 1],
		CHex[2] = CSIDBData[TabNum][CSData[TabNum].Revive_Speed[0] + 2], CHex[3] = CSIDBData[TabNum][CSData[TabNum].Revive_Speed[0] + 3];
	Hex = HextoFloat(CHex);
	sprintf(Text, "%f", Hex);
	SetWindowTextA(hTemp, Text);
}

void SetAllCurCostumeStat()
{
	int TabNum = 0;

	while (TabNum < 4)
	{
		CSCurEffect[TabNum].Health[0] = SearchEffectAmountID(CSData[TabNum].Health[0], CSIDBData[TabNum]);
		CSCurEffect[TabNum].Ki[0] = SearchEffectAmountID(CSData[TabNum].Ki[0], CSIDBData[TabNum]);
		CSCurEffect[TabNum].Ki_RegenRate[0] = SearchEffectAmountID(CSData[TabNum].Ki_RegenRate[0], CSIDBData[TabNum]);
		CSCurEffect[TabNum].Stamina[0] = SearchEffectAmountID(SSData.Stamina[0], CSIDBData[TabNum]);
		CSCurEffect[TabNum].Stamina_RegenRate[0] = SearchEffectAmountID(CSData[TabNum].Stamina_RegenRate[0], CSIDBData[TabNum]);
		CSCurEffect[TabNum].Ground_Speed[0] = SearchEffectAmountID(CSData[TabNum].Ground_Speed[0], CSIDBData[TabNum]);
		CSCurEffect[TabNum].Flight_Speed[0] = SearchEffectAmountID(CSData[TabNum].Flight_Speed[0], CSIDBData[TabNum]);
		CSCurEffect[TabNum].Boost_Speed[0] = SearchEffectAmountID(CSData[TabNum].Boost_Speed[0], CSIDBData[TabNum]);
		CSCurEffect[TabNum].Dash_Speed[0] = SearchEffectAmountID(CSData[TabNum].Dash_Speed[0], CSIDBData[TabNum]);
		CSCurEffect[TabNum].Basic_Attack[0] = SearchEffectAmountID(CSData[TabNum].Basic_Attack[0], CSIDBData[TabNum]);
		CSCurEffect[TabNum].Ki_Blast[0] = SearchEffectAmountID(CSData[TabNum].Ki_Blast[0], CSIDBData[TabNum]);
		CSCurEffect[TabNum].Strike_Super[0] = SearchEffectAmountID(CSData[TabNum].Strike_Super[0], CSIDBData[TabNum]);
		CSCurEffect[TabNum].Ki_Blast_Super[0] = SearchEffectAmountID(CSData[TabNum].Ki_Blast_Super[TabNum], CSIDBData[TabNum]);
		CSCurEffect[TabNum].Basic_Attack_Dmg[0] = SearchEffectAmountID(CSData[TabNum].Basic_Attack_Dmg[0], CSIDBData[TabNum]);
		CSCurEffect[TabNum].Ki_Blast_Dmg[0] = SearchEffectAmountID(CSData[TabNum].Ki_Blast_Dmg[0], CSIDBData[TabNum]);
		CSCurEffect[TabNum].Strike_Super_Dmg[0] = SearchEffectAmountID(CSData[TabNum].Strike_Super_Dmg[0], CSIDBData[TabNum]);
		CSCurEffect[TabNum].Ki_Blast_Super_Dmg[0] = SearchEffectAmountID(CSData[TabNum].Ki_Blast_Super_Dmg[0], CSIDBData[TabNum]);
		CSCurEffect[TabNum].Revive_Speed[0] = SearchEffectAmountID(CSData[TabNum].Revive_Speed[0], CSIDBData[TabNum]);

		TabNum++;
	}
}

void SetCurCostumeStat(HWND hDlg, int TabNum, std::string *IDBData )
{
	HWND hTemp;
	char Text[10];
	int SSIndex = 0;

	hTemp = GetDlgItem(hDlg, IDC_EDIT7);
	GetWindowTextA(hTemp, Text, 10);
	IDBData[TabNum].erase(CSData[TabNum].Health[0], 4);
	IDBData[TabNum].insert(CSData[TabNum].Health[0], FloattoHex(atof(Text)));
	hTemp = GetDlgItem(hDlg, IDC_EDIT8);
	GetWindowTextA(hTemp, Text, 10);
	IDBData[TabNum].erase(CSData[TabNum].Ki[0], 4);
	IDBData[TabNum].insert(CSData[TabNum].Ki[0], FloattoHex(atof(Text)));
	hTemp = GetDlgItem(hDlg, IDC_EDIT9);
	GetWindowTextA(hTemp, Text, 10);
	IDBData[TabNum].erase(CSData[TabNum].Ki_RegenRate[0], 4);
	IDBData[TabNum].insert(CSData[TabNum].Ki_RegenRate[0], FloattoHex(atof(Text)));
	hTemp = GetDlgItem(hDlg, IDC_EDIT10);
	GetWindowTextA(hTemp, Text, 10);
	IDBData[TabNum].erase(CSData[TabNum].Stamina[0], 4);
	IDBData[TabNum].insert(CSData[TabNum].Stamina[0], FloattoHex(atof(Text)));
	hTemp = GetDlgItem(hDlg, IDC_EDIT11);
	GetWindowTextA(hTemp, Text, 10);
	IDBData[TabNum].erase(CSData[TabNum].Stamina_RegenRate[0], 4);
	IDBData[TabNum].insert(CSData[TabNum].Stamina_RegenRate[0], FloattoHex(atof(Text)));
	hTemp = GetDlgItem(hDlg, IDC_EDIT12);
	GetWindowTextA(hTemp, Text, 10);
	IDBData[TabNum].erase(CSData[TabNum].Ground_Speed[0], 4);
	IDBData[TabNum].insert(CSData[TabNum].Ground_Speed[0], FloattoHex(atof(Text)));
	hTemp = GetDlgItem(hDlg, IDC_EDIT13);
	GetWindowTextA(hTemp, Text, 10);
	IDBData[TabNum].erase(CSData[TabNum].Flight_Speed[0], 4);
	IDBData[TabNum].insert(CSData[TabNum].Flight_Speed[0], FloattoHex(atof(Text)));
	hTemp = GetDlgItem(hDlg, IDC_EDIT14);
	GetWindowTextA(hTemp, Text, 10);
	IDBData[TabNum].erase(CSData[TabNum].Boost_Speed[0], 4);
	IDBData[TabNum].insert(CSData[TabNum].Boost_Speed[0], FloattoHex(atof(Text)));
	hTemp = GetDlgItem(hDlg, IDC_EDIT15);
	GetWindowTextA(hTemp, Text, 10);
	IDBData[TabNum].erase(CSData[TabNum].Dash_Speed[0], 4);
	IDBData[TabNum].insert(CSData[TabNum].Dash_Speed[0], FloattoHex(atof(Text)));
	hTemp = GetDlgItem(hDlg, IDC_EDIT16);
	GetWindowTextA(hTemp, Text, 10);
	IDBData[TabNum].erase(CSData[TabNum].Basic_Attack[0], 4);
	IDBData[TabNum].insert(CSData[TabNum].Basic_Attack[0], FloattoHex(atof(Text)));
	hTemp = GetDlgItem(hDlg, IDC_EDIT17);
	GetWindowTextA(hTemp, Text, 10);
	IDBData[TabNum].erase(CSData[TabNum].Ki_Blast[0], 4);
	IDBData[TabNum].insert(CSData[TabNum].Ki_Blast[0], FloattoHex(atof(Text)));
	hTemp = GetDlgItem(hDlg, IDC_EDIT18);
	GetWindowTextA(hTemp, Text, 10);
	IDBData[TabNum].erase(CSData[TabNum].Strike_Super[0], 4);
	IDBData[TabNum].insert(CSData[TabNum].Strike_Super[0], FloattoHex(atof(Text)));
	hTemp = GetDlgItem(hDlg, IDC_EDIT19);
	GetWindowTextA(hTemp, Text, 10);
	IDBData[TabNum].erase(CSData[TabNum].Ki_Blast_Super[0], 4);
	IDBData[TabNum].insert(CSData[TabNum].Ki_Blast_Super[0], FloattoHex(atof(Text)));
	hTemp = GetDlgItem(hDlg, IDC_EDIT20);
	GetWindowTextA(hTemp, Text, 10);
	IDBData[TabNum].erase(CSData[TabNum].Basic_Attack_Dmg[0], 4);
	IDBData[TabNum].insert(CSData[TabNum].Basic_Attack_Dmg[0], FloattoHex(atof(Text)));
	hTemp = GetDlgItem(hDlg, IDC_EDIT21);
	GetWindowTextA(hTemp, Text, 10);
	IDBData[TabNum].erase(CSData[TabNum].Ki_Blast_Dmg[0], 4);
	IDBData[TabNum].insert(CSData[TabNum].Ki_Blast_Dmg[0], FloattoHex(atof(Text)));
	hTemp = GetDlgItem(hDlg, IDC_EDIT22);
	GetWindowTextA(hTemp, Text, 10);
	IDBData[TabNum].erase(CSData[TabNum].Strike_Super_Dmg[0], 4);
	IDBData[TabNum].insert(CSData[TabNum].Strike_Super_Dmg[0], FloattoHex(atof(Text)));
	hTemp = GetDlgItem(hDlg, IDC_EDIT23);
	GetWindowTextA(hTemp, Text, 10);
	IDBData[TabNum].erase(CSData[TabNum].Ki_Blast_Super_Dmg[0], 4);
	IDBData[TabNum].insert(CSData[TabNum].Ki_Blast_Super_Dmg[0], FloattoHex(atof(Text)));
	hTemp = GetDlgItem(hDlg, IDC_EDIT24);
	GetWindowTextA(hTemp, Text, 10);
	IDBData[TabNum].erase(CSData[TabNum].Revive_Speed[0], 4);
	IDBData[TabNum].insert(CSData[TabNum].Revive_Speed[0], FloattoHex(atof(Text)));
}