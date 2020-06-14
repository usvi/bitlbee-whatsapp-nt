#ifndef _BBWANT_WEBSOCKET_H_
#define _BBWANT_WEBSOCKET_H_

#include <stdint.h>
#include <libwebsockets.h>

#define BBWANT_DEFAULT_WS_PORT ((int)7681)



typedef struct
{
  char* sWebsocketUrlPartStore; // Gets mutilated eventually
  char* sWebsocketOriginUrlStore;
  char* sWebsocketRealPathStore;
  struct lws_client_connect_info* pxWsClientConnectInfo;
  struct lws_context_creation_info* pxWsContextCreationInfo;
  struct lws_context* pxWsContext;
  
} tBBWANT_ConnState;


uint8_t u8BBWANT_Websocket_AllocateConnection(const char* sWsUrl, const char* sOriginUrl,
					   tBBWANT_ConnState** ppxConnState);
uint8_t u8BBWANT_Websocket_FreeConnection(tBBWANT_ConnState* pxConnState);
tBBWANT_ConnState* pxBBWANT_Websocket_GetSetContext(tBBWANT_ConnState** ppxConnState);  

#endif // #ifndef _BBWANT_WEBSOCKET_H_
