#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <sys/utsname.h>
#include <net/if.h>
#include <netinet/in.h>
#include <net/if_arp.h>
#include <linux/if_packet.h>
#include <linux/ip.h>
#include <linux/udp.h>
#include <netinet/ether.h>
#include <pthread.h>

/*
 * 2 examples are shown here
 *
 * 1.) Multiple TX threads using the same socket to send the data out of the same interface.
 *
 * 2.) Multiple RX threads receiving from the same socket and multiple RX threads using 2 different sockets.
 *      In the latter case the packet is duplicated to both sockets and in the former it depends on who is reday
 *     to receive.
 */

typedef struct sock_data_ {
    int sock;
    struct sockaddr_ll socket_address;
}sock_data_t;


sock_data_t sockets[2];

unsigned short 
csum(unsigned short *buf, int nwords)
{
    unsigned long sum;
    for(sum=0; nwords>0; nwords--)
        sum += *buf++;
    sum = (sum >> 16) + (sum &0xffff);
    sum += (sum >> 16);
    return (unsigned short)(~sum);
}

unsigned char sendbuf[1024];
int tx_len = 0;
int rx_sockfd = -1;
int rx_sockfd2 = -1;
#define BUF_SIZ 1024

static void *
rx_thread2 (void *arg)
{
    ssize_t numbytes;
    struct ifreq ifopts;    /* set promiscuous mode */
    struct ifreq if_ip; /* get ip addr */
    struct sockaddr_storage their_addr;
    uint8_t buf[BUF_SIZ];
    char ifName[IFNAMSIZ];
    char sender[1024];
    int sockopt;

    /* Header structures */
    struct ether_header *eh = (struct ether_header *) buf;
    struct iphdr *iph = (struct iphdr *) (buf + sizeof(struct ether_header));
    struct udphdr *udph = (struct udphdr *) (buf + sizeof(struct iphdr) + sizeof(struct ether_header));

    memset(&if_ip, 0, sizeof(struct ifreq));

    /* Open PF_PACKET socket, listening for EtherType ETHER_TYPE */
    if ((rx_sockfd2 = socket(AF_PACKET, SOCK_RAW, htons(0x0800))) == -1) {
        perror("listener: socket"); 
        goto done;
    }

    /* Set interface to promiscuous mode - do we need to do this every time? */
    strncpy(ifopts.ifr_name, ifName, IFNAMSIZ-1);
    ioctl(rx_sockfd2, SIOCGIFFLAGS, &ifopts);
    ifopts.ifr_flags |= IFF_PROMISC;
    ioctl(rx_sockfd2, SIOCSIFFLAGS, &ifopts);
    /* Allow the socket to be reused - incase connection is closed prematurely */
    if (setsockopt(rx_sockfd2, SOL_SOCKET, SO_REUSEADDR, &sockopt, sizeof sockopt) == -1) {
        perror("setsockopt");
        close(rx_sockfd2);
        goto done;
    }
    /* Bind to device */
    if (setsockopt(rx_sockfd2, SOL_SOCKET, SO_BINDTODEVICE, ifName, IFNAMSIZ-1) == -1)  {
        perror("SO_BINDTODEVICE");
        close(rx_sockfd2);
        goto done;
    }

    printf("\nrx_Thread2: Waiting to recvfrom...\n");

    while (1) {
        numbytes = recvfrom(rx_sockfd, buf, BUF_SIZ, 0, NULL, NULL);
        printf("\nRX_T2: got packet %lu bytes", numbytes);
        printf("\nRX_T2: %02x:%02x:%02x:%02x:%02x:%02x ",
                eh->ether_dhost[0],
                eh->ether_dhost[1],
                eh->ether_dhost[2],
                eh->ether_dhost[3],
                eh->ether_dhost[4],
                eh->ether_dhost[5]);

        ((struct sockaddr_in *)&their_addr)->sin_addr.s_addr = iph->saddr;
        inet_ntop(AF_INET, &((struct sockaddr_in*)&their_addr)->sin_addr, sender, sizeof sender);

        printf("\nRX_T2:Sender : %s id:%d",sender,ntohs(iph->id));

        //sleep(1);
    }

done:
    printf("\n Exiting RX thread2");
}
static void *
rx_thread (void *arg)
{
    ssize_t numbytes;
    struct ifreq ifopts;    /* set promiscuous mode */
    struct ifreq if_ip; /* get ip addr */
    struct sockaddr_storage their_addr;
    uint8_t buf[BUF_SIZ];
    char ifName[IFNAMSIZ];
    char sender[1024];
    int sockopt;

    /* Header structures */
    struct ether_header *eh = (struct ether_header *) buf;
    struct iphdr *iph = (struct iphdr *) (buf + sizeof(struct ether_header));
    struct udphdr *udph = (struct udphdr *) (buf + sizeof(struct iphdr) + sizeof(struct ether_header));

    memset(&if_ip, 0, sizeof(struct ifreq));

    /* Open PF_PACKET socket, listening for EtherType ETHER_TYPE */
    if ((rx_sockfd = socket(AF_PACKET, SOCK_RAW, htons(0x0800))) == -1) {
        perror("listener: socket"); 
        return;
    }

    /* Set interface to promiscuous mode - do we need to do this every time? */
    strncpy(ifopts.ifr_name, ifName, IFNAMSIZ-1);
    ioctl(rx_sockfd, SIOCGIFFLAGS, &ifopts);
    ifopts.ifr_flags |= IFF_PROMISC;
    ioctl(rx_sockfd, SIOCSIFFLAGS, &ifopts);
    /* Allow the socket to be reused - incase connection is closed prematurely */
    if (setsockopt(rx_sockfd, SOL_SOCKET, SO_REUSEADDR, &sockopt, sizeof sockopt) == -1) {
        perror("setsockopt");
        close(rx_sockfd);
        return;
    }
    /* Bind to device */
    if (setsockopt(rx_sockfd, SOL_SOCKET, SO_BINDTODEVICE, ifName, IFNAMSIZ-1) == -1)  {
        perror("SO_BINDTODEVICE");
        close(rx_sockfd);
        return;
    }

    printf("\nrx_Thread: Waiting to recvfrom...\n");

    while (1) {
        numbytes = recvfrom(rx_sockfd, buf, BUF_SIZ, 0, NULL, NULL);
        printf("\nRX_T1: got packet %lu bytes", numbytes);
        printf("\nRX_T1:%02x:%02x:%02x:%02x:%02x:%02x ",
                eh->ether_dhost[0],
                eh->ether_dhost[1],
                eh->ether_dhost[2],
                eh->ether_dhost[3],
                eh->ether_dhost[4],
                eh->ether_dhost[5]);

        ((struct sockaddr_in *)&their_addr)->sin_addr.s_addr = iph->saddr;
        inet_ntop(AF_INET, &((struct sockaddr_in*)&their_addr)->sin_addr, sender, sizeof sender);

        printf("\nRX_T1:Sender : %s id:%d",sender,ntohs(iph->id));

        //sleep(1);
    }

    printf("\n Exiting RX thread");

}

static void *
thread1 (void *arg)
{
    printf("\n Thread 1.....");

    //hack
    return;

    while (1) {
        printf("\n T1 sending packet");
        if (sendto(sockets[0].sock, sendbuf, tx_len, 0, (struct sockaddr*)&sockets[0].socket_address, sizeof(struct sockaddr_ll)) < 0)
            printf("Send failed\n");
        sleep(5);
    }

    printf("\n Leaving thread ....");
}

static void *
thread2 (void *arg)
{
    printf("\n Thread 2.....");

    //hack
    return;
    while (1) {
        printf("\n T2 sending packet");
        if (sendto(sockets[1].sock, sendbuf, tx_len, 0, (struct sockaddr*)&sockets[1].socket_address, sizeof(struct sockaddr_ll)) < 0)
            printf("Send failed\n");
        sleep(5);
    }

    printf("\n Leaving thread2 ....");
}

int main (int argc, char **argv)
{
    int sockfd = -1, sockfd2  = -1;
    struct ifreq if_idx;
    struct ifreq if_mac,if_ip;
    struct ether_header *eh = (struct ether_header *) sendbuf;
    struct iphdr *iph = (struct iphdr *) (sendbuf + sizeof(struct ether_header));
    struct udphdr *udph = (struct udphdr *) (sendbuf + sizeof(struct iphdr) + sizeof(struct ether_header));
    struct sockaddr_ll socket_address;
    int status = -1;
    pthread_t th1, th2,th3,th4;

    /* Open RAW socket to send on */
    if ((sockfd = socket(AF_PACKET, SOCK_RAW, IPPROTO_RAW)) == -1) {
        perror("Socket");
    }
    if ((sockfd2 = socket(AF_PACKET, SOCK_RAW, IPPROTO_RAW)) == -1) {
        perror("Socket");
    }

    printf("\n Socket: %d socketfd2: %d",sockfd, sockfd2);

    memset(&if_idx, 0x0, sizeof(if_idx));
    strncpy(if_idx.ifr_name, "eth0", IFNAMSIZ-1);
    if (ioctl(sockfd, SIOCGIFINDEX, &if_idx) < 0)
            perror("SIOCGIFINDEX");


    memset(&if_mac, 0, sizeof(struct ifreq));
    strncpy(if_mac.ifr_name, "eth0", IFNAMSIZ-1);
    if (ioctl(sockfd, SIOCGIFHWADDR, &if_mac) < 0)
            perror("SIOCGIFHWADDR");


    memset(&if_ip, 0, sizeof(struct ifreq));
    strncpy(if_ip.ifr_name, "eth0", IFNAMSIZ-1);
    if (ioctl(sockfd, SIOCGIFADDR, &if_ip) < 0)
            perror("SIOCGIFADDR");


    memset(sendbuf, 0, 1024);
    /* Ethernet header */
    eh->ether_shost[0] = ((uint8_t *)&if_mac.ifr_hwaddr.sa_data)[0];
    eh->ether_shost[1] = ((uint8_t *)&if_mac.ifr_hwaddr.sa_data)[1];
    eh->ether_shost[2] = ((uint8_t *)&if_mac.ifr_hwaddr.sa_data)[2];
    eh->ether_shost[3] = ((uint8_t *)&if_mac.ifr_hwaddr.sa_data)[3];
    eh->ether_shost[4] = ((uint8_t *)&if_mac.ifr_hwaddr.sa_data)[4];
    eh->ether_shost[5] = ((uint8_t *)&if_mac.ifr_hwaddr.sa_data)[5];
    eh->ether_type = htons(ETH_P_IP);
    tx_len += sizeof(struct ether_header);



    /* IP Header */
    iph->ihl = 5;
    iph->version = 4;
    iph->tos = 16; // Low delay
    iph->id = htons(54321);
    iph->ttl = 255; // hops
    iph->protocol = 17; // UDP
    /* Source IP address, can be spoofed */
    iph->saddr = inet_addr(inet_ntoa(((struct sockaddr_in *)&if_ip.ifr_addr)->sin_addr));
    // iph->saddr = inet_addr("192.168.0.112");
    /* Destination IP address */
    iph->daddr = inet_addr("1.1.1.10");
    tx_len += sizeof(struct iphdr);


    /* UDP Header */
    udph->source = htons(3423);
    udph->dest = htons(5342);
    udph->check = 0; // skip
    tx_len += sizeof(struct udphdr);

    sendbuf[tx_len++] = 0xde;
    sendbuf[tx_len++] = 0xad;
    sendbuf[tx_len++] = 0xbe;
    sendbuf[tx_len++] = 0xef;


    udph->len = htons(tx_len - sizeof(struct ether_header) - sizeof(struct iphdr));
    /* Length of IP payload and header */
    iph->tot_len = htons(tx_len - sizeof(struct ether_header));
    /* Calculate IP checksum on completed header */
    iph->check = csum((unsigned short *)(sendbuf+sizeof(struct ether_header)), sizeof(struct iphdr)/2);


    /* Index of the network device */
    socket_address.sll_ifindex = if_idx.ifr_ifindex;
    /* Address length*/
    socket_address.sll_halen = ETH_ALEN;
    /* Destination MAC */
    socket_address.sll_addr[0] = 0xaa;
    socket_address.sll_addr[1] = 0xbb;
    socket_address.sll_addr[2] = 0xcc;
    socket_address.sll_addr[3] = 0xdd;
    socket_address.sll_addr[4] = 0xee;
    socket_address.sll_addr[5] = 0xff;

#if 0
    /* Send packet */
    if (sendto(sockfd, sendbuf, tx_len, 0, (struct sockaddr*)&socket_address, sizeof(struct sockaddr_ll)) < 0)
        printf("Send failed\n");
    if (sendto(sockfd2, sendbuf, tx_len, 0, (struct sockaddr*)&socket_address, sizeof(struct sockaddr_ll)) < 0)
        printf("Send failed\n");
#endif

    sockets[0].sock = sockfd;
    sockets[1].sock = sockfd2;

    memcpy(&sockets[0].socket_address, &socket_address, sizeof(socket_address));
    memcpy(&sockets[1].socket_address, &socket_address, sizeof(socket_address));

    status = pthread_create(&th1, NULL, &thread1, NULL);
    if (status < 0 ) {
        printf("\n Failed to create thread 1");
        return -1;
    }
    status = pthread_create(&th2, NULL, &thread2, NULL);
    if (status < 0 ) {
        printf("\n Failed to create thread 2");
        return -1;
    }
    status = pthread_create(&th3, NULL, &rx_thread, NULL);
    if (status < 0 ) {
        printf("\n Failed to create thread 3");
        return -1;
    }
    status = pthread_create(&th4, NULL, &rx_thread2, NULL);
    if (status < 0 ) {
        printf("\n Failed to create thread 4");
        return -1;
    }

    pthread_join(th1, NULL);
    pthread_join(th2, NULL);
    pthread_join(th3, NULL);
    pthread_join(th4, NULL);



    return 0;
}
