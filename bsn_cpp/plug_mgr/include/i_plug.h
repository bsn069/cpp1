#pragma once

#include <bsn_cpp/include/name_space.h>

#include <boost/function.hpp>

#include <stdint.h>
#include <memory>
#include <string>
#include <set>

D_BsnNamespace1(plug_mgr)
//////////////////////////////////////////////////////////////////////
class I_PlugMgr;

/*
dll must has symbol CreatePlug like T_CreatePlug
*/
class I_Plug : public std::enable_shared_from_this<I_Plug> {
public:
	typedef std::shared_ptr<I_Plug>     T_SPI_Plug;
	typedef std::shared_ptr<I_PlugMgr>  T_SPI_PlugMgr;
	typedef T_SPI_Plug	(T_CreatePlug)(void*);
	typedef boost::function<void(bool, std::string const&)> T_FuncCmd;


public:
	virtual char const * const GetName() const = 0;

	// call on load after 
	// not need any plug
	virtual bool OnLoad(std::set<std::string>& needPlugNames) { return true; }
	virtual bool Init(T_SPI_PlugMgr spI_PlugMgr) {
        m_spI_PlugMgr = spI_PlugMgr;
        return true;
    }
	virtual bool AllInitAfter() {
        InitNeedPlug();
        RegAllCmd();
        return true;
    }
	virtual bool Update() { return true; }
	virtual bool Quit() { return true; }
	virtual bool UnInit() {
        ClearNeedPlug();
        return true;
    }

	virtual bool CanReload(std::string const& strName) { return false; }
	virtual void OnReloadPre(std::string const& strName) {
        ClearNeedPlug();
    }
	virtual void OnReloadPost(std::string const& strName) {
        InitNeedPlug();
        if (strName.compare("cmd") == 0) {
            RegAllCmd();
        }
    }

	virtual void ProcCmd(std::string const& strCmd) {}

    virtual bool InitNeedPlug() { return true; }
    virtual bool ClearNeedPlug() { return true; }

    virtual void RegPlugCmd(std::string const& strCmd, T_FuncCmd funcCmd) = 0;
	virtual bool RegAllCmd() { 
        RegPlugCmd("help", boost::bind(&I_Plug::CmdHelp, this, _1, _2));
        return true;
    }
	virtual void CmdHelp(bool bShowHelp, std::string const& strParam) {};

	T_SPI_Plug GetSPI_Plug() {
		return shared_from_this();
	}
	T_SPI_PlugMgr GetSPI_PlugMgr() {
		return m_spI_PlugMgr;
	}

public:
	virtual ~I_Plug() = default;

protected:
	T_SPI_PlugMgr 	m_spI_PlugMgr;
};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End

