#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>

#include "hi_mapi_sns_ctrl.h"

#ifdef HI_GPIO_I2C
#include "gpioi2c_ex.h"
#else
#include "hi_i2c.h"
#endif

const unsigned int sensor_i2c_addr	=	0x6c;		/* I2C Address of OV9732 */
const unsigned int sensor_addr_byte	=	2;
const unsigned int sensor_data_byte	=	1;
static int g_fd = -1;
static int flag_init = 0;

extern HI_MPP_WDR_MODE_E genSensorMode;
extern HI_U8 gu8SensorImageMode;
extern HI_BOOL bSensorInit;

int ov9732_i2c_init(void)
{
    if(g_fd >= 0)
    {
        return 0;
    }    
#ifdef HI_GPIO_I2C
    int ret;

    g_fd = open("/dev/gpioi2c_ex", 0);
    if(g_fd < 0)
    {
        printf("Open gpioi2c_ex error!\n");
        return -1;
    }
#else
    int ret;

    g_fd = open("/dev/i2c-0", O_RDWR);
    if(g_fd < 0)
    {
        printf("Open /dev/i2c-0 error!\n");
        return -1;
    }

    ret = ioctl(g_fd, I2C_SLAVE_FORCE, sensor_i2c_addr);
    if (ret < 0)
    {
        printf("CMD_SET_DEV error!\n");
        return ret;
    }
#endif

    return 0;
}

int ov9732_i2c_exit(void)
{
    if (g_fd >= 0)
    {
        close(g_fd);
        g_fd = -1;
        return 0;
    }
    return -1;
}

void ov9732_standby(ISP_ID IspId)
{
    // TODO:
    return;
}

void ov9732_restart(ISP_ID IspId)
{
    // TODO:
    return;
}

int ov9732_read_register(ISP_ID IspId, int addr)
{
	// TODO: 
	
	return 0;
}

int ov9732_write_register(ISP_ID IspId, int addr, int data)
{
#ifdef HI_GPIO_I2C
    i2c_data.dev_addr = sensor_i2c_addr;
    i2c_data.reg_addr = addr;
    i2c_data.addr_byte_num = sensor_addr_byte;
    i2c_data.data = data;
    i2c_data.data_byte_num = sensor_data_byte;

    ret = ioctl(g_fd, GPIO_I2C_WRITE, &i2c_data);

    if (ret)
    {
        printf("GPIO-I2C write faild!\n");
        return ret;
    }
#else
    if(flag_init == 0)
    {
		ov9732_i2c_init();
		flag_init = 1;
    }

    int idx = 0;
    int ret;
    char buf[8];
    buf[idx++] = addr & 0xFF;
    if (sensor_addr_byte == 2)
    {
    	ret = ioctl(g_fd, I2C_16BIT_REG, 1);
        buf[idx++] = addr >> 8;
    }
    else
    {
    	ret = ioctl(g_fd, I2C_16BIT_REG, 0);
    }
	
    if (ret < 0)
    {
        printf("CMD_SET_REG_WIDTH error!\n");
        return -1;
    }

    buf[idx++] = data;
    if (sensor_data_byte == 2)
    {
    	ret = ioctl(g_fd, I2C_16BIT_DATA, 1);
        buf[idx++] = data >> 8;
    }
    else
    {
    	ret = ioctl(g_fd, I2C_16BIT_DATA, 0);
    }

    if (ret)
    {
        printf("hi_i2c write faild!\n");
        return -1;
    }
	
    ret = write(g_fd, buf, idx);
    if(ret < 0)
    {
    	printf("I2C_WRITE error! \n");
    	return -1;
    }
	
#endif

	return 0;
}

void sensor_linear_720p30_init();

void ov9732_init(ISP_ID IspId)
{
	ov9732_i2c_init();

    sensor_linear_720p30_init();
    return ;
}

void ov9732_exit(ISP_ID IspId)
{
    ov9732_i2c_exit();
	flag_init = 0;
    return;
}


/* 720P30*/
void sensor_linear_720p30_init()
{
	ov9732_write_register(0, 0x0103, 0x01); 
	ov9732_write_register(0, 0x0100, 0x00); 
	ov9732_write_register(0, 0x0100, 0x00); 	
	ov9732_write_register(0, 0x3007, 0x1f); 
	ov9732_write_register(0, 0x3008, 0xff); 
	ov9732_write_register(0, 0x3014, 0x22); 
	ov9732_write_register(0, 0x3081, 0x3c); // 30 fps
	ov9732_write_register(0, 0x3084, 0x00); 
	ov9732_write_register(0, 0x3600, 0xf6); 
	ov9732_write_register(0, 0x3601, 0x72); 
	ov9732_write_register(0, 0x3610, 0x0c); 
	ov9732_write_register(0, 0x3611, 0xf0); 
	ov9732_write_register(0, 0x3612, 0x35); 
	ov9732_write_register(0, 0x3658, 0x22); 
	ov9732_write_register(0, 0x3659, 0x22); 
	ov9732_write_register(0, 0x365a, 0x02); 
	ov9732_write_register(0, 0x3700, 0x1f); 
	ov9732_write_register(0, 0x3701, 0x10); 
	ov9732_write_register(0, 0x3702, 0x0c); 
	ov9732_write_register(0, 0x3703, 0x07); 
	ov9732_write_register(0, 0x3704, 0x3c); 
	ov9732_write_register(0, 0x3705, 0x81); 
	ov9732_write_register(0, 0x3710, 0x0c); 
	ov9732_write_register(0, 0x3782, 0x58); 
	ov9732_write_register(0, 0x380f, 0x2b); 
	ov9732_write_register(0, 0x3501, 0x31); 
	ov9732_write_register(0, 0x350a, 0x0); 
	ov9732_write_register(0, 0x350b, 0x10); 
	ov9732_write_register(0, 0x3d82, 0x38); 
	ov9732_write_register(0, 0x3d83, 0xa4); 
	ov9732_write_register(0, 0x3d86, 0x1f);			   
	ov9732_write_register(0, 0x3d87, 0x03);			   
	ov9732_write_register(0, 0x4001, 0xe0);			   
	ov9732_write_register(0, 0x4006, 0x01);			   
	ov9732_write_register(0, 0x4007, 0x40);			   
	ov9732_write_register(0, 0x4821, 0x50);			   
	ov9732_write_register(0, 0x4823, 0x50);			   
	ov9732_write_register(0, 0x4837, 0x37);			   
	ov9732_write_register(0, 0x5000, 0x0f); 
	ov9732_write_register(0, 0x5708, 0x06); 
	ov9732_write_register(0, 0x5781, 0x00); 
	ov9732_write_register(0, 0x5783, 0x0f); 
	ov9732_write_register(0, 0x0100, 0x01);
	ov9732_write_register(0, 0x3703, 0x0b); 
	ov9732_write_register(0, 0x3705, 0x51); 

    bSensorInit = HI_TRUE;
	printf("=========================================================\n");
	printf("===ominivision ov9732 sensor 720P30fps(Parallel port) init =====\n");
	printf("=========================================================\n");


    return;
}

