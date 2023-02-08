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

/* キー情報 */
static uint8_t	g_ubFileManagerGetKey;
		
/* 関数のプロトタイプ宣言 */
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
/* 関数名	：	*/
/* 引数		：	*/
/* 戻り値	：	*/
/*-------------------------------------------------------------------------------------------*/
/* 機能		：	*/
/*===========================================================================================*/
/* ファイル読み込み */
/* *fname	ファイル名 */
/* *ptr		格納先の先頭アドレス */
/* size		データのサイズ */
/* n		データの個数 */
int16_t File_Load(int8_t *fname, void *ptr, size_t size, size_t n)
{
	FILE *fp;
	int16_t ret = 0;

	/* ファイルを開ける */
	fp = fopen(fname, "rb");
	
	if(fp == NULL)
	{
		/* ファイルが読み込めません */
		printf("error：%sファイルが見つかりません！\n", fname);
		ret = -1;
	}
	else
	{
		int i, j;
		size_t ld, ld_mod, ld_t;
		
		/* データ個数を指定しない場合 */
		if(n == 0)
		{
			/* ファイルサイズを取得 */
			n = filelength(fileno(fp));
		}
		
		fprintf(stderr, "0%% -=-=- 50%% -=-=- 100%% <cancel:ESC>\n");
		ld = n / 100;
		ld_mod = n % 100;
		ld_t = 0;
		
		fprintf(stderr, "+---------+---------+   ");
		fprintf(stderr, "\033[24D");	/* 左に24文字分移動 */
		for (i = 0; i <= 100; i++) {
			/* ファイル読み込み */
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
				fprintf(stderr, "\033[2A");	/* ２行上に移動 */
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
		
		/* ファイルを閉じる */
		fclose (fp);
	}

	return ret;
}

/*===========================================================================================*/
/* 関数名	：	*/
/* 引数		：	*/
/* 戻り値	：	*/
/*-------------------------------------------------------------------------------------------*/
/* 機能		：	*/
/*===========================================================================================*/
/* ファイル読み込み */
/* *fname	ファイル名 */
/* *ptr		格納先の先頭アドレス */
/* size		データのサイズ */
/* n		データの個数 */
int16_t FileHeader_Load(int8_t *fname, void *ptr, size_t size, size_t n)
{
	FILE *fp;
	int16_t ret = 0;

	char sSmallBuf[256];
	
	/* ファイルを開ける */
	fp = fopen(fname, "rb");
	
	if(fp == NULL)
	{
		/* ファイルが読み込めません */
		printf("error：%sファイルが見つかりません！\n", fname);
		ret = -1;
	}
	else
	{
		char sBuf[256];
		
		memset(sBuf, 0, sizeof(sBuf));
		fread (sBuf, sizeof(char), 8, fp);
		
		if(strcmp(sBuf, "MACSDATA") == 0)	/* MACSDATA判定 */
		{
			char toolver[2];
			long ld;
			
			fseek(fp, 8L, SEEK_SET);
			memset(sBuf, 0, sizeof(sBuf));
			fread (&toolver[0], sizeof(char), 1, fp);	/* バージョン H */
			fseek(fp, 9L, SEEK_SET);
			memset(sBuf, 0, sizeof(sBuf));
			fread (&toolver[1], sizeof(char), 1, fp);	/* バージョン L */
			ret = (int16_t)((toolver[0]<<8) + toolver[1]);
			
			fseek(fp, 10L, SEEK_SET);
			memset(sBuf, 0, sizeof(sBuf));
			fread (&ld, sizeof(long), 1, fp);	/* ファイルサイズ */
			
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
//			printf("\033[31m%s\033[m", "DataVer:");		/* 青字 */
			printf("\033[32m%x.%x\033[m ", toolver[0], toolver[1]);
			
			memset(sSmallBuf, 0, sizeof(sSmallBuf));
			SetQuarterFont("FileSize:", sSmallBuf);
			printf("%s", sSmallBuf);
//			printf("\033[31m%s\033[m", "FileSize:");	/* 青字 */
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
					/* 何もしない */
				}
			}
			printf(" ");
		}
		
		/* ファイルを閉じる */
		fclose (fp);
	}
	return ret;
}
	
/*===========================================================================================*/
/* 関数名	：	*/
/* 引数		：	*/
/* 戻り値	：	*/
/*-------------------------------------------------------------------------------------------*/
/* 機能		：	*/
/*===========================================================================================*/
/* ファイル保存 */
/* *fname	ファイル名 */
/* *ptr		格納先の先頭アドレス */
/* size		データのサイズ */
/* n		データの個数 */
int16_t File_strSearch(FILE *fp, char *str, int len, long file_ofst)
{
	int16_t ret = 0;
	
	int i;
	int cnt, sMeslen;
	char sBuf[256];
	char sSmallBuf[256];
	
	sMeslen = 0;
	
	/* 探したキーワードからNULLまで表示する */
	for(i=0; i < 256; i++)
	{
		fseek(fp, file_ofst + i, SEEK_SET);
		
		memset(sBuf, 0, sizeof(sBuf));
		fread (sBuf, sizeof(char), len, fp);	/* ファイル読み込み */
		
		if(strncmp(sBuf, str, len) == 0)	/* 読み込んだデータとキーワードの一致確認 */
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
//		printf("\033[31m%s\033[m", str);	/* 検索文字は青字 */
		memset(sSmallBuf, 0, sizeof(sSmallBuf));
		SetQuarterFont(str, sSmallBuf);
		printf("%s", sSmallBuf);
		printf("\033[37m%s\033[m", sBuf);	/* 検索結果文字はハイライト白色 */
//		printf("%s", sBuf);
	}

	return ret;
}

/*===========================================================================================*/
/* 関数名	：	*/
/* 引数		：	*/
/* 戻り値	：	*/
/*-------------------------------------------------------------------------------------------*/
/* 機能		：	*/
/*===========================================================================================*/
/* ファイル保存 */
/* *fname	ファイル名 */
/* *ptr		格納先の先頭アドレス */
/* size		データのサイズ */
/* n		データの個数 */
int16_t File_Save(int8_t *fname, void *ptr, size_t size, size_t n)
{
	FILE *fp;
	int16_t ret = 0;

	/* ファイルを開ける */
	fp = fopen(fname, "rb");
	
	if(fp == NULL)	/* ファイルが無い */
	{
		/* ファイルを開ける */
		fp = fopen(fname, "wb");
		fwrite(ptr, size, n, fp);
	}
	else
	{
		/* ファイルが存在する場合は何もしない */
	}
	/* ファイルを閉じる */
	fclose (fp);

	return ret;
}

/*===========================================================================================*/
/* 関数名	：	*/
/* 引数		：	*/
/* 戻り値	：	*/
/*-------------------------------------------------------------------------------------------*/
/* 機能		：	*/
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
/* 関数名	：	*/
/* 引数		：	*/
/* 戻り値	：	*/
/*-------------------------------------------------------------------------------------------*/
/* 機能		：	*/
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
/* 関数名	：	*/
/* 引数		：	*/
/* 戻り値	：	*/
/*-------------------------------------------------------------------------------------------*/
/* 機能		：	*/
/*===========================================================================================*/
void *MyMalloc(int32_t Size)
{
	void *pPtr = NULL;

	if(Size >= 0x1000000u)
	{
		printf("error：メモリ確保サイズが大きすぎます(0x%x)\n", Size );
	}
	else

	{
		pPtr = _dos_malloc(Size);	/* メモリ確保 */

//		pPtr = malloc(Size);	/* メモリ確保 */
		
		if(pPtr == NULL)
		{
			puts("error：メモリを確保することが出来ませんでした");
		}
		else if((uint32_t)pPtr >= 0x81000000)
		{
			if((uint32_t)pPtr >= 0x82000000)
			{
				printf("error：メモリを確保することが出来ませんでした(0x%x)\n", (uint32_t)pPtr);
			}
			else
			{
				printf("error：メモリを確保することが出来ませんでした(0x%x)\n", (uint32_t)pPtr - 0x81000000 );
			}
			pPtr = NULL;
		}
		else
		{
			//printf("Mem Address 0x%p Size = %d[byte]\n", pPtr, Size);
			//printf("メモリアドレス(0x%p)=%d\n", pPtr, Size);
		}
	}
	
	return pPtr;
}

/*===========================================================================================*/
/* 関数名	：	*/
/* 引数		：	*/
/* 戻り値	：	*/
/*-------------------------------------------------------------------------------------------*/
/* 機能		：	*/
/*===========================================================================================*/
void *MyMallocJ(int32_t Size)
{
	void *pPtr = NULL;
	
	PRAMREG(d0_reg, d0);		/* d0を変数d0_regに割り当てる */
	
	asm("\tmove.l 4(sp),d3");	/* スタックに格納された引数Sizeを(d3)へ代入 */
	
	asm("\tmove.l d3,-(sp)");	/* MALLOC3の引数にd3を入れる */
	
 	asm("\tDOS _MALLOC3");		/* MALLOC3 */

	asm("\taddq.l #4, sp");		
	
	pPtr = (void *)d0_reg;
	
	if(pPtr == NULL)
	{
		puts("error：メモリを確保することが出来ませんでした");
	}
	else if((uint32_t)pPtr >= 0x81000000)
	{
		if((uint32_t)pPtr >= 0x82000000)
		{
			printf("error：メモリを確保することが出来ませんでした(0x%x)\n", (uint32_t)pPtr);
		}
		else
		{
			printf("error：メモリを確保することが出来ませんでした(0x%x)\n", (uint32_t)pPtr - 0x81000000 );
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
/* 関数名	：	*/
/* 引数		：	*/
/* 戻り値	：	*/
/*-------------------------------------------------------------------------------------------*/
/* 機能		：	*/
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
		printf("error：メモリサイズ%d[MB](%d[byte])/一度に確保できる最大のサイズ %d[byte]\n", stOutReg.d0 >> 20u, stOutReg.d0, stOutReg.d1);
		return pPtr;
	}
	
	
	stInReg.d0 = 0xF8;					/* IOCS _HIMEM */
	stInReg.d1 = 0x01;					/* HIMEM_MALLOC */
	stInReg.d2 = Size;					/* サイズ */
	
	retReg = _iocs_trap15(&stInReg, &stOutReg);	/* Trap 15 */
	if(stOutReg.d0 == 0)
	{
		pPtr = (void *)stOutReg.a1;	/* 確保したメモリのアドレス */
		//printf("HiMem Address 0x%p Size = %d[byte]\n", pPtr, Size);
	}
	else
	{
		puts("error：メモリを確保することが出来ませんでした");
	}
	return pPtr;
}


/*===========================================================================================*/
/* 関数名	：	*/
/* 引数		：	*/
/* 戻り値	：	*/
/*-------------------------------------------------------------------------------------------*/
/* 機能		：	*/
/*===========================================================================================*/
int16_t	MyMfree(void *pPtr)
{
	int16_t ret = 0;
	uint32_t	result;
	
	if(pPtr == 0)
	{
		puts("message:自プロセス、子プロセスで確保したメモリをフルで解放します");
	}
	
	result = _dos_mfree(pPtr);
	//free(pPtr);
	
	if(result < 0)
	{
		puts("error：メモリ解放に失敗");
		ret = -1;
	}
	
	return ret;
}

/*===========================================================================================*/
/* 関数名	：	*/
/* 引数		：	*/
/* 戻り値	：	*/
/*-------------------------------------------------------------------------------------------*/
/* 機能		：	*/
/*===========================================================================================*/
int16_t	MyMfreeJ(void *pPtr)
{
	int16_t ret = 0;
	
	asm("\tmove.l 4(sp),d3");	/* スタックに格納された引数pPtrを(d3)へ代入 */
	
	asm("\tmove.l d3,-(sp)");	/* _MFREEの引数にd3を入れる */
	
 	asm("\tDOS _MFREE");		/* _MFREE */

	asm("\taddq.l #4, sp");		
	
	return ret;
}

/*===========================================================================================*/
/* 関数名	：	*/
/* 引数		：	*/
/* 戻り値	：	*/
/*-------------------------------------------------------------------------------------------*/
/* 機能		：	*/
/*===========================================================================================*/
int16_t	MyMfreeHi(void *pPtr)
{
	int16_t ret = 0;
	struct	_regs	stInReg = {0}, stOutReg = {0};
	int32_t	retReg;	/* d0 */
	
	if(pPtr == NULL)
	{
		puts("message:自プロセス、子プロセスで確保したメモリをフルで解放します");
	}
	
	stInReg.d0 = 0xF8;					/* IOCS _HIMEM */
	stInReg.d1 = 0x02;					/* HIMEM_FREE */
	stInReg.d2 = (int32_t)pPtr;			/* 確保したメモリの先頭アドレス */
	
	retReg = _iocs_trap15(&stInReg, &stOutReg);	/* Trap 15 */
	if(stOutReg.d0 < 0)
	{
		puts("error：メモリ解放に失敗");
	}
	
	return ret;
}

/*===========================================================================================*/
/* 関数名	：	*/
/* 引数		：	*/
/* 戻り値	：	*/
/*-------------------------------------------------------------------------------------------*/
/* 機能		：	*/
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
			if((int32_t)ptMem[i] >= 0xC00000)	/* 12MBの上限 */
			{
				chk[0] = 0;	/* 強制ループ脱出 */
				chk[1] = 2;	/* 強制ループ脱出 */
				break;
			}
			else
			{
				chk[i] = _dos_memcpy(ptMem[i], &dummy, 1);	/* バスエラーチェック */
			}
		}
		
		/* 実装メモリの境界 */
		if( (chk[0] == 0) &&	/* 読み書きできた */
			(chk[1] == 2) )		/* バスエラー */
		{
			break;	/* ループ脱出 */
		}
		
		ptMem[0] += 0x100000;	/* +1MB 加算 */
		ptMem[1] += 0x100000;	/* +1MB 加算 */
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
/* 関数名	：	*/
/* 引数		：	*/
/* 戻り値	：	*/
/*-------------------------------------------------------------------------------------------*/
/* 機能		：	*/
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
		printf("warning:プレイリストを解析します(%s)\n", fname);
		ret = Get_MACS_File(fname, &macs_list[i], list_max);
		if(ret < 0)
		{
			ret = -1;
		}
		i++;
	}
	else
	{
		printf("message:プレイリストを展開します(%s)\n", fname);
		fseek( fp, 0, SEEK_SET  );	/* 先頭行 */
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
/* 関数名	：	*/
/* 引数		：	*/
/* 戻り値	：	*/
/*-------------------------------------------------------------------------------------------*/
/* 機能		：	*/
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
	
	Astr = strchr(sPathName, '*');	/* *の位置 */
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
		*Astr = '\0';	/* *があればその位置をさがして.MCS\0に置き換える */
	}

	len = strlen(z_name);
	p = strrchr(z_name, '\\');	/* \の位置 */
	if(p != NULL)
	{
		p++;
		*p = '\0';	/* ￥があればその位置をさがして\0に置き換えpass名を得る */
	}
	else
	{
		strcpy( z_name, ".\\");
	}
//	printf("sPath = %s\n", sPath);
//	printf("z_name = %s\n", z_name);
	
	ret = _dos_files(&buff, sPathName, 0x31);
	if(ret >= 0)	/* フォルダ&ファイルなら登録 */
	{
		if((buff.atr & 0x10) != 0u)			/* ディレクトリ判定 */
		{
//			printf("dir :%s\n", z_name);
		}
		else if((buff.atr & 0x20) != 0u)	/* ファイル判定 */
		{
			
			p = _fullpath(macs_list[i], buff.name, 128);	/* フルパスを取得 */
			if(p != NULL){
				sprintf(macs_list[i], "%s%s", z_name, buff.name);		/* ファイルなら登録 */
//				printf("files(%d):%s\n", i, macs_list[i]);
				i++;
			}
		}
		
		while(_dos_nfiles(&buff) >= 0)	/* 次のファイルを検索 */
		{
			if((buff.atr & 0x20) != 0u)	/* ファイル判定 */
			{
				p = _fullpath(macs_list[i], buff.name, 128);	/* フルパスを取得 */
				if(p != NULL){
					sprintf(macs_list[i], "%s%s", z_name, buff.name);		/* ファイルなら登録 */
//					printf("files(%d):%s\n", i, macs_list[i]);
					i++;
				}
			}
		}
	}
	else
	{
		/* 何もみつからなかった */
		printf("error:Get_MACS_File not found :%s(%d)\n", sPathName, ret);
		ret = -1;
	}
	
	*list_max += i;
	
	return ret;
}
/*===========================================================================================*/
/* 関数名	：	*/
/* 引数		：	*/
/* 戻り値	：	*/
/*-------------------------------------------------------------------------------------------*/
/* 機能		：	*/
/*===========================================================================================*/
int32_t GetHisFileCnt(int8_t *sFullPath)
{
	FILE *fp;
	int32_t nRet = 0;

	/* ファイルを開ける */
	fp = fopen("MACSPHIS.LOG", "r");
	
	if(fp == NULL)
	{
		/* ファイルが読み込めません */
		printf("error：%sファイルが見つかりません！\n", "MACSPHIS.LOG");
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
				//printf("GetHisFileCnt 一致しました！\n");
				break;
			}
			nRet = 0;
		}
		fclose(fp);	/* ファイルを閉じる */
	}
	
	return nRet;
}

/*===========================================================================================*/
/* 関数名	：	*/
/* 引数		：	*/
/* 戻り値	：	*/
/*-------------------------------------------------------------------------------------------*/
/* 機能		：	*/
/*===========================================================================================*/
int32_t SetHisFileCnt(int8_t *sFullPath)
{
	FILE *fp;
	int32_t nRet = 0;
	int32_t nStrlen = 0;
	int8_t bFlag = FALSE;

	/* ファイルを開ける */
	fp = fopen("MACSPHIS.LOG", "a+");
	if(fp == NULL)
	{
		/* ファイルが読み込めません */
		printf("error：%sファイルが見つかりません！\n", "MACSPHIS.LOG");
		nRet = -1;
	}
	else
	{
		char sBuf[256];
		char sPathTmp[256];

		memset(sBuf, 0, sizeof(sBuf));
		
		nStrlen = 0;
		
		while(fgets(sBuf, sizeof(sBuf), fp) != NULL)	/* ファイルから文字列を読み込む */
		{
			if(feof(fp))
			{
				break;
			}
			
			memset(sPathTmp, 0, sizeof(sPathTmp));		/* 初期化 */
			
			sscanf( sBuf, "%s %d", sPathTmp, &nRet );	/* フルパスと再生回数を分ける */

			nStrlen += strlen(sBuf);	/* 文字列の長さを取得 */
			
			if(strcmp(sPathTmp, sFullPath) == 0)	/* テキストファイルの文字列と入力の文字列を比較 */
			{
				if(nRet <=  8)
				{
					nRet++;	/* 9がMAX（2桁に突入するとズレるので） */

					fseek( fp, nStrlen - 2, SEEK_SET );	/* 文字列の長さからCR/LF分と再生回数文字分バック */
					fprintf(fp, "%d", nRet);			/* 再生回数を書き込み */
				}
				
				bFlag = TRUE;	/* 文字列発見フラグをセット */
				break;
			}
			
			nStrlen += 1;	/* CR/LF分進める */
			
			nRet = 0;
		}
		
		if((nRet == 0) && (bFlag == FALSE))	/* カウント値が０だった かつ 見つからなかった */
		{
			nRet++;
			fseek( fp, 0, SEEK_END );	/* 最終行 */
			fprintf(fp, "%s %d\n", sFullPath, nRet);	/* 書き込み */
		}
		
		fclose(fp);	/* ファイルを閉じる */
	}
	
	return nRet;
}

/*===========================================================================================*/
/* 関数名	：	*/
/* 引数		：	*/
/* 戻り値	：	*/
/*-------------------------------------------------------------------------------------------*/
/* 機能		：	*/
/*===========================================================================================*/
uint8_t	GetKeyInfo(void)
{
	uint8_t ret = 0;
	
	ret = g_ubFileManagerGetKey;
	
	return ret;
}

/*===========================================================================================*/
/* 関数名	：	*/
/* 引数		：	*/
/* 戻り値	：	*/
/*-------------------------------------------------------------------------------------------*/
/* 機能		：	*/
/*===========================================================================================*/
uint8_t	SetKeyInfo(uint8_t ubKey)
{
	uint8_t ret = 0;
	
	g_ubFileManagerGetKey = ubKey;
	
	return ret;
}
/*===========================================================================================*/
/* 関数名	：	*/
/* 引数		：	*/
/* 戻り値	：	*/
/*-------------------------------------------------------------------------------------------*/
/* 機能		：	*/
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
	
	Astr = strchr(sPathName, '*');	/* *の位置 */
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
		*Astr = '\0';	/* *があればその位置をさがして.MCS\0に置き換える */
	}

//	printf("sPath = %s\n", sPath);
//	printf("sPathName = %s\n", sPathName);
	
	ret = _dos_files(&buff, sPathName, 0x31);
//	printf("(%d) buff.dirpos = %d(atr=%x)\n", ret, buff.dirpos, buff.atr);
	
	if(ret >= 0)	/* フォルダ&ファイルなら登録 */
	{
		if((buff.atr & 0x10) != 0u)			/* ディレクトリ判定 */
		{
//			printf("dir :%s\n", sPathName);
		}
		else if((buff.atr & 0x20) != 0u)	/* ファイル判定 */
		{
			
//			printf("buff.name = %s\n", &buff.name[0]);
			p = strstr(&buff.name[0], "CG");	/* \の位置 */
			if(p != NULL){
				i++;
//				printf("file%d:%s\n", i, &buff.name[0]);
			}
		}
		
		while(_dos_nfiles(&buff) >= 0)	/* 次のファイルを検索 */
		{
			if((buff.atr & 0x20) != 0u)	/* ファイル判定 */
			{
				p = strstr(&buff.name[0], "CG");	/* \の位置 */
				if(p != NULL){
					i++;
//					printf("file%d:%s\n", i, &buff.name[0]);
				}
			}
		}
	}
	else
	{
		/* 何もみつからなかった */
//		printf("error:Get_BMP_File not found :%s(%d)\n", sPathName, ret);
		i = 0;
		ret = -1;
	}
	
	*unCount += i;
	
	return ret;
}

/*===========================================================================================*/
/* 関数名	：	*/
/* 引数		：	*/
/* 戻り値	：	*/
/*-------------------------------------------------------------------------------------------*/
/* 機能		：	*/
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
	
	if(ret >= 0)	/* フォルダ&ファイルなら登録 */
	{
		if((buff.atr & 0x10) != 0u)			/* ディレクトリ判定 */
		{
//			printf("dir :%s\n", sPathName);
		}
		else{
			ret = -2;
		}
	}
	else
	{
		/* 何もみつからなかった */
//		printf("error:Get_BMP_File not found :%s(%d)\n", sPathName, ret);
		ret = -1;
	}
	return ret;
}

#endif	/* FILEMANAGER_C */
