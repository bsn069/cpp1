#pragma once

#include <bsn_cpp/plug_node/include/i_plug_node.h>
#include <bsn_cpp/plug_node/src/node.h>

#include <bsn_cpp/plug_mgr/include/i_plug.h>
#include <bsn_cpp/plug_net/include/i_plug_net.h>
#include <bsn_cpp/plug_cmd/include/i_plug_cmd.h>

#include <bsn_cpp/include/name_space.h>

D_BsnNamespace1(plug_node)
//////////////////////////////////////////////////////////////////////
class C_Plug : public I_PlugNode {
public:
	typedef std::shared_ptr<C_Plug>                     T_SPC_Plug;	
    typedef D_N1(plug_net)::I_PlugNet::T_SPI_PlugNet    T_SPI_PlugNet;
    typedef D_N1(plug_cmd)::I_PlugCmd::T_SPI_PlugCmd    T_SPI_PlugCmd;
    typedef std::map<C_Node::T_Id, C_Node::T_SPC_Node>  T_Id2Node;

public: // I_Plug
	virtual char const * const GetName() const override;
	virtual bool OnLoad(std::set<std::string>& needPlugNames) override;
    virtual bool InitNeedPlug() override;
    virtual bool ClearNeedPlug() override;
    virtual void RegPlugCmd(std::string const& strCmd, T_FuncCmd funcCmd) override;
	virtual bool RegAllCmd() override;
	virtual bool Quit() override;
	virtual bool UnInit() override;

public: // I_PlugNode

public: // cmd
    void CmdNewNode(bool bShowHelp, std::string const& strParam);
    void CmdNewTestNode(bool bShowHelp, std::string const& strParam);
    void CmdListNode(bool bShowHelp, std::string const& strParam);
    void CmdCDNode(bool bShowHelp, std::string const& strParam);
    void CmdCurNode(bool bShowHelp, std::string const& strParam);
    void CmdStartNode(bool bShowHelp, std::string const& strParam);
    void CmdStopNode(bool bShowHelp, std::string const& strParam);
    void CmdSetParentNode(bool bShowHelp, std::string const& strParam);
    void CmdConncetParentNode(bool bShowHelp, std::string const& strParam);
    void CmdCloseParentNode(bool bShowHelp, std::string const& strParam);

public: // get plug
	static C_Plug::T_SPC_Plug NewC_Plug(void* pData);
	static I_Plug::T_SPI_Plug NewI_Plug(void* pData);

	C_Plug::T_SPC_Plug      GetSPC_Plug();
    C_Plug::T_SPI_PlugNet   GetSPI_PlugNet();
    C_Plug::T_SPI_PlugCmd   GetSPI_PlugCmd();

public: // 
    int NewNode(
        C_Node::T_Id id
        , std::string const& listenAddr
        , uint16_t listenPort
        , std::string const& parentListenAddr
        , uint16_t parentListenPort
    );
    C_Node::T_SPC_Node GetNode(C_Node::T_Id id);
    int AddNode(C_Node::T_SPC_Node spC_Node);
    int StartNode(C_Node::T_Id id);
    

public:
	C_Plug(void* pData);
	virtual ~C_Plug();

public: // dependent plug
    C_Plug::T_SPI_PlugNet m_spI_PlugNet;
    C_Plug::T_SPI_PlugCmd m_spI_PlugCmd;

public:
    C_Plug::T_Id2Node m_Id2Node;
    C_Node::T_Id m_nodeIdForCmd;
};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End