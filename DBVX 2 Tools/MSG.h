#pragma once
struct MSGDATA
{
	int ID;
	std::string NameID;
	std::string Info;
	int startLength;
	int endLength;
	int stringStartID1;
	int stringStartID2;
};
void LoadMSG(std::string MSGData, MSGDATA *MSGInfo, int *MSGAmount);
void NormalizeMSG(std::string &NewString); //sets it back to how it was in MSG file
int SetMSG(std::string OTemp, std::string NTemp, int index, std::string &MSGData, MSGDATA* MSGID);
