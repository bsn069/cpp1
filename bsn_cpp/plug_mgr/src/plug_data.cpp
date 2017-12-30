#include "plug_data.h"

#include <bsn_cpp/include/d_out.h>

D_BsnNamespace1(plug_mgr)
//////////////////////////////////////////////////////////////////////
C_PlugData::C_PlugData(std::string strName) 
	: m_strName(strName) 
{
	D_OutInfo1(m_strName);

}

C_PlugData::~C_PlugData() {
	D_OutInfo1(m_strName);
 
}

bool C_PlugData::LoadLib() {
	return false;
}

bool C_PlugData::LoadPlug() {
	return true;
}

std::string const& C_PlugData::GetName() {
	return m_strName;
}

I_Plug::T_SPI_Plug C_PlugData::GetPlug() {
	return m_spI_Plug;
}


//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End

#if (defined WIN32)

#else
 
#endif