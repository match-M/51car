#include "reg52.h"
#include "Moter.h"
#include "Detection.h"
#include "pwm.h"
#include "Time.h"

sbit stopKey = P3^3;

static int carSpeed = 60; //小车正常时运行速度
static int carAvoidSpeed = 30; //避障时运行速度

void main(){
	initMoter();
	initPWM();
	setDuty(carSpeed);
	//如果不需要PWM调速需要调用下面的这两个方法，否则小车不会动，如果需要调速可不必调用。
	//enA();
	//enB();
	
	
	while(1){
		if(stopKey == 0){
			setDuty(0);
			stop();
			return;
		}
		
		if(!isRightObstacle() && !isLeftObstacle()){
			forward();
		} else if(isRightObstacle() && isLeftObstacle()){
			setDuty(carAvoidSpeed);
			delay_ms(2); //等待调速时间
			back();
			delay_ms(10); //倒退时间10ms
			right();
			delay_ms(15); //右转时间15ms
			setDuty(carSpeed); //恢复速度
		} else if(isRightObstacle()){
			setDuty(carAvoidSpeed);
			delay_ms(2); //等待调速时间
			left();
			delay_ms(15); //左转时间15ms
			setDuty(carSpeed); //恢复速度
		} else if(isLeftObstacle()){
			setDuty(carAvoidSpeed);
			delay_ms(2); //等待调速时间
			right();
			delay_ms(15); //右转时间15ms
			setDuty(carSpeed); //恢复速度
		}
	}
}