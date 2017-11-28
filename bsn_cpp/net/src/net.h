#pragma once
#include "./../include/i_net.h"
#include "session.h"
#include <bsn_cpp/log/include/i_Log.h>
#include <bsn_cpp/include/i_init.h>

#include <bsn_cpp/include/buffer.hpp>
#include <bsn_cpp/include/ring_buffer.hpp>
#include <asio.hpp>
#include <atomic>
#include <thread>
D_BsnNamespace1(net)
//////////////////////////////////////////////////////////////////////

class C_Net : public I_Net, public I_Init
{
public:
	typedef std::shared_ptr<C_Net> T_SharePtrCNet;
	typedef C_Session::T_SharePtrCSession T_SharePtrCSession;
	typedef std::list<T_SharePtrCSession> T_AcceptSession;
	typedef D_N1(log)::I_Log::T_SharePtr T_SharePtrLog;

public:
	virtual bool Listen(std::string strIp, uint16_t u16Port) override;
	virtual T_SharePtrISession GetAcceptSession() override;
	virtual T_SharePtrISession Connect(std::string strIp, uint16_t u16Port) override;
	
	virtual void Init() override;
	virtual void UnInit() override;
	virtual void SetCommon(D_N1(common)::T_SPI_Common spI_Common) override {
		m_spI_Common = spI_Common;
	};

public: 
	void PostAccept();
	void OnAccept(T_SharePtrCSession Session, const asio::error_code& error);

	void OnConnect(T_SharePtrCSession Session, const asio::error_code& error);

	void Run();

	void 	SetLog(T_SharePtrLog pLog) {
		m_pLog = pLog;
	};

public:
	C_Net();
	virtual ~C_Net();

private:
	D_N1(common)::T_SPI_Common m_spI_Common;
	asio::io_service		m_IO;
	asio::io_service::work	m_Work;
	asio::ip::tcp::acceptor	m_Acceptor;
	std::atomic<bool> 		m_bAccepting;

	T_AcceptSession m_Accepts;
	std::vector<std::thread*> m_workThread;
	T_SharePtrLog m_pLog;
};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End