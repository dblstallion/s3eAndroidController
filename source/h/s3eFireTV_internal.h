/*
 * Internal header for the s3eFireTV extension.
 *
 * This file should be used for any common function definitions etc that need to
 * be shared between the platform-dependent and platform-indepdendent parts of
 * this extension.
 */

/*
 * NOTE: This file was originally written by the extension builder, but will not
 * be overwritten (unless --force is specified) and is intended to be modified.
 */


#ifndef S3EFIRETV_INTERNAL_H
#define S3EFIRETV_INTERNAL_H

#include "s3eTypes.h"
#include "s3eFireTV.h"
#include "s3eFireTV_autodefs.h"


/**
 * Initialise the extension.  This is called once then the extension is first
 * accessed by s3eregister.  If this function returns S3E_RESULT_ERROR the
 * extension will be reported as not-existing on the device.
 */
s3eResult s3eFireTVInit();

/**
 * Platform-specific initialisation, implemented on each platform
 */
s3eResult s3eFireTVInit_platform();

/**
 * Terminate the extension.  This is called once on shutdown, but only if the
 * extension was loader and Init() was successful.
 */
void s3eFireTVTerminate();

/**
 * Platform-specific termination, implemented on each platform
 */
void s3eFireTVTerminate_platform();
void s3eFireTV_init_platform();

void s3eFireTV_startFrame_platform();

bool s3eFireTV_selectControllerByPlayer_platform(int player);

bool s3eFireTV_selectControllerByDeviceId_platform(int deviceId);

int s3eFireTV_getPlayerCount_platform();

int s3eFireTV_getPlayerNumber_platform();

bool s3eFireTV_getButtonState_platform(int button);

float s3eFireTV_getAxisValue_platform(int axis);


#endif /* !S3EFIRETV_INTERNAL_H */