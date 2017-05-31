@echo off
title 清除构造目录



if "%bsn_build%" == "" goto F_Error_2

rmdir /s /q %bsn_build%
echo 清除完成
goto F_Exit


:F_Error_2
echo 未找到环境变量 bsn_build
pause
goto F_Exit


:F_Exit