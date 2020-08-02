#ifndef _BBWANT_COREWEBSOCKET_H_
#define _BBWANT_COREWEBSOCKET_H_

#include "bbwant.h"

#include <stdint.h>
#include <gnutls/gnutls.h>


#define BBWANT_CAFILE "/etc/ssl/certs/ca-certificates.crt"


typedef struct
{
  char sHostname[BBWANT_URL_SIZE];
  uint16_t u16Port;
  uint8_t u8Secure;
  char sPath[BBWANT_URL_SIZE];
  char sOrigin[BBWANT_URL_SIZE];
  
} tBBWANT_CoreWebsocketUrl;

typedef struct
{
  gnutls_session_t xSession;
  gnutls_certificate_credentials_t xCredentials;
  
} tBBWANT_CoreWebsocketTls;

#define BBWANT_COREWEBSOCKET_ERR_FATAL (((uint32_t)1) << 0)
#define BBWANT_COREWEBSOCKET_ERR_NONFATAL (((uint32_t)1) << 1)
#define BBWANT_COREWEBSOCKET_CONNECTING (((uint32_t)1) << 2)
#define BBWANT_COREWEBSOCKET_CONNECTED (((uint32_t)1) << 3)
#define BBWANT_COREWEBSOCKET_DISCONNECTING (((uint32_t)1) << 4)
#define BBWANT_COREWEBSOCKET_RECV_MSGS_REMAIN (((uint32_t)1) << 5)
#define BBWANT_COREWEBSOCKET_SEND_MSGS_RAMAIN (((uint32_t)1) << 6)


typedef struct
{
  tBBWANT_CoreWebsocketUrl xUrl;
  tBBWANT_CoreWebsocketTls xTls;
  int iTcpSocket;
} tBBWANT_CoreWebsocketState;





uint8_t u8BBWANT_CoreWebsocket_Init(tBBWANT_CoreWebsocketState** ppxWebsocketState);
uint8_t u8BBWANT_CoreWebsocket_ParseUrls(tBBWANT_CoreWebsocketState** ppxWebsocketState,
					 char* sWebsocketUrl, char* sOriginUrl);
uint8_t u8BBWANT_CoreWebsocket_Connect(tBBWANT_CoreWebsocketState** ppxWebsocketState);
uint32_t u32BBWANT_CoreWebsocket_Service(tBBWANT_CoreWebsocketState** ppxWebsocketState);
uint32_t u32BBWANT_CoreWebsocket_QueueForSend(tBBWANT_CoreWebsocketState** ppxWebsocketState,
					      void* pData, uint32_t u32Size);
uint32_t u32BBWANT_CoreWebsocket_PopReceived(tBBWANT_CoreWebsocketState** ppxWebsocketState,
					     void* pData, uint32_t u32Size);
uint8_t u8BBWANT_CoreWebsocket_Disconnect(tBBWANT_CoreWebsocketState** ppxWebsocketState);
uint8_t u8BBWANT_CoreWebsocket_Deinit(tBBWANT_CoreWebsocketState** ppxWebsocketState);


#endif // #ifndef_BBWANT_COREWEBSOCKET_H_
