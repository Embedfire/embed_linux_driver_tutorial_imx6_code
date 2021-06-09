#ifndef __BSP_LED_H
#define __BSP_LED_H

#include "fsl_common.h"

/*********************************************************
 * LED GPIO�˿ڡ����źż�IOMUXC���ú궨��
 *********************************************************/

#define RGB_RED_LED_GPIO                GPIO1
#define RGB_RED_LED_GPIO_PIN            (4U)
#define RGB_RED_LED_IOMUXC              IOMUXC_GPIO1_IO04_GPIO1_IO04

#define RGB_GREEN_LED_GPIO              GPIO4
#define RGB_GREEN_LED_GPIO_PIN          (20U)
#define RGB_GREEN_LED_IOMUXC            IOMUXC_CSI_HSYNC_GPIO4_IO20

#define RGB_BLUE_LED_GPIO               GPIO4
#define RGB_BLUE_LED_GPIO_PIN           (19U)
#define RGB_BLUE_LED_IOMUXC             IOMUXC_CSI_VSYNC_GPIO4_IO19

#define LED_DELAY_COUNT                 70000000



/* ʹ�ñ�׼�Ĺ̼������IO 
   ʹ�÷�����CORE_BOARD_LED(ON); */
   

#define   RGB_RED_LED(a)  if (a)  \
          GPIO_PinWrite(RGB_RED_LED_GPIO, RGB_RED_LED_GPIO_PIN, 0U);\
          else    \
          GPIO_PinWrite(RGB_RED_LED_GPIO, RGB_RED_LED_GPIO_PIN, 1U);

#define   RGB_GREEN_LED(a)  if (a)  \
          GPIO_PinWrite(RGB_RGB_GREEN_LED_GPIO, RGB_RGB_GREEN_LED_GPIO_PIN, 0U);\
          else    \
          GPIO_PinWrite(RGB_GREEN_LED_GPIO, RGB_GREEN_LED_GPIO_PIN, 1U);

#define   RGB_BLUE_LED(a) if (a)  \
          GPIO_PinWrite(RGB_BLUE_LED_GPIO, RGB_BLUE_LED_GPIO_PIN, 0U);\
          else    \
          GPIO_PinWrite(RGB_BLUE_LED_GPIO, RGB_BLUE_LED_GPIO_PIN, 1U);     


/* ֱ�Ӳ����Ĵ����ķ�������IO */
#define digitalHi(p,i)      {p->DR |= (1U << i);}   //���Ϊ�ߵ�ƽ    
#define digitalLo(p,i)      {p->DR &= ~(1U << i);}  //����͵�ƽ
#define digitalToggle(p,i)  {p->DR ^= (1U<<i);}     //�����ת״̬
          


          /* �������IO�ĺ� */

#define RGB_RED_LED_TOGGLE          digitalToggle(RGB_RED_LED_GPIO,RGB_RED_LED_GPIO_PIN)
#define RGB_RED_LED_OFF             digitalHi(RGB_RED_LED_GPIO,RGB_RED_LED_GPIO_PIN)
#define RGB_RED_LED_ON              digitalLo(RGB_RED_LED_GPIO,RGB_RED_LED_GPIO_PIN)

#define RGB_GREEN_LED_TOGGLE        digitalToggle(RGB_GREEN_LED_GPIO,RGB_GREEN_LED_GPIO_PIN)
#define RGB_GREEN_LED_OFF           digitalHi(RGB_GREEN_LED_GPIO,RGB_GREEN_LED_GPIO_PIN)
#define RGB_GREEN_LED_ON            digitalLo(RGB_GREEN_LED_GPIO,RGB_GREEN_LED_GPIO_PIN)

#define RGB_BLUE_LED_TOGGLE         digitalToggle(RGB_BLUE_LED_GPIO,RGB_BLUE_LED_GPIO_PIN)
#define RGB_BLUE_LED_OFF            digitalHi(RGB_BLUE_LED_GPIO,RGB_BLUE_LED_GPIO_PIN)
#define RGB_BLUE_LED_ON             digitalLo(RGB_BLUE_LED_GPIO,RGB_BLUE_LED_GPIO_PIN)


/*******************************************************************************
 * ��������
 ******************************************************************************/
void LED_GPIO_Config(void);

#endif /* __BSP_LED_H */
