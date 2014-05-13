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

import android.os.Bundle;
import android.util.Log;
import android.view.KeyEvent;
import android.view.MotionEvent;
import com.amazon.device.gamecontroller.GameController;
import com.amazon.device.gamecontroller.GameController.DeviceNotFoundException;
import com.amazon.device.gamecontroller.GameController.PlayerNumberNotFoundException;
import com.ideaworks3d.marmalade.LoaderAPI;
import com.ideaworks3d.marmalade.LoaderActivity;

public class s3eFireTV extends LoaderActivity
{
    private static final String LOG_TAG = "s3eFireTV";
    
    public static s3eFireTV 		m_Activity = null;
	public static GameController	m_SelectedController = null;
    
    @Override
    public void onCreate(Bundle savedInstanceState)
	{
        Log.v(LOG_TAG, "onCreate");
        super.onCreate(savedInstanceState);
        m_Activity = this;

		s3eFireTV_init();
    }
    
    private void s3eFireTV_init()
    {
        Log.v(LOG_TAG, "s3eFireTV_init");
        GameController.init(getApplicationContext());
    }
    
    public void s3eFireTV_startFrame()
    {
        //Log.v(LOG_TAG, "s3eFireTV_startFrame");
        GameController.startFrame();
    }
    
    public boolean s3eFireTV_selectControllerByPlayer(int player)
    {
        //Log.v(LOG_TAG, "s3eFireTV_selectControllerByPlayer");
        try
        {
            m_SelectedController = GameController.getControllerByPlayer(player);
        }
        catch (PlayerNumberNotFoundException e)
        {
            // TODO: Do something more intelligent once we have the dev kit for testing.
        }
        
        return (m_SelectedController != null);
    }
    
    public int s3eFireTV_getPlayerCount()
    {
        //Log.v(LOG_TAG, "s3eFireTV_getPlayerCount");
        if (m_SelectedController != null)
        {
            return GameController.getPlayerCount();
        }
        else
        {
            return 0;
        }
    }
    
    public boolean s3eFireTV_getButtonState(int button)
    {
        //Log.v(LOG_TAG, "s3eFireTV_getButtonState");
        if (m_SelectedController != null)
        {
            return m_SelectedController.isButtonPressed(button);
        }
        else
        {
            return false;
        }
    }
    
    public float s3eFireTV_getAxisValue(int axis)
    {
        //Log.v(LOG_TAG, "s3eFireTV_getAxisValue");
        if (m_SelectedController != null)
        {
            return m_SelectedController.getAxisValue(axis);
        }
        else
        {
            return 0.0f;
        }
    }
}
