# ����ִ���궯����ص�����

## ����ִ����һ�����߶�������Ժ��Զ�����ĳ����������������

`Action action1 = .......
Action action2 = .......
Action action3 = .......

FiniteTimeAction * actionOne = Sequence::create(//��˳��ִ�������������󴥷��ص�����
			action1, 
			action2, 
			action3,
			CallFunc::create(this, CC_CALLFUNC_SELECTOR(PlayerSprite::maxAnima_finish)),//�ص��ĺ���
			NULL);
sprite->runAction(actionOne);`