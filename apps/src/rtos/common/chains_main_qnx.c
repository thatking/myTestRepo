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
 * \file chains_main_qnx.c
 *
 * \brief  Entry point for IPU1-0 application when A15 OS is QNX
 *
 * \version 0.0 (Feb 2016) : [PR] First version
 *
 *******************************************************************************
*/

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */

#include <src/include/chains.h>
#include <src/rtos/utils_common/include/utils_tsk.h>

#include <src/hlos/common/appCtrlLink_qnx.h>
#include <src/include/link_stats_monitor.h>
#include <src/rtos/utils_common/include/utils_stat_collector.h>

#define APP_CTRL_TSK_PRI                   (4)
#define APP_CTRL_TSK_STACK_SIZE            (16*1024)

/**
 *******************************************************************************
 * \brief Link Specific Object
 *******************************************************************************
 */
typedef struct {

    /**< App Ctrl Task Id */
    UInt32 tskId;

    /**< App Ctrl Task Handle */
    Utils_TskHndl tsk;

    VidSensor_CreateParams vidSensorPrm;

    UInt32 statCollectorInitDone;

} AppCtrl_Obj;

/**
 *******************************************************************************
 * \brief Link Stack
 *******************************************************************************
 */
#pragma DATA_ALIGN(gAppCtrl_tskStack, 32)
#pragma DATA_SECTION(gAppCtrl_tskStack, ".bss:taskStackSection")
UInt8 gAppCtrl_tskStack[APP_CTRL_TSK_STACK_SIZE];

/**
 *******************************************************************************
 * \brief Link Object holds the task id and handle
 *******************************************************************************
 */
AppCtrl_Obj gAppCtrl_obj;

/*******************************************************************************
 *  Functions
 *******************************************************************************
 */


/**
 *******************************************************************************
 *
 * \brief Create and start Video sensor
 *
 *******************************************************************************
 */
Int32 AppCtrl_videoSensorCreateAndStart(AppCtrlCmd_VideoSensorCreateAndStartPrm
                        *pAppPrm)
{
    Int32 status;
    VidSensor_CreateParams *pPrm;
    VidSensor_CreateStatus vidSensorStatus;

    pPrm = &gAppCtrl_obj.vidSensorPrm;

    Vps_printf(" APP_CTRL: Sensor Create And Start ...\n");

    VidSensor_CreateParams_Init(pPrm);

    if(pAppPrm->isLVDSCaptMode==FALSE)
    {
        switch(pAppPrm->sensorId)
        {
            case APP_CTRL_VID_SENSOR_OV10635:
                pPrm->sensorId      = VID_SENSOR_OV10635;
                pPrm->vipInstId[0]  = SYSTEM_CAPTURE_INST_VIP1_SLICE1_PORTA;
#ifdef TDA2EX_BUILD
                //This change is done for supporting tda2ex
                pPrm->vipInstId[0]  = SYSTEM_CAPTURE_INST_VIP1_SLICE2_PORTA;
#endif
                pPrm->standard      = SYSTEM_STD_720P_60;
                pPrm->dataformat    = SYSTEM_DF_YUV422I_UYVY;
                pPrm->videoIfWidth  = SYSTEM_VIFW_8BIT;
                pPrm->fps           = SYSTEM_FPS_30;
                pPrm->isLVDSCaptMode =FALSE;
                pPrm->numChan       = 1;
                break;

            default:
                Vps_printf(" APP_CTRL: Unsupported sensor ID (%d) !!!",
                            pAppPrm->sensorId);
                UTILS_assert(0);
                break;
        }
    }
    else
    {
        /* pAppPrm->sensorId is NOT used and force set to
         *  VID_SENSOR_MULDES_OV1063X from driver point of view
         */
        pPrm->sensorId      = VID_SENSOR_MULDES_OV1063X;
        pPrm->standard      = SYSTEM_STD_720P_60;
        pPrm->dataformat    = SYSTEM_DF_YUV422I_UYVY;
        pPrm->videoIfWidth  = SYSTEM_VIFW_8BIT;
        pPrm->fps           = SYSTEM_FPS_30;
        pPrm->isLVDSCaptMode = TRUE;
        pPrm->numChan       = pAppPrm->numLvdsCh;

        pPrm->vipInstId[0] = SYSTEM_CAPTURE_INST_VIP1_SLICE1_PORTA;
        pPrm->vipInstId[1] = SYSTEM_CAPTURE_INST_VIP1_SLICE2_PORTA;
        pPrm->vipInstId[2] = SYSTEM_CAPTURE_INST_VIP2_SLICE1_PORTA;
        pPrm->vipInstId[3] = SYSTEM_CAPTURE_INST_VIP3_SLICE1_PORTA;
        pPrm->vipInstId[4] = SYSTEM_CAPTURE_INST_VIP3_SLICE2_PORTA;
        pPrm->vipInstId[5] = SYSTEM_CAPTURE_INST_VIP2_SLICE2_PORTB;
        /* Vin4b has conflict with GMAC ,
         * Sensor connect fails when enabling NDK
         */
#ifdef TDA2EX_BUILD
        //This change is done for supporting tda2ex
        pPrm->vipInstId[0] = SYSTEM_CAPTURE_INST_VIP1_SLICE2_PORTA;
        pPrm->vipInstId[1] = SYSTEM_CAPTURE_INST_VIP1_SLICE1_PORTA;
        pPrm->vipInstId[2] = SYSTEM_CAPTURE_INST_VIP1_SLICE2_PORTB;
        pPrm->vipInstId[3] = SYSTEM_CAPTURE_INST_VIP1_SLICE1_PORTB;
#endif

    }

    status = VidSensor_create(pPrm, &vidSensorStatus);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    status = VidSensor_control(pPrm,
                                VID_SENSOR_CMD_START,
                                NULL,
                                NULL);

    Vps_printf(" APP_CTRL: Sensor Create And Start done.\n");
    return status;
}

/**
 *******************************************************************************
 *
 * \brief Stop and delete Video sensor
 *
 *******************************************************************************
 */
Int32 AppCtrl_videoSensorStopAndDelete()
{
    Int32 status;
    VidSensor_CreateParams *pPrm;

    Vps_printf(" APP_CTRL: Sensor Stop And Delete ...\n");

    pPrm = &gAppCtrl_obj.vidSensorPrm;

    status = VidSensor_control(pPrm,
                                VID_SENSOR_CMD_STOP,
                                NULL,
                                NULL);
    status |= VidSensor_delete(pPrm, NULL);

    Vps_printf(" APP_CTRL: Sensor Stop And Delete done.\n");
    return status;
}


/**
 *******************************************************************************
 *
 * \brief Set DMM priorities
 *
 *******************************************************************************
 */
Void AppCtrl_setSystemL3DmmPri()
{
    /* Assert Mflag of DSS to give DSS highest priority */
    Utils_setDssMflagMode(UTILS_DSS_MFLAG_MODE_FORCE_ENABLE);

    /* enable usage of Mflag at DMM */
    Utils_setDmmMflagEmergencyEnable(TRUE);

    /* Set DMM as higest priority at DMM and EMIF */
    Utils_setDmmPri(UTILS_DMM_INITIATOR_ID_DSS, 0);

    Utils_setBWLimiter(UTILS_DMM_INITIATOR_ID_GPU_P1, 1000);
    Utils_setBWLimiter(UTILS_DMM_INITIATOR_ID_GPU_P2, 1000);
}


/**
 *******************************************************************************
 *
 * \brief Handles the Commands received.
 *
 * \param   pObj           [IN] AppCtrl_Obj
 *
 * \param   cmd            [IN] input command
 *
 * \param   pPrm           [IN] input message
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Int32 AppCtrl_cmdHandler(AppCtrl_Obj * pObj, UInt32 cmd, Void * pPrm)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;

    switch (cmd)
    {
        case APP_CTRL_LINK_CMD_BOARD_ENABLE_USB_CHARGING:
            Board_enableUsbCharging();
            break;

        case APP_CTRL_LINK_CMD_BOARD_IS_MULTI_DES_CONNECTED:
        {
            AppCtrlCmd_BoardIsMultiDesConnectedPrm *pAppPrm
                = (AppCtrlCmd_BoardIsMultiDesConnectedPrm*)pPrm;

            pAppPrm->isConnected = Board_isMultiDesConnected();

            break;
        }

        case APP_CTRL_LINK_CMD_SET_DMM_PRIORITIES:
            Vps_printf(" APP_CTRL: CMD_SET_DMM_PRIORITIES !!!\n");
            AppCtrl_setSystemL3DmmPri();
            break;

        case APP_CTRL_LINK_CMD_STAT_COLLECTOR_INIT:
        {
            Vps_printf(" APP_CTRL: CMD_STAT_COLLECTOR_INIT !!!\n");
            if (gAppCtrl_obj.statCollectorInitDone) {
                /* Note: We currently initiaize the stat collector only once */
                break;
            }
            Utils_statCollectorInit(); /* Initializing the statCollector */
            Chains_linkStatsMonitorInit();
            gAppCtrl_obj.statCollectorInitDone = 1;
            break;
        }

        case APP_CTRL_LINK_CMD_STAT_COLLECTOR_DEINIT:
            Vps_printf(" APP_CTRL: CMD_STAT_COLLECTOR_DEINIT !!!\n");
            /* Note: We currently initiaize the stat collector only once
             * hence we do not deinit below
             */
            //Utils_statCollectorDeInit();
            //Chains_linkStatsMonitorDeInit();
            break;

        case APP_CTRL_LINK_CMD_VIDEO_SENSOR_CREATE_AND_START:
        {
            AppCtrlCmd_VideoSensorCreateAndStartPrm *pAppPrm
                = (AppCtrlCmd_VideoSensorCreateAndStartPrm*)pPrm;

            status = AppCtrl_videoSensorCreateAndStart(pAppPrm);
            break;
        }

        case APP_CTRL_LINK_CMD_VIDEO_SENSOR_STOP_AND_DELETE:
            status = AppCtrl_videoSensorStopAndDelete();
            break;

        default:
            break;
    }

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Creates Command handler task
 *        handles the commands for Profiling and core stats
 *
 * \param   pTsk    [IN]  Utils_TskHndl
 *
 * \param   pMsg    [IN]  Utils_MsgHndl
 *
 *******************************************************************************
*/
Void AppCtrl_tskMain(struct Utils_TskHndl_t * pTsk, Utils_MsgHndl * pMsg)
{
    Int32 status;
    AppCtrl_Obj *pObj = (AppCtrl_Obj *) pTsk->appData;

    status = AppCtrl_cmdHandler(pObj,
                                   Utils_msgGetCmd(pMsg),
                                   Utils_msgGetPrm(pMsg));
    Utils_tskAckOrFreeMsg(pMsg, status);

    return;
}

/**
 *******************************************************************************
 *
 * \brief Initialize the ipu systemLink
 *        Initializes the linkObj and creates the task for AppCtrl_tskMain
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Int32 AppCtrl_init()
{
    Int32 status;
    System_LinkObj linkObj;
    AppCtrl_Obj *pObj;
    char tskName[32];
    unsigned int coreId;

    pObj = &gAppCtrl_obj;

    memset(pObj, 0, sizeof(*pObj));
    coreId = System_getSelfProcId();
    pObj->tskId = SYSTEM_MAKE_LINK_ID(coreId, SYSTEM_LINK_ID_APP_CTRL);

    linkObj.pTsk = &pObj->tsk;
    linkObj.linkGetFullBuffers = NULL;
    linkObj.linkPutEmptyBuffers = NULL;
    linkObj.getLinkInfo = NULL;

    System_registerLink(pObj->tskId, &linkObj);

    sprintf(tskName, "APP_CTRL");

    status = Utils_tskCreate(&pObj->tsk,
                             AppCtrl_tskMain,
                             APP_CTRL_TSK_PRI,
                             gAppCtrl_tskStack,
                             sizeof(gAppCtrl_tskStack), pObj, tskName,
                             UTILS_TSK_AFFINITY_CORE0);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Delete the AppCtrl_tskMain created
 *
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Int32 AppCtrl_deInit()
{
    Utils_tskDelete(&gAppCtrl_obj.tsk);

    return SYSTEM_LINK_STATUS_SOK;
}


/**
 *******************************************************************************
 *
 * \brief   Entry point for application on IPU1-0
 *
 * \param   arg0    [IN]  default args
 *
 * \param   arg1    [IN]  default args
 *
 *******************************************************************************
*/
Void Chains_main(UArg arg0, UArg arg1)
{
#ifdef IPU_PRIMARY_CORE_IPU1
    Void IPU1_0_main(UArg arg0, UArg arg1);
#else
    Void IPU2_main(UArg arg0, UArg arg1);
#endif

    Vps_printf(" CHAINS: Application Started !!!");

#ifndef EARLY_SRV_ENABLE
    Board_init();
#endif

    AppCtrl_init();

#ifdef IPU_PRIMARY_CORE_IPU1
    IPU1_0_main(NULL, NULL);
#else
    IPU2_main(NULL, NULL);
#endif

    Board_deInit();
    AppCtrl_deInit();

    Vps_printf(" CHAINS: Application Exited !!!");
}

