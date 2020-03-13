/*
手机CAPP mrp版 android.h头文件说明

风的影子 编写
*/

//从aasts目录读取文件
void *readFileFromAssets(char *filename, int32 *len);

//释放assets目录读取的文件 （作废）
void freeFileFromAssets(void *data,int32 len);