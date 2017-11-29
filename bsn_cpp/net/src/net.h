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

class C_Net : public I_Net 
{
public:
	typedef std::shared_ptr<C_Net> T_SPC_Net;

public:
	virtual void 
		SetLog(D_N1(log)::I_Log::T_SPI_Log) override {
			m_pLog = pLog;
		};
	virtual void 
		SetCommon(D_N1(common)::T_SPI_Common) override {
			m_spI_Common = spI_Common;
		};

	virtual bool 
		Connect(
			std::string const& strIp
			, uint16_t u16Port
			, T_FuncOnConnect 
		) override;

public:
	C_Net(asio::io_service&);
	virtual ~C_Net();

private:
	asio::io_service&		m_IO;

	D_N1(common)::T_SPI_Common 	m_spI_Common;
	D_N1(log)::I_Log::T_SPI_Log m_spI_Log;
};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End