s3eAndroidController
====================

This is an Android gamepad/controller extension API for the Marmalade C++ SDK.
It's a polling based API (not event driven) that uses Amazon's GameController
API from their Fire TV SDK (see https://developer.amazon.com/appsandservices/solutions/devices/fire-tv/docs/gamecontroller-api)

Based on s3eFireTV extension by dblstallion
https://github.com/dblstallion/s3eFireTV

Mostly this is just renamed atm, ready to be pulled into a Quick generic
controller API. Im planning to integrate this into a cross-platform controller
module for C++ Marmalade at some point.

Functions
--------

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
