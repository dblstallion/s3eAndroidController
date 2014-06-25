/*
java implementation of the s3eFireTV extension.

Add android-specific functionality here.

These functions are called via JNI from native code.
*/
/*
 * NOTE: This file was originally written by the extension builder, but will not
 * be overwritten (unless --force is specified) and is intended to be modified.
 */
 
package com.s3eFireTV;

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

public class s3eFireTV
{
	GameController m_SelectedController = null;
    
    public void s3eFireTV_startFrame()
    {
        if (isAmazonFireTVDevice())
        {
            GameController.startFrame();
        }
    }
    
    public boolean s3eFireTV_selectControllerByPlayer(int player)
    {
        if (isAmazonFireTVDevice())
        {
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
        else
        {
            return false;
        }
    }
    
    public int s3eFireTV_getPlayerCount()
    {
        if (isAmazonFireTVDevice())
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
        else
        {
            return 0;
        }
    }
    
    public boolean s3eFireTV_getButtonState(int button)
    {
        if (isAmazonFireTVDevice())
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
        else
        {
            return false;
        }
    }
    
    public float s3eFireTV_getAxisValue(int axis)
    {
        if (isAmazonFireTVDevice())
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
        else
        {
            return 0.0f;
        }
    }
    
    public static boolean isAmazonFireTVDevice()
    {
        return android.os.Build.MANUFACTURER.equals("Amazon") &&
            android.os.Build.MODEL.substring(0, 3).equals("AFT");
    }
}
