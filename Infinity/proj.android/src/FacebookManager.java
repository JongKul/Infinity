import java.io.InputStream;
import java.net.URL;
import java.util.Arrays;
import java.util.List;

import org.apache.http.HttpEntity;
import org.apache.http.HttpResponse;
import org.apache.http.client.HttpClient;
import org.apache.http.client.methods.HttpGet;
import org.apache.http.entity.BufferedHttpEntity;
import org.apache.http.impl.client.DefaultHttpClient;

import android.app.Activity;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.drawable.BitmapDrawable;

import com.facebook.Request;
import com.facebook.Request.GraphUserCallback;
import com.facebook.Request.GraphUserListCallback;
import com.facebook.Response;
import com.facebook.Session;
import com.facebook.Session.StatusCallback;
import com.facebook.SessionState;
import com.facebook.model.GraphUser;


public class FacebookManager {
	private static FacebookManager instance;
	
	private Session.StatusCallback loginStatusCallback = 
		    new SessionStatusCallback();
	public static FacebookManager getInstance()	{
		if(instance == null) {
			instance  = new FacebookManager();
			Session session = Session.getActiveSession();
			session.closeAndClearTokenInformation();
		}
		return instance;
	}
	public FacebookManager() {
		
	}
	public void login(Activity activity, StatusCallback callback) {
		Session session = Session.getActiveSession();
	    if (!session.isOpened() && !session.isClosed()) {
	        session.openForRead(new Session.OpenRequest(activity)
	            .setPermissions(Arrays.asList("basic_info"))
	            .setCallback(loginStatusCallback));
	    } else {
	        Session.openActiveSession(activity, true,loginStatusCallback);
	    }
	}
	
	private class SessionStatusCallback implements StatusCallback {
		public void call(Session session, SessionState state, Exception ex) {
			if(session.isOpened()){
				
			}
			else {
				
			}
		}
	}
	public void requestMyAccount(){
		Session session = Session.getActiveSession();
		if(session.isOpened()) {
			Request.newMeRequest(session, new GraphUserCallback(){
				@Override
				public void onCompleted(GraphUser user, Response response) {
						String name = user.getName();
						String id = user.getId();
					
				}				
			});
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
							for(GraphUser user : users ) {
								String name = user.getName();
								String id = user.getId();
							}
							
						}
				
			});
		}
	}
	public void requestPicture(String id) throws Exception {
		StringBuilder sb = new StringBuilder("https://graph.facebook.com/");
		sb.append(id);
		sb.append("/picture?type=normal");
		String urlString = sb.toString();
		HttpGet httpRequest = new HttpGet(new URL(urlString).toURI());
		HttpClient httpClient = new DefaultHttpClient();
		HttpResponse response = (HttpResponse) httpClient.execute(httpRequest);
		HttpEntity entity = response.getEntity();
		BufferedHttpEntity bufHttpEntity = new BufferedHttpEntity(entity); 
		final long contentLength = bufHttpEntity.getContentLength();
		InputStream is = bufHttpEntity.getContent();
		Bitmap bitmap = BitmapFactory.decodeStream(is);
		
	}
	
	

}
