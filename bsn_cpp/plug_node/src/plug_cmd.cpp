#include <bsn_cpp/plug_node/src/plug.h>

#include <bsn_cpp/include/d_out.h>
#include <bsn_cpp/include/new.hpp>
#include <bsn_cpp/include/delete.hpp>

#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

D_BsnNamespace1(plug_node)
//////////////////////////////////////////////////////////////////////
bool C_Plug::RegAllCmd() { 
    I_PlugNode::RegAllCmd();

    RegPlugCmd("NewNode", boost::bind(&C_Plug::CmdNewNode, this, _1, _2));
    RegPlugCmd("NewTestNode", boost::bind(&C_Plug::CmdNewTestNode, this, _1, _2));
    RegPlugCmd("ListNode", boost::bind(&C_Plug::CmdListNode, this, _1, _2));
    RegPlugCmd("CDNode", boost::bind(&C_Plug::CmdCDNode, this, _1, _2));
    RegPlugCmd("CurNode", boost::bind(&C_Plug::CmdCurNode, this, _1, _2));
    RegPlugCmd("StartNode", boost::bind(&C_Plug::CmdStartNode, this, _1, _2));
    RegPlugCmd("StopNode", boost::bind(&C_Plug::CmdStopNode, this, _1, _2));
    RegPlugCmd("SetParentNode", boost::bind(&C_Plug::CmdSetParentNode, this, _1, _2));
    RegPlugCmd("ConncetParentNode", boost::bind(&C_Plug::CmdConncetParentNode, this, _1, _2));
    RegPlugCmd("CloseParentNode", boost::bind(&C_Plug::CmdCloseParentNode, this, _1, _2));

    return true;
}

void C_Plug::RegPlugCmd(std::string const& strCmd, T_FuncCmd funcCmd) {
    D_OutInfo();

	GetSPI_PlugCmd()->RegPlugCmd(GetName(), strCmd, funcCmd);
}

void C_Plug::CmdNewNode(bool bShowHelp, std::string const& strParam) {
    D_OutInfo();

    if (bShowHelp) {
        D_OutInfo1("new node");
        D_OutInfo1("param: id listenIP listenPort parentListenAddr parentListenPort");
        return;
    }

    std::vector<std::string> params;
    boost::algorithm::split(params, strParam, boost::algorithm::is_any_of(" "), boost::token_compress_on);
    if (params.size() != 5) {
        return CmdNewNode(true, strParam);
    }

    auto id = boost::lexical_cast<C_Node::T_Id>(params[0]);
    auto& listenAddr = params[1];
    auto listenPort = boost::lexical_cast<uint16_t>(params[2]);
    auto& parentListenAddr = params[3];
    auto parentListenPort = boost::lexical_cast<uint16_t>(params[4]);
    
    auto ret = NewNode(id, listenAddr, listenPort, parentListenAddr, parentListenPort);
    if (ret != 0) {
        D_OutInfo2("NewNode ret=", ret);
    }
}

void C_Plug::CmdNewTestNode(bool bShowHelp, std::string const& strParam) {
    D_OutInfo();

    if (bShowHelp) {
        D_OutInfo1("new test node, addr is localhost");
        D_OutInfo1("param: id listenPort parentListenPort");
        return;
    }

    std::vector<std::string> params;
    boost::algorithm::split(params, strParam, boost::algorithm::is_any_of(" "), boost::token_compress_on);
    if (params.size() != 3) {
        return CmdNewTestNode(true, strParam);
    }

    auto id = boost::lexical_cast<C_Node::T_Id>(params[0]);
    auto listenPort = boost::lexical_cast<uint16_t>(params[1]);
    auto parentListenPort = boost::lexical_cast<uint16_t>(params[2]);
    
    auto ret = NewNode(id, "localhost", listenPort, "localhost", parentListenPort);
    if (ret != 0) {
        D_OutInfo2("NewNode ret=", ret);
    }
}

void C_Plug::CmdSetParentNode(bool bShowHelp, std::string const& strParam) {
    D_OutInfo();

    if (bShowHelp) {
        D_OutInfo1("set cur cmd node's parent node addr");
        D_OutInfo1("param: parentListAddr parentListenPort");
        return;
    }

    std::vector<std::string> params;
    boost::algorithm::split(params, strParam, boost::algorithm::is_any_of(" "), boost::token_compress_on);
    if (params.size() != 2) {
        return CmdNewNode(true, strParam);
    }

    auto spC_Node = GetNode(m_nodeIdForCmd);
    if (!spC_Node) {
        D_OutInfo1("not found cur cmd node");
        return;
    }

    auto& parentListenAddr  = params[0];
    auto parentListenPort   = boost::lexical_cast<uint16_t>(params[1]);
 
    auto spI_PlugNet = GetSPI_PlugNet();
    auto spI_AddressParent = spI_PlugNet->NewI_Address();
	spI_AddressParent->SetAddr(parentListenAddr);
	spI_AddressParent->SetPort(parentListenPort);
    spC_Node->SetParentAddr(spI_AddressParent);
}

void C_Plug::CmdConncetParentNode(bool bShowHelp, std::string const& strParam) {
    D_OutInfo();
    int iRet = 0;

    if (bShowHelp) {
        D_OutInfo1("connect cur cmd node's parent node");
        return;
    }

    auto spC_Node = GetNode(m_nodeIdForCmd);
    if (!spC_Node) {
        D_OutInfo1("not found cur cmd node");
        return;
    }

    iRet = spC_Node->StartConnectParent();
    if (iRet < 0) {
        D_OutInfo2("start connect parent node fail, iRet=", iRet);
        return;
    }
}

void C_Plug::CmdCloseParentNode(bool bShowHelp, std::string const& strParam) {
    D_OutInfo();
    int iRet = 0;

    if (bShowHelp) {
        D_OutInfo1("close cur cmd node's parent node");
        return;
    }

    auto spC_Node = GetNode(m_nodeIdForCmd);
    if (!spC_Node) {
        D_OutInfo1("not found cur cmd node");
        return;
    }

    iRet = spC_Node->CloseParentConnect();
    if (iRet < 0) {
        D_OutInfo2("close parent connect fail, iRet=", iRet);
        return;
    }
}

void C_Plug::CmdListNode(bool bShowHelp, std::string const& strParam) {
    D_OutInfo();

    if (bShowHelp) {
        D_OutInfo1("show all node");
        return;
    }
 
    for (auto& pair : m_Id2Node) {
        D_OutInfo2("id=", pair.first);
    }
}

void C_Plug::CmdCDNode(bool bShowHelp, std::string const& strParam) {
    D_OutInfo();

    if (bShowHelp) {
        D_OutInfo1("enter node with id");
        return;
    }
 
    auto id = boost::lexical_cast<C_Node::T_Id>(strParam);
    m_nodeIdForCmd = id;
}

void C_Plug::CmdCurNode(bool bShowHelp, std::string const& strParam) {
    D_OutInfo();

    if (bShowHelp) {
        D_OutInfo1("show cur cmd use node id");
        return;
    }
 
    D_OutInfo2("cur cmd use node id=", m_nodeIdForCmd);
}

void C_Plug::CmdStartNode(bool bShowHelp, std::string const& strParam) {
    D_OutInfo();
    int iRet = 0;

    if (bShowHelp) {
        D_OutInfo1("start cur cmd node");
        return;
    }
  
    auto spC_Node = GetNode(m_nodeIdForCmd);
    if (!spC_Node) {
        D_OutInfo1("not found cur cmd node");
        return;
    }

    iRet = spC_Node->Start();
    if (iRet < 0) {
        D_OutInfo2("start node fail, iRet=", iRet);
        return;
    }
}

void C_Plug::CmdStopNode(bool bShowHelp, std::string const& strParam) {
    D_OutInfo();
    int iRet = 0;

    if (bShowHelp) {
        D_OutInfo1("stop cur cmd node");
        return;
    }
  
    auto spC_Node = GetNode(m_nodeIdForCmd);
    if (!spC_Node) {
        D_OutInfo1("not found cur cmd node");
        return;
    }

    iRet = spC_Node->Stop();
    if (iRet < 0) {
        D_OutInfo2("stop node fail, iRet=", iRet);
        return;
    }
}
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End
 