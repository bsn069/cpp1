#pragma once

#include <bsn_cpp/include/name_space.h>

#include <memory>

D_BsnNamespace1(plug_node)
//////////////////////////////////////////////////////////////////////
class C_Node;

class C_Child : public std::enable_shared_from_this<C_Child> {
public:
	typedef std::shared_ptr<C_Child>    T_SPC_Child;	
	typedef std::shared_ptr<C_Node>     T_SPC_Node;	
    typedef uint32_t T_Id;

public:
	static C_Child::T_SPC_Child NewC_Child(C_Child::T_SPC_Node spC_Node);

	C_Child::T_SPC_Child GetSPC_Child();

public:
	C_Child(C_Child::T_SPC_Node spC_Node);
	~C_Child();

public:
    C_Child::T_SPC_Node m_spC_Node;
    C_Child::T_Id m_id;
};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End