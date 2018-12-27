#include <jni.h>
#include <string>
#include <android/log.h>

//__VA_ARGS__
#define LogE(...)  __android_log_print(ANDROID_LOG_ERROR,"JNI",__VA_ARGS__);

extern "C" JNIEXPORT jstring JNICALL
Java_com_yangyakun_jnidemo_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_yangyakun_jnidemo_MainActivity_getNative(JNIEnv *env, jobject instance, jintArray number_,
                                                  jobjectArray Strings) {
    jint *number = env->GetIntArrayElements(number_, NULL);

    jint size = env->GetArrayLength(number_);
    for (int i = 0; i < size; ++i) {
        LogE("JNI","获取java的参数：%d",*(number+i));
        //修改值
        *(i+number) = 100;
    }

    /**
     * 参数三 mode
     * 0：刷新java数组并释放C、C++数组
     * 1：JNI_COMMIT 只刷新java数组
     * 2：JNI_ABORT 只释放
     */
    env->ReleaseIntArrayElements(number_,number,0);


    return 100;

}