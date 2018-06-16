#pragma once

//#include <vcclr.h>  


//void MSG_Read(char* filePathC, XV2Lib::MSG^ file, int *MSGAmount);
void LoadMSGID(char* filePathC, int *MSGAmount, int msg);
void SetMSG(int index, wchar_t* data, int msg);
LPSTR GetNameID(int index, int msg);
LPWSTR GetLines(int index, int msg);
bool isMSGLoaded(int msg);
int GetID(int index, int msg);
bool SaveMSG(char* filePathC, int msg);


