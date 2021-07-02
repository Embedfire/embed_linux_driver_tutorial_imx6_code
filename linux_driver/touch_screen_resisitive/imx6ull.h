#ifndef __IMX6ULL_H
#define __IMX6ULL_H


/** ADC_5HC - Register Layout Typedef */
struct imx6ull_adc{
  volatile unsigned int HC[5];                             /**< Control register for hardware triggers, array offset: 0x0, array step: 0x4 */
  volatile unsigned int HS;                                /**< Status register for HW triggers, offset: 0x14 */
  volatile unsigned int R[5];                              /**< Data result register for HW triggers, array offset: 0x18, array step: 0x4 */
  volatile unsigned int CFG;                               /**< Configuration register, offset: 0x2C */
  volatile unsigned int GC;                                /**< General control register, offset: 0x30 */
  volatile unsigned int GS;                                /**< General status register, offset: 0x34 */
  volatile unsigned int CV;                                /**< Compare value register, offset: 0x38 */
  volatile unsigned int OFS;                               /**< Offset correction value register, offset: 0x3C */
  volatile unsigned int CAL;                               /**< Calibration value register, offset: 0x40 */
};


/** TSC - Register Layout Typedef */
struct imx6ull_tsc{
  volatile unsigned int BASIC_SETTING;                     /**< PS Input Buffer Address, offset: 0x0 */
  volatile unsigned char RESERVED_0[12];
  volatile unsigned int PS_INPUT_BUFFER_ADDR;              /**< PS Input Buffer Address, offset: 0x10 */
  volatile unsigned char RESERVED_1[12];
  volatile unsigned int FLOW_CONTROL;                      /**< Flow Control, offset: 0x20 */
  volatile unsigned char RESERVED_2[12];
  volatile unsigned int MEASEURE_VALUE;                    /**< Measure Value, offset: 0x30 */
  volatile unsigned char RESERVED_3[12];
  volatile unsigned int INT_EN;                            /**< Interrupt Enable, offset: 0x40 */
  volatile unsigned char RESERVED_4[12];
  volatile unsigned int INT_SIG_EN;                        /**< Interrupt Signal Enable, offset: 0x50 */
  volatile unsigned char RESERVED_5[12];
  volatile unsigned int INT_STATUS;                        /**< Intterrupt Status, offset: 0x60 */
  volatile unsigned char RESERVED_6[12];
  volatile unsigned int DEBUG_MODE;                        /**< , offset: 0x70 */
  volatile unsigned char RESERVED_7[12];
  volatile unsigned int DEBUG_MODE2;                       /**< , offset: 0x80 */
};

#endif  /* __IMX6ULL_H */


