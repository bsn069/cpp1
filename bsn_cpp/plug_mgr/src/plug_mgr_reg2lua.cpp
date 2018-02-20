#include <bsn_cpp/plug_mgr/src/plug_mgr.h>
#include <bsn_cpp/third_part/LuaBridge/Source/LuaBridge/LuaBridge.h>

D_BsnNamespace1(plug_mgr)
//////////////////////////////////////////////////////////////////////
void C_PlugMgr::Reg2Lua(lua_State* pLuaState) {
	D_OutInfo();

	using namespace luabridge;

	getGlobalNamespace(pLuaState)
	.beginClass<C_PlugMgr>("C_PlugMgr")
		.addFunction("GetFrameMS", &C_PlugMgr::GetFrameMS)
		.addFunction("ProcCmd", &C_PlugMgr::ProcCmd)
		.addData("m_u32FrameMS", &C_PlugMgr::m_u32FrameMS)
		.addData("m_waitReloadPlug", &C_PlugMgr::m_waitReloadPlug)
		.addData("m_strConfigFile", &C_PlugMgr::m_strConfigFile)
		.addData("m_strConfigFile", &C_PlugMgr::m_strConfigFile)
	.endClass();
}
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End