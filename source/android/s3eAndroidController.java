/*
java implementation of the s3eAndroidController extension.

Add android-specific functionality here.

These functions are called via JNI from native code.
*/
/*
 * NOTE: This file was originally written by the extension builder, but will not
 * be overwritten (unless --force is specified) and is intended to be modified.
 */

package com.nickchops.s3eAndroidController;

import java.util.HashMap;
import android.os.Build;
import android.os.Bundle;
import android.util.Log;
import android.view.KeyEvent;
import android.view.MotionEvent;
import com.amazon.device.gamecontroller.GameController;
import com.amazon.device.gamecontroller.GameController.DeviceNotFoundException;
import com.amazon.device.gamecontroller.GameController.PlayerNumberNotFoundException;
import com.ideaworks3d.marmalade.LoaderAPI;
import com.ideaworks3d.marmalade.LoaderActivity;
//import android.hardware.input.InputManager;
//import android.content.Context;

public class s3eAndroidController
{
	GameController m_SelectedController = null;
    
    public static HashMap<Integer, Boolean> s_keyStates;
    public static float s_axisStickLeftX;
    public static float s_axisStickLeftY;
    public static float s_axisStickRightX;
    public static float s_axisStickRightY;
    public static float s_axisTriggerLeft;
    public static float s_axisTriggerRight;
    
    //public enum controllerType { amazonGameController = 0 };
    
    public void s3eAndroidControllerStartFrame()
    {
        if (s3eAndroidControllerActivity.s_useAmazonGameController)
            GameController.startFrame();
    }
    
    public boolean s3eAndroidControllerSelectControllerByPlayer(int player)
    {
        if (!s3eAndroidControllerActivity.s_useAmazonGameController)
            return false;
        
        try
        {
            m_SelectedController = GameController.getControllerByPlayer(player);
        }
        catch (PlayerNumberNotFoundException e)
        {
            m_SelectedController = null;
        }
        
        return (m_SelectedController != null);
    }
    
    public int s3eAndroidControllerGetPlayerCount()
    {
        if (m_SelectedController != null)
        {
            return GameController.getPlayerCount();
        }
        else
        {
            /* Need API 16 for generic input manager checks. just return 1 for now!
            // Fallback code just returning 1 if any devices exist (as we only handle one device atm)
            // or zero for none.
            ImputManager manager = Context.getSystemService(INPUT_SERVICE);
            int[] deviceIds = manager.getInputDeviceIds();
            for (int deviceId : deviceIds)
            {
                InputDevice dev = InputDevice.getDevice(deviceId);
                int sources = dev.getSources();

                // Verify that the device has gamepad buttons, control sticks, or both.
                if (((sources & InputDevice.SOURCE_GAMEPAD) == InputDevice.SOURCE_GAMEPAD)
                        || ((sources & InputDevice.SOURCE_JOYSTICK)  == InputDevice.SOURCE_JOYSTICK))
                    return 1;
            }
            return 0;
            */
            return 1;
        }
    }
    
    public boolean s3eAndroidControllerGetButtonState(int button)
    {
        if (m_SelectedController != null)
        {
            return m_SelectedController.isButtonPressed(button);
        }
        else
        {
            return s_keyStates.containsKey(button) ? s_keyStates.get(button) : false;
        }
    }
    
    public float s3eAndroidControllerGetAxisValue(int axis)
    {
        if (m_SelectedController != null)
        {
            return m_SelectedController.getAxisValue(axis);
        }
        else
        {
            switch(axis)
            {
                case android.view.MotionEvent.AXIS_X:
                    return s_axisStickLeftX;
                case android.view.MotionEvent.AXIS_Y:
                    return s_axisStickLeftY;
                case android.view.MotionEvent.AXIS_Z:
                    return s_axisStickRightX;
                case android.view.MotionEvent.AXIS_RZ:
                    return s_axisStickRightY;
                case android.view.MotionEvent.AXIS_BRAKE:
                    return s_axisTriggerLeft;
                case android.view.MotionEvent.AXIS_GAS:
                    return s_axisTriggerRight;
                default:
                    return 0.0f;
            }
        }
    }
    
    public void s3eAndroidControllerSetPropagateButtonsToKeyboard(boolean propagate)
    {
        s3eAndroidControllerActivity.m_propagateButtonEvents = propagate;
    }
    
    // TODO: check/get/set controller type here`
}
