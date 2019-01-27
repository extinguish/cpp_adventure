/*
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __JNI_LOG_H__
#define __JNI_LOG_H__


#define TAG "LogTag"

#ifdef __cplusplus
extern "C"
{
#endif

#ifdef ANDROID
#include <android/log.h>
#define LOGE(...) if(1) (void)__android_log_print(ANDROID_LOG_ERROR, TAG, __VA_ARGS__)
#else
#include <stdio.h>
#define LOGE(...) if(1) (void)printf(__VA_ARGS__);

#define LOGD(...) if(1) (void)printf(__VA_ARGS__);
#endif

#ifdef __cplusplus
}
#endif


#endif