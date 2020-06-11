#ifndef _BBWANT_BASE64_H_
#define _BBWANT_BASE64_H_


/**
 * usBBWANT_Base64Encode - Base64 encode
 * @src: Data to be encoded
 * @len: Length of the data to be encoded
 * @out_len: Pointer to output length variable, or %NULL if not used
 * Returns: Allocated buffer of out_len bytes of encoded data,
 * or %NULL on failure
 *
 * Caller is responsible for freeing the returned buffer. Returned buffer is
 * nul terminated to make it easier to use as a C string. The nul terminator is
 * not included in out_len.
 */
unsigned char* usBBWANT_Base64Encode(const unsigned char *src, size_t len,
				     size_t *out_len);

/**
 * usBBWANT_Base64Decode - Base64 decode
 * @src: Data to be decoded
 * @len: Length of the data to be decoded
 * @out_len: Pointer to output length variable
 * Returns: Allocated buffer of out_len bytes of decoded data,
 * or %NULL on failure
 *
 * Caller is responsible for freeing the returned buffer.
 */
unsigned char* usBBWANT_Base64Decode(const unsigned char *src, size_t len,
				     size_t *out_len);


#endif // #define _BBWANT_BASE64_H_
