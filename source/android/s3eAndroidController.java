/*
java implementation of the s3eAndroidController extension.

Add android-specific functionality here.

These functions are called via JNI from native code.
*/
/*
 * NOTE: This file was originally written by the extension builder, but will not
 * be overwritten (unless --force is specified) and is intended to be modified.
 */
 
package com.s3eAndroidController;

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

public class s3eAndroidController
{
	GameController m_SelectedController = null;
    static boolean s_pollingSupported = false;
    
    public void s3eAndroidControllerStartFrame()
    {
        if (s_pollingSupported)
            GameController.startFrame();
    }
    
    public boolean s3eAndroidControllerSelectControllerByPlayer(int player)
    {
        if (!s_pollingSupported)
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
            return 0;
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
            return false;
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
            return 0.0f;
        }
    }
    
    public void s3eAndroidControllerSetPropagateButtonsToKeyboard(boolean propagate)
    {
        s3eAndroidControllerActivity.m_propagateButtonEvents = propagate;
    }
    
    public static void setPollingSupported(boolean supported)
    {
        s_pollingSupported = supported;
    }
    
    public static boolean isPollingSupported()
    {
        return s_pollingSupported;
    }
    
    // We were using this to check for Fire TV explicitly but not currently used...
    /*public static boolean isAmazonFireTVDevice()
    {
        return android.os.Build.MANUFACTURER.equals("Amazon") &&
            android.os.Build.MODEL.substring(0, 3).equals("AFT");
    }*/
}
