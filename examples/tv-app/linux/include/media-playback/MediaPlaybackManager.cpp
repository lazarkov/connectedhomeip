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

#include "MediaPlaybackManager.h"
#include <app/Command.h>
#include <app/util/af.h>
#include <iostream>

#include <map>
#include <string>

using namespace std;

CHIP_ERROR MediaPlaybackManager::Init()
{
    CHIP_ERROR err = CHIP_NO_ERROR;

    // TODO: Store feature map once it is supported
    map<string, bool> featureMap;
    featureMap["AS"] = true;

    SuccessOrExit(err);
exit:
    return err;
}

EmberAfMediaPlaybackStatus MediaPlaybackManager::proxyMediaPlaybackRequest(MediaPlaybackRequest mediaPlaybackRequest,
                                                                           uint64_t deltaPositionMilliseconds)
{
    switch (mediaPlaybackRequest)
    {
    case MEDIA_PLAYBACK_REQUEST_PLAY:
    std::system("input keyevent 85");
    return EMBER_ZCL_MEDIA_PLAYBACK_STATUS_SUCCESS;
    break;
    case MEDIA_PLAYBACK_REQUEST_PAUSE:
    std::system("input keyevent 85");
    return EMBER_ZCL_MEDIA_PLAYBACK_STATUS_SUCCESS;
    break;
    case MEDIA_PLAYBACK_REQUEST_STOP:
    std::system("input keyevent 86");
    return EMBER_ZCL_MEDIA_PLAYBACK_STATUS_SUCCESS;
    break;
    case MEDIA_PLAYBACK_REQUEST_START_OVER:
    // TODO: Insert code here
    case MEDIA_PLAYBACK_REQUEST_PREVIOUS:
    std::system("input keyevent 88");
    return EMBER_ZCL_MEDIA_PLAYBACK_STATUS_SUCCESS;
    break;
    case MEDIA_PLAYBACK_REQUEST_NEXT:
    std::system("input keyevent 87");
    return EMBER_ZCL_MEDIA_PLAYBACK_STATUS_SUCCESS;
    break;
    case MEDIA_PLAYBACK_REQUEST_REWIND:
    std::system("input keyevent 89");
    return EMBER_ZCL_MEDIA_PLAYBACK_STATUS_SUCCESS;
    break;
    case MEDIA_PLAYBACK_REQUEST_FAST_FORWARD:
    std::system("input keyevent 90");
    return EMBER_ZCL_MEDIA_PLAYBACK_STATUS_SUCCESS;
    break;
    case MEDIA_PLAYBACK_REQUEST_SKIP_FORWARD:
    return EMBER_ZCL_MEDIA_PLAYBACK_STATUS_INVALID_STATE_FOR_COMMAND;
    // TODO: Insert code here
    case MEDIA_PLAYBACK_REQUEST_SKIP_BACKWARD:
    return EMBER_ZCL_MEDIA_PLAYBACK_STATUS_INVALID_STATE_FOR_COMMAND;
    // TODO: Insert code here
    case MEDIA_PLAYBACK_REQUEST_SEEK:
        return EMBER_ZCL_MEDIA_PLAYBACK_STATUS_SUCCESS;
        break;
    default: {
        return EMBER_ZCL_MEDIA_PLAYBACK_STATUS_SUCCESS;
    }
    }
}

EmberAfMediaPlaybackStatus mediaPlaybackClusterSendMediaPlaybackRequest(MediaPlaybackRequest mediaPlaybackRequest,
                                                                        uint64_t deltaPositionMilliseconds)
{
    return MediaPlaybackManager().proxyMediaPlaybackRequest(mediaPlaybackRequest, deltaPositionMilliseconds);
}
