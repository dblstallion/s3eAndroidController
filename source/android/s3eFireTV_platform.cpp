/*
 * android-specific implementation of the s3eFireTV extension.
 * Add any platform-specific functionality here.
 */
/*
 * NOTE: This file was originally written by the extension builder, but will not
 * be overwritten (unless --force is specified) and is intended to be modified.
 */
#include "s3eFireTV_internal.h"

#include "s3eEdk.h"
#include "s3eEdk_android.h"
#include <jni.h>
#include "IwDebug.h"

static jobject g_Obj;
static jmethodID g_s3eFireTV_init;
static jmethodID g_s3eFireTV_startFrame;
static jmethodID g_s3eFireTV_selectControllerByPlayer;
static jmethodID g_s3eFireTV_selectControllerByDeviceId;
static jmethodID g_s3eFireTV_getPlayerCount;
static jmethodID g_s3eFireTV_getPlayerNumber;
static jmethodID g_s3eFireTV_getButtonState;
static jmethodID g_s3eFireTV_getAxisValue;

s3eResult s3eFireTVInit_platform()
{
    // Get the environment from the pointer
    JNIEnv* env = s3eEdkJNIGetEnv();
    jobject obj = NULL;
    jmethodID cons = NULL;

    // Get the extension class
    jclass cls = s3eEdkAndroidFindClass("s3eFireTV");
    if (!cls)
        goto fail;

    // Get its constructor
    cons = env->GetMethodID(cls, "<init>", "()V");
    if (!cons)
        goto fail;

    // Construct the java class
    obj = env->NewObject(cls, cons);
    if (!obj)
        goto fail;

    // Get all the extension methods
    g_s3eFireTV_init = env->GetMethodID(cls, "s3eFireTV_init", "()V");
    if (!g_s3eFireTV_init)
        goto fail;

    g_s3eFireTV_startFrame = env->GetMethodID(cls, "s3eFireTV_startFrame", "()V");
    if (!g_s3eFireTV_startFrame)
        goto fail;

    g_s3eFireTV_selectControllerByPlayer = env->GetMethodID(cls, "s3eFireTV_selectControllerByPlayer", "(I)Z");
    if (!g_s3eFireTV_selectControllerByPlayer)
        goto fail;

    g_s3eFireTV_selectControllerByDeviceId = env->GetMethodID(cls, "s3eFireTV_selectControllerByDeviceId", "(I)Z");
    if (!g_s3eFireTV_selectControllerByDeviceId)
        goto fail;

    g_s3eFireTV_getPlayerCount = env->GetMethodID(cls, "s3eFireTV_getPlayerCount", "()I");
    if (!g_s3eFireTV_getPlayerCount)
        goto fail;

    g_s3eFireTV_getPlayerNumber = env->GetMethodID(cls, "s3eFireTV_getPlayerNumber", "()I");
    if (!g_s3eFireTV_getPlayerNumber)
        goto fail;

    g_s3eFireTV_getButtonState = env->GetMethodID(cls, "s3eFireTV_getButtonState", "(I)Z");
    if (!g_s3eFireTV_getButtonState)
        goto fail;

    g_s3eFireTV_getAxisValue = env->GetMethodID(cls, "s3eFireTV_getAxisValue", "(I)F");
    if (!g_s3eFireTV_getAxisValue)
        goto fail;



    IwTrace(FIRETV, ("FIRETV init success"));
    g_Obj = env->NewGlobalRef(obj);
    env->DeleteLocalRef(obj);
    env->DeleteGlobalRef(cls);

    // Add any platform-specific initialisation code here
    return S3E_RESULT_SUCCESS;

fail:
    jthrowable exc = env->ExceptionOccurred();
    if (exc)
    {
        env->ExceptionDescribe();
        env->ExceptionClear();
        IwTrace(s3eFireTV, ("One or more java methods could not be found"));
    }
    return S3E_RESULT_ERROR;

}

void s3eFireTVTerminate_platform()
{
    // Add any platform-specific termination code here
}

void s3eFireTV_init_platform()
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    env->CallVoidMethod(g_Obj, g_s3eFireTV_init);
}

void s3eFireTV_startFrame_platform()
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    env->CallVoidMethod(g_Obj, g_s3eFireTV_startFrame);
}

bool s3eFireTV_selectControllerByPlayer_platform(int player)
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    return (bool)env->CallBooleanMethod(g_Obj, g_s3eFireTV_selectControllerByPlayer, player);
}

bool s3eFireTV_selectControllerByDeviceId_platform(int deviceId)
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    return (bool)env->CallBooleanMethod(g_Obj, g_s3eFireTV_selectControllerByDeviceId, deviceId);
}

int s3eFireTV_getPlayerCount_platform()
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    return (int)env->CallIntMethod(g_Obj, g_s3eFireTV_getPlayerCount);
}

int s3eFireTV_getPlayerNumber_platform()
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    return (int)env->CallIntMethod(g_Obj, g_s3eFireTV_getPlayerNumber);
}

bool s3eFireTV_getButtonState_platform(int button)
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    return (bool)env->CallBooleanMethod(g_Obj, g_s3eFireTV_getButtonState, button);
}

float s3eFireTV_getAxisValue_platform(int axis)
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    return (float)env->CallFloatMethod(g_Obj, g_s3eFireTV_getAxisValue, axis);
}
