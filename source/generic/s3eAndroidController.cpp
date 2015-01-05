/*
Generic implementation of the s3eAndroidController extension.
This file should perform any platform-indepedentent functionality
(e.g. error checking) before calling platform-dependent implementations.
*/

/*
 * NOTE: This file was originally written by the extension builder, but will not
 * be overwritten (unless --force is specified) and is intended to be modified.
 */
#include <string.h>

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
    const char* const buttons[] = { "A", "B", "DPadCenter", "DPadDown", "DPadLeft", "DPadRight", "DPadUp",
                                    "ShoulderLeft", "ShoulderRight", "StickLeft", "StickRight",
                                    "TriggerLeft", "TriggerRight", "X", "Y" };
    const char* name;
    switch (button)
    {
        case S3E_ANDROID_CONTROLLER_BUTTON_A:
            name = buttons[0];
            break;
        case S3E_ANDROID_CONTROLLER_BUTTON_B:
            name = buttons[1];
            break;
        case S3E_ANDROID_CONTROLLER_BUTTON_DPAD_CENTER:
            name = buttons[2];
            break;
        case S3E_ANDROID_CONTROLLER_BUTTON_DPAD_DOWN:
            name = buttons[3];
            break;
        case S3E_ANDROID_CONTROLLER_BUTTON_DPAD_LEFT:
            name = buttons[4];
            break;
        case S3E_ANDROID_CONTROLLER_BUTTON_DPAD_RIGHT:
            name = buttons[5];
            break;
        case S3E_ANDROID_CONTROLLER_BUTTON_DPAD_UP:
            name = buttons[6];
            break;
        case S3E_ANDROID_CONTROLLER_BUTTON_SHOULDER_LEFT:
            name = buttons[7];
            break;
        case S3E_ANDROID_CONTROLLER_BUTTON_SHOULDER_RIGHT:
            name = buttons[8];
            break;
        case S3E_ANDROID_CONTROLLER_BUTTON_STICK_LEFT:
            name = buttons[9];
            break;
        case S3E_ANDROID_CONTROLLER_BUTTON_STICK_RIGHT:
            name = buttons[10];
            break;
        case S3E_ANDROID_CONTROLLER_BUTTON_TRIGGER_LEFT:
            name = buttons[11];
            break;
        case S3E_ANDROID_CONTROLLER_BUTTON_TRIGGER_RIGHT:
            name = buttons[12];
            break;
        case S3E_ANDROID_CONTROLLER_BUTTON_X:
            name = buttons[13];
            break;
        case S3E_ANDROID_CONTROLLER_BUTTON_Y:
            name = buttons[14];
            break;
        default:
            return S3E_RESULT_ERROR;
    }
    
    int length = strlen(name);
    if (terminateString)
        length += 1;
    
    strncpy(dst, name, length);
    
	return S3E_RESULT_SUCCESS;
}

s3eResult s3eAndroidControllerGetAxisDisplayName(char* dst, int axis, s3eBool terminateString)
{
    const char* const axes[] = { "StickLeftX", "StickLeftY", "StickRightX", "StickRightX", "TriggerLeft", "TriggerRight" };
    const char* name;
    switch (axis)
    {
        case S3E_ANDROID_CONTROLLER_AXIS_STICK_LEFT_X:
            name = axes[0];
            break;
        case S3E_ANDROID_CONTROLLER_AXIS_STICK_LEFT_Y:
            name = axes[1];
            break;
        case S3E_ANDROID_CONTROLLER_AXIS_STICK_RIGHT_X:
            name = axes[2];
            break;
        case S3E_ANDROID_CONTROLLER_AXIS_STICK_RIGHT_Y:
            name = axes[3];
            break;
        case S3E_ANDROID_CONTROLLER_AXIS_TRIGGER_LEFT:
            name = axes[4];
            break;
        case S3E_ANDROID_CONTROLLER_AXIS_TRIGGER_RIGHT:
            name = axes[5];
            break;
        default:
            return S3E_RESULT_ERROR;
    }
    
    int length = strlen(name);
    if (terminateString)
        length += 1;
    
    strncpy(dst, name, length);
    
	return S3E_RESULT_SUCCESS;
}
