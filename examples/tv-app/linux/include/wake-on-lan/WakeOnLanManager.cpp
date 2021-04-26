/*
 *
 *    Copyright (c) 2021 Project CHIP Authors
 *    All rights reserved.
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */

#include "WakeOnLanManager.h"

#include "gen/attribute-id.h"
#include "gen/attribute-type.h"
#include "gen/cluster-id.h"
#include "gen/command-id.h"

#include <app/util/af.h>
#include <app/util/basic-types.h>

#include <inipp/inipp.h>

#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;

CHIP_ERROR WakeOnLanManager::Init()
{
    CHIP_ERROR err = CHIP_NO_ERROR;

    return err;
}

std::string getMacAddress()
{
    std::ifstream input("/sys/class/net/eth0/address");
    std::string line;
    std::getline(input, line);
    return line;
}

void WakeOnLanManager::store(chip::EndpointId endpoint)
{
    std::string macAddress = "H" + getMacAddress();
    ChipLogProgress(Zcl, "mac address: %s, endpoint: %d", macAddress.c_str(), endpoint);
    EmberAfStatus macAddressStatus =
        emberAfWriteServerAttribute(endpoint, ZCL_WAKE_ON_LAN_CLUSTER_ID, ZCL_WAKE_ON_LAN_MAC_ADDRESS_ATTRIBUTE_ID, (uint8_t *) &s,
                                    ZCL_CHAR_STRING_ATTRIBUTE_TYPE);
    assert(macAddressStatus == EMBER_ZCL_STATUS_SUCCESS);
}