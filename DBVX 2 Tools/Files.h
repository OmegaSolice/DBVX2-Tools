#pragma once
void getFileName(HWND hwnd, char szFileName[MAX_PATH], COMDLG_FILTERSPEC *Filter, int numFilter); //Creates dialog to get file name
void getFolderPath(HWND hwnd, char szFolderPath[MAX_PATH]);
void openFile(char szfilename[MAX_PATH], std::string &Output); //Opens file in biinary format
int saveFile(char szfilename[MAX_PATH], std::string Input);  //Saves file in binary format