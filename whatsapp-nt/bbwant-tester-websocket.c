#include "bbwant-tester-websocket.h"
#include "bbwant-corewebsocket.h"

#include <stdio.h>


int main()
{
  tBBWANT_CoreWebsocketState* pxState;
  uint8_t u8RetVal = BBWANT_OK;

  u8RetVal = u8BBWANT_CoreWebsocket_Init(&pxState);
  
  if (u8RetVal == BBWANT_OK)
  {
    printf("Init retval OK\n");
  }
  else
  {
    printf("Init retval FAIL\n");
  }

  u8RetVal = u8BBWANT_CoreWebsocket_ParseUrls(&pxState,
					      "wss://echo.websocket.org:443/?encoding=text",
					      "https://www.websocket.org");

  if (u8RetVal == BBWANT_OK)
  {
    printf("Parse retval OK\n");
  }
  else
  {
    printf("Parse retval FAIL\n");
  }
  u8BBWANT_CoreWebsocket_Deinit(&pxState);
  
  return 0;
}
