package com.example.bkw.myapplication;

import android.content.Intent;
import android.support.v4.app.FragmentActivity;
import android.support.v7.app.ActionBarActivity;
import android.os.Bundle;
import android.text.Layout;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.ViewGroup;
import android.support.v4.app.Fragment;

import com.facebook.AppEventsLogger;
import com.facebook.FacebookException;
import com.facebook.FacebookOperationCanceledException;
import com.facebook.Request;
import com.facebook.Session;
import com.facebook.SessionState;
import com.facebook.UiLifecycleHelper;
import com.facebook.model.GraphUser;
import com.facebook.widget.FacebookDialog;
import com.facebook.widget.LoginButton;
import com.facebook.widget.WebDialog;

import android.widget.Button;
import android.widget.Toast;;
import java.util.Arrays;

public class MainActivity extends FragmentActivity {

    private  MainFragment mainFragment;
    private LoginButton authButton;
    private UiLifecycleHelper uiHelper;
    private Session.StatusCallback statusCallback = new Session.StatusCallback() {
        @Override
        public void call(Session session, SessionState sessionState, Exception e) {
            if (!sessionState.isOpened()) {
                authButton.setText("Log out");
            }else{
                authButton.setText("Log in with facebook");
            }
        }
    };
    //这段代码是为了记住用户登入状态
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

    //private MainFragment mainFragment;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        if(savedInstanceState == null){
            mainFragment = new MainFragment();
            getSupportFragmentManager().beginTransaction().add(android.R.id.content, mainFragment)
                    .commit();
        }else{
            mainFragment = (MainFragment)getSupportFragmentManager().findFragmentById(android.R.id.content);
        }

        authButton = (LoginButton)findViewById(R.id.authButton);
        authButton.setReadPermissions(Arrays.asList("public_profile"));

        uiHelper = new UiLifecycleHelper(this, null);
        uiHelper.onCreate(savedInstanceState);

    }

    protected void onResume(){

        super.onResume();
        //AppEventsLogger.activateApp(this);
    }
    protected void onPause(){

        super.onPause();
        //AppEventsLogger.deactivateApp(this);
    }


    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.menu_main, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();

        //noinspection SimplifiableIfStatement
        if (id == R.id.action_settings) {
            return true;
        }

        return super.onOptionsItemSelected(item);
    }

    //如果不用到facebook的loginButton按钮而是使用自己自定义的按钮则让按钮注册这个事件
   /* public void onClickLogin(View v){
        if (Session.getActiveSession() == null || !Session.getActiveSession().isOpened()) {
            Session.openActiveSession(MainActivity.this, true, statusCallback);
        }else{
            Session session = Session.getActiveSession();
            if(!session.isOpened()&&!session.isClosed()){
                session.openForRead(new Session.OpenRequest(this).setPermissions(Arrays.asList("public_profile"))
                        .setCallback(statusCallback));
            }else{
                Session.openActiveSession(MainActivity.this, true, statusCallback);
                Log.i("ss","ss");
            }
        }

    }*/

    public void checkout(View v) {
        Intent intent = new Intent();
        intent.setClass(this, ShareActivity.class);
        startActivity(intent);
    }

    public void checkout2(View v) {

        Intent intent = new Intent();
        intent.setClass(this, SendWithFriendActivity.class);
        startActivity(intent);
    }

}
