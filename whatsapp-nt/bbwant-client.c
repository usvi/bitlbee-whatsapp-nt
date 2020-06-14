#include "bbwant-client.h"
#include "bbwant.h"
#include "bbwant-client-qrencode.h"
#include "bbwant-websocket.h"

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>


#define BBWANT_QR_HELLO_TEST_URL "https://www.google.com/search?q=hello+world"



typedef struct
{
  uint8_t u8ParamQrHelloTest;

} tBBWANT_Client_State;



static void BBWANT_Client_PrintHelp(void)
{
  printf("bitlbee-whatsapp-nt-client v. 0.0.1\n");
}

static uint8_t u8BBWANT_Client_GetArgs(int argc, char* argv[], tBBWANT_Client_State* pxClientState)
{
  // Caller should clear memory, so no need here.
  int i = 0;

  for (i = 1; i < argc; i++)
  {
    if (strcmp(argv[i], "--qr-hello-test") == 0)
    {
      pxClientState->u8ParamQrHelloTest = 1;
    }
  }

  return BBWANT_OK;
}


static uint8_t u8BBWANT_Client_MakeQrFileStringForUser(const char* sFormat, char* sFileString)
{
  uint8_t u8RetVal = BBWANT_OK;
  uid_t xUid;
  struct passwd* pxPasswd = NULL;

  memset(&xUid, 0, sizeof(xUid));

  xUid = geteuid(); // Always successful
  pxPasswd = getpwuid(xUid);

  if (!pxPasswd)
  {
    u8RetVal = BBWANT_ERROR;
  }
  else
  {
    snprintf(sFileString, BBWANT_FILE_PATH_SIZE, sFormat, pxPasswd->pw_name);
    u8RetVal = BBWANT_OK;
  }

  return u8RetVal;
}


static uint8_t u8BBWANT_Client_MakeQrHelloTest(tBBWANT_Client_State* pxClientState)
{
  uint8_t u8RetVal = BBWANT_OK;
  QRcode* pxHelloQrCode = NULL;
  char sQrPngFilePath[BBWANT_FILE_PATH_SIZE] = { 0 };
  
  
  printf("QR Hello Test\n");
  pxHelloQrCode = QRcode_encodeString8bit(BBWANT_QR_HELLO_TEST_URL, 0, QR_ECLEVEL_Q);

  if (pxHelloQrCode == NULL)
  {
    u8RetVal = BBWANT_ERROR;
  }
  else
  {
    u8RetVal = u8BBWANT_Client_MakeQrFileStringForUser(BBWANT_CLIENT_HELLO_TEST_QR_PATH_FORMAT,
						       sQrPngFilePath);

    if (u8RetVal == BBWANT_OK)
    {
      u8RetVal = u8BBWANT_Client_WriteQRAsPNG(pxHelloQrCode, sQrPngFilePath);

      if (u8RetVal == BBWANT_OK)
      {
	printf("Successfully wrote test QR image to %s\n", sQrPngFilePath);
      }
    }
    QRcode_free(pxHelloQrCode);
  }
  
  return u8RetVal;
}

uint8_t u8BBWANT_Client_Default_Actions(tBBWANT_Client_State* pxClientState)
{
  uint8_t u8RetVal = BBWANT_OK;
  uint16_t u16AppDirResult = 0;
  
  /*
  tBBWANT_ConnState* pxTempConnection;
  u8RetVal = u8BBWANT_Websocket_AllocateConnection(&pxTempConnection);

  if (u8RetVal != BBWANT_OK)
  {

  }
  else
  {
    pxBBWANT_Websocket_GetSetContext(&pxTempConnection);
    u8RetVal = u8BBWANT_Websocket_BuildConnection("wss://web.whatsapp.com/ws", "https://web.whatsapp.com", &pxTempConnection);
    //u8RetVal = u8BBWANT_Websocket_BuildConnection("ws://echo.websocket.org/?encoding=text", "https://www.websocket.org", &pxTempConnection);

    if (u8RetVal != BBWANT_OK)
    {

    }
    else
    {
      u8RetVal = u8BBWANT_Websocket_Connect(&pxTempConnection);

      if (u8RetVal == BBWANT_OK)
      {
	// Manage loop
	// Disconnect
	u8RetVal = u8BBWANT_Websocket_Disconnect(&pxTempConnection);
      }
    }
  }
  
  u8BBWANT_Websocket_FreeConnection(pxTempConnection);
  */

  u8BBWANT_Userdir_AnalyzeStructure(&u16AppDirResult);
  
  return u8RetVal;
}

int main(int argc, char* argv[])
{
  tBBWANT_Client_State xClientState;
  uint8_t u8Ret = 0;

  memset(&xClientState, 0, sizeof(xClientState));
  BBWANT_Client_PrintHelp();
  u8BBWANT_Client_GetArgs(argc, argv, &xClientState);
  
  if (xClientState.u8ParamQrHelloTest)
  {
    u8Ret = u8BBWANT_Client_MakeQrHelloTest(&xClientState);
  }
  else // Last item
  {
    u8Ret = u8BBWANT_Client_Default_Actions(&xClientState);
  }
  
  return u8Ret;
}
