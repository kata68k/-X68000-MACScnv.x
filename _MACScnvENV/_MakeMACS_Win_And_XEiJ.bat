@echo off

pushd %~dp0

echo ====================================================================
echo MACS�f�[�^(��)���쐬���܂��B
echo ====================================================================
rem goto XEiJ
if exist "CG00000" (
	goto SKIPDIRMAKE
)
if exist "CG10000" (
	goto SKIPDIRMAKE
)
if exist "CG00000.BMP" (
	echo BMP�t�@�C�����T�u�f�B���N�g���Ɉړ����܂��B(00)
	call CG_SPLIT_AKT.BAT
	goto XEiJ
)
if exist "CG10000.BMP" (
	echo BMP�t�@�C�����T�u�f�B���N�g���Ɉړ����܂��B(1x)
	call CG_SPLIT_10000.bat
	goto XEiJ
)
goto enddat

:SKIPDIRMAKE

echo ====================================================================
echo �T�u�f�B���N�g���쐬���X�L�b�v���܂��B
echo ====================================================================

:XEiJ
echo ====================================================================
echo MACScnv.x�����s���܂�
echo XEiJ���N�����āA��ƃf�B���N�g���Ɉړ����Ă�������
echo ====================================================================
pause

time /T
echo MACScnv.x -A
echo MACScnv.x -A 1>\\.\pipe\XEiJPaste
rem timeout 1 > nul
echo 0_MakeTxTp.bat
echo 0_MakeTxTp.bat 1>\\.\pipe\XEiJPaste
rem timeout 1 > nul
echo 1_MakePCM.bat
echo 1_MakePCM.bat 1>\\.\pipe\XEiJPaste
rem timeout 1 > nul
echo 2_MakeBLK.bat
echo 2_MakeBLK.bat 1>\\.\pipe\XEiJPaste
rem timeout 1 > nul
echo 3_MakeMACS.bat
echo 3_MakeMACS.bat 1>\\.\pipe\XEiJPaste
time /T

echo ====================================================================
echo MACS�f�[�^(��)���쐬�������܂����B
echo ====================================================================

:enddat

pause
