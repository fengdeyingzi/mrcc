
@REM 开始编译
java -jar D:\app\mrpbuilder.jar -t build ^
-Iinterpreter\src\ -Iinterpreter\syslib\ -Isrc\ -Isfw -Isfw\res ^
-Isfw\adv\ -Isfw\common\ -Isfw\gui\ -Isfw\controls\ -Isfw\net\ ^
-DSCREEN_SIZE_240320 ^
-i interpreter\src\mpcrun.c interpreter\src\momo_picoc.c interpreter\src\myfunc.c interpreter\src\picoc.c interpreter\src\platform.c interpreter\src\table.c interpreter\src\type.c interpreter\src\variable.c interpreter\src\parse.c interpreter\src\lex.c interpreter\src\include.c interpreter\src\heap.c interpreter\src\expression.c interpreter\src\clibrary.c interpreter\syslib\m_base.c interpreter\syslib\m_sound.c interpreter\syslib\m_base_i.c interpreter\syslib\m_android.c interpreter\syslib\m_graphics.c src\mrc_android.c src\mrc_graphics.c src\xl_bmp.c src\xl_debug.c src\mpc.c ^
interpreter\syslib\m_ex_game.c interpreter\syslib\m_ex_math.c interpreter\syslib\m_exb.c interpreter\syslib\m_net.c ^
interpreter\syslib\math.c src\xl_coding.c ^
mpc\Android.mk(name=Android.mk) mpc\drawbitmap.mpc(name=mpc.c) mpc\assets\btn_back.bmp.png(name=btn_back.bmp) mpc\assets\1.txt(name=1.txt) mpc\ic_launcher.bmp.png(name=ic_launcher.bmp) mpc\dimg.mpc(name=dimg.h) ^
-o picoc.mrp -gzip ^
-filename picoc.mrp -displayname 手机CAPP运行器v1.5 -vendor "风的影子" -desc "手机CAPP运行器，读取mpc.c文件进行运行" -appid 202003 -version 3005
mrpbuilder -t info -i picoc.mrp
