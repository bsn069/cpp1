#pragma once

#include <bsn_cpp/include/name_space.h>

#include <stdint.h>
#include <memory>
#include <string>

D_BsnNamespace1(plug_mgr)
//////////////////////////////////////////////////////////////////////
class I_Plug : public std::enable_shared_from_this<I_Plug> {
public:
	typedef std::shared_ptr<I_Plug> T_SPI_Plug;
	
public:
	virtual void Awake() = 0;
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void UnInit() = 0;

public:
	virtual ~I_Plug() = default;
};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End