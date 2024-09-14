
#ifndef _FAL_TIGER_INTERRUPT_C
#define _FAL_TIGER_INTERRUPT_C
#include "fal_tiger_interrupt.h"
#include "fal_tiger_struct.h"
#include "fal_tiger_entry.h"
#ifdef PORT_INCLUDED
#include "fal_tiger_port.h"
#endif

yt_ret_t fal_tiger_int_polarity_set(yt_unit_t unit, yt_int_polarity_t type)
{
    global_ctrl1_t entry;
    cmm_err_t ret = CMM_ERR_OK;

    CMM_ERR_CHK(HAL_TBL_REG_READ(unit, GLOBAL_CTRL1m, 0, sizeof(global_ctrl1_t), &entry), ret);
    HAL_FIELD_SET(GLOBAL_CTRL1m, GLOBAL_CTRL1_INTERRUP_POLARITYf, &entry, type);
    CMM_ERR_CHK(HAL_TBL_REG_WRITE(unit, GLOBAL_CTRL1m, 0, sizeof(global_ctrl1_t), &entry), ret);

    return CMM_ERR_OK;
}


yt_ret_t fal_tiger_int_polarity_get(yt_unit_t unit, yt_int_polarity_t *pType)
{
    global_ctrl1_t entry;
    cmm_err_t ret = CMM_ERR_OK;
    uint32_t polarity;

    CMM_ERR_CHK(HAL_TBL_REG_READ(unit, GLOBAL_CTRL1m, 0, sizeof(global_ctrl1_t), &entry), ret);
    HAL_FIELD_GET(GLOBAL_CTRL1m, GLOBAL_CTRL1_INTERRUP_POLARITYf, &entry, &polarity);
    *pType = polarity ? INT_POLAR_HIGH : INT_POLAR_LOW;

    return CMM_ERR_OK;
}

yt_ret_t fal_tiger_int_control_set(yt_unit_t unit, yt_int_type_t type, yt_enable_t enable)
{
    cmm_err_t ret = CMM_ERR_OK;
    intr_mask_t intr_mask;
    uint32_t mask;

    CMM_ERR_CHK(HAL_TBL_REG_READ(unit, INTR_MASKm, 0, sizeof(intr_mask_t), &intr_mask), ret);
    mask = (YT_ENABLE == enable)?1:0;
    HAL_FIELD_SET(INTR_MASKm, INTR_MASK_HW_EXCEPTIONf-type, &intr_mask, mask);
    CMM_ERR_CHK(HAL_TBL_REG_WRITE(unit, INTR_MASKm, 0, sizeof(intr_mask_t), &intr_mask), ret);

    return CMM_ERR_OK;
}

yt_ret_t fal_tiger_int_control_get(yt_unit_t unit, yt_int_type_t type, yt_enable_t *pEnable)
{
    cmm_err_t ret = CMM_ERR_OK;
    uint32_t intr_mask;
    uint32_t mask;

    CMM_ERR_CHK(HAL_TBL_REG_READ(unit, INTR_MASKm, 0, sizeof(intr_mask_t), &intr_mask), ret);
    HAL_FIELD_GET(INTR_MASKm, INTR_MASK_HW_EXCEPTIONf-type, &intr_mask, &mask);
    *pEnable = mask ? YT_ENABLE : YT_DISABLE;

    return CMM_ERR_OK;
}

yt_ret_t fal_tiger_int_status_get(yt_unit_t unit, yt_intr_status_t *pIntStatus)
{
    cmm_err_t ret = CMM_ERR_OK;
    yt_intr_status_t intr_status;
#ifdef PORT_INCLUDED
    yt_port_t port;
    uint16_t tmpData;
#endif

    CMM_ERR_CHK(HAL_TBL_REG_READ(unit, INTR_STATUSm, 0, sizeof(yt_intr_status_t), &intr_status), ret);
    *pIntStatus = intr_status;

#ifdef PORT_INCLUDED
    for(port = 0; port < CAL_PORT_NUM_ON_UNIT(unit); port++)
    {
        /* TODO: clean phy status asynchronously */
        /* read and clean phy interrupt status */
        fal_tiger_port_phy_interruptStatus_get(unit, port, &tmpData);
    }
#endif

    return CMM_ERR_OK;
}


#endif //FAL_TIGER_INTERRUPT_C
