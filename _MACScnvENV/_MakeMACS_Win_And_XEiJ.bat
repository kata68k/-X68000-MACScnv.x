@echo off

pushd %~dp0

echo ====================================================================
echo MACSデータ(旧)を作成します。
echo ====================================================================
rem goto XEiJ
if exist "CG00000" (
	goto SKIPDIRMAKE
)
if exist "CG10000" (
	goto SKIPDIRMAKE
)
if exist "CG00000.BMP" (
	echo BMPファイルをサブディレクトリに移動します。(00)
	call CG_SPLIT_AKT.BAT
	goto XEiJ
)
if exist "CG10000.BMP" (
	echo BMPファイルをサブディレクトリに移動します。(1x)
	call CG_SPLIT_10000.bat
	goto XEiJ
)
goto enddat

:SKIPDIRMAKE

echo ====================================================================
echo サブディレクトリ作成をスキップします。
echo ====================================================================

:XEiJ
echo ====================================================================
echo MACScnv.xを実行します
echo XEiJを起動して、作業ディレクトリに移動してください
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
echo MACSデータ(旧)を作成完了しました。
echo ====================================================================

:enddat

pause
