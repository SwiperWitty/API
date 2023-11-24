#ifndef _CAVEN_TYPE__H_
#define _CAVEN_TYPE__H_

/*
 * Caven_Type.h file
 * 这是一个【纯C】的【.h】文件，是各个底层【.h】的 “共同语言”，上层管理函数的【.h】不需要包含
 *
*/
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "stdint.h"

/*
 *          SDK->Items
 *                      \\
 *                      -->Base     -->Mode
 *                      //          //
 *  C(Lib)->Caven_Type->        API
*/

#ifndef u8
    #define U8  unsigned char
    #define S8  signed char
    #define U16 unsigned short
    #define S16 signed short
    #define U32 unsigned int
    #define S32 signed int
    #define U64 unsigned long long

    #define u8  unsigned char
    #define s8  signed char
    #define u16 unsigned short
    #define s16 signed short
    #define u32 unsigned int
    #define s32 signed int
    #define u64 unsigned long long

#endif 


#ifndef ENABLE
    #define DISABLE 0
    #define ENABLE (!DISABLE)
#endif

#ifndef MAX
    #define MAX(a,b)    ((a)>(b))?(a):(b)               // 比较函数返回最大值，防止过小
    #define MIN(a,b)    ((a)<(b))?(a):(b)               // 比较函数返回最小值，防止过大
#endif

#define DESTROY(X,N) memset((X),0,(N))                  // 销毁 的地址 (X)  长度 (N)


#define BUFF_MAX 300


// 日期 8byte
typedef struct
{
    int year;
    U8 month;
    U8 day;
    U16 Days;
}Caven_Date_Type;

// 时间 8byte
typedef struct
{
    U8 hour;
    U8 minutes;
    U8 second;
    U32 time_us;          // 这里最大 1000 000
}Caven_Watch_Type;

// 系统运行总时长 8byte
typedef struct
{
    U32 SYS_Sec;
    U32 SYS_Us;
}Caven_TIME_Type;

// 颜色 4byte
typedef struct Caven_Color
{
    U8 REG;
    U8 GREEN;
    U8 BULE;
}Caven_Color_Type;

/*
**DATA
**让 Run_num 去追 Length，如果 (Length - Run_num)为0，且过了很长的时间，那么这个数据就该结束了
**将不在这个DATA存放数据，因为MCU内存不一样，规划的空间也不同，所以空间占用大小应该由MCU文件决定，而不是Caven文件。
*/
typedef struct Caven_Data           //这个数据是动态的
{
    U16 Length;                     //目前接收到的数据长度
    volatile U16 Run_num;           //目前运行/处理到的数据个数

    char index;                     //哪个指针会存放数据
    U8 *Poit_U8;
    U16 *Poit_U16;
    int *Poit_U32;
}Caven_Data_Type;


// Function
typedef void (*D_pFun) (u8 data);
typedef void (*V_pFun) (void);

#endif
