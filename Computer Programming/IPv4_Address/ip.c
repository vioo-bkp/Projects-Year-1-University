/* Nume: Mateescu Viorel-Cristian
   Grupa: 312 CB
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
void binaryRepresentation(unsigned char n) {
// functie pentru reprezentarea binara a lui IP_1
    int i;
    for (i=7; i >=0; i--) {
      if ( ((1 << i) &n) !=0 ) {
               printf("1");
        } else {
               printf("0");
        }
    }
}
// n - numarul octetului
// retine in fiecare "unsigned char", fiecare byte al adresei
// obtine adresa din cei 4 bytes
unsigned char getByte(unsigned int IP, int n) {
unsigned char byte;
    if (n == 4) {
        byte = IP & 255;
     return byte;
    }

    if (n == 3) {
        IP = IP>>8;
        byte = IP & 255;
        return byte;
    }

    if (n == 2) {
        IP = IP>>16;
        byte = IP & 255;
        return byte;
    }

    if (n == 1) {
        IP = IP>>24;
        byte = IP & 255;
        return byte;
    }
        return byte;
}

int main() {
    unsigned int MSK_1, MSK_2, IP_1, IP_2, N;
    int a, b, c, d, nr_set;
    scanf("%d", &nr_set);

    for (int i=1; i <= nr_set; i++) {
        printf("%d\n", i);
        scanf("%d.%d.%d.%d", &a, &b, &c, &d);
// a-primul octet, b-al doilea, etc
        MSK_1 = (a << 24)+(b << 16)+(c << 8)+d;

        scanf("%u", &MSK_2);
        scanf("%d.%d.%d.%d", &a, &b, &c, &d);
        IP_1 = (a << 24)+(b << 16)+(c << 8)+d;

        scanf("%d.%d.%d.%d", &a, &b, &c, &d);
        IP_2 = (a << 24)+(b << 16)+(c << 8)+d;
// afisare IP_1 si MSK_2 in format IP_1/MSK_2
    printf("-0 %d.%d.%d.%d/%u\n", getByte(IP_1, 1), getByte(IP_1, 2),
                                  getByte(IP_1, 3), getByte(IP_1, 4), MSK_2);

    unsigned int mask = 0;

    for (int i = 0; i < 32; i++) {
        if (MSK_2 > 0) {
            mask = mask << 1;
            mask = mask | 1;
            MSK_2--;

        } else {
               mask = mask << 1;
        }
    }

// Task 1 & 2
     printf("-1 %d.%d.%d.%d\n", getByte(mask, 1), getByte(mask, 2),
                                getByte(mask, 3), getByte(mask, 4));
     printf("-2 %o.%o.%o.%o %X.%X.%X.%X\n",
       getByte(MSK_1, 1), getByte(MSK_1, 2),
       getByte(MSK_1, 3), getByte(MSK_1, 4),
       getByte(MSK_1, 1), getByte(MSK_1, 2),
       getByte(MSK_1, 3), getByte(MSK_1, 4));

// Task 3
     unsigned int aux = IP_1;
    aux = aux & mask;
    printf("-3 %d.%d.%d.%d\n", getByte(aux, 1), getByte(aux, 2),
                               getByte(aux, 3), getByte(aux, 4));
    aux = IP_1;

// Task 4
    unsigned int mask1 = ~mask; // adresa de broadcast IP_1
    aux = aux | mask1;
    printf("-4 %d.%d.%d.%d\n", getByte(aux, 1), getByte(aux, 2),
                               getByte(aux, 3), getByte(aux, 4));

// Task 5
    unsigned int aux1 = IP_1;
       aux1 = aux1 & mask;
    unsigned int aux2 = IP_2;
       aux2 = aux2 & mask;

    if (aux1 == aux2) {
        printf("-5 DA\n");
    } else {
        printf("-5 NU\n");
    }

// Task 6
    unsigned int MSK_1p;
      MSK_1p = MSK_1;

    int nr = 0, i;

    while (MSK_1 % 2 == 0) {
        MSK_1 = MSK_1 >> 1; nr++;
    }

    unsigned int masca = (1 << (31-nr)) - 1;

    if ((MSK_1 & masca) == masca) {
        printf("-6 DA\n");
    } else {
        printf("-6 NU\n");
    }

// Task 7
    if ((MSK_1 & masca) == masca) {
            printf("-7 %d.%d.%d.%d\n", getByte(MSK_1p, 1), getByte(MSK_1p, 2),
                                       getByte(MSK_1p, 3), getByte(MSK_1p, 4));
    } else {
    for (i=31; i >= 0; i--) {
        if ((MSK_1p & (1 << i)) == 0) {
            MSK_1p = (MSK_1p >> i) << i;
        break;
       }
}
        printf("-7 %d.%d.%d.%d\n", getByte(MSK_1p, 1), getByte(MSK_1p, 2),
                                   getByte(MSK_1p, 3), getByte(MSK_1p, 4));
        }
// Task 8
    printf("-8 ");
    binaryRepresentation(getByte(IP_1, 1));
    printf(".");
    binaryRepresentation(getByte(IP_1, 2));
    printf(".");
    binaryRepresentation(getByte(IP_1, 3));
    printf(".");
    binaryRepresentation(getByte(IP_1, 4));
    printf("\n");
// Task 9
    printf("-9");
    scanf("%u", &N);
    mask = 0;
    unsigned int networkIP, networkMask;

    for (i=0; i <= N-1; i++) {
        scanf("%d.%d.%d.%d/%u", &a, &b, &c, &d, &networkMask);
        networkIP = (a << 24)+(b << 16)+(c << 8)+d;
    for (int j = 0; j < 32; j++) {
        if (networkMask > 0) {
         mask = mask << 1;
         mask = mask | 1;
         networkMask--;
            } else {
                mask = mask << 1;
            }
        }
        if ( (IP_2 & mask) == (networkIP & mask) ) {
            printf(" %d", i);
        }
    }
    printf("\n");
    }
    return 0;
}
