#include <bsn_cpp/plug_node/src/plug.h>

#include <bsn_cpp/include/d_out.h>
#include <bsn_cpp/include/new.hpp>
#include <bsn_cpp/include/delete.hpp>

#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

D_BsnNamespace1(plug_node)
//////////////////////////////////////////////////////////////////////
int C_Plug::StartNode(C_Node::T_Id id) {
    D_OutInfo1(id);

    auto spC_Node = GetNode(id);
    if (!spC_Node) {
        D_OutInfo1("not found node");
        return -1;
    }

    auto ret = spC_Node->Start();
    if (ret != 0) {
        D_OutInfo2("node start fail, ret=", ret);
        return -2;
    }
    
    return 0;
}

int C_Plug::NewNode(
    C_Node::T_Id id
    , std::string const& listenAddr
    , uint16_t listenPort
    , std::string const& parentListenAddr
    , uint16_t parentListenPort
) {
    D_OutInfo();

    if (id <= 0) {
        return -1;
    }

    auto spI_PlugNet = GetSPI_PlugNet();
	if (!spI_PlugNet) {
		return -2;
	}

	auto spI_AddressListen = spI_PlugNet->NewI_Address();
	spI_AddressListen->SetAddr(listenAddr);
	spI_AddressListen->SetPort(listenPort);

    auto spC_Node = C_Node::NewC_Node(GetSPC_Plug(), spI_AddressListen, id);
    spC_Node->Init();

	auto spI_AddressParent = spI_PlugNet->NewI_Address();
	spI_AddressParent->SetAddr(parentListenAddr);
	spI_AddressParent->SetPort(parentListenPort);
    spC_Node->SetParentAddr(spI_AddressParent);

    auto ret = AddNode(spC_Node);
    if (ret != 0) {
        D_OutInfo2("AddNode ret=", ret);
        return -3;
    }

    return 0;
}

C_Node::T_SPC_Node C_Plug::GetNode(C_Node::T_Id id) {
    D_OutInfo();

    auto itor = m_Id2Node.find(id);
    if (itor == m_Id2Node.end()) {
        return nullptr;
    }
    return itor->second;
}

int C_Plug::AddNode(C_Node::T_SPC_Node spC_Node) {
    D_OutInfo();

    if (!spC_Node) {
        return -1;
    }

    auto id = spC_Node->GetId();
    if (id < 0) {
        return -2;
    }

    if (GetNode(id)) {
        return -3;
    }

    m_Id2Node[spC_Node->GetId()] = spC_Node;
    return 0;
}
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End
 