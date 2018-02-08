#pragma once

#include <bsn_cpp/plug_mgr/include/i_plug.h>
#include <bsn_cpp/plug_mgr/include/i_plug_mgr.h>
#include <bsn_cpp/plug_mgr/include/i_plug_data.h>


#include <boost/dll.hpp>

#include <string>
#include <map>

D_BsnNamespace1(plug_mgr)
//////////////////////////////////////////////////////////////////////
class C_PlugData {
public:
	typedef std::shared_ptr<C_PlugData> T_SPC_PlugData;	
	typedef I_PlugData* (*T_FuncCreatePlugData)(I_PlugMgr::T_SPI_PlugMgr);
	typedef std::map<std::string, T_FuncCreatePlugData> T_Name2FuncCreatePlugData;
 
public:
	bool LoadLib();
	bool UnLoadLib();
	
	bool LoadPlug();
	bool UnLoadPlug();

	std::string const& GetName();
	I_Plug::T_SPI_Plug GetPlug();

	static bool RegPlugData();

public:
	C_PlugData(std::string strName, I_PlugMgr::T_SPI_PlugMgr spI_PlugMgr);
	~C_PlugData();

public:
	std::string 				m_strName;
	I_Plug::T_SPI_Plug 			m_spI_Plug;
	boost::dll::shared_library 	m_lib;
	I_PlugData* 				m_pData;
	static T_Name2FuncCreatePlugData m_Name2FuncCreatePlugData;
};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End