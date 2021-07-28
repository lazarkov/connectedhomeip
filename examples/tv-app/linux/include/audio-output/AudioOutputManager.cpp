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

#include "AudioOutputManager.h"

#include <app/util/af.h>
#include <app/util/basic-types.h>
#include <lib/core/CHIPSafeCasts.h>
#include <support/CodeUtils.h>

#include <map>
#include <string>

#include "../cluster-util/ClusterManager.h"
#include <app/common/gen/attribute-id.h>
#include <app/common/gen/cluster-id.h>

using namespace std;

int currentAudioOutputIndex = 0;

CHIP_ERROR AudioOutputManager::Init()
{
    CHIP_ERROR err = CHIP_NO_ERROR;

    // TODO: Store feature map once it is supported
    map<string, bool> featureMap;
    featureMap["NU"] = true;

    return err;
}

vector<EmberAfAudioOutputInfo> AudioOutputManager::proxyGetListOfAudioOutputInfo()
{
    // TODO: Insert code here
    vector<EmberAfAudioOutputInfo> audioOutputInfos;
    int maximumVectorSize = 3;

    for (int i = 0; i < maximumVectorSize; ++i)
    {
        const char * name       = "Audio";
        std::string s           = std::to_string(i + 1);
        const char * audioOutputIndexValue = s.c_str();
        unsigned long bufferSize = strlen(name) + strlen(audioOutputIndexValue) + 1;
        char * concatString     = new char[bufferSize];

        // copy strings one and two over to the new buffer:
        strcpy(concatString, name);
        strcat(concatString, audioOutputIndexValue);

        EmberAfAudioOutputInfo audioOutputInfo;
        audioOutputInfo.outputType = EMBER_ZCL_AUDIO_OUTPUT_TYPE_HDMI;
        audioOutputInfo.name       = chip::ByteSpan(chip::Uint8::from_const_char(concatString), strlen(concatString));
        audioOutputInfo.index      = static_cast<uint8_t>(1 + i);
        audioOutputInfos.push_back(audioOutputInfo);
    }

    return audioOutputInfos;
}

bool audioOutputClusterSelectOutput(uint8_t index)
{
    EmberAfAudioOutputInfo audioOutputInfo;
    ClusterManager().readAttribute(2, ZCL_AUDIO_OUTPUT_CLUSTER_ID, ZCL_AUDIO_OUTPUT_LIST_ATTRIBUTE_ID, (uint8_t *) &audioOutputInfo,
                                   index);
    ChipLogProgress(Zcl, "index: %d", audioOutputInfo.index);
    ChipLogProgress(Zcl, "outputType: %d", audioOutputInfo.outputType);
    ChipLogProgress(Zcl, "name: %.*s", static_cast<int>(audioOutputInfo.name.size()), audioOutputInfo.name.data());
    currentAudioOutputIndex = index;
    return true;
}

bool audioOutputClusterRenameOutput(uint8_t index, string name)
{
    EmberAfAudioOutputInfo audioOutputInfo;
    audioOutputInfo.outputType = EMBER_ZCL_AUDIO_OUTPUT_TYPE_HDMI;
    audioOutputInfo.name       = chip::ByteSpan(chip::Uint8::from_const_char(name.c_str()), strlen(name.c_str()));
    audioOutputInfo.index      = index;
    ClusterManager().writeAttribute(2, ZCL_AUDIO_OUTPUT_CLUSTER_ID, ZCL_AUDIO_OUTPUT_LIST_ATTRIBUTE_ID, (uint8_t *) &audioOutputInfo,
                                    index);
    return true;
}
