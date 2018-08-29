#include "time_measure.h"

// �趨�������
void Time_point::start_measure_time(void)
{
    uint8_t i;
    
    //��¼������
	time_p.period  =  getCount();
	if(time_p.period > time_p.period_max) 
        time_p.period_max = time_p.period ;
    
    //������һ�ε�ʱ����
	for(i=0; i<TIME_CAP; i++)
	{
		//��һ����ֱ��ʱ����ֱ�ӵ��ڵ�һ�����ֵ
		if(i == 0)
		{
			time_p.distant[0] = time_p.point[0];
			continue;
		}
		//��Ч�㣬������
		if(time_p.point[i] < time_p.point[i-1]) break;
		
		time_p.distant[i] = time_p.point[i] - time_p.point[i-1];
	}
    
	//��¼�������ʱ��
	time_p.total = time_p.point[i-1];
	if(time_p.total_max < time_p.total)
        time_p.total_max = time_p.total;

	//��ȡdistant���ֵ
	for(i=0; i<TIME_CAP; i++)
	{
		if(time_p.distant_max[i] < time_p.distant[i])
            time_p.distant_max[i] = time_p.distant[i];
	}
    
    // ֹͣ��ʱ��
    pause();
    // �趨���ֵ
    setOverflow(0xFFFFFFFF);
    // 
	setPrescaleFactor(TIMER_FREQUENCY - 1, TIM_PSCReloadMode_Update);

    setCounterMode(TIM_CounterMode_Up);
    setClockDiv(TIM_CKD_DIV1);
    // ������ʱ��
    resume();
}

// ��ȡ����ֵ�������β���֮���ʱ���
uint32_t Time_point::return_time(rt_uint8_t point)
{
    time_p.point[point] = getCount();
    time_p.interval[point][TIME_OLD] = time_p.interval[point][TIME_NOW];
    time_p.interval[point][TIME_NOW] = getCount();
    time_p.interval[point][TIME_NEW] = time_p.interval[point][TIME_NOW] - time_p.interval[point][TIME_OLD];
   	return time_p.interval[point][TIME_NEW];
}

// ��ȡ����ֵ����ȡ�̶���Ķ�ʱ������ֵ
uint32_t Time_point::get_time(rt_uint8_t point)
{
    time_p.point[point] = getCount();
    return getCount();
}

// ֹͣ����
void Time_point::stop_measure_time(void)
{
    uint8_t i ;

	//������һ�ε�ʱ����
	for(i=0; i<TIME_CAP; i++)
	{
		//��һ����ֱ��ʱ����ֱ�ӵ��ڵ�һ�����ֵ
		if(i == 0)
		{
			time_p.distant[0] = time_p.point[0];
			continue;
		}
		//��Ч�㣬������
		if(time_p.point[i] < time_p.point[i-1]) break;

		time_p.distant[i] = time_p.point[i] - time_p.point[i-1];
	}
	//��¼�������ʱ��
	time_p.total = time_p.point[i-1];
	if(time_p.total_max < time_p.total)
        time_p.total_max = time_p.total;

	//��ȡ���ֵ
	for(i=0; i<TIME_CAP; i++)
	{
		if(time_p.distant_max[i] < time_p.distant[i])
            time_p.distant_max[i] = time_p.distant[i];
	}
   	//ֹͣ����
	pause();
}

Time_point::~Time_point()
{
    stop_measure_time();
}


