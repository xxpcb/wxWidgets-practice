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
* ForTest存放尚未完善的测试代码
* 其余的文件夹为单独的例程代码（包含代码与fpb文件）

## 例程目录

* #### calcSquare
  计算平方数

  ![](./result/calcSquare.png)

* #### cameraTest
  摄像头测试

  ![](./result/cameraTest.jpg)


* #### findContours
  查找图片轮廓

  ![](./result/findContours.jpg)

* #### openPic
  打开图片测试

  ![](./result/openPic.jpg)
  
* #### openBigPic
  打开大尺寸图片测试（滚动窗口）

  ![](./result/openBigPic.jpg)
  
* #### picAdaption
  图像铺满窗口与自适应窗口

  ![](./result/picAdaption.png)

* #### serialTest
  串口测试

  ![](./result/serialTest.png)
  
* #### cvThread
  OpenCV多线程测试

  ![](./result/cvThread.png)
  
* #### wxMathPlot
  MathPlot二维图形显示测试
  
  <div align="left"> <img src = "./result/mathplot.gif" width = '500' /></div>
  
* #### socketTest
  wxSocket的测试，基于wxWidgets官方sockets例程，重新使用wxFormBuilder设计GUI，并添加基于TCP协议的文件传输功能
  
  <div align="left"> <img src = "./result/socket.png" width = '800' /></div>

### 本代码的参考例程和图片来源
* wxImage与Mat格式转换参考自：[*这里的代码*](https://github.com/yan9a/wxwidgets/blob/master/minimalcv/util.h)

* 用到的测试图片来自：[*这里的图片*](https://github.com/SSARCandy/Coherent-Line-Drawing/tree/master/data)
