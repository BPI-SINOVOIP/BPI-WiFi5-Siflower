/* SPDX-License-Identifier: BSD-2-Clause-Patent
 *
 * SPDX-FileCopyrightText: 2016-2020 the prplMesh contributors (see AUTHORS.md)
 *
 * This code is subject to the terms of the BSD+Patent license.
 * See LICENSE file for more details.
 */

#ifndef _BEEROCKS_MESSAGE_STRUCTS_H_
#define _BEEROCKS_MESSAGE_STRUCTS_H_

#include "beerocks_defines.h"
#include "network/net_struct.h"
#include "network/swap.h"

namespace beerocks {
namespace message {

typedef struct {
    uint32_t if_index = 0; // index of the network interface the message was received on
    uint8_t dst_bridge_mac[net::MAC_ADDR_LEN] = {};
    uint8_t src_bridge_mac[net::MAC_ADDR_LEN] = {};
    uint16_t length                           = 0;
} __attribute__((packed)) sUdsHeader;

//////////////////// tlvf includes /////////////////////////////

// Note:
// 1. Only structs which are needed for BCL should be defined here instead in a YAML file.
// 2. If you decided to add here a struct, make sure it has a construcor and swap function.
//    TIP: The best way to do it is to create the the struct in a yaml file temporary (beerocks_message_common.yaml),
//         and copy the auto generated struct to here.

// used in bcl on "son_wireless_utils.h"
typedef struct sRadioCapabilities {
    uint8_t ht_mcs                = 0; //beerocks::eWiFiMCS RX
    uint8_t vht_mcs               = 0; //beerocks::eWiFiMCS RX
    uint8_t ht_ss                 = 0; //beerocks::eWiFiSS RX
    uint8_t vht_ss                = 0; //beerocks::eWiFiSS RX
    uint8_t ht_bw                 = 0; //beerocks::eWiFiBandwidth
    uint8_t vht_bw                = 0; //beerocks::eWiFiBandwidth
    uint8_t ht_low_bw_short_gi    = 0; //20 Mhz
    uint8_t ht_high_bw_short_gi   = 0; //40 Mhz
    uint8_t vht_low_bw_short_gi   = 0; //80 Mhz
    uint8_t vht_high_bw_short_gi  = 0; //160 Mhz
    uint8_t ht_sm_power_save      = 0; //beerocks::eHtCapsSmPowerSaveMode
    uint8_t ant_num               = 0;
    uint8_t wifi_standard         = 0;
    uint8_t default_short_gi      = 0;
    uint8_t default_mcs           = 0;
    uint8_t btm_supported         = 0;
    uint8_t nr_enabled            = 0;
    uint8_t cell_capa             = 0;
    uint8_t valid                 = 0;
    uint8_t rrm_supported         = 0;
    uint8_t band_2g_capable       = 0;
    uint8_t band_5g_capable       = 0;
    uint8_t max_ch_width          = 0; //beerocks::eWiFiBandwidth
    uint8_t phy_mode              = 0;
    uint8_t max_mcs               = 0;
    uint8_t max_tx_power          = 0;
    uint8_t link_meas             = 0;
    uint8_t beacon_report_passive = 0;
    uint8_t beacon_report_active  = 0;
    uint8_t beacon_report_table   = 0;
    uint8_t lci_meas              = 0;
    uint8_t fmt_range_report      = 0;
    uint8_t mumimo_supported      = 0;
    uint8_t max_streams           = 0;
    uint8_t vht_su_beamformer     = 0;
    uint8_t vht_mu_beamformer     = 0;
    sRadioCapabilities() {}
    void struct_swap() {}
    void struct_init()
    {
        ht_mcs               = 0;
        vht_mcs              = 0;
        ht_ss                = 0;
        vht_ss               = 0;
        ht_bw                = 0;
        vht_bw               = 0;
        ht_low_bw_short_gi   = 0;
        ht_high_bw_short_gi  = 0;
        vht_low_bw_short_gi  = 0;
        vht_high_bw_short_gi = 0;
        ht_sm_power_save     = 0;
        ant_num              = 0;
        wifi_standard        = 0;
        default_short_gi     = 0;
        default_mcs          = 0;
        btm_supported        = 0;
        nr_enabled           = 0;
        cell_capa            = 0;
        valid                = 0;
    }
} __attribute__((packed)) sRadioCapabilities;

typedef struct sWifiChannel {
    uint8_t channel           = 0;
    int8_t noise              = 0;
    uint8_t tx_pow            = 0;
    uint8_t bss_overlap       = 0;
    uint8_t channel_bandwidth = 0;
    uint8_t is_dfs_channel    = 0;
    uint8_t radar_affected    = 0;
    int32_t rank              = -1;
    eDfsState dfs_state       = DFS_STATE_MAX;
    sWifiChannel(){};
    sWifiChannel(uint8_t _channel, uint8_t _channel_bandwidth)
        : channel(_channel), channel_bandwidth(_channel_bandwidth)
    {
    }
    void struct_swap() {}
    void struct_init()
    {
        channel           = 0;
        noise             = 0;
        tx_pow            = 0;
        bss_overlap       = 0;
        channel_bandwidth = 0;
        is_dfs_channel    = 0;
        radar_affected    = 0;
        rank              = -1;
        dfs_state         = DFS_STATE_MAX;
    }
} __attribute__((packed)) sWifiChannel;

//////////////////// tlvf includes - END/////////////////////////////

} // namespace message
} // namespace beerocks

#endif
