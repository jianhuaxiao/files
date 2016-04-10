
package com.farsight.Resource;
import com.farsight.res.R;

import com.farsight.service.LedService;

import android.content.Context;
import android.content.DialogInterface;
import android.app.Activity;
import android.app.AlertDialog;
import android.app.AlertDialog.Builder;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.util.Log;
import android.widget.EditText;
import android.widget.ImageButton;
import android.hardware.SensorManager;
import android.hardware.SensorListener;
import android.widget.Button;
import android.view.KeyEvent;
import android.view.View;
import android.view.View.OnClickListener;
public class Mainmenu extends Activity {

	final String tag = "farsight.res";

	ImageButton btn0;
	
	static LedService led_srv;

	static boolean iflag = false;


	protected void onCreate(Bundle savedInstanceState) {  
		super.onCreate(savedInstanceState);  
		setContentView(R.layout.main);

		  led_srv = new LedService();

		  
	         btn0 = (ImageButton)this.findViewById(R.id.imageButton1);
	      
 
	         this.btn0.setOnClickListener(new OnClickListener(){
	         	public void onClick(View v){
	         	     String title = new String();
	         	     if (iflag) {
	         	          title = led_srv.set_on(1);
	         	          setTitle(title);
	         	         btn0.setImageResource(R.drawable.bulb_on);
	         	          iflag = false;
	         	        } else {
	         	           title = led_srv.set_off(1);
	         	          setTitle(title);
	         	         btn0.setImageResource(R.drawable.bulb_off);
	         	           iflag = true;
	         	        }        		
	 			}        	
	         });
	         
	   
	   
	       
	      
	}

	
		protected void onResume() {
			super.onResume();	
		
		}


		protected void onStop() {
			
			super.onStop();
		}


}

