#include "Hex.h"

float HexToFloat(std::string SHex)
{
	union {
		char c[4];
		float f;
	}u;

	const char *Hex = SHex.c_str();

	u.c[0] = Hex[0];
	u.c[1] = Hex[1];
	u.c[2] = Hex[2];
	u.c[3] = Hex[3];

	return u.f;
}

std::string FloatToHex(float floatNum)
{
	union {
		char c[4];
		float f;
	}u;

	u.f = floatNum;
	std::string Output(u.c, 4);
	Output.resize(4);
	return Output;
}