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
 
 /*
	��bitmap��(tx,ty,tw,th)�������Ż��Ƶ���Ļ(x,y,w,h)������
	������
	x ���Ƶ���Ļ�ϵ�x����
	y ���Ƶ���Ļ�ϵ�y����
	w ���ƿ��
	h ���Ƹ߶�
	tx ty tw th �ü�����
*/
void drawBitmapEx(int32 b,int x,int y,int w,int h,int tx,int ty,int tw,int th);

 //����bitmap
 void drawBitmap(int b,int32 x,int32 y);
 //�ͷ�ͼƬ�ڴ�
 int32 bitmapFree(int b);

 //�ӹ���Ŀ¼assets�ļ��ж�ȡͼƬ
 int readBitmapFromAssets(char *filename);
 
 /*
 	����һ������
	������
	x,y ��������
	w,h, ���ο��
	color ������ɫ(ARGB��ɫֵ)
*/
	void drawRect(int x,int y,int w,int h,uint32 color);

/*
	
	����һ��Բ
	������
	x,y Բ������
	r Բ�İ뾶
	color ��ɫֵ(ARGB��ʽ)
*/
	void drawCir(int x,int y,int r,uint32 color);
 