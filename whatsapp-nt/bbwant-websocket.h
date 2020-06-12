#ifndef _BBWANT_WEBSOCKET_H_
#define _BBWANT_WEBSOCKET_H_

#include <stdint.h>
#include <libwebsockets.h>

#define BBWANT_DEFAULT_WS_PORT ((int)7681)



typedef struct
{
  char* sWebsockUrlPartStore; // Gets mutilated eventually
  char* sWebsockOriginUrlStore;
  char* sWebsockRealPathStore;
  struct lws_client_connect_info* pxWsClientConnectInfo;
  struct lws_context_creation_info* pxWsContextCreationInfo;
  struct lws_context* pxWsContext;
  
} tBBWANT_ConnState;


uint8_t u8BBWANT_AllocateConnection(const char* sWsUrl, const char* sOriginUrl,
					   tBBWANT_ConnState* pxConnState);
uint8_t u8BBWANT_FreeConnection(tBBWANT_ConnState* pxConnState);
tBBWANT_ConnState* pxBBWANT_GetSetWebsockContext(tBBWANT_ConnState* pxConnState);  

#endif // #ifndef _BBWANT_WEBSOCKET_H_
