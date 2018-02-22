#pragma once

#include <bsn_cpp/plug_node/src/child.h>
#include <bsn_cpp/plug_node/src/parent.h>

#include <bsn_cpp/plug_net/include/i_tcp_listen.h>
#include <bsn_cpp/plug_net/include/i_tcp_session.h>
#include <bsn_cpp/plug_net/include/i_address.h>

#include <bsn_cpp/include/name_space.h>

#include <memory>

D_BsnNamespace1(plug_node)
//////////////////////////////////////////////////////////////////////
class C_Plug;

class C_Node : public std::enable_shared_from_this<C_Node> {
public:
	typedef std::shared_ptr<C_Node> T_SPC_Node;	
	typedef std::shared_ptr<C_Plug> T_SPC_Plug;	
    typedef uint32_t T_Id;
    typedef std::map<C_Child::T_Id, C_Child::T_SPC_Child> T_Id2Child;
	typedef D_N1(plug_net)::I_TCPListen::T_SPI_TCPListen T_SPI_TCPListen;
	typedef D_N1(plug_net)::I_TCPSession::T_SPI_TCPSession T_SPI_TCPSession;
	typedef D_N1(plug_net)::I_TCPConnect::T_SPI_TCPConnect T_SPI_TCPConnect;
	typedef D_N1(plug_net)::I_Address::T_SPI_Address T_SPI_Address;

public:
    C_Node::T_Id GetId() const;
    bool SetParentAddr(C_Node::T_SPI_Address spI_AddressParent);

    int Init();
    int Start();
    int Stop();
    int UnInit();
    
    int StartTCPListen();
    int StartConnectParent();

public:
	static C_Node::T_SPC_Node NewC_Node(C_Node::T_SPC_Plug spC_Plug, C_Node::T_SPI_Address spI_AddressListen, C_Node::T_Id id);

	C_Node::T_SPC_Node GetSPC_Node();

    C_Node::T_SPI_TCPSession FuncNew();
    void FuncOnAccept(C_Node::T_SPI_TCPSession spI_TCPSession);



public:
	C_Node(C_Node::T_SPC_Plug spC_Plug, C_Node::T_SPI_Address spI_AddressListen, C_Node::T_Id id);
	~C_Node();

public:
    C_Node::T_SPC_Plug      m_spC_Plug;
    C_Node::T_Id            m_id;
    C_Parent::T_SPC_Parent  m_spC_Parent;
    C_Node::T_Id2Child      m_Id2Child;

    C_Node::T_SPI_TCPListen m_spI_TCPListen;
    C_Node::T_SPI_Address   m_spI_AddressListen;

    C_Node::T_SPI_TCPConnect    m_spI_TCPConnect;
    C_Node::T_SPI_Address       m_spI_AddressParent;
    C_Node::T_SPI_TCPSession    m_spI_TCPSessionParent;
};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End