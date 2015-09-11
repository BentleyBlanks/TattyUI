# TattyUI

本UI框架底层渲染框架采用[nanovg](https://github.com/memononen/nanovg),采用类似浏览器WebKit的做法，将UI的样式与业务逻辑分离。

> TattyUI ver 0.0.3之前采用XML+Json+Lua的脚本配合
TattyUI ver 0.0.4之后直接采用HTML+CSS+Lua的脚本

其中感谢[ccss](https://github.com/jdeng/ccss)给我提供了非常好的使用正则表达式解析CSS的案例。

#依赖项说明
1.[GLFW](http://www.glfw.org/) ver 3.11
2.[GLEW](http://glew.sourceforge.net/) ver 1.13.0

> 依赖项已上传至Git，也可以根据自行需要更换

#构建说明
1.TattyUI采用CMake做跨平台搭建工作,支持Windows,OSX等主流OS

2.假设您构建在新文件夹build中，那么仅需在IDE中设置包含```../TattyUI```即可

#使用说明
1.脚本说明 CSS目前支持的属性已在```t2Style.cpp```声明
2.C++通过和t2DivController交互即可获取全局```<div>```列表,详情可见example

##关于作者
```cpp
int 官某某 = "Bingo";

char[] 个人博客 = "http://bentleyblanks.github.io";
```




