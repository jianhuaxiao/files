#define LOG_TAG "LedService"
#include "utils/Log.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>
#include <jni.h>
#include "../../led_hal/include/led.h"
static led_control_device_t *sLedDevice = 0;
static led_module_t* sLedModule=0;
static jint get_count(void)
{
	ALOGD("%s E", __func__);
	if(sLedDevice)
		sLedDevice->getcount_led(sLedDevice);
	else
		ALOGE("sLedDevice is null");
	ALOGD("%s X", __func__);
	return 0;
}

static jint led_setOn(JNIEnv* env, jobject thiz, jint arg) {
	ALOGD("%s E", __func__);
	if (sLedDevice) {
		sLedDevice->set_on(sLedDevice, (int)arg);
	}else{
		ALOGE("sLedDevice is null");
	}
	ALOGD("%s X", __func__);
	return 0;
}

static jint led_setOff(JNIEnv* env, jobject thiz, jint arg) {
	ALOGD("%s E", __func__);
	if (sLedDevice) {
		sLedDevice->set_off(sLedDevice, (int)arg);
	}else{
		ALOGE("sLedDevice is null");
	}
	ALOGD("%s X", __func__);

	return 0;
}

/** helper APIs */
static inline int led_control_open(const struct hw_module_t* module,
	struct led_control_device_t** device) {
	ALOGD("%s", __func__);
	return module->methods->open(module,
		LED_HARDWARE_MODULE_ID, (struct hw_device_t**)device);
}

static jint led_init(JNIEnv *env, jclass clazz)
{
	led_module_t * module;
	ALOGD("%s E", __func__);

	if (hw_get_module(LED_HARDWARE_MODULE_ID, (hw_module_t const**)&module) == 0) {
		ALOGI("get module OK");     
		sLedModule = (led_module_t *) module;
		if (led_control_open(&module->common, &sLedDevice) != 0) {
			ALOGE("led_control_open error");
			return -1;
		}
	}

	ALOGD("%s X", __func__);
	return 0;
}

/*
 *
 ** Array of methods.
 ** Each entry has three fields: the name of the method, the method
 ** signature, and a pointer to the native implementation.
 */ 
static const JNINativeMethod gMethods[] = {
	{"_init",        "()Z", (void*)led_init},
	{ "_set_on",     "(I)I", (void*)led_setOn },
	{ "_set_off",    "(I)I", (void*)led_setOff },
	{ "_get_count",  "()I", (void*)get_count },
};

static int registerMethods(JNIEnv* env) {
	ALOGD("%s E", __func__);
	static const char* const kClassName = "com/farsight/service/LedService";
	jclass clazz; 
	/* look up the class */
	clazz = env->FindClass(kClassName);
	if (clazz == NULL) {
		ALOGE("Can't find class %s\n", kClassName);
		return -1;
	} 

	/* register all the methods */
	if (env->RegisterNatives(clazz, gMethods,
			sizeof(gMethods) / sizeof(gMethods[0])) != JNI_OK)
	{
		ALOGE("Failed registering methods for %s\n", kClassName);
		return -1;
	}
	ALOGD("%s X", __func__);
	/* fill out the rest of the ID cache */
	return 0;
} 

/*
 *
 *   * This is called by the VM when the shared library is first loaded.
 */ 
jint JNI_OnLoad(JavaVM* vm, void* reserved) {
	JNIEnv* env = NULL;
	jint result = -1;
	ALOGI("JNI_OnLoad");

	if (vm->GetEnv((void**) &env, JNI_VERSION_1_4) != JNI_OK) {
		ALOGE("ERROR: GetEnv failed\n");
		goto fail;
	}

	assert(env != NULL);
	if (registerMethods(env) != 0) {
		ALOGE("ERROR: PlatformLibrary native registration failed\n");
		goto fail;
	}
	/* success -- return valid version number */	
	result = JNI_VERSION_1_4;

fail:
	return result;
} 


