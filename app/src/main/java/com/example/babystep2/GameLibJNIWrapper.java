package com.example.babystep2;

public class GameLibJNIWrapper {
    static {
        System.loadLibrary("jni");
    }

    public static native void on_surface_created();

    public static native void on_surface_changed(int width, int height);

    public static native void on_draw_frame();

    public static native void on_touch_down(int x, int y);
}
