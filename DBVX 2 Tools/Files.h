#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <windows.h>
#include <shobjidl.h>

void getFileName(HWND hwnd, char szFileName[MAX_PATH], COMDLG_FILTERSPEC *Filter, int numFilter); //Creates dialog to get file name
void getFolderPath(HWND hwnd, char szFolderPath[MAX_PATH]);
void openFile(char szfilename[MAX_PATH], std::string &Output); //Opens file in biinary format
int saveFile(char szfilename[MAX_PATH], std::string Input);  //Saves file in binary format
void openFileW(char szfilename[MAX_PATH], std::wstring &Output); //Opens file in biinary format
int saveFileW(char szfilename[MAX_PATH], std::wstring Input);  //Saves file in binary format