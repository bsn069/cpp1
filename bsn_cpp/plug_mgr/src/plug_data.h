#pragma once

#include "./../include/i_plug.h"
#include "./../include/i_plug_mgr.h"
 
#include <boost/dll.hpp>

#include <string>

D_BsnNamespace1(plug_mgr)
//////////////////////////////////////////////////////////////////////
class C_PlugData {
public:
	typedef std::shared_ptr<C_PlugData> T_SPC_PlugData;	

public:
	bool LoadLib();
	bool UnLoadLib();
	
	bool LoadPlug();
	bool UnLoadPlug();

	std::string const& GetName();
	I_Plug::T_SPI_Plug GetPlug();

	bool Awake();
	bool Init(I_PlugMgr::T_SPI_PlugMgr spI_PlugMgr);
	bool AllInitAfter();
	bool Update();
	bool Quit();
	bool UnInit();

	void OnReloadPre(std::string const& strName);
	void OnReloadPost(std::string const& strName);

public:
	C_PlugData(std::string strName);
	~C_PlugData();

public:
	std::string 				m_strName;
	I_Plug::T_SPI_Plug 			m_spI_Plug;
	boost::dll::shared_library 	m_lib;
	void* m_pData;
	
};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End