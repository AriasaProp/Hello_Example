package com.ariasaproject.example;

import android.app.Activity;
import android.os.Bundle;
import android.widget.TextView;

public class HelloWorld extends Activity {
	static {
		System.loadLibrary("ext");
	}
	@Override
	public void onCreate(Bundle b) {
		super.onCreate(b);
		setContentView(R.layout.activity_main);
		((TextView)findViewById(R.id.text2)).setText(helloJNI());
	}
	
	public static native final String helloJNI();
}


