echo off
echo 生成物および中間生成物を削除します
del /s Tx*
del /s Tp*
del /s *.blk
del /s *.o
del /s *.PCM
del MACSsrc.x
del MACSsrc.s
del 0_MakeTxTp.bat
del 1_MakePCM.bat
del 2_MakeBLK.bat
del 3_MakeMACS.bat
