/*
 * WARNING: this is an autogenerated file and will be overwritten by
 * the extension interface script.
 */

#include "s3eExt.h"
#include "IwDebug.h"
#include "s3eDevice.h"


#include "s3eAndroidController.h"


#ifndef S3E_EXT_SKIP_LOADER_CALL_LOCK
// For MIPs (and WP8) platform we do not have asm code for stack switching
// implemented. So we make LoaderCallStart call manually to set GlobalLock
#if defined __mips || defined S3E_ANDROID_X86 || (defined(WINAPI_FAMILY) && (WINAPI_FAMILY == WINAPI_FAMILY_PHONE_APP))
#define LOADER_CALL_LOCK
#endif
#endif

/**
 * Definitions for functions types passed to/from s3eExt interface
 */
typedef       void(*s3eAndroidControllerStartFrame_t)();
typedef       bool(*s3eAndroidControllerSelectControllerByPlayer_t)(int player);
typedef        int(*s3eAndroidControllerGetPlayerCount_t)();
typedef       bool(*s3eAndroidControllerGetButtonState_t)(int button);
typedef      float(*s3eAndroidControllerGetAxisValue_t)(int axis);
typedef  s3eResult(*s3eAndroidControllerGetButtonDisplayName_t)(char* dst, int button, s3eBool terminateString);
typedef  s3eResult(*s3eAndroidControllerGetAxisDisplayName_t)(char* dst, int axis, s3eBool terminateString);

/**
 * struct that gets filled in by s3eAndroidControllerRegister
 */
typedef struct s3eAndroidControllerFuncs
{
    s3eAndroidControllerStartFrame_t m_s3eAndroidControllerStartFrame;
    s3eAndroidControllerSelectControllerByPlayer_t m_s3eAndroidControllerSelectControllerByPlayer;
    s3eAndroidControllerGetPlayerCount_t m_s3eAndroidControllerGetPlayerCount;
    s3eAndroidControllerGetButtonState_t m_s3eAndroidControllerGetButtonState;
    s3eAndroidControllerGetAxisValue_t m_s3eAndroidControllerGetAxisValue;
    s3eAndroidControllerGetButtonDisplayName_t m_s3eAndroidControllerGetButtonDisplayName;
    s3eAndroidControllerGetAxisDisplayName_t m_s3eAndroidControllerGetAxisDisplayName;
} s3eAndroidControllerFuncs;

static s3eAndroidControllerFuncs g_Ext;
static bool g_GotExt = false;
static bool g_TriedExt = false;
static bool g_TriedNoMsgExt = false;

static bool _extLoad()
{
    if (!g_GotExt && !g_TriedExt)
    {
        s3eResult res = s3eExtGetHash(0xb381b915, &g_Ext, sizeof(g_Ext));
        if (res == S3E_RESULT_SUCCESS)
            g_GotExt = true;
        else
            s3eDebugAssertShow(S3E_MESSAGE_CONTINUE_STOP_IGNORE,                 "error loading extension: s3eAndroidController");

        g_TriedExt = true;
        g_TriedNoMsgExt = true;
    }

    return g_GotExt;
}

static bool _extLoadNoMsg()
{
    if (!g_GotExt && !g_TriedNoMsgExt)
    {
        s3eResult res = s3eExtGetHash(0xb381b915, &g_Ext, sizeof(g_Ext));
        if (res == S3E_RESULT_SUCCESS)
            g_GotExt = true;
        g_TriedNoMsgExt = true;
        if (g_TriedExt)
            g_TriedExt = true;
    }

    return g_GotExt;
}

s3eBool s3eAndroidControllerAvailable()
{
    _extLoadNoMsg();
    return g_GotExt ? S3E_TRUE : S3E_FALSE;
}

void s3eAndroidControllerStartFrame()
{
    IwTrace(ANDROIDCONTROLLER_VERBOSE, ("calling s3eAndroidController[0] func: s3eAndroidControllerStartFrame"));

    if (!_extLoad())
        return;

#ifdef LOADER_CALL_LOCK
    s3eDeviceLoaderCallStart(S3E_TRUE, NULL);
#endif

    g_Ext.m_s3eAndroidControllerStartFrame();

#ifdef LOADER_CALL_LOCK
    s3eDeviceLoaderCallDone(S3E_TRUE, NULL);
#endif

    return;
}

bool s3eAndroidControllerSelectControllerByPlayer(int player)
{
    IwTrace(ANDROIDCONTROLLER_VERBOSE, ("calling s3eAndroidController[1] func: s3eAndroidControllerSelectControllerByPlayer"));

    if (!_extLoad())
        return false;

#ifdef LOADER_CALL_LOCK
    s3eDeviceLoaderCallStart(S3E_TRUE, NULL);
#endif

    bool ret = g_Ext.m_s3eAndroidControllerSelectControllerByPlayer(player);

#ifdef LOADER_CALL_LOCK
    s3eDeviceLoaderCallDone(S3E_TRUE, NULL);
#endif

    return ret;
}

int s3eAndroidControllerGetPlayerCount()
{
    IwTrace(ANDROIDCONTROLLER_VERBOSE, ("calling s3eAndroidController[2] func: s3eAndroidControllerGetPlayerCount"));

    if (!_extLoad())
        return 0;

#ifdef LOADER_CALL_LOCK
    s3eDeviceLoaderCallStart(S3E_TRUE, NULL);
#endif

    int ret = g_Ext.m_s3eAndroidControllerGetPlayerCount();

#ifdef LOADER_CALL_LOCK
    s3eDeviceLoaderCallDone(S3E_TRUE, NULL);
#endif

    return ret;
}

bool s3eAndroidControllerGetButtonState(int button)
{
    IwTrace(ANDROIDCONTROLLER_VERBOSE, ("calling s3eAndroidController[3] func: s3eAndroidControllerGetButtonState"));

    if (!_extLoad())
        return false;

#ifdef LOADER_CALL_LOCK
    s3eDeviceLoaderCallStart(S3E_TRUE, NULL);
#endif

    bool ret = g_Ext.m_s3eAndroidControllerGetButtonState(button);

#ifdef LOADER_CALL_LOCK
    s3eDeviceLoaderCallDone(S3E_TRUE, NULL);
#endif

    return ret;
}

float s3eAndroidControllerGetAxisValue(int axis)
{
    IwTrace(ANDROIDCONTROLLER_VERBOSE, ("calling s3eAndroidController[4] func: s3eAndroidControllerGetAxisValue"));

    if (!_extLoad())
        return 0;

#ifdef LOADER_CALL_LOCK
    s3eDeviceLoaderCallStart(S3E_TRUE, NULL);
#endif

    float ret = g_Ext.m_s3eAndroidControllerGetAxisValue(axis);

#ifdef LOADER_CALL_LOCK
    s3eDeviceLoaderCallDone(S3E_TRUE, NULL);
#endif

    return ret;
}

s3eResult s3eAndroidControllerGetButtonDisplayName(char* dst, int button, s3eBool terminateString)
{
    IwTrace(ANDROIDCONTROLLER_VERBOSE, ("calling s3eAndroidController[5] func: s3eAndroidControllerGetButtonDisplayName"));

    if (!_extLoad())
        return S3E_RESULT_ERROR;

#ifdef LOADER_CALL_LOCK
    s3eDeviceLoaderCallStart(S3E_TRUE, NULL);
#endif

    s3eResult ret = g_Ext.m_s3eAndroidControllerGetButtonDisplayName(dst, button, terminateString);

#ifdef LOADER_CALL_LOCK
    s3eDeviceLoaderCallDone(S3E_TRUE, NULL);
#endif

    return ret;
}

s3eResult s3eAndroidControllerGetAxisDisplayName(char* dst, int axis, s3eBool terminateString)
{
    IwTrace(ANDROIDCONTROLLER_VERBOSE, ("calling s3eAndroidController[6] func: s3eAndroidControllerGetAxisDisplayName"));

    if (!_extLoad())
        return S3E_RESULT_ERROR;

#ifdef LOADER_CALL_LOCK
    s3eDeviceLoaderCallStart(S3E_TRUE, NULL);
#endif

    s3eResult ret = g_Ext.m_s3eAndroidControllerGetAxisDisplayName(dst, axis, terminateString);

#ifdef LOADER_CALL_LOCK
    s3eDeviceLoaderCallDone(S3E_TRUE, NULL);
#endif

    return ret;
}
