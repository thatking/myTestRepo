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

#ifndef _chains_tidlDspTda3x_H_
#define _chains_tidlDspTda3x_H_

#include <include/link_api/system.h>
#include <include/link_api/nullSrcLink.h>
#include <include/alglink_api/algorithmLink_tidlpreproc.h>
#include <include/alglink_api/algorithmLink_tidl.h>
#include <include/link_api/ipcLink.h>
#include <include/link_api/mergeLink.h>
#include <include/link_api/nullLink.h>

typedef struct {
       UInt32    NullSourceLinkID;
       UInt32    Alg_tidlpreprocLinkID;
       UInt32    IPCOut_IPU1_0_DSP1_0LinkID;
       UInt32    IPCIn_DSP1_IPU1_0_0LinkID;
       UInt32    Alg_tidl_1LinkID;
       UInt32    IPCOut_DSP1_IPU1_0_0LinkID;
       UInt32    IPCIn_IPU1_0_DSP1_0LinkID;
       UInt32    MergeLinkID;
       UInt32    NullLinkID;

       NullSrcLink_CreateParams                          NullSourcePrm;
       AlgorithmLink_tidlpreprocCreateParams   Alg_tidlpreprocPrm;
       IpcLink_CreateParams                              IPCOut_IPU1_0_DSP1_0Prm;
       IpcLink_CreateParams                              IPCIn_DSP1_IPU1_0_0Prm;
       AlgorithmLink_tidlCreateParams          Alg_tidl_1Prm;
       IpcLink_CreateParams                              IPCOut_DSP1_IPU1_0_0Prm;
       IpcLink_CreateParams                              IPCIn_IPU1_0_DSP1_0Prm;
       MergeLink_CreateParams                            MergePrm;
       NullLink_CreateParams                             NullPrm;
} chains_tidlDspTda3xObj;

Void chains_tidlDspTda3x_SetLinkId(chains_tidlDspTda3xObj *pObj);

Void chains_tidlDspTda3x_ResetLinkPrms(chains_tidlDspTda3xObj *pObj);

Void chains_tidlDspTda3x_SetPrms(chains_tidlDspTda3xObj *pObj);

Void chains_tidlDspTda3x_ConnectLinks(chains_tidlDspTda3xObj *pObj);

Int32 chains_tidlDspTda3x_Create(chains_tidlDspTda3xObj *pObj, Void *appObj);

Int32 chains_tidlDspTda3x_Start(chains_tidlDspTda3xObj *pObj);

Int32 chains_tidlDspTda3x_Stop(chains_tidlDspTda3xObj *pObj);

Int32 chains_tidlDspTda3x_Delete(chains_tidlDspTda3xObj *pObj);

Void chains_tidlDspTda3x_printBufferStatistics(chains_tidlDspTda3xObj *pObj);

Void chains_tidlDspTda3x_printStatistics(chains_tidlDspTda3xObj *pObj);

Void chains_tidlDspTda3x_SetAppPrms(chains_tidlDspTda3xObj *pObj, Void *appObj);

#endif /* _chains_tidlDspTda3x_H_ */
