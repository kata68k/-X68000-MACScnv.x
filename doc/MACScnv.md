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
| 9  | YGMC.X           |        | ��ʃ��[�h��ύX����                |�ǂ��H|
| 10 | HAS.x            |        | �A�Z���u��                          |�����N�Q��|
| 11 | hlk.r            |3.01+15 | �����J                              |�����N�Q��|
| ~~12~~ | ~~CV.X~~             |        | ~~�t�@�C���R���o�[�^�[~~                |~~�����N�Q��~~|
| 13 | pcm3pcm.x        |        | WAV����PCM�֕ϊ�����                |�ǂ��H|
| 14 | MACScnv.x        |        | MACS�f�[�^�쐬�⏕                  |X68K BBS|

| No.| �t�@�C����       | �T�v                |����               |
|----|------------------|---------------------|-------------------|
| 1  | MACS_sch.h       | MACS�p�w�b�_�t�@�C��|MACS116.LZH�ɓ���  |


### �����N

- [�V�X�e���f�B�X�N](http://retropc.net/x68000/software/sharp/human302/):Makoto Kamada�����X68000 LIBRARY�̃y�[�W
- [MACSDRV](http://retropc.net/x68000/software/movie/macs/macsmoon/):Makoto Kamada�����X68000 LIBRARY�̃y�[�W
- [(V)TwentyOne](http://gorry.haun.org/x68index.html):GORRY����́u�|���o�P�c�w�v...X680x0�̃y�[�W
- [APICG](http://gorry.haun.org/x68index.html):GORRY����́u�|���o�P�c�w�v...X680x0�̃y�[�W
- [HAS](http://http://retropc.net/x68000/software/develop/as/has/):Makoto Kamada�����X68000 LIBRARY�̃y�[�W
- [hlk](https://github.com/kg68k/hlk-ev/releases/):����@�K���Z�������GitHub
- ~~[CV](http://retropc.net/x68000/software/develop/cv/cv_x/):Makoto Kamada�����X68000 LIBRARY�̃y�[�W~~

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
�u�J�n�ԍ��v�� 0<BR>
�u���Z���v �� 1<BR>
![���H1](img/CG3.png)<BR>
---
�u�ǉ��ݒ�v������<BR>
�u�T�C�Y�ύX�v�Ƀ`�F�b�N������<BR>
�u���T�C�Y�v�u�c�T�C�Y�v�� 256�iMACS�f�[�^��256��256�Ȃ̂Łj<BR>
�u�A�X�y�N�g����ێ����� �v�Ƀ`�F�b�N������<BR>
�u�摜�����T���v������v�Ƀ`�F�b�N������<BR>
�u�\���F�ύX�v�Ƀ`�F�b�N������<BR>
�u�ݒ�̐F���֕\���F�ύX�v��8�`14    �����ӁF15�A16�ɂ���ƌ�H���̃p���b�g�쐬�Ŏ��s����B<BR>
![���H1](img/CG4.png)<BR>
---
�u���ׂĒǉ��v�������āu��ƃt�@�C���̐��v�ɓo�^����B<BR>
�u���בւ��v�������āA�u�����̖��O�v��I�����A�t�@�C�������P���珇�Ԃɕ��Ԃ悤�ɂ���B<BR>
![���H1](img/CG5.png)<BR>
---
�u���s�v�������B
![���H1](img/CG6.png)<BR>
---
�A�X�y�N�g�䂪�ێ����ꂽBMP�摜���ł���B<BR>
![���H1](img/CG7.png)<BR>

---
### 5. �󔒂𖄂߂�256x256�T�C�Y�̉摜����낤�I<BR>
256x256�T�C�Y���K�v�Ȃ̂ŁA�������g������B<BR>
�܂�����u�t�@�C���v���u�ꊇ�����v��I�ԁB<BR>
�u�t�@�C���Ǘ��t�H���_�v ���u�ϊ���̃t�@�C�����ۑ������Ƃ���iX68000�������������Ƃ����ݒ�j�v<BR>
�u�t�@�C���̏ꏊ�v���u���T�C�Y�A���F����BMP�t�@�C�����ۑ�����Ă���ꏊ�v<BR>
�u�t�@�C���̎�ށv�� �uBMP - Windows Bitmap�v<BR>
�u���ׂĒǉ��v�������āu��ƃt�@�C���̐��v�ɓo�^����B<BR>
![���H2](img/CG8.png)<BR>
---
�u�ǉ��ݒ�v������<BR>
�u�T�C�Y�ύX�v�Ƀ`�F�b�N���O��<BR>
�u�\���F�ύX�v�Ƀ`�F�b�N���O��<BR>
�u�L�����o�X�T�C�Y�ύX�v�Ƀ`�F�b�N������<BR>
�u�ݒ�m�F�v������
![���H2](img/CG9.png)<BR>
---
�u�ݒ�m�F�v����������<BR>
�uMethod1�v�́uTop side�v�uBottom side�v���L����<BR>
����̗Ⴞ�� 256x192��256x256�ɃT�C�Y��ύX����ɂ́A<BR>
����������ĂȂ��̂ŏ㉺32�s�N�Z�������₷�B<BR>
�uCanvas Color�v�́A���ɂ��Ă����܂��傤�B<BR>
![���H2](img/CG10.png)<BR>
---
�u���s�v�������B<BR>
![���H2](img/CG11.png)<BR>
---
256x256�T�C�Y�ŁA4BPP(16�F�ȉ�)�̉摜���o���オ��B<BR>
![���H2](img/CG12.png)<BR>

---
### 6. MACS�f�[�^�쐬�⏕�c�[���iMACScnv.x)�����s���悤�I<BR>
X68000�̃G�~�����[�^���N�����āA�ϊ�����BMP������邩�m�F����B<BR>
MACScnv.x�AMACS_SCH.h�A__Clean.bat���R�s�[���Ă����B<BR>
�ϊ��ŕK�v�ȃc�[���́A�p�X�ݒ肪����Ƃ���ɔz�u���Ă����B<BR>
![MACS](img/MC1.png)<BR>
---
MACS�f�[�^�쐬�⏕�c�[���iMACScnv.x)�����s����B<BR>
���L�̗Ⴞ��<BR>
�������� �J�n�ԍ��� ex. 0�Ȃ�CG00000���ŏ��̉摜�ɂȂ�<BR>
�������� �����l  �� ex. 4�Ȃ�CG00000�ACG00004�ACG00008�ACG00012��+4����������B<BR>
����O���� �I���ԍ��� ex. 1620�Ȃ�CG01620�܂ŏ����ΏۂƂȂ�B<BR>
����l���� ����̍Đ����� or ����̉����̍Đ����ԁ� ex. 1��21�b�̓���Ȃ�81�b�Ȃ̂�81�Ɠ��͂���B<BR>
����ɂ��A1621��4��405���̉摜���g����1�b������5���̉摜������������悤��MACS�f�[�^���ł��܂��B
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
 * 060 turbo�̏ꍇ<BR>
`has -u MACSsrc`<BR>
<font color="Red">**`060high.x 1`**</font><BR>
<font color="Red">**`060loadhigh.x`**</font> `hlk -r MACSsrc LIST0_Tx (����) LIST_PCM`<BR>
<font color="Red">**`060high.x 0`**</font><BR>
`MakeMCS MACSsrc`<BR>

��L�΍�ŁA�������Ȃ��ꍇ�́A__Clean.bat�����s����X68000�ōs����Ƃ���A���g���C���܂��傤�I�i���ꂪ�h���c�j<BR>
![MACS](img/MC8-1.png)<BR>

---
### 6. �Đ����Ă݂悤�I<BR>
MACSDRV.x���풓��������ɁA�R�}���h���C���ňȉ������s���Ă��������B<BR>
���t�@�C�����iMACSsrc.MCS�j�́A�K���Ƀ��l�[�����Ă����Ƃ����ł��傤�B<BR>

\>copy MACSsrc.MCS MACS<BR>
�����C���������ȏ��MACS�f�[�^���Đ�����ꍇ�́AMACSplay.x�����g�����������B<BR>
![MACS](img/MC9.png)<BR>

���悪�Đ��ł����犮���ł��I
![MACS](img/MC9-1.png)<BR>
---
# �����