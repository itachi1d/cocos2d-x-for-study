# 尝试导入cocoStudio2.1.5制作的动画遇到的问题以及解决方案

## 问题
1.导入代码：`	
Widget* node = static_cast<Widget*>(CSLoader::createNode ("cocos/GameScene1.csb"));
	 if (!node)
	{
		return nullptr;
	}
	this->addChild (node);`导入后出现画面plist missed的问题

## 解决方案
1.plist missed的问题因为cocostudio发布路径需要放在根目录，如果要放在下级目录，则需要在AppDelegate.cpp中的if语句之后加上`std::vector<std::string> search_path;
	search_path.push_back ("cocos");
	FileUtils::getInstance ()->setSearchPaths (search_path);`.