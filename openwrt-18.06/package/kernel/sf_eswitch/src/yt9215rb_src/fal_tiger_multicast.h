/*******************************************************************************
*                                                                              *
*  Copyright (c), 2022, Motorcomm Electronic Technology Co.,Ltd.               *
*  Motorcomm Confidential and Proprietary.                                     *
*                                                                              *
********************************************************************************
*/
/**
********************************************************************************
* @file fal_tiger_multicast.h
*
* @brief x
*
********************************************************************************
*/
#ifndef __FAL_TIGER_MULTICAST_H
#define __FAL_TIGER_MULTICAST_H

#include "fal_cmm.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define PORT_NUM_INVALID        15
#define ROUTER_PORT_AGING_CNT   5


/**
 * @internal      fal_tiger_multicast_igmp_opmode_set
 * @endinternal
 *
 * @brief         Description
 * @param[in]     unit                -unit id
 * @param[in]     mode                -IGMP/MLD operation mode
 * @retval        CMM_ERR_OK          -on success
 * @retval        CMM_ERR_FAIL        -on fail
 */
extern yt_ret_t  fal_tiger_multicast_igmp_opmode_set(yt_unit_t unit,  yt_multi_op_mode_t mode);


/**
 * @internal      fal_tiger_multicast_igmp_opmode_get
 * @endinternal
 *
 * @brief         Description
 * @param[in]     unit                -unit id
 * @param[out]    pMode               -IGMP/MLD operation mode
 * @retval        CMM_ERR_OK          -on success
 * @retval        CMM_ERR_FAIL        -on fail
 */
extern yt_ret_t  fal_tiger_multicast_igmp_opmode_get(yt_unit_t unit,  yt_multi_op_mode_t *pMode);


/**
 * @internal      fal_tiger_multicast_mld_opmode_set
 * @endinternal
 *
 * @brief         Description
 * @param[in]     unit                -unit id
 * @param[in]     mode                -IGMP/MLD operation mode
 * @retval        CMM_ERR_OK          -on success
 * @retval        CMM_ERR_FAIL        -on fail
 */
extern yt_ret_t  fal_tiger_multicast_mld_opmode_set(yt_unit_t unit,  yt_multi_op_mode_t mode);


/**
 * @internal      fal_tiger_multicast_mld_opmode_get
 * @endinternal
 *
 * @brief         Description
 * @param[in]     unit                -unit id
 * @param[out]    pMode               -IGMP/MLD operation mode
 * @retval        CMM_ERR_OK          -on success
 * @retval        CMM_ERR_FAIL        -on fail
 */
extern yt_ret_t  fal_tiger_multicast_mld_opmode_get(yt_unit_t unit,  yt_multi_op_mode_t *pMode);


/**
 * @internal      fal_tiger_multicast_port_report_allow_set
 * @endinternal
 *
 * @brief         Description
 * @param[in]     unit                -unit id
 * @param[in]     port                -port num
 * @param[in]     enable              -enable or disable
 * @retval        CMM_ERR_OK          -on success
 * @retval        CMM_ERR_FAIL        -on fail
 */
extern yt_ret_t  fal_tiger_multicast_port_report_allow_set(yt_unit_t unit, yt_port_t port, yt_enable_t enable);


/**
 * @internal      fal_tiger_multicast_port_report_allow_get
 * @endinternal
 *
 * @brief         Description
 * @param[in]     unit                -unit id
 * @param[in]     port                -port num
 * @param[out]    pEnable             -enable or not
 * @retval        CMM_ERR_OK          -on success
 * @retval        CMM_ERR_FAIL        -on fail
 */
extern yt_ret_t  fal_tiger_multicast_port_report_allow_get(yt_unit_t unit, yt_port_t port, yt_enable_t *pEnable);


/**
 * @internal      fal_tiger_multicast_port_leave_allow_set
 * @endinternal
 *
 * @brief         Description
 * @param[in]     unit                -unit id
 * @param[in]     port                -port num
 * @param[in]     enable              -enable or disable
 * @retval        CMM_ERR_OK          -on success
 * @retval        CMM_ERR_FAIL        -on fail
 */
extern yt_ret_t  fal_tiger_multicast_port_leave_allow_set(yt_unit_t unit, yt_port_t port, yt_enable_t enable);


/**
 * @internal      fal_tiger_multicast_port_leave_allow_get
 * @endinternal
 *
 * @brief         Description
 * @param[in]     unit                -unit id
 * @param[in]     port                -port num
 * @param[out]    pEnable             -enable or not
 * @retval        CMM_ERR_OK          -on success
 * @retval        CMM_ERR_FAIL        -on fail
 */
extern yt_ret_t  fal_tiger_multicast_port_leave_allow_get(yt_unit_t unit, yt_port_t port, yt_enable_t *pEnable);


/**
 * @internal      fal_tiger_multicast_port_query_allow_set
 * @endinternal
 *
 * @brief         Description
 * @param[in]     unit                -unit id
 * @param[in]     port                -port num
 * @param[in]     enable              -enable or disable
 * @retval        CMM_ERR_OK          -on success
 * @retval        CMM_ERR_FAIL        -on fail
 */
extern yt_ret_t  fal_tiger_multicast_port_query_allow_set(yt_unit_t unit, yt_port_t port, yt_enable_t enable);


/**
 * @internal      fal_tiger_multicast_port_query_allow_get
 * @endinternal
 *
 * @brief         Description
 * @param[in]     unit                -unit id
 * @param[in]     port                -port num
 * @param[out]    pEnable             -enable or not
 * @retval        CMM_ERR_OK          -on success
 * @retval        CMM_ERR_FAIL        -on fail
 */
extern yt_ret_t  fal_tiger_multicast_port_query_allow_get(yt_unit_t unit, yt_port_t port, yt_enable_t *pEnable);


/**
 * @internal      fal_tiger_multicast_fastleave_set
 * @endinternal
 *
 * @brief         Description
 * @param[in]     unit                -unit id
 * @param[in]     enable              -enable or not
 * @retval        CMM_ERR_OK          -on success
 * @retval        CMM_ERR_FAIL        -on fail
 */
extern yt_ret_t  fal_tiger_multicast_fastleave_set(yt_unit_t unit, yt_enable_t enable);


/**
 * @internal      fal_tiger_multicast_fastleave_get
 * @endinternal
 *
 * @brief         Description
 * @param[in]     unit                -unit id
 * @param[out]    pEnable             -enable or not
 * @retval        CMM_ERR_OK          -on success
 * @retval        CMM_ERR_FAIL        -on fail
 */
extern yt_ret_t  fal_tiger_multicast_fastleave_get(yt_unit_t unit, yt_enable_t *pEnable);


/**
 * @internal      fal_tiger_multicast_learnlimit_en_set
 * @endinternal
 *
 * @brief         Description
 * @param[in]     unit                -unit id
 * @param[in]     enable              -enable or not
 * @retval        CMM_ERR_OK          -on success
 * @retval        CMM_ERR_FAIL        -on fail
 */
extern yt_ret_t  fal_tiger_multicast_learnlimit_en_set(yt_unit_t unit, yt_enable_t enable);


/**
 * @internal      fal_tiger_multicast_learnlimit_en_get
 * @endinternal
 *
 * @brief         Description
 * @param[in]     unit                -unit id
 * @param[out]    pEnable             -enable or not
 * @retval        CMM_ERR_OK          -on success
 * @retval        CMM_ERR_FAIL        -on fail
 */
extern yt_ret_t  fal_tiger_multicast_learnlimit_en_get(yt_unit_t unit, yt_enable_t *pEnable);


/**
 * @internal      fal_tiger_multicast_learnlimit_maxgroup_set
 * @endinternal
 *
 * @brief         Description
 * @param[in]     unit                -unit id
 * @param[in]     maxgroup            -x
 * @retval        CMM_ERR_OK          -on success
 * @retval        CMM_ERR_FAIL        -on fail
 */
extern yt_ret_t  fal_tiger_multicast_learnlimit_maxgroup_set(yt_unit_t unit, uint32_t  maxgroup);


/**
 * @internal      fal_tiger_multicast_learnlimit_maxgroup_get
 * @endinternal
 *
 * @brief         Description
 * @param[in]     unit                -unit id
 * @param[out]    pmaxgroup           -x
 * @retval        CMM_ERR_OK          -on success
 * @retval        CMM_ERR_FAIL        -on fail
 */
extern yt_ret_t  fal_tiger_multicast_learnlimit_maxgroup_get(yt_unit_t unit, uint32_t  *pmaxgroup);


/**
 * @internal      fal_tiger_multicast_fwd_routerport_only_set
 * @endinternal
 *
 * @brief         Description
 * @param[in]     unit                -unit id
 * @param[in]     enable              -enable or not
 * @retval        CMM_ERR_OK          -on success
 * @retval        CMM_ERR_FAIL        -on fail
 */
extern yt_ret_t  fal_tiger_multicast_fwd_routerport_only_set(yt_unit_t unit, yt_enable_t enable);


/**
 * @internal      fal_tiger_multicast_fwd_routerport_only_get
 * @endinternal
 *
 * @brief         Description
 * @param[in]     unit                -unit id
 * @param[out]    pEnable             -enable or not
 * @retval        CMM_ERR_OK          -on success
 * @retval        CMM_ERR_FAIL        -on fail
 */
extern yt_ret_t  fal_tiger_multicast_fwd_routerport_only_get(yt_unit_t unit, yt_enable_t *pEnable);


/**
 * @internal      fal_tiger_multicast_fwd_routerport_primary_set
 * @endinternal
 *
 * @brief         Description
 * @param[in]     unit                -unit id
 * @param[in]     enable              -enable or not
 * @retval        CMM_ERR_OK          -on success
 * @retval        CMM_ERR_FAIL        -on fail
 */
extern yt_ret_t  fal_tiger_multicast_fwd_routerport_primary_set(yt_unit_t unit, yt_enable_t enable);


/**
 * @internal      fal_tiger_multicast_fwd_routerport_primary_get
 * @endinternal
 *
 * @brief         Description
 * @param[in]     unit                -unit id
 * @param[out]    pEnable             -enable or not
 * @retval        CMM_ERR_OK          -on success
 * @retval        CMM_ERR_FAIL        -on fail
 */
extern yt_ret_t  fal_tiger_multicast_fwd_routerport_primary_get(yt_unit_t unit, yt_enable_t *pEnable);


/**
 * @internal      fal_tiger_multicast_bypass_grouprange_set
 * @endinternal
 *
 * @brief         Description
 * @param[in]     unit                -unit id
 * @param[in]     bypass              -Multicast IP range that bypass learn
 * @retval        CMM_ERR_OK          -on success
 * @retval        CMM_ERR_FAIL        -on fail
 */
extern yt_ret_t fal_tiger_multicast_bypass_grouprange_set(yt_unit_t unit, yt_multi_learn_bypass_range_t bypass);


/**
 * @internal      fal_tiger_multicast_bypass_grouprange_get
 * @endinternal
 *
 * @brief         Description
 * @param[in]     unit                -unit id
 * @param[out]    pbypass             -Multicast IP range that bypass learn
 * @retval        CMM_ERR_OK          -on success
 * @retval        CMM_ERR_FAIL        -on fail
 */
extern yt_ret_t fal_tiger_multicast_bypass_grouprange_get(yt_unit_t unit, yt_multi_learn_bypass_range_t *pbypass);


/**
 * @internal      fal_tiger_multicast_dynamic_routerport_get
 * @endinternal
 *
 * @brief         Description
 * @param[in]     unit                -unit id
 * @param[out]    prouter_port        -Multicast router port info
 * @retval        CMM_ERR_OK          -on success
 * @retval        CMM_ERR_FAIL        -on fail
 */
extern yt_ret_t  fal_tiger_multicast_dynamic_routerport_get(yt_unit_t unit, yt_multi_router_port_t *prouter_port);


/**
 * @internal      fal_tiger_multicast_routerport_dynamic_allow_set
 * @endinternal
 *
 * @brief         Description
 * @param[in]     unit                -unit id
 * @param[in]     port                -port num
 * @param[in]     enable              -enable or disable
 * @retval        CMM_ERR_OK          -on success
 * @retval        CMM_ERR_FAIL        -on fail
 */
extern yt_ret_t fal_tiger_multicast_routerport_dynamic_allow_set(yt_unit_t unit, yt_port_t port, yt_enable_t enable);


/**
 * @internal      fal_tiger_multicast_routerport_dynamic_allow_get
 * @endinternal
 *
 * @brief         Description
 * @param[in]     unit                -unit id
 * @param[in]     port                -port num
 * @param[out]    pEnable             -enable or not
 * @retval        CMM_ERR_OK          -on success
 * @retval        CMM_ERR_FAIL        -on fail
 */
extern yt_ret_t fal_tiger_multicast_routerport_dynamic_allow_get(yt_unit_t unit, yt_port_t port, yt_enable_t *pEnable);


/**
 * @internal      fal_tiger_multicast_dynamic_routerport_agingtime_set
 * @endinternal
 *
 * @brief         Description
 * @param[in]     unit                -unit id
 * @param[in]     sec                 -x
 * @retval        CMM_ERR_OK          -on success
 * @retval        CMM_ERR_FAIL        -on fail
 */
extern yt_ret_t fal_tiger_multicast_dynamic_routerport_agingtime_set(yt_unit_t unit, uint32_t sec);


/**
 * @internal      fal_tiger_multicast_dynamic_routerport_agingtime_get
 * @endinternal
 *
 * @brief         Description
 * @param[in]     unit                -unit id
 * @param[out]    psec                -x
 * @retval        CMM_ERR_OK          -on success
 * @retval        CMM_ERR_FAIL        -on fail
 */
extern yt_ret_t fal_tiger_multicast_dynamic_routerport_agingtime_get(yt_unit_t unit, uint32_t *psec);


/**
 * @internal      fal_tiger_multicast_vlan_add
 * @endinternal
 *
 * @brief         Description
 * @param[in]     unit                -unit id
 * @param[in]     vid                 -vlan id
 * @retval        CMM_ERR_OK          -on success
 * @retval        CMM_ERR_FAIL        -on fail
 */
extern yt_ret_t fal_tiger_multicast_vlan_add(yt_unit_t unit, yt_vlan_t vid);


/**
 * @internal      fal_tiger_multicast_vlan_get
 * @endinternal
 *
 * @brief         Description
 * @param[in]     unit                -unit id
 * @param[out]    pvlanarray          -multicast vlan info
 * @retval        CMM_ERR_OK          -on success
 * @retval        CMM_ERR_FAIL        -on fail
 */
extern yt_ret_t fal_tiger_multicast_vlan_get(yt_unit_t unit, yt_multi_vlan_t *pvlanarray);


/**
 * @internal      fal_tiger_multicast_vlan_del
 * @endinternal
 *
 * @brief         Description
 * @param[in]     unit                -unit id
 * @param[in]     vid                 -vlan id
 * @retval        CMM_ERR_OK          -on success
 * @retval        CMM_ERR_FAIL        -on fail
 */
extern yt_ret_t fal_tiger_multicast_vlan_del(yt_unit_t unit, yt_vlan_t vid);


/**
 * @internal      fal_tiger_multicast_static_routerport_set
 * @endinternal
 *
 * @brief         Description
 * @param[in]     unit                -unit id
 * @param[in]     port_mask           -yt_types.h
 * @retval        CMM_ERR_OK          -on success
 * @retval        CMM_ERR_FAIL        -on fail
 */
extern yt_ret_t  fal_tiger_multicast_static_routerport_set(yt_unit_t unit, yt_port_mask_t port_mask);


/**
 * @internal      fal_tiger_multicast_static_routerport_get
 * @endinternal
 *
 * @brief         Description
 * @param[in]     unit                -unit id
 * @param[out]    pport_mask          -yt_types.h
 * @retval        CMM_ERR_OK          -on success
 * @retval        CMM_ERR_FAIL        -on fail
 */
extern yt_ret_t  fal_tiger_multicast_static_routerport_get(yt_unit_t unit, yt_port_mask_t *pport_mask);

/**
 * @internal      fal_tiger_multicast_igmp_bypass_port_isolation_set
 * @endinternal
 *
 * @brief         Description
 * @param[in]     unit                -unit id
 * @param[in]     port                -port num
 * @param[in]     enable              -enable or disable
 * @retval        CMM_ERR_OK          -on success
 * @retval        CMM_ERR_FAIL        -on fail
 */
extern yt_ret_t fal_tiger_multicast_igmp_bypass_port_isolation_set(yt_unit_t unit, yt_port_t port, yt_enable_t enable);


/**
 * @internal      fal_tiger_multicast_igmp_bypass_port_isolation_get
 * @endinternal
 *
 * @brief         Description
 * @param[in]     unit                -unit id
 * @param[in]     port                -port num
 * @param[out]    pEnable             -enable or disable
 * @retval        CMM_ERR_OK          -on success
 * @retval        CMM_ERR_FAIL        -on fail
 */
extern yt_ret_t fal_tiger_multicast_igmp_bypass_port_isolation_get(yt_unit_t unit, yt_port_t port, yt_enable_t *pEnable);


/**
 * @internal      fal_tiger_multicast_ipmc_bypass_port_isolation_set
 * @endinternal
 *
 * @brief         Description
 * @param[in]     unit                -unit id
 * @param[in]     enable              -enable or disable
 * @retval        CMM_ERR_OK          -on success
 * @retval        CMM_ERR_FAIL        -on fail
 */
extern yt_ret_t fal_tiger_multicast_ipmc_bypass_port_isolation_set(yt_unit_t unit, yt_enable_t enable);


/**
 * @internal      fal_tiger_multicast_ipmc_bypass_port_isolation_get
 * @endinternal
 *
 * @brief         Description
 * @param[in]     unit                -unit id
 * @param[out]    pEnable             -enable or disable
 * @retval        CMM_ERR_OK          -on success
 * @retval        CMM_ERR_FAIL        -on fail
 */
extern yt_ret_t fal_tiger_multicast_ipmc_bypass_port_isolation_get(yt_unit_t unit, yt_enable_t *pEnable);

/**
 * @internal      fal_tiger_multicast_port_igmp_bypass_ingrfilter_en_set
 * @endinternal
 *
 * @brief         Description
 * @note          APPLICABLE DEVICES  -Tiger
 * @param[in]     unit                -unit id
 * @param[in]     port                -port num
 * @param[in]     enabled             -enable or disable
 * @retval        CMM_ERR_OK          -on success
 * @retval        CMM_ERR_FAIL        -on fail
 */
extern yt_ret_t  fal_tiger_multicast_port_igmp_bypass_ingrfilter_en_set(yt_unit_t unit, yt_port_t port, yt_enable_t enable);


/**
 * @internal      fal_tiger_multicast_port_igmp_bypass_ingrfilter_en_get
 * @endinternal
 *
 * @brief         Description
 * @note          APPLICABLE DEVICES  -Tiger
 * @param[in]     unit                -unit id
 * @param[in]     port                -port num
 * @param[out]    pEnabled            -enable or disable
 * @retval        CMM_ERR_OK          -on success
 * @retval        CMM_ERR_FAIL        -on fail
 */
extern yt_ret_t  fal_tiger_multicast_port_igmp_bypass_ingrfilter_en_get(yt_unit_t unit, yt_port_t port, yt_enable_t *pEnable);



#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif
