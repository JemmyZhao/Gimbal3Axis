/*
 * File      : gpio.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2015, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2015-01-05     Bernard      the first version
 */

#include "gpio.h"

/*
 * GPIO devices
 */
gpio_dev gpioa = {
    .GPIOx     = GPIOA,
    .clk       = RCC_AHB1Periph_GPIOA,
    .clkcmd    = RCC_AHB1PeriphClockCmd,
};
/** GPIO port A device. */
gpio_dev* _GPIOA = &gpioa;

gpio_dev gpiob = {
    .GPIOx      = GPIOB,
    .clk       = RCC_AHB1Periph_GPIOB,
    .clkcmd    = RCC_AHB1PeriphClockCmd,
};
/** GPIO port B device. */
gpio_dev* _GPIOB = &gpiob;

gpio_dev gpioc = {
    .GPIOx      = GPIOC,
    .clk       = RCC_AHB1Periph_GPIOC,
    .clkcmd    = RCC_AHB1PeriphClockCmd,
};
/** GPIO port C device. */
gpio_dev* _GPIOC = &gpioc;

gpio_dev gpiod = {
    .GPIOx      = GPIOD,
    .clk       = RCC_AHB1Periph_GPIOD,
    .clkcmd    = RCC_AHB1PeriphClockCmd,
};
/** GPIO port D device. */
gpio_dev* _GPIOD = &gpiod;

gpio_dev gpioe = {
    .GPIOx      = GPIOE,
    .clk       = RCC_AHB1Periph_GPIOE,
    .clkcmd    = RCC_AHB1PeriphClockCmd,
};
/** GPIO port E device. */
gpio_dev* _GPIOE = &gpioe;

// GPIO引脚映射阵列
stm32_pin_info PIN_MAP[BOARD_NR_GPIO_PINS];

/* 引脚阵列初始化 */
void set_pin_map_para(uint8_t gpio_pin, 
                      gpio_dev *GPIOx_dev, 
                      timer_dev *TIMx_dev, 
                      const adc_dev *ADCx_dev, 
                      uint16_t gpio_bit, 
                      uint8_t timer_channel, 
                      uint8_t adc_channel,
                      uint16_t GPIO_PinSource,
                      uint8_t GPIO_AF)
{
	PIN_MAP[gpio_pin].gpio_device   = GPIOx_dev;
	PIN_MAP[gpio_pin].timer_device  = TIMx_dev;
	PIN_MAP[gpio_pin].adc_device    = ADCx_dev;
	PIN_MAP[gpio_pin].gpio_bit      = gpio_bit;
	PIN_MAP[gpio_pin].timer_channel = timer_channel;
	PIN_MAP[gpio_pin].adc_channel   = adc_channel;
    PIN_MAP[gpio_pin].GPIO_PinSource= GPIO_PinSource;
    PIN_MAP[gpio_pin].GPIO_AF       = GPIO_AF;
}

void GPIO_OUT(uint8_t pin, uint8_t value)
{
    if(value)
        PIN_MAP[pin].gpio_device->GPIOx->BSRRL = BIT(PIN_MAP[pin].gpio_bit);
    else
        PIN_MAP[pin].gpio_device->GPIOx->BSRRH = BIT(PIN_MAP[pin].gpio_bit);
}

/* 初始化引脚阵列 */
void init_gpio_map()
{	
	//              GPIO    PORT     TIMERx     ADCx    Bit| TIM|ADC  GPIO_PinSource    GPIO_AF
	set_pin_map_para(PA0,  _GPIOA,   RT_NULL,   RT_NULL,  0, 0, ADCx, GPIO_PinSource0,  RT_NULL); // D00/PA0
	set_pin_map_para(PA1,  _GPIOA,   RT_NULL,   RT_NULL,  1, 0, ADCx, GPIO_PinSource1,  RT_NULL); // D01/PA1
	set_pin_map_para(PA2,  _GPIOA,   RT_NULL,   RT_NULL,  2, 0, ADCx, GPIO_PinSource2,  GPIO_AF_USART2); // D02/PA2    -->UART2_TX
	set_pin_map_para(PA3,  _GPIOA,   RT_NULL,   RT_NULL,  3, 0, ADCx, GPIO_PinSource3,  GPIO_AF_USART2); // D03/PA3    <--UART2_RX
	set_pin_map_para(PA4,  _GPIOA,   RT_NULL,   RT_NULL,  4, 0, ADCx, GPIO_PinSource4,  RT_NULL); // D04/PA4
	set_pin_map_para(PA5,  _GPIOA,   RT_NULL,   RT_NULL,  5, 0, ADCx, GPIO_PinSource5,  GPIO_AF_SPI1); // D05/PA5
	set_pin_map_para(PA6,  _GPIOA,   RT_NULL,   RT_NULL,  6, 0, ADCx, GPIO_PinSource6,  GPIO_AF_SPI1); // D06/PA6
	set_pin_map_para(PA7,  _GPIOA,   RT_NULL,   RT_NULL,  7, 0, ADCx, GPIO_PinSource7,  GPIO_AF_SPI1); // D07/PA7
	set_pin_map_para(PA8,  _GPIOA,   RT_NULL,   RT_NULL,  8, 0, ADCx, GPIO_PinSource8,  RT_NULL); // D08/PA8
	set_pin_map_para(PA9,  _GPIOA,   RT_NULL,   RT_NULL,  9, 0, ADCx, GPIO_PinSource9,  GPIO_AF_USART1); // D09/PA9     -->UART1_TX
	set_pin_map_para(PA10, _GPIOA,   RT_NULL,   RT_NULL, 10, 0, ADCx, GPIO_PinSource10, GPIO_AF_USART1); // D10/PA10    <--UART1_RX
	set_pin_map_para(PA11, _GPIOA,   RT_NULL,   RT_NULL, 11, 0, ADCx, GPIO_PinSource11, RT_NULL); // D11/PA11
	set_pin_map_para(PA12, _GPIOA,   RT_NULL,   RT_NULL, 12, 0, ADCx, GPIO_PinSource12, RT_NULL); // D12/PA12
	set_pin_map_para(PA13, _GPIOA,   RT_NULL,   RT_NULL, 13, 0, ADCx, GPIO_PinSource13, RT_NULL); // D13/PA13
	set_pin_map_para(PA14, _GPIOA,   RT_NULL,   RT_NULL, 14, 0, ADCx, GPIO_PinSource14, RT_NULL); // D14/PA14
	set_pin_map_para(PA15, _GPIOA,   RT_NULL,   RT_NULL, 15, 0, ADCx, GPIO_PinSource15, RT_NULL); // D15/PA15
	
	set_pin_map_para(PB0,  _GPIOB,   RT_NULL,   RT_NULL,  0, 0, ADCx, GPIO_PinSource0,  RT_NULL); // D16/PB0
	set_pin_map_para(PB1,  _GPIOB,   RT_NULL,   RT_NULL,  1, 0, ADCx, GPIO_PinSource1,  RT_NULL); // D17/PB1
	set_pin_map_para(PB2,  _GPIOB,   RT_NULL,   RT_NULL,  2, 0, ADCx, GPIO_PinSource3,  RT_NULL); // D18/PB2
	set_pin_map_para(PB3,  _GPIOB,   RT_NULL,   RT_NULL,  3, 0, ADCx, GPIO_PinSource3,  RT_NULL); // D19/PB3      -->SPI1_SCK
	set_pin_map_para(PB4,  _GPIOB,   RT_NULL,   RT_NULL,  4, 0, ADCx, GPIO_PinSource4,  RT_NULL); // D20/PB4      <--SPI1_MISO
	set_pin_map_para(PB5,  _GPIOB,   RT_NULL,   RT_NULL,  5, 0, ADCx, GPIO_PinSource5,  RT_NULL); // D21/PB5      -->SPI1_MOSI
    
	set_pin_map_para(PB6,  _GPIOB,   RT_NULL,   RT_NULL,  6, 0, ADCx, GPIO_PinSource6,  GPIO_AF_I2C1); // D22/PB6      -->I2C1_SCL
	set_pin_map_para(PB7,  _GPIOB,   RT_NULL,   RT_NULL,  7, 0, ADCx, GPIO_PinSource7,  GPIO_AF_I2C1); // D23/PB7      -->I2C1_SDA
    
	set_pin_map_para(PB8,  _GPIOB,   RT_NULL,   RT_NULL,  8, 0, ADCx, GPIO_PinSource8,  GPIO_AF_CAN1); // D24/PB8           -->SPI1_CS1
	set_pin_map_para(PB9,  _GPIOB,   RT_NULL,   RT_NULL,  9, 0, ADCx, GPIO_PinSource9,  GPIO_AF_CAN1); // D25/PB9           -->SPI1_CS2
	set_pin_map_para(PB10, _GPIOB,   RT_NULL,   RT_NULL, 10, 0, ADCx, GPIO_PinSource10, GPIO_AF_I2C2); // D26/PB10     -->I2C2_SCL
	set_pin_map_para(PB11, _GPIOB,   RT_NULL,   RT_NULL, 11, 0, ADCx, GPIO_PinSource11, GPIO_AF_I2C2); // D27/PB11     -->I2C2_SDA
	set_pin_map_para(PB12, _GPIOB,   RT_NULL,   RT_NULL, 12, 0, ADCx, GPIO_PinSource12, RT_NULL); // D28/PB12          -->HMC5983_CS
	set_pin_map_para(PB13, _GPIOB,   RT_NULL,   RT_NULL, 13, 0, ADCx, GPIO_PinSource13, GPIO_AF_SPI2); // D29/PB13     -->SPI2_SCK
	set_pin_map_para(PB14, _GPIOB,   RT_NULL,   RT_NULL, 14, 0, ADCx, GPIO_PinSource14, GPIO_AF_SPI2); // D30/PB14     <--SPI2_MISO
	set_pin_map_para(PB15, _GPIOB,   RT_NULL,   RT_NULL, 15, 0, ADCx, GPIO_PinSource15, GPIO_AF_SPI2); // D31/PB15     -->SPI2_MOSI
	
	set_pin_map_para(PC0,  _GPIOC,   RT_NULL,   RT_NULL,  0, 0, ADCx, GPIO_PinSource0,  RT_NULL); // D32/PC0
	set_pin_map_para(PC1,  _GPIOC,   RT_NULL,   RT_NULL,  1, 0, ADCx, GPIO_PinSource1,  RT_NULL); // D33/PC1
	set_pin_map_para(PC2,  _GPIOC,   RT_NULL,   RT_NULL,  2, 0, ADCx, GPIO_PinSource2,  RT_NULL); // D34/PC2
	set_pin_map_para(PC3,  _GPIOC,   RT_NULL,   RT_NULL,  3, 0, ADCx, GPIO_PinSource3,  RT_NULL); // D35/PC3
	set_pin_map_para(PC4,  _GPIOC,   RT_NULL,   RT_NULL,  4, 0, ADCx, GPIO_PinSource4,  RT_NULL); // D36/PC4
	set_pin_map_para(PC5,  _GPIOC,   RT_NULL,   RT_NULL,  5, 0, ADCx, GPIO_PinSource5,  RT_NULL); // D37/PC5
	set_pin_map_para(PC6,  _GPIOC,   RT_NULL,   RT_NULL,  6, 0, ADCx, GPIO_PinSource6,  GPIO_AF_USART6); // D38/PC6          
	set_pin_map_para(PC7,  _GPIOC,   RT_NULL,   RT_NULL,  7, 0, ADCx, GPIO_PinSource7,  GPIO_AF_USART6); // D39/PC7          -->SDIO_C0
	set_pin_map_para(PC8,  _GPIOC,   RT_NULL,   RT_NULL,  8, 0, ADCx, GPIO_PinSource8,  GPIO_AF_SDIO); // D40/PC8     -->SDIO_D0
	set_pin_map_para(PC9,  _GPIOC,   RT_NULL,   RT_NULL,  9, 0, ADCx, GPIO_PinSource9,  GPIO_AF_SDIO); // D41/PC9     -->SDIO_D1
	set_pin_map_para(PC10, _GPIOC,   RT_NULL,   RT_NULL, 10, 0, ADCx, GPIO_PinSource10, GPIO_AF_SDIO); // D42/PC10    -->SDIO_D2
	set_pin_map_para(PC11, _GPIOC,   RT_NULL,   RT_NULL, 11, 0, ADCx, GPIO_PinSource11, GPIO_AF_SDIO); // D43/PC11    -->SDIO_D3
	set_pin_map_para(PC12, _GPIOC,   RT_NULL,   RT_NULL, 12, 0, ADCx, GPIO_PinSource12, GPIO_AF_SDIO); // D44/PC12    -->SDIO_CK
	set_pin_map_para(PC13, _GPIOC,   RT_NULL,   RT_NULL, 13, 0, ADCx, GPIO_PinSource13, RT_NULL); // D45/PC13
	set_pin_map_para(PC14, _GPIOC,   RT_NULL,   RT_NULL, 14, 0, ADCx, GPIO_PinSource14, RT_NULL); // D46/PC14
	set_pin_map_para(PC15, _GPIOC,   RT_NULL,   RT_NULL, 15, 0, ADCx, GPIO_PinSource15, RT_NULL); // D47/PC15
	
	set_pin_map_para(PD0,  _GPIOD,   RT_NULL,   RT_NULL,  0, 0, ADCx, GPIO_PinSource0,  RT_NULL); // D48/PD0       <--CAN1_RX
	set_pin_map_para(PD1,  _GPIOD,   RT_NULL,   RT_NULL,  1, 0, ADCx, GPIO_PinSource1,  RT_NULL); // D49/PD1       -->CAN1_TX
	set_pin_map_para(PD2,  _GPIOD,   RT_NULL,   RT_NULL,  2, 0, ADCx, GPIO_PinSource2,  GPIO_AF_SDIO); // D50/PD2       -->SDIO_CMD
    set_pin_map_para(PD3,  _GPIOD,   RT_NULL,   RT_NULL,  3, 0, ADCx, GPIO_PinSource3,  RT_NULL); // D51/PD3            -->CAN1_EN
	set_pin_map_para(PD4,  _GPIOD,   RT_NULL,   RT_NULL,  4, 0, ADCx, GPIO_PinSource4,  RT_NULL); // D52/PD4
	set_pin_map_para(PD5,  _GPIOD,   RT_NULL,   RT_NULL,  5, 0, ADCx, GPIO_PinSource5,  RT_NULL); // D53/PD5
	set_pin_map_para(PD6,  _GPIOD,   RT_NULL,   RT_NULL,  6, 0, ADCx, GPIO_PinSource6,  RT_NULL); // D54/PD6            
	set_pin_map_para(PD7,  _GPIOD,   RT_NULL,   RT_NULL,  7, 0, ADCx, GPIO_PinSource7,  RT_NULL); // D55/PD7            -->MPU_CS
	set_pin_map_para(PD8,  _GPIOD,   RT_NULL,   RT_NULL,  8, 0, ADCx, GPIO_PinSource8,  GPIO_AF_USART3); // D56/PD8     -->UART3_TX
	set_pin_map_para(PD9,  _GPIOD,   RT_NULL,   RT_NULL,  9, 0, ADCx, GPIO_PinSource9,  GPIO_AF_USART3); // D57/PD9     <--UART3_RX
	
	set_pin_map_para(PD10, _GPIOD,   RT_NULL,   RT_NULL, 10, 0, ADCx, GPIO_PinSource10, RT_NULL); // D58/PD10
	set_pin_map_para(PD11, _GPIOD,   RT_NULL,   RT_NULL, 11, 0, ADCx, GPIO_PinSource11, RT_NULL); // D59/PD11
	set_pin_map_para(PD12, _GPIOD,   RT_NULL,   RT_NULL, 12, 0, ADCx, GPIO_PinSource12, RT_NULL); // D60/PD12 LED
	set_pin_map_para(PD13, _GPIOD,   RT_NULL,   RT_NULL, 13, 0, ADCx, GPIO_PinSource13, RT_NULL); // D61/PD13 LED
	set_pin_map_para(PD14, _GPIOD,   RT_NULL,   RT_NULL, 14, 0, ADCx, GPIO_PinSource14, RT_NULL); // D62/PD14 LED
	set_pin_map_para(PD15, _GPIOD,   RT_NULL,   RT_NULL, 15, 0, ADCx, GPIO_PinSource15, RT_NULL); // D63/PD15 LED
    
    set_pin_map_para(PE0,  _GPIOE,   RT_NULL,   RT_NULL,  0, 0, ADCx, GPIO_PinSource0,  RT_NULL); // D64/PE0
	set_pin_map_para(PE1,  _GPIOE,   RT_NULL,   RT_NULL,  1, 0, ADCx, GPIO_PinSource1,  RT_NULL); // D65/PE1  
	set_pin_map_para(PE2,  _GPIOE,   RT_NULL,   RT_NULL,  2, 0, ADCx, GPIO_PinSource2,  RT_NULL); // D66/PE2  
    set_pin_map_para(PE3,  _GPIOE,   RT_NULL,   RT_NULL,  3, 0, ADCx, GPIO_PinSource3,  RT_NULL); // D67/PE3  
	set_pin_map_para(PE4,  _GPIOE,   RT_NULL,   RT_NULL,  4, 0, ADCx, GPIO_PinSource4,  RT_NULL); // D68/PE4  
	set_pin_map_para(PE5,  _GPIOE,   RT_NULL,   RT_NULL,  5, 0, ADCx, GPIO_PinSource5,  RT_NULL); // D69/PE5  
	set_pin_map_para(PE6,  _GPIOE,   RT_NULL,   RT_NULL,  6, 0, ADCx, GPIO_PinSource6,  RT_NULL); // D70/PE6  
	set_pin_map_para(PE7,  _GPIOE,   RT_NULL,   RT_NULL,  7, 0, ADCx, GPIO_PinSource7,  RT_NULL); // D71/PE7  
	set_pin_map_para(PE8,  _GPIOE,   RT_NULL,   RT_NULL,  8, 0, ADCx, GPIO_PinSource8,  RT_NULL); // D72/PE8  
	set_pin_map_para(PE9,  _GPIOE,   RT_NULL,   RT_NULL,  9, 0, ADCx, GPIO_PinSource9,  RT_NULL); // D73/PE9  
	set_pin_map_para(PE10, _GPIOE,   RT_NULL,   RT_NULL, 10, 0, ADCx, GPIO_PinSource10, RT_NULL); // D74/PE10 
	set_pin_map_para(PE11, _GPIOE,   RT_NULL,   RT_NULL, 11, 0, ADCx, GPIO_PinSource11, RT_NULL); // D75/PE11 
	set_pin_map_para(PE12, _GPIOE,   RT_NULL,   RT_NULL, 12, 0, ADCx, GPIO_PinSource12, RT_NULL); // D76/PE12 
	set_pin_map_para(PE13, _GPIOE,   RT_NULL,   RT_NULL, 13, 0, ADCx, GPIO_PinSource13, RT_NULL); // D77/PE13 
	set_pin_map_para(PE14, _GPIOE,   RT_NULL,   RT_NULL, 14, 0, ADCx, GPIO_PinSource14, RT_NULL); // D78/PE14 
	set_pin_map_para(PE15, _GPIOE,   RT_NULL,   RT_NULL, 15, 0, ADCx, GPIO_PinSource15, RT_NULL); // D79/PE15 
}

/* GPIO引脚初始化 */
void gpio_init(const gpio_dev* dev) 
{
	/* Check the parameters */
	assert_param(IS_GPIO_ALL_PERIPH(dev->GPIOx));
    // 初始化GPIO控制寄存器
	//GPIO_DeInit(dev->GPIOx);
	/* Enable the GPIO Clock  */
	//LASER_PWM_PATCH
	dev->clkcmd(dev->clk, ENABLE);
}

/* 依次初始化所有GPIO口 */
void gpio_foreach(void (*gpio_config)(const gpio_dev*))
{
    gpio_config(_GPIOA);
    gpio_config(_GPIOB);
    gpio_config(_GPIOC);
    gpio_config(_GPIOD);
    gpio_config(_GPIOE);
}

/* 初始化所有GPIO脚,启用复用引脚 */
void gpio_clock_init_all()
{
	gpio_foreach(gpio_init);
}

/* GPIO引脚模式初始化 */
void gpio_set_mode(gpio_dev* dev, uint8_t pin, gpio_pin_mode mode)
{
	/* Check the parameters */
	assert_param(IS_GPIO_ALL_PERIPH(dev->GPIOx));
	assert_param(IS_GPIO_PIN_SOURCE(pin));
	
	GPIO_InitTypeDef config;
	
	/* Enable the GPIO Clock  */
	dev->clkcmd(dev->clk, ENABLE);
  
	/* Configure the pin */
	GPIO_StructInit(&config);
	config.GPIO_Speed = GPIO_DEFAULT_SPEED;
    switch(mode) 
    {
		case GPIO_OUTPUT_PP:
            config.GPIO_Mode  = GPIO_Mode_OUT;
			config.GPIO_OType = GPIO_OType_PP;
            config.GPIO_PuPd  = GPIO_PuPd_NOPULL;
			break;
		case GPIO_OUTPUT_OD:
			config.GPIO_Mode  = GPIO_Mode_OUT;
			config.GPIO_OType = GPIO_OType_OD;
            config.GPIO_PuPd  = GPIO_PuPd_NOPULL;
			break;
		case GPIO_INPUT_FLOATING:
			config.GPIO_Mode  = GPIO_Mode_AF;
            config.GPIO_PuPd  = GPIO_PuPd_NOPULL;
			break;
		case GPIO_INPUT_ANALOG:
			config.GPIO_Mode  = GPIO_Mode_AIN;
            config.GPIO_PuPd  = GPIO_PuPd_NOPULL;
			break;
		case GPIO_INPUT_PU:
			config.GPIO_Mode  = GPIO_Mode_IN;
            config.GPIO_PuPd  = GPIO_PuPd_UP;
			break;
		case GPIO_INPUT_PD:
			config.GPIO_Mode  = GPIO_Mode_IN;
            config.GPIO_PuPd  = GPIO_PuPd_DOWN;
			break;
		case GPIO_AF_OUTPUT_PP:
			config.GPIO_Mode  = GPIO_Mode_AF;
            config.GPIO_OType = GPIO_OType_PP;
            config.GPIO_PuPd  = GPIO_PuPd_NOPULL;
			break;
		case GPIO_AF_OUTPUT_OD:
			config.GPIO_Mode  = GPIO_Mode_AF;
            config.GPIO_OType = GPIO_OType_OD;
            config.GPIO_PuPd  = GPIO_PuPd_NOPULL;
			break;
        case COM_MODE:
            config.GPIO_Mode  = GPIO_Mode_AF;
            config.GPIO_OType = GPIO_OType_PP;
            config.GPIO_PuPd  = GPIO_PuPd_UP;
            break;
		default:
            #ifdef RT_USING_FINSH
			rt_kprintf("Invalid argument\n");
            #endif
			return;
    }
	config.GPIO_Pin = BIT(pin);
	GPIO_Init(dev->GPIOx, &config);      	
}

/* GPIO引脚模式初始化(包含对应模式下的外设设置) */
void Set_pinMode(uint8_t pin, GPIO_PinMode mode)
{
    gpio_pin_mode outputMode;
    rt_bool_t pwm = RT_FALSE;

    if (pin >= BOARD_NR_GPIO_PINS)
        return;
    
    switch(mode)
	{
    case OUTPUT:
        outputMode = GPIO_OUTPUT_PP;
        break;
    case OUTPUT_OPEN_DRAIN:
        outputMode = GPIO_OUTPUT_OD;
        break;
    case INPUT:
    case INPUT_FLOATING:
        outputMode = GPIO_INPUT_FLOATING;
        break;
    case INPUT_ANALOG:
        outputMode = GPIO_INPUT_ANALOG;
        break;
    case INPUT_PULLUP:
        outputMode = GPIO_INPUT_PU;
        break;
    case INPUT_PULLDOWN:
        outputMode = GPIO_INPUT_PD;
        break;
    case AF_OUTPUT:
        outputMode = GPIO_AF_OUTPUT_PP;
        pwm = RT_TRUE;
        break;
    case PWM_OPEN_DRAIN:
        outputMode = GPIO_AF_OUTPUT_OD;
        pwm = RT_TRUE;
        break;
    case TRANS_PIN_MODE:
        outputMode = COM_MODE;
        break;
    default:
        assert_param(0);
        return;
    }
    gpio_set_mode(PIN_MAP[pin].gpio_device, PIN_MAP[pin].gpio_bit, outputMode);

    if (PIN_MAP[pin].timer_device != RT_NULL)
	{
        /* Enable/disable timer channels if we're switching into or out of PWM. */
		if (pwm) 
			timer_set_mode(PIN_MAP[pin].timer_device,PIN_MAP[pin].timer_channel,pwm ? TIMER_PWM : TIMER_DISABLED);
    } 
    if(PIN_MAP[pin].GPIO_AF != RT_NULL && PIN_MAP[pin].GPIO_PinSource != RT_NULL)
    {
        GPIO_PinAFConfig(PIN_MAP[pin].gpio_device->GPIOx, PIN_MAP[pin].GPIO_PinSource, PIN_MAP[pin].GPIO_AF);
    }
}
