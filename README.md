# mrp版手机CAPP

mrp版本实现了部分手机C的函数，具体可以看mythroad/c目录下的相关头文件说明\

## 如何编译？
1. 需要准备mrp开发环境，及安装ads1.2
2. 编译手机C:buildall.bat 编译运行器:picoc.bat

## 关于运行器打包：
需要用到两个mrp，一个是掌上e(用来打包mrp)，一个是mrprun.mrp(运行器文件)
用掌上e将mpcrun.mrp解压，替换里面的mpc.c入口文件，将assets目录需要的资源也一起添加进mrp就可以了。
运行器里面的文件除以下是必须，其它文件可以删除：

- start.mr
- cfunction.ext
- ic_launcher.bmp

## 关于将其它文件打包进mrp
- assets里面的文件都加入mrp，注意assets里面不能再创建文件夹
- png/jpg图片需要处理成bmp，另外，目前打包器只支持bmp565/bmp24位位图，可以用电脑的画图工具另存为bmp24位图片，或者可以用我提供的bmp图片转换器apk

## 版本说明
### v3003
- 新增 _PLATFORM _RUN_MODR宏定义
- 修复内存泄露问题
- 新增ex_game.h exb.h ex_math.h，实现capp大部分函数




