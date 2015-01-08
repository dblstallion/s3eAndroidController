#ifndef __Q_ANDROIDCONTROLLER_H
#define __Q_ANDROIDCONTROLLER_H

#include <string>

// tolua_begin

namespace androidController {

enum
{
    maxPlayers  = 4,
    axisCount = 6,
    buttonCount = 15
};

enum
{
    axisStickLeftX   =  0,
    axisStickLeftY   =  1,
    axisStickRightX  = 11,
    axisStickRightY  = 14,
    axisTriggerLeft  = 23,
    axisTriggerRight = 22
};


enum
{
    buttonA               =  96,
    buttonB               =  97,
    buttonDPadCenter      =  23,
    buttonDPadDown        =  20,
    buttonDPadLeft        =  21,
    buttonDPadRight       =  22,
    buttonDPadUp          =  19,
    buttonShoulderLeft    = 102,
    buttonShoulderRight   = 103,
    buttonStickLeft       = 106,
    buttonStickRight      = 107,
    buttonTriggerLeft     = 104,
    buttonTriggerRight    = 105,
    buttonX               =  99,
    buttonY               = 100
};

bool isAvailable();
void startFrame();
bool selectControllerByPlayer(int player);
int getPlayerCount();
bool getButtonState(int button);
float getAxisValue(int axis);
char* getButtonDisplayName(int button);
char* getAxisDisplayName(int axis);
void setPropagateButtonsToKeyboard(bool propagate);

}

// tolua_end
#endif // __Q_ANDROIDCONTROLLER_H
