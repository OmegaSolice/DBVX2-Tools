#pragma once
void LoadSoulList();
void LoadPSC(STATHEADER *HData, STAT *Data, std::string PSCData);
float HextoFloat(std::string Hex);
std::string FloattoHex(std::string floatNum);
void DisplayStat(int index, HWND hDlg, STAT *Data);
void SetStat(HWND hDlg, int index, STAT *Data);
void SetPSCData(STAT *Data);
