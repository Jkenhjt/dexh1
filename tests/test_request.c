#include <stdio.h>
#include <string.h>
#include <time.h>
#include <assert.h>

#include <dexh1/http.h>

static dexh1_http_field method;
static dexh1_http_field path;
static dexh1_http_field http_version;
static dexh1_http_field host;
static dexh1_http_field accept;
static dexh1_http_field user_agent;
static dexh1_http_field content_type;
static dexh1_http_field content_length;
static dexh1_http_field authorization;
static dexh1_http_field message_body;
static dexh1_http_field origin;
static dexh1_http_field access_control_request_method;
static dexh1_http_field access_control_request_headers;
static dexh1_http_field max_forwards;
static dexh1_http_field proxy_authorization;


clock_t test_get_request()
{
  dexh1_http req;
  char http[] = "GET /api/v1/users HTTP/1.1\r\nHost: api.example.com\r\nAccept: application/json\r\nUser-Agent: ParserTestClient/1.0\r\n\r\n";
  
  clock_t t1;
  clock_t t2;

  t1 = clock();
  InitDexh1(&req);

  Dexh1RequestParser(&req, http, sizeof(http) - 1);

  method = Dexh1GetField(&req.ht, "method", 6);
  path = Dexh1GetField(&req.ht, "path", 4);
  http_version = Dexh1GetField(&req.ht, "http_version", 12);
  host = Dexh1GetField(&req.ht, "Host", 4);
  accept = Dexh1GetField(&req.ht, "Accept", 6);
  user_agent = Dexh1GetField(&req.ht, "User-Agent", 10);

  assert(strncmp(method.value.value, "GET", method.value.value_length) == 0);
  assert(strncmp(path.value.value, "/api/v1/users", path.value.value_length) == 0);
  assert(strncmp(http_version.value.value, "HTTP/1.1", http_version.value.value_length) == 0);
  assert(strncmp(host.value.value, "api.example.com", host.value.value_length) == 0);
  assert(strncmp(accept.value.value, "application/json", accept.value.value_length) == 0);
  assert(strncmp(user_agent.value.value, "ParserTestClient/1.0", user_agent.value.value_length) == 0);
  
  t2 = clock();

  return t2 - t1;
}

clock_t test_post_request()
{
  dexh1_http req;
  char http[] = "POST /api/v1/users HTTP/1.1\r\nHost: api.example.com\r\nContent-Type: application/json\r\nContent-Length: 38\r\nAuthorization: Bearer eyJhbGciOi...\r\n\r\n{\"name\": \"Charlie\", \"role\": \"admin\"}";
  
  clock_t t1;
  clock_t t2;

  t1 = clock();
  InitDexh1(&req);

  Dexh1RequestParser(&req, http, sizeof(http) - 1);

  method = Dexh1GetField(&req.ht, "method", 6);
  path = Dexh1GetField(&req.ht, "path", 4);
  http_version = Dexh1GetField(&req.ht, "http_version", 12);
  host = Dexh1GetField(&req.ht, "Host", 4);
  content_type = Dexh1GetField(&req.ht, "Content-Type", 12);
  content_length = Dexh1GetField(&req.ht, "Content-Length", 14);
  authorization = Dexh1GetField(&req.ht, "Authorization", 13);
  message_body = Dexh1GetField(&req.ht, "message_body", 12);
  
  assert(strncmp(method.value.value, "POST", method.value.value_length) == 0);
  assert(strncmp(path.value.value, "/api/v1/users", path.value.value_length) == 0);
  assert(strncmp(http_version.value.value, "HTTP/1.1", http_version.value.value_length) == 0);
  assert(strncmp(host.value.value, "api.example.com", host.value.value_length) == 0);
  assert(strncmp(content_type.value.value, "application/json", content_type.value.value_length) == 0);
  assert(strncmp(content_length.value.value, "38", content_length.value.value_length) == 0);
  assert(strncmp(authorization.value.value, "Bearer eyJhbGciOi...", authorization.value.value_length) == 0);
  assert(strncmp(message_body.value.value, "{\"name\": \"Charlie\", \"role\": \"admin\"}", message_body.value.value_length) == 0);

  t2 = clock();

  return t2 - t1;
}

clock_t test_patch_request()
{
  dexh1_http req;
  char http[] = "PATCH /api/v1/users/3 HTTP/1.1\r\nHost: api.example.com\r\nContent-Type: application/json\r\nContent-Length: 21\r\n\r\n{\"role\": \"moderator\"}";
  
  clock_t t1;
  clock_t t2;

  t1 = clock();
  InitDexh1(&req);

  Dexh1RequestParser(&req, http, sizeof(http) - 1);

  method = Dexh1GetField(&req.ht, "method", 6);
  path = Dexh1GetField(&req.ht, "path", 4);
  http_version = Dexh1GetField(&req.ht, "http_version", 12);
  host = Dexh1GetField(&req.ht, "Host", 4);
  content_type = Dexh1GetField(&req.ht, "Content-Type", 12);
  content_length = Dexh1GetField(&req.ht, "Content-Length", 14);
  message_body = Dexh1GetField(&req.ht, "message_body", 12);
  
  assert(strncmp(method.value.value, "PATCH", method.value.value_length) == 0);
  assert(strncmp(path.value.value, "/api/v1/users/3", path.value.value_length) == 0);
  assert(strncmp(http_version.value.value, "HTTP/1.1", http_version.value.value_length) == 0);
  assert(strncmp(host.value.value, "api.example.com", host.value.value_length) == 0);
  assert(strncmp(content_type.value.value, "application/json", content_type.value.value_length) == 0);
  assert(strncmp(content_length.value.value, "21", content_length.value.value_length) == 0);
  assert(strncmp(message_body.value.value, "{\"role\": \"moderator\"}", message_body.value.value_length) == 0);
  
  t2 = clock();

  return t2 - t1;
}

clock_t test_delete_request()
{
  dexh1_http req;
  char http[] = "DELETE /api/v1/users/3 HTTP/1.1\r\nHost: api.example.com\r\nAuthorization: Bearer eyJhbGciOi...\r\n\r\n";
  
  clock_t t1;
  clock_t t2;

  t1 = clock();
  InitDexh1(&req);

  Dexh1RequestParser(&req, http, sizeof(http) - 1);

  method = Dexh1GetField(&req.ht, "method", 6);
  path = Dexh1GetField(&req.ht, "path", 4);
  http_version = Dexh1GetField(&req.ht, "http_version", 12);
  host = Dexh1GetField(&req.ht, "Host", 4);
  authorization = Dexh1GetField(&req.ht, "Authorization", 13);

  assert(strncmp(method.value.value, "DELETE", method.value.value_length) == 0);
  assert(strncmp(path.value.value, "/api/v1/users/3", path.value.value_length) == 0);
  assert(strncmp(http_version.value.value, "HTTP/1.1", http_version.value.value_length) == 0);
  assert(strncmp(host.value.value, "api.example.com", host.value.value_length) == 0);
  assert(strncmp(authorization.value.value, "Bearer eyJhbGciOi...", authorization.value.value_length) == 0);
  
  t2 = clock();

  return t2 - t1;
}


clock_t test_options_request()
{
  dexh1_http req;
  char http[] = "OPTIONS /api/v1/users HTTP/1.1\r\nHost: api.example.com\r\nOrigin: https://app.example.com\r\nAccess-Control-Request-Method: POST\r\nAccess-Control-Request-Headers: Content-Type, Authorization\r\n\r\n";
  
  clock_t t1;
  clock_t t2;

  t1 = clock();
  InitDexh1(&req);

  Dexh1RequestParser(&req, http, sizeof(http) - 1);

  method = Dexh1GetField(&req.ht, "method", 6);
  path = Dexh1GetField(&req.ht, "path", 4);
  http_version = Dexh1GetField(&req.ht, "http_version", 12);
  host = Dexh1GetField(&req.ht, "Host", 4);
  origin = Dexh1GetField(&req.ht, "Origin", 6);
  access_control_request_method = Dexh1GetField(&req.ht, "Authorization", 13);
  access_control_request_headers = Dexh1GetField(&req.ht, "Access-Control-Request-Headers", 12);
  
  assert(strncmp(method.value.value, "OPTIONS", method.value.value_length) == 0);
  assert(strncmp(path.value.value, "/api/v1/users", path.value.value_length) == 0);
  assert(strncmp(http_version.value.value, "HTTP/1.1", http_version.value.value_length) == 0);
  assert(strncmp(host.value.value, "api.example.com", host.value.value_length) == 0);
  assert(strncmp(origin.value.value, "https://app.example.com", origin.value.value_length) == 0);
  assert(strncmp(access_control_request_method.value.value, "POST", access_control_request_method.value.value_length) == 0);
  assert(strncmp(access_control_request_headers.value.value, "Content-Type, Authorization", access_control_request_headers.value.value_length) == 0);
  
  t2 = clock();

  return t2 - t1;
}


clock_t test_head_request()
{
  dexh1_http req;
  char http[] = "HEAD /downloads/large-file.zip HTTP/1.1\r\nHost: files.example.com\r\n\r\n";
  
  clock_t t1;
  clock_t t2;

  t1 = clock();
  InitDexh1(&req);

  Dexh1RequestParser(&req, http, sizeof(http) - 1);

  method = Dexh1GetField(&req.ht, "method", 6);
  path = Dexh1GetField(&req.ht, "path", 4);
  http_version = Dexh1GetField(&req.ht, "http_version", 12);
  host = Dexh1GetField(&req.ht, "Host", 4);

  assert(strncmp(method.value.value, "HEAD", method.value.value_length) == 0);
  assert(strncmp(path.value.value, "/downloads/large-file.zip", path.value.value_length) == 0);
  assert(strncmp(http_version.value.value, "HTTP/1.1", http_version.value.value_length) == 0);
  assert(strncmp(host.value.value, "files.example.com", host.value.value_length) == 0);

  t2 = clock();

  return t2 - t1;
}


clock_t test_trace_request()
{
  dexh1_http req;
  char http[] = "TRACE /api/v1/status HTTP/1.1\r\nHost: api.example.com\r\nMax-Forwards: 0\r\n\r\n";
  
  clock_t t1;
  clock_t t2;

  t1 = clock();
  InitDexh1(&req);

  Dexh1RequestParser(&req, http, sizeof(http) - 1);

  method = Dexh1GetField(&req.ht, "method", 6);
  path = Dexh1GetField(&req.ht, "path", 4);
  http_version = Dexh1GetField(&req.ht, "http_version", 12);
  host = Dexh1GetField(&req.ht, "Host", 4);
  max_forwards = Dexh1GetField(&req.ht, "Max-Forwards", 12);

  assert(strncmp(method.value.value, "TRACE", method.value.value_length) == 0);
  assert(strncmp(path.value.value, "/api/v1/status", path.value.value_length) == 0);
  assert(strncmp(http_version.value.value, "HTTP/1.1", http_version.value.value_length) == 0);
  assert(strncmp(host.value.value, "api.example.com", host.value.value_length) == 0);
  assert(strncmp(max_forwards.value.value, "0", max_forwards.value.value_length) == 0);

  t2 = clock();

  return t2 - t1;
}

clock_t test_connect_request()
{
  dexh1_http req;
  char http[] = "CONNECT secure.example.com:443 HTTP/1.1\r\nHost: secure.example.com:443\r\nProxy-Authorization: Basic dXNlcjpwYXNz\r\n\r\n";
  
  clock_t t1;
  clock_t t2;

  t1 = clock();
  InitDexh1(&req);

  Dexh1RequestParser(&req, http, sizeof(http) - 1);

  method = Dexh1GetField(&req.ht, "method", 6);
  path = Dexh1GetField(&req.ht, "path", 4);
  http_version = Dexh1GetField(&req.ht, "http_version", 12);
  host = Dexh1GetField(&req.ht, "Host", 4);
  proxy_authorization = Dexh1GetField(&req.ht, "Proxy-Authorization", 12);

  assert(strncmp(method.value.value, "CONNECT", method.value.value_length) == 0);
  assert(strncmp(path.value.value, "secure.example.com:443", path.value.value_length) == 0);
  assert(strncmp(http_version.value.value, "HTTP/1.1", http_version.value.value_length) == 0);
  assert(strncmp(host.value.value, "secure.example.com:443", host.value.value_length) == 0);
  assert(strncmp(proxy_authorization.value.value, "application/json", proxy_authorization.value.value_length) == 0);

  t2 = clock();

  return t2 - t1;
}


clock_t test_put_request()
{
  dexh1_http req;
  char http[] = "PUT /api/v1/users/3 HTTP/1.1\r\nHost: api.example.com\r\nContent-Type: application/json\r\nContent-Length: 43\r\n\r\n{\"name\": \"Charles\", \"role\": \"superadmin\"}";
  
  clock_t t1;
  clock_t t2;

  t1 = clock();
  InitDexh1(&req);

  Dexh1RequestParser(&req, http, sizeof(http) - 1);

  method = Dexh1GetField(&req.ht, "method", 6);
  path = Dexh1GetField(&req.ht, "path", 4);
  http_version = Dexh1GetField(&req.ht, "http_version", 12);
  host = Dexh1GetField(&req.ht, "Host", 4);
  content_type = Dexh1GetField(&req.ht, "Content-Type", 12);
  content_length = Dexh1GetField(&req.ht, "Content-Length", 14);
  message_body = Dexh1GetField(&req.ht, "message_body", 12);

  assert(strncmp(method.value.value, "PUT", method.value.value_length) == 0);
  assert(strncmp(path.value.value, "/api/v1/users/3", path.value.value_length) == 0);
  assert(strncmp(http_version.value.value, "HTTP/1.1", http_version.value.value_length) == 0);
  assert(strncmp(host.value.value, "api.example.com", host.value.value_length) == 0);
  assert(strncmp(content_type.value.value, "application/json", content_type.value.value_length) == 0);
  assert(strncmp(content_length.value.value, "43", content_length.value.value_length) == 0);
  assert(strncmp(message_body.value.value, "{\"name\": \"Charles\", \"role\": \"superadmin\"}", message_body.value.value_length) == 0);
  
  t2 = clock();

  return t2 - t1;
}


int main(int argc, char** argv)
{
  clock_t total = 0;

  total += test_get_request();
  total += test_post_request();
  total += test_put_request();
  total += test_patch_request();
  total += test_delete_request();
  total += test_options_request();
  total += test_head_request();
  total += test_trace_request();
  total += test_connect_request();
  
  printf("\n================================================================\n\n");
  
  printf("Result time: %f\n", (double) (total) / CLOCKS_PER_SEC);
  
  printf("\n================================================================\n\n");

  return 0;
}
