#ifndef __CAN_H__
#define __CAN_H__

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>
#include <can.h>
#include <bxcan.h>
#include <AP_Math.h>
#include "parameter.h"
#include "fir_vec3f.h"

#ifdef __cplusplus
// �豸��
#define BGC_NUM                           (0x01 << 8)
#define BMC_P                             (0x02 << 8)
#define BMC_R                             (0x03 << 8)
#define BMC_Y                             (0x04 << 8)

#define BGC_P_ENC                         (BGC_NUM | 0x10)
#define BGC_R_ENC                         (BGC_NUM | 0x20)
#define BGC_Y_ENC                         (BGC_NUM | 0x30)

#define BGC_P_POSITION                    (BGC_NUM | 0x01)
#define BGC_R_POSITION                    (BGC_NUM | 0x02)
#define BGC_Y_POSITION                    (BGC_NUM | 0x03)
#define BGC_P_MOTOR_STATUS                (BGC_NUM | 0x04)
#define BGC_R_MOTOR_STATUS                (BGC_NUM | 0x05)
#define BGC_Y_MOTOR_STATUS                (BGC_NUM | 0x06)

#define BMC_P_MOTOR_CONTROL               (BMC_P | 0x01)
#define BMC_P_ENABLE_MOTOR                (BMC_P | 0x02)
#define BMC_P_MOTOR_DIR                   (BMC_P | 0x03)
#define BMC_P_MAXPWM                      (BMC_P | 0x04)
#define BMC_P_MOTOR_MODE                  (BMC_P | 0x05)
#define BMC_P_SET_DEFAULT                 (BMC_P | 0x06)
#define BMC_P_INIT_SIN_MATRIX             (BMC_P | 0x07)
#define BMC_P_SAVE_PARAM                  (BMC_P | 0x08)
#define BMC_P_TEST_MOTOR                  (BMC_P | 0x09)

#define BMC_R_MOTOR_CONTROL               (BMC_R | 0x01)
#define BMC_R_ENABLE_MOTOR                (BMC_R | 0x02)
#define BMC_R_MOTOR_DIR                   (BMC_R | 0x03)
#define BMC_R_MAXPWM                      (BMC_R | 0x04)
#define BMC_R_MOTOR_MODE                  (BMC_R | 0x05)
#define BMC_R_SET_DEFAULT                 (BMC_R | 0x06)
#define BMC_R_INIT_SIN_MATRIX             (BMC_R | 0x07)
#define BMC_R_SAVE_PARAM                  (BMC_R | 0x08)
#define BMC_R_TEST_MOTOR                  (BMC_R | 0x09)

#define BMC_Y_MOTOR_CONTROL               (BMC_Y | 0x01)
#define BMC_Y_ENABLE_MOTOR                (BMC_Y | 0x02)
#define BMC_Y_MOTOR_DIR                   (BMC_Y | 0x03)
#define BMC_Y_MAXPWM                      (BMC_Y | 0x04)
#define BMC_Y_MOTOR_MODE                  (BMC_Y | 0x05)
#define BMC_Y_SET_DEFAULT                 (BMC_Y | 0x06)
#define BMC_Y_INIT_SIN_MATRIX             (BMC_Y | 0x07)
#define BMC_Y_SAVE_PARAM                  (BMC_Y | 0x08)
#define BMC_Y_TEST_MOTOR                  (BMC_Y | 0x09)

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
// Message ID definition
// Write or Read (1 bit)
#define WRITE 														 (1<<2)
#define READ  														 (0<<2)
// Head or Normal (1 bit)
#define HEAD                               1
#define NORMAL                             0
// Priority type (2 bits)
#define PRIORITY_CONTROL 									(1<<9)
#define PRIORITY_ENCODER  								(2<<9)
#define PRIORITY_RQST    									(3<<9)   
// Device address (3 bits)
#define CONTROLLER_ADDR  									0
#define ROLL_MOTOR_ADDR  									1
#define PITCH_MOTOR_ADDR 									2
#define YAW_MOTOR_ADDR   									3
#define TRIPOD_MOTOR_ADDR                 4
#define TRIPOD_ENC_ADDR                   5

// Motor control
#define RPY_CTRL											0x20C
#define RP_CTRL                       0x214
#define Y_CTRL                        0x21C

// Encoder
#define ROLL_ENC                      0x444
#define PITCH_ENC                     0x484
#define YAW_ENC                       0x4C4

// RQRP Write
// MCU write single message to Motors
#define MCU_WS_ROLL                   0x60C
#define MCU_WS_PITCH                  0x614
#define MCU_WS_YAW                    0x61C
#define MCU_WS_TRPMOT                 0x624
#define MCU_WS_TRPENC                 0x62C
// Motors reply single message to MCU
#define ROLL_RPS_MCU                  0x644
#define PITCH_RPS_MCU                 0x684
#define YAW_RPS_MCU                   0x6C4
// MCU write long message to Motors
#define MCU_WL_ROLL_NORMAL            0x60E
#define MCU_WL_ROLL_HEAD              0x60F
#define MCU_WL_PITCH_NORMAL           0x616
#define MCU_WL_PITCH_HEAD             0x617
#define MCU_WL_YAW_NORMAL             0x61E
#define MCU_WL_YAW_HEAD               0x61F
// Motor reply long message to MCU
#define ROLL_RPL_MCU_NORMAL           0x646
#define ROLL_RPL_MCU_HEAD             0x647
#define PITCH_RPL_MCU_NORMAL          0x686
#define PITCH_RPL_MCU_HEAD            0x687
#define YAW_RPL_MCU_NORMAL            0x6C6
#define YAW_RPL_MCU_HEAD              0x6C7

// RQRP Read
// MCU read single message from Motors
#define MCU_RS_ROLL                   0x608
#define MCU_RS_PITCH                  0x610
#define MCU_RS_YAW                    0x618
// Motors read single message from MCU
#define ROLL_RS_MCU                   0x640
#define PITCH_RS_MCU                  0x680
#define YAW_RS_MCU                    0x6C0
// MCU read long message from Motors 
#define MCU_RL_ROLL                   0x60A
#define MCU_RL_PITCH                  0x612
#define MCU_RL_YAW                    0x61A
// Motors read long message from MCU
#define ROLL_RL_MCU                   0x642
#define PITCH_RL_MCU                  0x682
#define YAW_RL_MCU                    0x6C2

//Parameter ID definition
#define MAX_FRAMS                     30
enum motor_param_ids
{
	CURRENT_CTRL_KP = 0,
	CURRENT_CTRL_KI,
	ENCODER_OFS,
	ENCODER_RAT,
	SPEED_TRACKER_KP,
	SPEED_TRACKER_KI,
	DUTY_DOWNRAMP_KP,
	DUTY_DOWNRAMP_KI,
	F_SW,
	DTC,
	POS_CTRL_KP,
	POS_CTRL_KI,
	POS_CTRL_KD,
	POS_CTRL_ANGLE_DIVISION,
	SPEED_CTRL_KP,
	SPEED_CTRL_KI,
	SPEED_CTRL_KD,
	SPEED_CRTL_MIN_ERPM,
	FAULT_STOP_TIME,
	
	TACHO,
	TACHO_ABS,
	BUS_VOLTAGE,
	DUTY_CYCLE,
	ELECTRICAL_SPEED,
	BUS_CURRENT,
	MOTOR_CURRENT,
	MOSFET_TEMP,
	FAULT_CODE,
	
	OFS,
	RAT,
	I,
	
	MEASURE_R,
	MEASURE_L,
	DUTY_TEST,
	POS_TEST,
	CALC_CC_TC,
	CALC_CC_KP,
	CALC_CC_KI,
	CURRENT_TEST
};

#define PARAM_TYPE_TOTAL  31

enum param_type
{
	// FOC Config
	// Torque PID
	PID_TORQUE_REFERENCE = 0,
	PID_TORQUE_KP,    
  PID_TORQUE_KI,
  PID_TORQUE_KD,
  // Flux PID
  PID_FLUX_REFERENCE,
  PID_FLUX_KP,
  PID_FLUX_KI,
  PID_FLUX_KD,
  // PID DIV
  TF_KPDIV,
  TF_KIDIV,
  TF_KDDIV,
	// Open loop speed
	OPEN_LOOP_SPEED,
	
	POLE_PAIRS,  //12
	ENC_INVERT,
	ENC_MECHANICAL_ANGLE_BIAS,

  // Motor Control
	MOTOR_INIT,  //15
	MOTOR_RUN_FOC_MODE,
	MOTOR_RUN_OPENLOOP_MODE,
	MOTOR_STOP,
	MOTOR_RUN,
	MOTOR_DISABLE_UPPER_CONTROL,
	MOTOR_ENC_CALIBRATE,

  // Motor State for reading
	ENC,    // 22
	BUS_CURR,
	BUS_VOLT,
	Q_CURR,
	D_CURR,
	TORQUE,
	MOTOR_SPEED,
	
	SAVE_ALL_PARAMS,  // 29
	READ_ALL_PARAMS, 
	
	// Disable Motor
	DISABLE_MOTOR,  // 31
	
	// Tracking object
	TRACKING_OBJECT, //32
};

typedef struct
{
	float params[PARAM_TYPE_TOTAL];
  uint8_t dev_addr;
}__attribute__((packed)) motor_param_for_serial;


typedef struct
{
	rt_uint32_t priority		:	2;
	rt_uint32_t src_addr    : 3;
	rt_uint32_t dst_addr    : 3;
	rt_uint32_t write       : 1;
	rt_uint32_t long_msg     : 1;
	rt_uint32_t long_msg_head : 1;
}__attribute__((packed)) can_pro_head;

typedef struct
{
	rt_uint32_t param_id;
	float    value;
	rt_uint8_t dev_addr;
}__attribute__((packed)) can_param;

typedef struct
{
	rt_uint32_t block_id;
	rt_uint32_t msg_total;   //Total frams of the block 
	can_param   params[MAX_FRAMS];
	rt_uint32_t msg_cnt;     //Frams counter
	rt_uint8_t dev_addr;
}__attribute__((packed)) can_block;

//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////

#define constrain(val,min,max)  ((val)<(min)?(min):((val)>(max)?(max):(val)))
#define circadjust(val,lim)     ((val)<-(lim)?(val)+2*(lim):((val)>(lim)?(val)-2*(lim):(val)))

//FIR FILTERS
#define ENC_ORDER			10
#define ENC_COEF_LEN      ENC_ORDER+1
// Gyro x Freq cut = 
static float enc_x_coef[ENC_COEF_LEN] = {
	      0.01381333798044,  0.02969285839245,  0.07170595839153,   0.1245852401576,
     0.1679157516913,   0.1845737067733,   0.1679157516913,   0.1245852401576,
    0.07170595839153,  0.02969285839245,  0.01381333798044
};
// Gyro y Freq cut = 
static float enc_y_coef[ENC_COEF_LEN] = {
	     0.01381333798044,  0.02969285839245,  0.07170595839153,   0.1245852401576,
     0.1679157516913,   0.1845737067733,   0.1679157516913,   0.1245852401576,
    0.07170595839153,  0.02969285839245,  0.01381333798044
};
// Gyro z Freq cut = 
static float enc_z_coef[ENC_COEF_LEN] = {
	     0.01381333798044,  0.02969285839245,  0.07170595839153,   0.1245852401576,
     0.1679157516913,   0.1845737067733,   0.1679157516913,   0.1245852401576,
    0.07170595839153,  0.02969285839245,  0.01381333798044
};

// �߳���������
struct can_app_struct
{
    const char *name;
    struct rt_event canevent;
    struct rt_can_filter_config *filter;
    rt_uint8_t eventopt;
};

class CAN
{
private:
    struct rt_can_msg rx_msg;              // �������ݽṹ��
    rt_device_t       candev;              // can�����豸
    rt_uint32_t       e;

    struct rt_can_msg tx_msg;
    struct rt_can_msg tx_msg_block[MAX_FRAMS];

    struct rt_can_filter_item *event_ops;

    FIR_VEC3F           _enc_fir_filter;

    FIR_VEC3F           _enc_sin_fir_filter;
    FIR_VEC3F           _enc_cos_fir_filter;
    FIR_VEC3F           _motor_speed_fir;

public:
	  Vector3f           motor_enc_raw;
    Vector3f           motor_enc;
    Vector3f           motor_enc_bias;
    Vector3f           angle_mov;
    AP_Float           enc_x_bias;
    AP_Float           enc_y_bias;
    AP_Float           enc_z_bias;
    Vector3f           motor_speed;

    can_param         rx_param;
    can_param         tx_param;
    can_block         rx_block;
    can_block         tx_block;

		bool roll_rps_mcu_ok;
    bool pitch_rps_mcu_ok;
    bool yaw_rps_mcu_ok;
		bool roll_rpl_mcu_ok;
		bool pitch_rpl_mcu_ok;
		bool yaw_rpl_mcu_ok;

		bool motor_config_ready_to_send;
    bool motor_state_ready_to_send;

    motor_param_for_serial motors_params_for_serial[3];
    uint8_t ax_motor_for_serial;

    CAN();
    void start_init();
    void update();
    rt_size_t can_write(struct rt_can_msg msg);

    void get_enc(Vector3f &enc, Vector3f &enc_speed);
		
		void get_enc_trifun(Vector3f &enc);
		
		Vector3f get_enc_raw() {return motor_enc / 57.29577951308232f;};
		
		void encoder_zero_calibration(void);
		
    // user settable parameters
    static const struct AP_Param::GroupInfo var_info[];

		void can_recv_data(void);

    void send_control_rpy(float r_mot, float p_mot, float y_mot);

		void send_control_rp(float roll_motor, float pitch_motor);

    void send_control_y(float yaw_motor);

    void write_param(rt_uint32_t dst_addr, rt_uint32_t param_addr, float value);

		void read_param(rt_uint32_t dst_addr, rt_uint32_t param_addr, float param_value);
		
		void write_block(rt_uint32_t dst_addr, can_block block);
		
		void read_block(rt_uint32_t dst_addr, rt_uint32_t block_id);
		
		void write_test(rt_uint32_t id, int e);
		
};

#endif
#endif