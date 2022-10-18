package com.ariasaproject.example;

import android.content.Context;
import android.graphics.PixelFormat;
import android.opengl.GLSurfaceView;
import android.util.AttributeSet;
import android.util.Log;
import android.view.KeyEvent;
import android.view.MotionEvent;
/*
import javax.microedition.khronos.egl.EGL10;
import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.egl.EGLContext;
import javax.microedition.khronos.egl.EGLDisplay;
*/

import android.app.Activity;
import android.app.ActivityManager;
import android.content.Context;
import android.content.pm.ConfigurationInfo;
import android.content.res.AssetFileDescriptor;
import android.content.res.Configuration;
import android.media.AudioAttributes;
import android.media.AudioManager;
import android.media.MediaPlayer;
import android.media.SoundPool;
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

public class HelloWorld extends Activity implements Callback, Runnable {
    static {
        System.loadLibrary("ext");
    }
    public static final String TAG = "Hello World";

    // lifecycle loop peoperties
    Thread mainTGFThread;
    private SurfaceHolder holder;
    private final enum threadState { None, Resume, Resize, Pause, Destroy };
    volatile boolean resume, pause, resize, destroy;
    volatile boolean hasSurface;
    int mayorV, minorV;
    int width, height;
    boolean mExited = false;
    
    @Override
    public void onCreate(Bundle b) {
        super.onCreate(b);
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
        
	      // for main thread loop
        this.holder = view.getHolder();
        mainTGFThread = new Thread(this, "GLThread");
        mainTGFThread.start();
    }
    
    @Override
    protected synchronized void onResume() {
    		resume = true;
    }
    
    @Override
    protected synchronized void onPause() {
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
        } else {
        		pause = true;
    				notifyAll();
        		while (!mExited && pause) {
                try {
                    wait();
                } catch (InterruptedException ex) {
                    Thread.currentThread().interrupt();
                }
            }
        }
    }
    private static class ListenerAppl {
	    	public void create () {
	    		recreate();
	    	}
	    	public void resume() {
	    		
	    	}
        public void resize(int width, int height) {
            GLES30.glViewport(0, 0, width, height);
        }
        public void recreate() {
  					GLES30.glClearColor(1, 0, 1, 1);
            //init();
        }
        public void render() {
        		GLES30.glClear(GLES30.GL_COLOR_BUFFER_BIT);
            //step();
        }
        public void pause() {
        	
        }
        public void destroy() {
        	
        }
    }
    
    public static native final void init();
    public static native final void resize(int w, int h);
    public static native final void step();
   
   
    @Override
    public synchronized void surfaceCreated(SurfaceHolder holder) {
        // fall thru surfaceChanged
        hasSurface = true;
    }

    @Override
    public synchronized void surfaceChanged(SurfaceHolder holder, int format, int w, int h) {
        width = w;
        height = h;
        resize = true;
        notifyAll();
        while (!mExited && resize) {
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

    // main loop
    @Override
    public void run() {
        holder.addCallback(this);

        EGLDisplay mEglDisplay = null;
        EGLSurface mEglSurface = null;
        EGLConfig mEglConfig = null;
        EGLContext mEglContext = null;
        ListenerAppl appl = new ListenerAppl();
        try {
            byte eglDestroyRequest = 0;// to destroy egl surface, egl contex, egl display, ?....
            boolean newContext = true, // indicator
                    created = false, lrunning = true, lresize, lresume = false, lpause = false;// on running state
            while (!destroy) {
                synchronized (this) {
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
                    //after Rendererr
                    //request procces
                    if (lpause && pause) {
                    	pause = false;
                    	lrunning = false;
                    }
                    else
                    	lrunning = true;
                    lpause = pause;
                    if (lresume && resume) resume = false;
                    lresume = resume;
                    if (lresize && resize) resize = false;
                    lresize = resize; 
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
                        newContext = false;
                    }
                }
                if (lresize) {
                    EGL14.eglMakeCurrent(mEglDisplay, EGL14.EGL_NO_SURFACE, EGL14.EGL_NO_SURFACE, EGL14.EGL_NO_CONTEXT);
                    EGL14.eglMakeCurrent(mEglDisplay, mEglSurface, mEglSurface, mEglContext);
                    appl.resize(width, height);
                }
 
                if (lresume) {
                    appl.resume();
                }
                appl.render();
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
            }
        } catch (Throwable e) {
            // fall thru and exit normally
            for (StackTraceElement s : e.getStackTrace()) {
                Log.e(TAG, s.toString());
            }
            Log.e(TAG, "error " + e.getMessage());
        } finally {
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
