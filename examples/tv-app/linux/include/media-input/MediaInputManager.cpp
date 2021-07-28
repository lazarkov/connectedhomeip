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

#include "MediaInputManager.h"

#include <app/util/af.h>
#include <lib/core/CHIPSafeCasts.h>
#include <map>
#include <string>
#include <support/CodeUtils.h>

#include "../cluster-util/ClusterManager.h"
#include <app/common/gen/attribute-id.h>
#include <app/common/gen/cluster-id.h>

int currentIndex = 0;

CHIP_ERROR MediaInputManager::Init()
{
    CHIP_ERROR err = CHIP_NO_ERROR;

    // TODO: Store feature map once it is supported
    std::map<std::string, bool> featureMap;
    featureMap["NU"] = true;
    SuccessOrExit(err);
exit:
    return err;
}

std::vector<EmberAfMediaInputInfo> MediaInputManager::proxyGetInputList()
{
    std::vector<EmberAfMediaInputInfo> mediaInputList;
    int maximumVectorSize = 4;

    for (int i = 0; i < maximumVectorSize; ++i)
    {
        const char * name       = "HDMI";
        std::string s           = std::to_string(i + 1);
        const char * inputValue = s.c_str();
        unsigned long bufferSize = strlen(name) + strlen(inputValue) + 1;
        char * concatString     = new char[bufferSize];

        // copy strings one and two over to the new buffer:
        strcpy(concatString, name);
        strcat(concatString, inputValue);

        EmberAfMediaInputInfo mediaInput;
        mediaInput.description = chip::ByteSpan(chip::Uint8::from_const_char("TV HDMI Input"), strlen("TV HDMI Input"));
        mediaInput.name        = chip::ByteSpan(chip::Uint8::from_const_char(concatString), strlen(concatString));
        mediaInput.inputType   = EMBER_ZCL_MEDIA_INPUT_TYPE_HDMI;
        mediaInput.index       = static_cast<uint8_t>(1 + i);
        mediaInputList.push_back(mediaInput);
    }

    return mediaInputList;
}

bool mediaInputClusterSelectInput(uint8_t input)
{
    std::system("am start-foreground-service -a android.intent.action.SEND_COMMAND -e data \"{\\\"type\\\": \\\"TV\\\", "
                "\\\"deviceFunction\\\":\\\"HDMI_3\\\"}\"");

    currentIndex = input;
    return true;
}
bool mediaInputClusterShowInputStatus()
{
    EmberAfMediaInputInfo mediaInput;
    ClusterManager().readAttribute(1, ZCL_MEDIA_INPUT_CLUSTER_ID, ZCL_MEDIA_INPUT_LIST_ATTRIBUTE_ID, (uint8_t *) &mediaInput,
                                   currentIndex);
    ChipLogProgress(Zcl, "index: %d", mediaInput.index);
    ChipLogProgress(Zcl, "inputType: %d", mediaInput.inputType);
    ChipLogProgress(Zcl, "name: %.*s", static_cast<int>(mediaInput.name.size()), mediaInput.name.data());
    ChipLogProgress(Zcl, "description: %.*s", static_cast<int>(mediaInput.description.size()), mediaInput.description.data());
    return true;
}
bool mediaInputClusterHideInputStatus()
{
    ChipLogProgress(Zcl, "Status is hidden now!");
    return true;
}
bool mediaInputClusterRenameInput(uint8_t input, std::string name)
{
    EmberAfMediaInputInfo mediaInput;
    mediaInput.description = chip::ByteSpan(chip::Uint8::from_const_char("TV HDMI Input"), strlen("TV HDMI Input"));
    mediaInput.name        = chip::ByteSpan(chip::Uint8::from_const_char(name.c_str()), strlen(name.c_str()));
    mediaInput.inputType   = EMBER_ZCL_MEDIA_INPUT_TYPE_HDMI;
    mediaInput.index       = static_cast<uint8_t>(1 + input);
    ClusterManager().writeAttribute(1, ZCL_MEDIA_INPUT_CLUSTER_ID, ZCL_MEDIA_INPUT_LIST_ATTRIBUTE_ID, (uint8_t *) &mediaInput,
                                    currentIndex);
    return true;
}
