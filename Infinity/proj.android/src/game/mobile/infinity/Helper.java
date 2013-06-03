package game.mobile.infinity;

import android.app.AlertDialog;
import android.content.DialogInterface;
import android.widget.Toast;

public class Helper {

	private static Helper instance;
	public static Helper getInstance()	{
		if(instance == null) {
			instance  = new Helper();			
		}
		return instance;
	}
	public void alert(String message) {
		
		AlertDialog.Builder alertDialogBuilder = new AlertDialog.Builder(
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
		
		  /*Toast.makeText(Infinity.INFINITY.getApplicationContext(), 
				  message,  
                  Toast.LENGTH_SHORT).show();*/
	}
	public String getToken(){
		return Infinity.regId;
	}
	

}
