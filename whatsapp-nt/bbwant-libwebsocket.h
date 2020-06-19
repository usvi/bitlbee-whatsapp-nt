#ifndef _BBWANT_LIBWEBSOCKET_H_
#define _BBWANT_LIBWEBSOCKET_H_

#include <stdint.h>
#include <libwebsockets.h>

#define BBWANT_DEFAULT_WS_PORT ((int)443)



typedef struct
{
  char* sWebsocketUrlPartStore; // Gets mutilated eventually
  char* sWebsocketOriginUrlStore;
  char* sWebsocketRealPathStore;
  struct lws_client_connect_info* pxWsClientConnectInfo;
  struct lws_context_creation_info* pxWsContextCreationInfo;
  struct lws_context* pxWsContext;
  struct lws* pxConnection;
  uint8_t u8Connecting;
  
} tBBWANT_ConnState;


tBBWANT_ConnState* pxBBWANT_LibWebsocket_GetSetContext(tBBWANT_ConnState** ppxConnState);  

uint8_t u8BBWANT_LibWebsocket_AllocateConnection(tBBWANT_ConnState** ppxConnState);
uint8_t u8BBWANT_LibWebsocket_BuildConnection(const char* sWsUrl, const char* sOriginUrl,
					   tBBWANT_ConnState** ppxConnState);
uint8_t u8BBWANT_LibWebsocket_Connect(tBBWANT_ConnState** ppxConnState);
uint8_t u8BBWANT_LibWebsocket_Disconnect(tBBWANT_ConnState** ppxConnState);
uint8_t u8BBWANT_LibWebsocket_FreeConnection(tBBWANT_ConnState* pxConnState);

#endif // #ifndef _BBWANT_LIBWEBSOCKET_H_
