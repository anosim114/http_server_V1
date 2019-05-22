#pragma once

/*
    Valid Headers
    
    "accept",
    "accept-charset",
    "accept-encoding",
    "accept-language",
    "access-control-request-method",
    "cache-control",
    "connection",
    "content-length",
    "content-type",
    "cookie",
    "date",
    "from",
    "host",
    "origin",
    "range",
    "referer",
    "user-agent",
    "upgrade"
*/

struct Range {
    int from;
    int to;
};

struct Cookie {
    char name[128];
    char content[1024];
};

struct Request_HTTP_Header {
    char url[1024];
    char method[1024];
    char raw_header[2056];
    char req_ip[16];
    char accept[32];
    char accept_charset[16];
    char accept_encoding[16];
    char accept_language[8];
    char access_control_reqest_method[16];
    char cache_control[16];
    char connection[32];
    int content_length;
    char content_type[32];
    struct Cookie cookies[8];
    char date[64];
    char from[128];
    char host[64];
    char origin[64];
    struct Range range;
    char referer[128];
    char user_agent[256];
    char upgrade[32];
};
