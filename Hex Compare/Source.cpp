#include "Header.h"

int main()
{
	char * PrimaryFile = new char [MAX_PATH], *SecondaryFile = new char [MAX_PATH];
	std::string PrimaryData, SecondaryData, TempFile;
	int Size = 0, count = 0;

	TempFile.resize(MAX_PATH);
	std::cout << "Enter Primary Path\n";
	getline(std::cin, TempFile);
	std::copy(TempFile.begin(), TempFile.end(), PrimaryFile);

	std::cout << "Enter Secondary Path\n";
	getline(std::cin, TempFile);
	std::copy(TempFile.begin(), TempFile.end(), SecondaryFile);

	openFile(PrimaryFile, PrimaryData);
	openFile(SecondaryFile, SecondaryData);

	std::cout << "Offset\tPrimary\tSecondary\n";
	if (PrimaryData.size() == SecondaryData.size())
	{
		Size = PrimaryData.size();
	}
	else
	{
		if (PrimaryData.size() < SecondaryData.size())
		{
			Size = PrimaryData.size();
		}
		else
		{
			Size = SecondaryData.size();
		}
	}

	while (count < Size)
	{
		if (PrimaryData[count] != SecondaryData[count])
		{
			std::cout << std::hex << count << "\t" << std::hex << PrimaryData[count] << "\t" << SecondaryData[count] << std::endl;
		}
		count++;
	}
	system("PAUSE");
	return 0;
}