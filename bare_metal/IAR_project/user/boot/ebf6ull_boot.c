/*
 * The Clear BSD License
 * Copyright 2017 NXP
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted (subject to the limitations in the disclaimer below) provided
 * that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of the copyright holder nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * NO EXPRESS OR IMPLIED LICENSES TO ANY PARTY'S PATENT RIGHTS ARE GRANTED BY THIS LICENSE.
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "ebf6ull_boot.h"

#if defined(__CC_ARM) || defined(__GNUC__)
    __attribute__((section(".boot_hdr.ivt")))
#elif defined(__ICCARM__)
#pragma location=".boot_hdr.ivt"
#endif
/************************************* 
 *  IVT Data 
 *************************************/
const ivt image_vector_table = {
  IVT_HEADER,                         /* IVT 头部 */
  IMAGE_ENTRY_ADDRESS,                /* 固件入口地址 */
  IVT_RSVD,                           /* 保留 */
  (uint32_t)DCD_ADDRESS,              /* DCD数据存储的地址 */
  (uint32_t)BOOT_DATA_ADDRESS,        /* 启动数据结构存储的地址 */
  (uint32_t)&image_vector_table,      /* IVT自身指针的存储地址（绝对地址） */
  (uint32_t)CSF_ADDRESS,              /* 命令序列文件存储的地址，用于加密启动 */
  IVT_RSVD                            /* 保留 */
};

#if defined(__CC_ARM) || defined(__GNUC__)
    __attribute__((section(".boot_hdr.boot_data")))
#elif defined(__ICCARM__)
#pragma location=".boot_hdr.boot_data"
#endif
/************************************* 
 *  Boot Data 
 *************************************/
const BOOT_DATA_T boot_data = {
  FLASH_BASE,                 /* 固件的启动地址，即flash的首地址 */
  FLASH_SIZE,                 /* flash大小 */
  PLUGIN_FLAG,                /* 插件函数标志，用于加密启动*/
  0xFFFFFFFF                  /* 空，额外数据字 */
};



