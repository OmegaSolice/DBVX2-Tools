#include "Header.h"

int main()
{
	char PrimaryFile[MAX_PATH], SecondaryFile[MAX_PATH];
	std::string PrimaryData, SecondaryData;
	int Size = 0, count = 0;

	std::cout << "Enter Primary Path\n";
	std::cin >> PrimaryFile;

	std::cout << "Enter Secondary Path\n";
	std::cin >> SecondaryFile;

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