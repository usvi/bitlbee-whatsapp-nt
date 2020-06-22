#ifndef _BBWANT_COREWEBSOCKET_H_
#define _BBWANT_COREWEBSOCKET_H_

#include "bbwant.h"

#include <stdint.h>
#include <gnutls/gnutls.h>


typedef struct
{
  char sHostname[BBWANT_URL_SIZE];
  uint16_t u16Port;
  uint8_t u8Secure;
  char sPath[BBWANT_URL_SIZE];
  char sOrigin[BBWANT_URL_SIZE];
  
} tBBWANT_CoreWebsocketUrl;

typedef struct
{
  gnutls_session_t xSession;
  
} tBBWANT_CoreWebsocketTls;

typedef struct
{
  tBBWANT_CoreWebsocketUrl xUrl;
  tBBWANT_CoreWebsocketTls xTls;
} tBBWANT_CoreWebsocketState;


#define BBWANT_COREWEBSOCKET_CB_ERR_FATAL (((uint32_t)1) << 0)
#define BBWANT_COREWEBSOCKET_CB_ERR_TOO_BIG (((uint32_t)1) << 1)
#define BBWANT_COREWEBSOCKET_CB_CONNECTING (((uint32_t)1) << 2)
#define BBWANT_COREWEBSOCKET_CB_CONNECTED (((uint32_t)1) << 3)
#define BBWANT_COREWEBSOCKET_CB_DISCONNECTING (((uint32_t)1) << 4)
#define BBWANT_COREWEBSOCKET_CB_MSGS_REMAIN (((uint32_t)1) << 5)



uint8_t u8BBWANT_CoreWebsocket_Init(tBBWANT_CoreWebsocketState** ppxWebsocketState);
uint8_t u8BBWANT_CoreWebsocket_ParseUrls(tBBWANT_CoreWebsocketState** ppxWebsocketState,
					 char* sWebsocketUrl, char* sOriginUrl);
uint8_t u8BBWANT_CoreWebsocket_SetConnect(tBBWANT_CoreWebsocketState** ppxWebsocketState);
uint32_t u32BBWANT_CoreWebsocket_Service(tBBWANT_CoreWebsocketState** ppxWebsocketState);
uint32_t u32BBWANT_CoreWebsocket_QueueForSend(tBBWANT_CoreWebsocketState** ppxWebsocketState,
					      void* pData, uint32_t u32Size);
uint32_t u32BBWANT_CoreWebsocket_DequeueReceived(tBBWANT_CoreWebsocketState** ppxWebsocketState,
						 void* pData, uint32_t u32Size);
uint8_t u8BBWANT_CoreWebsocket_SetDisconnect(tBBWANT_CoreWebsocketState** ppxWebsocketState);
uint8_t u8BBWANT_CoreWebsocket_Deinit(tBBWANT_CoreWebsocketState** ppxWebsocketState);


#endif // #ifndef_BBWANT_COREWEBSOCKET_H_
