set DIR_PATH=%cd%
set OUT_DIR_PATH=%DIR_PATH%\release%date:~0,4%%date:~5,2%%date:~8,2%%tm1%%tm2%%tm3%%time:~3,2%%time:~6,2%
set SVNDIR="C:\Program Files\TortoiseSVN\bin"
set VSINSTALLDIR="C:\Program Files (x86)\Microsoft Visual Studio 10.0"

#@echo update working path...
#@echo off
#if not exist "%SVNDIR%\TortoiseProc.exe" goto StartDev
#set SVN="%SVNDIR%\TortoiseProc.exe"
#"%SVN%" /command:update /path:".\" /notempfile /closeonend:1
#@echo %DIR_PATH% already updated
goto StartDev

:StartDev
@echo   off
rem set VC_PATH="C:\Program Files(x86)\Microsoft Visual Studio 10.0\Common7\IDE\"
rem set VC_PATH="C:\Program Files(x86)\DevSoft\VC10\Common7\IDE\"
cd /d $DIR_PATH$

if not exist "%VSINSTALLDIR%\Common7\IDE\DEVENV.EXE" goto EnvError
@SET DEVENV="%VSINSTALLDIR%\Common7\IDE\DEVENV.EXE"

del ReleaseBuild.log
del DebugBuild.log

@echo [%date% %time%]:begin compile

@echo [%time%]:Building EncodecPressTest_2010 Debug ...
"%DEVENV%" ".\EncodecPressTest_2010.sln" /Build "Debug|x64" /out DebugBuild.log
FOR /F "tokens=6 delims= " %%i IN ('FIND/N "====" "DebugBuild.log" ') DO SET e3=%%i
IF %e3% NEQ 0 ECHO ".\EncodecPressTest_2010.sln" Debug mode finding %e3% ERRORs
IF %e3% NEQ 0 GOTO StartDev

@echo [%time%]:Building EncodecPressTest_2010.sln Release ...
"%DEVENV%" ".\EncodecPressTest_2010.sln" /Build "Release|x64" /out ReleaseBuild.log
FOR /F "tokens=6 delims= " %%i IN ('FIND/N "====" "ReleaseBuild.log" ') DO SET e2=%%i
IF %e2% NEQ 0 ECHO ".\EncodecPressTest_2010.sln" Release mode finding %e2% ERRORs
IF %e2% NEQ 0 GOTO StartDev

@echo [%time%]:checking ended

mkdir %OUT_DIR_PATH%
mkdir %OUT_DIR_PATH%\bin
mkdir %OUT_DIR_PATH%\include
mkdir %OUT_DIR_PATH%\include\ecCodec
mkdir %OUT_DIR_PATH%\include\Player
mkdir %OUT_DIR_PATH%\include\SDDefine
mkdir %OUT_DIR_PATH%\lib
mkdir %OUT_DIR_PATH%\lib\ecCodec
mkdir %OUT_DIR_PATH%\lib\Player
copy %DIR_PATH%\bin\avcodec-57.dll %OUT_DIR_PATH%\bin\
copy %DIR_PATH%\bin\avdevice-57.dll %OUT_DIR_PATH%\bin\
copy %DIR_PATH%\bin\avfilter-6.dll %OUT_DIR_PATH%\bin\
copy %DIR_PATH%\bin\avformat-57.dll %OUT_DIR_PATH%\bin\
copy %DIR_PATH%\bin\avutil-55.dll %OUT_DIR_PATH%\bin\
copy %DIR_PATH%\bin\ecCodecD.dll %OUT_DIR_PATH%\bin\
copy %DIR_PATH%\bin\ecCodecD.ilk %OUT_DIR_PATH%\bin\
copy %DIR_PATH%\bin\ecCodecD.pdb %OUT_DIR_PATH%\bin\
copy %DIR_PATH%\bin\ecCodecU.dll %OUT_DIR_PATH%\bin\
copy %DIR_PATH%\bin\ecCodecU.iobj %OUT_DIR_PATH%\bin\
copy %DIR_PATH%\bin\ecCodecU.ipdb %OUT_DIR_PATH%\bin\
copy %DIR_PATH%\bin\ecCodecU.pdb %OUT_DIR_PATH%\bin\
copy %DIR_PATH%\bin\EncodecPressTestU.exe %OUT_DIR_PATH%\bin\
copy %DIR_PATH%\bin\EncodecPressTestU.iobj %OUT_DIR_PATH%\bin\
copy %DIR_PATH%\bin\EncodecPressTestU.ipdb %OUT_DIR_PATH%\bin\
copy %DIR_PATH%\bin\EncodecPressTestU.pdb %OUT_DIR_PATH%\bin\
copy %DIR_PATH%\bin\EncodecPressTestUD.exe %OUT_DIR_PATH%\bin\
copy %DIR_PATH%\bin\EncodecPressTestUD.ilk %OUT_DIR_PATH%\bin\
copy %DIR_PATH%\bin\EncodecPressTestUD.pdb %OUT_DIR_PATH%\bin\
copy %DIR_PATH%\bin\postproc-54.dll %OUT_DIR_PATH%\bin\
copy %DIR_PATH%\bin\SDL2.dll %OUT_DIR_PATH%\bin\
copy %DIR_PATH%\bin\SDLVideoPlayerD.dll %OUT_DIR_PATH%\bin\
copy %DIR_PATH%\bin\SDLVideoPlayerD.ilk %OUT_DIR_PATH%\bin\
copy %DIR_PATH%\bin\SDLVideoPlayerD.pdb %OUT_DIR_PATH%\bin\
copy %DIR_PATH%\bin\SDLVideoPlayerU.dll %OUT_DIR_PATH%\bin\
copy %DIR_PATH%\bin\SDLVideoPlayerU.iobj %OUT_DIR_PATH%\bin\
copy %DIR_PATH%\bin\SDLVideoPlayerU.ipdb %OUT_DIR_PATH%\bin\
copy %DIR_PATH%\bin\SDLVideoPlayerU.pdb %OUT_DIR_PATH%\bin\
copy %DIR_PATH%\bin\swresample-2.dll %OUT_DIR_PATH%\bin\
copy %DIR_PATH%\bin\swscale-4.dll %OUT_DIR_PATH%\bin\
copy %DIR_PATH%\bin\TimeCodeImageGeneratorD.exe %OUT_DIR_PATH%\bin\
copy %DIR_PATH%\bin\TimeCodeImageGeneratorD.ilk %OUT_DIR_PATH%\bin\
copy %DIR_PATH%\bin\TimeCodeImageGeneratorD.pdb %OUT_DIR_PATH%\bin\
copy %DIR_PATH%\bin\TimeCodeImageGeneratorU.exe %OUT_DIR_PATH%\bin\
copy %DIR_PATH%\bin\TimeCodeImageGeneratorU.iobj %OUT_DIR_PATH%\bin\
copy %DIR_PATH%\bin\TimeCodeImageGeneratorU.ipdb %OUT_DIR_PATH%\bin\
copy %DIR_PATH%\bin\TimeCodeImageGeneratorU.pdb %OUT_DIR_PATH%\bin\

xcopy /E %DIR_PATH%\include\ecCodec\* %OUT_DIR_PATH%\include\ecCodec
xcopy /E %DIR_PATH%\include\Player\* %OUT_DIR_PATH%\include\Player
xcopy /E %DIR_PATH%\include\SDDefine\* %OUT_DIR_PATH%\include\SDDefine
xcopy /E %DIR_PATH%\lib\ecCodec\* %OUT_DIR_PATH%\lib\ecCodec
xcopy /E %DIR_PATH%\lib\Player\* %OUT_DIR_PATH%\lib\Player

pause