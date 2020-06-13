#include "bbwant-websocket.h"
#include "bbwant.h"

#include <stdint.h>
#include <libwebsockets.h>
#include <string.h>
#include <stdlib.h>



tBBWANT_ConnState* pxBBWANT_GetSetWebsockContext(tBBWANT_ConnState* pxConnState)
{
  static tBBWANT_ConnState* pxStoredConnState = NULL;

  if (pxConnState != NULL)
  {
    pxStoredConnState = pxConnState;
  }

  return pxStoredConnState;
}


static int iBBWANT_WebsockCallback(struct lws *wsi, enum lws_callback_reasons reason,
				   void *user, void *in, size_t len)
{

  switch (reason)
  {
  case LWS_CALLBACK_CLIENT_CONNECTION_ERROR:
    lwsl_err("CLIENT_CONNECTION_ERROR: %s\n",
	     in ? (char *)in : "(null)");
    break;

  case LWS_CALLBACK_CLIENT_ESTABLISHED:
    lwsl_notice("CONNE ESTABLISED\n");
    break;

  default:
    lwsl_notice("SOMETHING ELSE HAPPENET, PROBABLY NOT ERROR %d!\n", reason);
  }

  return 0;
}
  

static struct lws_protocols axBBWANT_WebsockProtocols[] =
{
  {
    "whatsapp-nt-minimal-client",
    iBBWANT_WebsockCallback,
    0,
    4000,
  },
  { NULL, NULL, 0, 0 }
};


static const struct lws_extension axBBWANT_WebsockExts[] =
{
  {
    "permessage-deflate",
    lws_extension_callback_pm_deflate,
    "permessage-deflate; client_max_window_bits"
  },
  {
    "deflate-frame",
    lws_extension_callback_pm_deflate,
    "deflate_frame"
  },
  { NULL, NULL, NULL }
};

uint8_t u8BBWANT_AllocateConnection(const char* sWsUrl, const char* sOriginUrl,
					   tBBWANT_ConnState** ppxConnState)
{
  // Everything needs to be malloced and zeroed.
  uint8_t u8RetVal = BBWANT_OK;
  const char* sParsedProto;
  const char* sParsedPath;
  int iTemp = 0;
  tBBWANT_ConnState* pxNewConnState = NULL;

  pxNewConnState = malloc(sizeof(tBBWANT_ConnState));

  
  if (pxNewConnState == NULL)
  {
    u8RetVal = BBWANT_ERROR;
  }
  else
  {
    // Creation successful, so assign pointer for exporting the stuff
    *ppxConnState = pxNewConnState;
    pxNewConnState->sWebsockUrlPartStore = NULL;
    pxNewConnState->sWebsockUrlPartStore = malloc(BBWANT_URL_PATH_SIZE);

    if (pxNewConnState->sWebsockUrlPartStore == NULL)
    {
      free(pxNewConnState);
      u8RetVal = BBWANT_ERROR;
    }
    else
    {
      pxNewConnState->sWebsockOriginUrlStore = NULL;
      pxNewConnState->sWebsockOriginUrlStore = malloc(BBWANT_URL_PATH_SIZE);

      if (pxNewConnState->sWebsockOriginUrlStore == NULL)
      {
	free(pxNewConnState->sWebsockUrlPartStore);
	free(pxNewConnState);
	u8RetVal = BBWANT_ERROR;
      }
      else
      {
	pxNewConnState->sWebsockRealPathStore = NULL;
	pxNewConnState->sWebsockRealPathStore = malloc(BBWANT_URL_PATH_SIZE);

	if (pxNewConnState->sWebsockRealPathStore == NULL)
	{
	  free(pxNewConnState->sWebsockOriginUrlStore);
	  free(pxNewConnState->sWebsockUrlPartStore);
	  free(pxNewConnState);
	  u8RetVal = BBWANT_ERROR;
	}
	else
	{
	  pxNewConnState->pxWsClientConnectInfo = NULL;
	  pxNewConnState->pxWsClientConnectInfo = malloc(sizeof(struct lws_client_connect_info));
	
	  if (pxNewConnState->pxWsClientConnectInfo == NULL)
	  {
	    free(pxNewConnState->sWebsockRealPathStore);
	    free(pxNewConnState->sWebsockOriginUrlStore);
	    free(pxNewConnState->sWebsockUrlPartStore);
	    free(pxNewConnState);
	    u8RetVal = BBWANT_ERROR;
	  }
	  else
	  {
	    pxNewConnState->pxWsContextCreationInfo = NULL;
	    pxNewConnState->pxWsContextCreationInfo = malloc(sizeof(struct lws_context_creation_info));
	  
	    if (pxNewConnState->pxWsContextCreationInfo == NULL)
	    {
	      free(pxNewConnState->pxWsClientConnectInfo);
	      free(pxNewConnState->sWebsockRealPathStore);
	      free(pxNewConnState->sWebsockOriginUrlStore);
	      free(pxNewConnState->sWebsockUrlPartStore);
	      free(pxNewConnState);
	      u8RetVal = BBWANT_ERROR;
	    }
	  }
	}
      }
    }
  }
  // All malloc'd, good. Zero everything in one go.
  memset(pxNewConnState->sWebsockUrlPartStore, 0, BBWANT_URL_PATH_SIZE);
  memset(pxNewConnState->sWebsockOriginUrlStore, 0, BBWANT_URL_PATH_SIZE);
  memset(pxNewConnState->sWebsockRealPathStore, 0, BBWANT_URL_PATH_SIZE);
  memset(pxNewConnState->pxWsClientConnectInfo, 0, sizeof(*(pxNewConnState->pxWsClientConnectInfo)));
  memset(pxNewConnState->pxWsContextCreationInfo, 0, sizeof(*(pxNewConnState->pxWsContextCreationInfo)));
  pxNewConnState->pxWsContext = NULL;

  // And now, do somewhat what we saw in the original websockets library
  // test-client.c
  strncpy(pxNewConnState->sWebsockUrlPartStore, sWsUrl, BBWANT_URL_PATH_SIZE - 1);
  strncpy(pxNewConnState->sWebsockOriginUrlStore, sOriginUrl, BBWANT_URL_PATH_SIZE - 1);

  pxNewConnState->pxWsClientConnectInfo->port = BBWANT_DEFAULT_WS_PORT;
  iTemp = lws_parse_uri(pxNewConnState->sWebsockUrlPartStore, &sParsedProto,
			&(pxNewConnState->pxWsClientConnectInfo->address),
			&(pxNewConnState->pxWsClientConnectInfo->port),
			&sParsedPath);

  if (iTemp != 0)
  {
    free(pxNewConnState->pxWsClientConnectInfo);
    free(pxNewConnState->sWebsockRealPathStore);
    free(pxNewConnState->sWebsockOriginUrlStore);
    free(pxNewConnState->sWebsockUrlPartStore);
    free(pxNewConnState);
    u8RetVal = BBWANT_ERROR;
  }
  else
  {
    // Add back leading /
    pxNewConnState->sWebsockRealPathStore[0] = '/';
    strncpy(pxNewConnState->sWebsockRealPathStore + 1, sParsedPath, BBWANT_URL_PATH_SIZE - 2);
    pxNewConnState->pxWsClientConnectInfo->path = pxNewConnState->sWebsockRealPathStore;

    pxNewConnState->pxWsContextCreationInfo->port = CONTEXT_PORT_NO_LISTEN;
    pxNewConnState->pxWsContextCreationInfo->protocols = axBBWANT_WebsockProtocols;
    pxNewConnState->pxWsContextCreationInfo->gid = -1;
    pxNewConnState->pxWsContextCreationInfo->uid = -1;

    pxNewConnState->pxWsContext = lws_create_context(pxNewConnState->pxWsContextCreationInfo);

    if (pxNewConnState->pxWsContext == NULL)
    {
      free(pxNewConnState->pxWsClientConnectInfo);
      free(pxNewConnState->sWebsockRealPathStore);
      free(pxNewConnState->sWebsockOriginUrlStore);
      free(pxNewConnState->sWebsockUrlPartStore);
      free(pxNewConnState);
      u8RetVal = BBWANT_ERROR;
    }
    else
    {
      pxNewConnState->pxWsClientConnectInfo->context = pxNewConnState->pxWsContext;
      pxNewConnState->pxWsClientConnectInfo->ssl_connection = 2; // FIXME: Use dynamic
      pxNewConnState->pxWsClientConnectInfo->host = pxNewConnState->pxWsClientConnectInfo->address;
      pxNewConnState->pxWsClientConnectInfo->origin = pxNewConnState->sWebsockOriginUrlStore;
      pxNewConnState->pxWsClientConnectInfo->ietf_version_or_minus_one = -1;
      pxNewConnState->pxWsClientConnectInfo->client_exts = axBBWANT_WebsockExts;
    }
  }
  pxNewConnState->pxWsClientConnectInfo->protocol = axBBWANT_WebsockProtocols[0].name;
  lws_client_connect_via_info(pxNewConnState->pxWsClientConnectInfo);

  lws_service(pxNewConnState->pxWsClientConnectInfo->context, 1000);



  return u8RetVal;
}

uint8_t u8BBWANT_FreeConnection(tBBWANT_ConnState* pxConnState)
{
  uint8_t u8RetVal = BBWANT_OK;
  
  lws_context_destroy(pxConnState->pxWsContext);
  free(pxConnState->pxWsClientConnectInfo);
  free(pxConnState->sWebsockRealPathStore);
  free(pxConnState->sWebsockOriginUrlStore);
  free(pxConnState->sWebsockUrlPartStore);
  free(pxConnState);

  return u8RetVal;
}
