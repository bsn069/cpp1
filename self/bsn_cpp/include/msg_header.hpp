#pragma once

namespace N_Bsn
{
 
	template<typename T_ID, typename T_Len>
	class C_MsgHeader
	{
	public:
		T_ID	m_ID;
		// �ܳ���(����C_MsgHeader)
		T_Len	m_Len;
	};


} // end namespace NBSN

 