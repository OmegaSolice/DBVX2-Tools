#pragma once

#include <vcclr.h> 
using namespace System;
using namespace System::Text;
using namespace System::Collections::Generic;
using namespace System::IO;
using namespace System::Runtime::InteropServices;
using namespace cli;

namespace XV2Lib
{
	public ref struct msgData
	{
		System::String^ NameID;
		int ID;
		array<System::String^>^ Lines;
	};

	public ref class MSG
	{
	public:
		int type;
		array<msgData^>^ data;

		System::String^ Find(System::String^ id)
		{
			for each (msgData ^ m in data)
			{
				if (m->NameID == id)
					return m->Lines[0];
			}
			return "";
		}

		System::String^ Find(int id)
		{
			for each (msgData ^ m in data)
			{
				if (m->ID == id)
					return m->Lines[0];
			}
			return "";
		}

		System::String^ FindByPart(System::String^ id)
		{
			for each (msgData ^ m in data)
			{
				if (m->NameID->Contains(id))
					return m->Lines[0];
			}
			return "";
		}

		List<String^>^ FindAllByPart(System::String^ id)
		{
			List<String^>^ found = gcnew List<String^>(data->Length);
			for each (msgData ^ m in data)
			{
				if (m->NameID->Contains(id))
					found->Add(m->Lines[0]);
			}
			return found;
		}
	};

	public ref class MSGStream
	{
	public:
		static MSG^ Read(System::String^ FilePath)
		{
			MSG^ file = gcnew MSG();
			FileStream^ fs = gcnew FileStream(FilePath, FileMode::Open);
			BinaryReader^ br = gcnew BinaryReader(fs);
			{;
			br->BaseStream->Seek(4, SeekOrigin::Begin);
			file->type = br->ReadInt16();
			br->BaseStream->Seek(2, SeekOrigin::Current);
			file->data = gcnew array<msgData^>(br->ReadInt32());

			//read NameID
			int startaddress = br->ReadInt32();
			for (int i = 0; i < file->data->Length; i++)
			{
				br->BaseStream->Seek(startaddress + (i * 16), SeekOrigin::Begin);
				int textaddress = br->ReadInt32();
				br->BaseStream->Seek(4, SeekOrigin::Current);
				int charCount = br->ReadInt32();
				br->BaseStream->Seek(textaddress, SeekOrigin::Begin);
				file->data[i] = gcnew msgData;
				if (file->type == 256)
					file->data[i]->NameID = Encoding::Unicode->GetString(br->ReadBytes(charCount - 2));
				else
					file->data[i]->NameID = Encoding::ASCII->GetString(br->ReadBytes(charCount - 1));
			}

			// read ID
			br->BaseStream->Seek(16, SeekOrigin::Begin);
			startaddress = br->ReadInt32();
			for (int i = 0; i < file->data->Length; i++)
			{
				br->BaseStream->Seek(startaddress + (i * 4), SeekOrigin::Begin);
				file->data[i]->ID = br->ReadInt32();
			}

			//read lines
			br->BaseStream->Seek(20, SeekOrigin::Begin);
			startaddress = br->ReadInt32();
			int address;
			for (int i = 0; i < file->data->Length; i++)
			{
				br->BaseStream->Seek(startaddress + (i * 8), SeekOrigin::Begin);
				file->data[i]->Lines = gcnew array<System::String^>(br->ReadInt32());
				address = br->ReadInt32();
				int address2;
				for (int j = 0; j < file->data[i]->Lines->Length; j++)
				{
					br->BaseStream->Seek(address + (j * 16), SeekOrigin::Begin);
					address2 = br->ReadInt32();
					br->BaseStream->Seek(4, SeekOrigin::Current);
					int charCount = br->ReadInt32();
					br->BaseStream->Seek(address2, SeekOrigin::Begin);
					file->data[i]->Lines[j] = Encoding::Unicode->GetString(br->ReadBytes(charCount - 2));
				}
			}

			for (int i = 0; i < file->data->Length; i++)
			{
				for (int j = 0; j < file->data[i]->Lines->Length; j++)
				{
					file->data[i]->Lines[j] = file->data[i]->Lines[j]->Replace("&apos;", "'");
				}
			}

			}
			br->Close();
			fs->Close();
			return file;
		}

		static void Write(MSG ^ file, System::String ^ FilePath)
		{
			for (int i = 0; i < file->data->Length; i++)
			{
				for (int j = 0; j < file->data[i]->Lines->Length; j++)
				{
					file->data[i]->Lines[j] = file->data[i]->Lines[j]->Replace("'", "&apos;");
				}
			}

			//MessageBox.Show("setup");
			int byteCount = 0;
			int TopLength = 32;
			int Mid1Length = file->data->Length * 16;
			int Mid2Length = file->data->Length * 4;
			int Mid3Length = file->data->Length * 8;
			int lineCount = 0;
			for (int i = 0; i < file->data->Length; i++)
				lineCount += file->data[i]->Lines->Length;
			int Mid4Length = lineCount * 16;
			byteCount = TopLength + Mid1Length + Mid2Length + Mid3Length + Mid4Length;
			array<byte> ^ fileData1 = gcnew array<byte>(byteCount);
			List<byte> ^ fileDataText = gcnew List<byte>();
			int TopStart = 0;
			int Mid1Start = 32;
			int Mid2Start = Mid1Start + Mid1Length;
			int Mid3Start = Mid2Start + Mid2Length;
			int Mid4Start = Mid3Start + Mid3Length;
			int LastStart = Mid4Start + Mid4Length;
			//MessageBox.Show("setup");
			//generate top
			fileData1[0] = 0x23; fileData1[1] = 0x4D; fileData1[2] = 0x53; fileData1[3] = 0x47;
			if (file->type == 256)
			{
				fileData1[4] = 0x00; fileData1[5] = 0x01; fileData1[6] = 0x01; fileData1[7] = 0x00;
			}
			else
			{
				fileData1[4] = 0x00; fileData1[5] = 0x00; fileData1[6] = 0x01; fileData1[7] = 0x00;
			}

			array<byte>^ pass;
			pass = BitConverter::GetBytes(file->data->Length);
			Applybyte(fileData1, pass, 8, 4);
			pass = BitConverter::GetBytes(32);
			Applybyte(fileData1, pass, 12, 4);
			pass = BitConverter::GetBytes(Mid2Start);
			Applybyte(fileData1, pass, 16, 4);
			pass = BitConverter::GetBytes(Mid3Start);
			Applybyte(fileData1, pass, 20, 4);
			pass = BitConverter::GetBytes(file->data->Length);
			Applybyte(fileData1, pass, 24, 4);
			pass = BitConverter::GetBytes(Mid4Start);
			Applybyte(fileData1, pass, 28, 4);
			//MessageBox.Show("setup 1");
			//generate Mid section 1
			for (int i = 0; i < file->data->Length; i++)
			{
				Applybyte(fileData1,
					GenWordsBytes(file->data[i]->NameID, file->type == 256, fileDataText, LastStart),
					Mid1Start + (i * 16),
					16);
			}
			//MessageBox.Show("setup 2");
			//generate Mid section 2
			for (int i = 0; i < file->data->Length; i++)
			{
				Applybyte(fileData1, BitConverter::GetBytes(file->data[i]->ID), Mid2Start + (i * 4), 4);
			}
			//MessageBox.Show("setup 3 4");
			//generate Mid section 3 & 4
			int ListCount = 0;
			int address3;
			for (int i = 0; i < file->data->Length; i++)
			{
				address3 = Mid4Start + (ListCount * 16);
				for (int j = 0; j < file->data[i]->Lines->Length; j++)
				{
					Applybyte(fileData1,
						GenWordsBytes(file->data[i]->Lines[j], true, fileDataText, LastStart),
						Mid4Start + (ListCount * 16),
						16);
					ListCount++;
				}
				Applybyte(fileData1, BitConverter::GetBytes(file->data[i]->Lines->Length), Mid3Start + (i * 8), 4);
				Applybyte(fileData1, BitConverter::GetBytes(address3), Mid3Start + (i * 8) + 4, 4);
			}
			//MessageBox.Show("setup final");
			List<byte>^ finalize = gcnew List<byte>();
			finalize->AddRange(fileData1);
			finalize->AddRange(fileDataText);

			FileStream^ fs = gcnew FileStream(FilePath, FileMode::Create);
			fs->Write(finalize->ToArray(), 0, finalize->Count);
			fs->Close();

		}

		static void Applybyte(array<byte> ^ file, array<byte> ^ data, int pos, int count)
		{
			for (int i = 0; i < count; i++)
				file[pos + i] = data[i];
		}

		static array<byte>^ GenWordsBytes(System::String ^ Line, bool type256, List<byte> ^ text, int bCount)
		{

			array<byte>^ charArray;
			if (type256)
			{
				charArray = gcnew array<byte>((Line->Length + 1) * 2);
				charArray = Encoding::Unicode->GetBytes(Line + "\0");

			}
			else
			{
				charArray = gcnew array<byte>(Line->Length + 1);
				charArray = Encoding::ASCII->GetBytes(Line + "\0");
			}

			array<byte> ^ AddressInfo = { 0x00, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x00 };
			Applybyte(AddressInfo, BitConverter::GetBytes(bCount + text->Count), 0, 4); //address of text
			Applybyte(AddressInfo, BitConverter::GetBytes(Line->Length), 4, 4);
			Applybyte(AddressInfo, BitConverter::GetBytes(charArray->Length), 8, 4);

			text->AddRange(charArray);

			return AddressInfo;
		}

	};
}

ref class MSGID
{
public:
	static XV2Lib::MSG^ NameMSGIDCS, ^ NameMSGIDCS1, ^ DescMSGIDCS, ^ DescMSGIDCS1;
};
//void MSG_Read(char* filePathC, XV2Lib::MSG^ file, int *MSGAmount);
void LoadMSGID(char* filePathC, int *MSGAmount, int msg);
void SetMSG(int index, wchar_t* data, int msg);
LPSTR GetNameID(int index, int msg);
LPWSTR GetLines(int index, int msg);
bool isMSGLoaded(int msg);
int GetID(int index, int msg);
bool SaveMSG(char* filePathC, int msg);
XV2Lib::MSG^ MSG_Read(char* filePathC, int* MSGAmount);
void MSG_Write(char* filePathC, XV2Lib::MSG^ file);
std::string MarshalString(System::String^ string);



