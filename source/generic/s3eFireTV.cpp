/*
Generic implementation of the s3eFireTV extension.
This file should perform any platform-indepedentent functionality
(e.g. error checking) before calling platform-dependent implementations.
*/

/*
 * NOTE: This file was originally written by the extension builder, but will not
 * be overwritten (unless --force is specified) and is intended to be modified.
 */


#include "s3eFireTV_internal.h"
s3eResult s3eFireTVInit()
{
    //Add any generic initialisation code here
    return s3eFireTVInit_platform();
}

void s3eFireTVTerminate()
{
    //Add any generic termination code here
    s3eFireTVTerminate_platform();
}

void s3eFireTV_init()
{
	s3eFireTV_init_platform();
}

void s3eFireTV_startFrame()
{
	s3eFireTV_startFrame_platform();
}

bool s3eFireTV_selectControllerByPlayer(int player)
{
	return s3eFireTV_selectControllerByPlayer_platform(player);
}

bool s3eFireTV_selectControllerByDeviceId(int deviceId)
{
	return s3eFireTV_selectControllerByDeviceId_platform(deviceId);
}

int s3eFireTV_getPlayerCount()
{
	return s3eFireTV_getPlayerCount_platform();
}

int s3eFireTV_getPlayerNumber()
{
	return s3eFireTV_getPlayerNumber_platform();
}

bool s3eFireTV_getButtonState(int button)
{
	return s3eFireTV_getButtonState_platform(button);
}

float s3eFireTV_getAxisValue(int axis)
{
	return s3eFireTV_getAxisValue_platform(axis);
}
