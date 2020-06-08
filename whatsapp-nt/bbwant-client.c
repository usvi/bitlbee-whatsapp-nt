#include "bbwant-client.h"
#include "bbwant-client-qrencode.h"

#include <stdio.h>
#include <stdint.h>
#include <string.h>


typedef struct
{
  uint8_t u8QrTestHello;

} tBBWANT_Client_Params;



static void BBWANT_Client_PrintHelp(void)
{
  printf("bitlbee-whatsapp-nt-client v. 0.0.1\n");
}

static uint8_t u8BBWANT_Client_GetArgs(int argc, char* argv[], tBBWANT_Client_Params* pxClientParams)
{
  // Caller should clear memory, so no need here.

  return 0;
}


int main(int argc, char* argv[])
{
  tBBWANT_Client_Params xClientParams;

  memset(&xClientParams, 0, sizeof(xClientParams));
  BBWANT_Client_PrintHelp();
  u8BBWANT_Client_GetArgs(argc, argv, &xClientParams);
  

  return 0;
}
