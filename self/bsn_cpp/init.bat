@echo off
title ����bsn�Ļ�������
set root_dir=%CD%

mkdir nosvn
mkdir nosvn\build
mkdir nosvn\out

mkdir lib3\nosvn
mkdir lib3\nosvn\bin
mkdir lib3\nosvn\include
mkdir lib3\nosvn\lib
mkdir lib3\nosvn\lib\debug
mkdir lib3\nosvn\lib\release

echo 7z����Ŀ¼
set bsn_path_7z="C:\Program Files\7-Zip"
echo ��3����Ŀ¼
set bsn_lib3_bin=%root_dir%\lib3\nosvn\bin
set bsn_lib3_lib=%root_dir%\lib3\nosvn\lib
set bsn_lib3_include=%root_dir%\lib3\nosvn\include
set bsn_build=%root_dir%\nosvn\build
set bsn_out=%root_dir%\nosvn\out
set bsn_src=%root_dir%
cd ..
set bsn_dir=%cd%
cd %root_dir%

echo д�뵱ǰֵ��ϵͳȫ�ֱ���
setx bsn_lib3_bin 		%bsn_lib3_bin%
setx bsn_lib3_lib 		%bsn_lib3_lib%
setx bsn_lib3_include 	%bsn_lib3_include%
setx bsn_path_7z 		%bsn_path_7z%
setx bsn_build 			%bsn_build%
setx bsn_out 			%bsn_out%
setx bsn_src 			%bsn_src%
setx bsn_dir 			%bsn_dir%




set bsn_path=%%bsn_lib3_bin%%;%%bsn_path_7z%%
echo %bsn_path%
setx bsn_path %bsn_path%

echo ��%%bsn_path%%;�ӵ��û�����path��ǰ��
pause