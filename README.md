# Target-tracking-gimbal
嵌入式工作室招新-edge AI-Embedded vision-目标跟踪云台


## 项目概况

一个基于yolov2的利⽤PID算法控制舵机移动摄像头实现实时跟踪特定物体的云台。



### 运行环境

- 器件：K210 MaixBit，STM32F103C8T6，m12-ov5640摄像头，舵机云台，sg90舵机，STLinkV2。
- 开发环境：MaixPy IDE, Keil uVision5
- 烧录环境：kflash_gui
- 串口调试环境：XCOM

### 演示模型

演示模型为**红绿灯检测**，模型来源：https://maixhub.com/model/zoo/160

## 数据集

数据集中共有标签2个，图片202张。组成如下：

| 标签 | 训练集/验证集 | 总计 |
| ---- | ------------ | ---- |
| 红灯 | 90 / 11 | 101 |
| 绿灯 | 90 / 11 | 101 |

## 训练参数

- 图像增强
  - 随机镜像：开
  - 随机旋转：开
  - 随机模糊：开
  - 缩放方式：contain
  - 缩放尺寸：224 * 224
  - 平均值：123.5
  - 标准差：58.395

## 模型信息

- 部署平台：nncase
- 模型网络：yolov2
- 主干网络：mobilenet_0.75

## 训练参数

- 训练次数：100
- 批量大小：32
- 学习率：0.001
- 标注框限制：10
- 数据均衡：关
- 允许负样本：关

## 训练结果

在验证集上第100次训练迭代有最佳准确率：1。


## 项目描述

见提交项目中的`学习笔记.pdf`


## 项目演示

演示视频见`demo`文件夹中`demo.mp4`。

