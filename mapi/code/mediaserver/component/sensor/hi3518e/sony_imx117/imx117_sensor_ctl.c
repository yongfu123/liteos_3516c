/******************************************************************************

  Copyright (C), 2001-2013, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : imx117_sensor_ctl.c
  Version       : Initial Draft
  Author        : Hisilicon BVT ISP group
  Created       : 
  Description   : Sony IMX117 sensor driver
  History       :
  1.Date        : 
  Author        : 
  Modification  : Created file

******************************************************************************/

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include "hi_mapi_isp_define.h"
#include "hi_mapi_sns_ctrl_define.h"
#include "hi_mapi_spi_define.h"
#include "imx117_slave_priv.h"

extern const IMX117_VIDEO_MODE_TBL_S g_astImx117ModeTbl[];
extern HI_MPP_ISP_SLAVE_SNS_SYNC_S gstImx117Sync[];

static int g_fd[ISP_MAX_DEV_NUM] = {-1,-1};
extern ISP_SNS_STATE_S             g_astImx117[ISP_MAX_DEV_NUM];
extern HI_MPP_ISP_SNS_COMMBUS_U     g_aunImx117BusInfo[];

static const HI_U16 gs_au16SensorCfgSeq[][IMX117_MODE_BUTT+1] = {
//    M_0    M_0A   M_1   M_1D    M_2  M_4A    M_11A    ADDR            
    { 0x11,  0x11,  NA,   0x00,   NA,  0x11,   0x11,    0x0003 },           
    { 0x80,  0x00,  NA,   0xb8,   NA,  0x48,   0x40,    0x0004 }, 
    { 0x07,  0x47,  NA,   0x81,   NA,  0x21,   0x15,    0x0005 }, 
    { 0x00,  0x00,  NA,   0x00,   NA,  0x00,   0x00,    0x0006 }, 
    { 0x00,  0x00,  NA,   0x00,   NA,  0x00,   0x00,    0x0007 }, 
    { 0x00,  0x00,  NA,   0x00,   NA,  0x00,   0x00,    0x0008 }, 
    { 0x00,  0x00,  NA,   0x00,   NA,  0x00,   0x00,    0x0009 }, 
    { 0x01,  0x01,  NA,   0x01,   NA,  0x06,   0x01,    0x000A }, 
    { 0x0a,  0x0a,  NA,   0x0a,   NA,  0x0a,   0x0a,    0x000b }, 
    { 0x00,  0x00,  NA,   0x00,   NA,  0x00,   0x00,    0x000C }, 
    { 0x00,  0x00,  NA,   0x00,   NA,  0x00,   0x00,    0x000d }, 
    { 0x00,  0x00,  NA,   0x00,   NA,  0x00,   0x00,    0x000E }, 
    { 0x00,  0x00,  NA,   0x00,   NA,  0x00,   0x00,    0x000f }, 
    { 0x00,  0x00,  NA,   0x00,   NA,  0x00,   0x00,    0x0010 }, 
    { 0x02,  0x02,  NA,   0x02,   NA,  0x03,   0x02,    0x0011 }, 
    { 0x00,  0x00,  NA,   0x00,   NA,  0x00,   0x00,    0x001a }, 
    { 0x74,  0x74,  NA,   0x74,   NA,  0x74,   NA  ,    0x0026 }, 
    { 0x74,  0x74,  NA,   0x74,   NA,  0x74,   NA  ,    0x0027 }, 
    { 0x74,  0x74,  NA,   0x74,   NA,  0x74,   NA  ,    0x0028 }, 
    { 0x32,  0x32,  NA,   0x32,   NA,  0x32,   0x32,    0x0045 }, 
    { 0x20,  0x20,  NA,   0x41,   NA,  0x00,   0x7F,    0x007e }, 
    { 0x01,  0x05,  NA,   0x00,   NA,  0x00,   0x11,    0x007F }, 
    { 0x00,  0x00,  NA,   0x0e,   NA,  0x00,   0x12,    0x0080 }, 
    { 0x00,  0x00,  NA,   0x00,   NA,  0x00,   0x00,    0x0081 }, 
    { 0x00,  0x00,  NA,   0x12,   NA,  0x00,   0x0C,    0x0082 }, 
    { 0x00,  0x00,  NA,   0x00,   NA,  0x00,   0x00,    0x0083 }, 
    { 0x00,  0x00,  NA,   0xca,   NA,  0x00,   0x1A,    0x0084 }, 
    { 0x00,  0x00,  NA,   0x09,   NA,  0x00,   0x04,    0x0085 }, 
    { 0x00,  0x00,  NA,   0xde,   NA,  0x00,   0x4C,    0x0086 }, 
    { 0x00,  0x00,  NA,   0x02,   NA,  0x00,   0x04,    0x0087 }, 
    { NA  ,  NA,    NA,   NA  ,   NA,  NA  ,   0x01,    0x0088 }, 
    { NA  ,  NA,    NA,   NA  ,   NA,  NA  ,   0x07,    0x0089 }, 
    { NA  ,  NA,    NA,   NA  ,   NA,  NA  ,   0x00,    0x008A }, 
    { NA  ,  NA,    NA,   NA  ,   NA,  NA  ,   0x00,    0x008B }, 
    { NA  ,  NA,    NA,   NA  ,   NA,  NA  ,   0x00,    0x008C }, 
    { NA  ,  NA,    NA,   NA  ,   NA,  NA  ,   0x00,    0x008D }, 
    { NA  ,  NA,    NA,   NA  ,   NA,  NA  ,   0x01,    0x008E }, 
    { NA  ,  NA,    NA,   NA  ,   NA,  NA  ,   0x07,    0x008F }, 
    { NA  ,  NA,    NA,   NA  ,   NA,  NA  ,   0x00,    0x0090 }, 
    { NA  ,  NA,    NA,   NA  ,   NA,  NA  ,   0x00,    0x0091 }, 
    { NA  ,  NA,    NA,   NA  ,   NA,  NA  ,   0x00,    0x0092 }, 
    { NA  ,  NA,    NA,   NA  ,   NA,  NA  ,   0x00,    0x0093 }, 
    { NA  ,  NA,    NA,   NA  ,   NA,  NA  ,   0x11,    0x0094 }, 
    { 0x00,  0x00,  NA,   0x10,   NA,  0x00,   0x14,    0x0095 },                          
    { 0x00,  0x00,  NA,   0x00,   NA,  0x00,   0x00,    0x0096 }, 
    { 0x00,  0x00,  NA,   0x12,   NA,  0x00,   0x0C,    0x0097 }, 
    { 0x00,  0x00,  NA,   0x00,   NA,  0x00,   0x00,    0x0098 }, 
    { 0x00,  0x00,  NA,   0xcc,   NA,  0x00,   0x1C,    0x0099 }, 
    { 0x00,  0x00,  NA,   0x09,   NA,  0x00,   0x04,    0x009a }, 
    { 0x00,  0x00,  NA,   0xde,   NA,  0x00,   0x4C,    0x009b }, 
    { 0x00,  0x00,  NA,   0x02,   NA,  0x00,   0x04,    0x009c }, 
    { NA  ,  NA  ,  NA,   NA  ,   NA,  NA  ,   0x01,    0x009D }, 
    { NA  ,  NA  ,  NA,   NA  ,   NA,  NA  ,   0x07,    0x009E }, 
    { NA  ,  NA  ,  NA,   NA  ,   NA,  NA  ,   0x00,    0x009F }, 
    { NA  ,  NA  ,  NA,   NA  ,   NA,  NA  ,   0x00,    0x00A0 }, 
    { NA  ,  NA  ,  NA,   NA  ,   NA,  NA  ,   0x00,    0x00A1 }, 
    { NA  ,  NA  ,  NA,   NA  ,   NA,  NA  ,   0x00,    0x00A2 }, 
    { NA  ,  NA  ,  NA,   NA  ,   NA,  NA  ,   0x01,    0x00A3 }, 
    { NA  ,  NA  ,  NA,   NA  ,   NA,  NA  ,   0x07,    0x00A4 }, 
    { NA  ,  NA  ,  NA,   NA  ,   NA,  NA  ,   0x00,    0x00A5 }, 
    { NA  ,  NA  ,  NA,   NA  ,   NA,  NA  ,   0x00,    0x00A6 }, 
    { NA  ,  NA  ,  NA,   NA  ,   NA,  NA  ,   0x00,    0x00A7 }, 
    { NA  ,  NA  ,  NA,   NA  ,   NA,  NA  ,   0x00,    0x00A8 }, 
    { NA  ,  NA  ,  NA,   NA  ,   NA,  NA  ,   0x11,    0x00A9 }, 
    { NA  ,  NA  ,  NA,   NA  ,   NA,  NA  ,   0x04,    0x00AA }, 
    { NA  ,  NA  ,  NA,   NA  ,   NA,  NA  ,   0x04,    0x00AB }, 
    { NA  ,  NA  ,  NA,   NA  ,   NA,  NA  ,   0x04,    0x00AC }, 
    { NA  ,  NA  ,  NA,   NA  ,   NA,  NA  ,   0x05,    0x00AD }, 
    { NA  ,  NA  ,  NA,   NA  ,   NA,  NA  ,   0x04,    0x00AE }, 
    { NA  ,  NA  ,  NA,   NA  ,   NA,  NA  ,   0x04,    0x00AF }, 
    { NA  ,  NA  ,  NA,   NA  ,   NA,  NA  ,   0x04,    0x00b0 }, 
    { NA  ,  NA  ,  NA,   NA  ,   NA,  NA  ,   0x08,    0x00b1 }, 
    { NA  ,  NA  ,  NA,   NA  ,   NA,  NA  ,   0x08,    0x00b2 }, 
    { NA  ,  NA  ,  NA,   NA  ,   NA,  NA  ,   0x05,    0x00b3 }, 
    { NA  ,  NA  ,  NA,   NA  ,   NA,  NA  ,   0x08,    0x00b4 }, 
    { NA  ,  NA  ,  NA,   NA  ,   NA,  NA  ,   0x08,    0x00b5 }, 
    { 0x47,  0x47,  NA,   0x00,   NA,  0x00,   0x04,    0x00b6 },                          
    { 0x00,  0x00,  NA,   0x00,   NA,  0x00,   0x0A,    0x00b7 }, 
    { 0x00,  0x00,  NA,   0x00,   NA,  0x00,   0x14,    0x00b8 }, 
    { 0x00,  0x00,  NA,   0x00,   NA,  0x00,   0x04,    0x00b9 }, 
    { 0x00,  0x00,  NA,   0x00,   NA,  0x00,   0x0A,    0x00ba }, 
    { 0x00,  0x00,  NA,   0x00,   NA,  0x00,   0x14,    0x00bb }, 
    { 0x00,  0x00,  NA,   0x00,   NA,  0x00,   0x00,    0x00bc }, 
    { 0x00,  0x00,  NA,   0x00,   NA,  0x00,   0x00,    0x00bd }, 
    { 0x00,  0x00,  NA,   0x07,   NA,  0x00,   0x09,    0x00be }, 
    { 0x00,  0x00,  NA,   0x00,   NA,  0x00,   0x00,    0x00bf }, 
    { 0x00,  0x00,  NA,   0x3a,   NA,  0x00,   0x48,    0x00c0 }, 
    { 0x00,  0x00,  NA,   0x00,   NA,  0x00,   0x00,    0x00c1 }, 
    { 0x00,  0x00,  NA,   0xf0,   NA,  0x00,   0xE9,    0x00c2 }, 
    { 0x00,  0x00,  NA,   0x00,   NA,  0x00,   0x01,    0x00c3 }, 
    { 0x00,  0x00,  NA,   0xea,   NA,  0x00,   0x50,    0x00c4 }, 
    { 0x00,  0x00,  NA,   0x07,   NA,  0x00,   0x15,    0x00c5 }, 
    { 0x00,  0x00,  NA,   0xf0,   NA,  0x00,   0xCB,    0x00c6 }, 
    { 0x00,  0x00,  NA,   0x00,   NA,  0x00,   0x01,    0x00c7 }, 
    { 0x00,  0x00,  NA,   0x8e,   NA,  0x00,   0x00,    0x00c8 }, 
    { 0x00,  0x00,  NA,   0x0f,   NA,  0x00,   0x00,    0x00c9 }, 
    { 0x00,  0x00,  NA,   0xf0,   NA,  0x00,   0x00,    0x00ca }, 
    { 0x00,  0x00,  NA,   0x00,   NA,  0x00,   0x00,    0x00cb }, 
    { 0x00,  0x00,  NA,   0x02,   NA,  0x00,   0x02,    0x00cc }, 
    { 0x0e,  0x0e,  NA,   0x0c,   NA,  0x00,   0x10,    0x00ce }, 
    { NA  ,  NA  ,  NA,   NA  ,   NA,  NA  ,   0x02,    0x00D3 }, 
    { 0x31,  0x31,  NA,   0x31,   NA,  0x31,   0x31,    0x0222 }, 
    { 0x01,  0x01,  NA,   0x01,   NA,  0x01,   0x01,    0x0223 }, 
    { 0x3d,  0x3d,  NA,   0x1F,   NA,  0x28,   0x28,    0x0352 }, 
    { 0x00,  0x00,  NA,   0x00,   NA,  0x00,   0x00,    0x0353 }, 
    { 0x3c,  0x3c,  NA,   0x1e,   NA,  0x27,   0x27,    0x0356 }, 
    { 0x00,  0x00,  NA,   0x00,   NA,  0x00,   0x00,    0x0357 }, 
    { 0x01,  0x01,  NA,   0x01,   NA,  0x01,   0x01,    0x0358 }, 
    { 0x0e,  0x0e,  NA,   0x0e,   NA,  0x0e,   0x0e,    0x0528 }, 
    { 0x0e,  0x0e,  NA,   0x0e,   NA,  0x0e,   0x0e,    0x0529 }, 
    { 0x0e,  0x0e,  NA,   0x0e,   NA,  0x0e,   0x0e,    0x052a }, 
    { 0x0e,  0x0e,  NA,   0x0e,   NA,  0x0e,   0x0e,    0x052b }, 
    { 0x10,  0x10,  NA,   0x10,   NA,  0x10,   0x10,    0x0534 }, 
    { 0x00,  0x00,  NA,   0x00,   NA,  0x00,   0x00,    0x057e }, 
    { 0x10,  0x10,  NA,   0x10,   NA,  0x10,   0x10,    0x057f }, 
    { 0x0d,  0x0d,  NA,   0x0d,   NA,  0x0d,   0x0d,    0x0580 }, 
    { 0x0d,  0x0d,  NA,   0x0d,   NA,  0x0d,   0x0d,    0x0581 }, 
    { 0x00,  0x00,  NA,   0x00,   NA,  0x00,   0x00,    0x0585 }, 
    { 0x07,  0x07,  NA,   0x07,   NA,  0x07,   0x07,    0x0586 }, 
    { 0x10,  0x10,  NA,   0x10,   NA,  0x10,   0x10,    0x0617 }, 
    { 0x05,  0x05,  NA,   0x05,   NA,  0x05,   0x05,    0x065c }, 
    { 0x19,  0x19,  NA,   0x19,   NA,  0x19,   0x19,    0x0700 }, 
    { 0x19,  0x19,  NA,   0x19,   NA,  0x19,   0x19,    0x0701 }, 
    { 0x00,  0x98,  NA,   NA  ,   NA,  NA  ,   NA  ,    0x00d0 }, 
    { 0x00,  0x10,  NA,   NA  ,   NA,  NA  ,   NA  ,    0x00d1 }, 
};                                                             
                                                            
                                                       
int imx117_spi_init(ISP_ID IspId)
{
    char acDevFile[16];
    HI_U8 u8DevNum, u8Cs;
    
    if(g_fd[IspId] >= 0)
    {
        return 0;
    }    
    unsigned int value;
    int ret = 0;

	u8DevNum = g_aunImx117BusInfo[IspId].s8SspDev.bit4SspDev;
    u8Cs = g_aunImx117BusInfo[IspId].s8SspDev.bit4SspCs;
    snprintf(acDevFile, sizeof(acDevFile), "/dev/spidev%d.%d", u8DevNum, u8Cs);


    g_fd[IspId] = open(acDevFile, 0);
    if (g_fd[IspId] < 0)
    {
        printf("Open %s error!\n",acDevFile);
        return -1;
    }

    value = SPI_MODE_3 | SPI_LSB_FIRST;// | SPI_LOOP;
    ret = ioctl(g_fd[IspId], SPI_IOC_WR_MODE, &value);
    if (ret < 0)
    {
        printf("ioctl SPI_IOC_WR_MODE err, value = %d ret = %d\n", value, ret);
        return ret;
    }

    value = 8;
    ret = ioctl(g_fd[IspId], SPI_IOC_WR_BITS_PER_WORD, &value);
    if (ret < 0)
    {
        printf("ioctl SPI_IOC_WR_BITS_PER_WORD err, value = %d ret = %d\n",value, ret);
        return ret;
    }

    value = 2000000;
    ret = ioctl(g_fd[IspId], SPI_IOC_WR_MAX_SPEED_HZ, &value);
    if (ret < 0)
    {
        printf("ioctl SPI_IOC_WR_MAX_SPEED_HZ err, value = %d ret = %d\n",value, ret);
        return ret;
    }

    return 0;
}

int imx117_spi_exit(ISP_ID IspId)
{
    if (g_fd[IspId] >= 0)
    {
        close(g_fd[IspId]);
        g_fd[IspId] = -1;
        return 0;
    }
    return -1;
}

int imx117_write_register(ISP_ID IspId,unsigned int addr, unsigned char data)
{
    int ret;
    struct spi_ioc_transfer mesg[1];
    unsigned char  tx_buf[8] = {0};
    unsigned char  rx_buf[8] = {0};

    if (0 > g_fd[IspId])
    {
        return 0;
    }
    
    tx_buf[0] = 0x81;
    tx_buf[1] = addr >> 8;
    tx_buf[2] = addr & 0xff;
    tx_buf[3] = data;

    memset(mesg, 0, sizeof(mesg));  
    mesg[0].tx_buf = (__u32)tx_buf;  
    mesg[0].len    = 4;  
    mesg[0].rx_buf = (__u32)rx_buf; 
    mesg[0].cs_change = 1;

    ret = ioctl(g_fd[IspId], SPI_IOC_MESSAGE(1), mesg);
    if (ret < 0) {  
        printf("SPI_IOC_MESSAGE error \n");  
        return -1;  
    }

    return 0;
}

int imx117_read_register(ISP_ID IspId,unsigned int addr)
{
    int ret = 0;
    struct spi_ioc_transfer mesg[1];
    unsigned char  tx_buf[8] = {0};
    unsigned char  rx_buf[8] = {0};
    

    tx_buf[0] = 0x80;
    tx_buf[1] = addr >> 8;
    tx_buf[2] = addr & 0xff;
    tx_buf[3] = 0;

    memset(mesg, 0, sizeof(mesg));
    mesg[0].tx_buf = (__u32)tx_buf;
    mesg[0].len    = 4;
    mesg[0].rx_buf = (__u32)rx_buf;
    mesg[0].cs_change = 1;

    ret = ioctl(g_fd[IspId], SPI_IOC_MESSAGE(1), mesg);
    if (ret  < 0) {  
        printf("SPI_IOC_MESSAGE error \n");  
        return -1;  
    }
    
    return rx_buf[3];
}

static void delay_ms(int ms) { 
    usleep(ms*1000);
}

void imx117_standby(ISP_ID IspId)
{
    // TODO:
    return;
}

void imx117_restart(ISP_ID IspId)
{
    // TODO:
    return;
}



void imx117_init(ISP_ID IspId)
{
    HI_U8            u8ImgMode;

    u8ImgMode   = g_astImx117[IspId].u8ImgMode;

    HI_U8 u16RegData;
    HI_U16 u16RegAddr;
    HI_U32 i;
    HI_U32 u32SeqEntries;
   
    /* hold sync signal as fixed */
    CHECK_RET(HI_MAPI_ISP_GetHvSync(IspId, &gstImx117Sync[IspId]));
    gstImx117Sync[IspId].unCfg.stBits.bitHEnable = 0;
    gstImx117Sync[IspId].unCfg.stBits.bitVEnable = 0;
    CHECK_RET(HI_MAPI_ISP_SetHvSync(IspId, &gstImx117Sync[IspId]));
      
    /* 2. sensor spi init */
    imx117_spi_init(IspId);

    /* When sensor first init, config all registers */
    u32SeqEntries = sizeof(gs_au16SensorCfgSeq) / sizeof(gs_au16SensorCfgSeq[0]);

    imx117_write_register (IspId,0x0000, 0x02); //standy=0[bit(0)],STBLogic=1[bit(1)]
    delay_ms(1); 
    imx117_write_register (IspId,0x0000, 0x00); //standy=0[bit(0)],STBLogic=0[bit(1)]
    delay_ms(16);
    imx117_write_register (IspId,0x0001, 0x11); //DCKRST=1[bit(0)],CLPSQRST=1[bit(4)]

    for ( i = 0 ; i < u32SeqEntries; i++ )
    {
        u16RegAddr = gs_au16SensorCfgSeq[i][IMX117_MODE_BUTT];
        u16RegData = gs_au16SensorCfgSeq[i][u8ImgMode];
        if ( NA == u16RegData )
        {
            continue;
        }
        imx117_write_register(IspId,u16RegAddr, u16RegData);
    }

    imx117_write_register (IspId,0x0000, 0x06);
    delay_ms(2);   
    imx117_write_register (IspId,0x0000, 0x04);
    delay_ms(200); 
    
    // release hv sync
    gstImx117Sync[IspId].u32HsTime = g_astImx117ModeTbl[u8ImgMode].u32InckPerHs;
    gstImx117Sync[IspId].u32VsTime = g_astImx117ModeTbl[u8ImgMode].u32InckPerVs;
    gstImx117Sync[IspId].unCfg.u32Bytes = 0xc0030000; 
    gstImx117Sync[IspId].u32HsCyc = 0x3;
    gstImx117Sync[IspId].u32VsCyc = 0x3;
    CHECK_RET(HI_MAPI_ISP_SetHvSync(IspId, &gstImx117Sync[IspId]));

    printf("IMX117 %s init succuss!\n", g_astImx117ModeTbl[u8ImgMode].pszModeName);
    
    g_astImx117[IspId].bInit = HI_TRUE;
   
    return ;
}

void imx117_exit(ISP_ID IspId)
{
    imx117_spi_exit(IspId);

    return;
}


