#pragma once

#include <memory>

D_BsnNamespace1(plug_node)
//////////////////////////////////////////////////////////////////////
class C_Node;

class C_Parent : public std::enable_shared_from_this<C_Parent> {
public:
	typedef std::shared_ptr<C_Parent>   T_SPC_Parent;	
	typedef std::shared_ptr<C_Node>     T_SPC_Node;	
    typedef uint32_t T_Id;

public:
	static C_Parent::T_SPC_Parent NewC_Parent(C_Parent::T_SPC_Node spC_Node);

	C_Parent::T_SPC_Parent GetSPC_Parent();

public:
	C_Parent(C_Parent::T_SPC_Node spC_Node);
	~C_Parent();

public:
    C_Parent::T_SPC_Node m_spC_Node;
    C_Parent::T_Id m_id;
};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End