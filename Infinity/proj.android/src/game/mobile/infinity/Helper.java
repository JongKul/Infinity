package game.mobile.infinity;

import android.os.Handler;
import android.os.Looper;
import android.widget.Toast;

public class Helper {

	private static Helper instance;
	public static Helper getInstance()	{
		if(instance == null) {
			instance  = new Helper();			
		}
		return instance;
	}
	public void alert(final String message) {
		Handler mHandler = new Handler(Looper.getMainLooper());
		mHandler.postDelayed(new Runnable() {
		@Override
		public void run() {
			Toast.makeText(Infinity.INFINITY.getApplicationContext(), 
					  message,  
	                  Toast.LENGTH_SHORT).show();
		 
		}
		}, 0);
		
		/*AlertDialog.Builder alertDialogBuilder = new AlertDialog.Builder(
				Infinity.INFINITY.getApplicationContext());
		alertDialogBuilder
		.setMessage("Click yes to exit!")
		.setCancelable(false)
		.setPositiveButton("Yes",new DialogInterface.OnClickListener() {
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
		*/
		  
	}
	public String getToken(){
		return Infinity.regId;
	}
	

}
