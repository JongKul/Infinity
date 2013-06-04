package game.mobile.infinity;

import java.io.File;
import java.io.FileOutputStream;
import java.io.InputStream;
import java.net.URL;
import java.util.Arrays;
import java.util.List;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

import org.apache.http.HttpEntity;
import org.apache.http.HttpResponse;
import org.apache.http.client.HttpClient;
import org.apache.http.client.methods.HttpGet;
import org.apache.http.entity.BufferedHttpEntity;
import org.apache.http.impl.client.DefaultHttpClient;
import org.cocos2dx.lib.Cocos2dxActivity;

import android.os.Bundle;
import android.os.Environment;
import android.util.Log;
import android.widget.Toast;

import com.facebook.FacebookException;
import com.facebook.FacebookRequestError;
import com.facebook.Request;
import com.facebook.Request.GraphUserCallback;
import com.facebook.Request.GraphUserListCallback;
import com.facebook.Response;
import com.facebook.Session;
import com.facebook.Session.StatusCallback;
import com.facebook.SessionState;
import com.facebook.model.GraphUser;
import com.facebook.widget.WebDialog;
import com.facebook.widget.WebDialog.OnCompleteListener;


public class FacebookManager {
	private static FacebookManager instance;
	
	private ExecutorService executor;
	private Session.StatusCallback loginStatusCallback = 
		    new SessionStatusCallback();
	public static FacebookManager getInstance()	{
		if(instance == null) {
			instance  = new FacebookManager();
			
		//	Session session = Session.getActiveSession();
		//	if(session != null)session.closeAndClearTokenInformation();
		}
		return instance;
	}
	public FacebookManager() {
		 executor = Executors.newFixedThreadPool(5);
	}
	public void login() {
		Log.d("test","login");
		Session session = Session.getActiveSession();
		
		
	    if (session != null&&!session.isOpened() && !session.isClosed()) {
	        session.openForRead(new Session.OpenRequest(Infinity.INFINITY)
	            .setPermissions(Arrays.asList("email"))
	            .setCallback(loginStatusCallback));
	    } else {
	    	
	    	session =Session.openActiveSession(Infinity.INFINITY, true,loginStatusCallback);
	    }
	}
	
	
	private class SessionStatusCallback implements StatusCallback {
		public void call(Session session, SessionState state, Exception ex) {
			Log.d("SessionStatusCallback",state.toString());
			if( ex != null)Log.d("test",ex.toString());
			if(session.isOpened()){
				Log.d("SessionStatusCallback","true");
				requestMyAccount();
			}
			else {
				Log.d("SessionStatusCallback","false");
				jniCallbackLogin(false);
				//
			}
		}
	}
	public void requestMyAccount(){
		Log.d("requestMyAccount","requestMyAccount");
		Session session = Session.getActiveSession();
		if(session.isOpened()) {
			Log.d("requestMyAccount","isOpened");
			Request.newMeRequest(session, new GraphUserCallback(){
				@Override
				public void onCompleted(GraphUser user, Response response) {
				//	Log.d("requestMyAccount","onCompleted");
					FacebookRequestError error = response.getError();
						if(error == null ) {
							String name = user.getName();
							String id = user.getId();
							
							jniSetMyAccount(name,id);
						}
						else {
							jniCallbackLogin(false);
							Log.d("error",error.toString());
						}
				}				
			}).executeAsync();
			
		}
	}
	public void requestFriends(){
		Session session = Session.getActiveSession();
		if(session.isOpened()) {
			Request.newMyFriendsRequest(session,
					new GraphUserListCallback(){

						@Override
						public void onCompleted(List<GraphUser> users,
								Response response) {
							if(response.getError()== null ) {
								for(GraphUser user : users ) {
									String name = user.getName();
									String id = user.getId();
									synchronized(this)
									{
										try {
											this.wait(1);
										} catch (InterruptedException e) {
											// TODO Auto-generated catch block
											e.printStackTrace();
										}
										jniAddFriend(name,id);
									}
								}
								Log.d("requestFriends","jniCallbackLogin");
								jniCallbackLogin(true);
								
							}
							else {
								jniCallbackLogin(false);
								Log.d("error",response.getError().toString());
							}
							
						}
				
			}).executeAsync();
		}
	}
	public void requestPicture(final String id) throws Exception {
		/*Infinity.INFINITY.runOnUiThread(new Runnable () {

			@Override
			public void run() {
				
				long contentLength= 0;
				String fbId = id;
				StringBuilder sb = new StringBuilder("https://graph.facebook.com/");
				sb.append(fbId);
				sb.append("/picture?type=normal");
				String urlString = sb.toString();
				HttpGet httpRequest;
				try {
					httpRequest = new HttpGet(new URL(urlString).toURI());
				
				HttpClient httpClient = new DefaultHttpClient();
				HttpResponse response = (HttpResponse) httpClient.execute(httpRequest);
				HttpEntity entity = response.getEntity();
				BufferedHttpEntity bufHttpEntity = new BufferedHttpEntity(entity); 
				contentLength = bufHttpEntity.getContentLength();
				InputStream is = bufHttpEntity.getContent();
				

				int nRead;
				byte[] readData = new byte[(int) contentLength];
				is.read(readData, 0, readData.length);
				Log.d("requestPicture", new Integer((int)contentLength).toString());			
				//		Bitmap bitmap = BitmapFactory.decodeStream(is);
			//	jniCallbackPicture(fbId , readData);		
				
				} catch (Exception e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				} 
				
			}
		});*/
		executor.execute(new Runnable () {

			@Override
			public void run() {
				long contentLength= 0;
				final String fbId = id;
				StringBuilder sb = new StringBuilder("https://graph.facebook.com/");
				sb.append(fbId);
				sb.append("/picture?type=normal");
				String urlString = sb.toString();
				HttpGet httpRequest;
				try {
					httpRequest = new HttpGet(new URL(urlString).toURI());
				
				HttpClient httpClient = new DefaultHttpClient();
				HttpResponse response = (HttpResponse) httpClient.execute(httpRequest);
				HttpEntity entity = response.getEntity();
				BufferedHttpEntity bufHttpEntity = new BufferedHttpEntity(entity); 
				contentLength = bufHttpEntity.getContentLength();
				InputStream is = bufHttpEntity.getContent();
				

				int nRead;
				final byte[] readData = new byte[(int) contentLength];
				is.read(readData, 0, readData.length);
				Log.d("requestPicture", new Integer((int)contentLength).toString());			
				//		Bitmap bitmap = BitmapFactory.decodeStream(is);
				((Cocos2dxActivity) Infinity.INFINITY).runOnGLThread(new Runnable(){

					@Override
					public void run() {
						// TODO Auto-generated method stub
						jniCallbackPicture(fbId , readData);
					}
					
				});
						
				
				} catch (Exception e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				} 				
			}
		});
	
/*
		long contentLength= 0;
		String fbId = id;
		StringBuilder sb = new StringBuilder("https://graph.facebook.com/");
		sb.append(fbId);
		sb.append("/picture?type=normal");
		String urlString = sb.toString();
		HttpGet httpRequest;
		try {
			httpRequest = new HttpGet(new URL(urlString).toURI());
		
		HttpClient httpClient = new DefaultHttpClient();
		HttpResponse response = (HttpResponse) httpClient.execute(httpRequest);
		HttpEntity entity = response.getEntity();
		BufferedHttpEntity bufHttpEntity = new BufferedHttpEntity(entity); 
		contentLength = bufHttpEntity.getContentLength();
		InputStream is = bufHttpEntity.getContent();
		

		int nRead;
		byte[] readData = new byte[(int) contentLength];
		is.read(readData, 0, readData.length);
		Log.d("requestPicture", new Integer((int)contentLength).toString());			
		//		Bitmap bitmap = BitmapFactory.decodeStream(is);
		jniCallbackPicture(fbId , readData);		
		
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} */
	
	}
	
	public void invite(String id) {
		Bundle params = new Bundle();
	    params.putString("title", "Othello Friends Invite");
	    params.putString("message", "Come check out my app");
	    params.putString("to", id);
	    WebDialog requestsDialog = (
	        new WebDialog.RequestsDialogBuilder(Infinity.INFINITY,
	            Session.getActiveSession(),
	            params))
	            .setOnCompleteListener(new OnCompleteListener() {

	                @Override
	                public void onComplete(Bundle values,
	                    FacebookException error) {
	                    final String requestId = values.getString("request");
	                    if (requestId != null) {
	                        Toast.makeText(Infinity.INFINITY.getApplicationContext(), 
	                            "Request sent",  
	                            Toast.LENGTH_SHORT).show();
	                    } else {
	                        Toast.makeText(Infinity.INFINITY.getApplicationContext(), 
	                            "Request cancelled", 
	                            Toast.LENGTH_SHORT).show();
	                    }
	                }

	            })
	            .build();
	    requestsDialog.show();
	}
	
	private native void jniCallbackLogin(boolean ret) ;
	
	private native void jniSetMyAccount(String name, String id);
	
	private native void jniAddFriend(String name, String id);
	
	private native void jniCallbackPicture(String id , byte[] image);
	

}
