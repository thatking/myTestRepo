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
 * \file eth_cam.c
 *
 * \brief  This file has the implementataion of AVB Cam Control API
 *
 *         APIs can be used to control AVB Cam on the TDA2EX ETH SRV board.
 *         Drivers for avb cam can be part of BSP or any other package.
 *
 *
 * \version 0.0 : First version
 *
 *******************************************************************************
*/

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
// #include <src/include/eth_cam.h>
#include <include/link_api/system.h>

#include <ti/drv/vps/include/fvid2/fvid2.h>
#include <ti/drv/vps/include/vps.h>
#include <ti/drv/vps/include/devices/bsp_device.h>
#include <ti/drv/vps/include/boards/bsp_board.h>


/**
 *******************************************************************************
 *
 * \brief Create function to create hdmi receiver.
 *
 *        Creates the hdmi receiver handle using bsp function calls.
 *
 * \param  createParams   [IN] Create parameters for hdmi receiver
 *
 * \param  createStatus   [OUT] Status
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Int32 EthCam_create()
{
    Int32  retVal = SYSTEM_LINK_STATUS_EFAIL;
    UInt32 avbCamInstId, avbCamDrvId;

    avbCamDrvId         = FVID2_VID_ETHSRV_CAM_DRV;
    avbCamInstId         = BSP_DEVICE_ETH_CAM_INST_ID_0;

    /* Power on Ethernet camera  */
    /*
     * Not calling for all camera instance ids as all camera modules are
     * controlled through same switch.
     */
    retVal = Bsp_boardPowerOnDevice(avbCamDrvId, avbCamInstId, TRUE);
    UTILS_assert (retVal == 0);

    return retVal;
}


/*******************************************************************************
 *
 * \brief Delete function to delete hdmi receiver.
 *
 *        Deletes the hdmi receiver handle using Fvid2_delete function calls.
 *
 * \param  createParams    [IN] Create parameters for hdmi receiver
 *
 * \param  deleteArgs      Not used.
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Int32 EthCam_delete()
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;

    Int32  retVal = SYSTEM_LINK_STATUS_EFAIL;
    UInt32 avbCamInstId, avbCamDrvId;

    avbCamDrvId         = FVID2_VID_ETHSRV_CAM_DRV;
    avbCamInstId         = BSP_DEVICE_ETH_CAM_INST_ID_0;

    /* Power off Ethernet camera  */
    /*
     * Not calling for all camera instance ids as all camera modules are
     * controlled through same switch.
     */
    retVal = Bsp_boardPowerOnDevice(avbCamDrvId, avbCamInstId, FALSE);
    UTILS_assert (retVal == 0);

    return status;
}

