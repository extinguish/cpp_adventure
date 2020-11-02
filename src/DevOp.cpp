//
// Created by guoshichao on 2020/5/16.
//

#include <errno.h>
#include <strings.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


int getDevMac(unsigned char *macAddr) {
    struct ifreq ifr;
    struct ifconf ifc;
    char buf[1024] = {0};
    int success = 0;
    int sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_IP);
    if (sock == -1) {
        printf("error happened while get create the socket, caused by %s", strerror(errno));
        return -1;
    }

    ifc.ifc_len = sizeof(buf);
    ifc.ifc_buf = buf;
    if (ioctl(sock, SIOCGIFCONF, &ifc) == -1) {
        printf("error happened while read data from ifc, caused by %s", strerror(errno));
        return -1;
    }

    struct ifreq *it = ifc.ifc_req;
    const struct ifreq *const end = it + (ifc.ifc_len / sizeof(struct ifreq));
    for (; it != end; ++it) {
        strcpy(ifr.ifr_name, it->ifr_name);
        if (ioctl(sock, SIOCGIFFLAGS, &ifr) == 0) {
            if (!(ifr.ifr_flags & IFF_LOOPBACK)) {
                if (ioctl(sock, SIOCGIFHWADDR, &ifr) == 0) {
                    success = 1;
                    break;
                }
            }
        }
    }

    if (!success) {
        printf("fail to get the mac address, caused by %s", strerror(errno));
        return -1;
    }

    printf("the mac address we get from are : %s", ifr.ifr_hwaddr.sa_data);

    printf("\n");
    memcpy(macAddr, ifr.ifr_hwaddr.sa_data, 6);

    return 0;
}

int main(int argc, char **argv) {
    unsigned char mac[6] = {0};
    getDevMac(mac);
    for (int i = 0; i < 6; ++i) {
        printf("%.2x ", mac[i]);
    }
    return 0;
}
