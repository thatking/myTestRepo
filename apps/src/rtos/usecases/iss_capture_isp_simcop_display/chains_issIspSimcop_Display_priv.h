/****************************************************************************
Copyright (c) [2012 - 2017] Texas Instruments Incorporated

All rights reserved not granted herein.

Limited License.

 Texas Instruments Incorporated grants a world-wide, royalty-free, non-exclusive
 license under copyrights and patents it now or hereafter owns or controls to
 make,  have made, use, import, offer to sell and sell ('Utilize') this software
 subject to the terms herein.  With respect to the foregoing patent license,
 such license is granted  solely to the extent that any such patent is necessary
 to Utilize the software alone.  The patent license shall not apply to any
 combinations which include this software, other than combinations with devices
 manufactured by or for TI ('TI Devices').  No hardware patent is licensed
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

 THIS SOFTWARE IS PROVIDED BY TI AND TI�S LICENSORS 'AS IS' AND ANY EXPRESS OR
 IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 IN NO EVENT SHALL TI AND TI�S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
******************************************************************************
*/
/*
*******************************************************************************
*
* IMPORTANT NOTE:
*  This file is AUTO-GENERATED by Vision SDK use case generation tool
*
*******************************************************************************
*/

#ifndef _chains_issIspSimcop_Display_H_
#define _chains_issIspSimcop_Display_H_

#include <include/link_api/system.h>
#include <include/link_api/issCaptureLink.h>
#include <include/link_api/issM2mIspLink.h>
#include <include/alglink_api/algorithmLink_sceneObstructionDetect.h>
#include <include/link_api/nullLink.h>
#include <include/link_api/issM2mResizerLink.h>
#include <src/rtos/iss/include/algorithmLink_issAewb.h>
#include <include/link_api/issM2mSimcopLink.h>
#include <include/link_api/grpxSrcLink.h>
#include <include/link_api/displayLink.h>

typedef struct {
       UInt32    IssCaptureLinkID;
       UInt32    IssM2mIspLinkID;
       UInt32    Alg_SceneObstructionDetectLinkID;
       UInt32    NullLinkID;
       UInt32    IssM2mResizerLinkID;
       UInt32    Display_VideoRszBLinkID;
       UInt32    Alg_IssAewbLinkID;
       UInt32    IssM2mSimcopLinkID;
       UInt32    Display_VideoLinkID;
       UInt32    GrpxSrcLinkID;
       UInt32    Display_GrpxLinkID;

       IssCaptureLink_CreateParams                       IssCapturePrm;
       IssM2mIspLink_CreateParams                        IssM2mIspPrm;
       AlgorithmLink_SceneObstructionDetectCreateParams  Alg_SceneObstructionDetectPrm;
       NullLink_CreateParams                             NullPrm;
       IssRszLink_CreateParams                           IssM2mResizerPrm;
       DisplayLink_CreateParams                          Display_VideoRszBPrm;
       AlgorithmLink_IssAewbCreateParams                 Alg_IssAewbPrm;
       IssM2mSimcopLink_CreateParams                     IssM2mSimcopPrm;
       DisplayLink_CreateParams                          Display_VideoPrm;
       GrpxSrcLink_CreateParams                          GrpxSrcPrm;
       DisplayLink_CreateParams                          Display_GrpxPrm;
} chains_issIspSimcop_DisplayObj;

Void chains_issIspSimcop_Display_SetLinkId(chains_issIspSimcop_DisplayObj *pObj);

Void chains_issIspSimcop_Display_ResetLinkPrms(chains_issIspSimcop_DisplayObj *pObj);

Void chains_issIspSimcop_Display_SetPrms(chains_issIspSimcop_DisplayObj *pObj);

Void chains_issIspSimcop_Display_ConnectLinks(chains_issIspSimcop_DisplayObj *pObj);

Int32 chains_issIspSimcop_Display_Create(chains_issIspSimcop_DisplayObj *pObj, Void *appObj);

Int32 chains_issIspSimcop_Display_Start(chains_issIspSimcop_DisplayObj *pObj);

Int32 chains_issIspSimcop_Display_Stop(chains_issIspSimcop_DisplayObj *pObj);

Int32 chains_issIspSimcop_Display_Delete(chains_issIspSimcop_DisplayObj *pObj);

Void chains_issIspSimcop_Display_printBufferStatistics(chains_issIspSimcop_DisplayObj *pObj);

Void chains_issIspSimcop_Display_printStatistics(chains_issIspSimcop_DisplayObj *pObj);

Void chains_issIspSimcop_Display_SetAppPrms(chains_issIspSimcop_DisplayObj *pObj, Void *appObj);

#endif /* _chains_issIspSimcop_Display_H_ */
