#include <bsn_cpp/plug_node/src/parent.h>
#include <bsn_cpp/plug_node/src/plug.h>

#include <bsn_cpp/include/d_out.h>
#include <bsn_cpp/include/new.hpp>
#include <bsn_cpp/include/delete.hpp>

D_BsnNamespace1(plug_node)
//////////////////////////////////////////////////////////////////////
C_Parent::C_Parent(C_Node::T_SPC_Node spC_Node) 
	: m_spC_Node(spC_Node) 
	, m_bStart(false)
	, m_id(0)
	, m_bInit(false)
{
	D_OutInfo();
}

C_Parent::~C_Parent() {
	D_OutInfo();
}

C_Parent::T_SPC_Parent C_Parent::GetSPC_Parent() {
	D_OutInfo();
    return shared_from_this();
}

C_Node::T_Id C_Parent::GetId() const {
	return m_id;
}


int C_Parent::Init() {
	D_OutInfo1(GetId());

	if (m_bInit) {
		D_OutInfo1("had init");
		return 1;
	}

    auto spI_PlugNet = m_spC_Node->m_spC_Plug->GetSPI_PlugNet();
    if (!spI_PlugNet) {
        D_OutInfo1("not found plug net");
		return -1;
	}

	if (!m_spI_TCPConnect) {
		m_spI_TCPConnect    = spI_PlugNet->NewI_TCPConnect();
		if (!m_spI_TCPConnect) {
			D_OutInfo1("new tcp connect fail");
			return -2;
		}
	}

	m_spI_TCPSession  = spI_PlugNet->NewI_TCPSession();
    if (!m_spI_TCPSession) {
        D_OutInfo1("new tcp session for parent fail");
		return -3;
	}
    m_spI_TCPSession->SetType(D_N1(plug_net)::I_TCPSession::E_Type::E_Type_Connect);

	m_bInit = true;
	return 0;
}

bool C_Parent::IsStart() const {
	return m_bStart;
}

int C_Parent::Start() {
	D_OutInfo1(GetId());
	int iRet = 0;

	if (m_bStart) {
		D_OutInfo1("had start");
		return 1;
	}

	iRet = StartConnect();
	if (iRet < 0) {
		D_OutInfo2("Start connect fail, iRet=", iRet);
		return -1;
	}

	m_bStart = true;
	return 0;
}

int C_Parent::Stop() {
	D_OutInfo1(GetId());

	if (!m_bStart) {
		D_OutInfo1("not start");
		return 1;
	}
	
	CloseConnect();

	m_bStart = false;
	return 0;
}

int C_Parent::SetAddr(C_Node::T_SPI_Address spI_Address) {
	D_OutInfo();

	if (!spI_Address) {
		D_OutInfo1("address is null");
		return -1;
	}

	m_spI_Address = spI_Address;
	
	return 0;
}

void C_Parent::UnInit() {
	D_OutInfo1(GetId());

	m_spI_TCPSession = nullptr;
    m_spI_TCPConnect = nullptr;
}

int C_Parent::StartConnect() {
    D_OutInfo1(GetId());
    // int iRet = 0;

    if (!m_spI_TCPConnect->CanConnect(m_spI_TCPSession)) {
        D_OutInfo1("can't connect");
        return -1;
    }

    if (m_spI_Address->GetPort() == 0) {
        D_OutInfo1("not set port");
        return 1;
    }

	m_spI_TCPConnect->Connect(
        m_spI_TCPSession
        , m_spI_Address
        , boost::bind(&C_Parent::OnConncet, GetSPC_Parent(), _1)
    );

    return 0;
}

int C_Parent::CloseConnect() {
    D_OutInfo1(GetId());
    // int iRet = 0;

    m_spI_TCPSession->Close();

    return 0;
}

void C_Parent::OnConncet(C_Node::T_SPI_TCPSession spI_TCPSession) {
    D_OutInfo();
}
//////////////////////////////////////////////////////////////////////
C_Parent* CreateC_Parent(C_Node::T_SPC_Node spC_Node) {
	D_OutInfo();
	C_Parent* pC_Parent = New<C_Parent>(spC_Node);
	return pC_Parent;
}

void ReleaseC_Parent(C_Parent* pC_Parent) {
	D_OutInfo();
	Delete(pC_Parent);
}

C_Parent::T_SPC_Parent C_Parent::NewC_Parent(C_Node::T_SPC_Node spC_Node) {
	D_OutInfo();
	auto pC_Parent = CreateC_Parent(spC_Node);
	auto spC_Parent = C_Parent::T_SPC_Parent(pC_Parent, ReleaseC_Parent);
	return spC_Parent;
}
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End
