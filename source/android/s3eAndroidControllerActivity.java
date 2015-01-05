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

import android.os.Bundle;
import android.util.Log;
import android.view.KeyEvent;
import android.view.MotionEvent;
import com.amazon.device.gamecontroller.GameController;
import com.amazon.device.gamecontroller.GameController.DeviceNotFoundException;
import com.amazon.device.gamecontroller.GameController.PlayerNumberNotFoundException;
import com.ideaworks3d.marmalade.LoaderAPI;
import com.ideaworks3d.marmalade.LoaderActivity;

// Extend loader activity to override key events.
// Need to include android-custom-activity='com.s3eAndroidController.s3eAndroidControllerActivity'
// in project deployment options for this to work.

// Currently, we're using Amazon's GameCrontroller lib from Fire TV SDK.
// This is a stub jar file with implementations on the actual devices, iOS style!
// The init function will throw an exception if only the stub exists.

// Future plan is to add generic Android button and axis handling via events here and
// and possibly also custom polling implementation to replace or compliment
// the Amazon versions.

// For now, extension just fails to initialise due to polling supported being false
// on non-fire tv devices.

public class s3eAndroidControllerActivity extends LoaderActivity
{
    static boolean m_propagateButtonEvents = true;
    
    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        
        try {
            //Initialize GameController with the context to attach to the game controller service
            GameController.init(this);
            s3eAndroidController.setPollingSupported(true);
        }
        catch (RuntimeException e) {
            s3eAndroidController.setPollingSupported(false);
            Log.d("ANDROIDCONTROLLER", "Amazon GameController library not found on device. s3eAndroidController will fail to initialise");
        }
    }
    
    //Forward key down events to GameController so it can manage state
    @Override
    public boolean onKeyDown(int keyCode, KeyEvent event)
    {
        Log.d("ANDROIDCONTROLLER", "onKeyDown");
        if (s3eAndroidController.isPollingSupported())
        {
            Log.d("ANDROIDCONTROLLER", "polling is supported");
            boolean handled = false;
            try {
                handled = GameController.onKeyDown(keyCode, event);
            }
            catch (DeviceNotFoundException e) {
                Log.d("ANDROIDCONTROLLER", "exception in onKeeyDown");
            }
            
            return (!m_propagateButtonEvents && handled) || super.onKeyDown(keyCode, event);
        }
        
        return super.onKeyDown(keyCode, event);
    }
    
    //Forward key up events to GameController so it can manage state
    @Override
    public boolean onKeyUp(int keyCode, KeyEvent event)
    {
        Log.d("ANDROIDCONTROLLER", "onKeyUp");
        if (s3eAndroidController.isPollingSupported())
        {
            boolean handled = false;
            try {
                handled = GameController.onKeyUp(keyCode, event);
            }
            catch (DeviceNotFoundException e) {
            }
            return (!m_propagateButtonEvents && handled) || super.onKeyUp(keyCode, event);
        }
        
        return super.onKeyUp(keyCode, event);
    }
    
    //Forward motion events to GameController so it can manage state
    @Override
    public boolean onGenericMotionEvent(MotionEvent event)
    {
        if (s3eAndroidController.isPollingSupported())
        {
            boolean handled = false;
            try {
                handled = GameController.onGenericMotionEvent(event);
            }
            catch (DeviceNotFoundException e) {
            }
            return (!m_propagateButtonEvents && handled) || super.onGenericMotionEvent(event);
        }
        
        return super.onGenericMotionEvent(event);
    }
}