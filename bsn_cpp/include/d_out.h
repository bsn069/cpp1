#pragma once

#include <iostream>

#ifdef D_OutInfoOpen

	#define D_OutInfo() \
		std::cout << __FILE__ << ":" << __LINE__ << "(" << __FUNCTION__ << ") " << std::endl 

	#define D_OutInfo1(strLog1) \
		std::cout << __FILE__ << ":" << __LINE__ << "(" << __FUNCTION__ << ") " << strLog1 << std::endl 

	#define D_OutInfo2(strLog1, strLog2) \
		std::cout << __FILE__ << ":" << __LINE__ << "(" << __FUNCTION__ << ") " << strLog1 << " " << strLog2 << std::endl 

	#define D_OutInfo3(strLog1, strLog2, strLog3) \
		std::cout << __FILE__ << ":" << __LINE__ << "(" << __FUNCTION__ << ") " << strLog1  << " " << strLog2 << " " << strLog3 << std::endl 

#else

	#define D_OutInfo()
	#define D_OutInfo1(strLog1)
	#define D_OutInfo2(strLog1, strLog2)
	#define D_OutInfo3(strLog1, strLog2, strLog3)

#endif
