#include "bbwant-client.h"
#include "bbwant-client-qrencode.h"

#include <stdio.h>
#include <stdint.h>
#include <string.h>


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

  return 0;
}


uint8_t u8MakeQrHelloTest(tBBWANT_Client_State* pxClientState)
{
  printf("QR Hello Test\n");
  QRcode* pxHelloQrCode = QRcode_encodeString8bit(BBWANT_QR_HELLO_TEST_URL, 0, QR_ECLEVEL_Q);
  iBBWANT_Client_WriteQRAsPNG(pxHelloQrCode, "/tmp/foo.png");
  
  QRcode_free(pxHelloQrCode);
  
  return 0;
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
    u8Ret = u8MakeQrHelloTest(&xClientState);
  }
  
  return u8Ret;
}
