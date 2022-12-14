# RecoilAssetsImporter是一个用来绘制并保存后坐力数据的插件，原生开发于UE5.0.3版本
该插件允许你在引擎中创建后坐力资产，或者将外部的后坐力数据导入

## 使用方法
在引擎Content Browser中右键可以找到创建后坐力资产的地方
![image](https://user-images.githubusercontent.com/103988839/196999943-86fff8a6-2bb2-44bc-957c-638eb93873f8.png)

创建后，打开对应的后坐力资产，可以看到绘制面板，鼠标左键可以添加新点，右键删除最后一个添加的点，右键推拽移动视图，鼠标滚轮缩放视图
![image](https://user-images.githubusercontent.com/103988839/197000214-6e56bd1c-5994-4925-80ad-f2243af1fe78.png)

在编辑器偏好设置->插件->Recoil Assets Importer Setting中可以对插件的基础设置进行修改
![image](https://user-images.githubusercontent.com/103988839/197000452-bd7911fb-cb40-45e2-aebe-a37fe4751d58.png)

## 外部后坐力数据导入
后缀为.recoilassets的文件可以直接拖入引擎，会自动被引擎处理为一个后坐力资产，这种文件为用空格隔开的浮点数
如文件ra_ak47.recoilassets，其内容为:
0.25 0.15 0.45 0.35
则导入引擎后，其绝对后坐力即为第一发{0.25, 0.15}，第二发{0.45, 0.35}

## 说明
插件只是提供数据支持，方便去绘制数据，插件并不提供后坐力解决方案，你仍然需要根据数据去实现自己的后坐力方案，且插件只是针对于View kick，我们不希望看到千篇一律的后坐力表现，但我们希望本插件能优化您的工作流，如果你正在制作一款采用模板后坐力，或许还有随机扰动而非完全随机后坐力的游戏，那么本插件可以帮助节省您的开发时间。
