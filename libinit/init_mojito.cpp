/*
 * Copyright (C) 2022 PixelExperience
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <vector>

#include <android-base/logging.h>
#include <android-base/properties.h>
#define _REALLY_INCLUDE_SYS__SYSTEM_PROPERTIES_H_
#include <sys/_system_properties.h>
#include <sys/sysinfo.h>

using android::base::GetProperty;
using std::string;

void property_override(string prop, string value) {
    auto pi = (prop_info*) __system_property_find(prop.c_str());

    if (pi != nullptr)
        __system_property_update(pi, value.c_str(), value.size());
    else
        __system_property_add(prop.c_str(), prop.size(), value.c_str(), value.size());
}

void load_dalvikvm_props() {
    struct sysinfo sys;
    sysinfo(&sys);

    if (sys.totalram > 5072ull * 1024 * 1024) {
        // from - phone-xhdpi-6144-dalvik-heap.mk
        property_override("dalvik.vm.heapstartsize", "16m");
        property_override("dalvik.vm.heapgrowthlimit", "256m");
        property_override("dalvik.vm.heaptargetutilization", "0.5");
        property_override("dalvik.vm.heapmaxfree", "32m");
    } else if (sys.totalram > 3072ull * 1024 * 1024) {
        // from - phone-xhdpi-4096-dalvik-heap.mk
        property_override("dalvik.vm.heapstartsize", "8m");
        property_override("dalvik.vm.heapgrowthlimit", "192m");
        property_override("dalvik.vm.heaptargetutilization", "0.6");
        property_override("dalvik.vm.heapmaxfree", "16m");
    }

    property_override("dalvik.vm.heapsize", "512m");
    property_override("dalvik.vm.heapminfree", "8m");
}

void load_vendor_props() {
    string device, fingerprint, model, name;

    string hwname = GetProperty("ro.boot.hwname", "");
    if (hwname.find("sunny") != std::string::npos) {
        device = "sunny";
        fingerprint = "Redmi/sunny_global/sunny:12/RKQ1.210614.002/V14.0.9.0.SKGMIXM:user/release-keys";
        model = "M2101K7AG";
        name = "sunny_global";
    } else {
        device = "mojito";
        fingerprint = "Redmi/mojito/mojito:12/RKQ1.210614.002/V14.0.9.0.SKGMIXM:user/release-keys";
        model = "Redmi Note 10";
        name = "mojito";
    }

    string prop_partitions[] = { "", "odm.", "product.", "system.",
					"system_ext.", "vendor.", "vendor_dlkm." };

    for (const string &prop : prop_partitions) {
        property_override(string("ro.product.") + prop + string("device"), device);
        property_override(string("ro.") + prop + string("build.fingerprint"), fingerprint);
        property_override(string("ro.product.") + prop + string("model"), model);
        property_override(string("ro.product.") + prop + string("name"), name);
    }

    if (hwname.find("sunny") != std::string::npos) {
        property_override("ro.build.description", "sunny_global-user 12 RKQ1.210614.002 V14.0.9.0.SKGMIXM release-keys");
    } else {
        property_override("ro.build.description", "mojito-user 12 RKQ1.210614.002 V14.0.9.0.SKGMIXM release-keys");
    }

    property_override("bluetooth.device.default_name", "Redmi Note 10");
    property_override("vendor.usb.product_string", "Redmi Note 10");
}

void vendor_load_properties() {
    if (access("/system/bin/recovery", F_OK) != 0) {
        load_vendor_props();
    }
    load_dalvikvm_props();
}
