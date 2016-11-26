#pragma once
#include "Header.h"

HWND CreateTabControl(HWND hwndParent, HINSTANCE hInstance, int numTab, TCHAR** TabLabel);//TCHAR** means *TCHAR Label[]= {L"", L"", L""}
HWND CreateTabDisplayWindow(HWND hwndTab, HINSTANCE hInstance);
void hideWindow(HWND *hwndDisplay);
BOOL OnNotify(HWND hwndTab, HWND *hwndDisplay, LPARAM lParam, HINSTANCE hInstance);
HRESULT OnSize(HWND hwndTab, LPARAM lParam);
void DialogResize(HWND hwnd, HWND hDlg);
void TabAuraUI();
INT_PTR CALLBACK MainDialogProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
