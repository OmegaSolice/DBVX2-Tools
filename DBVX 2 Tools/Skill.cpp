#include "Header.h"

void ChangeSkill(LRESULT Name, LRESULT Costume, LRESULT SuperSkill[4], LRESULT UltimateSkill[2], LRESULT AwokenSkill, LRESULT EvasiveSkill, HWND EditError)
{
	if (Name < 0)
	{
		SetWindowText(EditError, L"Error No Name chosen");
		SetFocus(EditError);
		return;
	}
	if (Costume < 0)
	{
		SetWindowText(EditError, L"Error No Costume chosen");
		SetFocus(EditError);
		return;
	}
	if (SuperSkill < 0)
	{
		SetWindowText(EditError, L"Error a SuperSkill chosen");
		SetFocus(EditError);
		return;
	}
	if (UltimateSkill < 0)
	{
		SetWindowText(EditError, L"Error a UltimateSkill chosen");
		SetFocus(EditError);
		return;
	}
	if (AwokenSkill < 0)
	{
		SetWindowText(EditError, L"Error No Awoken chosen");
		SetFocus(EditError);
		return;
	}
	if (EvasiveSkill < 0)
	{
		SetWindowText(EditError, L"Error No Evasive chosen");
		SetFocus(EditError);
		return;
	}
	int TempName = 32 * Costume;
	int count = 0x48, check = CharID[Name].HexID;
	if (!CusData.empty())
	{

		while ((uint8_t)CusData[count] != check)
		{
			count += 0x20;
		}
		TempName += count;
		CusData[TempName + 8] = SSkillID[SuperSkill[0]].HexID1, CusData[TempName + 9] = SSkillID[SuperSkill[0]].HexID2;
		CusData[TempName + 10] = SSkillID[SuperSkill[1]].HexID1, CusData[TempName + 11] = SSkillID[SuperSkill[1]].HexID2;
		CusData[TempName + 12] = SSkillID[SuperSkill[2]].HexID1, CusData[TempName + 13] = SSkillID[SuperSkill[2]].HexID2;
		CusData[TempName + 14] = SSkillID[SuperSkill[3]].HexID1, CusData[TempName + 15] = SSkillID[SuperSkill[3]].HexID2;
		CusData[TempName + 16] = USkillID[UltimateSkill[1]].HexID1, CusData[TempName + 17] = USkillID[UltimateSkill[1]].HexID2;
		CusData[TempName + 18] = USkillID[UltimateSkill[0]].HexID1, CusData[TempName + 19] = USkillID[UltimateSkill[0]].HexID2;
		CusData[TempName + 20] = ESkillID[EvasiveSkill].HexID1, CusData[TempName + 21] = ESkillID[EvasiveSkill].HexID2;
		CusData[TempName + 24] = ASkillID[AwokenSkill].HexID1, CusData[TempName + 25] = ASkillID[AwokenSkill].HexID2;
	}
	else
	{
		SetWindowText(EditError, L"Error No Cus file not open");
		SetFocus(EditError);
		return;
	}
}

void GetSkill(LRESULT Name, LRESULT Costume, LRESULT SuperSkill[4], LRESULT UltimateSkill[2], LRESULT &AwokenSkill, LRESULT &EvasiveSkill, HWND EditError)
{
	if (Name < 0)
	{
		SetWindowText(EditError, L"Error No Name chosen");
		SetFocus(EditError);
		return ;
	}

	if (Costume < 0)
	{
		SetWindowText(EditError, L"Error No Costume chosen");
		SetFocus(EditError);
		return ;
	}

	int TempName = 32 * Costume;
	int count = 0x48;
	uint8_t	check1 = CharID[Name].HexID, check2;

	if (!CusData.empty())
	{

		while ((uint8_t)CusData[count] != check1)
		{
			count += 0x20;
		}
		TempName += count;
		
		check1 = (uint8_t) CusData[TempName + 8], check2 = (uint8_t)CusData[TempName + 9];
		count = 0;

		while (SSkillID[count].HexID1 != check1 || SSkillID[count].HexID2 != check2)
		{
			count++;
		}

		SuperSkill[0] = count;

		check1 = (uint8_t) CusData[TempName + 10], check2 = (uint8_t) CusData[TempName + 11];
		count = 0;

		while (SSkillID[count].HexID1 != check1 || SSkillID[count].HexID2 != check2)
		{
			count++;
		}

		SuperSkill[1] = count;

		check1 = (uint8_t) CusData[TempName + 12], check2 = (uint8_t)CusData[TempName + 13];
		count = 0;

		while (SSkillID[count].HexID1 != check1 || SSkillID[count].HexID2 != check2)
		{
			count++;
		}

		SuperSkill[2] = count;

		check1 = (uint8_t) CusData[TempName + 14], check2 = (uint8_t) CusData[TempName + 15];
		count = 0;

		while (SSkillID[count].HexID1 != check1 || SSkillID[count].HexID2 != check2)
		{
			count++;
		}

		SuperSkill[3] = count;

		check1 = (uint8_t) CusData[TempName + 16], check2 = (uint8_t) CusData[TempName + 17];
		count = 0;

		while (USkillID[count].HexID1 != check1 || USkillID[count].HexID2 != check2)
		{
			count++;
		}

		UltimateSkill[0] = count;

		check1 = (uint8_t) CusData[TempName + 18], check2 = (uint8_t) CusData[TempName + 19];
		count = 0;

		while (USkillID[count].HexID1 != check1 || USkillID[count].HexID2 != check2)
		{
			count++;
		}

		UltimateSkill[1] = count;

		check1 = (uint8_t) CusData[TempName + 20], check2 = (uint8_t) CusData[TempName + 21];
		count = 0;

		while (ESkillID[count].HexID1 != check1 || ESkillID[count].HexID2 != check2)
		{
			count++;
		}

		EvasiveSkill = count;

		check1 = (uint8_t) CusData[TempName + 24], check2 = (uint8_t) CusData[TempName + 25];

		count = 0;

		while (ASkillID[count].HexID1 != check1 || ASkillID[count].HexID2 != check2)
		{
			count++;
		}

		AwokenSkill = count;	
	}
	else
	{
		SetWindowText(EditError, L"Error No Cus file not open");
		SetFocus(EditError);
		return;
	}

}

int LoadSkill(char File[MAX_PATH], std::string &SkillSetting, SKILL *SkillID)
{
	openFile(File, SkillSetting);
	std::istringstream TempStream(SkillSetting);
	std::string TempString;
	int SkillCount = 1;

	while (std::getline(TempStream, TempString))
	{ 
		char CTempRefID[100] = { NULL }, CTempRefCode[10] = { NULL }, CTempName[50] = { NULL };
		char CHexID1[2] = { NULL }, CHexID2[2] = { NULL };
		std::stringstream HexID1, HexID2;
		int count = 0, countHex = 0, posSet = 0,max = TempString.size(), CTempHexID1, CTempHexID2;
		while (count <= max)
		{
			if (TempString[count] != ' ')
			{
				CTempRefID[count] = TempString[count];
				count++;
			}
			else
			{
				count += 3;
				posSet += count;
				break;
			}
		}
		while (count <= max)
		{
			if (countHex < 2)
			{
				CHexID1[count - posSet] = TempString[count];
				count++;
				countHex++;
			}
			else
			{
				HexID1 << std::hex << CHexID1;
				HexID1 >> CTempHexID1;
				posSet = count;
				countHex = 0;
				break;
			}
		}
		while (count <= max)
		{
			if (countHex < 2)
			{
				CHexID2[count - posSet] = TempString[count];
				count++;
				countHex++;
			}
			else
			{
				HexID2 << std::hex << CHexID2;
				HexID2 >> CTempHexID2;
				count += 3;
				posSet = count;
				break;
			}
		}
		while (count <= max)
		{
			if (TempString[count] != ' ')
			{
					CTempRefCode[count - posSet] = TempString[count];

				count++;
			}
			else
			{
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
		SkillID[SkillCount].RefID = CTempRefID;
		SkillID[SkillCount].HexID1 = CTempHexID1;
		SkillID[SkillCount].HexID2 = CTempHexID2;
		SkillID[SkillCount].RefCode = CTempRefCode;
		SkillID[SkillCount].Name = CTempName;
#ifdef _DEBUG
		std::cout << SkillID[SkillCount].RefID << " - " << std::hex << SkillID[SkillCount].HexID1 << std::hex << SkillID[SkillCount].HexID2 <<
			" - " << SkillID[SkillCount].RefCode << " - " << SkillID[SkillCount].Name << std::endl;
#endif
		SkillCount++;
		//memset(CTempName, 0, strlen(CTempName));
	}
	return SkillCount;
}

