s3eAndroidController
====================

This is an Android gamepad/controller extension API for the Marmalade C++ and
Marmalade Quick SDKs.

Currently, it supports:
- Up to 4 controllers on Amazon FireTV
- 1 controller on other Android devices
- Polling API for buttons and analogue sticks
- Event API for buttons (not sticks)

On Fire TV, it uses Amazon's GameController lib. GameController.jar is in the
extension but is just a stub that relies on device libs which are only on the
Fire TV. On other devices it uses some custom code.

Amazon's API is from their Fire TV SDK (see https://developer.amazon.com/appsandservices/solutions/devices/fire-tv/docs/gamecontroller-api)

C++ extension is based on s3eFireTV extension by dblstallion
https://github.com/dblstallion/s3eFireTV

Compared to s3eFireTV, s3eAndroidController adds:
- Generic android (non Fire TV) support for 1 controller
- Callbacks/events for button presses
- Quick/Lua wrapper
- C++ and Lua example app projects
- Smarter checking for Fire TV lib

The Quick API is a simple wrapper around the C++ one, with the usual shortened
naming scheme. Quick version supports all the C++ features.

### Why not use IwGameController instead?!

I've recently created https://github.com/nickchops/IwGameController
That wraps this extension and also supports controller on other platforms.
It has a quick API that's are almost identical to QAndroidController,
so for Quick you could just pick one to use and define androidController to
gameController etc. or vice-versa - fairly easy to try one and swap!
Using IwGameController means you can also test on desktop Simulator...


Requirements and setup for C++ and Quick
----------------------------------------

### Add the extension to your Marmalade search path

You can either add s3eAndroidController to
default paths or keep it in your github project folder and add that to
your Marmalade search paths. The later is recommended so that you don't
have to do this every time you install a new Marmalade version and can
get Github updates easier.

To add your github root to global search, put the following in
< marmalade-root >/s3e/s3e-default.mkf:

        options { module_path="path/to/my/github/projects/root" }

Alternatively, copy s3eAndroidController to < marmalade-root >/extensions.


### Custom activity requirement on Android

You need to use s3eAndroidUserActivity and set that up to call some functions:

1) Grab www.github.com/nickchops/s3eAndroidUserActivity

2) In that, edit source/android/s3eAndroidUserActivity.java:

   - Above the class definition, add this:
   
        import com.nickchops.s3eAndroidController.s3eAndroidControllerActivity;

   - In the class, add/edit so that it includes:
   
        @Override
        protected void onCreate(Bundle savedInstanceState) {
            super.onCreate(savedInstanceState);
            s3eAndroidControllerActivity.onCreate(savedInstanceState);
        }
        
        @Override
        public boolean onKeyDown(int keyCode, KeyEvent event) {
            return s3eAndroidControllerActivity.onKeyDown(keyCode, event) ? true : super.onKeyDown(keyCode, event);
        }
        
        @Override
        public boolean onKeyUp(int keyCode, KeyEvent event) {
            return s3eAndroidControllerActivity.onKeyUp(keyCode, event) ? true : super.onKeyUp(keyCode, event);
        }
        
        @Override
        public boolean onGenericMotionEvent(MotionEvent event) {
            return s3eAndroidControllerActivity.onGenericMotionEvent(event) ? true : super.onGenericMotionEvent(event);
        }

3) Edit s3eAndroidUserActivity_android_java.mkb to include:

        librarypath "../s3eAndroidController/lib/android/s3eAndroidController.jar"
        
4) Rebuild that by running s3eAndroidUserActivity_android_java.mkb
    (no additional tools, or Android SDK needed to build that)


Additional setup for Quick only
-------------------------------

### Prerequisites for Quick only

- Marmalade SDK 7.4 or newer is needed for Quick extension improvements.

- You need scripts for rebuilding Quick binaries. Get these from
  https://github.com/nickchops/MarmaladeQuickRebuildScripts Copy those to the
  root *quick* folder in the SDK.


### You must rebuild binaries to embed the extension in Quick

For Quick, you need to make changes to two quick config files and then
rebuild the Quick binaries. Paths here refer to < marmalade-root >/quick.

1. Edit quick/quickuser_tolua.pkg and add this new line:

        $cfile "path/to/projects/s3eAndroidController/quick/QAndroidController.h"

2. Edit quick/quickuser.mkf and add the following to the 'subprojects' block:

        subprojects
        {
            s3eAndroidController/quick/QAndroidController
        }

   Make sure the parent folder of IwGameController is in global paths

3. Run quick/quickuser_tolua.bat to generate Lua bindings.

4. Rebuild the Quick binaries by running the scripts (build_quick_prebuilt.bat
   etc.)


Add the module to your C++ or Quick project
-------------------------------------------

You must add the following to your app project's MKB file:

        subprojects
        {
            s3eAndroidController
        }


Using the C++ API
-----------------

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


### Button and axis values

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


Using the Quick API
-------------------

NB: If adding the extension to an existing project, you'll likely need to
delete the project's 'build_temp' folder. This is so that the Hub will
regenerate all the necessary deployment scripts and include the new extension.

Quick functions behave like their similarly-named C++ versions:

        androidController.isAvailable()
        androidController.startFrame()
        androidController.selectControllerByPlayer(player)
        androidController.getMaxControllers()
        androidController.getPlayerCount()
        androidController.getButtonState(button)
        androidController.getAxisValue(axis)

See QAndroidController.h for types, axes and buttons. Use like this:

        androidController.getAxisValue(androidController.axisStickLeftX)
        androidController.getButtonState(androidController.buttonA)
        etc.

TODO: I'll probably change these to strings "a" "stickLeftX" etc.
since Lua can do fast string compares (compares object addresses).


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
