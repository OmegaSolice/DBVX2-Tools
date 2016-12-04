#include "Header.h"

//#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version = '6.0.0.0' processorArchitecture = '*' publicKeyToken = '6595b64144ccf1df' language = '*'\"")


LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
#ifdef _DEBUG
	AllocConsole();
	freopen("CONOUT$", "w", stdout);
	freopen("CONOUT$", "w", stderr);
	freopen("CONIN$", "r", stdin);
	std::wcout.clear();
	std::cout.clear();
	std::wcerr.clear();
	std::cerr.clear();
	std::wcin.clear();
	std::cin.clear();

	std::cout << "Console Initialzed" << std::endl;
#endif // _DEBUG

	WNDCLASSEX wcex;
	ZeroMemory(&wcex, sizeof(WNDCLASSEX));
	wcex.cbClsExtra = 0;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.cbWndExtra = 0;
	wcex.hbrBackground = CreatePatternBrush(LoadBitmap(hInstance, (LPCWSTR)IDR_IMAGE1));
	wcex.hCursor = NULL;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	wcex.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	wcex.hInstance = hInstance;
	wcex.lpfnWndProc = WndProc;
	wcex.lpszClassName = L"Window";
	wcex.lpszMenuName = NULL;// MAKEINTRESOURCE(IDR_MENU1);
	wcex.style = CS_VREDRAW | CS_HREDRAW;

	if (!RegisterClassEx(&wcex))
	{
		MessageBox(NULL, L"Class failed to register", L"Error", MB_ICONERROR | MB_OK);
	}

	HWND hwnd = CreateWindowEx(WS_EX_CLIENTEDGE, L"Window", L"DBXV Tool", WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
		CW_USEDEFAULT, CW_USEDEFAULT, 700, 900, NULL, NULL, hInstance, NULL);
	if (hwnd == NULL)
	{
		MessageBox(NULL, L"Window Creation fail", L"Error", MB_ICONERROR | MB_OK);
	}

	g_hInst = hInstance;
	int  count = 0;
	SSkillID[0].RefID = -1, SSkillID[0].HexID1 = 0xff, SSkillID[0].HexID2 = 0xff, SSkillID[0].RefCode = 'BLK', SSkillID[0].Name = '----';
	USkillID[0].RefID = -1, USkillID[0].HexID1 = 0xff, USkillID[0].HexID2 = 0xff, USkillID[0].RefCode = 'BLK', USkillID[0].Name = '----';
	ASkillID[0].RefID = -1, ASkillID[0].HexID1 = 0xff, ASkillID[0].HexID2 = 0xff, ASkillID[0].RefCode = 'BLK', ASkillID[0].Name = '----';
	ESkillID[0].RefID = -1, ESkillID[0].HexID1 = 0xff, ESkillID[0].HexID2 = 0xff, ESkillID[0].RefCode = 'BLK', ESkillID[0].Name = '----';
	SSSetting.Flag[0] = 0xff, SSSetting.Flag[1] = 0x01, SSSetting.Flag[2] = 0x0A, SSSetting.Flag[3] = 0x0A, SSSetting.Flag[4] = 0x00;
	SSSetting.TimerID1[0] = 0x80, SSSetting.TimerID2[0] = 0xBF, SSSetting.TimerID1[1] = 0x70, SSSetting.TimerID2[1] = 0x41;
	SSSetting.TimerID1[2] = 0xF0, SSSetting.TimerID2[2] = 0x41, SSSetting.TimerID1[3] = 0x70, SSSetting.TimerID2[3] = 0x42;
	SSSetting.TimerID1[4] = 0xff, SSSetting.TimerID2[4] = 0xff, SSSetting.TimerID1[5] = 0x00, SSSetting.TimerID2[5] = 0x00;
	SSSetting.Target[0] = 0x00, SSSetting.Target[1] = 0x01, SSSetting.Target[2] = 0x05;

	LoadAura();
	LoadCharacter();
	LoadCostume();
	int SSkillCount = LoadSkill("Data/Super Skill ID.ini", SSkillSetting, SSkillID);
	int USkillCount = LoadSkill("Data/Ultimate Skill ID.ini", USkillSetting, USkillID);
	int ASkillCount = LoadSkill("Data/Awoken Skill ID.ini", ASkillSetting, ASkillID);
	int ESkillCount = LoadSkill("Data/Evasive Skill ID.ini", ESkillSetting, ESkillID);
	LoadEffect();
	LoadEffectAmount();
	LoadTrigger();
	LoadTC();

	TCHAR *TabLabel[] = { L"Aura", L"Skill", L"Super Soul", L"Fusion" };
	count = 0;
	int numTab = 4;
	HWND hTemp;
	DWORD Err = NULL;
	WCHAR WERR[100] = L"";

	hwndTab = CreateTabControl(hwnd, g_hInst, numTab, TabLabel);
	hwndDisplay[0] = CreateDialog(g_hInst, MAKEINTRESOURCE(IDD_DIALOG1), hwndTab, MainDialogProc);
	if (!hwndDisplay[0]) { Err = GetLastError();  swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
	hwndDisplay[1] = CreateDialog(g_hInst, MAKEINTRESOURCE(IDD_DIALOG2), hwndTab, MainDialogProc);
	if (!hwndDisplay[1]) { Err = GetLastError();  swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
	hwndDisplay[2] = CreateDialog(g_hInst, MAKEINTRESOURCE(IDD_DIALOG3), hwndTab, MainDialogProc);
	if (!hwndDisplay[2]) { Err = GetLastError();  swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
	hwndDisplay[3] = CreateDialog(g_hInst, MAKEINTRESOURCE(IDD_DIALOG4), hwndTab, MainDialogProc);
	if (!hwndDisplay[3]) { Err = GetLastError();  swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }

	while (count < numTab )        //resizes dialog to window client
	{
		DialogResize(hwndTab, hwndDisplay[count]);
		count++;
	}
	
	count = 0; 
	while (count < AuraCount)
	{
		size_t size = strlen(AuraID[count].skillName.c_str()) + 1;
		wchar_t *ComboBoxItemAuraTemp = new wchar_t[size];

		size_t outSize;
		mbstowcs_s(&outSize, ComboBoxItemAuraTemp, size, AuraID[count].skillName.c_str(), size - 1);
		const TCHAR *ComboBoxItemAura = { ComboBoxItemAuraTemp };
		hTemp = GetDlgItem(hwndDisplay[0], IDC_COMBO1);
		if (!hTemp) { Err = GetLastError();  swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		SendMessage(hTemp, CB_ADDSTRING, 0, reinterpret_cast <LPARAM> ((LPCTSTR)ComboBoxItemAura));
		if ((Err = GetLastError()) != 0) { swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		hTemp = GetDlgItem(hwndDisplay[0], IDC_COMBO2);
		if (!hTemp) { Err = GetLastError();  swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		SendMessage(hTemp, CB_ADDSTRING, 0, reinterpret_cast <LPARAM> ((LPCTSTR)ComboBoxItemAura));
		if ((Err = GetLastError()) != 0) { swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		hTemp = GetDlgItem(hwndDisplay[0], IDC_COMBO5);
		SendMessage(hTemp, CB_ADDSTRING, 0, reinterpret_cast <LPARAM> ((LPCTSTR)ComboBoxItemAura));
		if ((Err = GetLastError()) != 0) { swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		count++;
	}

	count = 0;
	while (count < CharCount)
	{
		size_t size = strlen(CharID[count].Name.c_str()) + 1;
		wchar_t *ComboBoxItemCharTemp = new wchar_t[size];

		size_t outSize;
		mbstowcs_s(&outSize, ComboBoxItemCharTemp, size, CharID[count].Name.c_str(), size - 1);
		const TCHAR *ComboBoxItemChar = { ComboBoxItemCharTemp };
		hTemp = GetDlgItem(hwndDisplay[0], IDC_COMBO3);
		if (!hTemp) { Err = GetLastError(); swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		SendMessage(hTemp, CB_ADDSTRING, 0, reinterpret_cast <LPARAM> ((LPCTSTR)ComboBoxItemChar));
		if ((Err = GetLastError()) != 0) { swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		hTemp = GetDlgItem(hwndDisplay[1], IDC_COMBO6);
		Err = SendMessage(hTemp, CB_ADDSTRING, 0, reinterpret_cast <LPARAM> ((LPCTSTR)ComboBoxItemChar));
		if ((Err = GetLastError()) != 0) { swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		count++;
	}

	hComboCheck[0] = GetDlgItem(hwndDisplay[0], IDC_COMBO3); //Used to check combo box so when character change costume box can be set appropriatley  
	hComboCheck[1] = GetDlgItem(hwndDisplay[1], IDC_COMBO6);
	hComboCheck[2] = GetDlgItem(hwndDisplay[2], IDC_COMBO1);
	
	count = 0;
	//int maxCount = sizeof(SSkillID) / sizeof SKILL;

	while (count < SSkillCount)
	{
		size_t size = strlen(SSkillID[count].Name.c_str()) + 1;
		wchar_t *ComboBoxItemSkillTemp = new wchar_t[size];

		size_t outSize;
		mbstowcs_s(&outSize, ComboBoxItemSkillTemp, size, SSkillID[count].Name.c_str(), size - 1);
		const TCHAR *ComboBoxItemSkill = { ComboBoxItemSkillTemp };
		hTemp = GetDlgItem(hwndDisplay[1], IDC_COMBO8);
		if (!hTemp) { Err = GetLastError(); swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		Err = SendMessage(hTemp, CB_ADDSTRING, 0, reinterpret_cast <LPARAM> ((LPCTSTR)ComboBoxItemSkill));
		if ((Err = GetLastError()) != 0) { swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		hTemp = GetDlgItem(hwndDisplay[1], IDC_COMBO9);
		if (!hTemp) { Err = GetLastError(); swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		Err = SendMessage(hTemp, CB_ADDSTRING, 0, reinterpret_cast <LPARAM> ((LPCTSTR)ComboBoxItemSkill));
		if ((Err = GetLastError()) != 0) { swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		hTemp = GetDlgItem(hwndDisplay[1], IDC_COMBO10);
		if (!hTemp) { Err = GetLastError(); swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		Err = SendMessage(hTemp, CB_ADDSTRING, 0, reinterpret_cast <LPARAM> ((LPCTSTR)ComboBoxItemSkill));
		if ((Err = GetLastError()) != 0) { swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		hTemp = GetDlgItem(hwndDisplay[1], IDC_COMBO11);
		if (!hTemp) { Err = GetLastError(); swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		Err = SendMessage(hTemp, CB_ADDSTRING, 0, reinterpret_cast <LPARAM> ((LPCTSTR)ComboBoxItemSkill));
		if ((Err = GetLastError()) != 0) { swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		count++;
	}

	count = 0;

	while (count < USkillCount)
	{
		size_t size = strlen(USkillID[count].Name.c_str()) + 1;
		wchar_t *ComboBoxItemSkillTemp = new wchar_t[size];

		size_t outSize;
		mbstowcs_s(&outSize, ComboBoxItemSkillTemp, size, USkillID[count].Name.c_str(), size - 1);
		const TCHAR *ComboBoxItemSkill = { ComboBoxItemSkillTemp };
		hTemp = GetDlgItem(hwndDisplay[1], IDC_COMBO12);
		if (!hTemp) { Err = GetLastError(); swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
 		Err = SendMessage(hTemp, CB_ADDSTRING, 0, reinterpret_cast <LPARAM> ((LPCTSTR)ComboBoxItemSkill));
		if ((Err = GetLastError()) != 0) { swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		hTemp = GetDlgItem(hwndDisplay[1], IDC_COMBO13);
		if (!hTemp) { Err = GetLastError(); swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		Err = SendMessage(hTemp, CB_ADDSTRING, 0, reinterpret_cast <LPARAM> ((LPCTSTR)ComboBoxItemSkill));
		if ((Err = GetLastError()) != 0) { swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		count++;
	}

	count = 0;

	while (count < ASkillCount)
	{
		size_t size = strlen(ASkillID[count].Name.c_str()) + 1;
		wchar_t *ComboBoxItemSkillTemp = new wchar_t[size];

		size_t outSize;
		mbstowcs_s(&outSize, ComboBoxItemSkillTemp, size, ASkillID[count].Name.c_str(), size - 1);
		const TCHAR *ComboBoxItemSkill = { ComboBoxItemSkillTemp };
		hTemp = GetDlgItem(hwndDisplay[1], IDC_COMBO14);
		if (!hTemp) { Err = GetLastError(); swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		Err = SendMessage(hTemp, CB_ADDSTRING, 0, reinterpret_cast <LPARAM> ((LPCTSTR)ComboBoxItemSkill));
		if ((Err = GetLastError()) != 0) { swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		count++;
	}

	count = 0;

	while (count < ESkillCount)
	{
		size_t size = strlen(ESkillID[count].Name.c_str()) + 1;
		wchar_t *ComboBoxItemSkillTemp = new wchar_t[size];

		size_t outSize;
		mbstowcs_s(&outSize, ComboBoxItemSkillTemp, size, ESkillID[count].Name.c_str(), size - 1);
		const TCHAR *ComboBoxItemSkill = { ComboBoxItemSkillTemp };
		hTemp = GetDlgItem(hwndDisplay[1], IDC_COMBO15);
		if (!hTemp) { Err = GetLastError(); swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		Err = SendMessage(hTemp, CB_ADDSTRING, 0, reinterpret_cast <LPARAM> ((LPCTSTR)ComboBoxItemSkill));
		if ((Err = GetLastError()) != 0) { swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		count++;
	}

	count = 0;
	TCHAR *Ki_Blast[] = {L"Rush", L"Power", L"Paralyze", L"Bomb", L"Homing"};
	while (count < 5)
	{
		hTemp = GetDlgItem(hwndDisplay[2], IDC_COMBO2);
		Err = SendMessage(hTemp, CB_ADDSTRING, 0, reinterpret_cast <LPARAM> ((LPCTSTR)Ki_Blast[count]));
		if ((Err = GetLastError()) != 0) { swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		count++;
	}
	count = 0;

	hTemp = GetDlgItem(hwndDisplay[2], IDC_COMBO3);

	while (count < SSEffectCount)
	{
		std::cout << SSEffectID[count].EffectName << "\n";
		size_t size = strlen(SSEffectID[count].EffectName.c_str()) + 1;
		wchar_t *ComboBoxItemEffectTemp = new wchar_t[size];

		size_t outSize;
		mbstowcs_s(&outSize, ComboBoxItemEffectTemp, size, SSEffectID[count].EffectName.c_str(), size - 1);
		const TCHAR *ComboBoxItemEffect = { ComboBoxItemEffectTemp };
		if (!hTemp) { Err = GetLastError(); swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		SendMessage(hTemp, CB_ADDSTRING, 0, reinterpret_cast <LPARAM> ((LPCTSTR)ComboBoxItemEffect));
		if ((Err = GetLastError()) != 0) { swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		count++;
	}
	count = 0;
	
	while (count < SSEffectAmountCount)
	{
		size_t size = strlen(SSEAID[count].Amount.c_str()) + 1;
		wchar_t *ComboBoxItemEffectAmountTemp = new wchar_t[size];

		size_t outSize;
		mbstowcs_s(&outSize, ComboBoxItemEffectAmountTemp, size, SSEAID[count].Amount.c_str(), size - 1);
		const TCHAR *ComboBoxItemEffectAmount = { ComboBoxItemEffectAmountTemp };

		hTemp = GetDlgItem(hwndDisplay[2], IDC_COMBO4);
		if (!hTemp) { Err = GetLastError(); swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		SendMessage(hTemp, CB_ADDSTRING, 0, reinterpret_cast <LPARAM> ((LPCTSTR)ComboBoxItemEffectAmount));
		if ((Err = GetLastError()) != 0) { swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		hTemp = GetDlgItem(hwndDisplay[2], IDC_COMBO11);
		if (!hTemp) { Err = GetLastError(); swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		SendMessage(hTemp, CB_ADDSTRING, 0, reinterpret_cast <LPARAM> ((LPCTSTR)ComboBoxItemEffectAmount));
		if ((Err = GetLastError()) != 0) { swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		hTemp = GetDlgItem(hwndDisplay[2], IDC_COMBO12);
		if (!hTemp) { Err = GetLastError(); swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		SendMessage(hTemp, CB_ADDSTRING, 0, reinterpret_cast <LPARAM> ((LPCTSTR)ComboBoxItemEffectAmount));
		if ((Err = GetLastError()) != 0) { swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		hTemp = GetDlgItem(hwndDisplay[2], IDC_COMBO13);
		if (!hTemp) { Err = GetLastError(); swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		SendMessage(hTemp, CB_ADDSTRING, 0, reinterpret_cast <LPARAM> ((LPCTSTR)ComboBoxItemEffectAmount));
		if ((Err = GetLastError()) != 0) { swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		hTemp = GetDlgItem(hwndDisplay[2], IDC_COMBO14);
		if (!hTemp) { Err = GetLastError(); swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		SendMessage(hTemp, CB_ADDSTRING, 0, reinterpret_cast <LPARAM> ((LPCTSTR)ComboBoxItemEffectAmount));
		if ((Err = GetLastError()) != 0) { swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		hTemp = GetDlgItem(hwndDisplay[2], IDC_COMBO15);
		if (!hTemp) { Err = GetLastError(); swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		SendMessage(hTemp, CB_ADDSTRING, 0, reinterpret_cast <LPARAM> ((LPCTSTR)ComboBoxItemEffectAmount));
		if ((Err = GetLastError()) != 0) { swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		hTemp = GetDlgItem(hwndDisplay[2], IDC_COMBO16);
		if (!hTemp) { Err = GetLastError(); swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		SendMessage(hTemp, CB_ADDSTRING, 0, reinterpret_cast <LPARAM> ((LPCTSTR)ComboBoxItemEffectAmount));
		if ((Err = GetLastError()) != 0) { swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		hTemp = GetDlgItem(hwndDisplay[2], IDC_COMBO17);
		if (!hTemp) { Err = GetLastError(); swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		SendMessage(hTemp, CB_ADDSTRING, 0, reinterpret_cast <LPARAM> ((LPCTSTR)ComboBoxItemEffectAmount));
		if ((Err = GetLastError()) != 0) { swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		hTemp = GetDlgItem(hwndDisplay[2], IDC_COMBO18);
		if (!hTemp) { Err = GetLastError(); swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		SendMessage(hTemp, CB_ADDSTRING, 0, reinterpret_cast <LPARAM> ((LPCTSTR)ComboBoxItemEffectAmount));
		if ((Err = GetLastError()) != 0) { swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		hTemp = GetDlgItem(hwndDisplay[2], IDC_COMBO19);
		if (!hTemp) { Err = GetLastError(); swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		SendMessage(hTemp, CB_ADDSTRING, 0, reinterpret_cast <LPARAM> ((LPCTSTR)ComboBoxItemEffectAmount));
		if ((Err = GetLastError()) != 0) { swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		hTemp = GetDlgItem(hwndDisplay[2], IDC_COMBO20);
		if (!hTemp) { Err = GetLastError(); swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		SendMessage(hTemp, CB_ADDSTRING, 0, reinterpret_cast <LPARAM> ((LPCTSTR)ComboBoxItemEffectAmount));
		if ((Err = GetLastError()) != 0) { swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		hTemp = GetDlgItem(hwndDisplay[2], IDC_COMBO21);
		if (!hTemp) { Err = GetLastError(); swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		SendMessage(hTemp, CB_ADDSTRING, 0, reinterpret_cast <LPARAM> ((LPCTSTR)ComboBoxItemEffectAmount));
		if ((Err = GetLastError()) != 0) { swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		hTemp = GetDlgItem(hwndDisplay[2], IDC_COMBO22);
		if (!hTemp) { Err = GetLastError(); swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		SendMessage(hTemp, CB_ADDSTRING, 0, reinterpret_cast <LPARAM> ((LPCTSTR)ComboBoxItemEffectAmount));
		if ((Err = GetLastError()) != 0) { swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		hTemp = GetDlgItem(hwndDisplay[2], IDC_COMBO23);
		if (!hTemp) { Err = GetLastError(); swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		SendMessage(hTemp, CB_ADDSTRING, 0, reinterpret_cast <LPARAM> ((LPCTSTR)ComboBoxItemEffectAmount));
		if ((Err = GetLastError()) != 0) { swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		hTemp = GetDlgItem(hwndDisplay[2], IDC_COMBO24);
		if (!hTemp) { Err = GetLastError(); swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		SendMessage(hTemp, CB_ADDSTRING, 0, reinterpret_cast <LPARAM> ((LPCTSTR)ComboBoxItemEffectAmount));
		if ((Err = GetLastError()) != 0) { swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		hTemp = GetDlgItem(hwndDisplay[2], IDC_COMBO25);
		if (!hTemp) { Err = GetLastError(); swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		SendMessage(hTemp, CB_ADDSTRING, 0, reinterpret_cast <LPARAM> ((LPCTSTR)ComboBoxItemEffectAmount));
		if ((Err = GetLastError()) != 0) { swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		hTemp = GetDlgItem(hwndDisplay[2], IDC_COMBO26);
		if (!hTemp) { Err = GetLastError(); swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		SendMessage(hTemp, CB_ADDSTRING, 0, reinterpret_cast <LPARAM> ((LPCTSTR)ComboBoxItemEffectAmount));
		if ((Err = GetLastError()) != 0) { swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		hTemp = GetDlgItem(hwndDisplay[2], IDC_COMBO27);
		if (!hTemp) { Err = GetLastError(); swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		SendMessage(hTemp, CB_ADDSTRING, 0, reinterpret_cast <LPARAM> ((LPCTSTR)ComboBoxItemEffectAmount));
		if ((Err = GetLastError()) != 0) { swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		hTemp = GetDlgItem(hwndDisplay[2], IDC_COMBO28);
		if (!hTemp) { Err = GetLastError(); swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		SendMessage(hTemp, CB_ADDSTRING, 0, reinterpret_cast <LPARAM> ((LPCTSTR)ComboBoxItemEffectAmount));
		if ((Err = GetLastError()) != 0) { swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		count++;
	}
	count = 0;
	hTemp = GetDlgItem(hwndDisplay[2], IDC_COMBO5);
	TCHAR* ComboBoxItemFlag[] = { L"None", L"Once", L"Stack 10 Times", L"None",L"Not Found" };

	while (count < 5)
	{
		if (!hTemp) { Err = GetLastError(); swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		SendMessage(hTemp, CB_ADDSTRING, 0, reinterpret_cast <LPARAM> ((LPCTSTR)ComboBoxItemFlag[count]));
		if ((Err = GetLastError()) != 0) { swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		count++;
	}
	count = 0;
	hTemp = GetDlgItem(hwndDisplay[2], IDC_COMBO6);
	while (count < SSTriggerCount)
	{
		std::cout << SSTriggerID[count].Trigger << "\n";
		size_t size = strlen(SSTriggerID[count].Trigger.c_str()) + 1;
		wchar_t *ComboBoxItemTriggerTemp = new wchar_t[size];

		size_t outSize;
		mbstowcs_s(&outSize, ComboBoxItemTriggerTemp, size, SSTriggerID[count].Trigger.c_str(), size - 1);
		const TCHAR *ComboBoxItemTrigger = { ComboBoxItemTriggerTemp };
		if (!hTemp) { Err = GetLastError(); swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		SendMessage(hTemp, CB_ADDSTRING, 0, reinterpret_cast <LPARAM> ((LPCTSTR)ComboBoxItemTrigger));
		if ((Err = GetLastError()) != 0) { swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		count++;
	}
	count = 0;

	while (count < SSTCCount)
	{
		std::cout << SSTCID[count].TCName << "\n";
		size_t size = strlen(SSTCID[count].TCName.c_str()) + 1;
		wchar_t *ComboBoxItemTCTemp = new wchar_t[size];

		size_t outSize;
		mbstowcs_s(&outSize, ComboBoxItemTCTemp, size, SSTCID[count].TCName.c_str(), size - 1);
		const TCHAR *ComboBoxItemTC = { ComboBoxItemTCTemp };
		hTemp = GetDlgItem(hwndDisplay[2], IDC_COMBO8);
		if (!hTemp) { Err = GetLastError(); swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		SendMessage(hTemp, CB_ADDSTRING, 0, reinterpret_cast <LPARAM> ((LPCTSTR)ComboBoxItemTC));
		if ((Err = GetLastError()) != 0) { swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		hTemp = GetDlgItem(hwndDisplay[2], IDC_COMBO9);
		if (!hTemp) { Err = GetLastError(); swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		SendMessage(hTemp, CB_ADDSTRING, 0, reinterpret_cast <LPARAM> ((LPCTSTR)ComboBoxItemTC));
		if ((Err = GetLastError()) != 0) { swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		hTemp = GetDlgItem(hwndDisplay[2], IDC_COMBO10);
		if (!hTemp) { Err = GetLastError(); swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		SendMessage(hTemp, CB_ADDSTRING, 0, reinterpret_cast <LPARAM> ((LPCTSTR)ComboBoxItemTC));
		if ((Err = GetLastError()) != 0) { swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		count++;
	}
	count = 0;
	hTemp = GetDlgItem(hwndDisplay[2], IDC_COMBO7);
	TCHAR* ComboBoxItemTarget[] = { L"Self", L"Allies", L"Enemies", L"Not Found" };

	while (count < 4)
	{
		if (!hTemp) { Err = GetLastError(); swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		SendMessage(hTemp, CB_ADDSTRING, 0, reinterpret_cast <LPARAM> ((LPCTSTR)ComboBoxItemTarget[count]));
		if ((Err = GetLastError()) != 0) { swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		count++;
	}
	count = 0;
	hTemp = GetDlgItem(hwndDisplay[2], IDC_COMBO29);
	TCHAR* ComboBoxItemTimer[] = { L"0s", L"15s", L"30s", L"60s", L"None", L"Not Found" };

	while (count < 5)
	{
		if (!hTemp) { Err = GetLastError(); swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		SendMessage(hTemp, CB_ADDSTRING, 0, reinterpret_cast <LPARAM> ((LPCTSTR)ComboBoxItemTimer[count]));
		if ((Err = GetLastError()) != 0) { swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		count++;
	}

	ShowWindow(hwndTab, SW_SHOWNORMAL);
	ShowWindow(hwndDisplay[0], SW_SHOWNORMAL);
	UpdateWindow(hwndDisplay[0]);
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);
	
	MSG msg;
	
	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
		if (!IsDialogMessage(hwndDisplay[ActiveTab], &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	case WM_COMMAND:
		/*switch (wParam)
		{

		}*/
	case WM_CREATE:
	{
		
		break;
	}
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_NOTIFY:
		OnNotify(hwndTab, hwndDisplay, lParam, g_hInst);
		break;
	case WM_PAINT:
		break;
	case WM_SIZE:

		break;
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}

INT_PTR CALLBACK MainDialogProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	
	switch (message)
	{
	case WM_INITDIALOG:
	{
			int count = 0;
			DWORD Err = NULL;
			WCHAR WERR[100] = L"";
			HWND hTemp;
			TC_ITEMHEADER tabInfo;
			TCHAR* TabLabel2[] = { L"Intial Effect", L"Effect 1", L"Effect 2" };
			hTemp = GetDlgItem(hwndDisplay[2], IDC_TAB1);
			//TabCtrl_DeleteAllItems(hTemp);
			while (count < 3) //set super soul tab effects tabs name
			{
				//mbtowc(WTemp, Temp, strlen(Temp));// +1 is to include null character
				tabInfo.mask = TCIF_TEXT;
				tabInfo.iImage = -1;
				tabInfo.pszText = TabLabel2[count];
				SendMessage(hTemp, TCM_INSERTITEM, count, (LPARAM)&tabInfo);
				count++;
			}
	}
	break;
	case WM_COMMAND:
		switch (LOWORD(wParam)) 
		{
		case IDB_SET_AURA_COLOR:
		{
			LRESULT Name, Aura;
			HWND hAuraName = GetDlgItem(hwndDisplay[0], IDC_COMBO1);
			HWND hAuraColor = GetDlgItem(hwndDisplay[0], IDC_COMBO2);
			Name = SendMessage(hAuraName, CB_GETCURSEL, 0, 0);
			Aura = SendMessage(hAuraColor, CB_GETCURSEL, 0, 0);
			ChangeAuraColor(Name, Aura, GetDlgItem(hDlg, IDC_EDITERROR1));
			break;
		}
			break;
		case IDB_SET_CHAR_AURA_COLOR:
		{
			LRESULT Name = NULL, Costume, Color, InfiniteCheck;
			HWND hTemp = GetDlgItem(hDlg, IDC_COMBO3);
			Name = SendMessage(hTemp, CB_GETCURSEL, 0, 0);
			hTemp = GetDlgItem(hDlg, IDC_COMBO4);
			Costume = SendMessage(hTemp, CB_GETCURSEL, 0, 0);
			hTemp = GetDlgItem(hDlg, IDC_COMBO5);
			Color = SendMessage(hTemp, CB_GETCURSEL, 0, 0);
			hTemp = GetDlgItem(hDlg, IDC_CHECK1);
			InfiniteCheck = SendMessage(hTemp, BM_GETCHECK, 0, 0);
			ChangeCharAura(Name, Costume, Color, InfiniteCheck, GetDlgItem(hDlg, IDC_EDITERROR1));
			break;
		}
		case ID_FILE_OPEN_AURA:
		{
			COMDLG_FILTERSPEC Filter[] = { { L"aur file", L"*.aur" } };
			getFileName(hwnd, AuraFile, Filter, 1);
			openFile(AuraFile, AuraData);
			break;
		}
		case ID_FILE_SAVE_AURA:
			if (saveFile(AuraFile, AuraData) == 0)
			{
				HWND EditError = GetDlgItem(hDlg, IDC_EDITERROR1);
				SetWindowText(EditError, L"Save Succcesful");
				SetFocus(EditError);
			}
			else
			{
				HWND EditError = GetDlgItem(hDlg, IDC_EDITERROR1);
				SetWindowText(EditError, L"Error Failed to Save");
				SetFocus(EditError);
			}
			break;
		case IDC_BUTTON2:
		{
			LRESULT Name, Costume;
			HWND hTemp = GetDlgItem(hDlg, IDC_COMBO3);
			Name = SendMessage(hTemp, CB_GETCURSEL, 0, 0);
			hTemp = GetDlgItem(hDlg, IDC_COMBO4);
			Costume = SendMessage(hTemp, CB_GETCURSEL, 0, 0);
			hTemp = GetDlgItem(hDlg, IDC_COMBO5);
			SendMessage(hTemp, CB_SETCURSEL, GetAura(Name, Costume, GetDlgItem(hDlg, IDC_EDITERROR1)), 0);
		}
			break;
		case IDC_BUTTON3:
		{
			COMDLG_FILTERSPEC Filter[] = { { L"cus file", L"*.cus" } };
			getFileName(hwnd, CusFile, Filter, 1);
			openFile(CusFile, CusData);
			break;
		}
		case IDC_BUTTON4:
			if (saveFile(CusFile, CusData) == 0)
			{
				HWND EditError = GetDlgItem(hDlg, IDC_EDITERROR2);
				SetWindowText(EditError, L"Save Succcesful");
				SetFocus(EditError);
			}
			else
			{
				HWND EditError = GetDlgItem(hDlg, IDC_EDITERROR2);
				SetWindowText(EditError, L"Error Failed to Save");
				SetFocus(EditError);
			}
			break;
		case IDC_BUTTON5:
	
			break;
		case IDC_BUTTON6:
		{
			LRESULT Name, Costume, SuperSkill[4], UltimateSkill[2], AwokenSkill, EvasiveSkill;
			HWND hTemp;
			hTemp = GetDlgItem(hDlg, IDC_COMBO6);
			Name = SendMessage(hTemp, CB_GETCURSEL, 0, 0);
			hTemp = GetDlgItem(hDlg, IDC_COMBO7);
			Costume = SendMessage(hTemp, CB_GETCURSEL, 0, 0);
			hTemp = GetDlgItem(hDlg, IDC_COMBO8);
			SuperSkill[1] = SendMessage(hTemp, CB_GETCURSEL, 0, 0);
			hTemp = GetDlgItem(hDlg, IDC_COMBO9);
			SuperSkill[0] = SendMessage(hTemp, CB_GETCURSEL, 0, 0);
			hTemp = GetDlgItem(hDlg, IDC_COMBO10);
			SuperSkill[2] = SendMessage(hTemp, CB_GETCURSEL, 0, 0);
			hTemp = GetDlgItem(hDlg, IDC_COMBO11);
			SuperSkill[3] = SendMessage(hTemp, CB_GETCURSEL, 0, 0);
			hTemp = GetDlgItem(hDlg, IDC_COMBO12);
			UltimateSkill[0] = SendMessage(hTemp, CB_GETCURSEL, 0, 0);
			hTemp = GetDlgItem(hDlg, IDC_COMBO13);
			UltimateSkill[1] = SendMessage(hTemp, CB_GETCURSEL, 0, 0);
			hTemp = GetDlgItem(hDlg, IDC_COMBO14);
			AwokenSkill = SendMessage(hTemp, CB_GETCURSEL, 0, 0);
			hTemp = GetDlgItem(hDlg, IDC_COMBO15);
			EvasiveSkill = SendMessage(hTemp, CB_GETCURSEL, 0, 0);
			ChangeSkill( Name, Costume, SuperSkill, UltimateSkill, AwokenSkill, EvasiveSkill, GetDlgItem(hDlg, IDC_EDITERROR2));
			break;
		}
		case IDC_BUTTON7:
		{
			LRESULT Name, Costume, SuperSkill[4] = { 0 }, UltimateSkill[2] = { 0 }, AwokenSkill = 0, EvasiveSkill = 0;
			HWND hTemp;
			hTemp = GetDlgItem(hDlg, IDC_COMBO6);
			Name = SendMessage(hTemp, CB_GETCURSEL, 0, 0);
			hTemp = GetDlgItem(hDlg, IDC_COMBO7);
			Costume = SendMessage(hTemp, CB_GETCURSEL, 0, 0);
			GetSkill(Name, Costume, SuperSkill, UltimateSkill, AwokenSkill, EvasiveSkill, GetDlgItem(hDlg, IDC_EDITERROR2));
			hTemp = GetDlgItem(hDlg, IDC_COMBO8);
			SendMessage(hTemp, CB_SETCURSEL, 0, 0);
			SendMessage(hTemp, CB_SETCURSEL, SuperSkill[1], 0);
			hTemp = GetDlgItem(hDlg, IDC_COMBO9);
			SendMessage(hTemp, CB_SETCURSEL, 0, 0);
			 SendMessage(hTemp, CB_SETCURSEL, SuperSkill[0], 0);
			hTemp = GetDlgItem(hDlg, IDC_COMBO10);
			SendMessage(hTemp, CB_SETCURSEL, 0, 0);
			SendMessage(hTemp, CB_SETCURSEL, SuperSkill[2], 0);
			hTemp = GetDlgItem(hDlg, IDC_COMBO11);
			SendMessage(hTemp, CB_SETCURSEL, 0, 0);
			SendMessage(hTemp, CB_SETCURSEL, SuperSkill[3], 0);
			hTemp = GetDlgItem(hDlg, IDC_COMBO12);
			SendMessage(hTemp, CB_SETCURSEL, 0, 0);
			SendMessage(hTemp, CB_SETCURSEL, UltimateSkill[1], 0);
			hTemp = GetDlgItem(hDlg, IDC_COMBO13);
			SendMessage(hTemp, CB_SETCURSEL, 0, 0);
			SendMessage(hTemp, CB_SETCURSEL, UltimateSkill[0], 0);
			hTemp = GetDlgItem(hDlg, IDC_COMBO14);
			SendMessage(hTemp, CB_SETCURSEL, 0, 0);
			SendMessage(hTemp, CB_SETCURSEL, AwokenSkill, 0);
			hTemp = GetDlgItem(hDlg, IDC_COMBO15);
			SendMessage(hTemp, CB_SETCURSEL, 0, 0);
			SendMessage(hTemp, CB_SETCURSEL, EvasiveSkill, 0);
		}
			break;
		case IDC_OPENNAMEMSG:
		{
			COMDLG_FILTERSPEC Filter[] = { { L"Xenoverse MSG file", L"*.msg" } };
			HWND hTemp;
			DWORD Err = NULL;
			WCHAR WERR[100] = L"";
			int count = 0;
			getFileName(hwnd, NameMsgFile, Filter, 1);
			openFile(NameMsgFile, NameMSGData);
			if (NameMSGData.empty()) break;
			LoadMSG(NameMSGData, NameMSGID, 0);
			hTemp = GetDlgItem(hwndDisplay[2], IDC_COMBO1);
			if (!hTemp) { Err = GetLastError(); swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
			SendMessage(hTemp, CB_RESETCONTENT, 0, 0);

			while (count < MSGCount)
			{
				size_t size = strlen(NameMSGID[count].NameID.c_str()) + 1;
				wchar_t *ComboBoxItemMSGTemp = new wchar_t[size];

				size_t outSize;
				mbstowcs_s(&outSize, ComboBoxItemMSGTemp, size, NameMSGID[count].NameID.c_str(), size - 1);
				const TCHAR *ComboBoxItemMSG = { ComboBoxItemMSGTemp };
				hTemp = GetDlgItem(hwndDisplay[2], IDC_COMBO1);
				if (!hTemp) { Err = GetLastError(); swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
				SendMessage(hTemp, CB_ADDSTRING, 0, reinterpret_cast <LPARAM> ((LPCTSTR)ComboBoxItemMSG));
				if ((Err = GetLastError()) != 0) { swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
				count++;
			}
		}
			break;

		case IDC_OPENDESCMSG:
		{
			COMDLG_FILTERSPEC Filter[] = { { L"Xenoverse MSG file", L"*.msg" } };
			DWORD Err = NULL;
			WCHAR WERR[100] = L"";
			int count = 0;
			getFileName(hwnd, DescMsgFile, Filter, 1);
			openFile(DescMsgFile, DescMSGData);
			if (DescMSGData.empty()) break;
			LoadMSG(DescMSGData, DescMSGID, 1);
		}
			break;
		case IDC_OPENIDB:
		{
			COMDLG_FILTERSPEC Filter[] = { { L"Tailsman idb file", L"*.idb" } };
			DWORD Err = NULL;
			WCHAR WERR[100] = L"";
			int count = 0;
			getFileName(hwnd, SSIDBFile, Filter, 1);
			openFile(SSIDBFile, SSIDBData);
		}
		break;
		case IDC_SAVESOUL:
		{
			if (saveFile(NameMsgFile, NameMSGData) == 0)
			{
				HWND EditError = GetDlgItem(hDlg, IDC_EDITERROR1);
				SetWindowText(EditError, L"Name Msg Save Succcesful");
				SetFocus(EditError);
			}
			else
			{
				HWND EditError = GetDlgItem(hDlg, IDC_EDITERROR1);
				SetWindowText(EditError, L"Error Failed to Save Name Msg");
				SetFocus(EditError);
			}
			if (saveFile(DescMsgFile, DescMSGData) == 0)
			{
				HWND EditError = GetDlgItem(hDlg, IDC_EDITERROR1);
				SetWindowText(EditError, L"Description Msg Save Succcesful");
				SetFocus(EditError);
			}
			else
			{
				HWND EditError = GetDlgItem(hDlg, IDC_EDITERROR1);
				SetWindowText(EditError, L"Error Failed to Save Description Msg");
				SetFocus(EditError);
			}
			if (saveFile(SSIDBFile, SSIDBData) == 0)
			{
				HWND EditError = GetDlgItem(hDlg, IDC_EDITERROR1);
				SetWindowText(EditError, L"IDB Save Succcesful");
				SetFocus(EditError);
			}
			else
			{
				HWND EditError = GetDlgItem(hDlg, IDC_EDITERROR1);
				SetWindowText(EditError, L"Error Failed to Save IDB");
				SetFocus(EditError);
			}
		}
			break;
		case IDC_SETSOUL:
		{
			int index, count = 0, size;
			HWND hTemp;
		    char CTemp[200];
			std::string NTemp, OTemp;
			hTemp = GetDlgItem(hDlg, IDC_EDIT1);
			GetWindowTextA(hTemp, CTemp, GetWindowTextLength(hTemp) + 1);
			NTemp = CTemp;
			hTemp = GetDlgItem(hDlg, IDC_COMBO1);
			index = SendMessage(hTemp, CB_GETCURSEL, 0, 0);
			if (index == -1) break;
			OTemp = NameMSGID[index].Info;
			NormalizeMSG(NTemp);
			NormalizeMSG(OTemp);
			size = OTemp.size();
			count = NameMSGData.find(OTemp);
			NameMSGData.erase(count, size);
			NameMSGData.insert(count, NTemp);
			LoadMSG(NameMSGData, NameMSGID, 0);
			hTemp = GetDlgItem(hDlg, IDC_EDIT2);
			GetWindowTextA(hTemp, CTemp, GetWindowTextLength(hTemp) + 1);
			NTemp.clear();
			OTemp.clear();
			NTemp = CTemp;
			OTemp = DescMSGID[index].Info;
			NormalizeMSG(NTemp);
			NormalizeMSG(OTemp);
			size = OTemp.size();
			count = DescMSGData.find(OTemp);
			if (count == -1) { SetWindowText(GetDlgItem(hDlg, IDC_EDITERROR1), L"Error Desc saving String"); break; }
			DescMSGData.erase(count, size);
			DescMSGData.insert(count, NTemp);
			LoadMSG(DescMSGData, DescMSGID, 1);
			hTemp = GetDlgItem(hwndDisplay[2], IDC_EDIT4);
			index = SendMessage(hTemp, CB_GETCURSEL, 0, 0);
			GetWindowTextA(hTemp, CTemp, 2);
			SSIDBData[SSData.Rarity] = CTemp[0] - '0';
			hTemp = GetDlgItem(hwndDisplay[2], IDC_COMBO2);
			SSIDBData[SSData.Ki_BlastType] = SendMessage(hTemp, CB_GETCURSEL, 0, 0);
			hTemp = GetDlgItem(hwndDisplay[2], IDC_COMBO3);
			index = SendMessage(hTemp, CB_GETCURSEL, 0, 0);
			count = 0;
			while (count < 3)
			{
				hTemp = GetDlgItem(hwndDisplay[2], IDC_COMBO3);
				index = SendMessage(hTemp, CB_GETCURSEL, 0, 0);
				SSIDBData[SSData.Effect[count]] = SSEffectID[index].HexID;
				hTemp = GetDlgItem(hwndDisplay[2], IDC_COMBO4);
				index = SendMessage(hTemp, CB_GETCURSEL, 0, 0);
				SSIDBData[SSData.EffectAmount[count]] = SSEAID[index].HexID1;
				SSIDBData[SSData.EffectAmount[count] + 1] = SSEAID[index].HexID2;
				SSIDBData[SSData.EffectAmount[count] + 2] = SSEAID[index].HexID3;
				SSIDBData[SSData.EffectAmount[count] + 3] = SSEAID[index].HexID4;
				hTemp = GetDlgItem(hwndDisplay[2], IDC_COMBO5);
				index = SendMessage(hTemp, CB_GETCURSEL, 0, 0);
				SSIDBData[SSData.Flag[count]] = SSSetting.Flag[index];
				if (index == 0)
				{
					SSIDBData[SSData.Flag[count] + 1] = 0xff;
					SSIDBData[SSData.Flag[count] + 2] = 0xff;
					SSIDBData[SSData.Flag[count] + 3] = 0xff;
				}
				else
				{
					SSIDBData[SSData.Flag[count] + 1] = 0xff;
					SSIDBData[SSData.Flag[count] + 2] = 0xff;
					SSIDBData[SSData.Flag[count] + 3] = 0xff;
				}
				hTemp = GetDlgItem(hwndDisplay[2], IDC_COMBO6);
				index = SendMessage(hTemp, CB_GETCURSEL, 0, 0);
				SSIDBData[SSData.Trigger[count]] = SSTriggerID[index].HexID;
				hTemp = GetDlgItem(hwndDisplay[2], IDC_COMBO7);
				index = SendMessage(hTemp, CB_GETCURSEL, 0, 0);
				SSIDBData[SSData.Target[count]] = SSSetting.Target[index];
				hTemp = GetDlgItem(hwndDisplay[2], IDC_COMBO8);
				index = SendMessage(hTemp, CB_GETCURSEL, 0, 0);
				SSIDBData[SSData.TriggerConditions1[count] + 2] = SSTCID[index].HexID1;
				SSIDBData[SSData.TriggerConditions1[count] + 3] = SSTCID[index].HexID2;
				hTemp = GetDlgItem(hwndDisplay[2], IDC_COMBO9);
				index = SendMessage(hTemp, CB_GETCURSEL, 0, 0);
				SSIDBData[SSData.TriggerConditions2[count] + 2] = SSTCID[index].HexID1;
				SSIDBData[SSData.TriggerConditions2[count] + 3] = SSTCID[index].HexID2;
				hTemp = GetDlgItem(hwndDisplay[2], IDC_COMBO10);
				index = SendMessage(hTemp, CB_GETCURSEL, 0, 0);
				SSIDBData[SSData.TriggerConditions3[count] + 2] = SSTCID[index].HexID1;
				SSIDBData[SSData.TriggerConditions3[count] + 3] = SSTCID[index].HexID2;
				hTemp = GetDlgItem(hwndDisplay[2], IDC_COMBO29);
				index = SendMessage(hTemp, CB_GETCURSEL, 0, 0);
				SSIDBData[SSData.Timer[count] + 2] = SSSetting.TimerID1[index];
				SSIDBData[SSData.Timer[count] + 3] = SSSetting.TimerID2[index];
				hTemp = GetDlgItem(hwndDisplay[2], IDC_COMBO11);
				index = SendMessage(hTemp, CB_GETCURSEL, 0, 0);
				SSIDBData[SSData.Health[count]] = SSEAID[index].HexID1;
				SSIDBData[SSData.Health[count] + 1] = SSEAID[index].HexID2;
				SSIDBData[SSData.Health[count] + 2] = SSEAID[index].HexID3;
				SSIDBData[SSData.Health[count] + 3] = SSEAID[index].HexID4;
				hTemp = GetDlgItem(hwndDisplay[2], IDC_COMBO12);
				index = SendMessage(hTemp, CB_GETCURSEL, 0, 0);
				SSIDBData[SSData.Ki[count]] = SSEAID[index].HexID1;
				SSIDBData[SSData.Ki[count] + 1] = SSEAID[index].HexID2;
				SSIDBData[SSData.Ki[count] + 2] = SSEAID[index].HexID3;
				SSIDBData[SSData.Ki[count] + 3] = SSEAID[index].HexID4;
				hTemp = GetDlgItem(hwndDisplay[2], IDC_COMBO13);
				index = SendMessage(hTemp, CB_GETCURSEL, 0, 0);
				SSIDBData[SSData.Ki_RegenRate[count]] = SSEAID[index].HexID1;
				SSIDBData[SSData.Ki_RegenRate[count] + 1] = SSEAID[index].HexID2;
				SSIDBData[SSData.Ki_RegenRate[count] + 2] = SSEAID[index].HexID3;
				SSIDBData[SSData.Ki_RegenRate[count] + 3] = SSEAID[index].HexID4;
				hTemp = GetDlgItem(hwndDisplay[2], IDC_COMBO14);
				index = SendMessage(hTemp, CB_GETCURSEL, 0, 0);
				SSIDBData[SSData.Stamina[count]] = SSEAID[index].HexID1;
				SSIDBData[SSData.Stamina[count] + 1] = SSEAID[index].HexID2;
				SSIDBData[SSData.Stamina[count] + 2] = SSEAID[index].HexID3;
				SSIDBData[SSData.Stamina[count] + 3] = SSEAID[index].HexID4;
				hTemp = GetDlgItem(hwndDisplay[2], IDC_COMBO15);
				index = SendMessage(hTemp, CB_GETCURSEL, 0, 0);
				SSIDBData[SSData.Stamina_RegenRate[count]] = SSEAID[index].HexID1;
				SSIDBData[SSData.Stamina_RegenRate[count] + 1] = SSEAID[index].HexID2;
				SSIDBData[SSData.Stamina_RegenRate[count] + 2] = SSEAID[index].HexID3;
				SSIDBData[SSData.Stamina_RegenRate[count] + 3] = SSEAID[index].HexID4;
				hTemp = GetDlgItem(hwndDisplay[2], IDC_COMBO16);
				index = SendMessage(hTemp, CB_GETCURSEL, 0, 0);
				SSIDBData[SSData.Ground_Speed[count]] = SSEAID[index].HexID1;
				SSIDBData[SSData.Ground_Speed[count] + 1] = SSEAID[index].HexID2;
				SSIDBData[SSData.Ground_Speed[count] + 2] = SSEAID[index].HexID3;
				SSIDBData[SSData.Ground_Speed[count] + 3] = SSEAID[index].HexID4;
				hTemp = GetDlgItem(hwndDisplay[2], IDC_COMBO17);
				index = SendMessage(hTemp, CB_GETCURSEL, 0, 0);
				SSIDBData[SSData.Flight_Speed[count]] = SSEAID[index].HexID1;
				SSIDBData[SSData.Flight_Speed[count] + 1] = SSEAID[index].HexID2;
				SSIDBData[SSData.Flight_Speed[count] + 2] = SSEAID[index].HexID3;
				SSIDBData[SSData.Flight_Speed[count] + 3] = SSEAID[index].HexID4;
				hTemp = GetDlgItem(hwndDisplay[2], IDC_COMBO18);
				index = SendMessage(hTemp, CB_GETCURSEL, 0, 0);
				SSIDBData[SSData.Boost_Speed[count]] = SSEAID[index].HexID1;
				SSIDBData[SSData.Boost_Speed[count] + 1] = SSEAID[index].HexID2;
				SSIDBData[SSData.Boost_Speed[count] + 2] = SSEAID[index].HexID3;
				SSIDBData[SSData.Boost_Speed[count] + 3] = SSEAID[index].HexID4;
				hTemp = GetDlgItem(hwndDisplay[2], IDC_COMBO19);
				index = SendMessage(hTemp, CB_GETCURSEL, 0, 0);
				SSIDBData[SSData.Dash_Speed[count]] = SSEAID[index].HexID1;
				SSIDBData[SSData.Dash_Speed[count] + 1] = SSEAID[index].HexID2;
				SSIDBData[SSData.Dash_Speed[count] + 2] = SSEAID[index].HexID3;
				SSIDBData[SSData.Dash_Speed[count] + 3] = SSEAID[index].HexID4;
				hTemp = GetDlgItem(hwndDisplay[2], IDC_COMBO21);
				index = SendMessage(hTemp, CB_GETCURSEL, 0, 0);
				SSIDBData[SSData.Basic_Attack[count]] = SSEAID[index].HexID1;
				SSIDBData[SSData.Basic_Attack[count] + 1] = SSEAID[index].HexID2;
				SSIDBData[SSData.Basic_Attack[count] + 2] = SSEAID[index].HexID3;
				SSIDBData[SSData.Basic_Attack[count] + 3] = SSEAID[index].HexID4;
				hTemp = GetDlgItem(hwndDisplay[2], IDC_COMBO22);
				index = SendMessage(hTemp, CB_GETCURSEL, 0, 0);
				SSIDBData[SSData.Ki_Blast[count]] = SSEAID[index].HexID1;
				SSIDBData[SSData.Ki_Blast[count] + 1] = SSEAID[index].HexID2;
				SSIDBData[SSData.Ki_Blast[count] + 2] = SSEAID[index].HexID3;
				SSIDBData[SSData.Ki_Blast[count] + 3] = SSEAID[index].HexID4;
				hTemp = GetDlgItem(hwndDisplay[2], IDC_COMBO23);
				index = SendMessage(hTemp, CB_GETCURSEL, 0, 0);
				SSIDBData[SSData.Strike_Super[count]] = SSEAID[index].HexID1;
				SSIDBData[SSData.Strike_Super[count] + 1] = SSEAID[index].HexID2;
				SSIDBData[SSData.Strike_Super[count] + 2] = SSEAID[index].HexID3;
				SSIDBData[SSData.Strike_Super[count] + 3] = SSEAID[index].HexID4;
				hTemp = GetDlgItem(hwndDisplay[2], IDC_COMBO24);
				index = SendMessage(hTemp, CB_GETCURSEL, 0, 0);
				SSIDBData[SSData.Ki_Blast_Super[count]] = SSEAID[index].HexID1;
				SSIDBData[SSData.Ki_Blast_Super[count] + 1] = SSEAID[index].HexID2;
				SSIDBData[SSData.Ki_Blast_Super[count] + 2] = SSEAID[index].HexID3;
				SSIDBData[SSData.Ki_Blast_Super[count] + 3] = SSEAID[index].HexID4;
				hTemp = GetDlgItem(hwndDisplay[2], IDC_COMBO25);
				index = SendMessage(hTemp, CB_GETCURSEL, 0, 0);
				SSIDBData[SSData.Basic_Attack_Dmg[count]] = SSEAID[index].HexID1;
				SSIDBData[SSData.Basic_Attack_Dmg[count] + 1] = SSEAID[index].HexID2;
				SSIDBData[SSData.Basic_Attack_Dmg[count] + 2] = SSEAID[index].HexID3;
				SSIDBData[SSData.Basic_Attack_Dmg[count] + 3] = SSEAID[index].HexID4;
				hTemp = GetDlgItem(hwndDisplay[2], IDC_COMBO26);
				index = SendMessage(hTemp, CB_GETCURSEL, 0, 0);
				SSIDBData[SSData.Ki_Blast_Dmg[count]] = SSEAID[index].HexID1;
				SSIDBData[SSData.Ki_Blast_Dmg[count] + 1] = SSEAID[index].HexID2;
				SSIDBData[SSData.Ki_Blast_Dmg[count] + 2] = SSEAID[index].HexID3;
				SSIDBData[SSData.Ki_Blast_Dmg[count] + 3] = SSEAID[index].HexID4;
				hTemp = GetDlgItem(hwndDisplay[2], IDC_COMBO27);
				index = SendMessage(hTemp, CB_GETCURSEL, 0, 0);
				SSIDBData[SSData.Strike_Super_Dmg[count]] = SSEAID[index].HexID1;
				SSIDBData[SSData.Strike_Super_Dmg[count] + 1] = SSEAID[index].HexID2;
				SSIDBData[SSData.Strike_Super_Dmg[count] + 2] = SSEAID[index].HexID3;
				SSIDBData[SSData.Strike_Super_Dmg[count] + 3] = SSEAID[index].HexID4;
				hTemp = GetDlgItem(hwndDisplay[2], IDC_COMBO28);
				index = SendMessage(hTemp, CB_GETCURSEL, 0, 0);
				SSIDBData[SSData.Ki_Blast_Super_Dmg[count]] = SSEAID[index].HexID1;
				SSIDBData[SSData.Ki_Blast_Super_Dmg[count] + 1] = SSEAID[index].HexID2;
				SSIDBData[SSData.Ki_Blast_Super_Dmg[count] + 2] = SSEAID[index].HexID3;
				SSIDBData[SSData.Ki_Blast_Super_Dmg[count] + 3] = SSEAID[index].HexID4;
				hTemp = GetDlgItem(hwndDisplay[2], IDC_COMBO20);
				index = SendMessage(hTemp, CB_GETCURSEL, 0, 0);
				SSIDBData[SSData.Revive_Speed[count]] = SSEAID[index].HexID1;
				SSIDBData[SSData.Ki_Blast_Super_Dmg[count] + 1] = SSEAID[index].HexID2;
				SSIDBData[SSData.Ki_Blast_Super_Dmg[count] + 2] = SSEAID[index].HexID3;
				SSIDBData[SSData.Ki_Blast_Super_Dmg[count] + 3] = SSEAID[index].HexID4;


				count++;
				}
		}
		break;
		}
		switch (HIWORD(wParam))
		{
		case CBN_SELCHANGE:
		{
			if ((HWND)lParam == hComboCheck[0] || (HWND)lParam == hComboCheck[1])
			{
				int index, count = 0;
				DWORD Err = NULL;
				WCHAR WERR[100] = L"";
				HWND hTemp;
				if ((HWND)lParam == hComboCheck[0])
					hTemp = GetDlgItem(hDlg, IDC_COMBO4);
				else
					hTemp = GetDlgItem(hDlg, IDC_COMBO7);
				index = SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
				SendMessage(hTemp, CB_RESETCONTENT, 0, 0);
				while (TRUE)
				{
					std::cout << CharID[index].List[count].Name << "\n";
					if (CharID[index].List[count].Name[0] == '\0') break;
					size_t size = strlen(CharID[index].List[count].Name.c_str()) + 1;
					wchar_t *ComboBoxItemCostumeTemp = new wchar_t[size];

					size_t outSize;
					mbstowcs_s(&outSize, ComboBoxItemCostumeTemp, size, CharID[index].List[count].Name.c_str(), size - 1);
					const TCHAR *ComboBoxItemCostume = { ComboBoxItemCostumeTemp };
					if (!hTemp) { Err = GetLastError(); swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
					SendMessage(hTemp, CB_ADDSTRING, 0, reinterpret_cast <LPARAM> ((LPCTSTR)ComboBoxItemCostume));
					if ((Err = GetLastError()) != 0) { swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }			
					count++;
				}
			}
			if ((HWND)lParam == hComboCheck[2])
			{
				int index;
				DWORD Err = NULL;
				WCHAR WERR[100] = L"";
				HWND hTemp = GetDlgItem(hDlg, IDC_EDIT3);
				index = SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
				SetWindowText(hTemp, (LPWSTR)NameMSGID[index].ID);
				
				size_t size = strlen(NameMSGID[index].Info.c_str()) + 1;
				wchar_t *InfoTemp = new wchar_t[size];

				size_t outSize;
				mbstowcs_s(&outSize, InfoTemp, size, NameMSGID[index].Info.c_str(), size - 1);
				const TCHAR *Info = { InfoTemp };
				hTemp = GetDlgItem(hDlg, IDC_EDIT1);
				SetWindowText(hTemp, Info);
				hTemp = GetDlgItem(hDlg, IDC_EDIT2);
				if (!DescMSGData.empty())
				{
					size_t size = strlen(DescMSGID[index].Info.c_str()) + 1;
					wchar_t *InfoTemp = new wchar_t[size];

					size_t outSize;
					mbstowcs_s(&outSize, InfoTemp, size, DescMSGID[index].Info.c_str(), size - 1);
					const TCHAR *Info = { InfoTemp };
					SetWindowText(hTemp, Info);
				}
				else
				{
					SetWindowText(hTemp, L"Load Description MSG and reselect Name MSG ID");
				}

				if (!SSIDBData.empty())
				{
					memset(&SSData, 0, sizeof(SUPERSOUL));
					wchar_t Temp[10];
					SSData = SearchSS(index);
					int TabNum = TabCtrl_GetCurSel(GetDlgItem(hDlg, IDC_TAB1));
					hTemp = GetDlgItem(hDlg, IDC_EDIT3);
					wsprintfW(Temp, L"%x", SSIDBData[SSData.ID]);
					SetWindowText(hTemp, Temp);
					hTemp = GetDlgItem(hDlg, IDC_EDIT4);
					wsprintfW(Temp, L"%d", SSIDBData[SSData.Rarity ]);
					SetWindowText(hTemp, Temp);
					hTemp = GetDlgItem(hDlg, IDC_COMBO2);
					SendMessage(hTemp, CB_SETCURSEL, SSIDBData[SSData.Ki_BlastType], 0);
					hTemp = GetDlgItem(hDlg, IDC_COMBO3);
					SendMessage(hTemp, CB_SETCURSEL, SearchEffectID(SSData.Effect[TabNum]), 0);
					hTemp = GetDlgItem(hDlg, IDC_COMBO4);
					SendMessage(hTemp, CB_SETCURSEL, SearchEffectAmountID(SSData.EffectAmount[TabNum]), 0);
					hTemp = GetDlgItem(hDlg, IDC_COMBO5);
					SendMessage(hTemp, CB_SETCURSEL, SearchFlagID(SSData.Flag[TabNum]), 0);
					hTemp = GetDlgItem(hDlg, IDC_COMBO6);
					SendMessage(hTemp, CB_SETCURSEL, SearchTriggerID(SSData.Trigger[TabNum]), 0);
					hTemp = GetDlgItem(hDlg, IDC_COMBO7);
					SendMessage(hTemp, CB_SETCURSEL, SearchTargetID(SSData.Target[TabNum]), 0);
					hTemp = GetDlgItem(hDlg, IDC_COMBO8);
					SendMessage(hTemp, CB_SETCURSEL, SearchTCID(SSData.TriggerConditions1[TabNum]), 0);
					hTemp = GetDlgItem(hDlg, IDC_COMBO9);
					SendMessage(hTemp, CB_SETCURSEL, SearchTCID(SSData.TriggerConditions2[TabNum]), 0);
					hTemp = GetDlgItem(hDlg, IDC_COMBO10);
					SendMessage(hTemp, CB_SETCURSEL, SearchTCID(SSData.TriggerConditions3[TabNum]), 0);
					hTemp = GetDlgItem(hDlg, IDC_COMBO29);
					SendMessage(hTemp, CB_SETCURSEL, SearchTimerID(SSData.Timer[TabNum]), 0);
					hTemp = GetDlgItem(hDlg, IDC_COMBO11);
					SendMessage(hTemp, CB_SETCURSEL, SearchEffectAmountID(SSData.Health[TabNum]), 0);
					hTemp = GetDlgItem(hDlg, IDC_COMBO12);
					SendMessage(hTemp, CB_SETCURSEL, SearchEffectAmountID(SSData.Ki[TabNum]), 0);
					hTemp = GetDlgItem(hDlg, IDC_COMBO13);
					SendMessage(hTemp, CB_SETCURSEL, SearchEffectAmountID(SSData.Ki_RegenRate[TabNum]), 0);
					hTemp = GetDlgItem(hDlg, IDC_COMBO14);
					SendMessage(hTemp, CB_SETCURSEL, SearchEffectAmountID(SSData.Stamina[TabNum]), 0);
					hTemp = GetDlgItem(hDlg, IDC_COMBO15);
					SendMessage(hTemp, CB_SETCURSEL, SearchEffectAmountID(SSData.Stamina_RegenRate[TabNum]), 0);
					hTemp = GetDlgItem(hDlg, IDC_COMBO16);
					SendMessage(hTemp, CB_SETCURSEL, SearchEffectAmountID(SSData.Ground_Speed[TabNum]), 0);
					hTemp = GetDlgItem(hDlg, IDC_COMBO17);
					SendMessage(hTemp, CB_SETCURSEL, SearchEffectAmountID(SSData.Flight_Speed[TabNum]), 0);
					hTemp = GetDlgItem(hDlg, IDC_COMBO18);
					SendMessage(hTemp, CB_SETCURSEL, SearchEffectAmountID(SSData.Boost_Speed[TabNum]), 0);
					hTemp = GetDlgItem(hDlg, IDC_COMBO19);
					SendMessage(hTemp, CB_SETCURSEL, SearchEffectAmountID(SSData.Dash_Speed[TabNum]), 0);
					hTemp = GetDlgItem(hDlg, IDC_COMBO28);
					SendMessage(hTemp, CB_SETCURSEL, SearchEffectAmountID(SSData.Basic_Attack[TabNum]), 0);
					hTemp = GetDlgItem(hDlg, IDC_COMBO21);
					SendMessage(hTemp, CB_SETCURSEL, SearchEffectAmountID(SSData.Ki_Blast[TabNum]), 0);
					hTemp = GetDlgItem(hDlg, IDC_COMBO22);
					SendMessage(hTemp, CB_SETCURSEL, SearchEffectAmountID(SSData.Strike_Super[TabNum]), 0);
					hTemp = GetDlgItem(hDlg, IDC_COMBO23);
					SendMessage(hTemp, CB_SETCURSEL, SearchEffectAmountID(SSData.Ki_Blast_Super[TabNum]), 0);
					hTemp = GetDlgItem(hDlg, IDC_COMBO24);
					SendMessage(hTemp, CB_SETCURSEL, SearchEffectAmountID(SSData.Basic_Attack_Dmg[TabNum]), 0);
					hTemp = GetDlgItem(hDlg, IDC_COMBO25);
					SendMessage(hTemp, CB_SETCURSEL, SearchEffectAmountID(SSData.Ki_Blast_Dmg[TabNum]), 0);
					hTemp = GetDlgItem(hDlg, IDC_COMBO26);
					SendMessage(hTemp, CB_SETCURSEL, SearchEffectAmountID(SSData.Strike_Super_Dmg[TabNum]), 0);
					hTemp = GetDlgItem(hDlg, IDC_COMBO27);
					SendMessage(hTemp, CB_SETCURSEL, SearchEffectAmountID(SSData.Ki_Blast_Super_Dmg[TabNum]), 0);
					hTemp = GetDlgItem(hDlg, IDC_COMBO20);
					SendMessage(hTemp, CB_SETCURSEL, SearchEffectAmountID(SSData.Revive_Speed[TabNum]), 0);
				}
			}
		}
		
		}
		return (INT_PTR)TRUE;

	case WM_NOTIFY:
		switch (((LPNMHDR)lParam)->code)
			//switch (lParam)
		{
		case TCN_SELCHANGING:
		{
			// Return FALSE to allow the selection to change.
			return FALSE;
		}
		break;
		case TCN_SELCHANGE:
		{
			wchar_t Temp[10];
			HWND hTemp;
			int TabNum = TabCtrl_GetCurSel(GetDlgItem(hDlg, IDC_TAB1));
			switch (TabNum)
			{
			case 0:
			{
				if (!SSIDBData.empty())
				{
					hTemp = GetDlgItem(hDlg, IDC_COMBO3);
					SendMessage(hTemp, CB_SETCURSEL, SearchEffectID(SSData.Effect[TabNum]), 0);
					hTemp = GetDlgItem(hDlg, IDC_COMBO4);
					SendMessage(hTemp, CB_SETCURSEL, SearchEffectAmountID(SSData.EffectAmount[TabNum]), 0);
					hTemp = GetDlgItem(hDlg, IDC_COMBO5);
					SendMessage(hTemp, CB_SETCURSEL, SearchFlagID(SSData.Flag[TabNum]), 0);
					hTemp = GetDlgItem(hDlg, IDC_COMBO6);
					SendMessage(hTemp, CB_SETCURSEL, SearchTriggerID(SSData.Trigger[TabNum]), 0);
					hTemp = GetDlgItem(hDlg, IDC_COMBO7);
					SendMessage(hTemp, CB_SETCURSEL, SearchTargetID(SSData.Target[TabNum]), 0);
					hTemp = GetDlgItem(hDlg, IDC_COMBO8);
					SendMessage(hTemp, CB_SETCURSEL, SearchTCID(SSData.TriggerConditions1[TabNum]), 0);
					hTemp = GetDlgItem(hDlg, IDC_COMBO9);
					SendMessage(hTemp, CB_SETCURSEL, SearchTCID(SSData.TriggerConditions2[TabNum]), 0);
					hTemp = GetDlgItem(hDlg, IDC_COMBO10);
					SendMessage(hTemp, CB_SETCURSEL, SearchTCID(SSData.TriggerConditions3[TabNum]), 0);
					hTemp = GetDlgItem(hDlg, IDC_COMBO29);
					SendMessage(hTemp, CB_SETCURSEL, SearchTimerID(SSData.Timer[TabNum]), 0);
					hTemp = GetDlgItem(hDlg, IDC_COMBO11);
					SendMessage(hTemp, CB_SETCURSEL, SearchEffectAmountID(SSData.Health[TabNum]), 0);
					hTemp = GetDlgItem(hDlg, IDC_COMBO12);
					SendMessage(hTemp, CB_SETCURSEL, SearchEffectAmountID(SSData.Ki[TabNum]), 0);
					hTemp = GetDlgItem(hDlg, IDC_COMBO13);
					SendMessage(hTemp, CB_SETCURSEL, SearchEffectAmountID(SSData.Ki_RegenRate[TabNum]), 0);
					hTemp = GetDlgItem(hDlg, IDC_COMBO14);
					SendMessage(hTemp, CB_SETCURSEL, SearchEffectAmountID(SSData.Stamina[TabNum]), 0);
					hTemp = GetDlgItem(hDlg, IDC_COMBO15);
					SendMessage(hTemp, CB_SETCURSEL, SearchEffectAmountID(SSData.Stamina_RegenRate[TabNum]), 0);
					hTemp = GetDlgItem(hDlg, IDC_COMBO16);
					SendMessage(hTemp, CB_SETCURSEL, SearchEffectAmountID(SSData.Ground_Speed[TabNum]), 0);
					hTemp = GetDlgItem(hDlg, IDC_COMBO17);
					SendMessage(hTemp, CB_SETCURSEL, SearchEffectAmountID(SSData.Flight_Speed[TabNum]), 0);
					hTemp = GetDlgItem(hDlg, IDC_COMBO18);
					SendMessage(hTemp, CB_SETCURSEL, SearchEffectAmountID(SSData.Boost_Speed[TabNum]), 0);
					hTemp = GetDlgItem(hDlg, IDC_COMBO19);
					SendMessage(hTemp, CB_SETCURSEL, SearchEffectAmountID(SSData.Dash_Speed[TabNum]), 0);
					hTemp = GetDlgItem(hDlg, IDC_COMBO28);
					SendMessage(hTemp, CB_SETCURSEL, SearchEffectAmountID(SSData.Basic_Attack[TabNum]), 0);
					hTemp = GetDlgItem(hDlg, IDC_COMBO21);
					SendMessage(hTemp, CB_SETCURSEL, SearchEffectAmountID(SSData.Ki_Blast[TabNum]), 0);
					hTemp = GetDlgItem(hDlg, IDC_COMBO22);
					SendMessage(hTemp, CB_SETCURSEL, SearchEffectAmountID(SSData.Strike_Super[TabNum]), 0);
					hTemp = GetDlgItem(hDlg, IDC_COMBO23);
					SendMessage(hTemp, CB_SETCURSEL, SearchEffectAmountID(SSData.Ki_Blast_Super[TabNum]), 0);
					hTemp = GetDlgItem(hDlg, IDC_COMBO24);
					SendMessage(hTemp, CB_SETCURSEL, SearchEffectAmountID(SSData.Basic_Attack_Dmg[TabNum]), 0);
					hTemp = GetDlgItem(hDlg, IDC_COMBO25);
					SendMessage(hTemp, CB_SETCURSEL, SearchEffectAmountID(SSData.Ki_Blast_Dmg[TabNum]), 0);
					hTemp = GetDlgItem(hDlg, IDC_COMBO26);
					SendMessage(hTemp, CB_SETCURSEL, SearchEffectAmountID(SSData.Strike_Super_Dmg[TabNum]), 0);
					hTemp = GetDlgItem(hDlg, IDC_COMBO27);
					SendMessage(hTemp, CB_SETCURSEL, SearchEffectAmountID(SSData.Ki_Blast_Super_Dmg[TabNum]), 0);
					hTemp = GetDlgItem(hDlg, IDC_COMBO20);
					SendMessage(hTemp, CB_SETCURSEL, SearchEffectAmountID(SSData.Revive_Speed[TabNum]), 0);
				}
			}
			break;
			case 1:
			{
				if (!SSIDBData.empty())
				{
					hTemp = GetDlgItem(hDlg, IDC_COMBO3);
					SendMessage(hTemp, CB_SETCURSEL, SearchEffectID(SSData.Effect[TabNum]), 0);
					hTemp = GetDlgItem(hDlg, IDC_COMBO4);
					SendMessage(hTemp, CB_SETCURSEL, SearchEffectAmountID(SSData.EffectAmount[TabNum]), 0);
					hTemp = GetDlgItem(hDlg, IDC_COMBO5);
					SendMessage(hTemp, CB_SETCURSEL, SearchFlagID(SSData.Flag[TabNum]), 0);
					hTemp = GetDlgItem(hDlg, IDC_COMBO6);
					SendMessage(hTemp, CB_SETCURSEL, SearchTriggerID(SSData.Trigger[TabNum]), 0);
					hTemp = GetDlgItem(hDlg, IDC_COMBO7);
					SendMessage(hTemp, CB_SETCURSEL, SearchTargetID(SSData.Target[TabNum]), 0);
					hTemp = GetDlgItem(hDlg, IDC_COMBO8);
					SendMessage(hTemp, CB_SETCURSEL, SearchTCID(SSData.TriggerConditions1[TabNum]), 0);
					hTemp = GetDlgItem(hDlg, IDC_COMBO9);
					SendMessage(hTemp, CB_SETCURSEL, SearchTCID(SSData.TriggerConditions2[TabNum]), 0);
					hTemp = GetDlgItem(hDlg, IDC_COMBO10);
					SendMessage(hTemp, CB_SETCURSEL, SearchTCID(SSData.TriggerConditions3[TabNum]), 0);
					hTemp = GetDlgItem(hDlg, IDC_COMBO29);
					SendMessage(hTemp, CB_SETCURSEL, SearchTimerID(SSData.Timer[TabNum]), 0);
					hTemp = GetDlgItem(hDlg, IDC_COMBO11);
					SendMessage(hTemp, CB_SETCURSEL, SearchEffectAmountID(SSData.Health[TabNum]), 0);
					hTemp = GetDlgItem(hDlg, IDC_COMBO12);
					SendMessage(hTemp, CB_SETCURSEL, SearchEffectAmountID(SSData.Ki[TabNum]), 0);
					hTemp = GetDlgItem(hDlg, IDC_COMBO13);
					SendMessage(hTemp, CB_SETCURSEL, SearchEffectAmountID(SSData.Ki_RegenRate[TabNum]), 0);
					hTemp = GetDlgItem(hDlg, IDC_COMBO14);
					SendMessage(hTemp, CB_SETCURSEL, SearchEffectAmountID(SSData.Stamina[TabNum]), 0);
					hTemp = GetDlgItem(hDlg, IDC_COMBO15);
					SendMessage(hTemp, CB_SETCURSEL, SearchEffectAmountID(SSData.Stamina_RegenRate[TabNum]), 0);
					hTemp = GetDlgItem(hDlg, IDC_COMBO16);
					SendMessage(hTemp, CB_SETCURSEL, SearchEffectAmountID(SSData.Ground_Speed[TabNum]), 0);
					hTemp = GetDlgItem(hDlg, IDC_COMBO17);
					SendMessage(hTemp, CB_SETCURSEL, SearchEffectAmountID(SSData.Flight_Speed[TabNum]), 0);
					hTemp = GetDlgItem(hDlg, IDC_COMBO18);
					SendMessage(hTemp, CB_SETCURSEL, SearchEffectAmountID(SSData.Boost_Speed[TabNum]), 0);
					hTemp = GetDlgItem(hDlg, IDC_COMBO19);
					SendMessage(hTemp, CB_SETCURSEL, SearchEffectAmountID(SSData.Dash_Speed[TabNum]), 0);
					hTemp = GetDlgItem(hDlg, IDC_COMBO28);
					SendMessage(hTemp, CB_SETCURSEL, SearchEffectAmountID(SSData.Basic_Attack[TabNum]), 0);
					hTemp = GetDlgItem(hDlg, IDC_COMBO21);
					SendMessage(hTemp, CB_SETCURSEL, SearchEffectAmountID(SSData.Ki_Blast[TabNum]), 0);
					hTemp = GetDlgItem(hDlg, IDC_COMBO22);
					SendMessage(hTemp, CB_SETCURSEL, SearchEffectAmountID(SSData.Strike_Super[TabNum]), 0);
					hTemp = GetDlgItem(hDlg, IDC_COMBO23);
					SendMessage(hTemp, CB_SETCURSEL, SearchEffectAmountID(SSData.Ki_Blast_Super[TabNum]), 0);
					hTemp = GetDlgItem(hDlg, IDC_COMBO24);
					SendMessage(hTemp, CB_SETCURSEL, SearchEffectAmountID(SSData.Basic_Attack_Dmg[TabNum]), 0);
					hTemp = GetDlgItem(hDlg, IDC_COMBO25);
					SendMessage(hTemp, CB_SETCURSEL, SearchEffectAmountID(SSData.Ki_Blast_Dmg[TabNum]), 0);
					hTemp = GetDlgItem(hDlg, IDC_COMBO26);
					SendMessage(hTemp, CB_SETCURSEL, SearchEffectAmountID(SSData.Strike_Super_Dmg[TabNum]), 0);
					hTemp = GetDlgItem(hDlg, IDC_COMBO27);
					SendMessage(hTemp, CB_SETCURSEL, SearchEffectAmountID(SSData.Ki_Blast_Super_Dmg[TabNum]), 0);
					hTemp = GetDlgItem(hDlg, IDC_COMBO20);
					SendMessage(hTemp, CB_SETCURSEL, SearchEffectAmountID(SSData.Revive_Speed[TabNum]), 0);
				}
			}
			break;
			case 2:
			{
				if (!SSIDBData.empty())
				{
					hTemp = GetDlgItem(hDlg, IDC_COMBO3);
					SendMessage(hTemp, CB_SETCURSEL, SearchEffectID(SSData.Effect[TabNum]), 0);
					hTemp = GetDlgItem(hDlg, IDC_COMBO4);
					SendMessage(hTemp, CB_SETCURSEL, SearchEffectAmountID(SSData.EffectAmount[TabNum]), 0);
					hTemp = GetDlgItem(hDlg, IDC_COMBO5);
					SendMessage(hTemp, CB_SETCURSEL, SearchFlagID(SSData.Flag[TabNum]), 0);
					hTemp = GetDlgItem(hDlg, IDC_COMBO6);
					SendMessage(hTemp, CB_SETCURSEL, SearchTriggerID(SSData.Trigger[TabNum]), 0);
					hTemp = GetDlgItem(hDlg, IDC_COMBO7);
					SendMessage(hTemp, CB_SETCURSEL, SearchTargetID(SSData.Target[TabNum]), 0);
					hTemp = GetDlgItem(hDlg, IDC_COMBO8);
					SendMessage(hTemp, CB_SETCURSEL, SearchTCID(SSData.TriggerConditions1[TabNum]), 0);
					hTemp = GetDlgItem(hDlg, IDC_COMBO9);
					SendMessage(hTemp, CB_SETCURSEL, SearchTCID(SSData.TriggerConditions2[TabNum]), 0);
					hTemp = GetDlgItem(hDlg, IDC_COMBO10);
					SendMessage(hTemp, CB_SETCURSEL, SearchTCID(SSData.TriggerConditions3[TabNum]), 0);
					hTemp = GetDlgItem(hDlg, IDC_COMBO29);
					SendMessage(hTemp, CB_SETCURSEL, SearchTimerID(SSData.Timer[TabNum]), 0);
					hTemp = GetDlgItem(hDlg, IDC_COMBO11);
					SendMessage(hTemp, CB_SETCURSEL, SearchEffectAmountID(SSData.Health[TabNum]), 0);
					hTemp = GetDlgItem(hDlg, IDC_COMBO12);
					SendMessage(hTemp, CB_SETCURSEL, SearchEffectAmountID(SSData.Ki[TabNum]), 0);
					hTemp = GetDlgItem(hDlg, IDC_COMBO13);
					SendMessage(hTemp, CB_SETCURSEL, SearchEffectAmountID(SSData.Ki_RegenRate[TabNum]), 0);
					hTemp = GetDlgItem(hDlg, IDC_COMBO14);
					SendMessage(hTemp, CB_SETCURSEL, SearchEffectAmountID(SSData.Stamina[TabNum]), 0);
					hTemp = GetDlgItem(hDlg, IDC_COMBO15);
					SendMessage(hTemp, CB_SETCURSEL, SearchEffectAmountID(SSData.Stamina_RegenRate[TabNum]), 0);
					hTemp = GetDlgItem(hDlg, IDC_COMBO16);
					SendMessage(hTemp, CB_SETCURSEL, SearchEffectAmountID(SSData.Ground_Speed[TabNum]), 0);
					hTemp = GetDlgItem(hDlg, IDC_COMBO17);
					SendMessage(hTemp, CB_SETCURSEL, SearchEffectAmountID(SSData.Flight_Speed[TabNum]), 0);
					hTemp = GetDlgItem(hDlg, IDC_COMBO18);
					SendMessage(hTemp, CB_SETCURSEL, SearchEffectAmountID(SSData.Boost_Speed[TabNum]), 0);
					hTemp = GetDlgItem(hDlg, IDC_COMBO19);
					SendMessage(hTemp, CB_SETCURSEL, SearchEffectAmountID(SSData.Dash_Speed[TabNum]), 0);
					hTemp = GetDlgItem(hDlg, IDC_COMBO28);
					SendMessage(hTemp, CB_SETCURSEL, SearchEffectAmountID(SSData.Basic_Attack[TabNum]), 0);
					hTemp = GetDlgItem(hDlg, IDC_COMBO21);
					SendMessage(hTemp, CB_SETCURSEL, SearchEffectAmountID(SSData.Ki_Blast[TabNum]), 0);
					hTemp = GetDlgItem(hDlg, IDC_COMBO22);
					SendMessage(hTemp, CB_SETCURSEL, SearchEffectAmountID(SSData.Strike_Super[TabNum]), 0);
					hTemp = GetDlgItem(hDlg, IDC_COMBO23);
					SendMessage(hTemp, CB_SETCURSEL, SearchEffectAmountID(SSData.Ki_Blast_Super[TabNum]), 0);
					hTemp = GetDlgItem(hDlg, IDC_COMBO24);
					SendMessage(hTemp, CB_SETCURSEL, SearchEffectAmountID(SSData.Basic_Attack_Dmg[TabNum]), 0);
					hTemp = GetDlgItem(hDlg, IDC_COMBO25);
					SendMessage(hTemp, CB_SETCURSEL, SearchEffectAmountID(SSData.Ki_Blast_Dmg[TabNum]), 0);
					hTemp = GetDlgItem(hDlg, IDC_COMBO26);
					SendMessage(hTemp, CB_SETCURSEL, SearchEffectAmountID(SSData.Strike_Super_Dmg[TabNum]), 0);
					hTemp = GetDlgItem(hDlg, IDC_COMBO27);
					SendMessage(hTemp, CB_SETCURSEL, SearchEffectAmountID(SSData.Ki_Blast_Super_Dmg[TabNum]), 0);
					hTemp = GetDlgItem(hDlg, IDC_COMBO20);
					SendMessage(hTemp, CB_SETCURSEL, SearchEffectAmountID(SSData.Revive_Speed[TabNum]), 0);
				}
			}
			break;
			}
		}
		break;
		}
		return (INT_PTR)TRUE;
	default:
		return (INT_PTR)FALSE;

	}
	return (INT_PTR)FALSE;
}

