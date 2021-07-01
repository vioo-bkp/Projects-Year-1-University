#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>

#ifndef _DOWNLOAD_RESOURCE_
#define _DOWNLOAD_RESOURCE_

typedef struct
{
    char name[100];
    unsigned long dimension;
    unsigned long currently_downloaded;
} Resource;

Resource *get_page_resources(const char *URL_Name, int *n);

#endif /* _DOWNLOAD_RESOURCE_ */

#ifndef _PAGE_
#define _PAGE_

typedef struct Page
{
    char name[100];
    int num_res;
    Resource *resources;
    struct Page *next;

} Page;

#endif /* _PAGE_ */

#ifndef _TAB_
#define _TAB_

typedef struct Tab
{
    Page *current_page;
    Page *back;
    Page *forward;
    struct Tab *next;
    int tab_index;
} Tab;

void push_page(Page **currentPage, Page *otherPage);
Page *pop_page(Page **currentPage);

#endif /* _TAB_ */

#ifndef _HISTORY
#define _HISTORY

typedef struct HistoryNode
{
    char url[100];
    struct HistoryNode *next;
} HistoryNode;

typedef struct HistoryQueue
{
    struct HistoryNode *front;
    struct HistoryNode *rear;
} HistoryQueue;

typedef struct DownloadNode
{
    Resource resource;
    int priority;
    struct DownloadNode *next;
} DownloadNode;

typedef struct DownloadsPriorityQueue
{
    DownloadNode *front;
} DownloadsPriorityQueue;

#endif /* _HISTORY */

#ifndef _BROWSER_
#define _BROWSER_

typedef struct
{
    Tab *tab;
    HistoryQueue *history;
    int current_tab_index;
    DownloadsPriorityQueue *downloadsInProgress;
    DownloadsPriorityQueue *downloadsFinished;
    int bandwith;
} Browser;

#endif /* _BROWSER_ */

void queueHistoryEntry(HistoryQueue *queue, HistoryNode *entry);
HistoryNode *dequeueHistoryEntry(HistoryQueue *queue);
void queueDownloadEntry(DownloadsPriorityQueue *queue, DownloadNode *entry);
DownloadNode *dequeueDownloadEntry(DownloadsPriorityQueue *queue);
