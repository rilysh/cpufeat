/*===---- cpuid.h - X86 cpu model detection --------------------------------===
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 *===-----------------------------------------------------------------------===
 */

 /*
  * Author: John Baldwin
  * Email: john@baldwin.cx
  * Source: https://people.freebsd.org/~jhb/patches/cpuid.h
  * Modified by: rilysh
 */

#define BIT_MMX               0x00800000
#define BIT_SSE               0x02000000
#define BIT_SSE2              0x04000000
#define BIT_SSE3              0x00000001
#define BIT_SSSE3             0x00000200
#define BIT_SSE41             0x00080000
#define BIT_SSE42             0x00100000
#define BIT_SSE4a             0x00000040
#define BIT_FMA3              0x00001000
#define BIT_FMA4              0x00010000
#define BIT_AES               0x02000000
#define BIT_VAES              0x00000200
#define BIT_RDRAND            0x40000000
#define BIT_ADX               0x00080000
#define BIT_SHA               0x20000000
#define BIT_AVX               0x10000000
#define BIT_AVX2              0x00000020
#define BIT_AVX512F           0x00010000
#define BIT_AVX512CD          0x10000000
#define BIT_AVX512PF          0x04000000
#define BIT_AVX512ER          0x08000000
#define BIT_AVX512VL          0x80000000u
#define BIT_AVX512BW          0x40000000
#define BIT_AVX512DQ          0x00020000
#define BIT_AVX512IFMA        0x00200000
#define BIT_AVX512VBMI        0x00000002
#define BIT_AVX512VPOPCNTDQ   0x00004000
#define BIT_AVX5124FMAPS      0x00000008
#define BIT_AVX5124VNNIW      0x00000004
#define BIT_AVX512VNNI        0x00000800
#define BIT_AVX512VBMI2       0x00000040
#define BIT_XSAVE             0x04000000
#define BIT_XSAVEOPT          0x00000001
#define BIT_F16C              0x20000000
#define BIT_BMI               0x00000008
#define BIT_BMI2              0x00000100
#define BIT_MPX               0x00004000
#define BIT_RDSEED            0x00040000
#define BIT_PREFETCHWT1       0x00000001
#define BIT_RDPID             0x00400000
#define BIT_AVX512VPCLMUL     0x00000400
#define BIT_AVX512BITALG      0x00001000

/** Extended features */
#define BIT_X64               0x20000000
#define BIT_ABM               0x00000020
#define BIT_SSE4a             0x00000040
#define BIT_XOP               0x00000800
#define BIT_PREFETCHW         0x00000100
#define BIT_LAHF_LM           0x00000001

/* PIC on i386 uses %ebx, so preserve it. */
#if __i386__
#define __cpuid(__level, __eax, __ebx, __ecx, __edx) \
    __asm__ volatile("  pushl  %%ebx\n" \
          "  cpuid\n" \
          "  mov    %%ebx,%1\n" \
          "  popl   %%ebx" \
        : "=a"(__eax), "=r" (__ebx), "=c"(__ecx), "=d"(__edx) \
        : "0"(__level))

#define __cpuid_count(__level, __count, __eax, __ebx, __ecx, __edx) \
    __asm__ volatile("  pushl  %%ebx\n" \
          "  cpuid\n" \
          "  mov    %%ebx,%1\n" \
          "  popl   %%ebx" \
        : "=a"(__eax), "=r" (__ebx), "=c"(__ecx), "=d"(__edx) \
        : "0"(__level), "2"(__count))
#else
#define __cpuid(__level, __eax, __ebx, __ecx, __edx) \
    __asm__ volatile("cpuid" : "=a"(__eax), "=b" (__ebx), "=c"(__ecx), "=d"(__edx) \
                  : "0"(__level))

#define __cpuid_count(__level, __count, __eax, __ebx, __ecx, __edx) \
    __asm__ volatile("cpuid" : "=a"(__eax), "=b" (__ebx), "=c"(__ecx), "=d"(__edx) \
                  : "0"(__level), "2"(__count))
#endif
