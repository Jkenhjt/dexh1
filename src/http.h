#ifndef HTTP_H
#define HTTP_H

#ifdef __cplusplus
extern "C" {
#endif

#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "hash_table.h"

typedef struct
{
  dexh1_hash_table_t ht;
} dexh1_http;


void InitDexh1(dexh1_http* var);                                               /* Initialization function. */
void Dexh1RequestParser(dexh1_http* req, char* buff, int headers_length);      /* Processing request header. */
void Dexh1ResponseParser(dexh1_http* req, char* buff, int headers_length);     /* Processing response header. */

#ifdef __cplusplus
}
#endif

#endif
