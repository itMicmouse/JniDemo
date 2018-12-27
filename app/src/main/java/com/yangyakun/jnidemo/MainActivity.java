package com.yangyakun.jnidemo;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.TextView;

import java.util.Arrays;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Example of a call to a native method
        TextView tv = (TextView) findViewById(R.id.sample_text);
        tv.setText(stringFromJNI());

        int[] abc = {1,2,3};
        String[] strings = {"yangyakun","yangjifa","yangqingchen"};
        int aNative = getNative(abc, strings);
        System.out.println("int 数组"+Arrays.toString(abc));
        System.out.println("Native 返回的"+aNative);
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();


    public native int getNative(int[] number,String[] Strings);

}
