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
	wcex.hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1));
	wcex.hIconSm = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1));
	wcex.hInstance = hInstance;
	wcex.lpfnWndProc = WndProc;
	wcex.lpszClassName = L"Window";
	wcex.lpszMenuName = NULL;// MAKEINTRESOURCE(IDR_MENU1);
	wcex.style = 0;

	if (!RegisterClassEx(&wcex))
	{
		MessageBox(NULL, L"Class failed to register", L"Error", MB_ICONERROR | MB_OK);
	}
	
	HWND hwnd = CreateWindowEx(WS_EX_CLIENTEDGE, L"Window", L"DBXV Tool", WS_CLIPCHILDREN | WS_CAPTION | WS_SYSMENU | WS_MINIMIZE,
								CW_USEDEFAULT, CW_USEDEFAULT, 650, 700, NULL, NULL, hInstance, NULL);
	if (hwnd == NULL)
	{
		MessageBox(NULL, L"Window Creation fail", L"Error", MB_ICONERROR | MB_OK);
	}
	
	g_hInst = hInstance;
	SSkillID[0].RefID = -1, SSkillID[0].HexID1 = 0xff, SSkillID[0].HexID2 = 0xff, SSkillID[0].RefCode = 'BLK', SSkillID[0].Name = '----';
	USkillID[0].RefID = -1, USkillID[0].HexID1 = 0xff, USkillID[0].HexID2 = 0xff, USkillID[0].RefCode = 'BLK', USkillID[0].Name = '----';
	ASkillID[0].RefID = -1, ASkillID[0].HexID1 = 0xff, ASkillID[0].HexID2 = 0xff, ASkillID[0].RefCode = 'BLK', ASkillID[0].Name = '----';
	ESkillID[0].RefID = -1, ESkillID[0].HexID1 = 0xff, ESkillID[0].HexID2 = 0xff, ESkillID[0].RefCode = 'BLK', ESkillID[0].Name = '----';
	LoadAura();
	LoadCharacter();
	LoadCostume();
	int SSkillCount = LoadSkill("Data/Super Skill ID.ini", SSkillSetting, SSkillID);
	int USkillCount = LoadSkill("Data/Ultimate Skill ID.ini", USkillSetting, USkillID);
	int ASkillCount = LoadSkill("Data/Awoken Skill ID.ini", ASkillSetting, ASkillID);
	int ESkillCount = LoadSkill("Data/Evasive Skill ID.ini", ESkillSetting, ESkillID);

	TCHAR *TabLabel[] = { L"Aura", L"Skill", L"Super Soul" };
	int  count = 0, numTab = 2;
	DWORD Err = NULL;
	WCHAR WERR[100] = L"";
	hwndTab = CreateTabControl(hwnd, g_hInst, numTab, TabLabel);
	hwndDisplay[0] = CreateDialog(g_hInst, MAKEINTRESOURCE(IDD_DIALOG1), hwndTab, MainDialogProc);
	if (!hwndDisplay[0]) { Err = GetLastError();  swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
	hwndDisplay[1] = CreateDialog(g_hInst, MAKEINTRESOURCE(IDD_DIALOG2), hwndTab, MainDialogProc);
	if (!hwndDisplay[1]) { Err = GetLastError();  swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
	//hwndDisplay[2] = CreateDialog(g_hInst, MAKEINTRESOURCE(IDD_DIALOG3), hwndTab, MainDialogProc);
	//if (!hwndDisplay[2]) { Err = GetLastError();  swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
	while (count < numTab )
	{
		DialogResize(hwndTab, hwndDisplay[count]);
		count++;
	}
	HWND hTemp;
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

	hComboCheck[0] = GetDlgItem(hwndDisplay[0], IDC_COMBO3);; //Used to check combo box so when character change costume box can be set appropriatley  
	hComboCheck[1] = GetDlgItem(hwndDisplay[1], IDC_COMBO6);
	
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

	ShowWindow(hwndDisplay[0], SW_SHOWNORMAL);
	UpdateWindow(hwndDisplay[0]);
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);
	
	MSG msg;
	
	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);

			if (IsDialogMessage(hwndDisplay[ActiveTab], &msg))
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
		switch (wParam)
		{

		}
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
	{
		RECT rcClient;
		GetClientRect(hwnd, &rcClient);
		SetWindowPos(hwndTab, NULL, 0, 0, rcClient.right, rcClient.bottom, NULL);
		int count = 0, numTab = 2;
		while (count < numTab)
		{
			DialogResize(hwndTab, hwndDisplay[count]);
			count++;
			UpdateWindow(hwndDisplay[count]);
		}
		UpdateWindow(hwndTab);
	}
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
			if (saveFile(CusFile, AuraData) == -1)
			{
				HWND EditError = GetDlgItem(hDlg, IDC_EDITERROR1);
				SetWindowText(EditError, L"Error Failed to Save");
				SetFocus(EditError);
			}
			if (saveFile(CusFile, AuraData) == 0)
			{
				HWND EditError = GetDlgItem(hDlg, IDC_EDITERROR1);
				SetWindowText(EditError, L"Save Succcesful");
				SetFocus(EditError);
			}break;
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
			if (saveFile(CusFile, CusData) == -1 )
			{
				HWND EditError = GetDlgItem(hDlg, IDC_EDITERROR2);
				SetWindowText(EditError, L"Error Failed to Save");
				SetFocus(EditError);
			}
			if (saveFile(CusFile, CusData) == 0)
			{
				HWND EditError = GetDlgItem(hDlg, IDC_EDITERROR2);
				SetWindowText(EditError, L"Save Succcesful");
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
		}
			
		}
		return (INT_PTR)TRUE;

	default:
		return (INT_PTR)FALSE;

	}
	return (INT_PTR)FALSE;
}

