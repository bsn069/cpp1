#pragma once

#include <bsn_cpp/include/name_space.h>

#include <stdint.h>
#include <memory>

namespace N_Bsn {
	namespace N_global {
		class I_Global;
	}
}

D_BsnNamespace1(load_lib)
//////////////////////////////////////////////////////////////////////


class I_Lib : public std::enable_shared_from_this<I_Lib> {
public:
	typedef std::shared_ptr<I_Lib> T_SPI_Lib;
	
public:
	virtual void* 		
		Func(const char* strFuncName) = 0;
	virtual const char* 
		Name() = 0;
	virtual D_N1(global)::I_Global* 	
		GetGlobal() = 0;

protected:
	virtual ~I_Lib() = default;
};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End