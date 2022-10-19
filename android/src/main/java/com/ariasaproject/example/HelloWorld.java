package com.ariasaproject.example;

import android.app.Activity;
import android.app.ActivityManager;
import android.content.Context;
import android.content.pm.ConfigurationInfo;
import android.content.res.AssetFileDescriptor;
import android.content.res.Configuration;
import android.opengl.EGL14;
import android.opengl.EGLConfig;
import android.opengl.EGLContext;
import android.opengl.EGLDisplay;
import android.opengl.EGLSurface;
import android.opengl.GLES30;
import android.os.Build;
import android.os.Bundle;
import android.util.Log;
import android.view.SurfaceHolder;
import android.view.SurfaceHolder.Callback;
import android.view.SurfaceView;
import android.view.View;
import android.view.View.OnSystemUiVisibilityChangeListener;

import java.io.FileDescriptor;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.Random;

//AndroidApplication include graphics and Application
public class HelloWorld extends Activity implements Callback {
    public static final String TAG = "MainActivity";

    static {
        try {
            System.loadLibrary("ext");
        } catch (Exception e) {
            System.out.println("failed to load library : ext");
            System.exit(0);
        }
    }

    int mayorV, minorV;
    // graphics params
    private SurfaceHolder holder;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        // SharedPreferences pref = PreferenceManager.getDefaultSharedPreferences(this);
        super.onCreate(savedInstanceState);
        final View d = getWindow().getDecorView();
    		final int uiHide = 5382;//hide all system ui as possible
        d.setSystemUiVisibility(uiHide);
        d.setOnSystemUiVisibilityChangeListener(new OnSystemUiVisibilityChangeListener() {
            @Override
            public void onSystemUiVisibilityChange(int ui) {
                if (ui != uiHide)
                    d.setSystemUiVisibility(uiHide);
            }
        });
        setContentView(R.layout.activity_main);
        SurfaceView view = findViewById(R.id.glSurfaceView);
        
        ActivityManager activityManager = (ActivityManager) getSystemService(Context.ACTIVITY_SERVICE);
        ConfigurationInfo configurationInfo = activityManager.getDeviceConfigurationInfo();
        mayorV = (short) (configurationInfo.reqGlEsVersion >> 16);
        minorV = (short) (configurationInfo.reqGlEsVersion & 0x0000ffff);
        holder = view.getHolder();
    }
    
    private final native void onstart();

    @Override
    protected void onStart() {
    	super.onStart();
        holder.addCallback(this);
	onstart();
    }

    private final native void onresume();

    @Override
    protected void onResume() {
        super.onResume();
	onresume();
    }

    private final native void onpause(boolean finish);

    @Override
    protected void onPause() {
	onpause(isFinishing());
	super.onPause();
    }

    private final native void surfacecreated();

    @Override
    public void surfaceCreated(SurfaceHolder holder) {
        surfacecreated();
    }

    private final native void surfacechanged(int w, int h);

    @Override
    public void surfaceChanged(SurfaceHolder holder, int format, int w, int h) {
	surfacechanged(w, h);
    }

    private final native void surfacedestroyed();

    @Override
    public void surfaceDestroyed(SurfaceHolder holder) {
	surfacedestroyed();
    }
    
    private final native void onstop();

    @Override
    protected void onStop() {
	onstop();
    	holder.removeCallback(this);
    	super.onStop();
    }
}
