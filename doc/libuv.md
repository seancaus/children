libuv是一个基于事件的异步IO库，来自node.js项目。

libuv提供了Makefile.mingw，供MingW编译，由其中的规则我们可以得到一下编译步骤：

cd libuv/src

gcc  -c  *.c  -I../include -I./

cd win

gcc  -c  *.c   -I../../include  -I../  -I./

cd ../../

mingw32-make -f Makefile.mingw

最终在根目录下生成静态库libuv.a

需要注意的是libuv依赖库ws2_32.lib Iphlpapi.lib Psapi.lib Userenv.lib