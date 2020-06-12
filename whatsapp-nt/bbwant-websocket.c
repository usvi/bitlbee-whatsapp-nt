#include "bbwant-websocket.h"
#include "bbwant.h"

#include <stdint.h>
#include <libwebsockets.h>
#include <string.h>
#include <stdlib.h>

/*
static struct lws_client_connect_info gxBBWANT_ClientConnectInfo;
static struct lws_context_creation_info gxBBWANT_ContextCreationInfo;
*/

/*
struct lws_client_connect_info {
    struct lws_context * context;
    const char * address;
    int port;
    int ssl_connection;
    const char * path;
    const char * host;
    const char * origin;
    const char * protocol;
    int ietf_version_or_minus_one;
    void * userdata;
    const struct lws_extension * client_exts;
};
*/

static tBBWANT_ConnState* pxBBWANT_GetSetWebsockContext(tBBWANT_ConnState* pxConnState)
{
  static tBBWANT_ConnState* pxStoredConnState = NULL;

  if (pxConnState != NULL)
  {
    pxStoredConnState = pxConnState;
  }

  return pxStoredConnState;
}

static uint8_t u8BBWANT_AllocateConnection(const char* sWsUrl, tBBWANT_ConnState* pxConnState)
{
  // We need to malloc all of these eventually
  /*
  memset(&gxBBWANT_ClientConnectInfo, 0, sizeof(gxBBWANT_ClientConnectInfo));
  memset(&gxBBWANT_ContextCreationInfo, 0, sizeof(gxBBWANT_ContextCreationInfo));

  gxBBWANT_ClientConnectInfo.port = BBWANT_DEFAULT_WS_PORT;
  
  //lws_parse_uri(sWsUrl, &(
  */
  
  return 0;
}

static uint8_t u8BBWANT_FreeConnection(tBBWANT_ConnState* pxConnState)
{
  free(pxConnState->sWebsockUrlPartStore);
  free(pxConnState->pxWsClientConnectInfo);
  free(pxConnState->pxWsContextCreationInfo);
  free(pxConnState->pxWsContext);
  free(pxConnState);
  
  return 0;
}
