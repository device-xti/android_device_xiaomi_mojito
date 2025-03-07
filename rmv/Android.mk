LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := rmv
LOCAL_MODULE_CLASS := APPS
LOCAL_MODULE_TAGS := optional
LOCAL_OVERRIDES_PACKAGES := \
    Drive \
    Maps \
    NexusLauncherRelease \
    org.lineageos.aperture \
    Aperture \
    RCS \
    GoogleFeedback \
    arcore \
    MarkupGoogle \
    AndroidAutoStubPrebuilt \
    PartnerSetupPrebuilt \
    PixelThemesStub \
    PixelThemesStub2022_and_newer \
    MaestroPrebuilt \
    SecurityHubPrebuilt \
    KidsSupervisionStub \
    BetterBugStub \
    RecorderPrebuilt \
    SafetyHubPrebuilt \
    Videos \
    YouTube
LOCAL_UNINSTALLABLE_MODULE := true
LOCAL_CERTIFICATE := PRESIGNED
LOCAL_SRC_FILES := /dev/null
include $(BUILD_PREBUILT)
