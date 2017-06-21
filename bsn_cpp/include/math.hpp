#pragma once
#include "define.h"

namespace N_Bsn
{

/*判断一个数是否为2的次幂
若n为2的次幂，则n和n-1的二进制各个位肯定不同 (如8(1000)和7(0111))，&出来的结果肯定是0
如果n不为2的次幂，则各个位肯定有相同的 (如7(0111) 和6(0110))，&出来结果肯定为0
*/
bool IsPowOf2(uint32_t n)
{
	return (n != 0 && ((n & (n - 1)) == 0));
}

/** 
 * fls - find last bit set 
 * @x: the word to search 
 * 
 * This is defined the same way as ffs: 
 * - return 32..1 to indicate bit 31..0 most significant bit set 
 * - return 0 to indicate no bits set 
 */
int fls(uint32_t x)  
{  
    int r;  
  
    __asm__("bsrl %1,%0\n\t"  
            "jnz 1f\n\t"  
            "movl $-1,%0\n"  
            "1:" : "=r" (r) : "rm" (x));  
    return r+1;  
}  


int fls64(uint64_t x)  
{  
    uint32_t h = x >> 32;  
    if (h)  
        return fls(h) + 32;  
    return fls(x);  
}

uint32_t RoundUpOfPow2(uint32_t x)  
{  
    return 1UL << fls(x - 1);  
}  
} // end namespace N_Bsn
