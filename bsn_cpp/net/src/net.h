#pragma once
#include "./../include/i_net.h"
#include "session.h"
#include <bsn_cpp/log/include/i_Log.h>
#include <bsn_cpp/include/i_init.h>

#include <boost/asio.hpp>

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
		SetLog(D_N1(log)::I_Log::T_SPI_Log spI_Log) override {
			m_spI_Log = spI_Log;
		};
	virtual void 
		SetCommon(D_N1(common)::I_Common::T_SPI_Common spI_Common) override {
			m_spI_Common = spI_Common;
		};
	virtual void 
		SetLib(D_N1(load_lib)::I_Lib::T_SPI_Lib spI_Lib) override {
			m_spI_Lib = spI_Lib;
		};
	virtual bool 
		Connect(
			std::string const& strIp
			, uint16_t u16Port
			, T_FuncOnConnect 
		) override;
	virtual void	
		WaitQuit() override;
	virtual I_Session::T_SPI_Session
		Test() override {
			return nullptr;
		};
public:
	void 
		OnConnect(
			I_Session::T_SPI_Session 	
			, const boost::system::error_code& 		
			, T_FuncOnConnect 			
		);
public:
	C_Net(boost::asio::io_service&);
	virtual ~C_Net();

private:
	boost::asio::io_service&		m_IO;

	D_N1(common)::I_Common::T_SPI_Common 	m_spI_Common;
	D_N1(log)::I_Log::T_SPI_Log m_spI_Log;
	D_N1(load_lib)::I_Lib::T_SPI_Lib m_spI_Lib;
};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End