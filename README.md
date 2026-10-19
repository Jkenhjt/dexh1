# libdexh1

**libdexh1** is an fast, zero-copy HTTP request and response parser library written in C. It focuses on minimal memory overhead and portability.

---

## Key Features

| Feature | Description |
| :--- | :--- |
| **Language** | C (C89 compliant) |
| **Supported Protocols** | HTTP/1.0, HTTP/1.1 |
| **Static Library Size** | ~7.7 KB |
| **Throughput** | ~2.3M requests/sec (14 fields/request) |
| **Max Headers Number** | 100 fields per struct |
| **Memory Strategy** | Zero-copy, zero dynamic allocation (no malloc), only stack |
| **Lookup Engine** | Hash Tables |

---

## Quickstart

### Building

```
make
```

### Installing

```
sudo make install
```

to change the directory for installation

```
PREFIX={path} make install
```

## Usage

---

### Example

```c
#include <string.h>
#include <stdio.h>
#include <errno.h>

#include <dexh1/http.h>


int main (int argc, char** argv) {
  char *request = "GET /any_path HTTP/1.1\r\nConnection: keep-alive\r\nHost: www.website.what\r\n\r\n";

  dexh1_http req;
  init_dexh1(&req);

  int result = 0;
  
  dexh1_request_parser(&req, request, strlen(request));
  
  dexh1_http_field path = dexh1_get_field(&req.ht, "path", 4);

  printf("Path: %.*s\n", path.value_length, path.value);
}

```
