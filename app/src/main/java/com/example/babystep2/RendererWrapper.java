package com.example.babystep2;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import android.opengl.GLSurfaceView.Renderer;
import static android.opengl.GLES20.*;

public class RendererWrapper implements Renderer {

    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config){
        GameLibJNIWrapper.on_surface_created();//glClearColor(0.0f,0.0f,1.0f,0.0f);
    }

    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height){
        // No-op
        GameLibJNIWrapper.on_surface_changed(width,height);
    }

    @Override
    public void onDrawFrame(GL10 gl){
        GameLibJNIWrapper.on_draw_frame();
    }
}
