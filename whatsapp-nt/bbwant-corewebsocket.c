#include "bbwant-corewebsocket.h"

#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>

//static tBBWANT_CoreWebsocketState* gpxWebsocketState = NULL;


uint8_t u8BBWANT_CoreWebsocket_ParseUrls(tBBWANT_CoreWebsocketState** ppxWebsocketState,
					 char* sWebsocketUrl, char* sOriginUrl)
{
  uint8_t u8RetVal = BBWANT_OK;
  // We could get any of these
  // wss://foo:234/baz
  // wss://foo/
  // wss://foo/asd
  // ws://foo:32/baz
  // ws://foo/baz
  // ws://foo/


  char sUrlBuf[BBWANT_URL_SIZE] = { 0 };
  char* sBufPos = NULL;

  strncpy(sUrlBuf, sWebsocketUrl, sizeof(sUrlBuf));
  
  if (sUrlBuf[BBWANT_URL_SIZE - 1] != 0)
  {
    u8RetVal = BBWANT_ERROR;

    return u8RetVal;
  }
  if (strncmp(sUrlBuf, "ws://", strlen("ws://")) == 0)
  {
    memmove(sUrlBuf, sUrlBuf + strlen("ws://"), BBWANT_URL_SIZE - strlen("ws://"));
    memset(sUrlBuf + BBWANT_URL_SIZE - strlen("ws://"), 0, strlen("ws://"));
  }
  else if (strncmp(sUrlBuf, "wss://", strlen("wss://")) == 0)
  {
    memmove(sUrlBuf, sUrlBuf + strlen("wss://"), BBWANT_URL_SIZE - strlen("wss://"));
    memset(sUrlBuf + BBWANT_URL_SIZE - strlen("wss://"), 0, strlen("wss://"));
    ((*ppxWebsocketState)->xUrl).u8Secure = 1;
  }
  else
  {
    u8RetVal = BBWANT_ERROR;

    return u8RetVal;
  }
  // Getting the hostname now
  sBufPos = strstr(sUrlBuf, "/");

  if (sBufPos == NULL)
  {
    u8RetVal = BBWANT_ERROR;

    return u8RetVal;
  }
  // Copy out amount of length find, eg. sBufPos - sUrlBuf
  memcpy(((*ppxWebsocketState)->xUrl).sHostname, sUrlBuf, sBufPos - sUrlBuf);
  // Move to left by the amount found
  memmove(sUrlBuf, sBufPos, sBufPos - sUrlBuf);
  // Zero rest of buffer, just in case
  memset(sUrlBuf + strlen(sBufPos), 0, BBWANT_URL_SIZE - strlen(sBufPos));
  // Hostname can have :81, so check:

  if ((sBufPos = strstr(((*ppxWebsocketState)->xUrl).sHostname, ":")) != NULL)
  {
    // OK we need to try to parse it
    *sBufPos = 0;
    sBufPos++; // We need to memset to zero later from this

    if (sscanf(sBufPos, "%u", (unsigned int*)(&(((*ppxWebsocketState)->xUrl).u16Port))) != 1)
    {
      // Something went wrong
      u8RetVal = BBWANT_ERROR;

      return u8RetVal;
    }
    // Otherwise all ok! Just need to zero stuff just in case.

    memset(((*ppxWebsocketState)->xUrl).sHostname + strlen(((*ppxWebsocketState)->xUrl).sHostname),
	   0, BBWANT_URL_SIZE - strlen(((*ppxWebsocketState)->xUrl).sHostname));

  }
  // If we are here, last part is path and ok to 
  memcpy(((*ppxWebsocketState)->xUrl).sPath, sUrlBuf, strlen(sUrlBuf));
  
  strncpy(((*ppxWebsocketState)->xUrl).sOrigin, sOriginUrl, sizeof(((*ppxWebsocketState)->xUrl).sOrigin));
  
  if (((*ppxWebsocketState)->xUrl).sOrigin[BBWANT_URL_SIZE - 1] != 0)
  {
    u8RetVal = BBWANT_ERROR;

    return u8RetVal;
  }
  return u8RetVal;
}


static uint8_t u8BBWANT_CoreWebsocket_InitTls(tBBWANT_CoreWebsocketState** ppxWebsocketState)
{
  uint8_t u8RetVal = BBWANT_OK;

  return u8RetVal;
}


uint8_t u8BBWANT_CoreWebsocket_Init(tBBWANT_CoreWebsocketState** ppxWebsocketState)
{
  uint8_t u8RetVal = BBWANT_OK;

  *ppxWebsocketState = malloc(sizeof(tBBWANT_CoreWebsocketState));

  if (*ppxWebsocketState == NULL)
  {
    u8RetVal = BBWANT_ERROR;

    return u8RetVal;
  }
  memset(*ppxWebsocketState, 0, sizeof(tBBWANT_CoreWebsocketState));

  if ((*ppxWebsocketState)->xUrl.u8Secure)
  {
    u8RetVal = u8BBWANT_CoreWebsocket_InitTls(ppxWebsocketState);
  }
  
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

  if (*ppxWebsocketState != NULL)
  {
    free(*ppxWebsocketState);
  }

  return u8RetVal;
}


// u8BBWANT_
