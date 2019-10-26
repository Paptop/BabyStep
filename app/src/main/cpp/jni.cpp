#include <jni.h>
#include "game.h"

extern "C"
{
/*
 * Class:     com_example_babystep2_GameLibJNIWrapper
 * Method:    on_surface_created
 * Signature: ()V
 */
JNIEXPORT void JNICALL
Java_com_example_babystep2_GameLibJNIWrapper_on_1surface_1created(JNIEnv *, jclass){
    on_surface_created();
}

/*
 * Class:     com_example_babystep2_GameLibJNIWrapper
 * Method:    on_surface_changed
 * Signature: (II)V
 */
JNIEXPORT void JNICALL
Java_com_example_babystep2_GameLibJNIWrapper_on_1surface_1changed(JNIEnv *, jclass, jint width, jint height){
    on_surface_changed(width, height);
}

/*
 * Class:     com_example_babystep2_GameLibJNIWrapper
 * Method:    on_draw_frame
 * Signature: ()V
 */
JNIEXPORT void JNICALL
Java_com_example_babystep2_GameLibJNIWrapper_on_1draw_1frame(JNIEnv *, jclass) {
    on_draw_frame();
}

JNIEXPORT void JNICALL
Java_com_example_babystep2_GameLibJNIWrapper_on_1touch_1down(JNIEnv *, jclass, jint x, jint y){
    on_touch_down(x, y);
}


}
