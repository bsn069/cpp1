#pragma once


#define D_BsnNamespace1(strModNameSpaceName) \
namespace N_Bsn\
{\
	namespace N_##strModNameSpaceName\
	{

#define D_BsnNamespace1End \
	}\
}


#define D_BsnNamespace2(strModNameSpaceName, strNameSpaceName) \
namespace N_Bsn\
{\
	namespace N_##strModNameSpaceName\
	{\
		namespace N_##strNameSpaceName\
		{

#define D_BsnNamespace2End \
		}\
	}\
}


#define D_BsnNamespace3(strModNameSpaceName, strNameSpaceName, strSubName) \
namespace N_Bsn \
{ \
	namespace N_##strModNameSpaceName \
	{ \
		namespace N_##strNameSpaceName \
		{ \
			namespace N_##strSubName \
				{ 

#define D_BsnNamespace3End \
				}\
		}\
	}\
}


#define D_N1(strModNameSpaceName) N_Bsn::N_##strModNameSpaceName
#define D_N2(strModNameSpaceName, strNameSpaceName) N_Bsn::N_##strModNameSpaceName::N_##strNameSpaceName
#define D_N3(strModNameSpaceName, strNameSpaceName, strSubName) N_Bsn::N_##strModNameSpaceName::N_##strNameSpaceName::N_##strSubName
