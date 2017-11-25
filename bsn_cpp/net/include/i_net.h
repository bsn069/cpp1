#pragma once
#include "i_session.h"

#include <bsn_cpp/log/include/i_log.h>

#include <bsn_cpp/include/name_space.h>
#include <bsn_cpp/include/define.h>

#include <memory>
 
D_BsnNamespace1(net)
//////////////////////////////////////////////////////////////////////
class I_Net
{
public:
	typedef std::shared_ptr<I_Net> T_SPI_Net;
	typedef std::function<void(T_SPI_Session)> T_FuncOnAccept;
	typedef std::function<void(T_SPI_Session)> T_FuncOnConnect;
	
public:
	virtual void SetLog(D_N1(log)::I_Log::T_SPI_Log iLog) = 0;

	virtual bool Listen(std::string const& strIp, uint16_t u16Port, T_FuncOnAccept func) = 0;
	virtual bool Connect(std::string const& strIp, uint16_t u16Port, T_FuncOnConnect func) = 0;
};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End


