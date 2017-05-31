#pragma once

#ifdef FBNETWORK_EXPORTS
#define FBNETWORK_API __declspec(dllexport)
#else
#define FBNETWORK_API __declspec(dllimport)
#endif

#include "../../FBKernel/include/FBKernel_Port.h"

#include <winsock2.h>
#include <mswsock.h>
#include <mstcpip.h>

class FBNETWORK_API CFBNetwork_Resolve
{
public:
	CFBKernel_Vector<string>	m_IPs;

public:
	virtual						~CFBNetwork_Resolve();
};

class FBNETWORK_API CFBNetwork
{
public:
	static BOOL Init(void);
	static void Quit(void);

	static void IPPort2Addr(const char* pIP, WORD wPort, sockaddr_in* pAddr);
	static __int64 Addr2Int64(sockaddr_in* pAddr);
	static char* Addr2IPPort(sockaddr_in* pAddr, WORD* pPort);

	static void Resolve(char* pIPorDomain, vector<string>* pIPs);
};

#include "boost/shared_ptr.hpp"
#include "boost/enable_shared_from_this.hpp"

#include "asio.hpp"
using namespace asio;

#include "FBNetwork_Dg.h"
#include "FBNetwork_Stuff.h"
#include "FBNetwork_Parser.h"

#include "FBNetwork_A_Dg.h"
#include "FBNetwork_A_Socket.h"
#include "FBNetwork_A.h"

#include "FBNetwork_T_Dg.h"
#include "FBNetwork_T_Socket.h"
#include "FBNetwork_T.h"

#include "FBNetwork_U_SEQ.h"
#include "FBNetwork_U_Dg.h"
#include "FBNetwork_U_Flux.h"
#include "FBNetwork_U_IS.h"
#include "FBNetwork_U_OS.h"
#include "FBNetwork_U_Socket.h"
#include "FBNetwork_U.h"

#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "mswsock.lib")
