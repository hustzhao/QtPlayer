﻿# QtPlayer

## 我们要开始学习播放器了！！！
## 我们要开始学习播放器了！！！
## 我们要开始学习播放器了！！！
##  

重要的事情说三遍，其实应该说N遍，因为想学习播放相关知识已经很久了。
Tiger在11年的时候就介绍了FFmpeg，自己也比较感兴趣，但是到现在已经7年了，中间断断续续的学习，每次都是入门的学习。

借用网上的一句话：

***人体的细胞会新陈代谢，每三个月会替换一次，随着旧细胞的死去，新细胞华丽诞生。由于不同细胞代谢的时间和间隔的不同，将一身细胞全部换掉。需要七年，也就是说，在生理上，我们每七年就是另外一个人。你就是你，但你也不是你了***

现在我们重新学习，并尝试写一段教程，一是为了锻炼自己的能力，二是为了大家一块学习。

教程没有视频形式，只在是github的图文教程，因为我的声音很不好听，至少我这么认为。

图文教程和源代码都会及时的上传github，每一个阶段的“产品”都会及时的创建分支进行备份。master永远是开发分支。

初步的工程是基于Windows + QT + FFmpeg + SDL2，以后会向Linux平台移植。都有的代码和资料都来源与网络，能记住出处的地方都会有链接。

Windows使用的Windows7(10)，QT使用的5.11.0,FFmpeg使用的是(未知，因为直接搬运别人的代码，后期升级到最新版本),SDL是SDL2

教程中一些基本的流程操作就不做描述了，只记录关键步骤。


第一步，创建基本的播放界面

[PlayerBase](doc/PlayerBase.md)

2018/6/25 今天Windows 10崩溃了，现在还在重置，所以还是切换到ubuntu进行开发吧，windows伤不起

/usr/bin/x86_64-linux-gnu-ld: cannot find -lGL
sudo apt-get install libgl1-mesa-dev 
https://cn.aliyun.com/jiaocheng/128675.html
