package org.cocos2dx.cpp;

import org.cocos2dx.lib.Cocos2dxActivity;
import org.cocos2dx.lib.Cocos2dxGLSurfaceView;

import android.content.pm.ActivityInfo;

public class BNCocos2dxActivity extends Cocos2dxActivity 
{
	public Cocos2dxGLSurfaceView onCreateView() 
    {
        Cocos2dxGLSurfaceView glSurfaceView = new Cocos2dxGLSurfaceView(this);
        //����Ϊ��ģʽ 
  		setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_PORTRAIT);
        // TestCpp should create stencil buffer
        glSurfaceView.setEGLConfigChooser(5, 6, 5, 0, 16, 8);
        //glSurfaceView.setEGLConfigChooser(8, 8, 8, 8, 16, 8);
        return glSurfaceView;  
    }
}
