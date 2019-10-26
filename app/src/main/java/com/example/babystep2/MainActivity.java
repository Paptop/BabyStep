package com.example.babystep2;

import androidx.appcompat.app.AppCompatActivity;

import android.app.ActivityManager;
import android.content.Context;
import android.content.pm.ConfigurationInfo;
import android.opengl.GLSurfaceView;
import android.os.Bundle;
import android.view.MotionEvent;
import android.view.View;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity implements View.OnTouchListener {

    private GLSurfaceView _glSurfaceView;
    private boolean _bRendererSet;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);


        ActivityManager activityManager = (ActivityManager) getSystemService(Context.ACTIVITY_SERVICE);
        ConfigurationInfo configurationInfo = activityManager.getDeviceConfigurationInfo();

        final boolean supportsEs2 = configurationInfo.reqGlEsVersion >= 0x20000;

        if (supportsEs2){
            _glSurfaceView = new GLSurfaceView(this);

            _glSurfaceView.setEGLContextClientVersion(2);
            _glSurfaceView.setRenderer(new RendererWrapper());
            _glSurfaceView.setOnTouchListener(this);
            _bRendererSet = true;
            setContentView(_glSurfaceView);
        }
        else
        {
            Toast.makeText(this, "This device does not support OpenGL ES 2.0.", Toast.LENGTH_LONG).show();
            return;
        }

    }

    @Override
    public boolean onTouch(View v, MotionEvent event) {
        int x = (int)event.getX();
        int y = (int)event.getY();

        switch(event.getAction())
        {
            case MotionEvent.ACTION_DOWN:
                GameLibJNIWrapper.on_touch_down(x, y);
                break;
            default:
                return false;
        }

        return false;
    }
}
