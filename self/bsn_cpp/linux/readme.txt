&
在命令后加,命令在后台运行

ps
列出进程

pkill 进程名
终止进程

less
输出太多，方便查看 ls | less

rm -rf 目录名
递归强制删除目录

df
查看磁盘使用情况

ls -l | less
查看目录文件 方便查看

/sbin/ldconfig -v
安装了新的库，需要更新下
链接器ld默认的目录是/lib和/usr/lib，如果放在其他路径也可以，需要让ld知道库文件在哪里。
在/etc/ld.so.conf.d/目录下新建任何以.conf为后缀的文件，在该文件中加入库文件所在的目录

g++ blocking_udp_echo_client.cpp -lboost_thread
编译c++文件，链接库libboost_thread 默认生成a.out