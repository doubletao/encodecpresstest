set DIR_PATH=%cd%
set OUT_DIR_PATH=%DIR_PATH%\release%date:~0,4%%date:~5,2%%date:~8,2%%tm1%%tm2%%tm3%%time:~3,2%%time:~6,2%
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