s3eAndroidController
====================

This is an Android gamepad/controller extension API for the Marmalade C++ and
Marmalade Quick SDKs.

Currently, it supports:
- Up to 4 controllers on Amazon FireTV
- 1 conroller on other Android devices
- Polling API for buttons and analog sticks
- Event API for buttons (not sticks)

On Fire TV, it uses Amazon's GameController lib. GameController.jar is in the
extension but is just a stub that relies on device libs which are only on the
Fire TV. On other devices it uses some custom code.

Amazon's API is from their Fire TV SDK (see https://developer.amazon.com/appsandservices/solutions/devices/fire-tv/docs/gamecontroller-api)

C++ extension is based on s3eFireTV extension by dblstallion
https://github.com/dblstallion/s3eFireTV

Compared to s3eFireTV, s3eAndroidController adds:
- Generic android support for 1 controller
- Callbacks/events for button presses
- Quick/Lua wrapper
- C++ and Lua example app projects

The Quick API is a simple wrapper around the C++ one, with the usual shortened
naming scheme. Quick version supports all the C++ features.

### IwGameController

I've recently created 
That wraps this extension and other ones and also provides a Quick wrapper.
IwGameController is not well tested yet but will be the preferred API
rather than using this directly. The quick APIs are almost identical
(you could just define androidController to gameController or vice-versa,
so easy to try one and swap!)


Custom activity requirement
---------------------------

The extension requires that a custom main activity is set in your C++ or
Quick project. This is needed in order to catch key and axis events.
You must add the following to the deployments section of your MKB::

        android-custom-activity='com.s3eAndroidController.s3eAndroidControllerActivity'


C++ Functions
-------------

*void    s3eAndroidControllerStartFrame()*

- You must call this at the start of each update loop so that the get button/axis values are updated

*bool    s3eAndroidControllerSelectControllerByPlayer(int player)*

- Select controller by Player (1-4) to get states for

*int     s3eAndroidControllerGetPlayerCount()*

- Get number of players

*bool    s3eAndroidControllerGetButtonState(int button)*

- Get button state. True is down/pressed, false is up/released.
  Includes direction pad presses. D-pad and sticks can also
  have centre press states.

*float   s3eAndroidControllerGetAxisValue(int axis)*

- Get value from -1 to 1 indicating how far stick/pad is pressed along an axis.
  -1 is left/bottom, 0 centered and 1 is right/top.

*void s3eAndroidControllerSetPropagateButtonsToKeyboard(bool propagate)*

- If set true, on controller button presses, regular s3eKeyboard events/states
  for the pressed button will still occur. If set false, no s3eKeyboard event
  will happen. Default is true.


Button and axis values
----------------------

The Marmalade values here are just mapped directly to the equivalents in the Amazon Game Controller Java API

Axes for querying s3eAndroidControllerGetAxisValue:

- S3E_ANDROID_CONTROLLER_AXIS_STICK_LEFT_X         0
- S3E_ANDROID_CONTROLLER_AXIS_STICK_LEFT_Y         1
- S3E_ANDROID_CONTROLLER_AXIS_STICK_RIGHT_X        11
- S3E_ANDROID_CONTROLLER_AXIS_STICK_RIGHT_Y        14
- S3E_ANDROID_CONTROLLER_AXIS_TRIGGER_LEFT         23
- S3E_ANDROID_CONTROLLER_AXIS_TRIGGER_RIGHT        22

Buttons for querying s3eAndroidControllerGetButtonState:

- S3E_ANDROID_CONTROLLER_BUTTON_A                  96
- S3E_ANDROID_CONTROLLER_BUTTON_B                  97
- S3E_ANDROID_CONTROLLER_BUTTON_DPAD_CENTER        23
- S3E_ANDROID_CONTROLLER_BUTTON_DPAD_DOWN          20
- S3E_ANDROID_CONTROLLER_BUTTON_DPAD_LEFT          21
- S3E_ANDROID_CONTROLLER_BUTTON_DPAD_RIGHT         22
- S3E_ANDROID_CONTROLLER_BUTTON_DPAD_UP            19
- S3E_ANDROID_CONTROLLER_BUTTON_SHOULDER_LEFT      102
- S3E_ANDROID_CONTROLLER_BUTTON_SHOULDER_RIGHT     103
- S3E_ANDROID_CONTROLLER_BUTTON_STICK_LEFT         106
- S3E_ANDROID_CONTROLLER_BUTTON_STICK_RIGHT        107
- S3E_ANDROID_CONTROLLER_BUTTON_TRIGGER_LEFT       104
- S3E_ANDROID_CONTROLLER_BUTTON_TRIGGER_RIGHT      105
- S3E_ANDROID_CONTROLLER_BUTTON_X                  99
- S3E_ANDROID_CONTROLLER_BUTTON_Y                  100

Quick Wrapper
-------------

### Prerequisites

1. Marmalade SDK 7.4 or newer is needed for Quick extension improvemenmts.
   
2. Place the whole s3eAndroidController folder in sdk/extensions
   
2. You need scripts for rebuilding Quick binaries. Get these from
   https://github.com/nickchops/MarmaladeQuickRebuildScripts Copy those to the
   root *quick* folder in the SDK.


### Setup: Add and build this wrapper into Quick

3. Edit quick/quickuser_tolua.pkg and add this new line:

        $cfile "../extensions/s3eAndroidController/quick/QAndroidController.h"

4. Edit quick/quickuser.mkf and add the following to the 'files' block so that
   the wrappers can be built into the Quick binaries::

        ("$MARMALADE_ROOT/extensions/s3eAndroidController/quick")
        QAndroidController.h
        QAndroidController.cpp

5. In quickuser.mkf, also add s3eAndroidController to the 'subprojects' block:

        subprojects
        {
            s3eAndroidController
        }
        
   This allows C++ parts of the actual extension to be built into Quick's
   binaries.
   
5. Run quick/quickuser_tolua.bat to generate Lua bindings.

6. Rebuild the Quick binaries by running the scripts (build_quick_prebuilt.bat
   etc.)

### Use the wrapper in your project

1. Add s3eAndroidController to the subprojects block of you app's mkb as well.
   This makes the required libraries get bundled in the package.
   
2. Add android-custom-activity='com.s3eAndroidController.s3eAndroidControllerActivity'
   to the deployments block of your app's mkb.

2. If updating an existing project, you'll likely need to delete the project's
   'build_temp' folder. This is so that the Hub will regenerate all the
   necessary deployment scripts and include the new extension.


Issues with clashing custom activities
--------------------------------------

NB: you can only have one custom activity set like this. If you are already
using another extensions that requires a custom activity, you will have to
edit one to inherit and daisy-chain off the other. For example, edit
s3eAndroidController/source/android/s3eAndroidControllerActivity.java
so that the activity *imports* and *extends* your other existing activity
instead of LoaderActivity. Then re-build this extension and then just leave
the existing activity as the android-custom-activity.


------------------------------------------------------------------------------------------
(C) 2014 Nick Smith.

All code is provided under the MIT license unless stated otherwise:

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
