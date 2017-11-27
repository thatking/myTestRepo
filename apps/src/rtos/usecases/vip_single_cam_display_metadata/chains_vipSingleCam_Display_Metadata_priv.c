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
#include "chains_vipSingleCam_Display_Metadata_priv.h"
Void chains_vipSingleCam_Display_Metadata_SetLinkId(chains_vipSingleCam_Display_MetadataObj *pObj){
       pObj->CaptureLinkID                  = SYSTEM_LINK_ID_CAPTURE_0;
       pObj->DisplayMultiPipe_VideoLinkID   = SYSTEM_LINK_ID_DISPLAY_MULTI_PIPE_0;
       pObj->GrpxSrcLinkID                  = IPU1_0_LINK (SYSTEM_LINK_ID_GRPX_SRC_0);
       pObj->Display_GrpxLinkID             = SYSTEM_LINK_ID_DISPLAY_0;
       pObj->Capture_dsswbLinkID            = SYSTEM_LINK_ID_CAPTURE_1;
       pObj->NullLinkID                     = IPU1_0_LINK (SYSTEM_LINK_ID_NULL_0);
}

Void chains_vipSingleCam_Display_Metadata_ResetLinkPrms(chains_vipSingleCam_Display_MetadataObj *pObj){
       CaptureLink_CreateParams_Init(&pObj->CapturePrm);
       DisplayMpLink_CreateParams_Init(&pObj->DisplayMultiPipe_VideoPrm);
       GrpxSrcLink_CreateParams_Init(&pObj->GrpxSrcPrm);
       DisplayLink_CreateParams_Init(&pObj->Display_GrpxPrm);
       CaptureLink_CreateParams_Init(&pObj->Capture_dsswbPrm);
       NullLink_CreateParams_Init (&pObj->NullPrm);
}

Void chains_vipSingleCam_Display_Metadata_SetPrms(chains_vipSingleCam_Display_MetadataObj *pObj){
       (pObj->NullPrm).numInQue = 1;
}

Void chains_vipSingleCam_Display_Metadata_ConnectLinks(chains_vipSingleCam_Display_MetadataObj *pObj){

       //Capture -> DisplayMultiPipe_Video
       pObj->CapturePrm.outQueParams.nextLink = pObj->DisplayMultiPipe_VideoLinkID;
       pObj->DisplayMultiPipe_VideoPrm.inQueParams.prevLinkId = pObj->CaptureLinkID;
       pObj->DisplayMultiPipe_VideoPrm.inQueParams.prevLinkQueId = 0;

       //GrpxSrc -> Display_Grpx
       pObj->GrpxSrcPrm.outQueParams.nextLink = pObj->Display_GrpxLinkID;
       pObj->Display_GrpxPrm.inQueParams.prevLinkId = pObj->GrpxSrcLinkID;
       pObj->Display_GrpxPrm.inQueParams.prevLinkQueId = 0;

       //Capture_dsswb -> Null
       pObj->Capture_dsswbPrm.outQueParams.nextLink = pObj->NullLinkID;
       pObj->NullPrm.inQueParams[0].prevLinkId = pObj->Capture_dsswbLinkID;
       pObj->NullPrm.inQueParams[0].prevLinkQueId = 0;

}

Int32 chains_vipSingleCam_Display_Metadata_Create(chains_vipSingleCam_Display_MetadataObj *pObj, Void *appObj){

       Int32 status;

       chains_vipSingleCam_Display_Metadata_SetLinkId(pObj);
       chains_vipSingleCam_Display_Metadata_ResetLinkPrms(pObj);

       chains_vipSingleCam_Display_Metadata_SetPrms(pObj);
       chains_vipSingleCam_Display_Metadata_SetAppPrms(pObj, appObj);

       chains_vipSingleCam_Display_Metadata_ConnectLinks(pObj);
       status = System_linkCreate(pObj->CaptureLinkID, &pObj->CapturePrm, sizeof(pObj->CapturePrm));
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkCreate(pObj->DisplayMultiPipe_VideoLinkID, &pObj->DisplayMultiPipe_VideoPrm, sizeof(pObj->DisplayMultiPipe_VideoPrm));
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkCreate(pObj->GrpxSrcLinkID, &pObj->GrpxSrcPrm, sizeof(pObj->GrpxSrcPrm));
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkCreate(pObj->Display_GrpxLinkID, &pObj->Display_GrpxPrm, sizeof(pObj->Display_GrpxPrm));
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkCreate(pObj->Capture_dsswbLinkID, &pObj->Capture_dsswbPrm, sizeof(pObj->Capture_dsswbPrm));
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkCreate(pObj->NullLinkID, &pObj->NullPrm, sizeof(pObj->NullPrm));
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       return status;
}

Int32 chains_vipSingleCam_Display_Metadata_Start(chains_vipSingleCam_Display_MetadataObj *pObj){

       Int32 status;

       status = System_linkStart(pObj->NullLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStart(pObj->Capture_dsswbLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStart(pObj->Display_GrpxLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStart(pObj->GrpxSrcLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStart(pObj->DisplayMultiPipe_VideoLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStart(pObj->CaptureLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       return status;
}

Int32 chains_vipSingleCam_Display_Metadata_Stop(chains_vipSingleCam_Display_MetadataObj *pObj){

       Int32 status;

       status = System_linkStop(pObj->NullLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStop(pObj->Capture_dsswbLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStop(pObj->Display_GrpxLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStop(pObj->GrpxSrcLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStop(pObj->DisplayMultiPipe_VideoLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStop(pObj->CaptureLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       return status;
}

Int32 chains_vipSingleCam_Display_Metadata_Delete(chains_vipSingleCam_Display_MetadataObj *pObj){

       Int32 status;

       status = System_linkDelete(pObj->NullLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkDelete(pObj->Capture_dsswbLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkDelete(pObj->Display_GrpxLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkDelete(pObj->GrpxSrcLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkDelete(pObj->DisplayMultiPipe_VideoLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkDelete(pObj->CaptureLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       return status;
}

Void chains_vipSingleCam_Display_Metadata_printBufferStatistics(chains_vipSingleCam_Display_MetadataObj *pObj){
       System_linkPrintBufferStatistics(pObj->CaptureLinkID);
       System_linkPrintBufferStatistics(pObj->DisplayMultiPipe_VideoLinkID);
       System_linkPrintBufferStatistics(pObj->GrpxSrcLinkID);
       System_linkPrintBufferStatistics(pObj->Display_GrpxLinkID);
       System_linkPrintBufferStatistics(pObj->Capture_dsswbLinkID);
       System_linkPrintBufferStatistics(pObj->NullLinkID);
       Task_sleep(500);
}

Void chains_vipSingleCam_Display_Metadata_printStatistics(chains_vipSingleCam_Display_MetadataObj *pObj){
       System_linkPrintStatistics(pObj->CaptureLinkID);
       System_linkPrintStatistics(pObj->DisplayMultiPipe_VideoLinkID);
       System_linkPrintStatistics(pObj->GrpxSrcLinkID);
       System_linkPrintStatistics(pObj->Display_GrpxLinkID);
       System_linkPrintStatistics(pObj->Capture_dsswbLinkID);
       System_linkPrintStatistics(pObj->NullLinkID);
       Task_sleep(500);
}

