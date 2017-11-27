/******************************************************************************
Copyright (c) [2012 - 2017] Texas Instruments Incorporated

All rights reserved not granted herein.

Limited License.

 Texas Instruments Incorporated grants a world-wide, royalty-free, non-exclusive
 license under copyrights and patents it now or hereafter owns or controls to
 make,  have made, use, import, offer to sell and sell ("Utilize") this software
 subject to the terms herein.  With respect to the foregoing patent license,
 such license is granted  solely to the extent that any such patent is necessary
 to Utilize the software alone.  The patent license shall not apply to any
 combinations which include this software, other than combinations with devices
 manufactured by or for TI ("TI Devices").  No hardware patent is licensed
 hereunder.

 Redistributions must preserve existing copyright notices and reproduce this
 license (including the above copyright notice and the disclaimer and
 (if applicable) source code license limitations below) in the documentation
 and/or other materials provided with the distribution

 Redistribution and use in binary form, without modification, are permitted
 provided that the following conditions are met:

 * No reverse engineering, decompilation, or disassembly of this software
   is permitted with respect to any software provided in binary form.

 * Any redistribution and use are licensed by TI for use only with TI Devices.

 * Nothing shall obligate TI to provide you with source code for the software
   licensed and provided to you in object code.

 If software source code is provided to you, modification and redistribution of
 the source code are permitted provided that the following conditions are met:

 * Any redistribution and use of the source code, including any resulting
   derivative works, are licensed by TI for use only with TI Devices.

 * Any redistribution and use of any object code compiled from the source code
   and any resulting derivative works, are licensed by TI for use only with TI
   Devices.

 Neither the name of Texas Instruments Incorporated nor the names of its
 suppliers may be used to endorse or promote products derived from this software
 without specific prior written permission.

 DISCLAIMER.

 THIS SOFTWARE IS PROVIDED BY TI AND TI�S LICENSORS "AS IS" AND ANY EXPRESS OR
 IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 IN NO EVENT SHALL TI AND TI�S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
******************************************************************************/

/**
 *******************************************************************************
 *
 * \ingroup ALGORITHM_LINK_API
 * \defgroup ALGORITHM_LINK_IMPL Algorithm Link Implementation
 *
 * @{
 */

/**
 *******************************************************************************
 *
 * \file stereoAppLink_priv.h Stereo App Algorithm Link
 *       private API/Data structures
 *
 * \brief  This link private header file has defined
 *         - Algorithm link instance/handle object
 *         - All the local data structures
 *         - Algorithm plug in function interfaces
 *
 * \version 0.1 (Oct 2016) : [VT] First version
 *
 *******************************************************************************
 */

#ifndef _STEREOAPP_LINK_PRIV_H_
#define _STEREOAPP_LINK_PRIV_H_

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 *  Include files
 *******************************************************************************
 */
#include <include/link_api/system.h>
#include <include/link_api/algorithmLink.h>
#include <include/alglink_api/algorithmLink_stereoApp.h>
#include <include/link_api/algorithmLink_algPluginSupport.h>
#include <src/rtos/utils_common/include/utils_prf.h>
#include <src/rtos/utils_common/include/utils_que.h>
#include "./include/iStereoAppAlgo.h"
#include <src/rtos/utils_common/include/utils_link_stats_if.h>


/*******************************************************************************
 *  Defines
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 *   \brief Max number of output
 *
 *   This macro defines the number of outputs
 *
 *   SUPPORTED in ALL platforms
 *
 *******************************************************************************
 */
#define STEREOAPP_LINK_MAX_NUM_OUTPUT (4)

#define STEREOAPP_LINK_INPUT_WIDTH (640)

#define STEREOAPP_LINK_INPUT_HEIGHT (360)

#define STEREOAPP_LINK_MAX_NUM_PAIRS (3)


#define DRONE_MV_SIZE (3 * 2 + 4)
#define PCL_HEADER_SIZE    8  // 4 byte start code, 2 byte width, 2 byte height
#define OGMAP_HEADER_SIZE 10 // 4 byte start code, 2 * 3 bytes for OGMap size

#define PLC_START_CODE 0x00000101
#define OGMAP_START_CODE 0x00000102






/*******************************************************************************
 *  Data structures
 *******************************************************************************
 */


/**
 *******************************************************************************
 *
 *   \brief Structure containing feature plane computation algorithm link
 *          parameters
 *
 *          This structure holds any algorithm parameters specific to this link.
 *
 *******************************************************************************
*/
typedef struct
{

    void                      * algHandle;
    /**< Handle of the algorithm */

#if 0
    UInt32                      dataFormat;
    /**< Data format of the video to operate on */
    UInt32                      inPitch[SYSTEM_MAX_PLANES];
    /**< Pitch of the input video buffer, support only YUV420 Data format */
#endif
    UInt32                      numInputChannels;
    /**< Number of input channels on input Q (Prev link output Q) */
    System_LinkChInfo           inputChInfo[SYSTEM_MAX_CH_PER_OUT_QUE];
    /**< channel info of input */
    AlgorithmLink_StereoAppCreateParams         algLinkCreateParams;
    /**< Create params of the sense and avoid algorithm Link*/
    StereoApp_CreationParamsStruct              algCreateParams;
    /**< Create params of the sense and avoid algorithm */
    StereoApp_ControlParams                     controlParams;
    /**< Control params of the sense and avoid algorithm */
    System_Buffer               *sysBufferDisparity;
    /* Place holder for the Feature Pts sysBuffer */
    System_Buffer buffers[ALGLINK_STEREOAPP_OPQID_MAXOPQ][STEREOAPP_LINK_MAX_NUM_OUTPUT];
    /**< System buffer data structure to exchange buffers between links */
    //System_MetaDataBuffer motionVector[STEREOAPP_LINK_MAX_NUM_OUTPUT];
    System_MetaDataBuffer stereoAppOut[ALGLINK_STEREOAPP_OPQID_MAXOPQ][STEREOAPP_LINK_MAX_NUM_OUTPUT];
    /**< Payload for System buffers */
    AlgorithmLink_OutputQueueInfo outputQInfo[ALGLINK_STEREOAPP_OPQID_MAXOPQ];
    /**< All the information about output Queues used */
    AlgorithmLink_InputQueueInfo  inputQInfo[ALGLINK_STEREOAPP_IPQID_MAXIPQ];
    /**< All the information about input Queues used */
    UInt32                        frameDropCounter;
    /**< Counter to keep track of number of frame drops */
    System_LinkStatistics   *linkStatsInfo;
    /**< Pointer to the Link statistics information,
         used to store below information
            1, min, max and average latency of the link
            2, min, max and average latency from source to this link
            3, links statistics like frames captured, dropped etc
        Pointer is assigned at the link create time from shared
        memory maintained by utils_link_stats layer */
    Bool isFirstFrameRecv;
    /**< Flag to indicate if first frame is received, this is used as trigger
     *   to start stats counting
     */
    Bool isFirstFrameToProcess;

} AlgorithmLink_StereoAppObj;

/*******************************************************************************
 *  Algorithm Link Private Functions
 *******************************************************************************
 */
Int32 AlgorithmLink_StereoAppCreate(void * pObj, void * pCreateParams);
Int32 AlgorithmLink_StereoAppProcess(void * pObj);
Int32 AlgorithmLink_StereoAppControl(void * pObj, void * pControlParams);
Int32 AlgorithmLink_StereoAppStop(void * pObj);
Int32 AlgorithmLink_StereoAppDelete(void * pObj);
Int32 AlgorithmLink_StereoAppPrintStatistics
        (void *pObj, AlgorithmLink_StereoAppObj *pStereoAppObj);

Void AlgorithmLink_initAlgCreateParams(StereoApp_CreationParamsStruct *pAlgCreateParams,
        AlgorithmLink_StereoAppCreateParams * pStereoAppLinkCreateParams);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

/*@}*/

/* Nothing beyond this point */
