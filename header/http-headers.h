#pragma once

#include "http-headers.c"

char parse_http_req_header(const char *raw_header, struct Request_HTTP_Header *header);
