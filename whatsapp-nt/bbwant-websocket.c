#include "bbwant-websocket.h"
#include "bbwant.h"

#include <stdint.h>
#include <libwebsockets.h>
#include <string.h>
#include <stdlib.h>

static uint8_t gu8Connecting;


tBBWANT_ConnState* pxBBWANT_GetSetWebsockContext(tBBWANT_ConnState* pxConnState)
{
  static tBBWANT_ConnState* pxStoredConnState = NULL;

  if (pxConnState != NULL)
  {
    pxStoredConnState = pxConnState;
  }

  return pxStoredConnState;
}

static void BBWANT_WebsockPrintCbReason(enum lws_callback_reasons reason)
{
  switch (reason)
  {
  case LWS_CALLBACK_ESTABLISHED:
    lwsl_notice("LWS_CALLBACK_ESTABLISHED\n");
    break;
  case LWS_CALLBACK_CLIENT_CONNECTION_ERROR:
    lwsl_notice("WS_CALLBACK_CLIENT_CONNECTION_ERROR\n");
    break;
  case LWS_CALLBACK_CLIENT_FILTER_PRE_ESTABLISH:
    lwsl_notice("LWS_CALLBACK_CLIENT_FILTER_PRE_ESTABLISH\n");
    break;
  case LWS_CALLBACK_CLIENT_ESTABLISHED:
    lwsl_notice("LWS_CALLBACK_CLIENT_ESTABLISHED\n");
    break;
  case LWS_CALLBACK_CLOSED:
    lwsl_notice("LWS_CALLBACK_CLOSED\n");
    break;
  case LWS_CALLBACK_CLOSED_HTTP:
    lwsl_notice("LWS_CALLBACK_CLOSED_HTTP\n");
    break;
  case LWS_CALLBACK_RECEIVE:
    lwsl_notice("LWS_CALLBACK_RECEIVE\n");
    break;
  case LWS_CALLBACK_RECEIVE_PONG:
    lwsl_notice("LWS_CALLBACK_RECEIVE_PONG\n");
    break;
  case LWS_CALLBACK_CLIENT_RECEIVE:
    lwsl_notice("LWS_CALLBACK_CLIENT_RECEIVE\n");
    break;
  case LWS_CALLBACK_CLIENT_RECEIVE_PONG:
    lwsl_notice("LWS_CALLBACK_CLIENT_RECEIVE_PONG\n");
    break;
  case LWS_CALLBACK_CLIENT_WRITEABLE:
    lwsl_notice("LWS_CALLBACK_CLIENT_WRITEABLE\n");
    break;
  case LWS_CALLBACK_SERVER_WRITEABLE:
    lwsl_notice("LWS_CALLBACK_SERVER_WRITEABLE\n");
    break;
  case LWS_CALLBACK_HTTP:
    lwsl_notice("LWS_CALLBACK_HTTP\n");
    break;
  case LWS_CALLBACK_HTTP_BODY:
    lwsl_notice("LWS_CALLBACK_HTTP_BODY\n");
    break;
  case LWS_CALLBACK_HTTP_BODY_COMPLETION:
    lwsl_notice("LWS_CALLBACK_HTTP_BODY_COMPLETION\n");
    break;
  case LWS_CALLBACK_HTTP_FILE_COMPLETION:
    lwsl_notice("LWS_CALLBACK_HTTP_FILE_COMPLETION\n");
    break;
  case LWS_CALLBACK_HTTP_WRITEABLE:
    lwsl_notice("LWS_CALLBACK_HTTP_WRITEABLE\n");
    break;
  case LWS_CALLBACK_FILTER_NETWORK_CONNECTION:
    lwsl_notice("LWS_CALLBACK_FILTER_NETWORK_CONNECTION\n");
    break;
  case LWS_CALLBACK_FILTER_HTTP_CONNECTION:
    lwsl_notice("LWS_CALLBACK_FILTER_HTTP_CONNECTION\n");
    break;
  case LWS_CALLBACK_SERVER_NEW_CLIENT_INSTANTIATED:
    lwsl_notice("LWS_CALLBACK_SERVER_NEW_CLIENT_INSTANTIATED\n");
    break;
  case LWS_CALLBACK_FILTER_PROTOCOL_CONNECTION:
    lwsl_notice("LWS_CALLBACK_FILTER_PROTOCOL_CONNECTION\n");
    break;
  case LWS_CALLBACK_OPENSSL_LOAD_EXTRA_CLIENT_VERIFY_CERTS:
    lwsl_notice("LWS_CALLBACK_OPENSSL_LOAD_EXTRA_CLIENT_VERIFY_CERTS\n");
    break;
  case LWS_CALLBACK_OPENSSL_LOAD_EXTRA_SERVER_VERIFY_CERTS:
    lwsl_notice("LWS_CALLBACK_OPENSSL_LOAD_EXTRA_SERVER_VERIFY_CERTS\n");
    break;
  case LWS_CALLBACK_OPENSSL_PERFORM_CLIENT_CERT_VERIFICATION:
    lwsl_notice("LWS_CALLBACK_OPENSSL_PERFORM_CLIENT_CERT_VERIFICATION\n");
    break;
  case LWS_CALLBACK_CLIENT_APPEND_HANDSHAKE_HEADER:
    lwsl_notice("LWS_CALLBACK_CLIENT_APPEND_HANDSHAKE_HEADER\n");
    break;
  case LWS_CALLBACK_CONFIRM_EXTENSION_OKAY:
    lwsl_notice("LWS_CALLBACK_CONFIRM_EXTENSION_OKAY\n");
    break;
  case LWS_CALLBACK_CLIENT_CONFIRM_EXTENSION_SUPPORTED:
    lwsl_notice("LWS_CALLBACK_CLIENT_CONFIRM_EXTENSION_SUPPORTED\n");
    break;
  case LWS_CALLBACK_PROTOCOL_INIT:
    lwsl_notice("LWS_CALLBACK_PROTOCOL_INIT\n");
    break;
  case LWS_CALLBACK_PROTOCOL_DESTROY:
    lwsl_notice("LWS_CALLBACK_PROTOCOL_DESTROY\n");
    break;
  case LWS_CALLBACK_WSI_CREATE:
    lwsl_notice("LWS_CALLBACK_WSI_CREATE\n");
    break;
  case LWS_CALLBACK_WSI_DESTROY:
    lwsl_notice("LWS_CALLBACK_WSI_DESTROY\n");
    break;
  case LWS_CALLBACK_GET_THREAD_ID:
    lwsl_notice("LWS_CALLBACK_GET_THREAD_ID\n");
    break;
  case LWS_CALLBACK_ADD_POLL_FD:
    lwsl_notice("LWS_CALLBACK_ADD_POLL_FD\n");
    break;
  case LWS_CALLBACK_DEL_POLL_FD:
    lwsl_notice("LWS_CALLBACK_DEL_POLL_FD\n");
    break;
  case LWS_CALLBACK_CHANGE_MODE_POLL_FD:
    lwsl_notice("LWS_CALLBACK_CHANGE_MODE_POLL_FD\n");
    break;
  case LWS_CALLBACK_LOCK_POLL:
    lwsl_notice("LWS_CALLBACK_LOCK_POLL\n");
    break;
  case LWS_CALLBACK_UNLOCK_POLL:
    lwsl_notice("LWS_CALLBACK_UNLOCK_POLL\n");
    break;
  case LWS_CALLBACK_OPENSSL_CONTEXT_REQUIRES_PRIVATE_KEY:
    lwsl_notice("LWS_CALLBACK_OPENSSL_CONTEXT_REQUIRES_PRIVATE_KEY\n");
    break;
  case LWS_CALLBACK_WS_PEER_INITIATED_CLOSE:
    lwsl_notice("LWS_CALLBACK_WS_PEER_INITIATED_CLOSE\n");
    break;
  case LWS_CALLBACK_WS_EXT_DEFAULTS:
    lwsl_notice("LWS_CALLBACK_WS_EXT_DEFAULTS\n");
    break;
  default:
    lwsl_notice("SOMETHING ELSE HAPPENED\n");
  }

}


static int iBBWANT_WebsockCallback(struct lws *wsi, enum lws_callback_reasons reason,
				   void *user, void *in, size_t len)
{
  BBWANT_WebsockPrintCbReason(reason);
  
  switch (reason)
  {
  case LWS_CALLBACK_CLIENT_CONNECTION_ERROR:
    gu8Connecting = 0;
    break;
  case LWS_CALLBACK_CLIENT_ESTABLISHED:
    gu8Connecting = 0;
    break;
  default:
    break;
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
  struct lws* pxConnectResult;

  gu8Connecting = 0;
  lws_set_log_level(2047, NULL);
  
  
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
  gu8Connecting = 1;
  pxConnectResult = lws_client_connect_via_info(pxNewConnState->pxWsClientConnectInfo);

  if (pxConnectResult != NULL)
  {
    while(gu8Connecting)
    {
      lws_service(pxNewConnState->pxWsClientConnectInfo->context, 25);
    }
  }


  return u8RetVal;
}

uint8_t u8BBWANT_FreeConnection(tBBWANT_ConnState* pxConnState)
{
  uint8_t u8RetVal = BBWANT_OK;
  
  lws_context_destroy(pxConnState->pxWsContext);
  free(pxConnState->pxWsContextCreationInfo);
  free(pxConnState->pxWsClientConnectInfo);
  free(pxConnState->sWebsockRealPathStore);
  free(pxConnState->sWebsockOriginUrlStore);
  free(pxConnState->sWebsockUrlPartStore);
  free(pxConnState);

  return u8RetVal;
}
