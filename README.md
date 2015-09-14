# TattyUI

![screenshot](https://github.com/BentleyBlanks/TattyUI/blob/master/screenshots/1.png)

本UI框架底层渲染框架采用[nanovg](https://github.com/memononen/nanovg),采用类似浏览器WebKit的做法，将UI的样式与业务逻辑分离。

TattyUI第一个较为成熟的production级的产品将会是为 [WIP2D](https://github.com/wubugui/WIP) 2D游戏引擎制作```编辑器```，尽请期待。

感谢[ccss](https://github.com/jdeng/ccss)给我提供了非常好的使用正则表达式解析CSS的案例。

> TattyUI ver 0.0.3之前采用XML+Json+Lua的脚本配合

> TattyUI ver 0.0.4之后直接采用HTML+CSS+Lua的脚本

#依赖项说明
1.[GLFW](http://www.glfw.org/) ver 3.11

2.[GLEW](http://glew.sourceforge.net/) ver 1.13.0

> 依赖项已上传至Git，也可以根据自行需要更换

#构建说明
1.TattyUI采用CMake做跨平台搭建工作,支持Windows,OSX等

2.假设您构建在新文件夹build中，那么仅需在IDE中设置包含```../TattyUI```即可

3.可自行构建```resources```文件夹用于放置资源

#使用说明
1.脚本说明 CSS目前支持的属性已在```t2Style.cpp```声明，可自行查阅

2.C++通过和t2DivController交互即可获取全局```<div>```列表,所有C++代码都会与全局表```divTable```进行交互，详情可见example。

3.TattyUI较大的采用C++11标准，在回调函数的选择上使用```std::fucntion```从而支持成员函数，函数指针，Lambda表达式等，以最大的可能模拟浏览器的样式但采用本地矢量渲染。

4.支持CSS类选择器，伪类选择器，元素选择器。

##关于作者
```cpp
int 官某某 = "Bingo";

char[] 个人博客 = "http://bentleyblanks.github.io";
```




