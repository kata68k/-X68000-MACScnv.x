#ifndef	WAVE_C
#define	WAVE_C

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "wave.h"

/* C���� wav�t�@�C���̃w�b�_��ǂ� https://achapi2718.blogspot.com/2012/06/c-wav_10.html ��� */
/* �G���f�B�A���������������ăr�b�N�G���f�B�A���p�ɕύX */

/* format chunk �\���� */
struct FormatChunk {
	char id[5];
	unsigned int size;
	unsigned short format;
	unsigned short channels;
	unsigned int	samplerate;
	unsigned int	bytepersec;
	unsigned short blockalign;
	unsigned short bit;
}fmtchunk;

/* �o�b�t�@�[ �\���� */
struct Buff {
	FILE *fpr;
	unsigned char bufchar;
	unsigned char buf[5];
	unsigned int bufint;
	unsigned short bufshort;
} buff;

void readchar(void);
int readint(void);
int readshort(void);
uint16_t swap16(uint16_t);
uint32_t swap32(uint32_t);
void data(void);
void list(void);
void fmtview(void);
void fmt(void);
int headread(void);

/* ������ 4byte �r�b�O�G���f�B�A��*/
void readchar(void){
	int size;
	size = fread(buff.buf, sizeof(unsigned char), 4, buff.fpr);
}

/* ���l 4byte ���g���G���f�B�A�� */
int readint(void){
	fread(&buff.bufint, sizeof(unsigned int), 1, buff.fpr);
	buff.bufint = swap32(buff.bufint);	/*�r�b�O�G���f�B�A��*/
	return buff.bufint;
}

/* ���l 2byte ���g���G���f�B�A�� */
int readshort(void){
	fread(&buff.bufshort, sizeof(unsigned short), 1, buff.fpr);
	buff.bufshort = swap16(buff.bufshort);	/*�r�b�O�G���f�B�A��*/
	return buff.bufshort;
}

uint16_t swap16(uint16_t value)
{
    uint16_t ret;
    ret  = value << 8;
    ret |= value >> 8;
    return ret;
}

uint32_t swap32(uint32_t value)
{
    uint32_t ret;
    ret  = value              << 24;
    ret |= (value&0x0000FF00) <<  8;
    ret |= (value&0x00FF0000) >>  8;
    ret |= value              >> 24;
    return ret;
}

/* data */
void data(void){
	int ret;
	for(;;){
		fread(&buff.bufchar, sizeof(unsigned char), 1, buff.fpr);
		if(buff.bufchar == 'd'){
			fseek(buff.fpr, -1, SEEK_CUR);
			readchar();
			ret = strcmp(buff.buf,"data");
			if(ret == 0){
//				 printf("[%s]\n",buff.buf);
				 readint();
//				 printf("size: %d byte\n",buff.bufint);
				 break;
			}
		}
	}
}

/* LIST */
void list(void){
	int skip;
	int ret;
	readchar();
	ret = strcmp(buff.buf,"LIST");
	if(ret == 0){
//		printf("[%s]\n",buff.buf);
		skip = readint();
//		printf("size: %d byte\n",skip);
		/* skip���� */
		fseek(buff.fpr, skip, SEEK_CUR);
	}else{
		fseek(buff.fpr, -4, SEEK_CUR);
	}
}
/* fmt view */
void fmtview(void){
	printf("[%s]\n"
			"Size:%d byte\n"
			"AudioFormat: %d\n"
			"Channels: %d\n"
			"Samling Rate: %d Hz\n"
			"ByteRate: %d\n"
			"BlockAlign: %d\n"
			"BitsPerSample: %d bit\n",
			 fmtchunk.id,
			 fmtchunk.size,
			 fmtchunk.format,
			 fmtchunk.channels,
			 fmtchunk.samplerate,
			 fmtchunk.bytepersec,
			 fmtchunk.blockalign,
			 fmtchunk.bit);
}
/* fmt �Ǎ��� */
void fmt(void){
	/* id fmt */
	readchar();
	memcpy(fmtchunk.id, buff.buf, sizeof(buff.buf));
	/* size */
	fmtchunk.size = readint();
	/* PCM 2byte */
	fmtchunk.format = readshort();
	/* channels 2byte */
	fmtchunk.channels = readshort();
	/* samples/sec 4byte 44100Hz */
	fmtchunk.samplerate = readint();
	/* svg.bytes/sec 4byte */
	fmtchunk.bytepersec = readint();
	/* bloack align 2byte */
	fmtchunk.blockalign = readshort();
	/* bits/sample 2byte 32bit */
	fmtchunk.bit = readshort();
}

/* �w�b�h�Ǎ� */
int headread(void)
{
	int ret;
	int size;
	/* rb �o�C�i���Ƃ��ĊJ�� */
	char *str = "AD.WAV";
	buff.fpr = fopen(str, "rb"); 
//	printf("%s\n",str);
	
	/* �t�@�C�����Ȃ��ꍇ�̃G���[���� */
	if (buff.fpr == NULL) { 
		puts("error");
		exit(EXIT_FAILURE);
	}else{
		/* RIFF size */
		readchar();
		ret = strcmp(buff.buf,"RIFF");
		if(ret != 0){
			puts("not RIFF");
			exit(EXIT_FAILURE);
		}
//		printf("[%s]\n", buff.buf);
		readint();
		size = buff.bufint + 36;
//		printf("size = %d byte\n", buff.bufint + 36);

		/* WAVE�t�@�C�����ǂ����̊m�F */
		readchar();
		ret = strcmp(buff.buf,"WAVE");
		if(ret != 0){
			puts("not WAVE");
			exit(EXIT_FAILURE);
		}
//		printf("[%s]\n",buff.buf);
		
		/* fmt �I�[�f�B�I�t�H�[�}�b�g */
		fmt();
//		fmtview();
		
		/* LIST �X�L�b�v���� */
		list();
		
		/* data size �����t�@�C���X�^�[�g�n�_ */
		data();
//		printf("data start point: %d byte\n",ftell(buff.fpr));
		
		/* �t�@�C������� */
		fclose(buff.fpr);
		
		ret = size / fmtchunk.bytepersec;
//		printf("time: %d sec\n", ret);
	}
	return ret;
}

#endif	/* WAVE_C */
