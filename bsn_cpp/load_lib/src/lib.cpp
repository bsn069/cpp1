#include "load_lib.h"

#include <bsn_cpp/log/include/i_log.h>

D_BsnNamespace1(load_lib)
//////////////////////////////////////////////////////////////////////
C_Lib::C_Lib() {
	m_dllHandle = nullptr;
}


C_Lib::~C_Lib() {
	D_LogInfoF(
		m_iLog
		, "lib_%p name=%s"
		, this
		, Name()
	);
	this->Close();
}

char const * 
C_Lib::Name( ) {
	return m_strName.c_str();
}


void 	
C_Lib::SetName(char const * const pstrName) {
	m_strName = pstrName;
	D_LogInfoF(
		m_iLog
		, "lib_%p Name=%s"
		, this
		, Name()
	);
};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End


#if (defined WIN32)

#else
	#include "./linux/lib.ipp"
#endif
