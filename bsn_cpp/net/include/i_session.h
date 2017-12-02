#pragma once

#include <bsn_cpp/include/name_space.h>
#include <bsn_cpp/include/define.h>

#include <memory>
 
D_BsnNamespace1(net)
//////////////////////////////////////////////////////////////////////
class I_Session : public std::enable_shared_from_this<I_Session>
{
public:
	typedef std::shared_ptr<I_Session> T_SPI_Session;
 	enum E_State : uint8_t
	{
		E_State_Close	= 0,
		E_State_Connecting,
		E_State_Established,
	};
	
public:
	virtual I_Session::E_State 
		GetState() const = 0;
	virtual void 
		Close() = 0;

	virtual bool 
		Send(uint8_t const* pData, uint32_t u32Len) = 0;

protected:
	virtual ~I_Session() = default;
};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End


