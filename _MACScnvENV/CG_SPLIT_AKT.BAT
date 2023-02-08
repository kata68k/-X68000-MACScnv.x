@echo off

setlocal EnableDelayedExpansion

pushd %~dp0

rem CG00000.BMP`CGxxxxx.BMP‚ð‚T‚O‚OŒÂ‚¸‚ÂƒfƒBƒŒƒNƒgƒŠ‚É•ª‚¯‚é(AKT‚³‚ñ)

for /L %%i in (0,500,100000) do (
	set num1=0000%%i
	set num1=!num1:~-5,5!
	if not exist "CG!num1!" (
		mkdir CG!num1!
		echo CG!num1!
	)
	set /a forend = %%i + 500 - 1
	for /L %%j in (%%i,1,!forend!) do (
		set num2=0000%%j
		set num2=!num2:~-5,5!
		if not exist "CG!num2!.bmp" (
		  goto endbat
		)
		move "CG!num2!.bmp" CG!num1! > nul
	)
)
:endbat
endlocal
