#include "bbwant-client.h"
#include "bbwant-client-qrencode.h"

#include <stdio.h>
#include <stdint.h>
#include <string.h>


typedef struct
{
  uint8_t u8ParamQrTestHello;

} tBBWANT_Client_State;



static void BBWANT_Client_PrintHelp(void)
{
  printf("bitlbee-whatsapp-nt-client v. 0.0.1\n");
}

static uint8_t u8BBWANT_Client_GetArgs(int argc, char* argv[], tBBWANT_Client_State* pxClientState)
{
  // Caller should clear memory, so no need here.

  return 0;
}


int main(int argc, char* argv[])
{
  tBBWANT_Client_State xClientState;
  uint8_t u8Ret = 0;

  memset(&xClientState, 0, sizeof(xClientState));
  BBWANT_Client_PrintHelp();
  u8BBWANT_Client_GetArgs(argc, argv, &xClientState);
  
  if (xClientState.u8ParamQrTestHello)
  {
    //u8Ret = u8QrMakeHelloTest(&xClientState);
  }
  
  return u8Ret;
}
