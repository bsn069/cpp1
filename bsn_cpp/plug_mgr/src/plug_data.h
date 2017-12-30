#pragma once

#include "./../include/i_plug.h"
 
#include <boost/dll.hpp>

#include <string>

D_BsnNamespace1(plug_mgr)
//////////////////////////////////////////////////////////////////////
class C_PlugData {
public:
	bool LoadLib();
	bool LoadPlug();

	std::string const& GetName();
	I_Plug::T_SPI_Plug GetPlug();

public:
	C_PlugData(std::string strName);
	~C_PlugData();

public:
	std::string 				m_strName;
	I_Plug::T_SPI_Plug 			m_spI_Plug;
	boost::dll::shared_library 	m_lib;
};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End