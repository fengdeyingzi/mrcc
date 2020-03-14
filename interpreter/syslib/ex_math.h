
#ifndef _EX_MATH_H_
#define _EX_MATH_H_

/*
“shell（希尔）法”
shell法是一个叫 shell 的美国人与1969年发明的。它首先把相距k(k>=1)的那几个元素排好序，再缩小k值（一般取其一半），再排序，直到k=1时完成排序。下面让我们来分析其代码：
*/
void shell(int *a,int n)
{
int i,j,k,x;
k=n/2; /*间距值*/
while(k>=1) {
for(i=k;i<n;i++) {
x=a[i];
j=i-k;
while(j>=0&&x<a[j]) {
a[j+k]=a[j];
j-=k;
}
a[j+k]=x;
}
k/=2; /*缩小间距值*/
}
}



//判断点(x,y)是否在矩形区域(rectx,recty,rectw,recth)内
int ex_isPointCollisionRect(int x,int y,int rectx,int recty,int rectw,int recth)
{
	if(x>=rectx && x<rectx+rectw && y>=recty && y<recty+recth)
	{
		return TRUE;
	}
	return FALSE;
}


// 矩形和圆形碰撞检测
int ex_IsCircleCollisionRect(float circleXPos, float circleYPos, float radius, float rectX, float rectY, float rectW, float rectH)
{
    float arcR  = radius;
    float arcOx = circleXPos;
    float arcOy = circleYPos;
	float minDisX = 0;   
	float minDisY = 0;   
    //分别判断矩形4个顶点与圆心的距离是否<=圆半径；如果<=，说明碰撞成功   
    if(((rectX-arcOx) * (rectX-arcOx) + (rectY-arcOy) * (rectY-arcOy)) <= arcR * arcR)   
        return TRUE;   
    if(((rectX+rectW-arcOx) * (rectX+rectW-arcOx) + (rectY-arcOy) * (rectY-arcOy)) <= arcR * arcR)   
        return TRUE;   
    if(((rectX-arcOx) * (rectX-arcOx) + (rectY+rectH-arcOy) * (rectY+rectH-arcOy)) <= arcR * arcR)   
        return TRUE;   
    if(((rectX+rectW-arcOx) * (rectX+rectW-arcOx) + (rectY+rectH-arcOy) * (rectY+rectH-arcOy)) <= arcR * arcR)   
        return TRUE;

    //判断当圆心的Y坐标进入矩形内时X的位置，如果X在(rectX-arcR)到(rectX+rectW+arcR)这个范围内，则碰撞成功   
    
    if(arcOy >= rectY && arcOy <= rectY + rectH)
    {   
        if(arcOx < rectX)   
            minDisX = rectX - arcOx;   
        else if(arcOx > rectX + rectW)   
            minDisX = arcOx - rectX - rectW;   
        else    
            return TRUE;   
        if(minDisX <= arcR)   
            return TRUE;   
    }

    //判断当圆心的X坐标进入矩形内时Y的位置，如果X在(rectY-arcR)到(rectY+rectH+arcR)这个范围内，则碰撞成功
    
    if(arcOx >= rectX && arcOx <= rectX + rectW)
    {   
        if(arcOy < rectY)   
            minDisY = rectY - arcOy;   
        else if(arcOy > rectY + rectH)   
            minDisY = arcOy - rectY - rectH;   
        else  
            return TRUE;   
        if(minDisY <= arcR)   
            return TRUE;   
    }

    return FALSE; 
}

// 线段和线段碰撞检测
/*
int IsLineCollisionLine(int p1, int p2, int p3, int p4)
{
    float x1 = p1.x, x2 = p2.x, x3 = p3.x, x4 = p4.x;
    float y1 = p1.y, y2 = p2.y, y3 = p3.y, y4 = p4.y;

    float d = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
    // If d is zero, there is no intersection
    if (d == 0) 
        return FALSE;

    // Get the x and y
    float pre = (x1*y2 - y1*x2), post = (x3*y4 - y3*x4);
    float x = ( pre * (x3 - x4) - (x1 - x2) * post ) / d;
    float y = ( pre * (y3 - y4) - (y1 - y2) * post ) / d;

    // Check if the x and y coordinates are within both lines
    if ( x < MIN(x1, x2) || x > MAX(x1, x2) ||
        x < MIN(x3, x4) || x > MAX(x3, x4) )
        return FALSE;

    if ( y < MIN(y1, y2) || y > MAX(y1, y2) ||
        y < MIN(y3, y4) || y > MAX(y3, y4) ) 
        return FALSE;

    return TURE;
}
*/


int ex_isCollisionRect(int x1, int y1, int w1, int h1, int x2, int  y2, int w2, int h2) 
		{  
			//Logcat.e(""+x1 + " " + y1 + " " + w1+ " "  + h1+ " "  + x2+ " "  + y2+ " "  + w2+ " "  + h2);
		
		//当矩形1 位于矩形2 的左侧  
		if (x1 > x2 && x1 >= x2 + w2)
		{  
		return FALSE;  
		//当矩形1 位于矩形2 的右侧  
		} 
		else if (x1 < x2 && x1 + w1 <= x2)
		{ 
		return FALSE;  
		//当矩形1 位于矩形2 的上方  
		} 
		else if (y1 > y2 && y1 >= y2+ h2) 
		{  
		return FALSE;  
		//当矩形1 位于矩形2 的下方  
		} 
		else if (y1 < y2 && y1 + h1 <= y2) 
		{  
		return FALSE;  
		}  
		
		//所有不会发生碰撞都不满足时，肯定就是碰撞了  
		return TRUE;  
		}
	
	
	static float ex_toRad(float a)
	{
		return (a*3.14159265f)/180;
	}
	
	
		//点(x,y)旋转指定弧度r，得到旋转后的坐标
	//旋转一条水平线，得到旋转后的坐标
//参数：旋转中心点(px,py)，旋转横向半径rx，旋转纵向半径ry， 旋转后坐标指针(*x,*y)
	void ex_toSpin(int px,int py,int rx,int ry,int r,int* x,int* y)
	{
		
		*x=(int)( px+(rx)*cos(ex_toRad(r)));
		*y=(int)( py+(ry)*sin(ex_toRad(r)));

		
	}
	
	//求两点之间距离 可用于计算圆与圆的碰撞(当两个圆的圆心距离大于它们的半径只和，那么碰撞成功)
	float ex_getLineSize(int x,int y,int x2,int y2)
	{
		
		return sqrt( (x2-x)*(x2-x)+ (y2-y)*(y2-y));
	}
	
	
	
	//求点与点之间弧度
	float ex_getRadiam(float x,float y,float rx,float ry)
	{float dx=0,dy=0;
	float r=0;
		dx=rx-x;
		dy=ry-y;
		r=(atan((dy) / (dx))*180/3.14159265f);

		//右下角
		if(dx>=0 && dy>=0)
			r=r;
		//左下角
		else if(dx<=0&& dy>=0)
			r=90+r+90;
		//左上角
		else if(dx<0&&dy<=0)
			r=180+r;
		//右上角
		else if(dx>=0 && dy<=0)
			r=90+r+270;

		return r;
	}

	#endif
