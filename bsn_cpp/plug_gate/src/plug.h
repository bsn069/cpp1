#pragma once

#include <bsn_cpp/plug_gate/src/gate.h>

#include <bsn_cpp/plug_mgr/include/i_plug.h>
#include <bsn_cpp/plug_net/include/i_plug_net.h>
#include <bsn_cpp/plug_cmd/include/i_plug_cmd.h>

D_BsnNamespace1(plug_gate)
//////////////////////////////////////////////////////////////////////
class C_Plug : public D_N1(plug_mgr)::I_Plug {
public:
	typedef std::shared_ptr<C_Plug>                     T_SPC_Plug;	
    typedef D_N1(plug_net)::I_PlugNet::T_SPI_PlugNet    T_SPI_PlugNet;
    typedef D_N1(plug_cmd)::I_PlugCmd::T_SPI_PlugCmd    T_SPI_PlugCmd;
    typedef C_Gate::T_SPC_Gate T_SPC_Gate;
    typedef std::map<C_Gate::T_Id, T_SPC_Gate> T_Id2Gate;

public: // I_Plug
	virtual char const * const GetName() const override;
	virtual bool OnLoad(std::set<std::string>& needPlugNames) override;
    virtual bool InitNeedPlug() override;
    virtual bool ClearNeedPlug() override;
    virtual void RegPlugCmd(std::string const& strCmd, T_FuncCmd funcCmd) override;

public:
	static C_Plug::T_SPC_Plug NewC_Plug(void* pData);
	static I_Plug::T_SPI_Plug NewI_Plug(void* pData);

	C_Plug::T_SPC_Plug      GetSPC_Plug();
    C_Plug::T_SPI_PlugNet   GetSPI_PlugNet();
    C_Plug::T_SPI_PlugCmd   GetSPI_PlugCmd();

    void Cmd(bool bShowHelp, std::string const& strParam);

public:
	C_Plug(void* pData);
	virtual ~C_Plug();

public:
    C_Plug::T_SPI_PlugNet m_spI_PlugNet;
    C_Plug::T_SPI_PlugCmd m_spI_PlugCmd;

    T_Id2Gate m_Id2Gate;
};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End