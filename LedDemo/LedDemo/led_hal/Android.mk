LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE_PATH := $(TARGET_OUT_SHARED_LIBRARIES)/hw

LOCAL_MODULE := led.polaris

LOCAL_PRELINK_MODULE := false

LOCAL_SHARED_LIBRARIES := liblog

LOCAL_SRC_FILES := ./module/led.c

LOCAL_MODULE_TAGS := eng

include $(BUILD_SHARED_LIBRARY) 
