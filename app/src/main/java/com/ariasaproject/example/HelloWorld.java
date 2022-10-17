package com.ariasaproject.example;

import android.app.Activity;
import android.os.Bundle;
import android.view.TextView;

public class HelloWorld extends Activity {
	@Override
	public void onCreate(Bundle b) {
		setContentView(R.layout.activity_main);
		super.onCreate(b);
		((TextView)findViewById(R.id.text2)).setText(helloJNI());
	}
	
	public final native String helloJNI();
}


