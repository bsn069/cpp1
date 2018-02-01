#pragma once

#include "./../include/i_plug_base64.h"

#include <boost/function.hpp>

#include <map>

D_BsnNamespace1(plug_base64)
//////////////////////////////////////////////////////////////////////
class C_PlugBase64 : public I_PlugBase64 {
public:
	typedef std::shared_ptr<C_PlugBase64> T_SPC_PlugBase64;	

public: // I_Plug
	virtual char const * const GetName() const override;

	virtual bool Awake() override;
	virtual bool Init(T_SPI_PlugMgr spI_PlugMgr) override;
	virtual bool AllInitAfter() override;
	virtual bool Update() override;
	virtual bool Quit() override;
	virtual bool UnInit() override;

	virtual void ProcCmd(std::string const& strNet) {};

	virtual void OnReloadPre(std::string const& strName) override;
	virtual void OnReloadPost(std::string const& strName) override;

public: // I_PlugBase64
	virtual bool Encode(std::string const& strInput, std::string& strOut) override;  
	virtual bool Decode(std::string const& strInput, std::string& strOut) override;  

public:
	static T_SPC_PlugBase64 NewC_PlugBase64(void* pData);
	static T_SPI_PlugBase64 NewI_PlugBase64(void* pData);

	T_SPC_PlugBase64 GetSPC_PlugBase64();
	bool RegAllCmd();

public:  
	void CmdHelp(bool bShowHelp, std::string const& strParam);
    void CmdEncode(bool bShowHelp, std::string const& strParam);
    void CmdDecode(bool bShowHelp, std::string const& strParam);
public:
	C_PlugBase64(void* pData);
	virtual ~C_PlugBase64();

public:
	T_SPI_PlugMgr 	m_spI_PlugMgr;
};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End