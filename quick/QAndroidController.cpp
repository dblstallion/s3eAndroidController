#include "QAndroidController.h"
#include "s3eAndroidController.h"
namespace androidController {

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

} // namespace androidController
