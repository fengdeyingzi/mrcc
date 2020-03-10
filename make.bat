@echo off

del bin\mtk176.mrp
del bin\mtk240.mrp
del bin\mtk400.mrp
del bin\spr176.mrp
del bin\spr240.mrp
del bin\spr400.mrp
@echo on

C:\SKYsdk\Compiler\mrpbuilder.net.exe ./Makefile.mpr
pause
