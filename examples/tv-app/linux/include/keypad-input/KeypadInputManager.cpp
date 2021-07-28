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

#include "KeypadInputManager.h"

#include <app/util/af.h>
#include <app/util/basic-types.h>

#include <map>
#include <string>

using namespace std;

CHIP_ERROR KeypadInputManager::Init()
{
    CHIP_ERROR err = CHIP_NO_ERROR;

    // TODO: Store feature map once it is supported
    map<string, bool> featureMap;
    featureMap["NV"] = true;
    featureMap["LK"] = true;
    featureMap["NK"] = true;

    SuccessOrExit(err);
exit:
    return err;
}

EmberAfKeypadInputStatus keypadInputClusterSendKey(EmberAfKeypadInputCecKeyCode keyCode)
{
    switch (keyCode)
    {
    case EMBER_ZCL_KEYPAD_INPUT_CEC_KEY_CODE_SELECT:
        ChipLogProgress(Zcl, "Execute KEY_CODE_SELECT");
        std::system("input keyevent 66");
        break;
    case EMBER_ZCL_KEYPAD_INPUT_CEC_KEY_CODE_UP:
        ChipLogProgress(Zcl, "Execute KEY_CODE_UP");
        std::system("input keyevent 19");
        break;
    case EMBER_ZCL_KEYPAD_INPUT_CEC_KEY_CODE_DOWN:
        ChipLogProgress(Zcl, "Execute KEY_CODE_DOWN");
        std::system("input keyevent 20");
        break;
    case EMBER_ZCL_KEYPAD_INPUT_CEC_KEY_CODE_LEFT:
        ChipLogProgress(Zcl, "Execute KEY_CODE_LEFT");
        std::system("input keyevent 21");
        break;
    case EMBER_ZCL_KEYPAD_INPUT_CEC_KEY_CODE_RIGHT:
        ChipLogProgress(Zcl, "Execute EY_CODE_RIGHT");
        std::system("input keyevent 22");
        break;
    default: {
        //
    }
    }
    return EMBER_ZCL_KEYPAD_INPUT_STATUS_SUCCESS;
}
