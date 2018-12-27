package com.yangyakun.jnidemo;

import android.util.Log;

public class Bean {

    public Bean(int number) {
        this.number = number;
    }

    private static final String TAG = "Bean";
    private int number;

    public int getNumber() {
        return number;
    }

    public void setNumber(int number) {
        this.number = number;
    }

    @Override
    public String toString() {
        return "Bean{" +
                "number=" + number +
                '}';
    }

    public static void printinfo(String name){
        Log.e(TAG, "printinfo: "+ name);
    }

    public static void printInfo(Bean bean){
        Log.e(TAG, "printInfo: "+bean.toString() );
    }
}
