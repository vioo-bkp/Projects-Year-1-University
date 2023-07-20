/* Nume: Mateescu Viorel-Cristian
   Grupa: 312 CB */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define BITS_PER_BYTE 8
#define MAX_OCTET_VALUE 255
#define MAX_MASK_LENGTH 32

void binaryRepresentation(unsigned char n) {
    for (int i = BITS_PER_BYTE - 1; i >= 0; i--) {
        printf("%d", (n >> i) & 1);
    }
}

unsigned char getByte(unsigned int IP, int n) {
    unsigned char byte = 0;
    if (n == 4) {
        byte = IP & MAX_OCTET_VALUE;
    } else if (n == 3) {
        byte = (IP >> BITS_PER_BYTE) & MAX_OCTET_VALUE;
    } else if (n == 2) {
        byte = (IP >> (2 * BITS_PER_BYTE)) & MAX_OCTET_VALUE;
    } else if (n == 1) {
        byte = (IP >> (3 * BITS_PER_BYTE)) & MAX_OCTET_VALUE;
    }
    return byte;
}

unsigned int createMask(int length) {
    unsigned int mask = 0;
    for (int i = 0; i < MAX_MASK_LENGTH; i++) {
        if (length > 0) {
            mask = (mask << 1) | 1;
            length--;
        } else {
            mask = mask << 1;
        }
    }
    return mask;
}

void printIP(unsigned int IP) {
    for (int i = 1; i <= 4; i++) {
        printf("%d", getByte(IP, i));
        if (i < 4) {
            printf(".");
        }
    }
}

void printTask1(unsigned int IP, unsigned int mask) {
    unsigned int networkIP = IP & mask;
    printf("-1 ");
    printIP(networkIP);
    printf("\n");
}

void printTask2(unsigned int MSK_1) {
    printf("-2 %o.%o.%o.%o %X.%X.%X.%X\n",
           getByte(MSK_1, 1), getByte(MSK_1, 2),
           getByte(MSK_1, 3), getByte(MSK_1, 4),
           getByte(MSK_1, 1), getByte(MSK_1, 2),
           getByte(MSK_1, 3), getByte(MSK_1, 4));
}

void printTask3(unsigned int IP, unsigned int mask) {
    unsigned int networkIP = IP & mask;
    printf("-3 ");
    printIP(networkIP);
    printf("\n");
}

void printTask4(unsigned int IP, unsigned int mask) {
    unsigned int broadcastIP = IP | ~mask;
    printf("-4 ");
    printIP(broadcastIP);
    printf("\n");
}

void printTask5(unsigned int IP_1, unsigned int IP_2, unsigned int mask) {
    unsigned int networkIP_1 = IP_1 & mask;
    unsigned int networkIP_2 = IP_2 & mask;
    printf("-5 %s\n", (networkIP_1 == networkIP_2) ? "DA" : "NU");
}

void printTask6(unsigned int MSK_1) {
    unsigned int MSK_1p = MSK_1;
    int shiftCount = 0;
    while (MSK_1 % 2 == 0) {
        MSK_1 = MSK_1 >> 1;
        shiftCount++;
    }
    unsigned int masca = createMask(MAX_MASK_LENGTH - shiftCount);
    printf("-6 %s\n", ((MSK_1 & masca) == masca) ? "DA" : "NU");
}

void printTask7(unsigned int MSK_1) {
    unsigned int MSK_1p = MSK_1;
    for (int i = MAX_MASK_LENGTH - 1; i >= 0; i--) {
        if ((MSK_1p & (1 << i)) == 0) {
            MSK_1p = (MSK_1p >> i) << i;
            break;
        }
    }
    printf("-7 ");
    printIP(MSK_1p);
    printf("\n");
}

void printTask8(unsigned int IP_1) {
    printf("-8 ");
    for (int i = 1; i <= 4; i++) {
        binaryRepresentation(getByte(IP_1, i));
        if (i < 4) {
            printf(".");
        }
    }
    printf("\n");
}

void printTask9(unsigned int IP_2, unsigned int N) {
    printf("-9");
    unsigned int mask = 0;
    for (int i = 0; i < MAX_MASK_LENGTH; i++) {
        if (N > 0) {
            mask = (mask << 1) | 1;
            N--;
        } else {
            mask = mask << 1;
        }
    }

    unsigned int networkIP, networkMask;
    for (int i = 0; i < N; i++) {
        scanf("%d.%d.%d.%d/%u", &a, &b, &c, &d, &networkMask);
        networkIP = (a << 24) + (b << 16) + (c << 8) + d;
        if ((IP_2 & mask) == (networkIP & mask)) {
            printf(" %d", i);
        }
    }
    printf("\n");
}

int main() {
    unsigned int MSK_1, MSK_2, IP_1, IP_2, N;
    int a, b, c, d, nr_set;
    scanf("%d", &nr_set);

    for (int i = 1; i <= nr_set; i++) {
        printf("%d\n", i);
        scanf("%d.%d.%d.%d", &a, &b, &c, &d);
        IP_1 = (a << 24) + (b << 16) + (c << 8) + d;

        scanf("%u", &MSK_2);
        scanf("%d.%d.%d.%d", &a, &b, &c, &d);
        IP_2 = (a << 24) + (b << 16) + (c << 8) + d;

        printf("-0 %d.%d.%d.%d/%u\n", getByte(IP_1, 1), getByte(IP_1, 2),
               getByte(IP_1, 3), getByte(IP_1, 4), MSK_2);

        MSK_1 = createMask(MSK_2);
        printTask1(IP_1, MSK_1);
        printTask2(MSK_1);
        printTask3(IP_1, MSK_1);
        printTask4(IP_1, MSK_1);
        printTask5(IP_1, IP_2, MSK_1);
        printTask6(MSK_1);
        printTask7(MSK_1);
        printTask8(IP_1);

        printf("-9");
        scanf("%u", &N);
        printTask9(IP_2, N);
    }
    return 0;
}
