#ifndef __PAL_VIDEO_ENC_API_H__
#define __PAL_VIDEO_ENC_API_H__

#include "plat_define.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/// 视频编码压缩格式类型
typedef enum {
    videoEncH264,       /// H.264
    videoEncMotionJPEG, /// MJPG
    videoEncH265,       /// H.265
    videoEncNumber,     /// 压缩类型数目
}DspVideoEncType;

/// 帧类型
typedef enum {
    videoEncFrameI = 0, /// I帧
    videoEncFrameP,     /// P帧
    videoEncFrameB,     /// B帧
    videoEncFrameJ,     /// JPEG图像帧
    videoEncFrameNumber /// 帧类型数目
}DspVideoEncFrameType;

/// 视频帧封装格式
typedef enum {
    videoEncPackTypeES = 0, ///< ES流,原始流
    videoEncPackTypePS,     ///< PS流
    videoEncPackTypeCM,     ///< 自定义封装
}DspVideoEncPackType;

/// 视频编码包
typedef struct {
    uint8_t *buf;                 /// 帧数据
    uint32_t len;                 /// 帧数据长度
    uint64_t pts;                 /// 时间戳，毫秒为单位
    uint32_t seq;                 /// 帧序号，用于校验是否丢帧
    DspVideoEncFrameType type;    /// 帧类型
    uint32_t utc;                 /// UTC(1970-1-1 00:00:00)秒数
    uint16_t utcms;               /// UTC时间对应的毫秒数
    uint8_t specLen;              /// SpecInfo数据长度，0则表示无效
    uint8_t *specBuf;             /// SpecInfo信息，如H.264的PPS,SPS
    uint64_t ptsEnter;            /// 编码前的时间戳，毫秒为单位
    uint64_t ptsLeave;            /// 编码后的时间戳，毫秒为单位
    uint16_t width;               /// 该帧编码数据的宽度
    uint16_t height;              /// 该帧编码数据的长度
    DspVideoEncPackType packType; /// 该数据包的封装格式
    DspVideoEncType codecType;    /// 编码类型
}dspVideoEncPacket;

/// 视频帧推流回调函数
///
/// \param [out] cbUser 用户数据
/// \param [out] packet 数据包
/// \retval 0  成功  <0  失败
typedef int32_t (*dspVideoEncPacketCallback)(void *cbUser, dspVideoEncPacket *packet);

/// 视频编码
typedef struct dspVideoEncoder {
    void *impl;

    int32_t (*addRef)(struct dspVideoEncoder *self);

    int32_t (*release)(struct dspVideoEncoder *self);

    /// 码流回调函数
    int32_t (*attach)(struct dspVideoEncoder *self, dspVideoEncPacketCallback cb, void *cbUser);

    /// 开始编码。
    int32_t (*start)(struct dspVideoEncoder *self);

    /// 停止编码，
    int32_t (*stop)(struct dspVideoEncoder *self);

    /// 强制编码器产生I帧。
    int32_t (*forceIFrame)(struct dspVideoEncoder *self);

} dspVideoEncoder;

/// 视频编码接口
typedef struct {
    int32_t stream;  /// 指定编码码流的类型
    int32_t channel; /// 编码通道号
} dspVideoEncConfig;

/// 创建编码设备对象
int32_t palCreateVideoEncoder(dspVideoEncConfig *info, dspVideoEncoder **dspVideoEncoder);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif //__DSP_VIDEO_ENC_API_H__
