/*
 * Internal header for the s3eAndroidController extension.
 *
 * This file should be used for any common function definitions etc that need to
 * be shared between the platform-dependent and platform-indepdendent parts of
 * this extension.
 */

/*
 * NOTE: This file was originally written by the extension builder, but will not
 * be overwritten (unless --force is specified) and is intended to be modified.
 */


#ifndef S3EANDROIDCONTROLLER_INTERNAL_H
#define S3EANDROIDCONTROLLER_INTERNAL_H

#include "s3eTypes.h"
#include "s3eAndroidController.h"
#include "s3eAndroidController_autodefs.h"


/**
 * Initialise the extension.  This is called once then the extension is first
 * accessed by s3eregister.  If this function returns S3E_RESULT_ERROR the
 * extension will be reported as not-existing on the device.
 */
s3eResult s3eAndroidControllerInit();

/**
 * Platform-specific initialisation, implemented on each platform
 */
s3eResult s3eAndroidControllerInit_platform();

/**
 * Terminate the extension.  This is called once on shutdown, but only if the
 * extension was loader and Init() was successful.
 */
void s3eAndroidControllerTerminate();

/**
 * Platform-specific termination, implemented on each platform
 */
void s3eAndroidControllerTerminate_platform();
void s3eAndroidControllerStartFrame_platform();

bool s3eAndroidControllerSelectControllerByPlayer_platform(int player);

int s3eAndroidControllerGetPlayerCount_platform();

bool s3eAndroidControllerGetButtonState_platform(int button);

float s3eAndroidControllerGetAxisValue_platform(int axis);

s3eResult s3eAndroidControllerGetButtonDisplayName_platform(char* dst, int button, s3eBool terminateString);

s3eResult s3eAndroidControllerGetAxisDisplayName_platform(char* dst, int axis, s3eBool terminateString);

void s3eAndroidControllerSetPropagateButtonsToKeyboard_platform(bool propagate);

bool s3eAndroidControllerGetPropagateButtonsToKeyboard_platform();

bool s3eAndroidControllerIsTypeSupported_platform(s3eAndroidControllerType type);

s3eResult s3eAndroidControllerSetType_platform(s3eAndroidControllerType type);

s3eAndroidControllerType s3eAndroidControllerGetType_platform();


#endif /* !S3EANDROIDCONTROLLER_INTERNAL_H */