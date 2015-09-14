#ifndef T3_TIMER_H
#define T3_TIMER_H

class t3Timer
{
public:
    t3Timer():startTime(0.0f){}
    
    // 开始计时
    double start();
    
    // 结束计时
    double end();
    
    // 时间差
    double difference();
    
    double startTime, endTime;
};

#endif
