package com.farsight.service;
import  android.util.Log; 



public class LedService {

    static {
        Log.i ( "Java Service" , "****************before load led so" );
       System.loadLibrary ( "led_runtime" );
        Log.i ( "Java Service" , "****************after load led so" );
    }

    public LedService() {
        String icount;
        Log.i ( "Java Service" , "do init Native Call" );
        _init ();
       // icount = String.valueOf(_get_count ());
       // Log.d ( "Java Service Init OK ",icount );
    }

  
    public String set_on(int arg) {
        Log.i ( "LedService,LED On", String.valueOf(arg) );
       _set_on (arg);
        Log.i ( "Java Service" , "******************led on" );
        return "led " + String.valueOf(arg) + "on";
    }
 

    public String set_off(int arg) {
    	Log.i ( "LedService,LED Off",String.valueOf(arg) );
        _set_off (arg);
    	 Log.i ( "Java Service" , "******************led off" );
        return "led " + String.valueOf(arg) + "off" ;
    }

  
    private static native boolean _init();
    private static native int _set_on(int arg);
    private static native int _set_off(int arg);
    private static native int _get_count(); 

	 
}
