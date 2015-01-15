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
import android.os.Bundle;
import android.util.Log;
import android.view.KeyEvent;
import android.view.MotionEvent;
import android.view.InputDevice;
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
    // callbacks
    private static native void native_ButtonCallback(int button, int state); //TODO: pass controller/player IDs when supported
    //TODO: array to track state of keys for generic polling support
    
    static boolean m_propagateButtonEvents = true;
    static boolean s_supportsAmazonGameController = false;
    static boolean s_useAmazonGameController = false;
    
    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        
        try {
            //Initialize GameController with the context to attach to the game controller service
            GameController.init(this);
            s_supportsAmazonGameController = true;
            s_useAmazonGameController = true;
        }
        catch (RuntimeException e) {
            Log.d("ANDROIDCONTROLLER", "Amazon GameController library not found on device. s3eAndroidController will fail to initialise");
            s3eAndroidController.s_keyStates = new HashMap<Integer, Boolean>();
            s3eAndroidController.s_axisStickLeftX = 0;
            s3eAndroidController.s_axisStickLeftY = 0;
            s3eAndroidController.s_axisStickRightX = 0;
            s3eAndroidController.s_axisStickRightY = 0;
            s3eAndroidController.s_axisTriggerLeft = 0;
            s3eAndroidController.s_axisTriggerRight = 0;
        }
        //s3eAndroidController.setControllerTypeSupported(s3eAndroidController.amazonGameController);
    }
    
    //Forward key down events to GameController so it can manage state
    @Override
    public boolean onKeyDown(int keyCode, KeyEvent event)
    {
        Log.d("ANDROIDCONTROLLER", "onKeyDown");
        boolean handled = false;
        
        if (((event.getSource() & InputDevice.SOURCE_GAMEPAD) == InputDevice.SOURCE_GAMEPAD) && (event.getRepeatCount() == 0))
        {
            // we don't remap the android values - they already match the extension's defined
            // ones we don't map will just be undocumented ints - at least the user can use/ignore them as they wish
                        
            if (s_useAmazonGameController)
            {
                Log.d("ANDROIDCONTROLLER", "polling is supported");
                try {
                    handled = GameController.onKeyDown(keyCode, event);
                }
                catch (DeviceNotFoundException e) {
                    Log.d("ANDROIDCONTROLLER", "GameController not found in onKeyDown");
                }
            }
            else
            {
                handled = true;
                s3eAndroidController.s_keyStates.put(keyCode, true);
            }
            
            if (handled)
            {
                Log.d("ANDROIDCONTROLLER", "sending button down event: " + keyCode);
                native_ButtonCallback(keyCode, 1);
            }
        }
        
        if (!m_propagateButtonEvents && handled)
            return true;
        
        return super.onKeyDown(keyCode, event);
    }
    
    //Forward key up events to GameController so it can manage state
    @Override
    public boolean onKeyUp(int keyCode, KeyEvent event)
    {
        Log.d("ANDROIDCONTROLLER", "onKeyUp");
        boolean handled = false;
        
        if ((event.getSource() & InputDevice.SOURCE_GAMEPAD) == InputDevice.SOURCE_GAMEPAD)
        {
            if (s_useAmazonGameController)
            {
                try {
                    handled = GameController.onKeyUp(keyCode, event);
                }
                catch (DeviceNotFoundException e) {
                    Log.d("ANDROIDCONTROLLER", "GameController not found in onKeyDown");
                }
            }
            else
            {
                handled = true;
                s3eAndroidController.s_keyStates.put(keyCode, false);
            }

            if (handled)
            {
                Log.d("ANDROIDCONTROLLER", "sending button up event");
                native_ButtonCallback(keyCode, 0);
            }
        }
        
        if (!m_propagateButtonEvents && handled)
            return true;
        
        return super.onKeyUp(keyCode, event);
    }
    
    //Forward motion events to GameController so it can manage state
    @Override
    public boolean onGenericMotionEvent(MotionEvent event)
    {
        if (s_useAmazonGameController)
        {
            boolean handled = false;
            try {
                handled = GameController.onGenericMotionEvent(event);
            }
            catch (DeviceNotFoundException e) {
            }
            
            if (handled)
                return true;
        }
        else if ((event.getSource() & InputDevice.SOURCE_JOYSTICK) ==
                InputDevice.SOURCE_JOYSTICK &&
                event.getAction() == MotionEvent.ACTION_MOVE)
        {
            // This event holds all axis info
            // It may have batched movements via getHistoricalAxisValue()
            // These would be useful if we were firing callbacks, but since just
            // polling for now, we just want latest value
            // Could also force near-centre values to zero using 
            // event.getDevice().getMotionRange(axis, event.getSource()).getFlat()
            
            s3eAndroidController.s_axisStickLeftX = event.getAxisValue(MotionEvent.AXIS_X);
            s3eAndroidController.s_axisStickLeftY = event.getAxisValue(MotionEvent.AXIS_Y);
            s3eAndroidController.s_axisStickRightX = event.getAxisValue(MotionEvent.AXIS_Z);
            s3eAndroidController.s_axisStickRightY = event.getAxisValue(MotionEvent.AXIS_RZ);
            s3eAndroidController.s_axisTriggerLeft = event.getAxisValue(MotionEvent.AXIS_LTRIGGER);
            s3eAndroidController.s_axisTriggerRight = event.getAxisValue(MotionEvent.AXIS_RTRIGGER);

            return true;
        }
        
        return super.onGenericMotionEvent(event);
    }
}