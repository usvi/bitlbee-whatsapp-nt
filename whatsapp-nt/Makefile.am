
bin_PROGRAMS = \
	bbwhatsapp-nt-client



bbwhatsapp_nt_client_LDFLAGS = \
	$(QRENCODE_LIBS) \
	$(PNG_LIBS) \
	$(WEBSOCKETS_LIBS)

bbwhatsapp_nt_client_CFLAGS = \
	-Wall \
	-g

bbwhatsapp_nt_client_SOURCES = \
	bbwant.h \
	bbwant-curve25519-donna.c \
	bbwant-curve25519-donna.h \
	bbwant-base64.c \
	bbwant-base64.h \
	bbwant-libwebsocket.c \
	bbwant-libwebsocket.h \
	bbwant-client.c \
	bbwant-client.h \
	bbwant-client-appdir.c \
	bbwant-client-appdir.h \
	bbwant-client-qrencode.c \
	bbwant-client-qrencode.h



#bbwhatsapp_nt_client_websocket_LDFLAGS = \
#	$(GNUTLS_LIBS)

#bbwhatsapp_nt_client_websocket_CFLAGS = \
#	-Wall \
#	-g

#bbwhatsapp_nt_client_websocket_SOURCES = \
#	bbwant.h \
#	bbwant-corewebsocket.c \
#	bbwant-corewebsocket.h \
#	bbwant-corewebsocket-client.c \
#	bbwant-corewebsocket-client.h

