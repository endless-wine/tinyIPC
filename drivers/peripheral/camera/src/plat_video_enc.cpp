
#include <string.h>
#include <stdlib.h>

#include "plat_video_enc.h"
#include "sample_venc.h"

typedef struct  {
    dspVideoEncoder *encoder;
    dspVideoEncConfig *Info;
    dspVideoEncPacketCallback cb;
    void *cbUser;
    uint32_t refCount;
}dsp_VideoEncObj;

static dsp_VideoEncObj s_dspVideoEncObj[CHANNLE_MAX][CHANNLE_STREAM_TYPE_MAX];
static int32_t s_init = 0;

static int32_t palEncAddRef(struct dspVideoEncoder *owner)
{
    dsp_VideoEncObj *PObj = (dsp_VideoEncObj *)owner->impl;
    PObj->refCount++;
    return 0;
}

static int32_t palEncRelease(struct dspVideoEncoder *owner)
{
    dsp_VideoEncObj *PObj = (dsp_VideoEncObj *)owner->impl;
    if (PObj->refCount > 1) {
        PObj->refCount--;
        return 0;
    }

    free(PObj->encoder);
    free(PObj->Info);
    memset(PObj, 0, sizeof(dsp_VideoEncObj));
    return 0;
}

static int32_t dsp_encAttach(struct dspVideoEncoder *owner, dspVideoEncPacketCallback cb, void *cbUser)
{
    dsp_VideoEncObj *PObj = (dsp_VideoEncObj *)owner->impl;
    PObj->cb = cb;
    PObj->cbUser = cbUser;
}

static int32_t dsp_encStart(struct dspVideoEncoder *owner)
{
    dsp_VideoEncObj *PObj = (dsp_VideoEncObj *)owner->impl;
    dsp_hi_attach(PObj->cb);

    /// 待实现
    dsp_hi_start();
}

static int32_t dsp_encStop(struct dspVideoEncoder *owner) {}

static int32_t dsp_encForceIFrame(struct dspVideoEncoder *owner) {}

int32_t palCreateVideoEncoder(dspVideoEncConfig *info, dspVideoEncoder **handle)
{
    if (s_init == 0) {
        memset(&s_dspVideoEncObj[0][0], 0, sizeof(s_dspVideoEncObj));
        s_init = 1;
    }

    dsp_VideoEncObj *pObj = &s_dspVideoEncObj[info->channel][info->stream];
    if (pObj->encoder != NULL) {
        printf("already exist \n");
        *handle = pObj->encoder;
        return 0;
    }

    dspVideoEncoder *pEncoder = (dspVideoEncoder *)malloc(sizeof(dspVideoEncoder));
    dspVideoEncConfig *pInfo = (dspVideoEncConfig *)malloc(sizeof(dspVideoEncConfig));
    pObj->encoder = pEncoder;
    pObj->Info = pInfo;
    pObj->refCount = 1;

    pEncoder->impl = pObj;
    pEncoder->addRef = palEncAddRef;
    pEncoder->release = palEncRelease;
    pEncoder->attach = dsp_encAttach;
    pEncoder->start = dsp_encStart;
    pEncoder->stop = dsp_encStop;
    pEncoder->forceIFrame = dsp_encForceIFrame;

    *handle = pEncoder;
    return 0;
}