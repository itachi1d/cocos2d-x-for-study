# ���Ե���cocoStudio2.1.5�����Ķ��������������Լ��������

## ����
1.������룺`	
Widget* node = static_cast<Widget*>(CSLoader::createNode ("cocos/GameScene1.csb"));
	 if (!node)
	{
		return nullptr;
	}
	this->addChild (node);`�������ֻ���plist missed������

## �������
1.plist missed��������Ϊcocostudio����·����Ҫ���ڸ�Ŀ¼�����Ҫ�����¼�Ŀ¼������Ҫ��AppDelegate.cpp�е�if���֮�����`std::vector<std::string> search_path;
	search_path.push_back ("cocos");
	FileUtils::getInstance ()->setSearchPaths (search_path);`.