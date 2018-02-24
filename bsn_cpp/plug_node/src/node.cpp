#include <bsn_cpp/plug_node/src/node.h>
#include <bsn_cpp/plug_node/src/parent.h>
#include <bsn_cpp/plug_node/src/child.h>
#include <bsn_cpp/plug_node/src/plug.h>

#include <bsn_cpp/include/d_out.h>

#include <boost/bind.hpp>

D_BsnNamespace1(plug_node)
//////////////////////////////////////////////////////////////////////
C_Node::C_Node(C_Node::T_SPC_Plug spC_Plug, C_Node::T_SPI_Address spI_AddressListen, C_Node::T_Id id) 
    : m_spC_Plug(spC_Plug) 
    , m_id(id)
    , m_spI_AddressListen(spI_AddressListen) 
{
	D_OutInfo();

}

C_Node::~C_Node() {
	D_OutInfo();

    UnInit();
}

int C_Node::Init() {
    D_OutInfo1(GetId());
    int iRet = 0;

	m_spC_Parent = C_Parent::NewC_Parent(GetSPC_Node());

	iRet = m_spC_Parent->Init();
	if (iRet < 0) {
		D_OutInfo2("parent init fail, iRet=", iRet);
		return -1;
	}

    return 0;
}

void C_Node::UnInit() {
    D_OutInfo1(GetId());

    m_spC_Parent->UnInit();
}

int C_Node::Stop() {
    D_OutInfo1(GetId());
    // int iRet = 0;

    if (m_spI_TCPListen) {
        D_OutInfo1("stop listen");
        m_spI_TCPListen->StopListen();
    }

    return 0;
}

C_Node::T_SPC_Node C_Node::GetSPC_Node() {
	D_OutInfo();
    return shared_from_this();
}

C_Node::T_SPC_Parent C_Node::GetSPC_Parent() {
	return m_spC_Parent;
}


int C_Node::StartTCPListen() {
	D_OutInfo();

    if (m_spI_TCPListen) {
        if (m_spI_TCPListen->InListen()) {
            D_OutInfo1("had in listen");
            return 1;
        }
    } else {
        auto spI_PlugNet = m_spC_Plug->GetSPI_PlugNet();
        if (!spI_PlugNet) {
            D_OutInfo1("not found plug net");
            return -1;
        }

        D_OutInfo1("new tcp listen");
        m_spI_TCPListen = spI_PlugNet->NewI_TCPListen();
    }

    auto spC_Node = GetSPC_Node();
	m_spI_TCPListen->SetAddress(m_spI_AddressListen);
	m_spI_TCPListen->SetFuncNew(
		boost::bind(&C_Node::FuncNew, spC_Node)
	);
	m_spI_TCPListen->SetFuncOnAccept(
		boost::bind(&C_Node::FuncOnAccept, spC_Node, _1)
	);
	m_spI_TCPListen->StartListen();
	
	return 0;
}

C_Node::T_SPI_TCPSession C_Node::FuncNew() {
    D_OutInfo();

    auto spI_PlugNet = m_spC_Plug->GetSPI_PlugNet();
	if (!spI_PlugNet) {
		return nullptr;
	}

	auto spI_TCPSession = spI_PlugNet->NewI_TCPSession();
	return spI_TCPSession;
}

void C_Node::FuncOnAccept(C_Node::T_SPI_TCPSession spI_TCPSession) {
    D_OutInfo();
}

C_Node::T_Id C_Node::GetId() const {
    return m_id;
}

int C_Node::Start() {
    D_OutInfo1(GetId());
    int iRet = 0;

    iRet = StartTCPListen();
    if (iRet < 0) {
        D_OutInfo2("start tcp listen fail, iRet=", iRet);
        return -1;
    }

    iRet = m_spC_Parent->Start();
    if (iRet < 0) {
        D_OutInfo2("start parent fail, iRet=", iRet);
        return -2;
    }

    return 0;
}

//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End
