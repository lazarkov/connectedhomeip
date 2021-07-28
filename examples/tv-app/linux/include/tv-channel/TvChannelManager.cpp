/**
 *
 *    Copyright (c) 2021 Project CHIP Authors
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

#include "TvChannelManager.h"
#include <app/util/af.h>
#include <app/util/attribute-storage.h>
#include <lib/core/CHIPSafeCasts.h>
#include <support/CodeUtils.h>
#include <support/logging/CHIPLogging.h>

#include <map>
#include <string>
#include <vector>

using namespace chip;

int currentChannel = 0;

CHIP_ERROR TvChannelManager::Init()
{
    CHIP_ERROR err = CHIP_NO_ERROR;
    // TODO: Store feature map once it is supported
    std::map<std::string, bool> featureMap;
    featureMap["CL"] = true;
    featureMap["LI"] = true;

    SuccessOrExit(err);
exit:
    return err;
}

std::vector<EmberAfTvChannelInfo> TvChannelManager::proxyGetTvChannelList()
{
    // TODO: Insert code here
    std::vector<EmberAfTvChannelInfo> tvChannels;
    int maximumVectorSize = 5;

    for (int i = 0; i < maximumVectorSize; ++i)
    {
        EmberAfTvChannelInfo channelInfo;
        channelInfo.affiliateCallSign = ByteSpan(chip::Uint8::from_const_char("exampleASign"), strlen("exampleASign"));
        channelInfo.callSign          = ByteSpan(chip::Uint8::from_const_char("exampleCSign"), strlen("exampleCSign"));
        channelInfo.name              = ByteSpan(chip::Uint8::from_const_char("exampleName"), strlen("exampleName"));
        channelInfo.majorNumber       = static_cast<uint8_t>(1 + i);
        channelInfo.minorNumber       = static_cast<uint16_t>(0);
        tvChannels.push_back(channelInfo);
    }

    return tvChannels;
}

EmberAfTvChannelInfo tvChannelClusterChangeChannel(std::string match)
{
    // TODO: Insert code here
    EmberAfTvChannelInfo channel = {};
    return channel;
}

void blastNumber(int number)
{
    switch (number)
    {
    case 0:
        ChipLogProgress(Zcl, "Execute Channel 0");
        std::system("input keyevent 7");
        break;
    case 1:
        ChipLogProgress(Zcl, "Execute Channel 1");
        std::system("input keyevent 8");
        break;
    case 2:
        ChipLogProgress(Zcl, "Execute Channel 2");
        std::system("input keyevent 9");
        break;
    case 3:
        ChipLogProgress(Zcl, "Execute Channel 3");
        std::system("input keyevent 10");
        break;
    case 4:
        ChipLogProgress(Zcl, "Execute Channel 4");
        std::system("input keyevent 11");
        break;
    case 5:
        ChipLogProgress(Zcl, "Execute Channel 5");
        std::system("input keyevent 12");
        break;
    case 6:
        ChipLogProgress(Zcl, "Execute Channel 6");
        std::system("input keyevent 13");
        break;
    case 7:
        ChipLogProgress(Zcl, "Execute Channel 7");
        std::system("input keyevent 14");
        break;
    case 8:
        ChipLogProgress(Zcl, "Execute Channel 8");
        std::system("input keyevent 15");
        break;
    case 9:
        ChipLogProgress(Zcl, "Execute Channel 9");
        std::system("input keyevent 16");
        break;
    default: {
        //
    }
    }
}

bool tvChannelClusterChangeChannelByNumber(uint16_t majorNumber, uint16_t minorNumber)
{
    if (minorNumber > 0 || majorNumber > 1000 || majorNumber < 0)
    {
        return false;
    }
    else
    {
        int channelArray[10];
        int index = 0;
        while (majorNumber > 0)
        {
            int digit = majorNumber % 10;
            majorNumber /= 10;
            channelArray[index] = digit;
            index++;
        }

        for (int j = index; j >= 0; j--)
        {
            blastNumber(channelArray[j]);
        }
    }
    return true;
}

bool tvChannelClusterSkipChannel(uint16_t count)
{
    int newChannel = (count + currentChannel) % 5;
    currentChannel = newChannel;
    blastNumber(currentChannel);
    return true;
}