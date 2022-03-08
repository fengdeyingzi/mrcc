#ifndef __ARR_STATE_H__
#define __ARR_STATE_H__

#include <mrc_base.h>

//模拟堆结构
typedef struct ARR_STATE
{
    int32 *list;
    int32 len;
    int32 max;
} ARR_STATE;

//创建
ARR_STATE *arr_create(void);

//像堆中添加一个值
int arr_add(ARR_STATE *arr, int32 data);

//向堆中取出一个值 如果取不出 返回0
int32 arr_get(ARR_STATE *arr);

//获取堆中内容长度
int arr_getlen(ARR_STATE *arr);

//释放
int arr_free(ARR_STATE *arr);
#endif
