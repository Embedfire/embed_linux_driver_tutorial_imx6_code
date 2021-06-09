/**
  ******************************************************************
  * @file    bsp_led.c
  * @author  fire
  * @version V1.0
  * @date    2018-xx-xx
  * @brief   ��V2.3.1�汾�⽨�Ĺ���ģ��
  ******************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ��EBF6UL/6ULL������
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :http://firestm32.taobao.com
  *
  ******************************************************************
  */
#include "fsl_iomuxc.h"
#include "fsl_gpio.h"  
  
#include "pad_config.h"  
#include "./led/bsp_led.h"   


/*******************************************************************************
 * ��
 ******************************************************************************/
/* �������ž�ʹ��ͬ����PAD���� */
#define LED_PAD_CONFIG_DATA            (SRE_0_SLOW_SLEW_RATE| \
                                        DSE_6_R0_6| \
                                        SPEED_2_MEDIUM_100MHz| \
                                        ODE_0_OPEN_DRAIN_DISABLED| \
                                        PKE_0_PULL_KEEPER_DISABLED| \
                                        PUE_0_KEEPER_SELECTED| \
                                        PUS_0_100K_OHM_PULL_DOWN| \
                                        HYS_0_HYSTERESIS_DISABLED)   
    /* ����˵�� : */
    /* ת������: ת��������
      ����ǿ��: R0/6 
      �������� : medium(100MHz)
      ��©����: �ر� 
      ��/����������: �ر�
      ��/������ѡ��: �������������ѹرգ�������Ч��
      ����/����ѡ��: 100Kŷķ�����������ѹرգ�������Ч��
      �ͻ�������: �ر� */     

/*******************************************************************************
 * ����
 ******************************************************************************/
static void LED_IOMUXC_MUX_Config(void);
static void LED_IOMUXC_PAD_Config(void);
static void LED_GPIO_Mode_Config(void);

/**
* @brief  ��ʼ��LED���IOMUXC��MUX��������
* @param  ��
* @retval ��
*/
static void LED_IOMUXC_MUX_Config(void)
{
  /* RGB LED�ƣ�ʹ��ͬ����IOMUXC MUX���� */  
  IOMUXC_SetPinMux(RGB_RED_LED_IOMUXC, 0U); 
  IOMUXC_SetPinMux(RGB_BLUE_LED_IOMUXC, 0U);  
  IOMUXC_SetPinMux(RGB_GREEN_LED_IOMUXC, 0U);
}

/**
* @brief  ��ʼ��LED���IOMUXC��MUX��������
* @param  ��
* @retval ��
*/
static void LED_IOMUXC_PAD_Config(void)
{ 
 
  /* RGB LED�ƣ�ʹ��ͬ����IOMUXC PAD���� */ 
  IOMUXC_SetPinConfig(RGB_RED_LED_IOMUXC, LED_PAD_CONFIG_DATA); 
  IOMUXC_SetPinConfig(RGB_GREEN_LED_IOMUXC, LED_PAD_CONFIG_DATA); 
  IOMUXC_SetPinConfig(RGB_BLUE_LED_IOMUXC, LED_PAD_CONFIG_DATA);  
}


 /**
  * @brief  ��ʼ��LED��ص�GPIOģʽ
  * @param  ��
  * @retval ��
  */
static void LED_GPIO_Mode_Config(void)
{     
  /* ����gpio��ʼ�����ýṹ�� */
  gpio_pin_config_t led_config;      
    
   /** ���İ��LED�ƣ�GPIO���� **/       
  led_config.direction = kGPIO_DigitalOutput; //���ģʽ
  led_config.outputLogic =  1;                //Ĭ�ϸߵ�ƽ    
  led_config.interruptMode = kGPIO_NoIntmode; //��ʹ���ж�
  
  /* ʹ��ͬ����LED config����RGB LED�� */
  GPIO_PinInit(RGB_RED_LED_GPIO, RGB_RED_LED_GPIO_PIN, &led_config);
  GPIO_PinInit(RGB_GREEN_LED_GPIO, RGB_GREEN_LED_GPIO_PIN, &led_config);
  GPIO_PinInit(RGB_BLUE_LED_GPIO, RGB_BLUE_LED_GPIO_PIN, &led_config);
}

/**
  * @brief  ��ʼ������LED��IO
  * @param  ��
  * @retval ��
  */
void LED_GPIO_Config(void)
{
  /* ��ʼ��GPIO���á����ԡ�ģʽ */
  LED_IOMUXC_MUX_Config();
  LED_IOMUXC_PAD_Config();
  LED_GPIO_Mode_Config();
}


/*********************************************END OF FILE**********************/
