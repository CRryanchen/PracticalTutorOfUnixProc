#ifndef __UTMPLIB_H
#define __UTMPLIB_H

#ifdef __cplusplus
extern "C"{
#endif


/* 宏定义 */


/* 函数声明 */
int utmp_open(char *filename);
struct utmp *utmp_next(void);
int utmp_reload(void);
void utmp_close(void);


/* 全局变量声明 */


#ifdef __cplusplus
}
#endif

#endif /* __UTMPLIB_H */
