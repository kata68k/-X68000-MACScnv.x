# ����(MACS�f�[�^)������Ă݂悤�I

MACS�Ƃ́H
------------

#### MACSDRV.doc ���p

>MACS�Ƃ�X680x0�ɂ�����'�A�j���[�V����'�������Ǝ�y�Ɉ������߂ɐ��܂ꂽ�풓�^��
>�A�j���[�V�����R���g���[���ł��B

## MACS�f�[�^�쐬�⏕�c�[���iMACScnv.x)�ɂ���
MACS�f�[�^�́A�v���O����(�A�Z���u��)�{�摜�f�[�^�{�����f�[�^�̑g�ݍ��킹�ō쐬���܂��B
�����ɂ���ς����Ȃ̂ŁAMACS�f�[�^�쐬�⏕�c�[���iMACScnv.x)�����܂����B

Windows���ŉ摜�f�[�^�Ɖ����f�[�^�𒊏o������AX68000�Ƀf�[�^���R�s�[���܂��B
MACS�f�[�^�쐬�⏕�c�[���iMACScnv.x)���N�����A�������ꂽ�\�[�X�ƃo�b�`�t�@�C����MACS�f�[�^�����܂��B  

�܂��AXEiJ(X68000 Emulator in Java)���g���΁AWindows����o�b�`�t�@�C��������s���邾����MACS�f�[�^����邱�Ƃ��ł��܂��B

MACScnv.x�́A�摜�f�[�^�Ɖ����f�[�^��p�ӂ���΁A�v���O������f���o���d�g�݂ɂȂ��Ă��܂��B
�S�̃o�b�`�t�@�C�������������̂ŁA���ԂɎ��s����MACS�f�[�^�����܂��B
- 0_MakeTxTp.bat�@(�摜����)
- 1_MakePCM.bat�@ (�����f�[�^�ϊ�)
- 2_MakeBLK.bat�@ (�f�[�^����)
- 3_MakeMACS.bat�@(�A�Z���u���A�����N�AMACS�f�[�^�쐬)

### �K�v�Ȋ�
Windows��X68000�ԂŃf�[�^�̂���肪�ł��邱�ƁB
#### Windows
| No.| �c�[����            | �T�v                                |
|----|---------------------|-------------------------------------|
| 1  | VideoProc Converter | ������摜�f�[�^�Ɖ����f�[�^�ɕ���(���ꂪ�ł���Ȃ�ǂ̃c�[���ł��悢)  |
| 2  | IrfanView           | �����̉摜�f�[�^���ꊇ�ŉ��H�ł���  |

#### X68000(�G�~�����[�^����)
| No.| �c�[����         |Version | �T�v                                |����|
|----|------------------|--------|-------------------------------------|----|
| 1  | switch.x         |        | ���ڃ������T�C�Y��ύX              |�V�X�e���f�B�X�N�ɓ���|
| 2  | FLOATx.X         |        | ���������_�^(float)��������         |�V�X�e���f�B�X�N�ɓ���|
| 3  | (V)TwentyOne.sys |        | �����t�@�C������������              |�����N�Q��|
| 4  | MACSDRV.x        |        | �풓�^�̃A�j���[�V�����R���g���[��  |�����N�Q��|
| 5  | MakeMCS.x        |        | MACS�f�[�^����                      |MACS116.LZH�ɓ���  |
| 6  | txs.x            |        | �摜�f�[�^��MACS�`���ŕۑ�          |MACS116.LZH�ɓ���|
| 7  | blk.x            |        | �o�C�i�������̂�����                |MACS116.LZH�ɓ���  |
| 8  | APICG.r          |        | �摜���[�_�[���Z�[�o�[              |�����N�Q��|
| 9  | YGMC.X           |        | ��ʃ��[�h��ύX����                |�����N�Q��|
| 10 | HAS.x            |        | �A�Z���u��                          |�����N�Q��|
| 11 | hlk.r            |3.01+15 | �����J                              |�����N�Q��|
| ~~12~~ | ~~CV.X~~             |        | ~~�t�@�C���R���o�[�^�[~~                |~~�����N�Q��~~|
| 13 | pcm3pcm.x        |        | WAV����PCM�֕ϊ�����                |�����N�Q��|
| 14 | TS16DRVp.X       |        | XEiJ�AXM6TypeG�APhantomX�A060turbo�ATS-6BE16 �ȂǂŎ��������n�C������(���[�J��������)�������h���C�o                 |X68K BBS|
| 15 | MACScnv.x        |        | MACS�f�[�^�쐬�⏕                  |X68K BBS|

| No.| �t�@�C����       | �T�v                |����               |
|----|------------------|---------------------|-------------------|
| 1  | MACS_sch.h       | MACS�p�w�b�_�t�@�C��|MACS116.LZH�ɓ���  |

#### X68000(�G�~�����[�^)
| No.| �G�~�����[�^��         |Version | �T�v                                |����|
|----|------------------|--------|-------------------------------------|----|
| 1  | XEiJ (X68000 Emulator in Java)         | 0.23.01.21 | 060turbo���[�h���g���Ȃ炱��ł��I   |�����N�Q��|


### �����N

- [�V�X�e���f�B�X�N](http://retropc.net/x68000/software/sharp/human302/):Makoto Kamada�����X68000 LIBRARY�̃y�[�W
- [MACSDRV](http://retropc.net/x68000/software/movie/macs/macsmoon/):Makoto Kamada�����X68000 LIBRARY�̃y�[�W
- [(V)TwentyOne](http://gorry.haun.org/x68index.html):GORRY����́u�|���o�P�c�w�v...X680x0�̃y�[�W
- [APICG](http://gorry.haun.org/x68index.html):GORRY����́u�|���o�P�c�w�v...X680x0�̃y�[�W
- [HAS](http://http://retropc.net/x68000/software/develop/as/has/):Makoto Kamada�����X68000 LIBRARY�̃y�[�W
- [hlk](https://github.com/kg68k/hlk-ev/releases/):����@�K���Z�������GitHub
- ~~[CV](http://retropc.net/x68000/software/develop/cv/cv_x/):Makoto Kamada�����X68000 LIBRARY�̃y�[�W~~
- [pcm3pcm.x](https://www.vector.co.jp/soft/x68/art/se019752.html):Vector�̃y�[�W
- [YGMC.X](http://most.bigmoney.biz/g0org/x68tools/graphic/conv/ygmc100.lzh):x68tools�̃y�[�W
- [TS16DRVp.X](https://x68kbbs.com/uploader/?a=Hau_miyu&f=TS16DRVp.ZIP):x68k BBS
- [XEiJ](https://stdkmd.net/xeij/):Makoto Kamada�����XEiJ (X68000 Emulator in Java)�̃y�[�W


## �菇

---
### 1. �D���ȓ���t�@�C�����������悤�I<BR>
VideoProc Converter�̋@�\���֗��ł��B<BR>
�̌��ł́A�T���܂ł̐��񂪂���܂����AX68000�ł͈�������Ȃ��T�C�Y�Ȃ̂Ŗ�肠��܂���B(��)

---
### 2. VideoProc Converter�œ���t�@�C������摜�f�[�^(PNG)���o�͂��悤�I<BR>
�u�r�f�I�v��I�����܂��B<BR>
![�Î~��](img/GP1.png)<BR>
---
���̃��j���[����u�X�i�b�v�V���b�g�v��I�����܂��B<BR>
![�Î~��](img/GP2.png)<BR>
---
�u��f���v���ő�l�ɂȂ�悤�ɏグ�܂��B�����ړ��͂ł͂Ȃ��A�J�[�\���L�[���APageUp���I�X�X��<BR>
![�Î~��](img/GP3.png)<BR>
---
�E���́u�o�̓t�H���_�v�œK���ȏꏊ��I�����A�uRUN�v�������ĉ摜�𒊏o���܂��B<BR>
![�Î~��](img/GP4.png)<BR>
---
PNG�t�@�C�������o����܂��B<BR>
![�Î~��](img/GP5.png)<BR>

---
### 3. VideoProc Converter�œ���t�@�C�����特���f�[�^(WAV)���o�͂��悤�I<BR>
���̃��j���[����uPCM�v��I�����܂��B<BR>
![����](img/WA1.png)<BR>
---
�I�v�V�����̕ύX�͕s�v�ł��B
![����](img/WA2.png)<BR>
---
WAV�t�@�C�����쐬�����̂ŁA���������uAD.WAV�v�Ƀt�@�C������ύX���������B<BR>
![����](img/WA4.png)<BR>

---
### 4. ���T�C�Y�����F��PNG��BMP�ϊ����悤�I<BR>
PNG�t�@�C���̂ǂꂩ����uIrfanView�v�ŊJ���܂��B<BR>
![���H1](img/CG1-1.png)<BR>
---
�u�t�@�C���v���u�ꊇ�����v<BR>
![���H1](img/CG1.png)<BR>
---
�u�`���ݒ�v�� BMP - Windows Bitmap<BR>
�u���l�[���ݒ�v���uCG#####�v #�͂T��<BR>
�u�t�@�C���Ǘ��t�H���_�v ���u�ϊ���̃t�@�C�����ۑ������Ƃ���v<BR>
�u�t�@�C���̏ꏊ�v���uPNG�t�@�C�����ۑ�����Ă���ꏊ�v<BR>
�u�t�@�C���̎�ށv�� �uPNG - Portable Network Graphics �v<BR>
![���H1](img/CG2.png)<BR>
---
�u�ڍאݒ�v������<BR>
�u�J�n�ԍ��v�� 0�i10000�ł�OK�ł��B�j<BR>
�u���Z���v �� 1<BR>
![���H1](img/CG3.png)<BR>
---
�u�ǉ��ݒ�v������<BR>
![���H1](img/CG2.png)<BR>
---
�u�T�C�Y�ύX�v�Ƀ`�F�b�N������<BR>
�u���T�C�Y�v256�iMACS�f�[�^��256��256�Ȃ̂Łj<BR>
�u�c�T�C�Y�v������ <BR>
�u�A�X�y�N�g����ێ����� �v�Ƀ`�F�b�N������<BR>
�u�摜�����T���v������v�Ƀ`�F�b�N������<BR>
�u�\���F�ύX�v�Ƀ`�F�b�N������<BR>
�u�ݒ�̐F���֕\���F�ύX�v��8�`15<BR>
�����ӁF16�ɂ���ƌ�H���̃p���b�g�쐬�Ŏ��s���Ă��܂��܂��B<BR>
���Q�l�F��荂�掿�����߂�Ȃ�Εʂ̌��F�c�[�����I�X�X�����܂��B<BR>
�u�L�����o�X�T�C�Y�ύX�v�Ƀ`�F�b�N������<BR>
![���H1](img/CG4.png)<BR>
�u�ݒ�̍�Ə����ŕҏW�v�Ƀ`�F�b�N�����u���ʐݒ�v����Έ�A�̍�Ƃ��w�����Ɏ��s���邱�Ƃ��ł��܂��B  
���\���F�ύX�͕K���Ō�ɍs������<BR>
![���H1](img/CG4-1.png)<BR>
�u�ݒ�m�F�v������
�uMethod1�v�́uTop side�v�uBottom side�v���L����<BR>
����̗Ⴞ�� 256x192�̃T�C�Y����68�p��256x256�ɃT�C�Y��ύX����ɂ́A<BR>
����������ĂȂ��̂ŏ㉺32�s�N�Z���i��(256-192)/2�j���]���𑝂₷�B<BR>
�uCanvas Color�v�́A���ɂ��Ă����܂��傤�B<BR>
![���H2](img/CG10.png)<BR>
�ݒ肪����������OK�������Ă��������B
---
�u�t�@�C���Ǘ��t�H���_�v ���u�ϊ���̃t�@�C�����ۑ������Ƃ���iX68000�������������Ƃ����ݒ�j�v<BR>
�u�t�@�C���̏ꏊ�v���u���T�C�Y�A���F����BMP�t�@�C�����ۑ�����Ă���ꏊ�v<BR>
�u���ׂĒǉ��v�������āu��ƃt�@�C���̐��v�ɓo�^����B<BR>
![���H2](img/CG8.png)<BR>
---
�u���ׂĒǉ��v�������āu��ƃt�@�C���̐��v�ɓo�^����B<BR>
�u���בւ��v�������āA�u�����̖��O�v��I�����A�t�@�C�������P���珇�Ԃɕ��Ԃ悤�ɂ���B<BR>
![���H1](img/CG5.png)<BR>
---
�u���s�v�������B<BR>
![���H2](img/CG11.png)<BR>
---
256x256�T�C�Y�ŁA4BPP(16�F�ȉ�)�̉摜���o���オ��B<BR>
![���H2](img/CG12.png)<BR>

---
### 5. MACS�f�[�^�쐬�⏕�c�[���iMACScnv.x)�����s����O�Ɋm�F���悤<BR>
X68000�̃G�~�����[�^��060turbo���[�h�ŋN�����āA�ϊ�����BMP�AAD.PCM������邩�m�F����B<BR>
MACS_SCH.h�A__Clean.bat�Axeijwin.dll���R�s�[���Ă����B<BR>
MACScnv.x���͂��߁A�ϊ��ŕK�v�ȃc�[���́A�p�X�ݒ肪����Ƃ���ɔz�u���Ă����B<BR>
![MACS](img/MC1.png)<BR>

---
### 6. MACS�f�[�^�쐬�⏕�c�[���i_MakeMACS_Win_And_XEiJ.bat)�����s���悤�I�i�����ł��ꍇ�j<BR>
Windows����u_MakeMACS_Win_And_XEiJ.bat�v�����s����B<BR>
![MACS](img/MC1-1.png)<BR>
---
�o�b�`�t�@�C�������s�����l�q�B<BR>
![MACS](img/MC1-4.png)<BR>

---
CGxxxxx.bmp�t�@�C���́A�T�u�f�B���N�g�����Ɋi�[�����<BR>
![MACS](img/MC1-2.png)<BR>

---
X68000(XEiJ)���猩���l�q<BR>
![MACS](img/MC1-3.png)<BR>

---
�p�ӂ��o������A���������L�[�������āA�o�b�`�t�@�C�����p�����܂��B<BR>
![MACS](img/MC1-5.png)<BR>

---
XEiJ���o�R���āAX68000�̃R�}���h�v�����v�g�ɖ��߂���т܂��B<BR>
![MACS](img/MC1-6.png)<BR>
��́A�Q���Ԃ��炢���߂Ă��������Ŋ����ł��B<BR>

---
# �����i�����ł��ꍇ�j�� �W�͂�GO�I
---
### 7. MACS�f�[�^�쐬�⏕�c�[���iMACScnv.x)�����s���悤�I�i�蓮�ł��ꍇ�j<BR>
MACS�f�[�^�쐬�⏕�c�[���iMACScnv.x)�����s����B<BR>
��P<BR>
�������� �J�n�ԍ��� ex. 0�Ȃ�CG00000���ŏ��̉摜�ɂȂ�<BR>
�������� �����l  �� ex. 1�Ȃ�CG00000�ACG00001�ACG00002�ACG00003��+1����������B<BR>
����O���� �I���ԍ��� ex. 1620�Ȃ�CG01620�܂ŏ����ΏۂƂȂ�B<BR>
����l���� ����̍Đ����� or ����̉����̍Đ����ԁ� ex. 1��21�b�̓���Ȃ�81�b�Ȃ̂�81�Ɠ��͂���B<BR>
1621���̉摜���g���āA1�b������20���̉摜������������悤��MACS�f�[�^���ł��܂��B(�v�F�������j<BR>

��Q<BR>
�������� �J�n�ԍ��� ex. 0�Ȃ�CG00000���ŏ��̉摜�ɂȂ�<BR>
�������� �����l  �� ex. 4�Ȃ�CG00000�ACG00004�ACG00008�ACG00012��+4����������B<BR>
����O���� �I���ԍ��� ex. 1620�Ȃ�CG01620�܂ŏ����ΏۂƂȂ�B<BR>
����l���� ����̍Đ����� or ����̉����̍Đ����ԁ� ex. 1��21�b�̓���Ȃ�81�b�Ȃ̂�81�Ɠ��͂���B<BR>
405��(1621��4)�̉摜���g���āA1�b������5���̉摜������������悤��MACS�f�[�^���ł��܂��B<BR>
![MACS](img/MC2.png)<BR>
�o�b�`�t�@�C���S�ƃo�C�i���t�@�C�����X�g�R��ށA�A�Z���u���\�[�X���쐬�����B<BR>
![MACS](img/MC3.png)<BR>
���Ƀt�@�C�������݂���ꍇ�́A�㏑�����܂���B<BR>
__Clean.bat�����s���āA���������폜���Ă��������B
![MACS](img/MC4.png)<BR>
0_MakeTxTp.bat�����s���āAMACS�f�[�^�ɕK�v�ȉ摜�����܂��B
![MACS](img/MC5.png)<BR>
BMP�摜���e�L�X�g�摜�ɕϊ����Ă���l�q<BR>
![MACS](img/MC5-1.png)<BR>
1_MakePCM.bat�����s���āAWAV�t�@�C����ADPCM�̃f�[�^�ɕϊ����܂�<BR>
![MACS](img/MC6.png)<BR>
�ϊ����Ă�l�q<BR>
![MACS](img/MC6-1.png)<BR>
2_MakeBLK.bat�����s���āA�o�C�i���t�@�C�����������܂�<BR>
![MACS](img/MC7.png)<BR>
���[�j���O���b�Z�[�W�͋C�ɂ��Ȃ��Ă悢����<BR>
![MACS](img/MC7-1.png)<BR>
3_MakeMACS.bat�����s���āA�A�Z���u���A�����N(�R���o�[�g)�AMACS�f�[�^�����s���܂�<BR>
![MACS](img/MC8.png)<BR>
Out of memory���o��Ǝ��s�ł�<BR>
������������Ȃ�����~~�A�������́A�t�@�C���T�C�Y��8MB�Ɏ��܂��ĂȂ�����~~�������ł��B<BR>
�΍�P�F�풓�������炵�ă������̋󂫗̈�𑝂₷<BR>
�΍�Q�FMACScnv.x�̑������̐��l���������t���[�����[�g�𗎂Ƃ�<BR>
�΍�R�F3_MakeMACS.bat����hlk.r���n�C�������Ŏ��s����B��8MB�ȏ��MACS�f�[�^�����ꍇ�K�{<BR>
<BR>
 ���n�C���������g������<BR>
  3_MakeMACS.bat���@��ɂ��킹��<font color="Red">**����**</font>��ǋL�ҏW��������<BR>
 * Xellent30�̏ꍇ + �g���������̏ꍇ<BR>
<font color="Red">**���ؒ��i�ł��Ȃ������j**</font><BR>
 * X68030 + �g���������̏ꍇ<BR>
<font color="Red">**���ؒ��i�ł��Ȃ������j**</font><BR>
 * 040 turbo�̏ꍇ<BR>
<font color="Red">**���ؒ��i�ł��Ȃ������j**</font><BR>
 * 060 turbo�̏ꍇ�iPhantomX�AXEiJ���܂ށj<BR>
`has -u MACSsrc`<BR>
<font color="Red">**`060high.x 1`**</font><BR>
 `hlk -r MACSsrc LIST0_Tx (����) LIST_PCM`<BR>
<font color="Red">**`060high.x 0`**</font><BR>
`MakeMCS MACSsrc`<BR>

��L�΍�ŁA�������Ȃ��ꍇ�́A__Clean.bat�����s����X68000�ōs����Ƃ���A���g���C���܂��傤�I�i���ꂪ�h���c�j<BR>
![MACS](img/MC8-1.png)<BR>

---
### 8. �Đ����Ă݂悤�I<BR>
MACSDRV.x���풓��������ɁA�R�}���h���C���ňȉ������s���Ă��������B<BR>
���t�@�C�����iMACSsrc.MCS�j�́A�K���Ƀ��l�[�����Ă����Ƃ����ł��傤�B<BR>

\>copy MACSsrc.MCS MACS<BR>
�����C��������������Ȃ��ꍇ�́A030���[�h�ڍs�Ńn�C�������ɑΉ�����MACSplay.x�����g�����������B<BR>
![MACS](img/MC9.png)<BR>

���悪�Đ��ł����犮���ł��I
![MACS](img/MC9-1.png)<BR>
---
# �����