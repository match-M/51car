#include "reg52.h"

/*
	初始化PWM
*/
void initPWM(){
	TMOD=0x01; //定时器0工作方式1
	TH0=0xff; //赋初值
	TL0=0xf7; 
	EA=1; //开总中断
	ET0=1; //开定时器0中断
	TR0=1; //启动定时器0
}

/*
	复位T0计时器
*/
void restT0(){
	TR0=0; //关闭定时器
	TH0=0xff; //赋初值定
	TL0=0xf7; 
	TR0=1; //打开定时器
}