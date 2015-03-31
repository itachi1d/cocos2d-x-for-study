package com.example.bkw.myapplication;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.support.v4.app.FragmentActivity;
import android.support.v7.app.ActionBarActivity;
import android.util.Log;
import android.view.View;
import android.widget.Toast;

import com.facebook.FacebookException;
import com.facebook.FacebookOperationCanceledException;
import com.facebook.LoggingBehavior;
import com.facebook.Session;
import com.facebook.SessionState;
import com.facebook.Settings;
import com.facebook.UiLifecycleHelper;
import com.facebook.widget.FacebookDialog;
import com.facebook.widget.WebDialog;

/**
 * Created by bkw on 2015/3/12.
 */
public class ShareActivity extends FragmentActivity {
    private UiLifecycleHelper uiHelper;

    private Session.StatusCallback statusCallback = new Session.StatusCallback() {
        @Override
        public void call(Session session, SessionState sessionState, Exception e) {
            if (sessionState.isOpened()) {
                publishFeedDialog();
            }
        }
    };
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.share);

        uiHelper = new UiLifecycleHelper(this, null);
        uiHelper.onCreate(savedInstanceState);

    }
    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data){
        super.onActivityResult(requestCode, resultCode, data);

        uiHelper.onActivityResult(requestCode, resultCode, data, new FacebookDialog.Callback() {
            @Override
            public void onComplete(FacebookDialog.PendingCall pendingCall, Bundle bundle) {
                Log.i("onComplete", "Success");
            }

            @Override
            public void onError(FacebookDialog.PendingCall pendingCall, Exception e, Bundle bundle) {
                Log.e("Error", String.format("Error: %s", e.toString()));
            }
        });

    }

    protected void onResume(){

        super.onResume();
        uiHelper.onResume();
    }
    protected void onPause(){

        super.onPause();
        uiHelper.onPause();
    }

    public void onDestroy(){
        super.onDestroy();
        uiHelper.onDestroy();
    }

    protected void onSaveInstanceState(Bundle outState){
        super.onSaveInstanceState(outState);
        uiHelper.onSaveInstanceState(outState);

    }

    public void startShare(View view){
        //此方法必须用户已经安装facebook app才行
       /* FacebookDialog shareDialog = new FacebookDialog.ShareDialogBuilder(this)
                .setLink("https://developers.facebook.com/android")
                .build();
        uiHelper.trackPendingDialogCall(shareDialog.present());*/

        if (Session.getActiveSession() == null || !Session.getActiveSession().isOpened()) {
            Session.openActiveSession(ShareActivity.this, true, statusCallback);
        } else {
            Log.i("click", "sisi");
            publishFeedDialog();
        }


    }
    private void publishFeedDialog(){
            Bundle params = new Bundle();
            params.putString("name", "Facebook SDK for Android");
            params.putString("caption", "Build great social apps and get more installs.");
            params.putString("description", "The Facebook SDK for Android makes it easier and faster to develop Facebook integrated Android apps.");
            params.putString("link", "https://developers.facebook.com/android");
            params.putString("picture", "https://raw.github.com/fbsamples/ios-3.x-howtos/master/Images/iossdk_logo.png");
            Log.i("click", "sisi");
            WebDialog feedDialog = (
                    new WebDialog.FeedDialogBuilder(ShareActivity.this,
                            Session.getActiveSession(),
                            params))
                    .setOnCompleteListener(new WebDialog.OnCompleteListener() {

                        @Override
                        public void onComplete(Bundle values,
                                               FacebookException error) {
                            if (error == null) {
                                // When the story is posted, echo the success
                                // and the post Id.
                                final String postId = values.getString("post_id");
                                if (postId != null) {
                                    Toast.makeText(getApplicationContext(),
                                            "Posted story, id: " + postId,
                                            Toast.LENGTH_SHORT).show();
                                } else {
                                    // User clicked the Cancel button
                                    Toast.makeText(getApplicationContext(),
                                            "Publish cancelled",
                                            Toast.LENGTH_SHORT).show();
                                }
                            } else if (error instanceof FacebookOperationCanceledException) {
                                // User clicked the "x" button
                                Toast.makeText(getApplicationContext(),
                                        "Publish cancelled",
                                        Toast.LENGTH_SHORT).show();
                            } else {
                                // Generic, ex: network error
                                Toast.makeText(getApplicationContext(),
                                        "Error posting story",
                                        Toast.LENGTH_SHORT).show();
                            }
                        }

                    })
                    .build();
            feedDialog.show();

        }
}
