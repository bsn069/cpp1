#pragma once

class CFBNetwork_A;
class FBNETWORK_API CFBNetwork_A_Socket : public enable_shared_from_this<CFBNetwork_A_Socket>
{
public:
	typedef shared_ptr<CFBNetwork_A_Socket> Ptr;

public:
	enum STATE
	{
		S_CLOSE								= 0,
		S_WATTINGORCONNECTING,
		S_ESTABLISHED,
	};

public:
	#ifdef _DEBUG
	char*									m_pTemp;
	#endif

	ip::tcp::socket							m_Socket;
	CFBKernel_Double<CFBNetwork_A_Dg*>		m_Dgs;							// 可以供上层读取的Dg

	CFBNetwork_A_Dg*						m_pSendDg;						// 攒大包

	STATE volatile							m_State;						// 状态

	// 地址
	ip::address								m_Local;
	ip::address								m_Remote;

	// 流量
	LONG volatile							m_lFluxOut;

public:
	void									Read(void);

	void									OnRead(CFBNetwork_A_Dg* pDg, const error_code &Error, size_t Bytes);
	void									OnWrite(CFBNetwork_A_Dg* pDg, const error_code& Error, size_t Bytes);

	long const	FluxOut(void){ return InterlockedExchangeAdd(&m_lFluxOut, 0); };

public:
											CFBNetwork_A_Socket(CFBNetwork_A* pA);
	virtual									~CFBNetwork_A_Socket();

	BOOL									Send(char* pBuffer, DWORD dwLen);
	BOOL									Recv(CFBNetwork_Stuff* pStuff);

	BOOL									End(void);

	STATE									State(void);

};