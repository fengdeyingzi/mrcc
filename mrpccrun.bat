
@REM ��ʼ����
java -jar D:\app\mrpbuilder.jar -t build ^
-Iinterpreter\src\ -Iinterpreter\syslib\ -Isrc\ -Isfw -Isfw\res ^
-Isfw\adv\ -Isfw\common\ -Isfw\gui\ -Isfw\controls\ -Isfw\net\ ^
-DSCREEN_SIZE_240320 ^
-i interpreter\src\mpcrun.c interpreter\src\momo_picoc.c interpreter\src\myfunc.c interpreter\src\picoc.c interpreter\src\platform.c interpreter\src\table.c interpreter\src\type.c interpreter\src\variable.c interpreter\src\parse.c interpreter\src\lex.c interpreter\src\include.c interpreter\src\heap.c interpreter\src\expression.c interpreter\src\clibrary.c interpreter\syslib\m_base.c interpreter\syslib\m_sound.c interpreter\syslib\m_base_i.c interpreter\syslib\m_android.c interpreter\syslib\m_graphics.c src\mrc_android.c src\mrc_graphics.c src\xl_bmp.c src\xl_debug.c src\mpc.c ^
interpreter\syslib\m_ex_game.c interpreter\syslib\m_ex_math.c interpreter\syslib\m_exb.c interpreter\syslib\m_net.c ^
interpreter\syslib\math.c src\xl_coding.c ^
 mpc\hello.mpc(name=mpc.c) mpc\ic_launcher.bmp.png(name=ic_launcher.bmp) ^
-o run.mrp -gzip ^
-filename picoc.mrp -displayname �ֻ�CAPP������v1.6 -vendor "���Ӱ��" -desc "�ֻ�CAPP����������ȡmpc.c�ļ���������" -appid 202003 -version 3006
mrpbuilder -t info -i run.mrp