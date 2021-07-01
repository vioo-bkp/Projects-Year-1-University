/* Mateescu F. Viorel-Cristian - 312CB */
#include "utils.h"

Resource *get_page_resources(const char *URL_Name, int *n)
{
    int i, j, name_len, url_name_len = strlen(URL_Name);

    unsigned int resource_nr = 0;
    uint32_t size = 0;
    if (URL_Name == NULL)
    {
        return NULL;
    }

    for (i = 0; i < url_name_len; i++)
    {
        resource_nr += URL_Name[i];
    }

    resource_nr %= 13;
    Resource *result = (Resource *)calloc(resource_nr, sizeof(Resource));
    *n = resource_nr;
    for (i = 0; i < resource_nr; i++)
    {
        sprintf(result[i].name, "%s-(%d)", URL_Name, i);
        size = 0;
        name_len = strlen(result[i].name);

        for (j = 0; j < name_len; j++)
        {
            size += result[i].name[j];
        }
        /* Some randomness */
        size ^= size << 3;
        size += size >> 5;
        size ^= size << 4;
        size += size >> 17;
        size ^= size << 25;
        size += size >> 6;

        /* 100MB Maximum size */
        result[i].dimension = size % 104857601;
        result[i].currently_downloaded = 0;
    }

    return result;
}

void push_page(Page **currentPage, Page *otherPage)
{
    if (*currentPage == NULL)
    {
        *currentPage = otherPage;
    }
    else
    {
        otherPage->next = *currentPage;
        *currentPage = otherPage;
    }
}
Page *pop_page(Page **currentPage)
{
    Page *page = *currentPage;
    *currentPage = (*currentPage)->next;
    return page;
}

void queueHistoryEntry(HistoryQueue *queue, HistoryNode *entry)
{

    if (queue->front == NULL)
    {
        queue->front = queue->rear = entry;
    }
    else
    {
        queue->rear->next = entry;
        queue->rear = entry;
    }
}
HistoryNode *dequeueHistoryEntry(HistoryQueue *queue)
{
    HistoryNode *temp = queue->front;
    if (temp != NULL)
    {
        queue->front = queue->front->next;
    }
    return temp;
}

void queueDownloadEntry(DownloadsPriorityQueue *queue, DownloadNode *entry)
{
    if (queue->front == NULL)
    {
        queue->front = entry;
    }
    else
    {
        if (entry->priority < queue->front->priority)
        {
            entry->next = queue->front;
            queue->front = entry;
        }
        else
        {
            DownloadNode *aux = queue->front;
            while (aux->next != NULL && aux->next->priority <= entry->priority)
            {
                aux = aux->next;
            }
            entry->next = aux->next;
            aux->next = entry;
        }
    }
}

DownloadNode* dequeueDownloadEntry(DownloadsPriorityQueue *queue)
{
    DownloadNode *temp = queue->front;
    if (queue->front != NULL)
    {
        queue->front = queue->front->next;
    }
    return temp;
}