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
import com.facebook.model.GraphUser;
import com.facebook.widget.FacebookDialog;
import com.facebook.widget.LoginButton;
import com.facebook.widget.WebDialog;

import android.widget.Button;
import android.widget.Toast;;
import java.util.Arrays;

public class MainActivity extends FragmentActivity {

    private  MainFragment mainFragment;
    private Session.StatusCallback statusCallback = new Session.StatusCallback() {
        @Override
        public void call(Session session, SessionState sessionState, Exception e) {
            if (sessionState.isOpened()) {

            }
        }
    };

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

        LoginButton authButton = (LoginButton)this.findViewById(R.id.authButton);
        authButton.setReadPermissions(Arrays.asList("public_profile"));

        //Button checkoutButton = (Button)this.findViewById(R.id.checkButton);

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
   /* private void onClickLogin(){
        Session session = Session.getActiveSession();
        if(!session.isOpened()&&!session.isClosed()){
            session.openForRead(new Session.OpenRequest(this).setPermissions(Arrays.asList("public_profile"))
            .setCallback(statusCallback));
        }else{
            //Session.openActiveSession(, this, true, statusCallback);
            Log.i("ss","ss");
        }
    }*/

    private class SessionStatusCallback implements Session.StatusCallback{
        public void call(Session session, SessionState state, Exception exception){
            Log.i("seccess","ss");
        }
    }

    public void checkout(View v) {
        Log.i("click", "ss");
        Intent intent = new Intent();
        intent.setClass(this, ShareActivity.class);
        startActivity(intent);
    }

}
