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

### 3006
- 去除mrp插件化，使用自定义编译器
- 小字体替换为16号字库
- 新增mrp打包

### 3007
- 增加读取png图片功能

### 3008
- 新增toast函数
- textwh兼容性变更，textwh的宽高参数使用int32*

### 3009
- 支持自动识别编码，标题栏显示编码信息
- 优化编辑器分页算法


## 相关资料收集
pngj java的png编码库
https://github.com/leonbloy/pngj
png解码 
https://github.com/elanthis/upng
https://github.com/jcorks/tPNG
GBK编码
参考连接: http://www.cnblogs.com/tmscnz/archive/2012/12/12/2815339.html
    GBK是国家标准GB2312基础上扩容后兼容GB2312的标准。GBK的文字编码是用双字节来表示的，
    即不论中、英文字符均使用双字节来表示，为了区分中文，将其最高位都设定成1。
    GBK包含全部中文字符，是国家编码，通用性比UTF8差，不过UTF8占用的数据库比GBK大。
https://www.cnblogs.com/albertofwb/p/6149976.html