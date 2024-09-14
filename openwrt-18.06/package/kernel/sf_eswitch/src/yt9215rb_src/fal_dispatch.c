/*******************************************************************************
*                                                                              *
*  Copyright (c), 2022, Motorcomm Electronic Technology Co.,Ltd.               *
*  Motorcomm Confidential and Proprietary.                                     *
*                                                                              *
********************************************************************************
*/
#include "yt_error.h"
#include "osal_mem.h"
#include "osal_print.h"
#include "yt_types.h"
#include "fal_dispatch.h"
#include "cal_mgm.h"

#ifdef SWITCH_SERIES_TIGER
#include "fal_tiger_dispatch.h"
#endif


fal_dispatch_info_t gfal_dispatch_info[] =
{
#ifdef SWITCH_SERIES_TIGER
    {YT_SW_ID_9215,  YT_SW_REV_A, &fal_tiger_dispatch},
#endif
};

fal_dispatch_t *gpfal_dispatch[YT_MAX_UNIT];

/*
 * Function Declaration
 */

uint32_t fal_dispatch_init(void)
{
    uint32_t i;
    cmm_err_t ret = CMM_ERR_OK;
    
    static uint8_t gdispatch_inited = FALSE;
    
    CMM_PARAM_CHK((TRUE == gdispatch_inited), CMM_ERR_OK);
    
    for(i = 0; YT_UNIT_NUM > i; i++)
    {
        CMM_ERR_CHK(fal_dispatch_get(&(gpfal_dispatch[i]), i), ret);
        gpfal_dispatch[i]->is_inited = TRUE;             
    }

    gdispatch_inited = TRUE;
   
    return CMM_ERR_OK;
}

uint32_t fal_dispatch_get(fal_dispatch_t **pdispatch, uint8_t unit)
{
    uint32_t num = sizeof(gfal_dispatch_info) / sizeof(fal_dispatch_info_t);
    uint32_t i;
    
    CMM_PARAM_CHK((YT_UNIT_NUM <= unit), CMM_ERR_INPUT);
          
    CMM_PARAM_CHK((NULL == pdispatch), CMM_ERR_NULL_POINT);
    
    for(i = 0; num > i; i++)
    {
        if(gfal_dispatch_info[i].chip_id == UNITINFO(unit)->chip_id)
        {
            *pdispatch = gfal_dispatch_info[i].pdispatch;
            return CMM_ERR_OK;
        }
    }
   
    return CMM_ERR_FAIL;
}

yt_ret_t fal_func_unavailable(void)
{
    return CMM_ERR_NOT_SUPPORT;
}
