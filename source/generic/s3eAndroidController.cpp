/*
Generic implementation of the s3eAndroidController extension.
This file should perform any platform-indepedentent functionality
(e.g. error checking) before calling platform-dependent implementations.
*/

/*
 * NOTE: This file was originally written by the extension builder, but will not
 * be overwritten (unless --force is specified) and is intended to be modified.
 */


#include "s3eAndroidController_internal.h"
s3eResult s3eAndroidControllerInit()
{
    //Add any generic initialisation code here
    return s3eAndroidControllerInit_platform();
}

void s3eAndroidControllerTerminate()
{
    //Add any generic termination code here
    s3eAndroidControllerTerminate_platform();
}

void s3eAndroidControllerStartFrame()
{
	s3eAndroidControllerStartFrame_platform();
}

bool s3eAndroidControllerSelectControllerByPlayer(int player)
{
	return s3eAndroidControllerSelectControllerByPlayer_platform(player);
}

int s3eAndroidControllerGetPlayerCount()
{
	return s3eAndroidControllerGetPlayerCount_platform();
}

bool s3eAndroidControllerGetButtonState(int button)
{
	return s3eAndroidControllerGetButtonState_platform(button);
}

float s3eAndroidControllerGetAxisValue(int axis)
{
	return s3eAndroidControllerGetAxisValue_platform(axis);
}

s3eResult s3eAndroidControllerGetButtonDisplayName(char* dst, int button, s3eBool terminateString)
{
	return s3eAndroidControllerGetButtonDisplayName_platform(dst, button, terminateString);
}

s3eResult s3eAndroidControllerGetAxisDisplayName(char* dst, int axis, s3eBool terminateString)
{
	return s3eAndroidControllerGetAxisDisplayName_platform(dst, axis, terminateString);
}

void s3eAndroidControllerSetPropagateButtonsToKeyboard(bool propagate)
{
	s3eAndroidControllerSetPropagateButtonsToKeyboard_platform(propagate);
}

bool s3eAndroidControllerGetPropagateButtonsToKeyboard()
{
	return s3eAndroidControllerGetPropagateButtonsToKeyboard_platform();
}

bool s3eAndroidControllerIsTypeSupported(s3eAndroidControllerType type)
{
	return s3eAndroidControllerIsTypeSupported_platform(type);
}

s3eResult s3eAndroidControllerSetType(s3eAndroidControllerType type)
{
	return s3eAndroidControllerSetType_platform(type);
}

s3eAndroidControllerType s3eAndroidControllerGetType()
{
	return s3eAndroidControllerGetType_platform();
}
