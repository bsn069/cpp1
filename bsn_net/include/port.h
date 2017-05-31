#pragma once

class ISocket
{
public:
	virtual bool Send(int8_t* pData, uint32_t uLen) =0;
}