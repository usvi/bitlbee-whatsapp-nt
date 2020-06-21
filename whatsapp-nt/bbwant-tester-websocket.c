#include "bbwant-tester-websocket.h"
#include "bbwant-corewebsocket.h"

#include <stdio.h>


int main()
{
  tBBWANT_CoreWebsocketState* pxState;
  uint8_t u8RetVal = BBWANT_OK;

  u8RetVal = u8BBWANT_CoreWebsocket_Init(&pxState, "wss://echo.websocket.org/?encoding=text",
					 "https://www.websocket.org");

  if (u8RetVal == BBWANT_OK)
  {
    printf("Retval OK\n");
  }
  else
  {
    printf("Retval FAIL\n");
  }
  
  u8BBWANT_CoreWebsocket_Deinit(&pxState);
  
  return 0;
}
