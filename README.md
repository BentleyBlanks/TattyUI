# TattyUI

![screenshot](https://github.com/BentleyBlanks/TattyUI/blob/master/screenshots/1.png?raw=true)

本UI框架底层渲染框架采用[nanovg](https://github.com/memononen/nanovg),采用类似浏览器WebKit的做法，将UI的样式与业务逻辑分离。本质上是一个简易的浏览器内核实现。

TattyUI第一个较为成熟的production级的产品将会是为 [WIP2D](https://github.com/wubugui/WIP) 2D游戏引擎制作```编辑器```，尽请期待。

底层[CSS解析器](https://github.com/BentleyBlanks/t2CSSPareser)为使用Flex+Bison，借鉴[Webkit](https://www.webkit.org/)与[W3C](http://www.w3.org/)中CSS2.0实现，详见[t2CSSParser](https://github.com/BentleyBlanks/t2CSSPareser)介绍。

#依赖项说明
1.[GLFW](http://www.glfw.org/) ver 3.11

2.[GLEW](http://glew.sourceforge.net/) ver 1.13.0

3.[Gumbo](https://github.com/google/gumbo-parser) 

4.[t3DataStructures](https://github.com/BentleyBlanks/t3DataStructures) ver 1.0

5.[nanovg](https://github.com/memononen/nanovg)

> 依赖项已附带至Git，也可以根据需要自行更换

#构建说明
1.TattyUI采用CMake做跨平台搭建工作,支持Windows,OSX等

2.假设您构建在新文件夹build中，那么仅需在IDE中设置包含```../TattyUI```即可

3.可自行构建```resources```文件夹用于放置资源

#使用说明
1.脚本说明 CSS目前支持的属性已在```t2Style.cpp```声明，可自行查阅

2.C++通过和t2DivController交互即可获取全局```<div>```列表,所有C++代码都会与全局表```divTable```进行交互，详情可见example。

3.TattyUI较大的采用C++11标准，在回调函数的选择上使用```std::fucntion```从而支持成员函数，函数指针，Lambda表达式等，以最大的可能模拟浏览器的样式但采用本地矢量渲染。

4.支持CSS类选择器，伪类选择器，元素选择器。元素选择器将会在未来全面支持CSS3步骤中添加。即将封装完毕t2CSSParser,转而新建为一个独立分支。

5.支持大部分CSS2.0语法，部分未支持的语法规则已在[t2CSSParser](https://github.com/BentleyBlanks/t2CSSPareser)简介中给出

#版本说明
TattyUI ver 0.0.7 中感谢[ccss](https://github.com/jdeng/ccss)给我提供了非常好的使用正则表达式解析CSS的案例。

TattyUI ver 0.0.3 之前采用XML+Json+Lua的脚本配合

TattyUI ver 0.0.4 之后直接采用HTML+CSS+Lua的脚本

##关于作者
```cpp
int 官某某 = "Bingo";

char[] 个人博客 = "http://bentleyblanks.github.io";
```




