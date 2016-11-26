#include "Header.h"

HWND CreateTabControl(HWND hwndParent, HINSTANCE hInstance, int numTab, TCHAR** TabLabel)
{
	RECT rcClient;
	INITCOMMONCONTROLSEX icex;
	HWND hwndTab;
	TC_ITEMHEADER tabInfo;

	//Initialize common control
	icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
	icex.dwICC = ICC_TAB_CLASSES;

	//Get Dimensions of parent client area and create child tab window of same size
	GetClientRect(hwndParent, &rcClient);
	hwndTab = CreateWindow(WC_TABCONTROL, L"", WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE, 0, 0, rcClient.right, rcClient.bottom, hwndParent,
							NULL, hInstance, NULL);
	if (hwndTab == NULL)
	{
		return NULL;
	}
	int count = 0;
		while (count < numTab)
		{
			//mbtowc(WTemp, Temp, strlen(Temp));// +1 is to include null character
			tabInfo.mask = TCIF_TEXT;
			tabInfo.iImage = -1;
			tabInfo.pszText = TabLabel[count];
			SendMessage(hwndTab, TCM_INSERTITEM, count, (LPARAM)&tabInfo);
			count++;
		}
	return hwndTab;
}

HWND CreateTabDisplayWindow(HWND hwndTab, HINSTANCE hInstance)
{
	// Creates a child window (a static control) to occupy the tab control's display area. 
	// Returns the handle to the static control. 
	// hwndTab - handle of the tab control. 
	RECT rc;
	GetClientRect(hwndTab, &rc);

	HWND hwndTabStatic = CreateWindow(WC_STATIC, L"", WS_CHILD | WS_VISIBLE | SS_BITMAP | SS_CENTERIMAGE,
		                               0, 20, rc.right, rc.bottom - 20, hwndTab, NULL, hInstance, NULL);
	if (hwndTab == NULL)
	{
		return NULL;
	}

	return hwndTabStatic;
}

HRESULT OnSize(HWND hwndTab, LPARAM lParam)
{
	RECT rc;

	if (hwndTab == NULL)
		return E_INVALIDARG;

	GetClientRect(hwndTab, &rc);

	// Resize the tab control to fit the client are of main window.
	//if (!SetWindowPos(hwndTab, HWND_TOP, 0, 0, rc.bottom, rc.right, SWP_SHOWWINDOW))
		return E_FAIL;

	return S_OK;
}


BOOL OnNotify(HWND hwndTab, HWND *hwndDisplay, LPARAM lParam, HINSTANCE hInstance)
{
	// Handles notifications from the tab control, as follows: 
	//   TCN_SELCHANGING - always returns FALSE to allow the user to select a different tab.  
	//   TCN_SELCHANGE - loads a string resource and displays it in a static control on the selected tab.
	// hwndTab - handle of the tab control.
	// hwndDisplay - handle of the static control. 
	// lParam - the lParam parameter of the WM_NOTIFY message.

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
		int iPage = TabCtrl_GetCurSel(hwndTab);
		switch (iPage)
		{
		case 0:
		{
			//TabAuraUI();
			ShowWindow(hwndDisplay[ActiveTab], SW_HIDE);
			ShowWindow(hwndDisplay[0], SW_SHOWNORMAL);
			UpdateWindow(hwndDisplay[0]);
			ActiveTab = iPage;
		}
			break;
		case 1:	
		{
			ShowWindow(hwndDisplay[ActiveTab], SW_HIDE);
			ShowWindow(hwndDisplay[1], SW_SHOWNORMAL);
			UpdateWindow(hwndDisplay[1]);
			ActiveTab = iPage;
		}
			break;
		case 2:
		{
			ShowWindow(hwndDisplay[ActiveTab], SW_HIDE);
			ShowWindow(hwndDisplay[2], SW_SHOW);
			UpdateWindow(hwndDisplay[1]);
			ActiveTab = iPage;
			
		}
			break;
		}
	}
	break;
	}
	return TRUE;
}

void DialogResize(HWND Rect, HWND hDlg)
{
	RECT rcClient;
	GetClientRect(Rect, &rcClient);
	SetWindowPos(hDlg, NULL, 0, 20, rcClient.right, rcClient.bottom - 20, NULL);
}

void hideWindow( HWND *hwndDisplay)
{
	int count = 0;
	while (count <= sizeof(hwndDisplay) / sizeof(hwndDisplay[0]) )
	{
		ShowWindow(hwndDisplay[count], SW_HIDE);
		count++;
	}
}

