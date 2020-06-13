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
  /*
        LWS_CALLBACK_OPENSSL_LOAD_EXTRA_CLIENT_VERIFY_CERTS     = 21,
        LWS_CALLBACK_OPENSSL_LOAD_EXTRA_SERVER_VERIFY_CERTS     = 22,
        LWS_CALLBACK_OPENSSL_PERFORM_CLIENT_CERT_VERIFICATION   = 23,
        LWS_CALLBACK_CLIENT_APPEND_HANDSHAKE_HEADER             = 24,
        LWS_CALLBACK_CONFIRM_EXTENSION_OKAY                     = 25,
        LWS_CALLBACK_CLIENT_CONFIRM_EXTENSION_SUPPORTED         = 26,
        LWS_CALLBACK_PROTOCOL_INIT                              = 27,
  */

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
					   tBBWANT_ConnState* pxConnState)
{
  // Everything needs to be malloced and zeroed.
  uint8_t u8RetVal = BBWANT_OK;
  const char* sParsedProto;
  const char* sParsedPath;
  int iTemp = 0;
    
  
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
	pxConnState->sWebsockRealPathStore = NULL;
	pxConnState->sWebsockRealPathStore = malloc(BBWANT_URL_PATH_SIZE);

	if (pxConnState->sWebsockRealPathStore == NULL)
	{
	  free(pxConnState->sWebsockOriginUrlStore);
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
	    free(pxConnState->sWebsockRealPathStore);
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
	      free(pxConnState->sWebsockRealPathStore);
	      free(pxConnState->sWebsockOriginUrlStore);
	      free(pxConnState->sWebsockUrlPartStore);
	      free(pxConnState);
	      u8RetVal = BBWANT_ERROR;
	    }
	  }
	}
      }
    }
  }
  // All malloc'd, good. Zero everything in one go.
  memset(pxConnState->sWebsockUrlPartStore, 0, BBWANT_URL_PATH_SIZE);
  memset(pxConnState->sWebsockOriginUrlStore, 0, BBWANT_URL_PATH_SIZE);
  memset(pxConnState->sWebsockRealPathStore, 0, BBWANT_URL_PATH_SIZE);
  memset(pxConnState->pxWsClientConnectInfo, 0, sizeof(*(pxConnState->pxWsClientConnectInfo)));
  memset(pxConnState->pxWsContextCreationInfo, 0, sizeof(*(pxConnState->pxWsContextCreationInfo)));
  pxConnState->pxWsContext = NULL;

  // And now, do somewhat what we saw in the original websockets library
  // test-client.c
  strncpy(pxConnState->sWebsockUrlPartStore, sWsUrl, BBWANT_URL_PATH_SIZE - 1);
  strncpy(pxConnState->sWebsockOriginUrlStore, sOriginUrl, BBWANT_URL_PATH_SIZE - 1);

  pxConnState->pxWsClientConnectInfo->port = BBWANT_DEFAULT_WS_PORT;
  iTemp = lws_parse_uri(pxConnState->sWebsockUrlPartStore, &sParsedProto,
			&(pxConnState->pxWsClientConnectInfo->address),
			&(pxConnState->pxWsClientConnectInfo->port),
			&sParsedPath);

  if (iTemp != 0)
  {
    free(pxConnState->pxWsClientConnectInfo);
    free(pxConnState->sWebsockRealPathStore);
    free(pxConnState->sWebsockOriginUrlStore);
    free(pxConnState->sWebsockUrlPartStore);
    free(pxConnState);
    u8RetVal = BBWANT_ERROR;
  }
  else
  {
    // Add back leading /
    pxConnState->sWebsockRealPathStore[0] = '/';
    strncpy(pxConnState->sWebsockRealPathStore + 1, sParsedPath, BBWANT_URL_PATH_SIZE - 2);
    pxConnState->pxWsClientConnectInfo->path = pxConnState->sWebsockRealPathStore;

    pxConnState->pxWsContextCreationInfo->port = CONTEXT_PORT_NO_LISTEN;
    pxConnState->pxWsContextCreationInfo->protocols = axBBWANT_WebsockProtocols;
    pxConnState->pxWsContextCreationInfo->gid = -1;
    pxConnState->pxWsContextCreationInfo->uid = -1;

    pxConnState->pxWsContext = lws_create_context(pxConnState->pxWsContextCreationInfo);

    if (pxConnState->pxWsContext == NULL)
    {
      free(pxConnState->pxWsClientConnectInfo);
      free(pxConnState->sWebsockRealPathStore);
      free(pxConnState->sWebsockOriginUrlStore);
      free(pxConnState->sWebsockUrlPartStore);
      free(pxConnState);
      u8RetVal = BBWANT_ERROR;
    }
    else
    {
      pxConnState->pxWsClientConnectInfo->context = pxConnState->pxWsContext;
      pxConnState->pxWsClientConnectInfo->ssl_connection = 1; // FIXME: Use dynamic
      pxConnState->pxWsClientConnectInfo->host = pxConnState->pxWsClientConnectInfo->address;
      pxConnState->pxWsClientConnectInfo->origin = pxConnState->sWebsockOriginUrlStore;
      pxConnState->pxWsClientConnectInfo->ietf_version_or_minus_one = -1;
      pxConnState->pxWsClientConnectInfo->client_exts = axBBWANT_WebsockExts;
    }
  }
  pxConnState->pxWsClientConnectInfo->protocol = axBBWANT_WebsockProtocols[0].name;
  lws_client_connect_via_info(pxConnState->pxWsClientConnectInfo);

  lws_service(pxConnState->pxWsClientConnectInfo->context, 1000);
  
  return u8RetVal;
}

uint8_t u8BBWANT_FreeConnection(tBBWANT_ConnState* pxConnState)
{
  lws_context_destroy(pxConnState->pxWsContext);

  free(pxConnState->sWebsockRealPathStore);
  free(pxConnState->sWebsockOriginUrlStore);
  free(pxConnState->sWebsockUrlPartStore);

  lws_context_destroy(pxConnState->pxWsContext);
  free(pxConnState->pxWsClientConnectInfo);
  free(pxConnState);

  return 0;
}
