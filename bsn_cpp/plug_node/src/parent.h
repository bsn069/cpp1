#pragma once

#include <bsn_cpp/plug_node/src/node.h>

#include <bsn_cpp/include/name_space.h>

#include <memory>

D_BsnNamespace1(plug_node)
//////////////////////////////////////////////////////////////////////
class C_Parent : public std::enable_shared_from_this<C_Parent> {
public:
	typedef std::shared_ptr<C_Parent>   T_SPC_Parent;	

public:
    C_Node::T_Id GetId() const;
    int SetAddr(C_Node::T_SPI_Address spI_Address);

    int Init();
    int Start();
    int Stop();
    void UnInit();

	int StartConnect();
    int CloseConnect();
	void OnConncet(C_Node::T_SPI_TCPSession spI_TCPSession);

public:
	static C_Parent::T_SPC_Parent NewC_Parent(C_Node::T_SPC_Node spC_Node);

	C_Parent::T_SPC_Parent GetSPC_Parent();

public:
	C_Parent(C_Node::T_SPC_Node spC_Node);
	~C_Parent();

public:
    C_Node::T_SPC_Node m_spC_Node;
    C_Node::T_Id m_id;

	C_Node::T_SPI_TCPConnect    m_spI_TCPConnect;
    C_Node::T_SPI_Address       m_spI_Address;
    C_Node::T_SPI_TCPSession    m_spI_TCPSession;
};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End