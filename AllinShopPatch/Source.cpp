#include "Header.h"

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK MainDialogProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
WNDPROC WndProcEditDefault = 0;
void SetIDBPrice(std::string &IDBData);
HWND hwndDisplay;
char FileName[20][MAX_PATH], FolderPath[MAX_PATH];
std::string IDBData[20];

//tell it to accept files
//DragAcceptFiles(hwndedit, true);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wcex;
	ZeroMemory(&wcex, sizeof(WNDCLASSEX));
	wcex.cbClsExtra = 0;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.cbWndExtra = 0;
	wcex.hbrBackground = NULL;//CreatePatternBrush(LoadBitmap(hInstance, (LPCWSTR)IDR_IMAGE1));
	wcex.hCursor = NULL;
	wcex.hIcon = NULL;//LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	wcex.hIconSm = NULL;// LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	wcex.hInstance = hInstance;
	wcex.lpfnWndProc = WndProc;
	wcex.lpszClassName = L"Window";
	wcex.lpszMenuName = NULL;// MAKEINTRESOURCE(IDR_MENU1);
	wcex.style = CS_VREDRAW | CS_HREDRAW;

	if (!RegisterClassEx(&wcex))
	{
		MessageBox(NULL, L"Class failed to register", L"Error", MB_ICONERROR | MB_OK);
	}

	HWND hwnd = CreateWindowEx(WS_EX_CLIENTEDGE, L"Window", L"AllinShop", WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
		CW_USEDEFAULT, CW_USEDEFAULT, 490,350, NULL, NULL, hInstance, NULL);
	/*HWND hwnd = CreateWindowEx(WS_EX_CLIENTEDGE, L"Window", L"DBXV2 Tool", WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
	CW_USEDEFAULT, CW_USEDEFAULT, 900, 1200, NULL, NULL, hInstance, NULL);*/
	if (hwnd == NULL)
	{
		MessageBox(NULL, L"Window Creation fail", L"Error", MB_ICONERROR | MB_OK);
	}

	hwndDisplay = CreateDialog(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), hwnd, MainDialogProc);

	ShowWindow(hwndDisplay, SW_SHOWNORMAL);
	UpdateWindow(hwndDisplay);
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);


	MSG msg;

	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
		if (!IsDialogMessage(hwndDisplay, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return msg.wParam;

}

void SetIDBPrice(std::string &IDBData)
{
	int count = IDBData[0x0c] + 0x10, size = IDBData.size();

	while (count < size)
	{
		if (IDBData[count] == 00 && IDBData[count + 1] == 00 && IDBData[count + 2] == 00 && IDBData[count + 3] == 00)
		{
			IDBData[count] = 01;
			IDBData[count - 6] = -1, IDBData[count - 5] = -1, IDBData[count + 8] = -1;
		}
		count += 720;
	}
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
		//store the original window's procedure
		WndProcEditDefault = (WNDPROC)GetWindowLongPtr(GetDlgItem(hDlg, IDC_EDIT1), GWLP_WNDPROC);
	}
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		switch (wParam)
		{
		case IDC_BUTTON1:
		{
			COMDLG_FILTERSPEC Filter[] = { { L"IDB file", L"*.idb" } };
			memset(FileName[0], 0, MAX_PATH);
			getFileName(hDlg, FileName[0], Filter, 1);
			if (FileName[0][0] == '0') break;
			SetWindowTextA(GetDlgItem(hDlg, IDC_EDIT1), FileName[0]);
		}
		break;
		case IDC_BUTTON2:
		{
			GetWindowTextA(GetDlgItem(hDlg, IDC_EDIT1), FileName[0], MAX_PATH);
			IDBData[0].clear();
			openFile(FileName[0], IDBData[0]);
			if (!IDBData[0].empty()) //
			{
				SetIDBPrice(IDBData[0]);
				if (saveFile(FileName[0], IDBData[0]) == 0)
				{
					SetWindowTextA(GetDlgItem(hDlg, IDC_EDITERR1), "Price Set Sucessfull");
				}
				else
				{
					SetWindowTextA(GetDlgItem(hDlg, IDC_EDITERR1), "Failed to Set Price");
				}
			}
			else
			{
				SetWindowTextA(GetDlgItem(hDlg, IDC_EDITERR1), "File Path not found");
			}
		}
		break;
		case IDC_BUTTON3:
		{
			memset(FolderPath, 0, MAX_PATH);
			getFolderPath(hDlg, FolderPath);
			SetWindowTextA(GetDlgItem(hDlg, IDC_EDIT2), FolderPath);
		}
		break;
		case IDC_BUTTON4:
		{
			char IDBName[10][100] = {"accessory_item.idb", "battle_item.idb", "costume_bottom_item.idb", "costume_gloves_item.idb"
				"costume_shoes_item.idb", "costume_top_item.idb", "extra_item.idb", "material_item.idb", "skill_item.idb", "talisman_item.idb"};
			memset(FileName, 0, sizeof(FileName[0][0]) * 20 * MAX_PATH);
			for (int i = 0; i < 10; i++)
			{
				IDBData[i].clear();
				GetWindowTextA(GetDlgItem(hDlg, IDC_EDIT2), FileName[i], MAX_PATH);
				strcat_s(FileName[i], "\\");
				strcat_s(FileName[i], IDBName[i]);
				openFile(FileName[i], IDBData[i]);
				SetIDBPrice(IDBData[i]);
				saveFile(FileName[i], IDBData[i]);
			}
			SetWindowTextA(GetDlgItem(hDlg, IDC_EDITERR2), "Finish Setting Prices");
			
		}
		break;
		}
		return (INT_PTR)TRUE;
	}
	return (INT_PTR)FALSE;
}

LRESULT CALLBACK WndProcEditControl(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DROPFILES:
	{
		GetWindowTextA(GetDlgItem(hDlg, IDC_EDIT1), FileName[0], MAX_PATH);
		SetWindowTextA(GetDlgItem(hDlg, IDC_EDIT1), FileName[0]);
	}
	break;
	default:
		//here we route non drag & drop messages to the original procedure
		return CallWindowProc(WndProcEditDefault, hDlg, msg, wParam, lParam);
		break;
	}
	//return fodder
	return DefWindowProc(hDlg, msg, wParam, lParam);
}
