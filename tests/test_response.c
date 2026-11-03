#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <time.h>

#include <dexh1/http.h>
#include <dexh1/hash_table.h>

clock_t test_200()
{
  dexh1_http response;
  char* http_resp = "HTTP/1.1 200 OK\r\n"
                    "Content-Type: application/json; charset=utf-8\r\n"
                    "Content-Length: 27\r\nConnection: keep-alive\r\n\r\n"
                    "{\"status\": \"success\", \"id\": 42}";
  clock_t t1;
  clock_t t2;
  dexh1_http_field http_version;
  dexh1_http_field status_code;
  dexh1_http_field status_message;
  dexh1_http_field content_type;
  dexh1_http_field content_length;
  dexh1_http_field connection;
  dexh1_http_field message_body;

  t1 = clock();

  InitDexh1(&response);

  Dexh1ResponseParser(&response, http_resp, strlen(http_resp));

  http_version = Dexh1GetField(&response.ht, "http_version", 12);
  status_code = Dexh1GetField(&response.ht, "status_code", 11);
  status_message = Dexh1GetField(&response.ht, "status_message", 14);
  content_type = Dexh1GetField(&response.ht, "Content-Type", 12);
  content_length = Dexh1GetField(&response.ht, "Content-Length", 14);
  connection = Dexh1GetField(&response.ht, "Connection", 10);
  message_body = Dexh1GetField(&response.ht, "message_body", 12);

  assert(strncmp(http_version.value.value, "HTTP/1.1", http_version.value.value_length) == 0);
  assert(strncmp(status_code.value.value, "200", status_code.value.value_length) == 0);
  assert(strncmp(status_message.value.value, "OK", status_message.value.value_length) == 0);
  assert(strncmp(content_type.value.value, "application/json; charset=utf-8", content_type.value.value_length) == 0);
  assert(strncmp(content_length.value.value, "27", content_length.value.value_length) == 0);
  assert(strncmp(connection.value.value, "keep-alive", connection.value.value_length) == 0);
  assert(strncmp(message_body.value.value, "{\"status\": \"success\", \"id\": 42}", message_body.value.value_length) == 0);

  t2 = clock();

  return t2 - t1;
}

clock_t test_301()
{
  dexh1_http response;
  char* http_resp = "HTTP/1.1 301 Moved Permanently\r\n"
                    "Location: https://example.com/new-path\r\n"
                    "Content-Length: 0\r\n"
                    "Date: Tue, 03 Nov 2026 00:38:00 GMT\r\n\r\n";
  clock_t t1;
  clock_t t2;
  dexh1_http_field http_version;
  dexh1_http_field status_code;
  dexh1_http_field status_message;
  dexh1_http_field location;
  dexh1_http_field content_length;
  dexh1_http_field date;

  t1 = clock();

  InitDexh1(&response);

  Dexh1ResponseParser(&response, http_resp, strlen(http_resp));

  http_version = Dexh1GetField(&response.ht, "http_version", 12);
  status_code = Dexh1GetField(&response.ht, "status_code", 11);
  status_message = Dexh1GetField(&response.ht, "status_message", 14);
  location = Dexh1GetField(&response.ht, "Location", 8);
  content_length = Dexh1GetField(&response.ht, "Content-Length", 14);
  date = Dexh1GetField(&response.ht, "Date", 4);

  assert(strncmp(http_version.value.value, "HTTP/1.1", http_version.value.value_length) == 0);
  assert(strncmp(status_code.value.value, "301", status_code.value.value_length) == 0);
  assert(strncmp(status_message.value.value, "Moved Permanently", status_message.value.value_length) == 0);
  assert(strncmp(location.value.value, "https://example.com/new-path", location.value.value_length) == 0);
  assert(strncmp(content_length.value.value, "0", content_length.value.value_length) == 0);
  assert(strncmp(date.value.value, "Tue, 03 Nov 2026 00:38:00 GMT", date.value.value_length) == 0);

  t2 = clock();

  return t2 - t1;
}

clock_t test_400()
{
  dexh1_http response;
  char* http_resp = "HTTP/1.1 400 Bad Request\r\n"
                    "Content-Type: text/plain; charset=utf-8\r\n"
                    "Content-Length: 19\r\n"
                    "Connection: close\r\n\r\n"
                    "Invalid request body.";
  clock_t t1;
  clock_t t2;
  dexh1_http_field http_version;
  dexh1_http_field status_code;
  dexh1_http_field status_message;
  dexh1_http_field content_type;
  dexh1_http_field content_length;
  dexh1_http_field connection;
  dexh1_http_field message_body;

  t1 = clock();

  InitDexh1(&response);

  Dexh1ResponseParser(&response, http_resp, strlen(http_resp));

  http_version = Dexh1GetField(&response.ht, "http_version", 12);
  status_code = Dexh1GetField(&response.ht, "status_code", 11);
  status_message = Dexh1GetField(&response.ht, "status_message", 14);
  content_type = Dexh1GetField(&response.ht, "Content-Type", 12);
  content_length = Dexh1GetField(&response.ht, "Content-Length", 14);
  connection = Dexh1GetField(&response.ht, "Connection", 10);
  message_body = Dexh1GetField(&response.ht, "message_body", 12);

  assert(strncmp(http_version.value.value, "HTTP/1.1", http_version.value.value_length) == 0);
  assert(strncmp(status_code.value.value, "400", status_code.value.value_length) == 0);
  assert(strncmp(status_message.value.value, "Bad Request", status_message.value.value_length) == 0);
  assert(strncmp(content_type.value.value, "text/plain; charset=utf-8", content_type.value.value_length) == 0);
  assert(strncmp(content_length.value.value, "19", content_length.value.value_length) == 0);
  assert(strncmp(connection.value.value, "close", connection.value.value_length) == 0);
  assert(strncmp(message_body.value.value, "Invalid request body.", message_body.value.value_length) == 0);

  t2 = clock();

  return t2 - t1;
}

clock_t test_500()
{
  dexh1_http response;
  char* http_resp = "HTTP/1.1 500 Internal Server Error\r\n"
                    "Content-Type: application/json\r\n"
                    "Content-Length: 38\r\n"
                    "Connection: close\r\n\r\n"
                    "{\"error\": \"Database connection failed\"}";
  clock_t t1;
  clock_t t2;
  dexh1_http_field http_version;
  dexh1_http_field status_code;
  dexh1_http_field status_message;
  dexh1_http_field content_type;
  dexh1_http_field content_length;
  dexh1_http_field connection;
  dexh1_http_field message_body;

  t1 = clock();

  InitDexh1(&response);

  Dexh1ResponseParser(&response, http_resp, strlen(http_resp));

  http_version = Dexh1GetField(&response.ht, "http_version", 12);
  status_code = Dexh1GetField(&response.ht, "status_code", 11);
  status_message = Dexh1GetField(&response.ht, "status_message", 14);
  content_type = Dexh1GetField(&response.ht, "Content-Type", 12);
  content_length = Dexh1GetField(&response.ht, "Content-Length", 14);
  connection = Dexh1GetField(&response.ht, "Connection", 10);
  message_body = Dexh1GetField(&response.ht, "message_body", 12);

  assert(strncmp(http_version.value.value, "HTTP/1.1", http_version.value.value_length) == 0);
  assert(strncmp(status_code.value.value, "500", status_code.value.value_length) == 0);
  assert(strncmp(status_message.value.value, "Internal Server Error", status_message.value.value_length) == 0);
  assert(strncmp(content_type.value.value, "application/json", content_type.value.value_length) == 0);
  assert(strncmp(content_length.value.value, "38", content_length.value.value_length) == 0);
  assert(strncmp(connection.value.value, "close", connection.value.value_length) == 0);
  assert(strncmp(message_body.value.value, "{\"error\": \"Database connection failed\"}", message_body.value.value_length) == 0);

  t2 = clock();

  return t2 - t1;
}

clock_t test_200_with_cookies()
{
  dexh1_http response;
  char* http_resp = "HTTP/1.1 200 OK\r\n"
                    "Content-Type: text/html; charset=UTF-8\r\n"
                    "Content-Length: 12\r\n"
                    "Set-Cookie: session_id=abc123xyz; Path=/; HttpOnly; Secure\r\n"
                    "Date: Tue, 03 Nov 2026 00:38:00 GMT\r\n"
                    "\r\n\r\n"
                    "{\"status\": \"success\", \"id\": 42}";
  clock_t t1;
  clock_t t2;
  dexh1_http_field http_version;
  dexh1_http_field status_code;
  dexh1_http_field status_message;
  dexh1_http_field content_type;
  dexh1_http_field content_length;
  dexh1_http_field set_cookie;
  dexh1_http_field date;
  dexh1_http_field message_body;

  t1 = clock();

  InitDexh1(&response);

  Dexh1ResponseParser(&response, http_resp, strlen(http_resp));

  http_version = Dexh1GetField(&response.ht, "http_version", 12);
  status_code = Dexh1GetField(&response.ht, "status_code", 11);
  status_message = Dexh1GetField(&response.ht, "status_message", 14);
  content_type = Dexh1GetField(&response.ht, "Content-Type", 12);
  content_length = Dexh1GetField(&response.ht, "Content-Length", 14);
  set_cookie = Dexh1GetField(&response.ht, "Set-Cookie", 10);
  date = Dexh1GetField(&response.ht, "Date", 4);
  message_body = Dexh1GetField(&response.ht, "message_body", 12);

  assert(strncmp(http_version.value.value, "HTTP/1.1", http_version.value.value_length) == 0);
  assert(strncmp(status_code.value.value, "200", status_code.value.value_length) == 0);
  assert(strncmp(status_message.value.value, "OK", status_message.value.value_length) == 0);
  assert(strncmp(content_type.value.value, "text/html; charset=UTF-8", content_type.value.value_length) == 0);
  assert(strncmp(content_length.value.value, "12", content_length.value.value_length) == 0);
  assert(strncmp(set_cookie.value.value, "session_id=abc123xyz; Path=/; HttpOnly; Secure", set_cookie.value.value_length) == 0);
  assert(strncmp(date.value.value, "Tue, 03 Nov 2026 00:38:00 GMT", date.value.value_length) == 0);
  assert(strncmp(message_body.value.value, "{\"status\": \"success\", \"id\": 42}", message_body.value.value_length) == 0);

  t2 = clock();

  return t2 - t1;
}

int main(int argc, char** argv, char** envp)
{
  clock_t total = 0;

  total += test_200();
  total += test_301();
  total += test_400();
  total += test_500();
  total += test_200_with_cookies();

  printf("\n================================================================\n\n");

  printf("Result time: %f\n", (double) (total) / CLOCKS_PER_SEC);

  printf("\n================================================================\n\n");

  return 0;
}
