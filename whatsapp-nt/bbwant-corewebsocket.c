#include "bbwant-corewebsocket.h"

#include <stddef.h>
#include <string.h>


static tBBWANT_CoreWebsocketState* gpxWebsocketState = NULL;


uint8_t u8BBWANT_CoreWebsocket_Init(char* sWebsocketUrl)
{
  uint8_t u8RetVal = BBWANT_OK;

  gpxWebsocketState = malloc(sizeof(tBBWANT_CoreWebsocketState));

  if (gpxWebsocketState == NULL)
  {
    u8RetVal = BBWANT_ERROR;

    return u8RetVal;
  }

  memset(gpxWebsocketState, 0, sizeof(tBBWANT_CoreWebsocketState));

  return u8RetVal;
}

uint8_t u8BBWANT_CoreWebsocket_SetConnect(void)
{
  uint8_t u8RetVal = BBWANT_OK;

  return u8RetVal;
}

uint32_t u32BBWANT_CoreWebsocket_Service(void)
{
  uint32_t u32RetVal = 0;

  return u32RetVal;
}

uint32_t u32BBWANT_CoreWebsocket_QueueForSend(void* pData, uint32_t u32Size)
{
  uint32_t u32RetVal = 0;

  return u32RetVal;
}

uint32_t u32BBWANT_CoreWebsocket_DequeueReceived(void* pData, uint32_t u32Size)
{
  uint32_t u32RetVal = 0;

  return u32RetVal;
}

uint8_t u8BBWANT_CoreWebsocket_SetDisconnect(void)
{
  uint8_t u8RetVal = BBWANT_OK;

  return u8RetVal;
}

uint8_t u8BBWANT_CoreWebsocket_Deinit(void)
{
  uint8_t u8RetVal = BBWANT_OK;

  // Previously

  return u8RetVal;
}


// u8BBWANT_
