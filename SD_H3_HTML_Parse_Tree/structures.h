#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef _STRUCTURES_
#define _STRUCTURES_

/* Lista generica */

typedef struct cell {
  void *info;
  struct cell *urm;
} TCell, *ACell;

void DistrLG(ACell *list);
int InsLG(ACell *List, void *elem);

#endif /* _STRUCTURES_ */
