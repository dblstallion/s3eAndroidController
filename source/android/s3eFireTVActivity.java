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

public class s3eFireTVActivity extends LoaderActivity
{
    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        
        if (s3eFireTV.isAmazonDevice())
        {
            //Initialize GameController with the context to attach to the game controller service
            GameController.init(this);
        }
    }
    
    //Forward key down events to GameController so it can manage state
    @Override
    public boolean onKeyDown(int keyCode, KeyEvent event)
    {
        if (s3eFireTV.isAmazonDevice())
        {
            boolean handled = false;
            try {
                handled = GameController.onKeyDown(keyCode, event);
            }
            catch (DeviceNotFoundException e) {
            }
            return handled || super.onKeyDown(keyCode, event);
        }
        else
        {
            return super.onKeyDown(keyCode, event);
        }
    }
    
    //Forward key up events to GameController so it can manage state
    @Override
    public boolean onKeyUp(int keyCode, KeyEvent event)
    {
        if (s3eFireTV.isAmazonDevice())
        {
            boolean handled = false;
            try {
                handled = GameController.onKeyUp(keyCode, event);
            }
            catch (DeviceNotFoundException e) {
            }
            return handled || super.onKeyUp(keyCode, event);
        }
        else
        {
            return super.onKeyUp(keyCode, event);
        }
    }
    
    //Forward motion events to GameController so it can manage state
    @Override
    public boolean onGenericMotionEvent(MotionEvent event)
    {
        if (s3eFireTV.isAmazonDevice())
        {
            boolean handled = false;
            try {
                handled = GameController.onGenericMotionEvent(event);
            }
            catch (DeviceNotFoundException e) {
            }
            return handled || super.onGenericMotionEvent(event);
        }
        else
        {
            return super.onGenericMotionEvent(event);
        }
    }
}