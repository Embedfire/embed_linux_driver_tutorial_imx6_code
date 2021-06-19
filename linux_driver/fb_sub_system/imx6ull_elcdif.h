#ifndef __IMX6ULL_ELCDIF_H
#define __IMX6ULL_ELCDIF_H

/** LCDIF - Register Layout Typedef */
struct imx6ull_elcdif{
  volatile unsigned int CTRL;                              /**< eLCDIF General Control Register, offset: 0x0 */
  volatile unsigned int CTRL_SET;                          /**< eLCDIF General Control Register, offset: 0x4 */
  volatile unsigned int CTRL_CLR;                          /**< eLCDIF General Control Register, offset: 0x8 */
  volatile unsigned int CTRL_TOG;                          /**< eLCDIF General Control Register, offset: 0xC */
  volatile unsigned int CTRL1;                             /**< eLCDIF General Control1 Register, offset: 0x10 */
  volatile unsigned int CTRL1_SET;                         /**< eLCDIF General Control1 Register, offset: 0x14 */
  volatile unsigned int CTRL1_CLR;                         /**< eLCDIF General Control1 Register, offset: 0x18 */
  volatile unsigned int CTRL1_TOG;                         /**< eLCDIF General Control1 Register, offset: 0x1C */
  volatile unsigned int CTRL2;                             /**< eLCDIF General Control2 Register, offset: 0x20 */
  volatile unsigned int CTRL2_SET;                         /**< eLCDIF General Control2 Register, offset: 0x24 */
  volatile unsigned int CTRL2_CLR;                         /**< eLCDIF General Control2 Register, offset: 0x28 */
  volatile unsigned int CTRL2_TOG;                         /**< eLCDIF General Control2 Register, offset: 0x2C */
  volatile unsigned int TRANSFER_COUNT;                    /**< eLCDIF Horizontal and Vertical Valid Data Count Register, offset: 0x30 */
       unsigned char RESERVED_0[12];
  volatile unsigned int CUR_BUF;                           /**< LCD Interface Current Buffer Address Register, offset: 0x40 */
       unsigned char RESERVED_1[12];
  volatile unsigned int NEXT_BUF;                          /**< LCD Interface Next Buffer Address Register, offset: 0x50 */
       unsigned char RESERVED_2[12];
  volatile unsigned int TIMING;                            /**< LCD Interface Timing Register, offset: 0x60 */
       unsigned char RESERVED_3[12];
  volatile unsigned int VDCTRL0;                           /**< eLCDIF VSYNC Mode and Dotclk Mode Control Register0, offset: 0x70 */
  volatile unsigned int VDCTRL0_SET;                       /**< eLCDIF VSYNC Mode and Dotclk Mode Control Register0, offset: 0x74 */
  volatile unsigned int VDCTRL0_CLR;                       /**< eLCDIF VSYNC Mode and Dotclk Mode Control Register0, offset: 0x78 */
  volatile unsigned int VDCTRL0_TOG;                       /**< eLCDIF VSYNC Mode and Dotclk Mode Control Register0, offset: 0x7C */
  volatile unsigned int VDCTRL1;                           /**< eLCDIF VSYNC Mode and Dotclk Mode Control Register1, offset: 0x80 */
       unsigned char RESERVED_4[12];
  volatile unsigned int VDCTRL2;                           /**< LCDIF VSYNC Mode and Dotclk Mode Control Register2, offset: 0x90 */
       unsigned char RESERVED_5[12];
  volatile unsigned int VDCTRL3;                           /**< eLCDIF VSYNC Mode and Dotclk Mode Control Register3, offset: 0xA0 */
       unsigned char RESERVED_6[12];
  volatile unsigned int VDCTRL4;                           /**< eLCDIF VSYNC Mode and Dotclk Mode Control Register4, offset: 0xB0 */
       unsigned char RESERVED_7[12];
  volatile unsigned int DVICTRL0;                          /**< Digital Video Interface Control0 Register, offset: 0xC0 */
       unsigned char RESERVED_8[12];
  volatile unsigned int DVICTRL1;                          /**< Digital Video Interface Control1 Register, offset: 0xD0 */
       unsigned char RESERVED_9[12];
  volatile unsigned int DVICTRL2;                          /**< Digital Video Interface Control2 Register, offset: 0xE0 */
       unsigned char RESERVED_10[12];
  volatile unsigned int DVICTRL3;                          /**< Digital Video Interface Control3 Register, offset: 0xF0 */
       unsigned char RESERVED_11[12];
  volatile unsigned int DVICTRL4;                          /**< Digital Video Interface Control4 Register, offset: 0x100 */
       unsigned char RESERVED_12[12];
  volatile unsigned int CSC_COEFF0;                        /**< RGB to YCbCr 4:2:2 CSC Coefficient0 Register, offset: 0x110 */
       unsigned char RESERVED_13[12];
  volatile unsigned int CSC_COEFF1;                        /**< RGB to YCbCr 4:2:2 CSC Coefficient1 Register, offset: 0x120 */
       unsigned char RESERVED_14[12];
  volatile unsigned int CSC_COEFF2;                        /**< RGB to YCbCr 4:2:2 CSC Coefficent2 Register, offset: 0x130 */
       unsigned char RESERVED_15[12];
  volatile unsigned int CSC_COEFF3;                        /**< RGB to YCbCr 4:2:2 CSC Coefficient3 Register, offset: 0x140 */
       unsigned char RESERVED_16[12];
  volatile unsigned int CSC_COEFF4;                        /**< RGB to YCbCr 4:2:2 CSC Coefficient4 Register, offset: 0x150 */
       unsigned char RESERVED_17[12];
  volatile unsigned int CSC_OFFSET;                        /**< RGB to YCbCr 4:2:2 CSC Offset Register, offset: 0x160 */
       unsigned char RESERVED_18[12];
  volatile unsigned int CSC_LIMIT;                         /**< RGB to YCbCr 4:2:2 CSC Limit Register, offset: 0x170 */
       unsigned char RESERVED_19[12];
  volatile unsigned int DATA;                              /**< LCD Interface Data Register, offset: 0x180 */
       unsigned char RESERVED_20[12];
  volatile unsigned int BM_ERROR_STAT;                     /**< Bus Master Error Status Register, offset: 0x190 */
       unsigned char RESERVED_21[12];
  volatile unsigned int CRC_STAT;                          /**< CRC Status Register, offset: 0x1A0 */
       unsigned char RESERVED_22[12];
  volatile const   unsigned int STAT;                              /**< LCD Interface Status Register, offset: 0x1B0 */
       unsigned char RESERVED_23[76];
  volatile unsigned int THRES;                             /**< eLCDIF Threshold Register, offset: 0x200 */
       unsigned char RESERVED_24[12];
  volatile unsigned int AS_CTRL;                           /**< eLCDIF AS Buffer Control Register, offset: 0x210 */
       unsigned char RESERVED_25[12];
  volatile unsigned int AS_BUF;                            /**< Alpha Surface Buffer Pointer, offset: 0x220 */
       unsigned char RESERVED_26[12];
  volatile unsigned int AS_NEXT_BUF;                       /**< , offset: 0x230 */
       unsigned char RESERVED_27[12];
  volatile unsigned int AS_CLRKEYLOW;                      /**< eLCDIF Overlay Color Key Low, offset: 0x240 */
       unsigned char RESERVED_28[12];
  volatile unsigned int AS_CLRKEYHIGH;                     /**< eLCDIF Overlay Color Key High, offset: 0x250 */
       unsigned char RESERVED_29[12];
  volatile unsigned int SYNC_DELAY;                        /**< LCD working insync mode with CSI for VSYNC delay, offset: 0x260 */
} ;


#endif /* __IMX6ULL_ELCDIF_H */

