#include "reg52.h"
#include "pwm.h"

sbit ENB = P1^0;
sbit IN4 = P1^1;
sbit IN3 = P1^2;
sbit IN2 = P1^3;
sbit IN1 = P1^4;
sbit ENA = P1^5;

static int duty = 10; //默认占空比 10%
static int runTime = 0; //记录周期内运行的时间

/*
初始化电机
*/
void initMoter(){
	ENB = 0;
	IN4 = 0;
	IN3 = 0;
	IN2 = 0;
	IN1 = 0;
	ENA = 0;	
}

/*
	设置占空比
*/
void setDuty(int newDuty){
	if(newDuty < 0 || newDuty > 100) return; //不合法的值
	duty = newDuty;
}

/*
	使能A
*/
void enA(){
	ENA = 1;
}

/*
	取消使能A
*/
void cancelEnA(){
	ENA = 0;
}

/*
	使能B
*/
void enB(){
	ENB = 1;
}

/*
	取消使能B
*/
void cancelEnB(){
	ENB = 0;
}

/*
	前进
*/
void forward(){
	IN1 = 0;
	IN2 = 1;
	IN3 = 0;
	IN4 = 1;
}

/*
	后退
*/
void back(){
	IN1 = 1;
	IN2 = 0;
	IN3 = 1;
	IN4 = 0;
}

/*
	右转
*/
void right(){
	IN1 = 1;
	IN2 = 0;
	IN3 = 0;
	IN4 = 1;
}

/*
	左转
*/
void left(){
	IN1 = 0;
	IN2 = 1;
	IN3 = 1;
	IN4 = 0;
}

/*
	停止/刹车
*/
void stop(){
	IN1 = 1;
	IN2 = 1;
	IN3 = 1;
	IN4 = 1;
}

/*
	PWM波输出，51中断会自动调用，不需要在main中调用
	默认频率1kHz，每0.01ms会中断处理这个方法一次，100次就是1ms，所以是runTime > 100时代表一个周期运行结束把runTime清零
*/
void pwm() interrupt 1 {
	restT0(); //复位计时器T0
	
	runTime++;
	if(runTime > 100){
		runTime = 0;
		return;
	}
	if(runTime < duty){
		enA();
		enB();
		return;
	}
	
	cancelEnA();
	cancelEnB();
}

