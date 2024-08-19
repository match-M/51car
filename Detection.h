#include "reg52.h"

typedef unsigned char uchar;

sbit leftDetection = P3^6;
sbit rightDetection = P3^7;

/*
	右边有障碍/右边碰到黑线
*/
uchar isRightObstacle(){
	return rightDetection == 1;
}

/*
	右边有障碍/右边碰到黑线
*/
uchar isLeftObstacle(){
	return leftDetection == 1;
}