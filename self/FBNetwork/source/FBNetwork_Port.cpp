#include "../include/FBNetwork_Port.h"

CFBNetwork_Resolve::~CFBNetwork_Resolve()
{
	m_IPs.Release();
}

BOOL CFBNetwork::Init(void)
{
	WSADATA wsd;
	if(WSAStartup(MAKEWORD(2, 2), &wsd) != 0)
	{
		return false;
	}
	return true;
}
void CFBNetwork::Quit(void)
{
	WSACleanup();
}

void CFBNetwork::IPPort2Addr(const char* pIP, WORD wPort, sockaddr_in* pAddr)
{
	pAddr->sin_family = AF_INET;
	pAddr->sin_addr.s_addr = (pIP ? inet_addr(pIP) : htonl(INADDR_ANY));
	pAddr->sin_port = htons(wPort);
}
__int64 CFBNetwork::Addr2Int64(sockaddr_in* pAddr)
{
	return ((__int64)pAddr->sin_addr.S_un.S_addr << 32) | pAddr->sin_port;
}
char* CFBNetwork::Addr2IPPort(sockaddr_in* pAddr, WORD* pPort)
{
	*pPort = ntohs(pAddr->sin_port);
	return inet_ntoa(pAddr->sin_addr);
}

void CFBNetwork::Resolve(char* pIPorDomain, vector<string>* pIPs)
{
	pIPs->clear();

	DWORD dwAddr = inet_addr(pIPorDomain);
	if(dwAddr == INADDR_NONE)
	{
		hostent* pHost;
		pHost = gethostbyname(pIPorDomain);
		if(pHost)
		{
			DWORD dwIP;
			char pIP[16];

			char** pTemp = pHost->h_addr_list;
			for(; *pTemp; pTemp++)
			{
				dwIP = (DWORD)(*(DWORD*)(*pTemp));
				sprintf(
					pIP, 
					"%d.%d.%d.%d", 
					*((BYTE*)&dwIP + 0),
					*((BYTE*)&dwIP + 1),
					*((BYTE*)&dwIP + 2),
					*((BYTE*)&dwIP + 3));

				pIPs->push_back(pIP);
			}
		}
	}
	else
	{
		pIPs->push_back(pIPorDomain);
	}
}
