@echo off
title �������Ŀ¼



if "%bsn_build%" == "" goto F_Error_2

rmdir /s /q %bsn_build%
echo ������
goto F_Exit


:F_Error_2
echo δ�ҵ��������� bsn_build
pause
goto F_Exit


:F_Exit