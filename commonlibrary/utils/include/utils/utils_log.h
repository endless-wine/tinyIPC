#ifndef UTILS_BASE_LOG_H
#define UTILS_BASE_LOG_H

#ifdef CONFIG_HILOG
#include "hilog_base/log_base.h"
constexpr LogType UTILS_LOG_TYPE = LOG_CORE;
constexpr unsigned int UTILS_LOG_DOMAIN = 0xD003D00;
constexpr const char *UTILS_LOG_TAG = "utils_base";
#define UTILS_LOGF(...) (void)HiLogBasePrint(UTILS_LOG_TYPE, LOG_FATAL, UTILS_LOG_DOMAIN, UTILS_LOG_TAG, __VA_ARGS__)
#define UTILS_LOGE(...) (void)HiLogBasePrint(UTILS_LOG_TYPE, LOG_ERROR, UTILS_LOG_DOMAIN, UTILS_LOG_TAG, __VA_ARGS__)
#define UTILS_LOGW(...) (void)HiLogBasePrint(UTILS_LOG_TYPE, LOG_WARN, UTILS_LOG_DOMAIN, UTILS_LOG_TAG, __VA_ARGS__)
#define UTILS_LOGI(...) (void)HiLogBasePrint(UTILS_LOG_TYPE, LOG_INFO, UTILS_LOG_DOMAIN, UTILS_LOG_TAG, __VA_ARGS__)
#ifdef DEBUG_UTILS
#define UTILS_LOGD(...) (void)HiLogBasePrint(UTILS_LOG_TYPE, LOG_DEBUG, UTILS_LOG_DOMAIN, UTILS_LOG_TAG, __VA_ARGS__)
#else
#define UTILS_LOGD(...)
#endif
#else
#define UTILS_LOGF(...)
#define UTILS_LOGE(...)
#define UTILS_LOGW(...)
#define UTILS_LOGI(...)
#define UTILS_LOGD(...)
#endif  // CONFIG_HILOG

#if (defined CONFIG_HILOG) && (defined CONFIG_PARCEL_DEBUG)
constexpr LogType PARCEL_LOG_TYPE = LOG_CORE;
constexpr unsigned int PARCEL_LOG_DOMAIN = 0xD003D01;
constexpr const char *PARCEL_LOG_TAG = "parcel";
#define PARCEL_LOGF(...) \
    (void)HiLogBasePrint(PARCEL_LOG_TYPE, LOG_FATAL, PARCEL_LOG_DOMAIN, PARCEL_LOG_TAG, __VA_ARGS__)
#define PARCEL_LOGE(...) \
    (void)HiLogBasePrint(PARCEL_LOG_TYPE, LOG_ERROR, PARCEL_LOG_DOMAIN, PARCEL_LOG_TAG, __VA_ARGS__)
#define PARCEL_LOGW(...) \
    (void)HiLogBasePrint(PARCEL_LOG_TYPE, LOG_WARN, PARCEL_LOG_DOMAIN, PARCEL_LOG_TAG, __VA_ARGS__)
#define PARCEL_LOGI(...) \
    (void)HiLogBasePrint(PARCEL_LOG_TYPE, LOG_INFO, PARCEL_LOG_DOMAIN, PARCEL_LOG_TAG, __VA_ARGS__)
#define PARCEL_LOGD(...) \
    (void)HiLogBasePrint(PARCEL_LOG_TYPE, LOG_DEBUG, PARCEL_LOG_DOMAIN, PARCEL_LOG_TAG, __VA_ARGS__)
#else
#define PARCEL_LOGF(...)
#define PARCEL_LOGE(...)
#define PARCEL_LOGW(...)
#define PARCEL_LOGI(...)
#define PARCEL_LOGD(...)
#endif  // (defined CONFIG_HILOG) && (defined CONFIG_PARCEL_DEBUG)

#endif  // UTILS_BASE_LOG_H
