/* SPDX-License-Identifier: BSD-2-Clause-Patent
 *
 * SPDX-FileCopyrightText: 2016-2020 the prplMesh contributors (see AUTHORS.md)
 *
 * This code is subject to the terms of the BSD+Patent license.
 * See LICENSE file for more details.
 */

#ifndef _CmduMessage_H_
#define _CmduMessage_H_

#include <memory>
#include <tlvf/ClassList.h>
#include <tlvf/ieee_1905_1/cCmduHeader.h>
#include <tlvf/ieee_1905_1/eTlvType.h>
#include <tlvf/tlvflogging.h>

namespace ieee1905_1 {

typedef struct sTlvHeader {
    uint8_t type;
    uint16_t length;
} __attribute__((packed)) sTlvHeader;

class CmduMessage {

public:
    CmduMessage() = delete;
    CmduMessage(uint8_t *buff, size_t buff_len) : msg(buff, buff_len){};
    ~CmduMessage(){};

    std::shared_ptr<cCmduHeader> getCmduHeader() const { return msg.getClass<cCmduHeader>(); };
    static uint16_t getCmduHeaderLength() { return kCmduHeaderLength; }
    eMessageType getMessageType();
    uint16_t getMessageId();
    void setMessageId(uint16_t mid);

    size_t getMessageLength() const { return msg.getMessageLength(); };
    size_t getMessageBuffLength() const { return msg.getMessageBuffLength(); };
    uint8_t *getMessageBuff() const { return msg.getMessageBuff(); };
    template <class T> std::shared_ptr<T> getClass() { return msg.getClass<T>(); }
    void swap() { msg.swap(); };
    bool is_finalized() const { return msg.is_finalized(); };
    bool is_swapped() const { return msg.is_swapped(); };

    static const uint16_t kCmduHeaderLength = 8;
    static const uint16_t kTlvHeaderLength  = 3;

    // Time (in seconds) when the CMDU was received.
    std::chrono::time_point<std::chrono::system_clock> received_time = {};

protected:
    ClassList msg;
};

}; // namespace ieee1905_1

#endif //_CmduMessage_H_
