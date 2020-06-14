#ifndef _BBWANT_CLIENT_APPDIR_H_
#define _BBWANT_CLIENT_APPDIR_H_


#include <stdint.h>

#define BBWANT_CLIENT_APPDIR_DIR_EXISTS (((uint16_t)1) << 0)
#define BBWANT_CLIENT_APPDIR_PROTOFILE_OK (((uint16_t)1) << 1)
#define BBWANT_CLIENT_APPDIR_KEYFILE_FORMAT_OK (((uint16_t)1) << 2)


uint8_t u8BBWANT_Client_Appdir_AnalyzeStructure(uint16_t* pu16Result);
uint8_t u8BBWANT_Client_Appdir_CreateDir(void);
uint8_t u8BBWANT_Client_Appdir_WriteProtofile(char* sWriteProtoDesc);
uint8_t u8BBWANT_Client_Appdir_ReadProtofile(char* sReadProtoDesc);

// 

#endif // #ifndef _BBWANT_CLIENT_APPDIR_H_
