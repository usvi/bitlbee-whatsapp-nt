#include "bbwant-client-appdir.h"
#include "bbwant.h"

#include <stdint.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <string.h>
#include <stdio.h>


static uint8_t u8BBWANT_Client_Appdir_GetPath(char* sAppUserdir)
{
  uint8_t u8RetVal = BBWANT_OK;
  uid_t xUid;
  struct passwd* pxPasswd = NULL;

  memset(&xUid, 0, sizeof(xUid));

  xUid = geteuid(); // Always successful
  pxPasswd = getpwuid(xUid);

  if (pxPasswd == NULL)
  {
    u8RetVal = BBWANT_ERROR;
  }
  else
  {
    snprintf(sAppUserdir, BBWANT_FILE_PATH_SIZE - 1, "%s/.bbwhatsapp-nt-client", pxPasswd->pw_dir);
  }

  return u8RetVal;
}

uint8_t u8BBWANT_Client_Appdir_AnalyzeStructure(uint16_t* pu16Result)
{
  uint8_t u8RetVal = BBWANT_OK;
  char sBuf1[BBWANT_FILE_PATH_SIZE] = { 0 };
  //char sBuf2[BBWANT_FILE_PATH_SIZE] = { 0 };

  u8RetVal = u8BBWANT_Client_Appdir_GetPath(sBuf1);

  if (u8RetVal == BBWANT_ERROR)
  {
    ;
  }
  else
  {
    printf("appdir will be >%s<\n", sBuf1);
  }
  
  return u8RetVal;
}

uint8_t u8BBWANT_Client_Appdir_AnalyzeStructure(uint16_t* pu16Result);
//uint8_t u8BBWANT_Client_Appdir_CreateDir(void);
//uint8_t u8BBWANT_Client_Appdir_WriteProtofile(char* sWriteProtoDesc);
//uint8_t u8BBWANT_Client_Appdir_ReadProtofile(char* sReadProtoDesc);

