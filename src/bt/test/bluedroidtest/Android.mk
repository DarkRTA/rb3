#
#  Copyright (C) 2009-2012 Broadcom Corporation
#
#  Licensed under the Apache License, Version 2.0 (the "License");
#  you may not use this file except in compliance with the License.
#  You may obtain a copy of the License at:
#
#  http://www.apache.org/licenses/LICENSE-2.0
#
#  Unless required by applicable law or agreed to in writing, software
#  distributed under the License is distributed on an "AS IS" BASIS,
#  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#  See the License for the specific language governing permissions and
#  limitations under the License.
#

LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_SRC_FILES:=     \
    bluedroidtest.c

LOCAL_C_INCLUDES :=

LOCAL_MODULE_TAGS := eng

LOCAL_MODULE:= bdt

LOCAL_LDLIBS += -lpthread -ldl -llog -lreadline
LIBS_c += -lreadline

LOCAL_SHARED_LIBRARIES += libcutils   \
                          libutils    \
                          libhardware \
                          libhardware_legacy

include $(BUILD_EXECUTABLE)

