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

static uint8_t u8BBWANT_AllocateConnection(const char* sWsUrl, const char* sOriginUrl,
					   tBBWANT_ConnState* pxConnState)
{
  // Everything needs to be malloced and zeroed.
  uint8_t u8RetVal = BBWANT_OK;
    
  pxConnState = NULL;
  pxConnState = malloc(sizeof(tBBWANT_ConnState));

  if (pxConnState == NULL)
  {
    u8RetVal = BBWANT_ERROR;
  }
  else
  {
    pxConnState->sWebsockUrlPartStore = NULL;
    pxConnState->sWebsockUrlPartStore = malloc(BBWANT_URL_PATH_SIZE);

    if (pxConnState->sWebsockUrlPartStore == NULL)
    {
      free(pxConnState);
      u8RetVal = BBWANT_ERROR;
    }
    else
    {
      pxConnState->sWebsockOriginUrlStore = NULL;
      pxConnState->sWebsockOriginUrlStore = malloc(BBWANT_URL_PATH_SIZE);

      if (pxConnState->sWebsockOriginUrlStore == NULL)
      {
	free(pxConnState->sWebsockUrlPartStore);
	free(pxConnState);
	u8RetVal = BBWANT_ERROR;
      }
      else
      {
	pxConnState->pxWsClientConnectInfo = NULL;
	pxConnState->pxWsClientConnectInfo = malloc(sizeof(struct lws_client_connect_info));
	
	if (pxConnState->pxWsClientConnectInfo == NULL)
	{
	  free(pxConnState->sWebsockOriginUrlStore);
	  free(pxConnState->sWebsockUrlPartStore);
	  free(pxConnState);
	  u8RetVal = BBWANT_ERROR;
	}
	else
	{
	  pxConnState->pxWsContextCreationInfo = NULL;
	  pxConnState->pxWsContextCreationInfo = malloc(sizeof(struct lws_context_creation_info));
	  
	  if (pxConnState->pxWsContextCreationInfo == NULL)
	  {
	    free(pxConnState->pxWsClientConnectInfo);
	    free(pxConnState->sWebsockOriginUrlStore);
	    free(pxConnState->sWebsockUrlPartStore);
	    free(pxConnState);
	    u8RetVal = BBWANT_ERROR;
	  }
	}
      }
    }
  }
  // All malloc'd, good. Zero everything in one go.
  memset(pxConnState->sWebsockUrlPartStore, 0, BBWANT_URL_PATH_SIZE);
  memset(pxConnState->sWebsockOriginUrlStore, 0, BBWANT_URL_PATH_SIZE);
  memset(pxConnState->pxWsClientConnectInfo, 0, sizeof(*(pxConnState->pxWsClientConnectInfo)));
  memset(pxConnState->pxWsContextCreationInfo, 0, sizeof(*(pxConnState->pxWsContextCreationInfo)));
  pxConnState->pxWsContext = NULL;
  
  return u8RetVal;
}

static uint8_t u8BBWANT_FreeConnection(tBBWANT_ConnState* pxConnState)
{
  free(pxConnState->sWebsockUrlPartStore);
  free(pxConnState->pxWsClientConnectInfo);
  free(pxConnState->pxWsContextCreationInfo);
  lws_context_destroy(pxConnState->pxWsContext);
  free(pxConnState);
  
  return 0;
}
