#ifndef	FILEMANAGER_C
#define	FILEMANAGER_C

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <io.h>
#include <time.h>
#include <doslib.h>
#include <iocslib.h>
#include <interrupt.h>

#include "usr_macro.h"

#include "FileManager.h"

asm("	.include	doscall.mac");

/* �L�[��� */
static uint8_t	g_ubFileManagerGetKey;
		
/* �֐��̃v���g�^�C�v�錾 */
int16_t File_Load(int8_t *, void *, size_t, size_t);
int16_t FileHeader_Load(int8_t *, void *, size_t, size_t);
int16_t File_strSearch(FILE *, char *, int, long);
int16_t File_Save(int8_t *, void *, size_t, size_t);
int16_t GetFileLength(int8_t *, int32_t *);
int16_t	SetQuarterFont(int8_t *, int8_t *);
void *MyMalloc(int32_t);
void *MyMallocJ(int32_t);
void *MyMallocHi(int32_t);
int16_t MyMfree(void *);
int16_t	MyMfreeJ(void *);
int16_t	MyMfreeHi(void *);
int32_t	MaxMemSize(int8_t);
int16_t Load_MACS_List(	int8_t *, int8_t (*)[256], uint32_t *);
int16_t Get_MACS_File(int8_t *, int8_t (*)[256], uint32_t *);
int32_t GetHisFileCnt(int8_t *);
int32_t SetHisFileCnt(int8_t *);
uint8_t	GetKeyInfo(void);
uint8_t	SetKeyInfo(uint8_t);
int16_t Get_BMP_File(int8_t *, uint32_t *);
int16_t IsArriveDir(int8_t *);

/*===========================================================================================*/
/* �֐���	�F	*/
/* ����		�F	*/
/* �߂�l	�F	*/
/*-------------------------------------------------------------------------------------------*/
/* �@�\		�F	*/
/*===========================================================================================*/
/* �t�@�C���ǂݍ��� */
/* *fname	�t�@�C���� */
/* *ptr		�i�[��̐擪�A�h���X */
/* size		�f�[�^�̃T�C�Y */
/* n		�f�[�^�̌� */
int16_t File_Load(int8_t *fname, void *ptr, size_t size, size_t n)
{
	FILE *fp;
	int16_t ret = 0;

	/* �t�@�C�����J���� */
	fp = fopen(fname, "rb");
	
	if(fp == NULL)
	{
		/* �t�@�C�����ǂݍ��߂܂��� */
		printf("error�F%s�t�@�C����������܂���I\n", fname);
		ret = -1;
	}
	else
	{
		int i, j;
		size_t ld, ld_mod, ld_t;
		
		/* �f�[�^�����w�肵�Ȃ��ꍇ */
		if(n == 0)
		{
			/* �t�@�C���T�C�Y���擾 */
			n = filelength(fileno(fp));
		}
		
		fprintf(stderr, "0%% -=-=- 50%% -=-=- 100%% <cancel:ESC>\n");
		ld = n / 100;
		ld_mod = n % 100;
		ld_t = 0;
		
		fprintf(stderr, "+---------+---------+   ");
		fprintf(stderr, "\033[24D");	/* ����24�������ړ� */
		for (i = 0; i <= 100; i++) {
			/* �t�@�C���ǂݍ��� */
			if(i < 100)
			{
				fread (ptr, size, ld, fp);
				ptr += ld;
				ld_t += ld;
			}
			else
			{
				fread (ptr, size, ld_mod, fp);
				ld_t += ld_mod;
			}
			
			for (j = 0; j < i / 5 + 1; j++) {
				fprintf(stderr, "#");
			}
			fprintf(stderr, "\n");
			fprintf(stderr, "%3d%%(%d/%d)", i, ld_t, n);
			if(i < 100)
			{
				fprintf(stderr, "\n");
				fprintf(stderr, "\033[2A");	/* �Q�s��Ɉړ� */
			}
			
			if(GetKeyInfo() == 0x01u)	/* ESC */
			{
				break;
			}
			if(GetKeyInfo() == 0x11u)	/* Q */
			{
				break;
			}
		}
		if(i >= 100)
		{
			fprintf(stderr, "  File loading completed!! ");
		}
		else
		{
			fprintf(stderr, "  File load canceled ");
			ret = -1;
		}
		fprintf(stderr, "\n");
		
		/* �t�@�C������� */
		fclose (fp);
	}

	return ret;
}

/*===========================================================================================*/
/* �֐���	�F	*/
/* ����		�F	*/
/* �߂�l	�F	*/
/*-------------------------------------------------------------------------------------------*/
/* �@�\		�F	*/
/*===========================================================================================*/
/* �t�@�C���ǂݍ��� */
/* *fname	�t�@�C���� */
/* *ptr		�i�[��̐擪�A�h���X */
/* size		�f�[�^�̃T�C�Y */
/* n		�f�[�^�̌� */
int16_t FileHeader_Load(int8_t *fname, void *ptr, size_t size, size_t n)
{
	FILE *fp;
	int16_t ret = 0;

	char sSmallBuf[256];
	
	/* �t�@�C�����J���� */
	fp = fopen(fname, "rb");
	
	if(fp == NULL)
	{
		/* �t�@�C�����ǂݍ��߂܂��� */
		printf("error�F%s�t�@�C����������܂���I\n", fname);
		ret = -1;
	}
	else
	{
		char sBuf[256];
		
		memset(sBuf, 0, sizeof(sBuf));
		fread (sBuf, sizeof(char), 8, fp);
		
		if(strcmp(sBuf, "MACSDATA") == 0)	/* MACSDATA���� */
		{
			char toolver[2];
			long ld;
			
			fseek(fp, 8L, SEEK_SET);
			memset(sBuf, 0, sizeof(sBuf));
			fread (&toolver[0], sizeof(char), 1, fp);	/* �o�[�W���� H */
			fseek(fp, 9L, SEEK_SET);
			memset(sBuf, 0, sizeof(sBuf));
			fread (&toolver[1], sizeof(char), 1, fp);	/* �o�[�W���� L */
			ret = (int16_t)((toolver[0]<<8) + toolver[1]);
			
			fseek(fp, 10L, SEEK_SET);
			memset(sBuf, 0, sizeof(sBuf));
			fread (&ld, sizeof(long), 1, fp);	/* �t�@�C���T�C�Y */
			
			if( (toolver[0] == 1) && (toolver[1] > 0x16))
			{
				printf("   ");
				if(File_strSearch( fp, "TITLE:", 6, 14L ) == 0)		/* TITLE: */
				{
					printf("\n");
				}
				printf(" ");
				if(File_strSearch( fp, "COMMENT:", 8, 14L ) == 0)		/* COMMENT: */
				{
					printf("\n");
				}
			}
			
			memset(sSmallBuf, 0, sizeof(sSmallBuf));
			SetQuarterFont("DataVer:", sSmallBuf);
			printf("%s", sSmallBuf);
//			printf("\033[31m%s\033[m", "DataVer:");		/* �� */
			printf("\033[32m%x.%x\033[m ", toolver[0], toolver[1]);
			
			memset(sSmallBuf, 0, sizeof(sSmallBuf));
			SetQuarterFont("FileSize:", sSmallBuf);
			printf("%s", sSmallBuf);
//			printf("\033[31m%s\033[m", "FileSize:");	/* �� */
			if((ld>>20) > 0)
			{
				printf("\033[32m%ld[MB]\033[m ", ld>>20);
			}
			else if((ld>>10) > 0)
			{
				printf("\033[32m%ld[KB]\033[m ", ld>>10);
			}
			else
			{
				printf("\033[32m%ld[Byte]\033[m ", ld);
			}
			
			if( (toolver[0] == 1) && (toolver[1] > 0x16))
			{
				if(File_strSearch( fp, "DUALPCM/PCM8PP:", 15, 14L ) == 0)		/* DUALPCM/ */
				{
				}
				else if(File_strSearch( fp, "PCM8PP:", 7, 14L ) == 0)	/* PCM8PP */
				{
				}
				else if(File_strSearch( fp, "ADPCM:", 6, 14L ) == 0)	/* ADPCM */
				{
				}
				else
				{
					/* �������Ȃ� */
				}
			}
			printf(" ");
		}
		
		/* �t�@�C������� */
		fclose (fp);
	}
	return ret;
}
	
/*===========================================================================================*/
/* �֐���	�F	*/
/* ����		�F	*/
/* �߂�l	�F	*/
/*-------------------------------------------------------------------------------------------*/
/* �@�\		�F	*/
/*===========================================================================================*/
/* �t�@�C���ۑ� */
/* *fname	�t�@�C���� */
/* *ptr		�i�[��̐擪�A�h���X */
/* size		�f�[�^�̃T�C�Y */
/* n		�f�[�^�̌� */
int16_t File_strSearch(FILE *fp, char *str, int len, long file_ofst)
{
	int16_t ret = 0;
	
	int i;
	int cnt, sMeslen;
	char sBuf[256];
	char sSmallBuf[256];
	
	sMeslen = 0;
	
	/* �T�����L�[���[�h����NULL�܂ŕ\������ */
	for(i=0; i < 256; i++)
	{
		fseek(fp, file_ofst + i, SEEK_SET);
		
		memset(sBuf, 0, sizeof(sBuf));
		fread (sBuf, sizeof(char), len, fp);	/* �t�@�C���ǂݍ��� */
		
		if(strncmp(sBuf, str, len) == 0)	/* �ǂݍ��񂾃f�[�^�ƃL�[���[�h�̈�v�m�F */
		{
			fseek(fp, file_ofst + i + len, SEEK_SET);
			memset(sBuf, 0, sizeof(sBuf));
			fgets(sBuf, 256, fp);
			sMeslen = strlen(sBuf);
			cnt = i;
			ret = 0;
			break;
		}
		memset(sBuf, 0, sizeof(sBuf));
		ret = -1;
	}
	
	if(sMeslen != 0)
	{
//		printf("\033[31m%s\033[m", str);	/* ���������͐� */
		memset(sSmallBuf, 0, sizeof(sSmallBuf));
		SetQuarterFont(str, sSmallBuf);
		printf("%s", sSmallBuf);
		printf("\033[37m%s\033[m", sBuf);	/* �������ʕ����̓n�C���C�g���F */
//		printf("%s", sBuf);
	}

	return ret;
}

/*===========================================================================================*/
/* �֐���	�F	*/
/* ����		�F	*/
/* �߂�l	�F	*/
/*-------------------------------------------------------------------------------------------*/
/* �@�\		�F	*/
/*===========================================================================================*/
/* �t�@�C���ۑ� */
/* *fname	�t�@�C���� */
/* *ptr		�i�[��̐擪�A�h���X */
/* size		�f�[�^�̃T�C�Y */
/* n		�f�[�^�̌� */
int16_t File_Save(int8_t *fname, void *ptr, size_t size, size_t n)
{
	FILE *fp;
	int16_t ret = 0;

	/* �t�@�C�����J���� */
	fp = fopen(fname, "rb");
	
	if(fp == NULL)	/* �t�@�C�������� */
	{
		/* �t�@�C�����J���� */
		fp = fopen(fname, "wb");
		fwrite(ptr, size, n, fp);
	}
	else
	{
		/* �t�@�C�������݂���ꍇ�͉������Ȃ� */
	}
	/* �t�@�C������� */
	fclose (fp);

	return ret;
}

/*===========================================================================================*/
/* �֐���	�F	*/
/* ����		�F	*/
/* �߂�l	�F	*/
/*-------------------------------------------------------------------------------------------*/
/* �@�\		�F	*/
/*===========================================================================================*/
int16_t	GetFileLength(int8_t *pFname, int32_t *pSize)
{
	FILE *fp;
	int16_t ret = 0;
	int32_t	Tmp;

	fp = fopen( pFname , "rb" ) ;
	if(fp == NULL)		/* Error */
	{
		ret = -1;
	}
	else
	{
		Tmp = fileno( fp );
		if(Tmp == -1)	/* Error */
		{
			*pSize = 0;
			ret = -1;
		}
		else
		{
			Tmp = filelength( Tmp );
			if(Tmp == -1)		/* Error */
			{
				*pSize = 0;
				ret = -1;
			}
			else
			{
				*pSize = Tmp;
			}
		}
//		printf("GetFileLength = (%4d, %4d)\n", *pSize, Tmp );

		fclose( fp ) ;
	}
	
	return ret;
}

/*===========================================================================================*/
/* �֐���	�F	*/
/* ����		�F	*/
/* �߂�l	�F	*/
/*-------------------------------------------------------------------------------------------*/
/* �@�\		�F	*/
/*===========================================================================================*/
int16_t	SetQuarterFont(int8_t *sString, int8_t *sDst)
{
	int16_t ret = 0;
	int32_t length;
	int32_t i;
	
	length = strlen(sString);
	
	for(i = 0; i < length; i++ )
	{
		*sDst = 0xF3;
		sDst++;
		*sDst = *sString;
		sDst++;
		sString++;
	}
	
	return ret;
}


/*===========================================================================================*/
/* �֐���	�F	*/
/* ����		�F	*/
/* �߂�l	�F	*/
/*-------------------------------------------------------------------------------------------*/
/* �@�\		�F	*/
/*===========================================================================================*/
void *MyMalloc(int32_t Size)
{
	void *pPtr = NULL;

	if(Size >= 0x1000000u)
	{
		printf("error�F�������m�ۃT�C�Y���傫�����܂�(0x%x)\n", Size );
	}
	else

	{
		pPtr = _dos_malloc(Size);	/* �������m�� */

//		pPtr = malloc(Size);	/* �������m�� */
		
		if(pPtr == NULL)
		{
			puts("error�F���������m�ۂ��邱�Ƃ��o���܂���ł���");
		}
		else if((uint32_t)pPtr >= 0x81000000)
		{
			if((uint32_t)pPtr >= 0x82000000)
			{
				printf("error�F���������m�ۂ��邱�Ƃ��o���܂���ł���(0x%x)\n", (uint32_t)pPtr);
			}
			else
			{
				printf("error�F���������m�ۂ��邱�Ƃ��o���܂���ł���(0x%x)\n", (uint32_t)pPtr - 0x81000000 );
			}
			pPtr = NULL;
		}
		else
		{
			//printf("Mem Address 0x%p Size = %d[byte]\n", pPtr, Size);
			//printf("�������A�h���X(0x%p)=%d\n", pPtr, Size);
		}
	}
	
	return pPtr;
}

/*===========================================================================================*/
/* �֐���	�F	*/
/* ����		�F	*/
/* �߂�l	�F	*/
/*-------------------------------------------------------------------------------------------*/
/* �@�\		�F	*/
/*===========================================================================================*/
void *MyMallocJ(int32_t Size)
{
	void *pPtr = NULL;
	
	PRAMREG(d0_reg, d0);		/* d0��ϐ�d0_reg�Ɋ��蓖�Ă� */
	
	asm("\tmove.l 4(sp),d3");	/* �X�^�b�N�Ɋi�[���ꂽ����Size��(d3)�֑�� */
	
	asm("\tmove.l d3,-(sp)");	/* MALLOC3�̈�����d3������ */
	
 	asm("\tDOS _MALLOC3");		/* MALLOC3 */

	asm("\taddq.l #4, sp");		
	
	pPtr = (void *)d0_reg;
	
	if(pPtr == NULL)
	{
		puts("error�F���������m�ۂ��邱�Ƃ��o���܂���ł���");
	}
	else if((uint32_t)pPtr >= 0x81000000)
	{
		if((uint32_t)pPtr >= 0x82000000)
		{
			printf("error�F���������m�ۂ��邱�Ƃ��o���܂���ł���(0x%x)\n", (uint32_t)pPtr);
		}
		else
		{
			printf("error�F���������m�ۂ��邱�Ƃ��o���܂���ł���(0x%x)\n", (uint32_t)pPtr - 0x81000000 );
		}
		pPtr = NULL;
	}
	else
	{
		printf("message:JMem Address 0x%p Size = %d[byte]\n", pPtr, Size);
	}
	
	return (void*)pPtr;
}

/*===========================================================================================*/
/* �֐���	�F	*/
/* ����		�F	*/
/* �߂�l	�F	*/
/*-------------------------------------------------------------------------------------------*/
/* �@�\		�F	*/
/*===========================================================================================*/
void *MyMallocHi(int32_t Size)
{
	void *pPtr = NULL;

	struct	_regs	stInReg = {0}, stOutReg = {0};
	int32_t		retReg;	/* d0 */
	
	stInReg.d0 = 0xF8;					/* IOCS _HIMEM */
	stInReg.d1 = 0x03;					/* HIMEM_GETSIZE */
	
	retReg = _iocs_trap15(&stInReg, &stOutReg);	/* Trap 15 */
	if(stOutReg.d0 == 0)
	{
		printf("error�F�������T�C�Y%d[MB](%d[byte])/��x�Ɋm�ۂł���ő�̃T�C�Y %d[byte]\n", stOutReg.d0 >> 20u, stOutReg.d0, stOutReg.d1);
		return pPtr;
	}
	
	
	stInReg.d0 = 0xF8;					/* IOCS _HIMEM */
	stInReg.d1 = 0x01;					/* HIMEM_MALLOC */
	stInReg.d2 = Size;					/* �T�C�Y */
	
	retReg = _iocs_trap15(&stInReg, &stOutReg);	/* Trap 15 */
	if(stOutReg.d0 == 0)
	{
		pPtr = (void *)stOutReg.a1;	/* �m�ۂ����������̃A�h���X */
		//printf("HiMem Address 0x%p Size = %d[byte]\n", pPtr, Size);
	}
	else
	{
		puts("error�F���������m�ۂ��邱�Ƃ��o���܂���ł���");
	}
	return pPtr;
}


/*===========================================================================================*/
/* �֐���	�F	*/
/* ����		�F	*/
/* �߂�l	�F	*/
/*-------------------------------------------------------------------------------------------*/
/* �@�\		�F	*/
/*===========================================================================================*/
int16_t	MyMfree(void *pPtr)
{
	int16_t ret = 0;
	uint32_t	result;
	
	if(pPtr == 0)
	{
		puts("message:���v���Z�X�A�q�v���Z�X�Ŋm�ۂ������������t���ŉ�����܂�");
	}
	
	result = _dos_mfree(pPtr);
	//free(pPtr);
	
	if(result < 0)
	{
		puts("error�F����������Ɏ��s");
		ret = -1;
	}
	
	return ret;
}

/*===========================================================================================*/
/* �֐���	�F	*/
/* ����		�F	*/
/* �߂�l	�F	*/
/*-------------------------------------------------------------------------------------------*/
/* �@�\		�F	*/
/*===========================================================================================*/
int16_t	MyMfreeJ(void *pPtr)
{
	int16_t ret = 0;
	
	asm("\tmove.l 4(sp),d3");	/* �X�^�b�N�Ɋi�[���ꂽ����pPtr��(d3)�֑�� */
	
	asm("\tmove.l d3,-(sp)");	/* _MFREE�̈�����d3������ */
	
 	asm("\tDOS _MFREE");		/* _MFREE */

	asm("\taddq.l #4, sp");		
	
	return ret;
}

/*===========================================================================================*/
/* �֐���	�F	*/
/* ����		�F	*/
/* �߂�l	�F	*/
/*-------------------------------------------------------------------------------------------*/
/* �@�\		�F	*/
/*===========================================================================================*/
int16_t	MyMfreeHi(void *pPtr)
{
	int16_t ret = 0;
	struct	_regs	stInReg = {0}, stOutReg = {0};
	int32_t	retReg;	/* d0 */
	
	if(pPtr == NULL)
	{
		puts("message:���v���Z�X�A�q�v���Z�X�Ŋm�ۂ������������t���ŉ�����܂�");
	}
	
	stInReg.d0 = 0xF8;					/* IOCS _HIMEM */
	stInReg.d1 = 0x02;					/* HIMEM_FREE */
	stInReg.d2 = (int32_t)pPtr;			/* �m�ۂ����������̐擪�A�h���X */
	
	retReg = _iocs_trap15(&stInReg, &stOutReg);	/* Trap 15 */
	if(stOutReg.d0 < 0)
	{
		puts("error�F����������Ɏ��s");
	}
	
	return ret;
}

/*===========================================================================================*/
/* �֐���	�F	*/
/* ����		�F	*/
/* �߂�l	�F	*/
/*-------------------------------------------------------------------------------------------*/
/* �@�\		�F	*/
/*===========================================================================================*/
int32_t	MaxMemSize(int8_t SizeType)
{
	int32_t ret = 0;
	int32_t i, dummy;
	int32_t chk[2];
	int8_t *ptMem[2];
	
	ptMem[0] = (int8_t *)0x0FFFFF;
	ptMem[1] = (int8_t *)0x100000;
	
	do{
		for(i=0; i<2; i++)
		{
			if((int32_t)ptMem[i] >= 0xC00000)	/* 12MB�̏�� */
			{
				chk[0] = 0;	/* �������[�v�E�o */
				chk[1] = 2;	/* �������[�v�E�o */
				break;
			}
			else
			{
				chk[i] = _dos_memcpy(ptMem[i], &dummy, 1);	/* �o�X�G���[�`�F�b�N */
			}
		}
		
		/* �����������̋��E */
		if( (chk[0] == 0) &&	/* �ǂݏ����ł��� */
			(chk[1] == 2) )		/* �o�X�G���[ */
		{
			break;	/* ���[�v�E�o */
		}
		
		ptMem[0] += 0x100000;	/* +1MB ���Z */
		ptMem[1] += 0x100000;	/* +1MB ���Z */
	}while(1);
	
//	printf("Memory Size = %d[MB](%d[Byte])(0x%p)\n", ((int)ptMem[1])>>20, ((int)ptMem[1]), ptMem[0]);

	switch(SizeType)
	{
	case 0:	/* Byte */
		ret = ((int)ptMem[1]);
		break;
	case 1:	/* KByte */
		ret = ((int)ptMem[1])>>10;
		break;
	case 2:	/* MByte */
	default:
		ret = ((int)ptMem[1])>>20;
		break;
	}
	
	return ret;
}
/*===========================================================================================*/
/* �֐���	�F	*/
/* ����		�F	*/
/* �߂�l	�F	*/
/*-------------------------------------------------------------------------------------------*/
/* �@�\		�F	*/
/*===========================================================================================*/
int16_t Load_MACS_List(int8_t *fname, int8_t (*macs_list)[256], uint32_t *list_max)
{
	FILE *fp;
	int16_t ret = 0;
	int8_t buf[1000];
	uint32_t i;
	
	i = *list_max;
	
	memset(&buf[0], '\0', sizeof(buf));
	
	fp = fopen(fname, "r");
	if(fp == NULL)
	{
		printf("warning:�v���C���X�g����͂��܂�(%s)\n", fname);
		ret = Get_MACS_File(fname, &macs_list[i], list_max);
		if(ret < 0)
		{
			ret = -1;
		}
		i++;
	}
	else
	{
		printf("message:�v���C���X�g��W�J���܂�(%s)\n", fname);
		fseek( fp, 0, SEEK_SET  );	/* �擪�s */
		while(fgets(buf, sizeof(buf), fp) != NULL)
		{
			int8_t *p;
			p = strchr(buf, '\n');
			if(p)
			{
				*p = '\0';
			}
			ret = Get_MACS_File(buf, &macs_list[i], list_max);
			if(ret < 0)
			{
				break;
			}
//			printf("buf = %s,%s(%d)\n", buf, macs_list[i], *list_max);
			i+=(*list_max - i);
		}
		
		if(ferror(fp) == 0)
		{
//			printf("read success!!!\n");
		} else {
			printf("read failure...\n");
		}
		
		fclose(fp);
	}
	
	return ret;
}

/*===========================================================================================*/
/* �֐���	�F	*/
/* ����		�F	*/
/* �߂�l	�F	*/
/*-------------------------------------------------------------------------------------------*/
/* �@�\		�F	*/
/*===========================================================================================*/
int16_t Get_MACS_File(int8_t *sPath, int8_t (*macs_list)[256], uint32_t *list_max)
{
	int16_t ret = 0;
	int8_t z_name[256];
	int8_t sPathName[256];
	uint32_t i=0;
	uint32_t len=0;
	int8_t *p;
	int8_t *Astr;
	
	struct _filbuf buff;
	
	memset(&buff, 0, sizeof(buff));
	memset(&z_name[0], '\0', sizeof(z_name));
	memset(&sPathName[0], '\0', sizeof(sPathName));
	
	sscanf(sPath,"%s", sPathName);
	sscanf(sPathName,"%s", z_name);
	
	Astr = strchr(sPathName, '*');	/* *�̈ʒu */
	if(Astr != NULL)
	{
		Astr++;
		*Astr = '.';
		Astr++;
		*Astr = 'M';
		Astr++;
		*Astr = 'C';
		Astr++;
		*Astr = 'S';
		Astr++;
		*Astr = '\0';	/* *������΂��̈ʒu����������.MCS\0�ɒu�������� */
	}

	len = strlen(z_name);
	p = strrchr(z_name, '\\');	/* \�̈ʒu */
	if(p != NULL)
	{
		p++;
		*p = '\0';	/* ��������΂��̈ʒu����������\0�ɒu������pass���𓾂� */
	}
	else
	{
		strcpy( z_name, ".\\");
	}
//	printf("sPath = %s\n", sPath);
//	printf("z_name = %s\n", z_name);
	
	ret = _dos_files(&buff, sPathName, 0x31);
	if(ret >= 0)	/* �t�H���_&�t�@�C���Ȃ�o�^ */
	{
		if((buff.atr & 0x10) != 0u)			/* �f�B���N�g������ */
		{
//			printf("dir :%s\n", z_name);
		}
		else if((buff.atr & 0x20) != 0u)	/* �t�@�C������ */
		{
			
			p = _fullpath(macs_list[i], buff.name, 128);	/* �t���p�X���擾 */
			if(p != NULL){
				sprintf(macs_list[i], "%s%s", z_name, buff.name);		/* �t�@�C���Ȃ�o�^ */
//				printf("files(%d):%s\n", i, macs_list[i]);
				i++;
			}
		}
		
		while(_dos_nfiles(&buff) >= 0)	/* ���̃t�@�C�������� */
		{
			if((buff.atr & 0x20) != 0u)	/* �t�@�C������ */
			{
				p = _fullpath(macs_list[i], buff.name, 128);	/* �t���p�X���擾 */
				if(p != NULL){
					sprintf(macs_list[i], "%s%s", z_name, buff.name);		/* �t�@�C���Ȃ�o�^ */
//					printf("files(%d):%s\n", i, macs_list[i]);
					i++;
				}
			}
		}
	}
	else
	{
		/* �����݂���Ȃ����� */
		printf("error:Get_MACS_File not found :%s(%d)\n", sPathName, ret);
		ret = -1;
	}
	
	*list_max += i;
	
	return ret;
}
/*===========================================================================================*/
/* �֐���	�F	*/
/* ����		�F	*/
/* �߂�l	�F	*/
/*-------------------------------------------------------------------------------------------*/
/* �@�\		�F	*/
/*===========================================================================================*/
int32_t GetHisFileCnt(int8_t *sFullPath)
{
	FILE *fp;
	int32_t nRet = 0;

	/* �t�@�C�����J���� */
	fp = fopen("MACSPHIS.LOG", "r");
	
	if(fp == NULL)
	{
		/* �t�@�C�����ǂݍ��߂܂��� */
		printf("error�F%s�t�@�C����������܂���I\n", "MACSPHIS.LOG");
		nRet = -1;
	}
	else
	{
		char sBuf[256];
		char sPathTmp[256];
		
		while(fgets(sBuf, sizeof(sBuf), fp) != NULL)
		{
			memset(sPathTmp, 0, sizeof(sPathTmp));
			
			sscanf( sBuf, "%s %d", sPathTmp, &nRet );
//			printf("GetHisFileCnt file :%s %d\n", sPathTmp, nRet);
//			printf("GetHisFileCnt input:%s\n", sFullPath);
			if(strcmp(sPathTmp, sFullPath) == 0)
			{
				//printf("GetHisFileCnt ��v���܂����I\n");
				break;
			}
			nRet = 0;
		}
		fclose(fp);	/* �t�@�C������� */
	}
	
	return nRet;
}

/*===========================================================================================*/
/* �֐���	�F	*/
/* ����		�F	*/
/* �߂�l	�F	*/
/*-------------------------------------------------------------------------------------------*/
/* �@�\		�F	*/
/*===========================================================================================*/
int32_t SetHisFileCnt(int8_t *sFullPath)
{
	FILE *fp;
	int32_t nRet = 0;
	int32_t nStrlen = 0;
	int8_t bFlag = FALSE;

	/* �t�@�C�����J���� */
	fp = fopen("MACSPHIS.LOG", "a+");
	if(fp == NULL)
	{
		/* �t�@�C�����ǂݍ��߂܂��� */
		printf("error�F%s�t�@�C����������܂���I\n", "MACSPHIS.LOG");
		nRet = -1;
	}
	else
	{
		char sBuf[256];
		char sPathTmp[256];

		memset(sBuf, 0, sizeof(sBuf));
		
		nStrlen = 0;
		
		while(fgets(sBuf, sizeof(sBuf), fp) != NULL)	/* �t�@�C�����當�����ǂݍ��� */
		{
			if(feof(fp))
			{
				break;
			}
			
			memset(sPathTmp, 0, sizeof(sPathTmp));		/* ������ */
			
			sscanf( sBuf, "%s %d", sPathTmp, &nRet );	/* �t���p�X�ƍĐ��񐔂𕪂��� */

			nStrlen += strlen(sBuf);	/* ������̒������擾 */
			
			if(strcmp(sPathTmp, sFullPath) == 0)	/* �e�L�X�g�t�@�C���̕�����Ɠ��͂̕�������r */
			{
				if(nRet <=  8)
				{
					nRet++;	/* 9��MAX�i2���ɓ˓�����ƃY����̂Łj */

					fseek( fp, nStrlen - 2, SEEK_SET );	/* ������̒�������CR/LF���ƍĐ��񐔕������o�b�N */
					fprintf(fp, "%d", nRet);			/* �Đ��񐔂��������� */
				}
				
				bFlag = TRUE;	/* �����񔭌��t���O���Z�b�g */
				break;
			}
			
			nStrlen += 1;	/* CR/LF���i�߂� */
			
			nRet = 0;
		}
		
		if((nRet == 0) && (bFlag == FALSE))	/* �J�E���g�l���O������ ���� ������Ȃ����� */
		{
			nRet++;
			fseek( fp, 0, SEEK_END );	/* �ŏI�s */
			fprintf(fp, "%s %d\n", sFullPath, nRet);	/* �������� */
		}
		
		fclose(fp);	/* �t�@�C������� */
	}
	
	return nRet;
}

/*===========================================================================================*/
/* �֐���	�F	*/
/* ����		�F	*/
/* �߂�l	�F	*/
/*-------------------------------------------------------------------------------------------*/
/* �@�\		�F	*/
/*===========================================================================================*/
uint8_t	GetKeyInfo(void)
{
	uint8_t ret = 0;
	
	ret = g_ubFileManagerGetKey;
	
	return ret;
}

/*===========================================================================================*/
/* �֐���	�F	*/
/* ����		�F	*/
/* �߂�l	�F	*/
/*-------------------------------------------------------------------------------------------*/
/* �@�\		�F	*/
/*===========================================================================================*/
uint8_t	SetKeyInfo(uint8_t ubKey)
{
	uint8_t ret = 0;
	
	g_ubFileManagerGetKey = ubKey;
	
	return ret;
}
/*===========================================================================================*/
/* �֐���	�F	*/
/* ����		�F	*/
/* �߂�l	�F	*/
/*-------------------------------------------------------------------------------------------*/
/* �@�\		�F	*/
/*===========================================================================================*/
int16_t Get_BMP_File(int8_t *sPath, uint32_t *unCount)
{
	int16_t ret = 0;
	int8_t sPathName[256];
	uint32_t i=0;
	int8_t *p;
	int8_t *Astr;
	
	struct _filbuf buff;
	
	memset(&buff, 0, sizeof(buff));
	memset(&sPathName[0], '\0', sizeof(sPathName));
	
	sscanf(sPath,"%s", sPathName);
	
	Astr = strchr(sPathName, '*');	/* *�̈ʒu */
	if(Astr != NULL)
	{
		Astr++;
		*Astr = '.';
		Astr++;
		*Astr = 'B';
		Astr++;
		*Astr = 'M';
		Astr++;
		*Astr = 'P';
		Astr++;
		*Astr = '\0';	/* *������΂��̈ʒu����������.MCS\0�ɒu�������� */
	}

//	printf("sPath = %s\n", sPath);
//	printf("sPathName = %s\n", sPathName);
	
	ret = _dos_files(&buff, sPathName, 0x31);
//	printf("(%d) buff.dirpos = %d(atr=%x)\n", ret, buff.dirpos, buff.atr);
	
	if(ret >= 0)	/* �t�H���_&�t�@�C���Ȃ�o�^ */
	{
		if((buff.atr & 0x10) != 0u)			/* �f�B���N�g������ */
		{
//			printf("dir :%s\n", sPathName);
		}
		else if((buff.atr & 0x20) != 0u)	/* �t�@�C������ */
		{
			
//			printf("buff.name = %s\n", &buff.name[0]);
			p = strstr(&buff.name[0], "CG");	/* \�̈ʒu */
			if(p != NULL){
				i++;
//				printf("file%d:%s\n", i, &buff.name[0]);
			}
		}
		
		while(_dos_nfiles(&buff) >= 0)	/* ���̃t�@�C�������� */
		{
			if((buff.atr & 0x20) != 0u)	/* �t�@�C������ */
			{
				p = strstr(&buff.name[0], "CG");	/* \�̈ʒu */
				if(p != NULL){
					i++;
//					printf("file%d:%s\n", i, &buff.name[0]);
				}
			}
		}
	}
	else
	{
		/* �����݂���Ȃ����� */
//		printf("error:Get_BMP_File not found :%s(%d)\n", sPathName, ret);
		i = 0;
		ret = -1;
	}
	
	*unCount += i;
	
	return ret;
}

/*===========================================================================================*/
/* �֐���	�F	*/
/* ����		�F	*/
/* �߂�l	�F	*/
/*-------------------------------------------------------------------------------------------*/
/* �@�\		�F	*/
/*===========================================================================================*/
int16_t IsArriveDir(int8_t *sPath)
{
	int16_t ret = 0;
	int8_t sPathName[256];
	
	struct _filbuf buff;
	
	memset(&buff, 0, sizeof(buff));
	memset(&sPathName[0], '\0', sizeof(sPathName));
	
	sscanf(sPath,"%s", sPathName);

//	printf("sPath = %s\n", sPath);
//	printf("sPathName = %s\n", sPathName);
	
	ret = _dos_files(&buff, sPathName, 0x31);
//	printf("(%d) buff.dirpos = %d(atr=%x)\n", ret, buff.dirpos, buff.atr);
	
	if(ret >= 0)	/* �t�H���_&�t�@�C���Ȃ�o�^ */
	{
		if((buff.atr & 0x10) != 0u)			/* �f�B���N�g������ */
		{
//			printf("dir :%s\n", sPathName);
		}
		else{
			ret = -2;
		}
	}
	else
	{
		/* �����݂���Ȃ����� */
//		printf("error:Get_BMP_File not found :%s(%d)\n", sPathName, ret);
		ret = -1;
	}
	return ret;
}

#endif	/* FILEMANAGER_C */
