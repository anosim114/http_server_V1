#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "type-header.h"

/* RETURNS 1 if parsing was successful */
char parse_http_req_header(const char *raw_header, struct Request_HTTP_Header *header) {
    char buffer1[32];
    char buffer2[256];

    int mode = 0;
    int i = 0;

    for (int j = 0; j < strlen(raw_header); j++) {
        /*
        MODE
            0: keyword
                example: "host", "referrer", ...
            1: data to keyword
                everything after the ':' until "\r\n"
        */

        if (mode == 0) {
            char snipped[4];
            strncpy(snipped, raw_header + j, 4);
            if (strncmp(snipped, "\r\n", 4) == 0) {
                printf("done\n");
                break;
            }

            if (raw_header[j] == ':') {
                mode = 1;

                i = 0;

                if (raw_header[j + 1] == ' ') {
                    j += 2;
                } else {
                    j++;
                }
                
            } else {
                buffer1[i] = raw_header[j];
                i++;
            }
        }
        
        if (mode == 1) {
           if (raw_header[j] == '\n') {

                if (strncmp(buffer1, "accept", 6) == 0) {
                    if (strlen(buffer1) == 6) {
                        strcpy(header->accept, buffer2);
                    }
                }

                if (strncmp(buffer1, "accept-charset", 14) == 0) {
                    strcpy(header->accept_charset, buffer2);
                }

                if (strncmp(buffer1, "accept-encoding", 15) == 0) {
                    strcpy(header->accept_encoding, buffer2);
                }

                if (strncmp(buffer1, "accept-language", 15) == 0) {
                    strcpy(header->accept_language, buffer2);
                }

                if (strncmp(buffer1, "access-control-request-method", 29) == 0) {
                    strcpy(header->access_control_reqest_method, buffer2);
                }

                if (strncmp(buffer1, "cache-control", 13) == 0) {
                    strcpy(header->cache_control, buffer2);
                }

                if (strncmp(buffer1, "connection", 10) == 0) {
                    strcpy(header->connection, buffer2);
                }

                if (strncmp(buffer1, "content-length", 14) == 0) {
                    header->content_length = atoi(buffer2);
                }

                if (strncmp(buffer1, "content-type", 12) == 0) {
                    strcpy(header->content_type, buffer2);
                }

                if (strncmp(buffer1, "cookie", 6) == 0) {
                    // TODO
                }

                if (strncmp(buffer1, "date", 4) == 0) {
                    strcpy(header->date, buffer2);
                }

                if (strncmp(buffer1, "from", 4) == 0) {
                    strcpy(header->from, buffer2);
                }

                if (strncmp(buffer1, "host", 4) == 0) {
                    strcpy(header->host, buffer2);
                }

                if (strncmp(buffer1, "origin", 6) == 0) {
                    strcpy(header->origin, buffer2);
                }

                if (strncmp(buffer1, "range", 5) == 0) {
                    // TODO
                }

                if (strncmp(buffer1, "referer", 7) == 0) {
                    strcpy(header->referer, buffer2);
                }

                if (strncmp(buffer1, "user-agent", 10) == 0) {
                    strcpy(header->user_agent, buffer2);
                }

                if (strncmp(buffer1, "upgrade", 8) == 0) {
                    strcpy(header->user_agent, buffer2);
                }

                mode = 0;

                strncpy(buffer2, " ", 256);
                strncpy(buffer1, " ", 32);
                i = 0;

            } else {
                buffer2[i] = raw_header[j];
                i++;
            }
        }
    }
    return 1;
}
