
# Linux系统中的权限
Linux是一套免费使用和自由传播的类UNIX操作系统，是一个基于POSIX和Unix的多用户、多任务、支持多线程和多CPU的操作系统。

Linux系统中，一切都是文件，既然是多用户的操作系统，主要是每个用户使用自己的空间进行操作。接下来我们会介绍用户和文件的创建、使用、登录、权限等，还有就是操作系统中的环境变量如何修改和生效。

小提示:
> Linux中所有命令，都支持使用--help参数进行查看这个命令的帮助和介绍。
```
// 使用passwd作为例子
# passwd --help
用法: passwd [选项...] <帐号名称>
  -k, --keep-tokens       保持身份验证令牌不过期
  -d, --delete            删除已命名帐号的密码(只有根用户才能进行此操作)
  -l, --lock              锁定指名帐户的密码(仅限 root 用户)
  -u, --unlock            解锁指名账户的密码(仅限 root 用户)
  -e, --expire            终止指名帐户的密码(仅限 root 用户)
  -f, --force             强制执行操作
  -x, --maximum=DAYS      密码的最长有效时限(只有根用户才能进行此操作)
  -n, --minimum=DAYS      密码的最短有效时限(只有根用户才能进行此操作)
  -w, --warning=DAYS      在密码过期前多少天开始提醒用户(只有根用户才能进行此操作)
  -i, --inactive=DAYS     当密码过期后经过多少天该帐号会被禁用(只有根用户才能进行此操作)
  -S, --status            报告已命名帐号的密码状态(只有根用户才能进行此操作)
  --stdin                 从标准输入读取令牌(只有根用户才能进行此操作)

Help options:
  -?, --help              Show this help message
  --usage                 Display brief usage message
```

## 1. 用户权限
Linux系统中，跟我们使用者直接相关的有两种用户类型：
- **管理员用户**： root、sudo用户，可以操作任何本机上所有的文件，能够操作其他任何用户的文件和数据。
- **普通用户**：只能操作自己账户下的文件，一般情况下不能查看其他用户下的文件，不能修改系统文件等。

1.1 添加新用户

1. 使用useradd命令添加新用户。

```
# useradd foolcat
```
2. 设置密码：passwd，根据提示依次输入密码即可。
```
# passwd foolcat
```
3. 查看useradd的默认参数
```
# useradd -D
GROUP=100 <---> 新用户会被添加到GID为100的公共组
HOME=/home <---> 新用户的HOME目录将会位于/home
INACTIVE=-1 <--->  新用户账户密码在过期后不会被禁用
EXPIRE= <---> 新用户账户未被设置过期日期
SHELL=/bin/bash <---> 新用户账户将bash shell作为默认shell
SKEL=/etc/skel <---> 系统会将/etc/skel目录下的内容复制到用户的HOME目录下 
CREATE_MAIL_SPOOL=yes <---> 系统为该用户账户在mail目录下创建一个用于接收邮件的文件
# 
```
4. 删除用户：userdel
```
# userdel -r foolcat
```
> 不使用-r参数，只是删除用户，但是会保留目录/home/foolcat；使用-r会删除用户的对应目录/home/foolcat，-r参数一定要慎用。

5. 修改用户

常用命令：
|命令|描述|
|:---:|:---:|
|usermod|修改用户账户的字段，还可以指定主要组以及附加组的所属关系|
|passwd| 修改已有用户的密码，如果后面没有用户参数，则表示修改当前用户密码|

a. usermod

> usermod命令是用户账户修改工具中最强大的一个。它能用来修改/etc/passwd文件中的大部
分字段，只需用与想修改的字段对应的命令行参数就可以了。参数大部分跟useradd命令的参数
一样（比如，-c修改备注字段，-e修改过期日期，-g修改默认的登录组）。

除此之外，还有另外
一些可能派上用场的选项。
```
 -l修改用户账户的登录名。
 -L锁定账户，使用户无法登录。
 -p修改账户的密码。
 -U解除锁定，使用户能够登录。
```
-L选项尤其实用。它可以将账户锁定，使用户无法登录，同时无需删除账户和用户的数据。
要让账户恢复正常，只要用-U选项就行了。

b. passwd
> 如果只用passwd命令，它会改你自己的密码。系统上的任何用户都能改自己的密码，但只
有root或者其他关了员权限的用户才有权限改别人的密码。

1.3 用户组

Linux系统为了更好控制权限，使用了组的概念，多个用户可以添加到一个用户组中，一个用户也可以加入多个用户组。使用户服从组的权限，便于管理用户之间的权限。

组信息保存在系统的一个文件中。/etc/group文件包含系统上用到的每个组的信息（其实用户也有一个这样的文件）。

常用命令如下表：
|命令|描述|
|:--:|:--:|
|groupadd|创建新组；可以配合usermod命令，将用户加入组中|
|groupmod|groupmod命令可以修改已有组的GID（加-g选项）或组名（加-n选项）|

```
// 创建一个新组cat_house
# groupadd cat_house 

// 使用usermod将用户foolcat加入新组中
# usermod -G cat_house foolcat

// 将cat_house的名字修改为new_house
# groupmod -n new_house cat_house
```
1.4 其他命令

su: 切换用户，root用户切换成其他用户一般不需要密码，其他用户之间相互切换，需要待切换的用户密码。
```
// 切换成用户cat1
# su cat1

// sodu表示拥有管理员权限的用户，不需要密码
# sudo su cat2
```

## 2. 文件权限
Linux系统中万物皆文件，由于文件权限操作中，需要用到很多命令，例如：ls、cat、chmod等，文件权限会在文件的操作中进行讲解。

## 3. 环境变量

Linux由于是多用户的操作系统，因此存在两个环境变量文件，/etc/profile和.bashrc。

|文件|类型|作用域|用户|即时生效方式|
|:--:|:--:|:--:|:--:|:--:|
|/etc/profile|整个系统只有一个|一旦修改，作用域全部用户|只有管理用户和root用户能够修改|source /etc/profile|
|~/.bastrc|每个用户一个，在用户的根目录下|一旦修改作用当前用户|管理员和root用户以及当前用户可以修改|source ~/.bashrc|

临时变量：是当前终端下执行export命令，没有写入文件的命令。

例如，有些系统的终端默认是不支持中文显示的，此时如果你不想修改系统变量，可以临时执行下面的命令：
```
# export LANG="zh_CN.UTF-8"
# export SYSFONT="latarcyrheb-sun16"
# export SUPPORTED="zh_CN.UTF-8:zh_CN:zh"
```

配置Java环境变量

我们基于用户foolcat配置java环境环境，采用Jdk1.8作为例子。
```
// 1. 下载jdk，由于oracle需要登录下载，这里使用清华镜像
# cd Downloads
# wget https://mirrors.tuna.tsinghua.edu.cn/AdoptOpenJDK/8/jdk/x64/linux/OpenJDK8U-jdk_x64_linux_openj9_8u265b01_openj9-0.21.0.tar.gz

// 解压文件
# tar -zxf OpenJDK8U-jdk_x64_linux_openj9_8u265b01_openj9-0.21.0.tar.gz
// 将文件移动到指定目录~/Tools/
# mv jdk8u265-b01 ~/Tools/jdk8

// 配置环境变量, 编译.bashrc写入下面字段
# vim .bashrc

 export JAVA_HOME=~/Tools/jdk8
 export JRE_HOME=${JAVA_HOME}/jre
 export CLASSPATH=.:${JAVA_HOME}/lib:${JRE_HOME}/lib:$CLASSPATH
 export JAVA_PATH=${JAVA_HOME}/bin:${JRE_HOME}/bin
 export PATH=$PATH:${JAVA_PATH}

// 立即生效，之后输入java进行检验
# source .bashrc
```
