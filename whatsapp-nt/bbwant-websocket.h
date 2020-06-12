#ifndef _BBWANT_WEBSOCKET_H_
#define _BBWANT_WEBSOCKET_H_


#define BBWANT_DEFAULT_WS_PORT ((int)7681)


typedef struct
{
  char* sWebsockUrlPartStore; // Gets mutilated eventually
  char* sWebsockOriginUrlStore;
  struct lws_client_connect_info* pxWsClientConnectInfo;
  struct lws_context_creation_info* pxWsContextCreationInfo;
  struct lws_context* pxWsContext;
  
} tBBWANT_ConnState;



#endif // #ifndef _BBWANT_WEBSOCKET_H_
