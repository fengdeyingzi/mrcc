/*
�ֻ�CAPP mrp�� ͷ�ļ�˵��
graphics.h
ע�⣺graphics.hֻ֧�ֶ�ȡbmpͼƬ��ʽ��֧��������bmpͼƬ
Ŀǰ��֧��16λ��24λ��bmp

���Ӱ�� ��д
*/

 //���ڴ濨��ȡbitmap 
 int readBitmap(char *filename);
 //�ü�����bitmap
 int32 drawBitmapFlip(int buf, int32 x, int32 y, int32 w, int32 h, int32 sx, int32 sy);
 //����bitmap
 void drawBitmap(int b,int32 x,int32 y);
 //�ͷ�ͼƬ�ڴ�
 int32 bitmapFree(int b);

 //�ӹ���Ŀ¼assets�ļ��ж�ȡͼƬ
 int readBitmapFromAssets(char *filename);