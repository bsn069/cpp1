#pragma once
#include "i_session.h"

#include <bsn_cpp/log/include/i_log.h>
#include <bsn_cpp/common/include/i_common.h>

#include <bsn_cpp/include/name_space.h>
#include <bsn_cpp/include/define.h>

#include <memory>
 
D_BsnNamespace1(net)
//////////////////////////////////////////////////////////////////////
class I_Net
{
public:
	typedef std::shared_ptr<I_Net> T_SPI_Net;
	typedef std::function<void(I_Session::T_SPI_Session)> T_FuncOnConnect;
	
public:
	virtual void 
		SetLog(D_N1(log)::I_Log::T_SPI_Log) = 0;
	virtual void 
		SetCommon(D_N1(common)::I_Common::T_SPI_Common) = 0;

	virtual bool 
		Connect(
			std::string const& strIp
			, uint16_t u16Port
			, T_FuncOnConnect 
		) = 0;
	virtual void		
		WaitQuit() = 0;

protected:
	virtual ~I_Net() = default;
};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End


