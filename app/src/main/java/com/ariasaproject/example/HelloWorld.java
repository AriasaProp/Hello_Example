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
public class HelloWorld extends Activity implements Runnable, Callback {
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
    volatile boolean resume = false, pause = false, destroy = false, resize = false, rendered = false, hasFocus = true,
            hasSurface = false, mExited = false;
    long frameStart = System.currentTimeMillis(), lastFrameTime = System.currentTimeMillis();
    int frames, fps, width = 0, height = 0;
    float deltaTime = 0;
    Thread mainTGFThread;
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
        this.mayorV = (short) (configurationInfo.reqGlEsVersion >> 16);
        this.minorV = (short) (configurationInfo.reqGlEsVersion & 0x0000ffff);
        this.holder = view.getHolder();
        
        mainTGFThread = new Thread(this, "GLThread");
        mainTGFThread.start();
    }

    @Override
    protected synchronized void onResume() {
        super.onResume();
        resume = true;
        notifyAll();
    }

    @Override
    protected synchronized void onPause() {
        // graphics
        pause = true;
        rendered = true;
        notifyAll();
        while (!mExited && rendered) {
            try {
                wait();
            } catch (InterruptedException ex) {
                Thread.currentThread().interrupt();
            }
        }
        if (isFinishing()) {
            destroy = true;
            notifyAll();
            while (!mExited) {
                try {
                    wait();
                } catch (InterruptedException ex) {
                    Thread.currentThread().interrupt();
                }
            }

        }
        super.onPause();
    }

    @Override
    public synchronized void surfaceCreated(SurfaceHolder holder) {
        // fall thru surfaceChanged
    }

    @Override
    public synchronized void surfaceChanged(SurfaceHolder holder, int format, int w, int h) {
        if (!hasSurface) {
            rendered = true;
            hasSurface = true;
        }
        width = w;
        height = h;
        resize = true;
        notifyAll();
        while (!mExited && rendered) {
            try {
                wait();
            } catch (InterruptedException ex) {
                Thread.currentThread().interrupt();
            }
        }
    }

    @Override
    public synchronized void surfaceDestroyed(SurfaceHolder holder) {
        hasSurface = false;
        notifyAll();
    }
    
    public static class ApplicationListener {
    		public void create() {}
    		public void recreate() {
    		}
    		public void resize(int w, int h) {}
    		public void resume() {
    		}
    		public void render(float d) {
    			GLES30.glClearColor(1, 1, 0, 1); 
    			GLES30.glClear(GLES30.GL_COLOR_BUFFER_BIT | GLES30.GL_DEPTH_BUFFER_BIT | GLES30.GL_STENCIL_BUFFER_BIT );
    		}
    		public void pause() {}
    		public void destroy() {}
    }

    // main loop
    @Override
    public void run() {
        holder.addCallback(this);

        EGLDisplay mEglDisplay = null;
        EGLSurface mEglSurface = null;
        EGLConfig mEglConfig = null;
        EGLContext mEglContext = null;
        ApplicationListener appl = new ApplicationListener();
        try {
            byte eglDestroyRequest = 0;// to destroy egl surface, egl contex, egl display, ?....
            boolean wantRender = false, newContext = true, // indicator
                    created = false, lrunning = true, lresize, lresume = false, lpause = false;// on running state
            while (!destroy) {
                synchronized (this) {
                    // render notify
                    if (wantRender) {
                        rendered = false;
                        wantRender = false;
                        notifyAll();
                    }
                    if (rendered)
                        wantRender = true;
                    // egl destroy request
                    if (mEglSurface != null && (eglDestroyRequest > 0 || !hasSurface)) {
                        EGL14.eglMakeCurrent(mEglDisplay, EGL14.EGL_NO_SURFACE, EGL14.EGL_NO_SURFACE, EGL14.EGL_NO_CONTEXT);
                        if (!EGL14.eglDestroySurface(mEglDisplay, mEglSurface))
                            throw new RuntimeException("eglDestroySurface failed: " + Integer.toHexString(EGL14.eglGetError()));
                        mEglSurface = null;
                        if (mEglContext != null && (eglDestroyRequest > 1)) {
                            if (!EGL14.eglDestroyContext(mEglDisplay, mEglContext))
                                throw new RuntimeException("eglDestroyContext failed: " + Integer.toHexString(EGL14.eglGetError()));
                            mEglContext = null;
                            newContext = true;
                            if (mEglDisplay != null && (eglDestroyRequest > 3)) {
                                EGL14.eglTerminate(mEglDisplay);
                                mEglDisplay = null;
                            }
                        }
                        eglDestroyRequest = 0;
                    }
                    // end destroy request

                    lresize = resize;
                    if (resize)
                        resize = false;
                    if (lpause)
                        lrunning = false;
                    lpause = pause;
                    if (pause)
                        pause = false;
                    lresume = resume;
                    if (resume) {
                        resume = false;
                        lrunning = true;
                    }
                    // Ready to draw?
                    if (!lrunning || !hasSurface) {
                        wait();
                        continue;
                    }
                }

                if (mEglDisplay == null) {
                    final int[] temp = new int[2]; // for chaching value output

                    mEglDisplay = EGL14.eglGetDisplay(EGL14.EGL_DEFAULT_DISPLAY);
                    if (mEglDisplay == EGL14.EGL_NO_DISPLAY || mEglDisplay == null) {
                        mEglDisplay = null;
                        throw new RuntimeException("eglGetDisplay failed " + Integer.toHexString(EGL14.eglGetError()));
                    }
                    if (EGL14.eglInitialize(mEglDisplay, temp, 0, temp, 1))
                        Log.i(TAG, "version EGL " + temp[0] + "." + temp[1]);
                    else
                        throw new RuntimeException("eglInitialize failed " + Integer.toHexString(EGL14.eglGetError()));

                    if (mEglConfig == null) {
                        // choose best config
                        final int[] s_configAttribs2 = {EGL14.EGL_COLOR_BUFFER_TYPE, EGL14.EGL_RGB_BUFFER, EGL14.EGL_NONE };
                        EGL14.eglChooseConfig(mEglDisplay, s_configAttribs2, 0, null, 0, 0, temp, 0);
                        if (temp[0] <= 0)
                            throw new IllegalArgumentException("No configs match with configSpec");
                        EGLConfig[] configs = new EGLConfig[temp[0]];
                        EGL14.eglChooseConfig(mEglDisplay, s_configAttribs2, 0, configs, 0, configs.length, temp, 0);
                        int lastSc = -1, curSc;
                        mEglConfig = configs[0];
                        for (EGLConfig config : configs) {
                            temp[0] = -1;
                            // alpha should 0
                            // choose higher depth, stencil, color buffer(rgba)
                            curSc = -1;
                            for (int attr : new int[]{EGL14.EGL_RENDERABLE_TYPE, EGL14.EGL_BUFFER_SIZE, EGL14.EGL_ALPHA_SIZE, EGL14.EGL_DEPTH_SIZE, EGL14.EGL_STENCIL_SIZE}) {
                                if (EGL14.eglGetConfigAttrib(mEglDisplay, config, attr, temp, 0)) {
                                    if (attr == EGL14.EGL_ALPHA_SIZE)
                                        temp[0] *= -1;
                                    curSc += temp[0];
                                } else {
                                    int error;
                                    while ((error = EGL14.eglGetError()) != EGL14.EGL_SUCCESS)
                                        Log.e(TAG, String.format("EglConfigAttribute : EGL error: 0x%x", error));
                                }
                            }
                            if (curSc > lastSc) {
                                lastSc = curSc;
                                mEglConfig = config;
                            }
                        }
                    }
                }
                if (newContext || mEglSurface == null) {
                    if (newContext) {
                        final int[] attrib_list = {EGL14.EGL_CONTEXT_CLIENT_VERSION, mayorV, EGL14.EGL_NONE};
                        mEglContext = EGL14.eglCreateContext(mEglDisplay, mEglConfig, EGL14.EGL_NO_CONTEXT, attrib_list, 0);
                        if (mEglContext == null || mEglContext == EGL14.EGL_NO_CONTEXT) {
                            mEglContext = null;
                            throw new RuntimeException("createContext failed: " + Integer.toHexString(EGL14.eglGetError()));
                        }
                    }
                    mEglSurface = EGL14.eglCreateWindowSurface(mEglDisplay, mEglConfig, holder, null, 0);
                    if (mEglSurface == null || mEglSurface == EGL14.EGL_NO_SURFACE) {
                        mEglSurface = null;
                        throw new RuntimeException("Create EGL Surface failed: " + Integer.toHexString(EGL14.eglGetError()));
                    }
                    if (!EGL14.eglMakeCurrent(mEglDisplay, mEglSurface, mEglSurface, mEglContext))
                        throw new RuntimeException("Make EGL failed: " + Integer.toHexString(EGL14.eglGetError()));

                    if (newContext) {
                        if (created)
                      			appl.recreate();
                        else
                            appl.create();
                       
                        appl.resize(width, height);
                        lresize = false;
                        lastFrameTime = System.currentTimeMillis();
                        newContext = false;
                    }
                }
                if (lresize) {
                    EGL14.eglMakeCurrent(mEglDisplay, EGL14.EGL_NO_SURFACE, EGL14.EGL_NO_SURFACE, EGL14.EGL_NO_CONTEXT);
                    EGL14.eglMakeCurrent(mEglDisplay, mEglSurface, mEglSurface, mEglContext);
                    appl.resize(width, height);
                }

                long time = System.currentTimeMillis();

                if (lresume) {
                    appl.resume();
                    time = frameStart = lastFrameTime = 0;
                }
                if (time - frameStart > 1000l) {
                    fps = frames;
                    frames = 0;
                    frameStart = time;
                }
                deltaTime = (time - lastFrameTime) / 1000f;
                lastFrameTime = time;

                appl.render(deltaTime);
                
                if (lpause) {
                    appl.pause();
                    eglDestroyRequest |= 1;
                }
                if (!EGL14.eglSwapBuffers(mEglDisplay, mEglSurface)) {
                    int error = EGL14.eglGetError();
                    switch (error) {
                        case EGL14.EGL_BAD_DISPLAY:
                            eglDestroyRequest |= 4;
                            break;
                        case 0x300E:
                        case EGL14.EGL_BAD_CONTEXT:
                            eglDestroyRequest |= 2;
                            break;
                        case EGL14.EGL_BAD_SURFACE:
                            eglDestroyRequest |= 1;
                            break;
                        case EGL14.EGL_BAD_NATIVE_WINDOW:
                            Log.e(TAG, "eglSwapBuffers returned EGL_BAD_NATIVE_WINDOW. tid=" + Thread.currentThread().getId());
                            break;
                        default:
                            Log.e(TAG, "eglSwapBuffers failed: " + Integer.toHexString(EGL14.eglGetError()));
                    }
                }
                frames++;
            }
        } catch (Throwable e) {
            // fall thru and exit normally
            for (StackTraceElement s : e.getStackTrace()) {
                Log.e(TAG, s.toString());
            }
            Log.e(TAG, "error " + e.getMessage());
        } finally {
            // dispose all resources
            appl.destroy();

            if (mEglSurface != null) {
                EGL14.eglMakeCurrent(mEglDisplay, EGL14.EGL_NO_SURFACE, EGL14.EGL_NO_SURFACE, EGL14.EGL_NO_CONTEXT);
                EGL14.eglDestroySurface(mEglDisplay, mEglSurface);
                mEglSurface = null;
            }
            if (mEglContext != null) {
                EGL14.eglDestroyContext(mEglDisplay, mEglContext);
                mEglContext = null;
            }
            if (mEglDisplay != null) {
                EGL14.eglTerminate(mEglDisplay);
                mEglDisplay = null;
            }
            holder.removeCallback(this);
            // end thread
            synchronized (this) {
                mExited = true;
                notifyAll();
            }
        }
    }
}
