#ifndef __PID_H
#define __PID_H

typedef struct{
float Err; // 误差
float Err_sum; // 误差和
float Err_difference; // 误差差值
float Last_err; // 上次误差
float Kp;
float Ki;
float Kd;
}PID_typedef;

void PID_Init(void);
float PID_value_x(float measure, float calcu);


#endif
