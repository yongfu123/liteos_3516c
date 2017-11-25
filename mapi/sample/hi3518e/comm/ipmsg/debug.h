#pragma once

#ifdef DEBUG
#define F_OUT                       printf("%s:", __FUNCTION__);fflush(stdout);
#define L_OUT		                printf("%s:%d:", __FILE__, __LINE__);fflush(stdout);
#define A_OUT                       printf("%s:%d:%s:", __FILE__, __LINE__, __FUNCTION__);fflush(stdout);
#define D_OUT                       printf("DEBUG:");fflush(stdout);

#define F_PRINTF(fmt, arg...)       F_OUT printf(fmt, ##arg)
#define L_PRINTF(fmt, arg...)       L_OUT printf(fmt, ##arg)
#define A_PRINTF(fmt, arg...)       A_OUT printf(fmt, ##arg)
#define PRINTF(fmt, arg...)         D_OUT printf(fmt, ##arg)
#define DBUG(a)     {a;}
#else
#define F_OUT
#define L_OUT
#define A_OUT
#define D_OUT

#define F_PRINTF(fmt, ...)
#define L_PRINTF(fmt, ...)
#define A_PRINTF(fmt, ...)
#define PRINTF(fmt, ...)
#define DBUG(a)
#endif

#define F_PERROR(fmt)               F_OUT perror(fmt)
#define L_PERROR(fmt)               L_OUT perror(fmt)
#define A_PERROR(fmt)               A_OUT perror(fmt)
#define PERROR(fmt)                 D_OUT perror(fmt)

