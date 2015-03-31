# 精灵执行完动作后回调函数

## 精灵执行完一个或者多个动作以后自动调用某个函数，代码如下

`Action action1 = .......
Action action2 = .......
Action action3 = .......

FiniteTimeAction * actionOne = Sequence::create(//按顺序执行完三个动作后触发回调函数
			action1, 
			action2, 
			action3,
			CallFunc::create(this, CC_CALLFUNC_SELECTOR(PlayerSprite::maxAnima_finish)),//回调的函数
			NULL);
sprite->runAction(actionOne);`