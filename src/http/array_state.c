#include "array_state.h"
#include <mrc_base.h>

//创建
ARR_STATE *arr_create(){
    ARR_STATE *arr = (ARR_STATE*)malloc(sizeof(ARR_STATE));
    memset(arr,0,sizeof(ARR_STATE));
    arr->max = 1024;
    arr->list = malloc(arr->max*sizeof(int32));
    return arr;
}

//像堆中添加一个值
int arr_add(ARR_STATE *arr, int32 data){
    // printf("arr_add %d\n", data);
    if(arr->len < arr->max-1){
        arr->list[arr->len++] = data;
    }
    return 0;
}

//向堆中取出一个值 如果取不出 返回0
int32 arr_get(ARR_STATE *arr){
    int32 data = 0;
    // printf("arr_get \n");
    if(arr->len>0){
        data = arr->list[0];
        // memmove(arr->list, arr->list+1, (arr->len-1)*sizeof(int32));
        memmove(arr->list, arr->list+1, (arr->len)*sizeof(int32)); //为了解决多线程问题 暂时多1位
        arr->len--;
    }
    return data;
}

//获取堆中内容长度
int arr_getlen(ARR_STATE *arr){
    return arr->len;
}

//释放
int arr_free(ARR_STATE *arr){
    free(arr->list);
    free(arr);
    return 0;
}