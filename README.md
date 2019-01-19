# wxWidgets-practice
wxWidgets+wxFormBuilder+OpenCV

## 测试环境
* wxWidgets 3.0.3
* wxFormBuilder 3.5.1
* OpenCV 3.3
* Visual Studio 2015 Community

## 文件结构说明
* common 存放所有例程共用的函数文件
* img 存放测试图片
* result存放测试结果图片
* 其余的文件夹为单独的例程代码（包含代码与fpb文件）

## 例程目录

* #### calcSquare
  计算平方数

  ![](https://github.com/xxpcb/wxWidgets-practice/blob/master/result/calcSquare.png)

* #### cameraTest
  摄像头测试

  ![](https://github.com/xxpcb/wxWidgets-practice/blob/master/result/cameraTest.jpg)

  现存一个问题：界面第一次打开无法加载相机封面图片

* #### findContours
  查找图片轮廓

  ![](https://github.com/xxpcb/wxWidgets-practice/blob/master/result/findContours.jpg)

* #### openPic
  打开图片测试

  ![](https://github.com/xxpcb/wxWidgets-practice/blob/master/result/openPic.jpg)

### 本代码的参考例程和图片来源
* wxImage与Mat格式转换参考自：[*这里的代码*](https://github.com/yan9a/wxwidgets/blob/master/minimalcv/util.h)

* 用到的测试图片来自：[*这里的代码*](https://github.com/yan9a/wxwidgets/blob/master/minimalcv/util.h)
