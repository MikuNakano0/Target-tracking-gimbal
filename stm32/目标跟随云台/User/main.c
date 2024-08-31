#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Servo.h"
#include "Serial.h"
#include "PID.h"

float Angle;			//定义角度变量
#define angle_X_center 70.0   //中心坐标

int main(void)
{
	/*模块初始化*/
	OLED_Init();		//OLED初始化
	Servo_Init();		//舵机初始化
	PID_Init();			//PID初始化
	Serial_Init();      //Serial初始化
	
	/*显示静态字符串"x_position:"*/
	OLED_ShowString(1, 1, "x_position:");	//1行1列显示字符串x_position:
	OLED_ShowString(2,1,"AngleX:");
	OLED_ShowString(3,1,"PID_ResultX:");
	
	float angle_X = 100.0;
	float PID_ResultX = 0.0;
	Servo_SetAngle(angle_X);
	x = 90;

	while (1)
	{
		PID_ResultX = PID_value_x(90.0,(float)x);
			angle_X+=PID_ResultX;
			// 防止角度过量
			if(angle_X>170){angle_X = 170;}
			if(angle_X<10){angle_X = 10;}
			// 舵机移动
			Servo_SetAngle(angle_X);//设置舵机的角度为角度变量
			OLED_ShowNum(1, 12, x, 3);	//OLED显示角度变量
			OLED_ShowNum(2,8,(int)angle_X,3);
			OLED_ShowNum(3,13,(int)PID_ResultX,3);
			Delay_ms(30);
	}
}

