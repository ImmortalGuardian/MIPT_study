#include "func_num.h"

typedef struct
{
    char* str;
    int num;
}   func_id;

func_id functions [] = {{"sin", FUNC_SIN}, {"cos", FUNC_COS}, {"tg", FUNC_TG}, {"ln", FUNC_LN},
                        {"sqrt", FUNC_SQRT}};

#define CHK_FUNC(func)                                                      \
        {                                                                   \
            int flag = 0;                                                   \
            for (cnt1 = 0; cnt1 <= NUM_FUNC - 1; cnt1++)                    \
                if (!strcmp ((functions [cnt1]).str, func))                 \
                {                                                           \
                    (CODE [TOKEN_CNT]).data = (functions [cnt1]).num;       \
                    (CODE [TOKEN_CNT++]).type = TYPE_FUNC;                  \
                    flag = 1;                                               \
                    break;                                                  \
                }                                                           \
                                                                            \
            if (flag)                                                       \
                continue;                                                   \
        }

int NUM_FUNC = sizeof (functions) / sizeof (func_id), cnt1 = 0;


