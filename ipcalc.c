#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <stdint.h>

#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte) \
  ((byte) & 0x80 ? '1' : '0'), \
  ((byte) & 0x40 ? '1' : '0'), \
  ((byte) & 0x20 ? '1' : '0'), \
  ((byte) & 0x10 ? '1' : '0'), \
  ((byte) & 0x08 ? '1' : '0'), \
  ((byte) & 0x04 ? '1' : '0'), \
  ((byte) & 0x02 ? '1' : '0'), \
  ((byte) & 0x01 ? '1' : '0') 

bool debug = false, vverbose = false;
char dBuff[1000];

void verbose(const char *msg, const char *file, const int line, const char *func, const bool enabled);
void parseIP(const char *ipString);

int main(const int argc, const char *argv[]) {
    
    if (argc > 1) {
        for (int i = 1; i < argc; i++) {
            if ((strncmp(argv[i], "-d", sizeof("-d")) == 0) || (strncmp(argv[i], "--debug", sizeof("--debug")) == 0)) {
                debug = true;
            }
            if ((strncmp(argv[i], "-v", sizeof("-v")) == 0) || (strncmp(argv[i], "--verbose", sizeof("--verbose")) == 0)) {
                vverbose = true;
            }
        }

        for (int i = 1; i < argc; i++) {
            const char *arg = argv[i];
            if ((strncmp(arg, "-h", sizeof("-h")) == 0) || (strncmp(arg, "--help", sizeof("--help")) == 0)) {
                printf("\nCalculate CIDR IP Address\n\n%s <A.B.C.D/XY>\n\n", argv[0]);
                printf("[-h || --help]     Print this help message\n");
                printf("[-d || --debug]    Dispaly debug output\n");
                printf("[-v || --verbose]  List IP address of each host\n");
                printf("<A.B.C.D/XY>       CIDR IP address\n");

                return 0;
            }

            int periodCnt = 0, slashCnt = 0;
            for (size_t j = 0; j < strlen(arg); j++) {

                if ((arg[j] > 45) && (arg[j] < 58)) {
                    if (arg[j] == '.') {
                        periodCnt++;
                    }
                    if (arg[j] == '/') {
                        slashCnt++;
                    }
                    if ((j == strlen(arg) - 1) && (periodCnt == 3) && (slashCnt == 1)) {
                        printf("\n");
                       parseIP(arg);
                    }
                } else {
                    break;
                }
            }
        }
    }
}

void parseIP(const char *ipString) {
    snprintf(dBuff, sizeof(dBuff), "Parsing IP string: %s", ipString);
    verbose(dBuff, __FILE__, __LINE__, __FUNCTION__, debug);
    
    uint32_t tmpIP = 0;
    uint32_t snm = 0;
    uint32_t startIP = 0;
    uint32_t stopIP = 0;
    int octet1 = 0, octet2 = 0, octet3 = 0, octet4 = 0, netbit = 0, cnt = 0, pos1 = 0, pos2 = 0, pos3 = 0, pos4 = 0;

    for (size_t i = 0; i < strlen(ipString); i++) {
        if (ipString[i] == '.') {
            cnt++;

            switch(cnt) {
                case 1:
                    pos1 = (int)i;
                    break;
                case 2:
                    pos2 = (int)i;
                    break;
                case 3:
                    pos3 = (int)i;
                    break;
            }
        }
        if (ipString[i] == '/') {
            pos4 = (int)i;
        }
    }

    snprintf(dBuff, sizeof(dBuff), "Octet 1 end position: %d", pos1);
    verbose(dBuff, __FILE__, __LINE__, __FUNCTION__, debug);

    snprintf(dBuff, sizeof(dBuff), "Octet 2 end position: %d", pos2);
    verbose(dBuff, __FILE__, __LINE__, __FUNCTION__, debug);

    snprintf(dBuff, sizeof(dBuff), "Octet 3 end position: %d", pos3);
    verbose(dBuff, __FILE__, __LINE__, __FUNCTION__, debug);
    
    snprintf(dBuff, sizeof(dBuff), "Octet 4 end position: %d", pos4);
    verbose(dBuff, __FILE__, __LINE__, __FUNCTION__, debug);
    
    char tmpBuf[4] = {'\0'};
    strncpy(tmpBuf, ipString, pos1);
    octet1 = atoi(tmpBuf);
    snprintf(dBuff, sizeof(dBuff), "Octet 1: %d", octet1);
    verbose(dBuff, __FILE__, __LINE__, __FUNCTION__, debug);

    for (size_t i = 0; i < strlen(tmpBuf); i++) {
        tmpBuf[i] = '\0';
    }
    strncpy(tmpBuf, ipString + pos1 + 1, pos2 - pos1);
    octet2 = atoi(tmpBuf);
    snprintf(dBuff, sizeof(dBuff), "Octet 2: %d", octet2);
    verbose(dBuff, __FILE__, __LINE__, __FUNCTION__, debug);

    for (size_t i = 0; i < strlen(tmpBuf); i++) {
        tmpBuf[i] = '\0';
    }
    strncpy(tmpBuf, ipString + pos2 + 1, pos3 - pos2);
    octet3 = atoi(tmpBuf);
    snprintf(dBuff, sizeof(dBuff), "Octet 3: %d", octet3);
    verbose(dBuff, __FILE__, __LINE__, __FUNCTION__, debug);

    for (size_t i = 0; i < strlen(tmpBuf); i++) {
        tmpBuf[i] = '\0';
    }
    strncpy(tmpBuf, ipString + pos3 + 1, pos4 - pos3);
    octet4 = atoi(tmpBuf);    
    snprintf(dBuff, sizeof(dBuff), "Octet 4: %d", octet4);
    verbose(dBuff, __FILE__, __LINE__, __FUNCTION__, debug);
    
    for (size_t i = 0; i < strlen(tmpBuf); i++) {
        tmpBuf[i] = '\0';
    }
    strncpy(tmpBuf, ipString + pos4 + 1, strlen(ipString) - pos4);
    netbit = atoi(tmpBuf);
    snprintf(dBuff, sizeof(dBuff), "Network Bit: %d", netbit);
    verbose(dBuff, __FILE__, __LINE__, __FUNCTION__, debug);

    if ((octet1 < 0) || (octet1 > 255)) {
        snprintf(dBuff, sizeof(dBuff), "Octet 1 is out of range [%d]", octet1);
        verbose(dBuff, __FILE__, __LINE__, __FUNCTION__, true);
        exit(1);
    }
    if ((octet2 < 0) || (octet2 > 255)) {
        snprintf(dBuff, sizeof(dBuff), "Octet 2 is out of range [%d]", octet2);
        verbose(dBuff, __FILE__, __LINE__, __FUNCTION__, true);
        exit(1);
    }
    if ((octet3 < 0) || (octet3 > 255)) {
        snprintf(dBuff, sizeof(dBuff), "Octet 3 is out of range [%d]", octet3);
        verbose(dBuff, __FILE__, __LINE__, __FUNCTION__, true);
        exit(1);
    }
    if ((octet4 < 0) || (octet4 > 255)) {
        snprintf(dBuff, sizeof(dBuff), "Octet 4 is out of range [%d]", octet4);
        verbose(dBuff, __FILE__, __LINE__, __FUNCTION__, true);
        exit(1);
    }
    if ((netbit < 0) || (netbit > 32)) {
        snprintf(dBuff, sizeof(dBuff), "Network mask is out of range [%d]", netbit);
        verbose(dBuff, __FILE__, __LINE__, __FUNCTION__, true);
        exit(1);
    }

    tmpIP += (uint32_t)octet1 << 24;
    tmpIP += (uint32_t)octet2 << 16;
    tmpIP += (uint32_t)octet3 << 8;
    tmpIP += (uint32_t)octet4;

    snprintf(dBuff, sizeof(dBuff), "Given IP: %d.%d.%d.%d", (unsigned char)(tmpIP>>24), (unsigned char)(tmpIP>>16), (unsigned char)(tmpIP>>8), (unsigned char)(tmpIP));
    verbose(dBuff, __FILE__, __LINE__, __FUNCTION__, debug);

    for (int i = 0; i <= netbit; i++) {
        snm <<= 1;
        snm++;
    }
    for (int i = netbit; i < 32; i++) {
        snm <<= 1;
    }

    snprintf(dBuff, sizeof(dBuff), "Subnet mask: %d.%d.%d.%d", (unsigned char)(snm>>24), (unsigned char)(snm>>16), (unsigned char)(snm>>8), (unsigned char)(snm));
    verbose(dBuff, __FILE__, __LINE__, __FUNCTION__, debug);

    startIP = tmpIP & snm;

    snprintf(dBuff, sizeof(dBuff), "Network ID: %d.%d.%d.%d", (unsigned char)(startIP>>24), (unsigned char)(startIP>>16), (unsigned char)(startIP>>8), (unsigned char)(startIP));
    verbose(dBuff, __FILE__, __LINE__, __FUNCTION__, debug);

    stopIP = tmpIP | ~snm;

    snprintf(dBuff, sizeof(dBuff), "Broadcast: %d.%d.%d.%d", (unsigned char)(stopIP>>24), (unsigned char)(stopIP>>16), (unsigned char)(stopIP>>8), (unsigned char)(stopIP));
    verbose(dBuff, __FILE__, __LINE__, __FUNCTION__, debug);

    char class = '\0';

    if ((startIP >> 31) == 0x0) {
        class = 'A';
    }
    if ((startIP >> 30) == 0x10) {
        class = 'B';
    }
    if ((startIP >> 29) == 0x110) {
        class = 'C';
    }
    if ((startIP >> 28) == 0x1110) {
        class = 'D';
    }
    if ((startIP >> 28) == 0x1111) {
        class = 'E';
    }

    if (vverbose) {
        char tmpBuf[31] = {'\0'};

        snprintf(tmpBuf, sizeof(tmpBuf), "Address:   %d.%d.%d.%d", (unsigned char)(tmpIP>>24), (unsigned char)(tmpIP>>16), (unsigned char)(tmpIP>>8), (unsigned char)(tmpIP));
        printf("%-31s"BYTE_TO_BINARY_PATTERN"."BYTE_TO_BINARY_PATTERN"."BYTE_TO_BINARY_PATTERN"."BYTE_TO_BINARY_PATTERN"\n", tmpBuf, BYTE_TO_BINARY((unsigned char)(tmpIP>>24)), 
        BYTE_TO_BINARY((unsigned char)(tmpIP>>16)), BYTE_TO_BINARY((unsigned char)(tmpIP>>8)), BYTE_TO_BINARY((unsigned char)(tmpIP)));

        for (size_t i = 0; i < strlen(tmpBuf); i++) {
            tmpBuf[i] = '\0';
        }
        snprintf(tmpBuf, sizeof(tmpBuf), "Netmask:   %d.%d.%d.%d", (unsigned char)(snm>>24), (unsigned char)(snm>>16), (unsigned char)(snm>>8), (unsigned char)(snm));
        printf("%-31s"BYTE_TO_BINARY_PATTERN"."BYTE_TO_BINARY_PATTERN"."BYTE_TO_BINARY_PATTERN"."BYTE_TO_BINARY_PATTERN"\n",tmpBuf, BYTE_TO_BINARY((unsigned char)(snm>>24)), 
        BYTE_TO_BINARY((unsigned char)(snm>>16)), BYTE_TO_BINARY((unsigned char)(snm>>8)), BYTE_TO_BINARY((unsigned char)(snm)));

        for (size_t i = 0; i < strlen(tmpBuf); i++) {
            tmpBuf[i] = '\0';
        }
        snprintf(tmpBuf, sizeof(tmpBuf), "Wildcard:  %d.%d.%d.%d", (unsigned char)((~snm)>>24), (unsigned char)((~snm)>>16), (unsigned char)((~snm)>>8), (unsigned char)((~snm)));
        printf("%-31s"BYTE_TO_BINARY_PATTERN"."BYTE_TO_BINARY_PATTERN"."BYTE_TO_BINARY_PATTERN"."BYTE_TO_BINARY_PATTERN"\n", tmpBuf, BYTE_TO_BINARY((unsigned char)((~snm)>>24)), 
        BYTE_TO_BINARY((unsigned char)((~snm)>>16)), BYTE_TO_BINARY((unsigned char)((~snm)>>8)), BYTE_TO_BINARY((unsigned char)((~snm))));

        for (size_t i = 0; i < strlen(tmpBuf); i++) {
            tmpBuf[i] = '\0';
        }
        snprintf(tmpBuf, sizeof(tmpBuf), "Network:   %d.%d.%d.%d/%d", (unsigned char)(startIP>>24), (unsigned char)(startIP>>16), (unsigned char)(startIP>>8), (unsigned char)(startIP), netbit);
        printf("%-31s"BYTE_TO_BINARY_PATTERN"."BYTE_TO_BINARY_PATTERN"."BYTE_TO_BINARY_PATTERN"."BYTE_TO_BINARY_PATTERN"\n", tmpBuf, BYTE_TO_BINARY((unsigned char)(startIP>>24)), 
        BYTE_TO_BINARY((unsigned char)(startIP>>16)), BYTE_TO_BINARY((unsigned char)(startIP>>8)), BYTE_TO_BINARY((unsigned char)(startIP)));

        for (size_t i = 0; i < strlen(tmpBuf); i++) {
            tmpBuf[i] = '\0';
        }
        snprintf(tmpBuf, sizeof(tmpBuf), "Broadcast: %d.%d.%d.%d", (unsigned char)(stopIP>>24), (unsigned char)(stopIP>>16), (unsigned char)(stopIP>>8), (unsigned char)(stopIP));
        printf("%-31s"BYTE_TO_BINARY_PATTERN"."BYTE_TO_BINARY_PATTERN"."BYTE_TO_BINARY_PATTERN"."BYTE_TO_BINARY_PATTERN"\n", tmpBuf, BYTE_TO_BINARY((unsigned char)(stopIP>>24)), 
        BYTE_TO_BINARY((unsigned char)(stopIP>>16)), BYTE_TO_BINARY((unsigned char)(stopIP>>8)), BYTE_TO_BINARY((unsigned char)(stopIP)));

        for (size_t i = 0; i < strlen(tmpBuf); i++) {
            tmpBuf[i] = '\0';
        }
        snprintf(tmpBuf, sizeof(tmpBuf), "Host Min:  %d.%d.%d.%d", (unsigned char)((startIP + 1)>>24), (unsigned char)((startIP + 1)>>16), (unsigned char)((startIP + 1)>>8), (unsigned char)((startIP + 1)));
        printf("%-31s"BYTE_TO_BINARY_PATTERN"."BYTE_TO_BINARY_PATTERN"."BYTE_TO_BINARY_PATTERN"."BYTE_TO_BINARY_PATTERN"\n", tmpBuf, BYTE_TO_BINARY((unsigned char)((startIP + 1)>>24)), 
        BYTE_TO_BINARY((unsigned char)((startIP + 1)>>16)), BYTE_TO_BINARY((unsigned char)((startIP + 1)>>8)), BYTE_TO_BINARY((unsigned char)((startIP + 1))));

        for (size_t i = 0; i < strlen(tmpBuf); i++) {
            tmpBuf[i] = '\0';
        }
        snprintf(tmpBuf, sizeof(tmpBuf), "Host Max:  %d.%d.%d.%d", (unsigned char)((stopIP - 1)>>24), (unsigned char)((stopIP - 1)>>16), (unsigned char)((stopIP - 1)>>8), (unsigned char)((stopIP - 1)));
        printf("%-31s"BYTE_TO_BINARY_PATTERN"."BYTE_TO_BINARY_PATTERN"."BYTE_TO_BINARY_PATTERN"."BYTE_TO_BINARY_PATTERN"\n", tmpBuf, BYTE_TO_BINARY((unsigned char)((stopIP - 1)>>24)), 
        BYTE_TO_BINARY((unsigned char)((stopIP - 1)>>16)), BYTE_TO_BINARY((unsigned char)((stopIP - 1)>>8)), BYTE_TO_BINARY((unsigned char)((stopIP - 1))));

        printf("Hosts/Net: %d\n", stopIP - startIP - 1);
        printf("Class:     %c\n", class);
    } else {
        printf("Address:   %d.%d.%d.%d\n",    (unsigned char)(tmpIP>>24),         (unsigned char)(tmpIP>>16),         (unsigned char)(tmpIP>>8),         (unsigned char)(tmpIP));
        printf("Netmask:   %d.%d.%d.%d\n",    (unsigned char)(snm>>24),           (unsigned char)(snm>>16),           (unsigned char)(snm>>8),           (unsigned char)(snm));
        printf("Wildcard:  %d.%d.%d.%d\n",    (unsigned char)((~snm)>>24),        (unsigned char)((~snm)>>16),        (unsigned char)((~snm)>>8),        (unsigned char)((~snm)));
        printf("Network:   %d.%d.%d.%d/%d\n", (unsigned char)(startIP>>24),       (unsigned char)(startIP>>16),       (unsigned char)(startIP>>8),       (unsigned char)(startIP), netbit);
        printf("Broadcast: %d.%d.%d.%d\n",    (unsigned char)(stopIP>>24),        (unsigned char)(stopIP>>16),        (unsigned char)(stopIP>>8),        (unsigned char)(stopIP));
        printf("Host Min:  %d.%d.%d.%d\n",    (unsigned char)((startIP + 1)>>24), (unsigned char)((startIP + 1)>>16), (unsigned char)((startIP + 1)>>8), (unsigned char)((startIP + 1)));
        printf("Host Max:  %d.%d.%d.%d\n",    (unsigned char)((stopIP - 1)>>24),  (unsigned char)((stopIP - 1)>>16),  (unsigned char)((stopIP - 1)>>8),  (unsigned char)((stopIP - 1)));
        printf("Hosts/Net: %d\n", stopIP - startIP - 1);
        printf("Class:     %c\n", class);
    }

    if (vverbose) {
        printf("Hosts:\n");
        for (uint32_t i = startIP + 1; i < stopIP; i++) {
            printf("  %d.%d.%d.%d\n", (unsigned char)(i>>24), (unsigned char)(i>>16), (unsigned char)(i>>8), (unsigned char)(i));
        }
    }

    return ;
}

void verbose(const char *msg, const char *file, const int line, const char *func, const bool enabled) {
    time_t now;
    struct tm *timeinfo;
    time(&now);
    timeinfo = localtime(&now);

    if (enabled) {
        fprintf(stderr, "%.2d:%.2d:%.2d | %s:%d | %s | DEBUG: %s\n", timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec, file, line, func, msg);
    }
}