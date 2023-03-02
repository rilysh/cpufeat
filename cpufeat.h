#ifndef CPUFEAT_H
#define CPUFEAT_H

#undef YES
#undef NO
#define YES     "\033[0;92mYes\033[0m"
#define NO      "\033[0;91mNo\033[0m"

#define TABS2   "\t\t"
#define TABS3   "\t\t\t"
#define TABS4   "\t\t\t\t"

#define CHECK_AND_PRINT(reg, bit, name, tabs) \
    if (reg & bit) \
        fprintf(stdout, "%s:%s[%s]\n", name, tabs, YES); \
    else \
        fprintf(stdout, "%s:%s[%s]\n", name, tabs, NO);

#endif
