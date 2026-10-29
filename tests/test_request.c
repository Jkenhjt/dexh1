#include <stdio.h>
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
  init_dexh1(&req);

  dexh1_request_parser(&req, http, sizeof(http) - 1);

  method = dexh1_get_field(&req.ht, "method", 6);
  path = dexh1_get_field(&req.ht, "path", 4);
  http_version = dexh1_get_field(&req.ht, "http_version", 12);
  host = dexh1_get_field(&req.ht, "Host", 4);
  accept = dexh1_get_field(&req.ht, "Accept", 6);
  user_agent = dexh1_get_field(&req.ht, "User-Agent", 10);

  assert(strncmp(method.value, "GET", method.value_length) == 0);
  assert(strncmp(path.value, "/api/v1/users", path.value_length) == 0);
  assert(strncmp(http_version.value, "HTTP/1.1", http_version.value_length) == 0);
  assert(strncmp(host.value, "api.example.com", host.value_length) == 0);
  assert(strncmp(accept.value, "application/json", accept.value_length) == 0);
  assert(strncmp(user_agent.value, "ParserTestClient/1.0", user_agent.value_length) == 0);
  
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
  init_dexh1(&req);

  dexh1_request_parser(&req, http, sizeof(http) - 1);

  method = dexh1_get_field(&req.ht, "method", 6);
  path = dexh1_get_field(&req.ht, "path", 4);
  http_version = dexh1_get_field(&req.ht, "http_version", 12);
  host = dexh1_get_field(&req.ht, "Host", 4);
  content_type = dexh1_get_field(&req.ht, "Content-Type", 12);
  content_length = dexh1_get_field(&req.ht, "Content-Length", 14);
  authorization = dexh1_get_field(&req.ht, "Authorization", 13);
  message_body = dexh1_get_field(&req.ht, "message_body", 12);
  
  assert(strncmp(method.value, "POST", method.value_length) == 0);
  assert(strncmp(path.value, "/api/v1/users", path.value_length) == 0);
  assert(strncmp(http_version.value, "HTTP/1.1", http_version.value_length) == 0);
  assert(strncmp(host.value, "api.example.com", host.value_length) == 0);
  assert(strncmp(content_type.value, "application/json", content_type.value_length) == 0);
  assert(strncmp(content_length.value, "38", content_length.value_length) == 0);
  assert(strncmp(authorization.value, "Bearer eyJhbGciOi...", authorization.value_length) == 0);
  assert(strncmp(message_body.value, "{\"name\": \"Charlie\", \"role\": \"admin\"}", message_body.value_length) == 0);

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
  init_dexh1(&req);

  dexh1_request_parser(&req, http, sizeof(http) - 1);

  method = dexh1_get_field(&req.ht, "method", 6);
  path = dexh1_get_field(&req.ht, "path", 4);
  http_version = dexh1_get_field(&req.ht, "http_version", 12);
  host = dexh1_get_field(&req.ht, "Host", 4);
  content_type = dexh1_get_field(&req.ht, "Content-Type", 12);
  content_length = dexh1_get_field(&req.ht, "Content-Length", 14);
  message_body = dexh1_get_field(&req.ht, "message_body", 12);
  
  assert(strncmp(method.value, "PATCH", method.value_length) == 0);
  assert(strncmp(path.value, "/api/v1/users/3", path.value_length) == 0);
  assert(strncmp(http_version.value, "HTTP/1.1", http_version.value_length) == 0);
  assert(strncmp(host.value, "api.example.com", host.value_length) == 0);
  assert(strncmp(content_type.value, "application/json", content_type.value_length) == 0);
  assert(strncmp(content_length.value, "21", content_length.value_length) == 0);
  assert(strncmp(message_body.value, "{\"role\": \"moderator\"}", message_body.value_length) == 0);
  
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
  init_dexh1(&req);

  dexh1_request_parser(&req, http, sizeof(http) - 1);

  method = dexh1_get_field(&req.ht, "method", 6);
  path = dexh1_get_field(&req.ht, "path", 4);
  http_version = dexh1_get_field(&req.ht, "http_version", 12);
  host = dexh1_get_field(&req.ht, "Host", 4);
  authorization = dexh1_get_field(&req.ht, "Authorization", 13);

  assert(strncmp(method.value, "DELETE", method.value_length) == 0);
  assert(strncmp(path.value, "/api/v1/users/3", path.value_length) == 0);
  assert(strncmp(http_version.value, "HTTP/1.1", http_version.value_length) == 0);
  assert(strncmp(host.value, "api.example.com", host.value_length) == 0);
  assert(strncmp(authorization.value, "Bearer eyJhbGciOi...", authorization.value_length) == 0);
  
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
  init_dexh1(&req);

  dexh1_request_parser(&req, http, sizeof(http) - 1);

  method = dexh1_get_field(&req.ht, "method", 6);
  path = dexh1_get_field(&req.ht, "path", 4);
  http_version = dexh1_get_field(&req.ht, "http_version", 12);
  host = dexh1_get_field(&req.ht, "Host", 4);
  origin = dexh1_get_field(&req.ht, "Origin", 6);
  access_control_request_method = dexh1_get_field(&req.ht, "Authorization", 13);
  access_control_request_headers = dexh1_get_field(&req.ht, "Access-Control-Request-Headers", 12);
  
  assert(strncmp(method.value, "OPTIONS", method.value_length) == 0);
  assert(strncmp(path.value, "/api/v1/users", path.value_length) == 0);
  assert(strncmp(http_version.value, "HTTP/1.1", http_version.value_length) == 0);
  assert(strncmp(host.value, "api.example.com", host.value_length) == 0);
  assert(strncmp(origin.value, "https://app.example.com", origin.value_length) == 0);
  assert(strncmp(access_control_request_method.value, "POST", access_control_request_method.value_length) == 0);
  assert(strncmp(access_control_request_headers.value, "Content-Type, Authorization", access_control_request_headers.value_length) == 0);
  
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
  init_dexh1(&req);

  dexh1_request_parser(&req, http, sizeof(http) - 1);

  method = dexh1_get_field(&req.ht, "method", 6);
  path = dexh1_get_field(&req.ht, "path", 4);
  http_version = dexh1_get_field(&req.ht, "http_version", 12);
  host = dexh1_get_field(&req.ht, "Host", 4);

  assert(strncmp(method.value, "HEAD", method.value_length) == 0);
  assert(strncmp(path.value, "/downloads/large-file.zip", path.value_length) == 0);
  assert(strncmp(http_version.value, "HTTP/1.1", http_version.value_length) == 0);
  assert(strncmp(host.value, "files.example.com", host.value_length) == 0);

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
  init_dexh1(&req);

  dexh1_request_parser(&req, http, sizeof(http) - 1);

  method = dexh1_get_field(&req.ht, "method", 6);
  path = dexh1_get_field(&req.ht, "path", 4);
  http_version = dexh1_get_field(&req.ht, "http_version", 12);
  host = dexh1_get_field(&req.ht, "Host", 4);
  max_forwards = dexh1_get_field(&req.ht, "Max-Forwards", 12);

  assert(strncmp(method.value, "TRACE", method.value_length) == 0);
  assert(strncmp(path.value, "/api/v1/status", path.value_length) == 0);
  assert(strncmp(http_version.value, "HTTP/1.1", http_version.value_length) == 0);
  assert(strncmp(host.value, "api.example.com", host.value_length) == 0);
  assert(strncmp(max_forwards.value, "0", max_forwards.value_length) == 0);

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
  init_dexh1(&req);

  dexh1_request_parser(&req, http, sizeof(http) - 1);

  method = dexh1_get_field(&req.ht, "method", 6);
  path = dexh1_get_field(&req.ht, "path", 4);
  http_version = dexh1_get_field(&req.ht, "http_version", 12);
  host = dexh1_get_field(&req.ht, "Host", 4);
  proxy_authorization = dexh1_get_field(&req.ht, "Proxy-Authorization", 12);

  assert(strncmp(method.value, "CONNECT", method.value_length) == 0);
  assert(strncmp(path.value, "secure.example.com:443", path.value_length) == 0);
  assert(strncmp(http_version.value, "HTTP/1.1", http_version.value_length) == 0);
  assert(strncmp(host.value, "secure.example.com:443", host.value_length) == 0);
  assert(strncmp(proxy_authorization.value, "application/json", proxy_authorization.value_length) == 0);

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
  init_dexh1(&req);

  dexh1_request_parser(&req, http, sizeof(http) - 1);

  method = dexh1_get_field(&req.ht, "method", 6);
  path = dexh1_get_field(&req.ht, "path", 4);
  http_version = dexh1_get_field(&req.ht, "http_version", 12);
  host = dexh1_get_field(&req.ht, "Host", 4);
  content_type = dexh1_get_field(&req.ht, "Content-Type", 12);
  content_length = dexh1_get_field(&req.ht, "Content-Length", 14);
  message_body = dexh1_get_field(&req.ht, "message_body", 12);

  assert(strncmp(method.value, "PUT", method.value_length) == 0);
  assert(strncmp(path.value, "/api/v1/users/3", path.value_length) == 0);
  assert(strncmp(http_version.value, "HTTP/1.1", http_version.value_length) == 0);
  assert(strncmp(host.value, "api.example.com", host.value_length) == 0);
  assert(strncmp(content_type.value, "application/json", content_type.value_length) == 0);
  assert(strncmp(content_length.value, "43", content_length.value_length) == 0);
  assert(strncmp(message_body.value, "{\"name\": \"Charles\", \"role\": \"superadmin\"}", message_body.value_length) == 0);
  
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
