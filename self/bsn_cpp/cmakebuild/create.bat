@echo off
title �������Ŀ¼

if "%bsn_build%" == "" goto F_Error_2
echo bsn_build=%bsn_build%
if "%bsn_out%" == "" goto F_Error_3
echo bsn_out=%bsn_out%

echo �����ɱ���Ŀ¼ %bsn_build%
echo ��Ҫ��ֹ ֱ��ɱ����  Ctrl+c
pause

call clear.bat

mkdir %bsn_build%
mkdir %bsn_out%

if not exist %bsn_out% goto F_Error_5
if not exist %bsn_build% goto F_Error_6

cd /d %bsn_build%
cmake %bsn_src%
echo ������� 
goto F_Exit



:F_Error_2
echo δ�ҵ��������� bsn_build
goto F_Exit

:F_Error_3
echo δ�ҵ��������� bsn_out
goto F_Exit


:F_Error_5
echo bsn_out[%bsn_out%]Ŀ¼������
goto F_Exit

:F_Error_6
echo bsn_build[%bsn_build%]Ŀ¼������
goto F_Exit

:F_Exit