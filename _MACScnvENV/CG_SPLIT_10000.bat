@echo off

setlocal EnableDelayedExpansion

pushd %~dp0

rem CG10000.BMP`CGxxxxx.BMP‚ð‚T‚O‚OŒÂ‚¸‚ÂƒfƒBƒŒƒNƒgƒŠ‚É•ª‚¯‚é(AKT‚³‚ñ)

for /L %%i in (10000,500,100000) do (
	set /a num1 = %%i
	if not exist "CG!num1!" (
		mkdir CG!num1!
		echo CG!num1!
	)
	set /a forend = %%i + 500 - 1
	for /L %%j in (%%i,1,!forend!) do (
		set /a num2=%%j
		if not exist "CG!num2!.bmp" (
		  goto endbat
		)
		move "CG!num2!.bmp" CG!num1! > nul
	)
)
:endbat
endlocal
