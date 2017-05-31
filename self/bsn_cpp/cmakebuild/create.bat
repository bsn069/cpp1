@echo off
title 构造编译目录

if "%bsn_build%" == "" goto F_Error_2
echo bsn_build=%bsn_build%
if "%bsn_out%" == "" goto F_Error_3
echo bsn_out=%bsn_out%

echo 将生成编译目录 %bsn_build%
echo 若要终止 直接杀进程  Ctrl+c
pause

call clear.bat

mkdir %bsn_build%
mkdir %bsn_out%

if not exist %bsn_out% goto F_Error_5
if not exist %bsn_build% goto F_Error_6

cd /d %bsn_build%
cmake %bsn_src%
echo 构造完成 
goto F_Exit



:F_Error_2
echo 未找到环境变量 bsn_build
goto F_Exit

:F_Error_3
echo 未找到环境变量 bsn_out
goto F_Exit


:F_Error_5
echo bsn_out[%bsn_out%]目录不存在
goto F_Exit

:F_Error_6
echo bsn_build[%bsn_build%]目录不存在
goto F_Exit

:F_Exit