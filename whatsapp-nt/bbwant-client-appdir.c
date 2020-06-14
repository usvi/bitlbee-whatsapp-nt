#include "bbwant-client-appdir.h"
#include "bbwant.h"

#include <stdint.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <string.h>
#include <stdio.h>
#include <dirent.h>


#define BBWANT_CLIENT_APPDIR_PROTOFILE "protoversion"


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
  char sBuf2[BBWANT_FILE_PATH_SIZE] = { 0 };
  DIR* pDir = NULL;

  *pu16Result = 0;
  u8RetVal = u8BBWANT_Client_Appdir_GetPath(sBuf1);

  if (u8RetVal == BBWANT_ERROR)
  {
    ;
  }
  else
  {
    // Check if the whole directory exists
    pDir = opendir(sBuf1);

    if (pDir == NULL)
    {
      ;
    }
    else
    {
      *pu16Result |= BBWANT_CLIENT_APPDIR_DIR_EXISTS;
      closedir(pDir);
    }
    // Hax, use the public function to see if the file exists XD
    u8RetVal = u8BBWANT_Client_Appdir_ReadProtofile(sBuf2);

    if (u8RetVal == BBWANT_OK)
    {
      *pu16Result |= BBWANT_CLIENT_APPDIR_PROTOFILE_OK;
    }
    u8RetVal = BBWANT_OK;
  }
  
  return u8RetVal;
}

//uint8_t u8BBWANT_Client_Appdir_CreateDir(void);

//uint8_t u8BBWANT_Client_Appdir_WriteProtofile(char* sWriteProtoDesc);

uint8_t u8BBWANT_Client_Appdir_ReadProtofile(char* sReadProtoDesc)
{
  uint8_t u8RetVal = BBWANT_OK;
  char sBuf1[BBWANT_FILE_PATH_SIZE] = { 0 };
  char sBuf2[BBWANT_FILE_PATH_SIZE] = { 0 };
  FILE* pProtofile = NULL;
  char* sTemp = NULL;
  
  u8RetVal = u8BBWANT_Client_Appdir_GetPath(sBuf1);

  if (u8RetVal == BBWANT_OK)
  {
    snprintf(sBuf2, BBWANT_FILE_PATH_SIZE - 1, "%s/%s",
	     sBuf1, BBWANT_CLIENT_APPDIR_PROTOFILE);

    // And try to open it
    pProtofile = fopen(sBuf2, "r+");

    if (pProtofile == NULL)
    {
      u8RetVal = BBWANT_ERROR;
    }
    else
    {
      // Try to read from the protofile
      memset(sBuf1, 0, sizeof(sBuf1));

      if (fgets(sBuf1, BBWANT_FILE_PATH_SIZE - 1, pProtofile) == NULL)
      {
	u8RetVal = BBWANT_ERROR;
	fclose(pProtofile);
      }
      else
      {
	fclose(pProtofile);

	// Terminate \n
	sTemp = strstr(sBuf1, "\n");

	if (sTemp != NULL)
	{
	  *sTemp = 0;
	}

	// Ok, if we now have something in sBuf1, then we have it
	if (strlen(sBuf1) > 0)
	{
	  // We have it! Copy out.
	  strncpy(sReadProtoDesc, sBuf1, BBWANT_FILE_PATH_SIZE - 1);
	}
	else
	{
	  u8RetVal = BBWANT_ERROR;
	}
      }
    }
  }
    
  return u8RetVal;
}
