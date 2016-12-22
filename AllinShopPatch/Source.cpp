#include "Header.h"

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK MainDialogProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
void SetIDBPrice(std::string &IDBData);
HWND hwndDisplay;
char FileName[MAX_PATH], FolderPath[MAX_PATH];
std::string IDBData[20];

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
	int count = 0x20, size = IDBData.size();

	while (count < size)
	{
		if (IDBData[count] == 00 && IDBData[count + 1] == 00)
		{
			IDBData[count] = 01;
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
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		switch (wParam)
		{
		case IDC_BUTTON1:
		{
			COMDLG_FILTERSPEC Filter[] = { { L"IDB file", L"*.idb" } };
			getFileName(hDlg, FileName, Filter, 1);
			IDBData[0].clear();
			openFile(FileName, IDBData[0]);
			SetWindowTextA(GetDlgItem(hDlg, IDC_EDIT1), FileName);
		}
		break;
		case IDC_BUTTON2:
		{
			char TempName[MAX_PATH];
			GetWindowTextA(GetDlgItem(hDlg, IDC_EDIT1), TempName, MAX_PATH);
			if (strcmp(FileName, TempName)) //
			{
				SetIDBPrice(IDBData[0]);
				saveFile(FileName, IDBData[0]);
			}
			else
			{
				*FileName = *TempName;
				SetIDBPrice(IDBData[0]);
				saveFile(FileName, IDBData[0]);
			}
		}
		break;
		case IDC_BUTTON3:
		{
			getFolderPath(hDlg, FolderPath);
			IDBData[0].clear();
			openFile(FolderPath, IDBData[0]);
			SetWindowTextA(GetDlgItem(hDlg, IDC_EDIT1), FolderPath);
		}
		break;
		case IDC_BUTTON4:
		{

		}
		break;
		}
		return (INT_PTR)TRUE;
	}
	return (INT_PTR)FALSE;
}