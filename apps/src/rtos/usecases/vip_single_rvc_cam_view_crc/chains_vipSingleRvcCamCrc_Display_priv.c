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

/*
*******************************************************************************
*
* IMPORTANT NOTE:
*  This file is AUTO-GENERATED by Vision SDK use case generation tool
*
*******************************************************************************
*/
#include "chains_vipSingleRvcCamCrc_Display_priv.h"
Void chains_vipSingleRvcCamCrc_Display_SetLinkId(chains_vipSingleRvcCamCrc_DisplayObj *pObj){
       pObj->CaptureLinkID                  = SYSTEM_LINK_ID_CAPTURE_0;
       pObj->Dup_captureLinkID              = IPU1_0_LINK (SYSTEM_LINK_ID_DUP_0);
       pObj->IPCOut_IPU1_0_DSP1_0LinkID     = IPU1_0_LINK (SYSTEM_LINK_ID_IPC_OUT_0);
       pObj->IPCIn_DSP1_IPU1_0_0LinkID      = DSP1_LINK (SYSTEM_LINK_ID_IPC_IN_0);
       pObj->Alg_SwCrcLinkID                = DSP1_LINK (SYSTEM_LINK_ID_ALG_0);
       pObj->Alg_RvcDiagnosticLinkID        = IPU1_0_LINK (SYSTEM_LINK_ID_ALG_0);
       pObj->VPE_deiLinkID                  = SYSTEM_LINK_ID_VPE_0;
       pObj->Display_VideoLinkID            = SYSTEM_LINK_ID_DISPLAY_0;
       pObj->GrpxSrcLinkID                  = IPU1_0_LINK (SYSTEM_LINK_ID_GRPX_SRC_0);
       pObj->Display_GrpxLinkID             = SYSTEM_LINK_ID_DISPLAY_1;
}

Void chains_vipSingleRvcCamCrc_Display_ResetLinkPrms(chains_vipSingleRvcCamCrc_DisplayObj *pObj){
       CaptureLink_CreateParams_Init(&pObj->CapturePrm);
       DupLink_CreateParams_Init(&pObj->Dup_capturePrm);
       IpcLink_CreateParams_Init(&pObj->IPCOut_IPU1_0_DSP1_0Prm);
       IpcLink_CreateParams_Init(&pObj->IPCIn_DSP1_IPU1_0_0Prm);
       AlgorithmLink_SwCrc_Init(&pObj->Alg_SwCrcPrm);
       AlgorithmLink_RvcDiagnostic_Init(&pObj->Alg_RvcDiagnosticPrm);
       VpeLink_CreateParams_Init(&pObj->VPE_deiPrm);
       DisplayLink_CreateParams_Init(&pObj->Display_VideoPrm);
       GrpxSrcLink_CreateParams_Init(&pObj->GrpxSrcPrm);
       DisplayLink_CreateParams_Init(&pObj->Display_GrpxPrm);
}

Void chains_vipSingleRvcCamCrc_Display_SetPrms(chains_vipSingleRvcCamCrc_DisplayObj *pObj){
       (pObj->Dup_capturePrm).numOutQue = 2;
       (pObj->Alg_SwCrcPrm).baseClassCreate.size = sizeof(AlgorithmLink_SwCrcCreateParams);
       (pObj->Alg_SwCrcPrm).baseClassCreate.algId = ALGORITHM_LINK_DSP_ALG_SW_CRC;
       (pObj->Alg_RvcDiagnosticPrm).baseClassCreate.size  = sizeof(AlgorithmLink_RvcDiagnosticCreateParams);
       (pObj->Alg_RvcDiagnosticPrm).baseClassCreate.algId  = ALGORITHM_LINK_IPU_ALG_RVC_DIAGNOSTIC;
}

Void chains_vipSingleRvcCamCrc_Display_ConnectLinks(chains_vipSingleRvcCamCrc_DisplayObj *pObj){

       //Capture -> Dup_capture
       pObj->CapturePrm.outQueParams.nextLink = pObj->Dup_captureLinkID;
       pObj->Dup_capturePrm.inQueParams.prevLinkId = pObj->CaptureLinkID;
       pObj->Dup_capturePrm.inQueParams.prevLinkQueId = 0;

       //Dup_capture -> Alg_RvcDiagnostic
       pObj->Dup_capturePrm.outQueParams[0].nextLink = pObj->Alg_RvcDiagnosticLinkID;
       pObj->Alg_RvcDiagnosticPrm.inQueParams.prevLinkId = pObj->Dup_captureLinkID;
       pObj->Alg_RvcDiagnosticPrm.inQueParams.prevLinkQueId = 0;

       //Dup_capture -> IPCOut_IPU1_0_DSP1_0
       pObj->Dup_capturePrm.outQueParams[1].nextLink = pObj->IPCOut_IPU1_0_DSP1_0LinkID;
       pObj->IPCOut_IPU1_0_DSP1_0Prm.inQueParams.prevLinkId = pObj->Dup_captureLinkID;
       pObj->IPCOut_IPU1_0_DSP1_0Prm.inQueParams.prevLinkQueId = 1;

       //IPCOut_IPU1_0_DSP1_0 -> IPCIn_DSP1_IPU1_0_0
       pObj->IPCOut_IPU1_0_DSP1_0Prm.outQueParams.nextLink = pObj->IPCIn_DSP1_IPU1_0_0LinkID;
       pObj->IPCIn_DSP1_IPU1_0_0Prm.inQueParams.prevLinkId = pObj->IPCOut_IPU1_0_DSP1_0LinkID;
       pObj->IPCIn_DSP1_IPU1_0_0Prm.inQueParams.prevLinkQueId = 0;

       //IPCIn_DSP1_IPU1_0_0 -> Alg_SwCrc
       pObj->IPCIn_DSP1_IPU1_0_0Prm.outQueParams.nextLink = pObj->Alg_SwCrcLinkID;
       pObj->Alg_SwCrcPrm.inQueParams.prevLinkId = pObj->IPCIn_DSP1_IPU1_0_0LinkID;
       pObj->Alg_SwCrcPrm.inQueParams.prevLinkQueId = 0;

       //Alg_RvcDiagnostic -> VPE_dei
       pObj->Alg_RvcDiagnosticPrm.outQueParams.nextLink = pObj->VPE_deiLinkID;
       pObj->VPE_deiPrm.inQueParams.prevLinkId = pObj->Alg_RvcDiagnosticLinkID;
       pObj->VPE_deiPrm.inQueParams.prevLinkQueId = 0;

       //VPE_dei -> Display_Video
       pObj->VPE_deiPrm.outQueParams[0].nextLink = pObj->Display_VideoLinkID;
       pObj->Display_VideoPrm.inQueParams.prevLinkId = pObj->VPE_deiLinkID;
       pObj->Display_VideoPrm.inQueParams.prevLinkQueId = 0;

       //GrpxSrc -> Display_Grpx
       pObj->GrpxSrcPrm.outQueParams.nextLink = pObj->Display_GrpxLinkID;
       pObj->Display_GrpxPrm.inQueParams.prevLinkId = pObj->GrpxSrcLinkID;
       pObj->Display_GrpxPrm.inQueParams.prevLinkQueId = 0;

}

Int32 chains_vipSingleRvcCamCrc_Display_Create(chains_vipSingleRvcCamCrc_DisplayObj *pObj, Void *appObj){

       Int32 status;

       chains_vipSingleRvcCamCrc_Display_SetLinkId(pObj);
       chains_vipSingleRvcCamCrc_Display_ResetLinkPrms(pObj);

       chains_vipSingleRvcCamCrc_Display_SetPrms(pObj);
       chains_vipSingleRvcCamCrc_Display_SetAppPrms(pObj, appObj);

       chains_vipSingleRvcCamCrc_Display_ConnectLinks(pObj);
       status = System_linkCreate(pObj->CaptureLinkID, &pObj->CapturePrm, sizeof(pObj->CapturePrm));
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkCreate(pObj->Dup_captureLinkID, &pObj->Dup_capturePrm, sizeof(pObj->Dup_capturePrm));
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkCreate(pObj->IPCOut_IPU1_0_DSP1_0LinkID, &pObj->IPCOut_IPU1_0_DSP1_0Prm, sizeof(pObj->IPCOut_IPU1_0_DSP1_0Prm));
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkCreate(pObj->IPCIn_DSP1_IPU1_0_0LinkID, &pObj->IPCIn_DSP1_IPU1_0_0Prm, sizeof(pObj->IPCIn_DSP1_IPU1_0_0Prm));
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkCreate(pObj->Alg_SwCrcLinkID, &pObj->Alg_SwCrcPrm, sizeof(pObj->Alg_SwCrcPrm));
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkCreate(pObj->Alg_RvcDiagnosticLinkID, &pObj->Alg_RvcDiagnosticPrm, sizeof(pObj->Alg_RvcDiagnosticPrm));
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkCreate(pObj->VPE_deiLinkID, &pObj->VPE_deiPrm, sizeof(pObj->VPE_deiPrm));
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkCreate(pObj->Display_VideoLinkID, &pObj->Display_VideoPrm, sizeof(pObj->Display_VideoPrm));
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkCreate(pObj->GrpxSrcLinkID, &pObj->GrpxSrcPrm, sizeof(pObj->GrpxSrcPrm));
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkCreate(pObj->Display_GrpxLinkID, &pObj->Display_GrpxPrm, sizeof(pObj->Display_GrpxPrm));
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       return status;
}

Int32 chains_vipSingleRvcCamCrc_Display_Start(chains_vipSingleRvcCamCrc_DisplayObj *pObj){

       Int32 status;

       status = System_linkStart(pObj->Display_GrpxLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStart(pObj->GrpxSrcLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStart(pObj->Display_VideoLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStart(pObj->VPE_deiLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStart(pObj->Alg_RvcDiagnosticLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStart(pObj->Alg_SwCrcLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStart(pObj->IPCIn_DSP1_IPU1_0_0LinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStart(pObj->IPCOut_IPU1_0_DSP1_0LinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStart(pObj->Dup_captureLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStart(pObj->CaptureLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       return status;
}

Int32 chains_vipSingleRvcCamCrc_Display_Stop(chains_vipSingleRvcCamCrc_DisplayObj *pObj){

       Int32 status;

       status = System_linkStop(pObj->Display_GrpxLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStop(pObj->GrpxSrcLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStop(pObj->Display_VideoLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStop(pObj->VPE_deiLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStop(pObj->Alg_RvcDiagnosticLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStop(pObj->Alg_SwCrcLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStop(pObj->IPCIn_DSP1_IPU1_0_0LinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStop(pObj->IPCOut_IPU1_0_DSP1_0LinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStop(pObj->Dup_captureLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStop(pObj->CaptureLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       return status;
}

Int32 chains_vipSingleRvcCamCrc_Display_Delete(chains_vipSingleRvcCamCrc_DisplayObj *pObj){

       Int32 status;

       status = System_linkDelete(pObj->Display_GrpxLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkDelete(pObj->GrpxSrcLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkDelete(pObj->Display_VideoLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkDelete(pObj->VPE_deiLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkDelete(pObj->Alg_RvcDiagnosticLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkDelete(pObj->Alg_SwCrcLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkDelete(pObj->IPCIn_DSP1_IPU1_0_0LinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkDelete(pObj->IPCOut_IPU1_0_DSP1_0LinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkDelete(pObj->Dup_captureLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkDelete(pObj->CaptureLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       return status;
}

Void chains_vipSingleRvcCamCrc_Display_printBufferStatistics(chains_vipSingleRvcCamCrc_DisplayObj *pObj){
       System_linkPrintBufferStatistics(pObj->CaptureLinkID);
       System_linkPrintBufferStatistics(pObj->Dup_captureLinkID);
       System_linkPrintBufferStatistics(pObj->IPCOut_IPU1_0_DSP1_0LinkID);
       Task_sleep(500);
       System_linkPrintBufferStatistics(pObj->IPCIn_DSP1_IPU1_0_0LinkID);
       System_linkPrintBufferStatistics(pObj->Alg_SwCrcLinkID);
       Task_sleep(500);
       System_linkPrintBufferStatistics(pObj->Alg_RvcDiagnosticLinkID);
       System_linkPrintBufferStatistics(pObj->VPE_deiLinkID);
       System_linkPrintBufferStatistics(pObj->Display_VideoLinkID);
       System_linkPrintBufferStatistics(pObj->GrpxSrcLinkID);
       System_linkPrintBufferStatistics(pObj->Display_GrpxLinkID);
       Task_sleep(500);
}

Void chains_vipSingleRvcCamCrc_Display_printStatistics(chains_vipSingleRvcCamCrc_DisplayObj *pObj){
       System_linkPrintStatistics(pObj->CaptureLinkID);
       System_linkPrintStatistics(pObj->Dup_captureLinkID);
       System_linkPrintStatistics(pObj->IPCOut_IPU1_0_DSP1_0LinkID);
       Task_sleep(500);
       System_linkPrintStatistics(pObj->IPCIn_DSP1_IPU1_0_0LinkID);
       System_linkPrintStatistics(pObj->Alg_SwCrcLinkID);
       Task_sleep(500);
       System_linkPrintStatistics(pObj->Alg_RvcDiagnosticLinkID);
       System_linkPrintStatistics(pObj->VPE_deiLinkID);
       System_linkPrintStatistics(pObj->Display_VideoLinkID);
       System_linkPrintStatistics(pObj->GrpxSrcLinkID);
       System_linkPrintStatistics(pObj->Display_GrpxLinkID);
       Task_sleep(500);
}