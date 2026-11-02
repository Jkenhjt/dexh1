#include "http.h"


int Dexh1IdxDelim(void* pointer, int delim)
{
  /* Fast search char without simd.
   * Using ctzll (count trailing zeros long long) function for count
   * is char in size_t variable and on what position.
   * Decreases count of loops, because scans sizeof(size_t) bytes per call
   */

  size_t mask_delim;
  size_t result;
  size_t data;
  memcpy(&data, pointer, sizeof(size_t));

  mask_delim = (0x0101010101010101) * delim;
  result = data ^ mask_delim;

  result = (result - 0x0101010101010101) & ~result & 0x8080808080808080;
  
  if(result == 0)
  {
    return -1;
  }
  
  return __builtin_ctzll(result) / sizeof(size_t);
}

int Dexh1LengthField(char* buff, int length, char delim, int* idx)
{
  int result = 0;
  int field_length = 0;
  
  while(*idx < length)
  {
    result = Dexh1IdxDelim(&buff[*idx], delim);
    if(result != -1)
    {
      *idx += result+1;
      field_length += result;
	    break;
    }
    
    *idx += sizeof(size_t);
    field_length += sizeof(size_t);
  }

  return field_length;
}

void Dexh1MethodRequest(dexh1_http* req, char* buff, int length)
{
  char* method;
  int method_length = 0;
  char* path;
  int path_length = 0;
  char* http_version;
  int http_version_length = 0;
  int idx = 0;
  dexh1_http_field method_;
  dexh1_http_field path_;
  dexh1_http_field http_version_;

  /* Finding method. */

  method = &buff[idx];
  method_length = Dexh1LengthField(buff, length, ' ', &idx);

  /* Findg path. */

  path = &buff[idx];
  path_length = Dexh1LengthField(buff, length, ' ', &idx);
  
  /* Finding http version. */

  http_version = &buff[idx];
  http_version_length = Dexh1LengthField(buff, length, '\r', &idx);
 
  /* Inserting all previous parsed data into hash table. */

  method_.name.name = "method";
  method_.name.name_length = 6;
  method_.value.value = method;
  method_.value.value_length = method_length;

  path_.name.name = "path";
  path_.name.name_length = 4;
  path_.value.value = path;
  path_.value.value_length = path_length;

  http_version_.name.name = "http_version";
  http_version_.name.name_length = 12;
  http_version_.value.value = http_version;
  http_version_.value.value_length = http_version_length;

  Dexh1InsertField(&(req->ht), method_);
  Dexh1InsertField(&(req->ht), path_);
  Dexh1InsertField(&(req->ht), http_version_);
}

void Dexh1MethodResponse(dexh1_http** req, char* buff, int length)
{
  char* http_version;
  int http_version_length = 0;
  char* status_code;
  int status_code_length = 0;
  char* status_message;
  int status_message_length = 0;
  int idx = 0;
  dexh1_http_field http_version_;
  dexh1_http_field status_code_;
  dexh1_http_field status_message_;

  /* Finding http version. */

  http_version = &buff[idx];
  http_version_length = Dexh1LengthField(buff, length, ' ', &idx);

  /* Finding status code. */

  status_code = &buff[idx];
  status_code_length = Dexh1LengthField(buff, length, ' ', &idx);

  /* Finding status message (if exist). */
  
  status_message = &buff[idx];
  status_message_length = Dexh1LengthField(buff, length, '\r', &idx);
  
  /* Inserting all previous parsed data into hash table. */
  
  http_version_.name.name = "http_version";
  http_version_.name.name_length = 12;
  http_version_.value.value = http_version;
  http_version_.value.value_length = http_version_length;

  status_code_.name.name = "status_code";
  status_code_.name.name_length = 11;
  status_code_.value.value = status_code;
  status_code_.value.value_length = status_code_length;

  status_message_.name.name = "status_message";
  status_message_.name.name_length = 14;
  status_message_.value.value = status_message;
  status_message_.value.value_length = status_message_length;

  Dexh1InsertField(&((*req)->ht), http_version_);
  Dexh1InsertField(&((*req)->ht), status_code_);
  Dexh1InsertField(&((*req)->ht), status_message_);
}

void Dexh1FindFields(int headers_length, dexh1_http* req, char* buff)
{
  dexh1_name name;
  dexh1_value value;
  dexh1_http_field field;
  
  int result = 0;
  int i = 0;
  while(i < headers_length)
  {
    result = Dexh1IdxDelim(&buff[i], '\r');
    if(result == -1)
    {
      i += sizeof(size_t);
      continue;
    }

    i += result + 2;

    if(buff[i] == '\r')
    {
      value.value = buff+i+2;
      value.value_length = headers_length - i;
      
      field.name.name = "message_body";
      field.name.name_length = 12;
      field.value = value;

      Dexh1InsertField(&req->ht, field);

      break;
    }

    name.name = buff+i;
    name.name_length = i;

    result = Dexh1LengthField(&buff[i], headers_length, ':', &i);

    name.name_length = i - name.name_length;
    
    i += 2;
 
    value.value = buff+i;
    value.value_length = i;

    result = Dexh1LengthField(&buff[i], headers_length, '\r', &i);

    value.value_length = i - value.value_length;

    field.name = name;
    field.value = value;

    Dexh1InsertField(&req->ht, field);
  }
}

void Dexh1RequestParser(dexh1_http* req, char* buff, int headers_length)
{
  Dexh1MethodRequest(req, buff, headers_length);
  
  Dexh1FindFields(headers_length, req, buff);
}

void Dexh1ResponseParser(dexh1_http* resp, char* buff, int headers_length)
{
  Dexh1MethodResponse(&resp, buff, headers_length);
  
  Dexh1FindFields(headers_length, resp, buff);
}

void InitDexh1(dexh1_http* var)
{
  DEXH1_INIT_HASH_TABLE(var->ht)
}
