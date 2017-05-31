#pragma once

class FBNETWORK_API CFBNetwork_Dg
{
public:
	virtual					~CFBNetwork_Dg(){};

	virtual	DWORD			DataLen(void) = 0;
	virtual char*			Data(void) = 0;
};