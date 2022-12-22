#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>
#include "common/sample_comm.h"
#include "plat_video_enc.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

int32_t dsp_hi_attach(dspVideoEncPacketCallback bc);

int32_t dsp_hi_start();

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif
