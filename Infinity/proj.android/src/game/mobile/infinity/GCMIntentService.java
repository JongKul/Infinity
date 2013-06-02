package game.mobile.infinity;


import android.app.Notification;
import android.app.NotificationManager;
import android.app.PendingIntent;
import android.content.Context;
import android.content.Intent;
import android.util.Log;

import com.google.android.gcm.GCMBaseIntentService;


public class GCMIntentService extends GCMBaseIntentService {

	public GCMIntentService() {
		// TODO Auto-generated constructor stub
	}

	public GCMIntentService(String... senderIds) {
		super(senderIds);
		// TODO Auto-generated constructor stub
	}

	@Override
	protected void onError(Context arg0, String arg1) {
		// TODO Auto-generated method stub

	}

	@Override
	protected void onMessage(Context context, Intent message) {

        
		if(message == null)
			return;
		final String gcmMsg =  message.getStringExtra("alert");
		generateNotification(context, gcmMsg);
	}

	@Override
	protected void onRegistered(Context arg0, String registrationId) {
		Infinity.regId = registrationId;	
		Log.d("GCMIntentService", registrationId);
	}

	@Override
	protected void onUnregistered(Context arg0, String arg1) {
		// TODO Auto-generated method stub

	}
	  private static void generateNotification(Context context, String message) {
			int icon = R.drawable.icon;
	        long when = System.currentTimeMillis();
	        NotificationManager notificationManager = (NotificationManager)
	                context.getSystemService(Context.NOTIFICATION_SERVICE);
	        Notification notification = new Notification(icon, message, when);
	        String title = context.getString(R.string.app_name);
	        Intent notificationIntent = new Intent(context, Infinity.class);
	        // set intent so it does not start a new activity
	        notificationIntent.setFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP |
	                Intent.FLAG_ACTIVITY_SINGLE_TOP);
	        PendingIntent intent =
	                PendingIntent.getActivity(context, 0, notificationIntent, 0);
	        notification.setLatestEventInfo(context, title, message, intent);
	        notification.flags |= Notification.FLAG_AUTO_CANCEL;
	        notificationManager.notify(0, notification);
	    }

}
