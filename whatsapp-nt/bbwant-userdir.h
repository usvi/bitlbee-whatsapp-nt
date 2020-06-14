#ifndef _BBWANT_USERDIR_H_
#define _BBWANT_USERDIR_H_

#include <stdint.h>

#define BBWANT_USERDIR_DIR_EXISTS (((uint16_t)1) << 0)
#define BBWANT_USERDIR_DIR_PROTOFILE_OK (((uint16_t)1) << 1)
#define BBWANT_USERDIR_DIR_KEYFILE_FORMAT_OK (((uint16_t)1) << 2)


uint8_t u8BBWANT_Userdir_AnalyzeStructure(uint16_t* pu16Result);
uint8_t u8BBWANT_Userdir_CreateDir(void);
uint8_t u8BBWANT_Userdir_WriteProtofile(char* sWriteProtoDesc);
uint8_t u8BBWANT_Userdir_ReadProtofile(char* sReadProtoDesc);

// 

#endif // #ifndef _BBWANT_USERDIR_H_
