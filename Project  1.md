# 东南大学操作系统实践1 （张竞慧班）
实际上是一个进程隐藏的Project，本身难度不高，涉及编译内核，比较麻烦
## 实验环境
* ubuntu 22.0.4
* vmware
## 实验过程
下载内核并解压到 /usr/src 下
![Alt text](image.png)
我们可以看到 linux-6.6.4 即是解压出的源码

进入新内核增加系统调用
![Alt text](image-1.png)
**编辑系统调用表**

 首先进入系统调用表所在目录
 ```
cd arch/x86/entry/syscalls
 ```
然后进入系统调用表添加上我们的两个系统调用
```
sudo vim syscalls_64.tbl
```
![Alt text](image-2.png)
这里要注意将添加的系统调用添加到453后，蓝字其实已经说明原因
![Alt text](image-3.png)

**修改unistd.h**
![Alt text](image-15.png)
**紧接着是添加系统调用的声明**

进入所在目录
```
cd include/linux
```
修改系统调用声明文件
```
sudo vim syscalls.h
```
添加到最后即可
![Alt text](image-6.png)
**然后是实现两个系统调用的具体定义**
同样先进入所在目录
```
cd kernel
```
然后在末尾写入系统调用定义
```
sudo vim sys.c
```
![Alt text](image-18.png)
![Alt text](image-17.png)
这里要注意前缀要加上***asmlinkage***  强迫参数全部从堆栈中读取，防止从寄存器中读取导致编译优化过程中影响传参过程
**然后是在sche.h中 task_struct的定义的末尾加上hide 以及old_pid的定义**

先进入目标目录
```
cd include/linux
```
然后添加定义
```
sudo vim sched.h
```
![Alt text](image-8.png)
这里按照他的要求写以以满足 randomized_struct_fields_end的要求 使结构体对齐某个边界，增强安全性

**接着是fork.c的补充**
首先进入目标目录
```
cd kernel
```
在进入文件修改之前，可以先查询一下 copy_process在哪一行
![Alt text](image-10.png)
![Alt text](image-14.png)


**接下来编译内核**

```
make mrproper //将编译生成的文件删除
make oldconfig //将当前系统应用的内核配置应用到新内核中
```
然后将.config文件中的两行内容置空
```
CONFIG_SYSTEM_TRUSTED_KEYS=""
CONFIG_SYSTEM_REVOCATION_KEYS=""
```
接下来重新构建整个内核
```
make all -j4 //4为线程数，这点要根据实际硬件处理器核数来调整以加速编译
```
接下来将编译好的内核安装到指定目录
```
make modules_install
```
接下来将编译生成的内核安装到系统中
```
make install
```
紧接着reboot即可使用新内核了