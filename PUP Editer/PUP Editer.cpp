// PUP Editer.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "PUP Editer.h"

#define MAX_LOADSTRING 100
#define screenWidth 525
#define screenHeight 600

struct PUPDATA
{
	int ID;
	std::string Name;
};

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
HWND g_hwnd, hwndDisplayPUP;
char FileNamePUP[MAX_PATH];
std::string PUPData, PUPSetting;
PUPDATA PUPID[1000];

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK DialogProc(HWND, UINT, WPARAM, LPARAM);
void loadPSC();
void GetStat(int);
void SetStat(int);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_PUPEDITER, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

	hwndDisplayPUP = CreateDialog(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), g_hwnd, DialogProc);
	DialogResize(g_hwnd, hwndDisplayPUP);


	ShowWindow(hwndDisplayPUP, SW_SHOWNORMAL);
	UpdateWindow(hwndDisplayPUP);

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PUPEDITER));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = NULL;
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   g_hwnd = CreateWindowEx(WS_EX_CLIENTEDGE, szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
	   CW_USEDEFAULT, CW_USEDEFAULT, screenWidth, screenHeight, nullptr, nullptr, hInstance, nullptr);

   if (!g_hwnd)
   {
      return FALSE;
   }

   ShowWindow(g_hwnd, nCmdShow);
   UpdateWindow(g_hwnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
	case WM_CLOSE:
		DestroyWindow(hwnd);
    case WM_COMMAND:
        {

        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
            EndPaint(hwnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for Dialog box.
INT_PTR CALLBACK DialogProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case IDC_OPENPUP:
		{
			COMDLG_FILTERSPEC filter[] = { { L"Xenoverse Pup File", L"*.pup" } };

			getFileName(g_hwnd, FileNamePUP, filter, 1);
			openFile(FileNamePUP, PUPData);
			loadPSC();
		}
		break;
		case IDC_SETSTAT:
		{
			int ID;

			ID = SendDlgItemMessage(hwndDisplayPUP, IDC_COMBO1, CB_GETCURSEL, 0, 0);
			if(ID > -1)
				SetStat((PUPID[ID].ID));
		}
		break;
		case IDC_SAVEPUP:
		{
			if (saveFile(FileNamePUP, PUPData) == 0)
			{
				HWND EditError = GetDlgItem(hDlg, IDC_EDITERR1);
				SetWindowText(EditError, L"PUP File Save Succcesful");
				SetFocus(EditError);
			}
			else
			{
				if (!PUPData.empty())
				{
					HWND EditError = GetDlgItem(hDlg, IDC_EDITERR1);
					SetWindowText(EditError, L"Error Failed to Save PUP File");
					SetFocus(EditError);
				}
				else
				{
					HWND EditError = GetDlgItem(hDlg, IDC_EDITERR1);
					SetWindowText(EditError, L"No PUP File Loaded");
					SetFocus(EditError);
				}
			}
		}
		break;
		}
		switch (HIWORD(wParam))
		{
		case CBN_SELCHANGE:
		{
			int index;

			index = SendDlgItemMessage(hwndDisplayPUP, IDC_COMBO1, CB_GETCURSEL, 0, 0);

			if (index > -1)
			{
				GetStat(PUPID[index].ID);
			}
		}
		}
		break;
	}
	return (INT_PTR)FALSE;
    }
    return (INT_PTR)FALSE;
}

void loadPSC()
{
	int count = 0;
	HWND hTemp;
	WCHAR WERR[100];
	std::string tempName;
	LRESULT Err;
	std::string TempString;
	PUPDATA tempID[1000];
	char  CTempValue[105] = { NULL };
	int PUPCount = 0, HexCount = 0x10;

	if (PUPData.empty()) return;

	openFile("Data/PUP ID.ini", PUPSetting);
	std::istringstream TempStream(PUPSetting);


	while (std::getline(TempStream, TempString))
	{
		int posSet = 0, max = TempString.size();
		count = 0;
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
		tempID[PUPCount].ID = (uint8_t)CTempHexID;
		tempID[PUPCount].Name = CTempValue;
#ifdef _DEBUG
		std::cout << tempID[PUPCount].ID << " - " << tempID[PUPCount].Name << std::endl;
#endif
		memset(CTempValue, 0, strlen(CTempValue));//Used to clear CTempValue to ensure names dont have extra characters from previous names  
		PUPCount++;
	}

	count = 0;
	while (count < (uint8_t)PUPData[0x08])
	{
		PUPID[count].ID = PUPData[HexCount];
		for (int i = 0; i < PUPCount; i++)
		{
			if (PUPID[count].ID == tempID[i].ID)
				PUPID[count].Name = tempID[i].Name;
		}
		
		count++;
		HexCount += 0x98;
	}

	count = 0;
	char tempNum[10];
	while (count < (uint8_t)PUPData[0x08])
	{
		tempName.clear();
		sprintf_s(tempNum, "%.2d", PUPID[count].ID);
		tempName.append(tempNum), tempName.append(" - "), tempName.append(PUPID[count].Name.c_str());
		size_t size = strlen(tempName.c_str()) + 1;
		wchar_t *ComboBoxItemMSGTemp = new wchar_t[size];

		size_t outSize;
		mbstowcs_s(&outSize, ComboBoxItemMSGTemp, size, tempName.c_str(), size - 1);
		const TCHAR *ComboBoxItemMSG = { ComboBoxItemMSGTemp };
		hTemp = GetDlgItem(hwndDisplayPUP, IDC_COMBO1);
		if (!hTemp) { Err = GetLastError(); swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		SendMessage(hTemp, CB_ADDSTRING, 0, reinterpret_cast <LPARAM> ((LPCTSTR)ComboBoxItemMSG));
		if ((Err = GetLastError()) != 0) { swprintf_s(WERR, 100, L"%d", Err); MessageBox(NULL, WERR, L"ERROR", MB_OK | MB_ICONERROR); }
		count++;
	}
}

void GetStat(int ID)
{
	int index = 0x10, tempNum;
	char tempInfo[100];
	std::string CHex;
	CHex.resize(4);

	while (index < PUPData.size())
	{
		if (ID == PUPData[index]) break;
		index += 0x98;
	}

	sprintf_s(tempInfo, "%d", ID);
	SetDlgItemTextA(hwndDisplayPUP, IDC_EDIT1, tempInfo);

	tempNum = (PUPData[index + 4]) + (PUPData[index + 5] * 100) + (PUPData[index + 6] * 10000) + (PUPData[index + 7] * 1000000);
	sprintf_s(tempInfo, "%d", tempNum);
	SetDlgItemTextA(hwndDisplayPUP, IDC_EDIT2, tempInfo);

	tempNum = (PUPData[index + 8] ) + (PUPData[index + 9] * 100) + (PUPData[index + 10] * 10000) + (PUPData[index + 11] * 1000000);
	sprintf_s(tempInfo, "%d", tempNum);
	SetDlgItemTextA(hwndDisplayPUP, IDC_EDIT3, tempInfo);

	tempNum = (PUPData[index + 12]) + (PUPData[index + 13] * 100) + (PUPData[index + 14] * 10000) + (PUPData[index + 15] * 1000000);
	sprintf_s(tempInfo, "%d", tempNum);
	SetDlgItemTextA(hwndDisplayPUP, IDC_EDIT4, tempInfo);

	for (int i = 0; i < 23; i++)
	{
		CHex[0] = PUPData[index + 16 + (i * 4)], CHex[1] = PUPData[index + 17 + (i * 4)], CHex[2] = PUPData[index + 18 + (i * 4)], 
			CHex[3] = PUPData[index + 19 + (i * 4)];
		sprintf_s(tempInfo, "%f", HexToFloat(CHex));
		SetDlgItemTextA(hwndDisplayPUP, IDC_EDIT5 + i, tempInfo);
	}
}

void SetStat(int ID)
{
	int index = 0x10;
	char tempInfo[100], NumTemp[20], HexTemp[10];
	std::string CHex;
	CHex.resize(4);

	while (index < PUPData.size())
	{
		if (ID == PUPData[index]) break;
		index += 0x98;
	}

	GetDlgItemTextA(hwndDisplayPUP, IDC_EDIT2, NumTemp, 20);
	sprintf_s(HexTemp, "%.8x", atoi(NumTemp));

	std::stringstream HexNum;
	char Temp1[2], Temp2[2], Temp3[2], Temp4[2];
	int TempID1, TempID2, TempID3, TempID4;

	Temp1[0] = HexTemp[0], Temp1[1] = HexTemp[1];
	Temp2[0] = HexTemp[2], Temp2[1] = HexTemp[3];
	Temp3[0] = HexTemp[4], Temp3[1] = HexTemp[5];
	Temp4[0] = HexTemp[6], Temp4[1] = HexTemp[7];

	HexNum << std::hex << Temp1;
	HexNum >> TempID1;
	HexNum.str(std::string());
	HexNum.clear();
	HexNum << std::hex << Temp2;
	HexNum >> TempID2;
	HexNum.str(std::string());
	HexNum.clear();
	HexNum << std::hex << Temp3;
	HexNum >> TempID3;
	HexNum.str(std::string());
	HexNum.clear();
	HexNum << std::hex << Temp4;
	HexNum >> TempID4;

	PUPData[index + 7] = TempID1;
	PUPData[index + 6] = TempID2;
	PUPData[index + 5] = TempID3;
	PUPData[index + 4] = TempID4;

	GetDlgItemTextA(hwndDisplayPUP, IDC_EDIT3, NumTemp, 20);
	sprintf_s(HexTemp, "%.8x", atoi(NumTemp));

	Temp1[0] = HexTemp[0], Temp1[1] = HexTemp[1];
	Temp2[0] = HexTemp[2], Temp2[1] = HexTemp[3];
	Temp3[0] = HexTemp[4], Temp3[1] = HexTemp[5];
	Temp4[0] = HexTemp[6], Temp4[1] = HexTemp[7];

	HexNum.str(std::string());
	HexNum.clear();
	HexNum << std::hex << Temp1;
	HexNum >> TempID1;
	HexNum.str(std::string());
	HexNum.clear();
	HexNum << std::hex << Temp2;
	HexNum >> TempID2;
	HexNum.str(std::string());
	HexNum.clear();
	HexNum << std::hex << Temp3;
	HexNum >> TempID3;
	HexNum.str(std::string());
	HexNum.clear();
	HexNum << std::hex << Temp4;
	HexNum >> TempID4;

	PUPData[index + 11] = TempID1;
	PUPData[index + 10] = TempID2;
	PUPData[index + 9] = TempID3;
	PUPData[index + 8] = TempID4;

	GetDlgItemTextA(hwndDisplayPUP, IDC_EDIT4, NumTemp, 8);
	sprintf_s(HexTemp, "%.8x", atoi(NumTemp));

	Temp1[0] = HexTemp[0], Temp1[1] = HexTemp[1];
	Temp2[0] = HexTemp[2], Temp2[1] = HexTemp[3];
	Temp3[0] = HexTemp[4], Temp3[1] = HexTemp[5];
	Temp4[0] = HexTemp[6], Temp4[1] = HexTemp[7];

	HexNum.str(std::string());
	HexNum.clear();
	HexNum << std::hex << Temp1;
	HexNum >> TempID1;
	HexNum.str(std::string());
	HexNum.clear();
	HexNum << std::hex << Temp2;
	HexNum >> TempID2;
	HexNum.str(std::string());
	HexNum.clear();
	HexNum << std::hex << Temp3;
	HexNum >> TempID3;
	HexNum.str(std::string());
	HexNum.clear();
	HexNum << std::hex << Temp4;
	HexNum >> TempID4;

	PUPData[index + 15] = TempID1;
	PUPData[index + 14] = TempID2;
	PUPData[index + 13] = TempID3;
	PUPData[index + 12] = TempID4;

	for (int i = 0; i < 23; i++)
	{
		GetDlgItemTextA(hwndDisplayPUP, IDC_EDIT5 + i, tempInfo, 8);
		PUPData.erase(index + 16 + (i * 4), 4);
		PUPData.insert(index + 16 + (i * 4), FloatToHex(atof(tempInfo)));
	}
}