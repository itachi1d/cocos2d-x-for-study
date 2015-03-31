package com.example.bkw.myapplication;

import android.net.Uri;
import android.os.Bundle;
import android.support.v4.app.FragmentActivity;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.Toast;

import com.facebook.FacebookException;
import com.facebook.FacebookOperationCanceledException;
import com.facebook.Session;
import com.facebook.SessionState;
import com.facebook.widget.LoginButton;
import com.facebook.widget.WebDialog;

import java.util.Arrays;

/**
 * Created by bkw on 2015/3/13.
 */
public class SendWithFriendActivity extends FragmentActivity {
    private Button sendRequestButton;
    private String requestId;

    private Session.StatusCallback statusCallback = new Session.StatusCallback() {
        @Override
        public void call(Session session, SessionState state, Exception e) {
            if (state.isOpened()) {
                sendRequestButton.setVisibility(View.VISIBLE);
            } else if (state.isClosed()) {
                sendRequestButton.setVisibility(View.INVISIBLE);
            }
        }
    };


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.send);

        sendRequestButton = (Button) findViewById(R.id.sendRequestButton);
        sendRequestButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if (Session.getActiveSession() == null || !Session.getActiveSession().isOpened()) {
                    Session.openActiveSession(SendWithFriendActivity.this, true, statusCallback);
                } else {
                    Log.i("click", "sisi");
                    sendRequestDialog();
                }
            }
        });
        //判断是否是登入状态
        if (Session.getActiveSession() == null || !Session.getActiveSession().isOpened()) {
            sendRequestButton.setVisibility(View.INVISIBLE);
        } else {
            sendRequestButton.setVisibility(View.VISIBLE);
        }

    }

    private void sendRequestDialog() {
        Bundle params = new Bundle();
        params.putString("message", "Learn how to make your Android apps social");
        params.putString("data", "params.putString(\"data\",\n" +
                "        \"{\\\"badge_of_awesomeness\\\":\\\"1\\\",\" +\n" +
                "        \"\\\"social_karma\\\":\\\"5\\\"}\");");

        WebDialog requestsDialog = (
                new WebDialog.RequestsDialogBuilder(SendWithFriendActivity.this,
                        Session.getActiveSession(),
                        params))
                .setOnCompleteListener(new WebDialog.OnCompleteListener() {

                    @Override
                    public void onComplete(Bundle values,
                                           FacebookException error) {
                        if (error != null) {
                            if (error instanceof FacebookOperationCanceledException) {
                                Toast.makeText(getApplicationContext().getApplicationContext(),
                                        "Request cancelled",
                                        Toast.LENGTH_SHORT).show();
                            } else {
                                Toast.makeText(getApplicationContext().getApplicationContext(),
                                        "Network Error",
                                        Toast.LENGTH_SHORT).show();
                            }
                        } else {
                            final String requestId = values.getString("request");
                            if (requestId != null) {
                                Toast.makeText(getApplicationContext().getApplicationContext(),
                                        "Request sent",
                                        Toast.LENGTH_SHORT).show();
                            } else {
                                Toast.makeText(getApplicationContext().getApplicationContext(),
                                        "Request cancelled",
                                        Toast.LENGTH_SHORT).show();
                            }
                        }
                    }

                })
                .build();
        requestsDialog.show();
    }
}
