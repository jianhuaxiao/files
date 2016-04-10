#define LOG_TAG "LedStub"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <hardware/hardware.h>
#include <fcntl.h>
#include <errno.h>
#include <cutils/log.h>
#include <cutils/atomic.h>
#include <sys/ioctl.h>
#include "../include/led.h"
#define LED_ON _IO('k', 0)
#define LED_OFF _IO('k', 1)
int fd;
static int led_device_close(struct hw_device_t* device)
{
	struct led_control_context_t* ctx = (struct led_control_context_t*)device;
	if (ctx) {
		free(ctx);
	}
	close(fd);
	return 0; }

static int led_getcount(struct led_control_device_t *dev)
{
	ALOGD("%s", __func__);
	return 4;
}


static int led_set_on(struct led_control_device_t *dev, int arg)
{    
	//FIXME: do system call to control gpio led
	ALOGD("%s", __func__);
	ioctl(fd,LED_ON,arg);  //GPF0 0
	return 0;
} 

static int led_set_off(struct led_control_device_t *dev, int arg)
{
	//FIXME: do system call to control gpio led
	ALOGD("%s", __func__);
	ioctl(fd,LED_OFF,arg); //GPF0 1
	return 0;
}

static int led_device_open(const struct hw_module_t* module, const char* name,
	struct hw_device_t** device)
{
	struct led_control_context_t *context;
	ALOGD("%s E", __func__);
	context = (struct led_control_context_t *)malloc(sizeof(*context));
	memset(context, 0, sizeof(*context)); 

	//HAL must init property
	context->device.common.tag= HARDWARE_DEVICE_TAG;
	context->device.common.version = 0;
	context->device.common.module= module;
	context->device.common.close = led_device_close; 

	// 初始化控制 API 
	context->device.set_on= led_set_on;
	context->device.set_off= led_set_off;
	context->device.getcount_led = led_getcount;
	*device= (struct hw_device_t *)&(context->device);

	if((fd=open("/dev/led", O_RDWR))==-1)
	{
		ALOGD("open error: %s",strerror(errno));
		exit(1);
	}else{
		ALOGD("open ok\n");
	}
	
	ioctl(fd,LED_ON);  //GPF0 0
	ALOGD("%s X", __func__);

	return 0;
}


static struct hw_module_methods_t led_module_methods = {
open: led_device_open  
};

struct hw_module_t HAL_MODULE_INFO_SYM = {
	.tag = HARDWARE_MODULE_TAG,
	.version_major = 1,
	.version_minor = 0,
	.id = LED_HARDWARE_MODULE_ID,
	.name = "led HAL module",
	.author = "farsight",
	.methods = &led_module_methods
};

