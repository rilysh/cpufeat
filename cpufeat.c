#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cpuid.h"
#include "cpufeat.h"

static void cpu_vendor(int all_aligned)
{
    unsigned int reg[4];
    char buf[13];

    memset(buf, '\0', sizeof(buf));
    __cpuid(0, reg[0], reg[1], reg[2], reg[3]);
    memcpy(buf, &reg[1], sizeof(reg[1]));
    memcpy(buf + 4, &reg[3], sizeof(reg[3]));
    memcpy(buf + 8, &reg[2], sizeof(reg[2]));

    buf[12] = '\0';

    if (all_aligned)
        PRINT_CPU_VENDOR(buf, TABS3)
    else
        PRINT_CPU_VENDOR(buf, TABS0)
}

static void cpu_supported_extensions(void)
{
    unsigned int reg[4];
    unsigned int eax0, eax1;

    cpu_vendor(1);

    __cpuid(0, reg[0], reg[1], reg[2], reg[3]);
    eax0 = reg[0]; /* Temporary keep first eax */

    __cpuid(0x80000000, reg[0], reg[1], reg[2], reg[3]);
    eax1 = reg[0]; /* Temporary keep second eax */

    if (eax0 >= 1) {
        __cpuid(1, reg[0], reg[1], reg[2], reg[3]);

        CHECK_AND_PRINT(reg[3], BIT_MMX, "MMX", TABS4);
        CHECK_AND_PRINT(reg[3], BIT_SSE, "SSE", TABS4);
        CHECK_AND_PRINT(reg[3], BIT_SSE2, "SSE2", TABS4);
        CHECK_AND_PRINT(reg[3], BIT_SSE3, "SSE2", TABS4);
        CHECK_AND_PRINT(reg[2], BIT_SSSE3, "SSSE3", TABS4);
        CHECK_AND_PRINT(reg[2], BIT_SSE2, "SSE4.1", TABS4);
        CHECK_AND_PRINT(reg[2], BIT_SSE2, "SSE4.2", TABS4);

        CHECK_AND_PRINT(reg[2], BIT_AES, "AES", TABS4);
        CHECK_AND_PRINT(reg[2], BIT_AVX, "AVX", TABS4);
        CHECK_AND_PRINT(reg[2], BIT_FMA3, "FMA3", TABS4);
        CHECK_AND_PRINT(reg[2], BIT_RDRAND, "RDRAND", TABS4);
        CHECK_AND_PRINT(reg[2], BIT_XSAVE, "XSAVE", TABS4);
        CHECK_AND_PRINT(reg[2], BIT_F16C, "F16C", TABS4);
    }

    if (eax0 >= 7) {
        __cpuid(7, reg[0], reg[1], reg[2], reg[3]);

        CHECK_AND_PRINT(reg[1], BIT_AVX2, "AVX2", TABS4);
        CHECK_AND_PRINT(reg[1], BIT_BMI, "BMI", TABS4);
        CHECK_AND_PRINT(reg[1], BIT_BMI2, "BMI2", TABS4);
        CHECK_AND_PRINT(reg[1], BIT_ADX, "ADX", TABS4);
        CHECK_AND_PRINT(reg[1], BIT_MPX, "MPX", TABS4);
        CHECK_AND_PRINT(reg[1], BIT_SHA, "SHA", TABS4);
        CHECK_AND_PRINT(reg[1], BIT_RDSEED, "RDSEED", TABS4);
        CHECK_AND_PRINT(reg[2], BIT_PREFETCHWT1, "PREFETCHWT1", TABS3);
        CHECK_AND_PRINT(reg[2], BIT_RDPID, "RDPID", TABS4);

        CHECK_AND_PRINT(reg[1], BIT_AVX512F, "AVX512F", TABS3);
        CHECK_AND_PRINT(reg[1], BIT_AVX512CD, "AVX512CD", TABS3);
        CHECK_AND_PRINT(reg[1], BIT_AVX512PF, "AVX512PF", TABS3);
        CHECK_AND_PRINT(reg[1], BIT_AVX512ER, "AVX512ER", TABS3);
        CHECK_AND_PRINT(reg[1], BIT_AVX512VL, "AVX512VL", TABS3);
        CHECK_AND_PRINT(reg[1], BIT_AVX512BW, "AVX512BW", TABS3);
        CHECK_AND_PRINT(reg[1], BIT_AVX512DQ, "AVX512DQ", TABS3);
        CHECK_AND_PRINT(reg[1], BIT_AVX512IFMA, "AVX512IFMA", TABS3);
        CHECK_AND_PRINT(reg[2], BIT_AVX512VBMI, "AVX512VBMI", TABS3);
        CHECK_AND_PRINT(reg[2], BIT_AVX512VPOPCNTDQ, "AVX512VPOPCNTDQ", TABS2);
        CHECK_AND_PRINT(reg[3], BIT_AVX5124FMAPS, "AVX5124FMAPS", TABS3);
        CHECK_AND_PRINT(reg[3], BIT_AVX5124VNNIW, "AVX5124VNNIW", TABS3);
        CHECK_AND_PRINT(reg[2], BIT_AVX512VNNI, "AVX512VNNI", TABS3);
        CHECK_AND_PRINT(reg[2], BIT_AVX512VBMI2, "AVX512VBMI2", TABS3);
        CHECK_AND_PRINT(reg[2], BIT_AVX512BITALG, "AVX512BITALG", TABS3);

        CHECK_AND_PRINT(reg[2], BIT_VAES, "VAES", TABS4);
    }

    if (eax1 >= 0x80000001) {
        __cpuid(0x80000001, reg[0], reg[1], reg[2], reg[3]);

        CHECK_AND_PRINT(reg[3], BIT_X64, "X64", TABS4);
        CHECK_AND_PRINT(reg[2], BIT_ABM, "ABM", TABS4);
        CHECK_AND_PRINT(reg[2], BIT_SSE4a, "SSE4a", TABS4);
        CHECK_AND_PRINT(reg[2], BIT_FMA4, "FMA4", TABS4);
        CHECK_AND_PRINT(reg[2], BIT_XOP, "XOP", TABS4);
        CHECK_AND_PRINT(reg[2], BIT_PREFETCHW, "PREFETCHW", TABS3);
        CHECK_AND_PRINT(reg[2], BIT_LAHF_LM, "LAHF_LM", TABS3);
    }

    if (eax0 >= 13) {
        int ecx = 1;
        __cpuid(13, reg[0], reg[1], ecx, reg[3]);

        CHECK_AND_PRINT(reg[2], BIT_XSAVEOPT, "XSAVEOPT", TABS3);
    }
}

static void help(void)
{
    fprintf(stdout,
        "cpufeat\n\n"
        "Usage:\n"
        "   --features      -- Output several relevant CPU features (default)\n"
        "   --vendor        -- Output CPU vendor\n"
    );
}

int main(int argc, char **argv)
{
    if (argc < 2) {
        cpu_supported_extensions();
        exit(EXIT_SUCCESS);
    }

    if (strcmp(argv[1], "--vendor") == 0)
        cpu_vendor(0);
    else if (strcmp(argv[1], "--features") == 0)
        cpu_supported_extensions();
    else if (strcmp(argv[1], "--help") == 0)
        help();
    else
        fprintf(stdout, "Unknown command: %s\n", argv[1]);

    exit(EXIT_SUCCESS);
}
