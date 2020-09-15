#include "Header.h"
#include "MSGCS.h"
#include <vector>
//#using <XV2Lib.dll>
#include <vcclr.h>  

XV2Lib::MSG^ MSG_Read(char* filePathC, int *MSGAmount)
{
	String^ filePath = Marshal::PtrToStringAnsi((IntPtr)filePathC);
	XV2Lib::MSG^ file = XV2Lib::MSGStream::Read(filePath); //static class method

	*MSGAmount = file->data->Length;

	return file;
}

void MSG_Write(char* filePathC, XV2Lib::MSG^ file)
{
	String^ filePath = Marshal::PtrToStringAnsi((IntPtr)filePathC);
	XV2Lib::MSGStream::Write(file, filePath); //static class method
}

void LoadMSGID(char* filePathC, int *MSGAmount, int msg)
{
	switch (msg)
	{
	case 1:
		MSGID::NameMSGIDCS = MSG_Read(filePathC, MSGAmount);
		break;
	case 2:
		MSGID::NameMSGIDCS1 = MSG_Read(filePathC, MSGAmount);
		break;
	case 3:
		MSGID::DescMSGIDCS = MSG_Read(filePathC, MSGAmount);
		break;
	case 4:
		MSGID::DescMSGIDCS1 = MSG_Read(filePathC, MSGAmount);;
		break;
	}
}

bool SaveMSG(char* filePathC, int msg)
{
	switch (msg)
	{
	case 1:
		MSG_Write(filePathC, MSGID::NameMSGIDCS);
		break;
	case 2:
		MSG_Write(filePathC, MSGID::NameMSGIDCS1);
		break;
	case 3:
		MSG_Write(filePathC, MSGID::DescMSGIDCS);
		break;
	case 4:
		MSG_Write(filePathC, MSGID::DescMSGIDCS1);
		break;
	}
	return true;
}

void SetMSG(int index, wchar_t* data, int msg)
{
	int count = 0;
	array<String^>^ cString = gcnew array<String^>(1);
	if (lstrcmpW(data, L"") == 0) return;
	
	cString[0] = Marshal::PtrToStringUni((IntPtr)data);

	switch (msg)
	{
	case 1:
		MSGID::NameMSGIDCS->data[index]->Lines = cString;
		break;
	case 2:
		MSGID::NameMSGIDCS1->data[index]->Lines = cString;
		break;
	case 3:
		MSGID::DescMSGIDCS->data[index]->Lines = cString;
		break;
	case 4:
		MSGID::DescMSGIDCS1->data[index]->Lines = cString;
		break;
	}
}

LPSTR GetNameID(int index, int msg)
{
	LPSTR temp = " ";

	switch (msg)
	{
	case 1:
		temp = (char*)(void*)Marshal::StringToHGlobalAnsi(MSGID::NameMSGIDCS->data[index]->NameID);
		break;
	case 2:
		temp = (char*)(void*)Marshal::StringToHGlobalAnsi(MSGID::NameMSGIDCS1->data[index]->NameID);
		break;
	case 3:
		temp = (char*)(void*)Marshal::StringToHGlobalAnsi(MSGID::DescMSGIDCS->data[index]->NameID);
		break;
	case 4:
		temp = (char*)(void*)Marshal::StringToHGlobalAnsi(MSGID::DescMSGIDCS1->data[index]->NameID);
		break;
	}
	
	return temp;
}

LPWSTR GetLines(int index, int msg)
{
	int count = 1;
	array<String^>^ cstring;
	LPWSTR data = L" ", temp;

	switch (msg)
	{
	case 1:
		cstring = gcnew array<String^>(MSGID::NameMSGIDCS->data[index]->Lines->Length);
		count = MSGID::NameMSGIDCS->data[index]->Lines->Length;
		data = (wchar_t*)(void*)Marshal::StringToHGlobalUni(MSGID::NameMSGIDCS->data[index]->Lines[0]);
		break;
	case 2:
		cstring = gcnew array<String^>(MSGID::NameMSGIDCS1->data[index]->Lines->Length);
		count = MSGID::NameMSGIDCS1->data[index]->Lines->Length;
		data = (wchar_t*)(void*)Marshal::StringToHGlobalUni(MSGID::NameMSGIDCS1->data[index]->Lines[0]);
		break;
	case 3:
		cstring = gcnew array<String^>(MSGID::DescMSGIDCS->data[index]->Lines->Length);
		count = MSGID::DescMSGIDCS->data[index]->Lines->Length;
		data = (wchar_t*)(void*)Marshal::StringToHGlobalUni(MSGID::DescMSGIDCS->data[index]->Lines[0]);
		break;
	case 4:
		cstring = gcnew array<String^>(MSGID::DescMSGIDCS1->data[index]->Lines->Length);
		count = MSGID::DescMSGIDCS1->data[index]->Lines->Length;
		data = (wchar_t*)(void*)Marshal::StringToHGlobalUni(MSGID::DescMSGIDCS1->data[index]->Lines[0]);
		break;
	}

	for (int i = 1; i < count; i++)
	{
		switch (msg)
		{
		case 1:
			temp = (wchar_t*)(void*)Marshal::StringToHGlobalUni(MSGID::NameMSGIDCS->data[index]->Lines[i]);
			data = lstrcatW(data, temp);
			break;
		case 2:
			temp = (wchar_t*)(void*)Marshal::StringToHGlobalUni(MSGID::NameMSGIDCS1->data[index]->Lines[i]);
			data = lstrcatW(data, temp);
			break;
		case 3:
			temp = (wchar_t*)(void*)Marshal::StringToHGlobalUni(MSGID::DescMSGIDCS->data[index]->Lines[i]);
			data = lstrcatW(data, temp);
			break;
		case 4:
			temp = (wchar_t*)(void*)Marshal::StringToHGlobalUni(MSGID::DescMSGIDCS1->data[index]->Lines[i]);
			data = lstrcatW(data, temp);
			break;
		}
	}
	return data;
}

int GetID(int index, int msg)
{
	switch (msg)
	{
	case 1:
		return MSGID::NameMSGIDCS->data[index]->ID;
		break;
	case 2:
		return MSGID::NameMSGIDCS1->data[index]->ID;
		break;
	case 3:
		return MSGID::DescMSGIDCS->data[index]->ID;
		break;
	case 4:
		return MSGID::DescMSGIDCS1->data[index]->ID;
		break;
	}

	return -1;
}

bool isMSGLoaded(int msg)
{
	switch (msg)
	{
	case 1:
		if (MSGID::NameMSGIDCS != nullptr)
		return true;
		break;
	case 2:
		if (MSGID::NameMSGIDCS1 != nullptr)
		return true;
		break;
	case 3:
		if (MSGID::DescMSGIDCS != nullptr)
		return true;
		break;
	case 4:
		if (MSGID::DescMSGIDCS1 != nullptr)
		return true;
		break;
	}
	return false;
}

std::string MarshalString(String ^string)
{
	const char* converted;
	converted = (const char*)Marshal::StringToHGlobalAnsi(string).ToPointer();
	return std::string(converted);
}