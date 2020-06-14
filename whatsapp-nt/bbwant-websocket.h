#ifndef _BBWANT_WEBSOCKET_H_
#define _BBWANT_WEBSOCKET_H_

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


tBBWANT_ConnState* pxBBWANT_Websocket_GetSetContext(tBBWANT_ConnState** ppxConnState);  

uint8_t u8BBWANT_Websocket_AllocateConnection(tBBWANT_ConnState** ppxConnState);
uint8_t u8BBWANT_Websocket_BuildConnection(const char* sWsUrl, const char* sOriginUrl,
					   tBBWANT_ConnState** ppxConnState);
uint8_t u8BBWANT_Websocket_Connect(tBBWANT_ConnState** ppxConnState);
uint8_t u8BBWANT_Websocket_Disconnect(tBBWANT_ConnState** ppxConnState);
uint8_t u8BBWANT_Websocket_FreeConnection(tBBWANT_ConnState* pxConnState);

#endif // #ifndef _BBWANT_WEBSOCKET_H_
