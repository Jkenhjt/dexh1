#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#ifdef __cplusplus
extern "C" {
#endif


#include <stdlib.h>
#include <string.h>


#define DEXH1_HASH_TABLE_SIZE 128                                                                             /* Hash table size macros */
#define DEXH1_INIT_HASH_TABLE(x) memset(&x.http, \
                                        0, \
                                        DEXH1_HASH_TABLE_SIZE * sizeof(dexh1_http_field)); \
	                               x.size = DEXH1_HASH_TABLE_SIZE;                                              /* Initialization hash table macros. */

typedef struct
{
  char* name;          /* Name of field */
  int name_length;     /* Name length. */
} dexh1_name;

typedef struct
{
  char* value;         /* Value of filed */
  int value_length;    /* Value length. */
} dexh1_value;

typedef struct
{
  dexh1_name name;
  dexh1_value value;
} dexh1_http_field;    /* Http field struct. */

typedef struct
{
  dexh1_http_field http[DEXH1_HASH_TABLE_SIZE];    /* Array of http fields. */
  int size;                                           /* Size of hash table for runtime usage. */
} dexh1_hash_table_t;

dexh1_http_field Dexh1GetField(dexh1_hash_table_t* ht, char* name, int length);    /* Extracts field from hash table. */
void Dexh1InsertField(dexh1_hash_table_t* ht, dexh1_http_field value);             /* Inserts field into hash table. */
void Dexh1DeleteField(dexh1_hash_table_t* ht, char* name, int length);             /* Deletes field from hash table. By zeroing it. */

#ifdef __cplusplus
}
#endif

#endif
