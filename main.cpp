#include <fstream>
#include <map>

#define _REALLY_INCLUDE_SYS__SYSTEM_PROPERTIES_H_
#include <sys/_system_properties.h>

void property_override(char const prop[], char const value[], bool add = false) {
    auto pi = (prop_info *) __system_property_find(prop);

    if (pi != nullptr) {
        __system_property_update(pi, value, strlen(value));
    } else if (add) {
        __system_property_add(prop, strlen(prop), value, strlen(value));
    }
}

std::map<std::string, std::string> load_config() {
    std::map<std::string, std::string> config;

    if (std::ifstream file("/system/etc/ih8sn.conf"); file.good()) {
        std::string line;

        while (std::getline(file, line)) {
            if (line[0] == '#') {
                continue;
            }

            if (const auto separator = line.find('='); separator != std::string::npos) {
                config[line.substr(0, separator)] = line.substr(separator + 1);
            }
        }
    }

    return config;
}

int main(int argc, char *argv[]) {
    if (__system_properties_init()) {
        return -1;
    }

    if (argc != 2) {
        return -1;
    }

    const auto is_init_stage = strcmp(argv[1], "init") == 0;
    const auto is_boot_completed_stage = strcmp(argv[1], "boot_completed") == 0;

    const auto config = load_config();
    const auto build_fingerprint = config.find("BUILD_FINGERPRINT");
    const auto build_description = config.find("BUILD_DESCRIPTION");
    const auto build_security_patch_date = config.find("BUILD_SECURITY_PATCH_DATE");
    const auto build_tags = config.find("BUILD_TAGS");
    const auto build_type = config.find("BUILD_TYPE");
    const auto build_version_release = config.find("BUILD_VERSION_RELEASE");
    const auto debuggable = config.find("DEBUGGABLE");
    const auto product_name = config.find("PRODUCT_NAME");
    const auto product_brand = config.find("PRODUCT_BRAND");
    const auto product_device = config.find("PRODUCT_DEVICE");
    const auto build_id = config.find("BUILD_ID");
    const auto version_incremental = config.find("VERSION_INCREMENTAL");
    const auto display_id = config.find("DISPLAY_ID");
    const auto product_manufacturer = config.find("PRODUCT_MANUFACTURER");
    const auto product_model = config.find("PRODUCT_MODEL");
    

    if (is_init_stage && build_fingerprint != config.end()) {
        for (const auto &prop : {
            "ro.bootimage.build.fingerprint",
            "ro.build.fingerprint",
            "ro.odm.build.fingerprint",
            "ro.product.build.fingerprint",
            "ro.system.build.fingerprint",
            "ro.system_ext.build.fingerprint",
            "ro.vendor.build.fingerprint",
            "ro.vendor_dlkm.build.fingerprint",
        }) {
            property_override(prop, build_fingerprint->second.c_str());
        }
    }

    if (is_init_stage && build_tags != config.end()) {
        for (const auto &prop : {
            "ro.bootimage.build.tags",
            "ro.build.tags",
            "ro.odm.build.tags",
            "ro.product.build.tags",
            "ro.system.build.tags",
            "ro.system_ext.build.tags",
            "ro.vendor.build.tags",
            "ro.vendor_dlkm.build.tags",
        }) {
            property_override(prop, build_tags->second.c_str());
        }
    }

    if (is_init_stage && build_type != config.end()) {
        for (const auto &prop : {
            "ro.bootimage.build.type",
            "ro.build.type",
            "ro.odm.build.type",
            "ro.product.build.type",
            "ro.system.build.type",
            "ro.system_ext.build.type",
            "ro.vendor.build.type",
            "ro.vendor_dlkm.build.type",
        }) {
            property_override(prop, build_type->second.c_str());
        }
    }

    if (is_boot_completed_stage && build_version_release != config.end()) {
        for (const auto &prop : {
            "ro.bootimage.build.version.release",
            "ro.build.version.release",
            "ro.odm.build.version.release",
            "ro.product.build.version.release",
            "ro.system.build.version.release",
            "ro.system_ext.build.version.release",
            "ro.vendor.build.version.release",
            "ro.bootimage.build.version.release_or_codename",
            "ro.build.version.release_or_codename",
            "ro.odm.build.version.release_or_codename",
            "ro.product.build.version.release_or_codename",
            "ro.system.build.version.release_or_codename",
            "ro.system_ext.build.version.release_or_codename",
            "ro.vendor.build.version.release_or_codename",
            "ro.vendor_dlkm.build.version.release_or_codename",
        }) {
            property_override(prop, build_version_release->second.c_str());
        }
    }

    if (is_init_stage && build_description != config.end()) {
        property_override("ro.build.description", build_description->second.c_str());
    }

    if (is_boot_completed_stage && build_security_patch_date != config.end()) {
        property_override("ro.build.version.security_patch",
                build_security_patch_date->second.c_str());
    }

    if (is_init_stage && debuggable != config.end()) {
        property_override("ro.debuggable", debuggable->second.c_str());
    }
    
    if (is_init_stage && display_id != config.end()) {
        property_override("ro.build.display.id", display_id->second.c_str());
    }

    if (is_init_stage && product_name != config.end()) {
        for (const auto &prop : {
            "ro.product.name",
            "ro.product.odm.name",
            "ro.product.product.name",
            "ro.product.system.name",
            "ro.product.system_ext.name",
            "ro.product.vendor.name",
            "ro.product.vendor_dlkm.name",
        }) {
            property_override(prop, product_name->second.c_str());
        }
    }
    
    if (is_init_stage && product_brand != config.end()) {
        for (const auto &prop : {
            "ro.product.brand",
            "ro.product.odm.brand",
            "ro.product.product.brand",
            "ro.product.system.brand",
            "ro.product.system_ext.brand",
            "ro.product.vendor.brand",
            "ro.product.vendor_dlkm.brand",
        }) {
            property_override(prop, product_brand->second.c_str());
        }
    }
    
    if (is_init_stage && product_device != config.end()) {
        for (const auto &prop : {
            "ro.product.device",
            "ro.product.odm.device",
            "ro.product.product.device",
            "ro.product.system.device",
            "ro.product.system_ext.device",
            "ro.product.vendor.device",
            "ro.product.vendor_dlkm.device",
        }) {
            property_override(prop, product_device->second.c_str());
        }
    }
    
    if (is_init_stage && build_id != config.end()) {
        for (const auto &prop : {
            "ro.build.id",
            "ro.odm.build.id",
            "ro.product.build.id",
            "ro.system.build.id",
            "ro.system_ext.build.id",
            "ro.vendor.build.id",
            "ro.vendor_dlkm.build.id",
        }) {
            property_override(prop, build_id->second.c_str());
        }
    }
    
    if (is_init_stage && version_incremental != config.end()) {
        for (const auto &prop : {
            "ro.build.version_incremental",
            "ro.odm.build.version_incremental",
            "ro.product.build.version_incremental",
            "ro.system.build.version_incremental",
            "ro.system_ext.build.version_incremental",
            "ro.vendor.build.version_incremental",
            "ro.vendor_dlkm.build.version_incremental",
        }) {
            property_override(prop, version_incremental->second.c_str());
        }
    }
    
    if (is_init_stage && product_manufacturer != config.end()) {
        for (const auto &prop : {
            "ro.product.manufacturer",
            "ro.product.odm.manufacturer",
            "ro.product.product.manufacturer",
            "ro.product.system.manufacturer",
            "ro.product.system_ext.manufacturer",
            "ro.product.vendor.manufacturer",
            "ro.product.vendor_dlkm.manufacturer",
        }) {
            property_override(prop, product_manufacturer->second.c_str());
        }
    }
    
    if (is_init_stage && product_model != config.end()) {
        for (const auto &prop : {
            "ro.product.model",
            "ro.product.odm.model",
            "ro.product.product.model",
            "ro.product.system.model",
            "ro.product.system_ext.model",
            "ro.product.vendor.model",
            "ro.product.vendor_dlkm.model",
        }) {
            property_override(prop, product_model->second.c_str());
        }
    }

    property_override("ro.boot.flash.locked", "1");
    property_override("ro.boot.vbmeta.device_state", "locked");
    property_override("ro.boot.verifiedbootstate", "green");
    property_override("ro.boot.veritymode", "enforcing");
    property_override("ro.boot.warranty_bit", "0");
    property_override("ro.warranty_bit", "0");
    property_override("init.svc.adbd", "stopped");
    property_override("init.svc.adb_root", "stopped");
    property_override("ro.surface_flinger.max_frame_buffer_acquired_buffers", "3");
    return 0;
}
