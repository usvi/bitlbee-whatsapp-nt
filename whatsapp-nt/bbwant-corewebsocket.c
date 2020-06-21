#include "bbwant-corewebsocket.h"

#include <stddef.h>
#include <string.h>


//static tBBWANT_CoreWebsocketState* gpxWebsocketState = NULL;


static uint8_t u8BBWANT_CoreWebsocket_ParseUrl(char* sWebsocketUrl)
{
  uint8_t u8RetVal = BBWANT_OK;
  // We could get any of these
  // wss://foo:234/baz
  // wss://foo/
  // wss://foo/asd
  // ws://foo:32/baz
  // ws://foo/baz
  // ws://foo/

  /*
  char sUrlBuf[BBWANT_URL_SIZE] = { 0 };
  strncpy(sUrlBuf, sWebsocketUrl, sizeof(sUrlBuf));

  if (sUrlBuf[BBWANT_URL_SIZE - 1] != 0)
  {
    u8RetVal = BBWANT_ERROR;

    return u8RetVal;
  }
  
  if (strstr(sUrlBuf, 
  
  */
  //if (strncmp(sWebsocketUrl,

  return u8RetVal;
}



uint8_t u8BBWANT_CoreWebsocket_Init(tBBWANT_CoreWebsocketState** ppxWebsocketState,
				    char* sWebsocketUrl, char* sWebsocketOrigin)
{
  uint8_t u8RetVal = BBWANT_OK;

  
  return u8RetVal;
}

uint8_t u8BBWANT_CoreWebsocket_SetConnect(tBBWANT_CoreWebsocketState** ppxWebsocketState)
{
  uint8_t u8RetVal = BBWANT_OK;

  return u8RetVal;
}

uint32_t u32BBWANT_CoreWebsocket_Service(tBBWANT_CoreWebsocketState** ppxWebsocketState)
{
  uint32_t u32RetVal = 0;

  return u32RetVal;
}

uint32_t u32BBWANT_CoreWebsocket_QueueForSend(tBBWANT_CoreWebsocketState** ppxWebsocketState,
					      void* pData, uint32_t u32Size)
{
  uint32_t u32RetVal = 0;

  return u32RetVal;
}

uint32_t u32BBWANT_CoreWebsocket_DequeueReceived(tBBWANT_CoreWebsocketState** ppxWebsocketState,
						 void* pData, uint32_t u32Size)
{
  uint32_t u32RetVal = 0;

  return u32RetVal;
}

uint8_t u8BBWANT_CoreWebsocket_SetDisconnect(tBBWANT_CoreWebsocketState** ppxWebsocketState)
{
  uint8_t u8RetVal = BBWANT_OK;

  return u8RetVal;
}

uint8_t u8BBWANT_CoreWebsocket_Deinit(tBBWANT_CoreWebsocketState** ppxWebsocketState)
{
  uint8_t u8RetVal = BBWANT_OK;

  // Previously

  return u8RetVal;
}


// u8BBWANT_
