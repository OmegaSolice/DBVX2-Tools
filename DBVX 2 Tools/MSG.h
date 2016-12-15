#pragma once
void LoadMSG(std::string MSGData, MSGDATA *MSGInfo, int mode);
void NormalizeMSG(std::string &NewString); //sets it back to how it was in MSG file
int SetMSG(std::string OTemp, std::string NTemp, int index, std::string &MSGData, MSGDATA* MSGID);
