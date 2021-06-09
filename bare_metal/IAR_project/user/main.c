/**
  ******************************************************************
  * @file    main.c
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
#include "fsl_debug_console.h"

#include "board.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "./led/bsp_led.h"   


/*******************************************************************
 * Prototypes
 *******************************************************************/


/*******************************************************************
 * Code
 *******************************************************************/


void delay(uint32_t count)
{
    volatile uint32_t i = 0;
    for (i = 0; i < count; ++i)
    {
        __asm("NOP"); /* ����nop��ָ�� */
    }
}

/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{

    /* ��ʼ������������ */
    BOARD_InitPins();
    /* ��ʼ��������ʱ�� */
    BOARD_BootClockRUN();
    /* ��ʼ�����Դ��� */
    BOARD_InitDebugConsole();
    /* ��ӡϵͳʱ�� */
    PRINTF("\r\n");
    PRINTF("*****��ӭʹ��Ұ��EBF6UL/6ULL������*****\r\n");
    PRINTF("CPU:             %d Hz\r\n", CLOCK_GetFreq(kCLOCK_CpuClk));
    PRINTF("AHB:             %d Hz\r\n", CLOCK_GetFreq(kCLOCK_AhbClk));
    PRINTF("MMDC:            %d Hz\r\n", CLOCK_GetFreq(kCLOCK_MmdcClk));
    PRINTF("SYSPLL:          %d Hz\r\n", CLOCK_GetFreq(kCLOCK_SysPllClk));
    PRINTF("SYSPLLPFD0:      %d Hz\r\n", CLOCK_GetFreq(kCLOCK_SysPllPfd0Clk));
    PRINTF("SYSPLLPFD1:      %d Hz\r\n", CLOCK_GetFreq(kCLOCK_SysPllPfd1Clk));
    PRINTF("SYSPLLPFD2:      %d Hz\r\n", CLOCK_GetFreq(kCLOCK_SysPllPfd2Clk));
    PRINTF("SYSPLLPFD3:      %d Hz\r\n", CLOCK_GetFreq(kCLOCK_SysPllPfd3Clk));  
    /* �����������Ĵ���^_^. */
    

    /* ��ʼ��LED���� */
    LED_GPIO_Config();  
  
    while(1)
    {
      RGB_RED_LED_ON
      delay(0xFFFFF);
      RGB_RED_LED_OFF
        
      RGB_GREEN_LED_ON
      delay(0xFFFFF);
      RGB_GREEN_LED_OFF
        
      RGB_BLUE_LED_ON 
      delay(0xFFFFF);
      RGB_BLUE_LED_OFF
    }     

}
/****************************END OF FILE**********************/

//typedef struct {
//  __IO uint32_t DR;     /**< GPIO data register, offset: 0x0 */
//  __IO uint32_t GDIR;   /**< GPIO direction register, offset: 0x4 */
//  __I  uint32_t PSR;    /**< GPIO pad status register, offset: 0x8 */
//  __IO uint32_t ICR1;   /**< GPIO interrupt configuration register1,*/
//  __IO uint32_t ICR2;   /**< GPIO interrupt configuration register2, */
//  __IO uint32_t IMR;    /**< GPIO interrupt mask register, offset: 0x14 */
//  __IO uint32_t ISR;    /**< GPIO interrupt status register, offset: 0x18 */
//  __IO uint32_t EDGE_SEL;/**< GPIO edge select register, offset: 0x1C */
//} GPIO_Type;
//
///*********************���´���ʡ��***************************8*/
///** Peripheral GPIO1 base address */
//#define GPIO1_BASE                               (0x209C000u)
///** Peripheral GPIO1 base pointer */
//#define GPIO1                                    ((GPIO_Type *)GPIO1_BASE)
//
//
//
//
//
//
//
///***************************��һ����***************************/
//#define IOMUXC_GPIO1_IO00_I2C2_SCL        
//\ 0x020E005CU, 0x0U, 0x020E05ACU, 0x1U, 0x020E02E8U
//#define IOMUXC_GPIO1_IO00_GPT1_CAPTURE1L        
//\ 0x020E005CU, 0x1U, 0x020E058CU, 0x0U, 0x020E02E8U
//#define IOMUXC_GPIO1_IO00_ANATOP_OTG1_IDL        
//\ 0x020E005CU, 0x2U, 0x020E04B8U, 0x0U, 0x020E02E8U
//#define IOMUXC_GPIO1_IO00_ENET1_REF_CLK1L        
//\ 0x020E005CU, 0x3U, 0x020E0574U, 0x0U, 0x020E02E8U
//#define IOMUXC_GPIO1_IO00_MQS_RIGHTL        
//\ 0x020E005CU, 0x4U, 0x00000000U, 0x0U, 0x020E02E8U
//#define IOMUXC_GPIO1_IO00_GPIO1_IO00L        
//\ 0x020E005CU, 0x5U, 0x00000000U, 0x0U, 0x020E02E8U
//#define IOMUXC_GPIO1_IO00_ENET1_1588_EVENT0_INL        
//\ 0x020E005CU, 0x6U, 0x00000000U, 0x0U, 0x020E02E8U
//#define IOMUXC_GPIO1_IO00_SRC_SYSTEM_RESETL        
//\ 0x020E005CU, 0x7U, 0x00000000U, 0x0U, 0x020E02E8U
//#define IOMUXC_GPIO1_IO00_WDOG3_WDOG_BL        
//\ 0x020E005CU, 0x8U, 0x00000000U, 0x0U, 0x020E02E8U
//#define IOMUXC_GPIO1_IO01_I2C2_SDAL        
//\ 0x020E0060U, 0x0U, 0x020E05B0U, 0x1U, 0x020E02ECU
//#define IOMUXC_GPIO1_IO01_GPT1_COMPARE1L        
//\ 0x020E0060U, 0x1U, 0x00000000U, 0x0U, 0x020E02ECU
//#define IOMUXC_GPIO1_IO01_USB_OTG1_OCL        
//\ 0x020E0060U, 0x2U, 0x020E0664U, 0x0U, 0x020E02ECU
//
///***************************�ڶ�����***************************/
//static inline void IOMUXC_SetPinMux(uint32_t muxRegister,
//                                    uint32_t muxMode,
//                                    uint32_t inputRegister,
//                                    uint32_t inputDaisy,
//                                    uint32_t configRegister,
//                                    uint32_t inputOnfield)
//{
//    *((volatile uint32_t *)muxRegister) =
//IOMUXC_SW_MUX_CTL_PAD_MUX_MODE(muxMode) |\
//  IOMUXC_SW_MUX_CTL_PAD_SION(inputOnfield);
//
//    if (inputRegister)
// {
// *((volatile uint32_t *)inputRegister) = \
//   IOMUXC_SELECT_INPUT_DAISY(inputDaisy);
// }
//}
//
//
///***************************��������***************************/
//static inline void IOMUXC_SetPinConfig(uint32_t muxRegister,
//                                       uint32_t muxMode,
//                                       uint32_t inputRegister,
//                                       uint32_t inputDaisy,
//                                       uint32_t configRegister,
//                                       uint32_t configValue)
//{
//    if (configRegister)
//    {
//        *((volatile uint32_t *)configRegister) = configValue;
//    }
//}
