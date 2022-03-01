
@REM 开始编译
java -jar D:\app\mrpbuilder.jar -t build ^
-Iinterpreter\src\ -Iinterpreter\syslib\ -Isrc\ -Isfw -Isfw\res ^
-Isfw\adv\ -Isfw\common\ -Isfw\gui\ -Isfw\controls\ -Isfw\net\ -Isrc\tPNG\ ^
-DSCREEN_SIZE_240320 -DC_RUN ^
-i ^
 sfw\common\string.c ^
 sfw\gui\bmp.c ^
 sfw\gui\gal.c ^
 sfw\gui\i18n.c ^
 sfw\gui\platform.c ^
 sfw\gui\rect.c ^
 sfw\gui\window.c ^
 sfw\controls\smp.c ^
 sfw\controls\smp_edit.c ^
 sfw\controls\smp_list.c ^
 sfw\controls\smp_menu.c ^
 sfw\controls\smp_menuwnd.c ^
 sfw\controls\smp_msgbox.c ^
 sfw\controls\smp_scrollbar.c ^
 sfw\controls\smp_textinfo.c ^
 sfw\controls\smp_toolbar.c ^
 sfw\controls\smp_progbar.c ^
 sfw\controls\smp_titlebar.c ^
 sfw\controls\smp_inputbox.c ^
 src\mrc_skyfont.c ^
 src\topwnd.c ^
 src\application.c ^
 src\mainwnd.c ^
 src\momo.c ^
 src\help.c ^
 src\opendlg.c ^
 interpreter\src\myfunc.c ^
 interpreter\src\picoc.c ^
 interpreter\src\platform.c ^
 interpreter\src\table.c ^
 interpreter\src\type.c ^
 interpreter\src\variable.c ^
 interpreter\src\parse.c ^
 interpreter\src\lex.c ^
 interpreter\src\include.c ^
 interpreter\src\heap.c ^
 interpreter\src\expression.c ^
 interpreter\src\clibrary.c ^
 interpreter\syslib\m_base.c ^
 interpreter\syslib\m_ctype.c ^
 interpreter\syslib\m_sound.c ^
 interpreter\syslib\m_base_i.c ^
 src\mrc_graphics.c ^
 src\mrc_android.c ^
 src\xl_bmp.c ^
 interpreter\syslib\m_android.c ^
 interpreter\syslib\m_graphics.c ^
 src\xl_debug.c ^
 src\mpc.c ^
 interpreter\syslib\m_ex_game.c ^
 interpreter\syslib\m_ex_math.c ^
 interpreter\syslib\m_exb.c ^
 interpreter\syslib\m_net.c ^
 interpreter\syslib\math.c ^
 src\xl_coding.c src\mrp.c src\FileRW.c src\tPNG\tpng.c ^
 sfw\res\res_lang0.rc ^
 sfw\res\bmp\folder.bmp ^
 sfw\res\bmp\file.bmp ^
 sfw\res\head ^
 help\base.h(name=base_h) ^
 help\sound.h(name=sound_h) ^
 help\net.h(name=net_h) ^
 help\t ^
 help\欢迎.txt(name=hellow) ^
 help\bat.txt(name=bat) ^
 help\更新说明.txt(name=updata) ^
 help\base_i.h(name=base_i_h) ^
 help\android.h(name=android.h) ^
 help\graphics.h(name=graphics.h) ^
 help\demo\BMP图片显示.txt(name=11) ^
 help\demo\helloworld.h(name=12) ^
 help\demo\helloworld.txt(name=13) ^
 help\demo\MP3播放.txt(name=14) ^
 help\demo\unicode转gb2312.txt(name=15) ^
 help\demo\编辑框.txt(name=16) ^
 help\demo\菜单.txt(name=17) ^
 help\demo\定时器.txt(name=18) ^
 help\demo\对话框，文件查找.txt(name=19) ^
 help\demo\内存与震动.txt(name=20) ^
 help\demo\屏幕坐标.txt(name=21) ^
 help\demo\时间日期.txt(name=22) ^
 help\demo\数组与排序.txt(name=23) ^
 help\demo\贪吃蛇.txt(name=24) ^
 run.mrp(name=run.mrp) ^
-o capp.mrp -gzip -bmp565 ^
-filename mrcc.mrp -displayname "手机CAPP_1.7 mrp版" -vendor "风的影子" -desc "根据冒泡开发实验系统修改而来 增加内存 新增头文件 mrpoid专用" -appid 111210 -version 3007
@REM mrpbuilder -t info -i capp.mrp
@REM start capp.mrp