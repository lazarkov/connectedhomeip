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

#include "ApplicationLauncherManager.h"
#include <app/clusters/application-launcher-server/application-launcher-server.h>
#include <app/util/af.h>
#include <app/util/basic-types.h>

using namespace std;

vector<uint16_t> applications;

CHIP_ERROR ApplicationLauncherManager::Init()
{
    CHIP_ERROR err = CHIP_NO_ERROR;
    SuccessOrExit(err);
exit:
    return err;
}

void launchApp(uint16_t catalogId)
{
    if (catalogId == 22163)
    {
        std::system("am start -n com.amazon.tv.legal.notices/.AlexaLegalTermsActivity");
    }
    else if (catalogId == 48462)
    {
        std::system("am start -n com.amazon.tv.legal.notices/.LegalAndComplianceActivity");
    }
    else if (catalogId == 72)
    {
        std::system("am start -a com.amazon.device.settings.action.LANGUAGE");
    }
    else if (catalogId == 38095)
    {
        std::system(
            "am start "
            "com.amazon.tv.devicecontrolsettings/com.amazon.tv.devicecontrolsettings.screens.main_menu.OzOobeSettingsActivity");
    }
}

vector<uint16_t> ApplicationLauncherManager::proxyGetApplicationList()
{
    applications.push_back(22163);
    applications.push_back(48462);
    applications.push_back(72);
    applications.push_back(38095);
    return applications;
}

ApplicationLauncherResponse applicationLauncherClusterLaunchApp(EmberAfApplicationLauncherApp application, std::string data)
{
    bool appFound     = false;
    size_t vectorSize = applications.size();
    for (size_t i = 0; i < vectorSize; ++i)
    {
        if (application.catalogVendorId == applications[i])
        {
            appFound = true;
        }
    }
    ApplicationLauncherResponse response;

    if (appFound)
    {
        launchApp(application.catalogVendorId);
        const char * testData = "data";
        response.data         = (uint8_t *) testData;
        response.status       = EMBER_ZCL_APPLICATION_LAUNCHER_STATUS_SUCCESS;
    }
    else
    {
        const char * testData = "data";
        response.data         = (uint8_t *) testData;
        response.status       = EMBER_ZCL_APPLICATION_LAUNCHER_STATUS_APP_NOT_AVAILABLE;
    }

    return response;
}
