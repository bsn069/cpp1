#pragma once

#include <bsn_cpp/include/name_space.h>
#include <bsn_cpp/include/std.h>

#include <stdint.h>
#include <memory>
#include <vector>
#include <string>

D_BsnNamespace1(input)
//////////////////////////////////////////////////////////////////////
class I_Input : public std::enable_shared_from_this<I_Input> {
public:
	typedef std::shared_ptr<I_Input> T_SPI_Input;
	typedef std::vector<std::string> T_Cmds;

public:
	virtual void
		Init() = 0;
	virtual void
		Start() = 0;
	virtual void
		Quit() = 0;
	virtual void
		UnInit() = 0;

	virtual T_Cmds* 
		GetCmds() = 0;

	virtual void 
		DebugInfo() = 0;

protected:
	virtual ~I_Input() = default;
};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End