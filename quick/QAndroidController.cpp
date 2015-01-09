#include "QAndroidController.h"
#include "s3eAndroidController.h"
#include "QLuaHelpers.h"

using namespace quick;

namespace androidController {

    //---- Callbacks ----

    int32 onButtonEvent(void* systemData, void* userData)
    {
        QTrace("androidController.onButtonEvent");
        
        s3eAndroidControllerButtonEvent* data = static_cast<s3eAndroidControllerButtonEvent*>(systemData);

        if (data == NULLL)
        {
            QTrace("onButtonEvent error: callback data is NULL.");
            return 1;
        }
        
        // Note that we are still just using the android key codes.
        // When we extend this api to be cross platform, we'll need to map them
        // (likely that will happen in C++ interface though)
        // Could have reused the "key" event but decided not to to avoid potential
        // clashes in future updates
        LUA_EVENT_PREPARE("controller");
        LUA_EVENT_SET_STRING("keyCode", data->m_Button);
        if (data->m_Pressed)
        {
            LUA_EVENT_SET_STRING("phase", "pressed");
        }
        else
        {
            LUA_EVENT_SET_STRING("phase", "released");
        }
        LUA_EVENT_SET_STRING("device", data->m_Device);
        LUA_EVENT_SET_INTEGER("player", data->m_Player);
        
        LUA_EVENT_SEND();
        lua_pop(g_L, 1);
        return 0;
    }

    bool isAvailable()
    {
        return s3eAndroidControllerAvailable() == S3E_TRUE;
    }

    void startFrame()
    {
        s3eAndroidControllerStartFrame();
    }

    bool selectControllerByPlayer(int player)
    {
        return s3eAndroidControllerSelectControllerByPlayer(player);
    }

    int getPlayerCount()
    {
        return s3eAndroidControllerGetPlayerCount();
    }

    bool getButtonState(int button)
    {
        return s3eAndroidControllerGetButtonState(button);
    }

    float getAxisValue(int axis)
    {
        return s3eAndroidControllerGetAxisValue(axis);
    }

    char* getButtonDisplayName(int button)
    {
        char name[20];
        s3eAndroidControllerGetButtonDisplayName(name, button, S3E_TRUE);
        return name;
    }

    char* getAxisDisplayName(int axis)
    {
        char name[20];
        s3eAndroidControllerGetAxisDisplayName(name, axis, S3E_TRUE);
        return name;
    }

    void setPropagateButtonsToKeyboard(bool propagate)
    {
        s3eAndroidControllerSetPropagateButtonsToKeyboard(propagate);
    }

    void useButtonEvents(bool enabled)
    {
        if (enabled)
        {
            s3eAndroidControllerRegister(S3E_ANDROIDCONTROLLER_CALLBACK_BUTTON, onButtonEvent,  NULL);
        }
        else
        {
            s3eAndroidControllerUnregister(S3E_ANDROIDCONTROLLER_CALLBACK_BUTTON, onButtonEvent,  NULL);
        }
    }
    
} // namespace androidController
