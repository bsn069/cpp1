#pragma once

#include <bsn_cpp/plug_gate/src/udp_server.h>

#include <memory>

D_BsnNamespace1(plug_gate)
//////////////////////////////////////////////////////////////////////
class C_Plug;

class C_Gate : public std::enable_shared_from_this<C_Gate> {
public:
	typedef std::shared_ptr<C_Gate> T_SPC_Gate;	
	typedef std::shared_ptr<C_Plug> T_SPC_Plug;	
    typedef uint32_t T_Id;

public:
	static C_Gate::T_SPC_Gate NewC_Gate(C_Gate::T_SPC_Plug spC_Plug);

	C_Gate::T_SPC_Gate GetSPC_Gate();

public:
	C_Gate(C_Gate::T_SPC_Plug spC_Plug);
	~C_Gate();

public:
    C_Gate::T_SPC_Plug m_spC_Plug;
    C_Gate::T_Id m_id;
};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End