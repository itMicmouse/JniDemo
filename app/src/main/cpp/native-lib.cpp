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

    int32_t size = env->GetArrayLength(number_);
    for (int i = 0; i < size; ++i) {
        LogE("获取java的参数：%d", *(number + i));
        //修改值
        *(i + number) = 100;
    }

    /**
     * 参数三 mode
     * 0：刷新java数组并释放C、C++数组
     * 1：JNI_COMMIT 只刷新java数组
     * 2：JNI_ABORT 只释放
     */
    env->ReleaseIntArrayElements(number_, number, 0);


    int32_t stringsSize = env->GetArrayLength(Strings);
    for (int i = 0; i < stringsSize; ++i) {
        jstring str = static_cast<jstring>(env->GetObjectArrayElement(Strings, i));
        //转成可操作的
        const char *s = env->GetStringUTFChars(str, 0);
        LogE("获取java的参数：%s", s);
        env->ReleaseStringUTFChars(str, s);
    }

    return 100;

}

extern "C"
JNIEXPORT jint JNICALL
Java_com_yangyakun_jnidemo_MainActivity_getBean(JNIEnv *env, jobject instance, jobject bean,
                                                jstring string_) {
    const char *string = env->GetStringUTFChars(string_, 0);

    //类似于java中的反射
    //1、获取java对应的class对象
    jclass classBean = env->GetObjectClass(bean);
    //2、获取要调用的方法  // 参数3： 签名
    jmethodID getNumber = env->GetMethodID(classBean, "getNumber", "()I");
    //3、调用方法
    jint number = env->CallIntMethod(bean, getNumber);
    LogE("jni调用java方法getNumber 获取的结果：%d", number);


    jmethodID setNumber = env->GetMethodID(classBean, "setNumber", "(I)V");
    env->CallVoidMethod(bean, setNumber, 129);

    jmethodID printinfo = env->GetStaticMethodID(classBean, "printinfo", "(Ljava/lang/String;)V");
    jstring info = env->NewStringUTF("我是Bean类的静态方法，被C++调用");
    env->CallStaticVoidMethod(classBean, printinfo, info);
    //释放局部引用
    env->DeleteLocalRef(info);

    jmethodID printinfo2 = env->GetStaticMethodID(classBean, "printInfo",
                                                  "(Lcom/yangyakun/jnidemo/Bean;)V");
    // bean对象
    //在Jni创建java对象：
    jclass bean2Cls = env->FindClass("com/yangyakun/jnidemo/Bean");
    //反射创建对象
    //1、获得类的构造方法
    jmethodID constuct = env->GetMethodID(bean2Cls, "<init>", "(I)V");
    //2、调用构造方法 创建对象
    jobject bean2Obj = env->NewObject(bean2Cls, constuct,89);

    env->CallStaticVoidMethod(classBean, printinfo2, bean2Obj);

    env->DeleteLocalRef(bean2Obj);
    env->DeleteLocalRef(bean2Cls);


    jfieldID number2 = env->GetFieldID(classBean,"number","I");
    env->SetIntField(bean,number2,555);

    env->ReleaseStringUTFChars(string_, string);

    return 100;
}