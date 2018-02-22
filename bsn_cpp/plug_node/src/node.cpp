#include <bsn_cpp/plug_node/src/node.h>
#include <bsn_cpp/plug_node/src/plug.h>

#include <bsn_cpp/include/d_out.h>

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

    auto spI_PlugNet = m_spC_Plug->GetSPI_PlugNet();
    if (!spI_PlugNet) {
        D_OutInfo1("not found plug net");
		return -1;
	}

	m_spI_TCPConnect    = spI_PlugNet->NewI_TCPConnect();
    if (!m_spI_TCPConnect) {
        D_OutInfo1("new tcp connect fail");
		return -2;
	}

	m_spI_TCPSessionParent  = spI_PlugNet->NewI_TCPSession();
    if (!m_spI_TCPSessionParent) {
        D_OutInfo1("new tcp session for parent fail");
		return -3;
	}
    m_spI_TCPSessionParent->SetType(D_N1(plug_net)::I_TCPSession::E_Type::E_Type_Connect);

    return 0;
}

int C_Node::UnInit() {
    D_OutInfo1(GetId());
    int iRet = 0;

    m_spI_TCPSessionParent = nullptr;
    m_spI_TCPConnect = nullptr;

    return 0;
}

int C_Node::Stop() {
    D_OutInfo1(GetId());
    int iRet = 0;

    if (m_spI_TCPListen) {
        D_OutInfo1("stop listen");
        m_spI_TCPListen->StopListen();
    }

    if (m_spI_TCPSessionParent) {
        m_spI_TCPSessionParent->Close();
    }

    return 0;
}

C_Node::T_SPC_Node C_Node::GetSPC_Node() {
	D_OutInfo();
    return shared_from_this();
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

bool C_Node::SetParentAddr(C_Node::T_SPI_Address spI_AddressParent) {
    D_OutInfo();

    m_spI_AddressParent = spI_AddressParent;
    return true;
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

    iRet = StartConnectParent();
    if (iRet < 0) {
        D_OutInfo2("start connect parent fail, iRet=", iRet);
        return -2;
    }

    return 0;
}

int C_Node::StartConnectParent() {
    D_OutInfo1(GetId());
    int iRet = 0;

    if (!m_spI_TCPConnect->CanConnect(m_spI_TCPSessionParent)) {
        D_OutInfo1("can't connect");
        return -1;
    }

    if (m_spI_AddressParent->GetPort() == 0) {
        D_OutInfo1("not set parent port");
        return 1;
    }

	m_spI_TCPConnect->Connect(
        m_spI_TCPSessionParent
        , m_spI_AddressParent
        , boost::bind(&C_Node::OnConncetParent, GetSPC_Node(), _1)
    );

    return 0;
}

int C_Node::CloseParentConnect() {
    D_OutInfo1(GetId());
    int iRet = 0;

    m_spI_TCPSessionParent->Close();

    return 0;
}

void C_Node::OnConncetParent(C_Node::T_SPI_TCPSession spI_TCPSession) {
    D_OutInfo();
}
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End
