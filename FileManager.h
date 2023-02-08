#ifndef	FILEMANAGER_H
#define	FILEMANAGER_H

#include <string.h>

#include "usr_style.h"
#include "usr_define.h"
#include "usr_macro.h"

extern int16_t File_Load(int8_t *, void *, size_t, size_t);
extern int16_t FileHeader_Load(int8_t *, void *, size_t, size_t);
extern int16_t File_strSearch(FILE *, char *, int, long);
extern int16_t GetFileLength(int8_t *, int32_t *);
extern int16_t	SetQuarterFont(int8_t *, int8_t *);
extern void *MyMalloc(int32_t);
extern void *MyMallocJ(int32_t);
extern void *MyMallocHi(int32_t);
extern int16_t MyMfree(void *);
extern int16_t MyMfreeJ(void *);
extern int16_t MyMfreeHi(void *);
extern int32_t MaxMemSize(int8_t);
extern int16_t Load_MACS_List(	int8_t *, int8_t (*)[256], uint32_t *);
extern int16_t Get_MACS_File(	int8_t *, int8_t (*)[256], uint32_t *);
extern int32_t GetHisFileCnt(int8_t *);
extern int32_t SetHisFileCnt(int8_t *);
extern uint8_t SetKeyInfo(uint8_t);
extern int16_t Get_BMP_File(int8_t *, uint32_t *);
extern int16_t IsArriveDir(int8_t *);

#endif	/* FILEMANAGER_H */
