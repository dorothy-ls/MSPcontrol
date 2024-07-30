#ifndef CONTROL_CONFIG_H
#define CONTROL_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "string.h"
#include "arm_math.h"
#include "ti_msp_dl_config.h"

#define MAIN_LOOP_FREQ 1000

#ifndef M_PI
#define M_PI        3.14159265358979323846
#endif

#define INRANGE(num, max)   if(num > max) num = max; else if(num < -max) num = -max;//限定区间
#define MAP(num, frommin, frommax, tomin, tomax) (((float)(num) - frommin) / (frommax - frommin) * (tomax - tomin) + tomin)//线性映射
#define ABS(n) ((n>=0)? n:-n)//取绝对值
#define MOD(ang, n)     if(ang >= n){ang -= (int)(ang / n) * n;}else if(ang < 0){ang -= (int)(ang / n) * n - n;}

#ifdef __cplusplus
}
#endif

#endif
