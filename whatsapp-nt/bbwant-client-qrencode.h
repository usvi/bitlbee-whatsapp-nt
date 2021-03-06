#ifndef _BBWANT_CLIENT_QRENCODE_H_
#define _BBWANT_CLIENT_QRENCODE_H_

#include <stdint.h>
#include <qrencode.h>


#define BBWANT_CLIENT_QR_ELEMENT_SIZE (12)
#define BBWANT_CLIENT_QR_MARGIN (2)


uint8_t u8BBWANT_Client_WriteQRAsPNG(QRcode *qrcode, const char *outfile);


#endif // #ifdef _BBWANT_CLIENT_QRENCODE_H_
