#pragma once
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

void ChangeAuraColor(LRESULT Name, LRESULT Color, HWND EditError);
void ChangeCharAura(LRESULT Name, LRESULT Costume, LRESULT Color, LRESULT InfiniteCheck, HWND EditError);
int GetAura(LRESULT Name, LRESULT Costume, HWND EditError);
void LoadAura();
void LoadCharacter();
void LoadCostume();
void AuraSetup(HWND ErrorDisplay);