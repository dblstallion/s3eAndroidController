/*
 * android-specific implementation of the s3eAndroidController extension.
 * Add any platform-specific functionality here.
 */
/*
 * NOTE: This file was originally written by the extension builder, but will not
 * be overwritten (unless --force is specified) and is intended to be modified.
 */
#include "s3eAndroidController_internal.h"

#include "s3eEdk.h"
#include "s3eEdk_android.h"
#include <jni.h>
#include "IwDebug.h"

static jobject g_Obj;
static jmethodID g_s3eAndroidControllerStartFrame;
static jmethodID g_s3eAndroidControllerSelectControllerByPlayer;
static jmethodID g_s3eAndroidControllerGetPlayerCount;
static jmethodID g_s3eAndroidControllerGetButtonState;
static jmethodID g_s3eAndroidControllerGetAxisValue;

s3eResult s3eAndroidControllerInit_platform()
{
    // Get the environment from the pointer
    JNIEnv* env = s3eEdkJNIGetEnv();
    jobject obj = NULL;
    jmethodID cons = NULL;
    jmethodID isFireTV = NULL; //cant declare pointers between goto and fail!
    bool supportedDevice;

    // Get the extension class
    jclass cls = s3eEdkAndroidFindClass("com/s3eAndroidController/s3eAndroidController");
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
    g_s3eAndroidControllerStartFrame = env->GetMethodID(cls, "s3eAndroidControllerStartFrame", "()V");
    if (!g_s3eAndroidControllerStartFrame)
        goto fail;

    g_s3eAndroidControllerSelectControllerByPlayer = env->GetMethodID(cls, "s3eAndroidControllerSelectControllerByPlayer", "(I)Z");
    if (!g_s3eAndroidControllerSelectControllerByPlayer)
        goto fail;

    g_s3eAndroidControllerGetPlayerCount = env->GetMethodID(cls, "s3eAndroidControllerGetPlayerCount", "()I");
    if (!g_s3eAndroidControllerGetPlayerCount)
        goto fail;

    g_s3eAndroidControllerGetButtonState = env->GetMethodID(cls, "s3eAndroidControllerGetButtonState", "(I)Z");
    if (!g_s3eAndroidControllerGetButtonState)
        goto fail;

    g_s3eAndroidControllerGetAxisValue = env->GetMethodID(cls, "s3eAndroidControllerGetAxisValue", "(I)F");
    if (!g_s3eAndroidControllerGetAxisValue)
        goto fail;
    

    isFireTV = env->GetMethodID(cls, "isAmazonFireTVDevice", "()Z");
    if (!isFireTV)
        goto fail;
    
    supportedDevice = (bool)env->CallBooleanMethod(obj, isFireTV);
    if (supportedDevice)
    {
        IwTrace(ANDROIDCONTROLLER, ("supported"));
    }
    else
    {
        IwTrace(ANDROIDCONTROLLER, ("NOT supported"));
        goto fail;
    }

    IwTrace(ANDROIDCONTROLLER, ("ANDROIDCONTROLLER init success"));
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
        IwTrace(ANDROIDCONTROLLER, ("One or more java methods could not be found"));
    }
    return S3E_RESULT_ERROR;
}

void s3eAndroidControllerTerminate_platform()
{
    // Add any platform-specific termination code here
}

void s3eAndroidControllerStartFrame_platform()
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    env->CallVoidMethod(g_Obj, g_s3eAndroidControllerStartFrame);
}

bool s3eAndroidControllerSelectControllerByPlayer_platform(int player)
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    return (bool)env->CallBooleanMethod(g_Obj, g_s3eAndroidControllerSelectControllerByPlayer, player);
}

int s3eAndroidControllerGetPlayerCount_platform()
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    return (int)env->CallIntMethod(g_Obj, g_s3eAndroidControllerGetPlayerCount);
}

bool s3eAndroidControllerGetButtonState_platform(int button)
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    return (bool)env->CallBooleanMethod(g_Obj, g_s3eAndroidControllerGetButtonState, button);
}

float s3eAndroidControllerGetAxisValue_platform(int axis)
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    return (float)env->CallFloatMethod(g_Obj, g_s3eAndroidControllerGetAxisValue, axis);
}
