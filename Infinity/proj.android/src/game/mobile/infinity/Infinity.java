/****************************************************************************
Copyright (c) 2010-2011 cocos2d-x.org

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
package game.mobile.infinity;

import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;

import org.cocos2dx.lib.Cocos2dxActivity;
import org.cocos2dx.lib.Cocos2dxGLSurfaceView;

import android.app.Activity;
import android.app.AlertDialog;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager;
import android.content.pm.PackageManager.NameNotFoundException;
import android.content.pm.Signature;
import android.os.Bundle;
import android.util.Base64;
import android.util.Log;
import android.view.KeyEvent;

import com.facebook.Session;

public class Infinity extends Cocos2dxActivity{
	public static Activity INFINITY;
	
	
	

	protected void onCreate(Bundle savedInstanceState){
		super.onCreate(savedInstanceState);	
		 Log.d("onCreate:", "onCreate");
		INFINITY = this;
		try {
		    PackageInfo info = getPackageManager().getPackageInfo(
		          "game.mobile.infinity", PackageManager.GET_SIGNATURES);
		    for (Signature signature : info.signatures) 
		        {
		           MessageDigest md = MessageDigest.getInstance("SHA");
		           md.update(signature.toByteArray());
		           Log.d("KeyHash:", Base64.encodeToString(md.digest(), Base64.DEFAULT));
		        }
		    
		
		} catch (NameNotFoundException ex) {
		} catch (NoSuchAlgorithmException ex) {
		}
		
	}

    public Cocos2dxGLSurfaceView onCreateView() {
    	Cocos2dxGLSurfaceView glSurfaceView = new Cocos2dxGLSurfaceView(this);
    	// Infinity should create stencil buffer
    	glSurfaceView.setEGLConfigChooser(5, 6, 5, 0, 16, 8);
    	
    	return glSurfaceView;
    }
    public void onActivityResult(int requestCode, int resultCode, Intent data) {
    	  super.onActivityResult(requestCode, resultCode, data);
    	  Session.getActiveSession().onActivityResult(this, requestCode, resultCode, data);
    }

    public void onBackPressed() {
		
	    	Log.d("onBackPressed","onBackPressed");
	    	AlertDialog.Builder alertDialogBuilder = new AlertDialog.Builder(
					this);
			alertDialogBuilder
			.setMessage("Do you want to exit?")			
			.setPositiveButton("Yes",new DialogInterface.OnClickListener() {
				public void onClick(DialogInterface dialog,int id) {
					// if this button is clicked, close
					// current activity
					android.os.Process.killProcess(android.os.Process.myPid());
					
				}
			  }).setNegativeButton("No", new DialogInterface.OnClickListener() {
				public void onClick(DialogInterface dialog,int id) {
					// if this button is clicked, close
					// current activity
					dialog.cancel();
				}
			  });
			
				// create alert dialog
			  AlertDialog alertDialog = alertDialogBuilder.create();
		
				// show it
			  alertDialog.show();
	    

	}
    static {
        System.loadLibrary("cocos2dcpp");
    }     
}
