#include "Header.h"



void ChangeAuraColor(LRESULT Name, LRESULT Color, HWND EditError)
{
	if (Name < 0)
	{
		if (EditError)
		{
			SetWindowText(EditError, L"There is no name selected");
		}
	}
	if (!AuraData.empty())
	{
		int TempName = 0x20 + (16 * Name);
		int TempColor = 0x20 + (16 * Color);
		AuraData[TempName + 12] = AuraData[TempColor + 12];
		AuraData[TempName + 13] = AuraData[TempColor + 13];
	}
	else
	{
		SetWindowText(EditError, L"Error No Aura file not open");
		SetFocus(EditError);
		return;
	}
}

void ChangeCharAura(LRESULT Name, LRESULT Costume, LRESULT Color, LRESULT InfiniteCheck, HWND EditError)
{
	if (Name < 0)
	{
		SetWindowText(EditError, L"Error No name chosen");
		SetFocus(EditError);
		return ;
	}
	if (Costume < 0)
	{
		SetWindowText(EditError, L"Error No Costume chosen");
		SetFocus(EditError);
		return ;
	}
	if (Color < 0)
	{
		SetWindowText(EditError, L"Error No Color chosen");
		SetFocus(EditError);
		return ;
	}
	int TempName = 16 * Costume;
	int TempColor = 0x20 + (16 * Color);
	int count = 0xA20, check = CharID[Name].HexID;
	if (!AuraData.empty())
	{

		while ((uint8_t) AuraData[count] != check)
		{
			count+= 0x10;
		}
		TempName += count;
		AuraData[TempName + 8] = AuraData[TempColor];
		if (InfiniteCheck == BST_CHECKED)
		{
			AuraData[TempName + 12] = 0x01;
		}
		else
		{
			AuraData[TempName + 12] = 0x00;
		}
	}
	else
	{
		SetWindowText(EditError, L"Error No Aura file not open");
		SetFocus(EditError);
		return;
	}
}

int GetAura(LRESULT Name, LRESULT Costume, HWND EditError)
{
	int TempName = 16 * Costume;
	int count = 0xA20, check = CharID[Name].HexID, Offset;

	if (Name < 0)
	{
		SetWindowText(EditError, L"Error No Name chosen");
		SetFocus(EditError);
		return  -2;
	}

	if (Costume < 0)
	{
		SetWindowText(EditError, L"Error No Costume chosen");
		SetFocus(EditError);
		return  -2;
	}
	if (!AuraData.empty())
	{


		while ((uint8_t)AuraData[count] != check)
		{
			count += 0x10;
		}
		TempName += count;

		check = AuraData[TempName + 8];
		count = 0;

		while (AuraID[count].HexID != check)
		{
			count ++;
		}
		Offset = count;
		return Offset ;
	}
	else
	{
		SetWindowText(EditError, L"Error No Aura file not open");
		SetFocus(EditError);
		return -2;
	}
	
}

void LoadAura()
{
	openFile("Data/Aura ID.ini", AuraSetting);
	std::istringstream TempStream(AuraSetting);
	std::string TempString;
	int CTempHexID;
	char CTempValue[105] = { NULL };

	while (std::getline(TempStream, TempString))
	{

		int count = 0, posSet = 0, max = TempString.size();
		std::stringstream HexID;
		char CHexID[2] = { NULL };
		while (count <= max)
		{
			if (TempString[count] != ' ')
			{
				CHexID[count] = TempString[count];
				count++;
			}
			else
			{
				HexID << std::hex << CHexID;
				HexID >> CTempHexID;
				posSet = count;
				count += 3;
				posSet = count;
				break;
			}
		}
		while (count <= max)
		{
			if (TempString[count] != ';')
			{
				CTempValue[count - posSet] = TempString[count];
				count++;
			}
			else
			{
				break;
			}
		}
		AuraID[AuraCount].HexID = CTempHexID;
		AuraID[AuraCount].skillName = CTempValue;
#ifdef _DEBUG
		std::cout << AuraID[AuraCount].HexID << " - " << AuraID[AuraCount].skillName << std::endl;
#endif
		memset(CTempValue, 0, strlen(CTempValue));
		AuraCount++;
	}
}

void LoadCharacter()
{
	openFile("Data/Character ID.ini", CharSetting);
	std::istringstream TempStream(CharSetting);
	std::string TempString;
	char  CTempValue[105] = { NULL };


	while (std::getline(TempStream, TempString))
	{

		int count = 0, posSet = 0, max = TempString.size();
		int CTempHexID;
		std::stringstream HexID;
		char CHexID[2] = { NULL };
		while (count <= max)
		{
			if (TempString[count] != ' ')
			{
				CHexID[count] = TempString[count];
				count++;
			}
			else
			{
				HexID << std::hex << CHexID;
				HexID >> CTempHexID;
				posSet = count;
				count += 3;
				posSet = count;
				break;
			}
		}

		while (count <= max)
		{
			if (TempString[count] != ';')
			{
					CTempValue[count - posSet] = TempString[count];
					count++;
			}
			else
			{
				break;
			}
		}
		CharID[CharCount].HexID = CTempHexID;
		CharID[CharCount].Name = CTempValue;
#ifdef _DEBUG
		std::cout << CharID[CharCount].HexID << " - " << CharID[CharCount].Name << std::endl;
#endif
		memset(CTempValue, 0, strlen(CTempValue));//Used to clear CTempValue to ensure names dont have ectra characters from previous names  
		CharCount++;
	}
}

void LoadCostume()
{
	openFile("Data/Costume ID.ini", CostumeSetting);
	std::istringstream TempStream(CostumeSetting);
	std::string TempString;
	char CTempHexID[5] = { NULL }, CTempName[105] = { NULL }, TempCheck[3] = { NULL };
	int CosCount = 0, CharCheck = 0, fCount = 0;

	while (std::getline(TempStream, TempString))
	{

		int count = 0, posSet = 0, max = TempString.size();
		int  CTempHexID, CTempCheck;
		std::stringstream HexID, Check;
		char CHexID [2];

		while (count <= max)
		{
			
			if (TempString[count] != ' ')
			{
				TempCheck[count] = TempString[count];
				count++;
			}
			else
			{
				Check << std::hex << TempCheck;
				Check >> CTempCheck;

				if (CTempCheck == CharID[CharCheck].HexID)
				{
					if (fCount != 0)
					{
						CosCount++;
					}	
				}
				else
				{
					CosCount = 0;
					CharCheck++;
				}
				count += 3;
				posSet = count;
				break;
			}
		}
		while (count <= max)
		{
			if (TempString[count] != ' ')
			{
				CHexID[count - posSet] = TempString[count];
				count++;
			}
			else
			{
				HexID << std::hex << CHexID;
				HexID >> CTempHexID;
				posSet = count;
				count += 3;
				posSet = count; 
				break;
			}
		}
		while (count <= max)
		{
			if (TempString[count] != ';')
			{
					CTempName[count - posSet] = TempString[count];
					count++;
			}
			else
			{
				break;
			}
		}


		CharID[CharCheck].List[CosCount].ID = CTempHexID;
		CharID[CharCheck].List[CosCount].Name = CTempName;
#ifdef _DEBUG
		std::cout << CharID[CharCheck].List[CosCount].ID << " - " << CharID[CharCheck].List[CosCount].Name << std::endl;
#endif
		memset(CTempName, 0, strlen(CTempName));//Used to clear CTempValue to ensure names dont have ectra characters from previous names 
		fCount++;
	} 
}
