# 尝试导入cocoStudio制作的动画遇到的问题以及解决方案

## 问题
1.导入代码：`	ArmatureDataManager::getInstance()->addArmatureFileInfo("NewAnimation/NewAnimation.ExportJson");    
		Armature *armatureBird = Armature::create("Animation1");  
		armatureBird->setPosition(Point(visibleSize.width/2, visibleSize.height/2));  
		this->addChild(armatureBird);  
		armatureBird->getAnimation()->playByIndex(0);`运行后出错

## 解决方案
1.运行出错因为Armature *armatureBird = Armature::create("NewAnimation"); 中" "中填入的是cocostduio的项目名字，不能乱取名字或者填写动画名