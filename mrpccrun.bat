
@REM ��ʼ����
java -jar D:\app\mrpbuilder.jar -t build ^
-Iinterpreter\src\ -Iinterpreter\syslib\ -Isrc\ -Isfw -Isfw\res ^
-Isfw\adv\ -Isfw\common\ -Isfw\gui\ -Isfw\controls\ -Isfw\net\ -Isrc\tPNG\ -Isrc\http\ ^
-DSCREEN_SIZE_240320 ^
-i ^
src\http\array_state.c src\http\buffer.c src\http\httpclient.c ^
interpreter\src\mpcrun.c interpreter\src\momo_picoc.c interpreter\src\myfunc.c interpreter\src\picoc.c interpreter\src\platform.c interpreter\src\table.c interpreter\src\type.c interpreter\src\variable.c interpreter\src\parse.c interpreter\src\lex.c interpreter\src\include.c interpreter\src\heap.c interpreter\src\expression.c interpreter\src\clibrary.c interpreter\syslib\m_base.c interpreter\syslib\m_sound.c interpreter\syslib\m_base_i.c interpreter\syslib\m_android.c interpreter\syslib\m_graphics.c src\mrc_android.c src\mrc_graphics.c src\xl_bmp.c src\xl_debug.c src\mpc.c ^
interpreter\syslib\m_ex_game.c interpreter\syslib\m_ex_math.c interpreter\syslib\m_exb.c interpreter\syslib\m_net.c ^
interpreter\syslib\math.c src\xl_coding.c src\tPNG\tpng.c ^
 mpc\hello.mpc(name=mpc.c) mpc\ic_launcher.bmp.png(name=ic_launcher.bmp) mpc\assets\1.png ^
-o run.mrp -gzip ^
-filename picoc.mrp -displayname �ֻ�CAPP������v1.8 -vendor "���Ӱ��" -desc "�ֻ�CAPP����������ȡmpc.c�ļ���������" -appid 202003 -version 3008
@REM mrpbuilder -t info -i run.mrp
