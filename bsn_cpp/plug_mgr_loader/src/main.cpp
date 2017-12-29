#include <bsn_cpp/plug_mgr/include/port.h>
#include <bsn_cpp/include/name_space.h>

int main(int argc, char* argv[]) {
	D_N1(plug_mgr)::I_PlugMgr::T_SPI_PlugMgr 
		spI_PlugMgr = D_N1(plug_mgr)::NewPlugMgr();
	spI_PlugMgr->Run();
	spI_PlugMgr = nullptr;
}
