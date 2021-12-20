/* Mateescu F. Viorel-Cristian - 312CB */
#include <stdio.h>
#include "utils.h"

enum Action
{
    None = 0,
    NewTab = 1,
    DelTab = 2,
    ChangeTab = 3,
    PrintOpenTabs = 4,
    GoTo = 5,
    Back = 6,
    Forward = 7,
    History = 8,
    ClearHistory = 9,
    ListDownloads = 10,
    Download = 11,
    ListResources = 12,
    SetBandWidth = 13,
    Wait = 14
} Action;

enum Action get_action(char *command)
{
    char *action = (char *)malloc(100);
    strcpy(action, command);

    if (strcmp(action, "newtab") == 0)
    {
        return NewTab;
    }
    else if (strcmp(action, "deltab") == 0)
    {
        return DelTab;
    }
    else if (strcmp(action, "print_open_tabs") == 0)
    {
        return PrintOpenTabs;
    }
    else if (strcmp(action, "back") == 0)
    {
        return Back;
    }
    else if (strcmp(action, "forward") == 0)
    {
        return Forward;
    }
    else if (strcmp(action, "history") == 0)
    {
        return History;
    }
    else if (strcmp(action, "list_dl") == 0)
    {
        return ListResources;
    }
    else if (strcmp(action, "downloads") == 0)
    {
        return ListDownloads;
    }

    action = strtok(action, " ");
    if (strcmp(action, "change_tab") == 0)
    {
        return ChangeTab;
    }
    else if (strcmp(action, "goto") == 0)
    {
        return GoTo;
    }
    else if (strcmp(action, "del_history") == 0)
    {
        return ClearHistory;
    }
    else if (strcmp(action, "download") == 0)
    {
        return Download;
    }
    else if (strcmp(action, "set_band") == 0)
    {
        return SetBandWidth;
    }
    else if (strcmp(action, "wait") == 0)
    {
        return Wait;
    }
    return None;
}

void init_browser(Browser **browser)
{
    *browser = (Browser *)malloc(sizeof(Browser));
    Tab *defaultTab = (Tab *)malloc(sizeof(Tab));
    defaultTab->current_page = NULL;
    defaultTab->tab_index = 0;
    defaultTab->next = NULL;
    (*browser)->tab = defaultTab;
    (*browser)->history = (HistoryQueue *)malloc(sizeof(HistoryQueue));
    (*browser)->history->front = NULL;
    (*browser)->downloadsInProgress = (DownloadsPriorityQueue *)malloc(sizeof(DownloadsPriorityQueue));
    (*browser)->downloadsFinished = (DownloadsPriorityQueue *)malloc(sizeof(DownloadsPriorityQueue));
    (*browser)->current_tab_index = 0;
    (*browser)->bandwith = 1024;
}

void add_new_tab(Browser *browser)
{
    Tab *new_tab = (Tab *)malloc(sizeof(Tab));
    new_tab->next = NULL;
    Tab *tab_aux = browser->tab;
    int i = 1;
    while (tab_aux != NULL)
    {
        if (tab_aux->next == NULL)
        {
            new_tab->tab_index = i;
            browser->current_tab_index = i;
            tab_aux->next = new_tab;
            return;
        }
        tab_aux = tab_aux->next;
        i++;
    }
}

Page *create_page(char *url)
{
    Page *page = (Page *)malloc(sizeof(Page));
    strcpy(page->name, url);
    return page;
}

HistoryNode *create_history_entry(char *url)
{
    HistoryNode *history = (HistoryNode *)malloc(sizeof(HistoryNode));
    strcpy(history->url, url);
    return history;
}

void add_to_history(Browser *browser, char *url)
{
    queueHistoryEntry(browser->history, create_history_entry(url));
}

void show_history(Browser *browser, FILE *fptr)
{
    HistoryNode *entry = dequeueHistoryEntry(browser->history);
    HistoryQueue *aux1 = (HistoryQueue *)malloc(sizeof(struct HistoryQueue));

    while (entry != NULL)
    {
        fprintf(fptr, "%s\n", entry->url);
        queueHistoryEntry(aux1, entry);
        entry = dequeueHistoryEntry(browser->history);
    }
    browser->history = aux1;
}

void process_download(Browser *browser, int time)
{
    DownloadNode *node = browser->downloadsInProgress->front;
    long int size = time * browser->bandwith;
    while (size > 0 && node != NULL)
    {
        unsigned long int leftDownload = node->resource.dimension - node->resource.currently_downloaded;
        if (size <= leftDownload)
        {
            node->resource.currently_downloaded += size;
        }
        else
        {
            dequeueDownloadEntry(browser->downloadsInProgress);
            DownloadNode *newNode = (DownloadNode *)malloc(sizeof(DownloadNode));
            newNode->priority = 0;
            newNode->resource = node->resource;
            newNode->next = NULL;
            queueDownloadEntry(browser->downloadsFinished, newNode);
        }
        size -= leftDownload;
        node = node->next;
    }
}

void go_to_previous(Browser *browser)
{
    int i = 0;
    Tab *tab_aux = browser->tab;
    while (i != browser->current_tab_index)
    {
        tab_aux = tab_aux->next;
        i++;
    }

    push_page(&tab_aux->forward, tab_aux->current_page);

    tab_aux->current_page = pop_page(&tab_aux->back);
}

void go_to_next(Browser *browser)
{
    int i = 0;
    Tab *tab_aux = browser->tab;
    while (i != browser->current_tab_index)
    {
        tab_aux = tab_aux->next;
        i++;
    }
    push_page(&tab_aux->back, tab_aux->current_page);
    tab_aux->current_page = pop_page(&tab_aux->forward);
}

void go_to(Browser *browser, char *url)
{
    int i = 0;
    Tab *tab_aux = browser->tab;

    while (i != browser->current_tab_index)
    {
        tab_aux = tab_aux->next;
        i++;
    }

    if (tab_aux->current_page == NULL)
    {
        Page *page = create_page(url);
        page->next = NULL;
        tab_aux->current_page = page;
    }
    else
    {
        push_page(&tab_aux->back, tab_aux->current_page);
        Page *page = create_page(url);
        tab_aux->current_page = page;
    }
    add_to_history(browser, url);
    process_download(browser, 1);
}

void print_open_tabs(Browser *browser, FILE *fptr)
{
    Tab *tab_aux = browser->tab;
    while (tab_aux != NULL)
    {
        fprintf(fptr, "(%d: %s)\n", tab_aux->tab_index, tab_aux->current_page->name != NULL ? tab_aux->current_page->name : "empty");
        //printf("(%d: %s)\n", tab_aux->tab_index, tab_aux->current_page->name != NULL ? tab_aux->current_page->name : "empty");
        tab_aux = tab_aux->next;
    }
}

void change_tab(Browser **browser, int tabNo)
{
    (*browser)->current_tab_index = tabNo;
}

void clear_history(Browser **browser, int entries)
{
    if (entries != 0)
    {
        while (entries-- != 0 && (*browser)->history != NULL)
        {
            dequeueHistoryEntry((*browser)->history);
        }
    }
    else
    {
        (*browser)->history->front = NULL;
    }
}

void fill_resources_if_needed(Browser *browser)
{
    int i = 0;
    Tab *tab_aux = browser->tab;

    while (i != browser->current_tab_index)
    {
        tab_aux = tab_aux->next;
        i++;
    }

    if (tab_aux->current_page != NULL && tab_aux->current_page->resources == NULL)
    {
        Resource *resources = get_page_resources(tab_aux->current_page->name, &tab_aux->current_page->num_res);
        tab_aux->current_page->resources = resources;
    }
}

void show_resources(Browser *browser, FILE *fptr)
{

    fill_resources_if_needed(browser);
    int i = 0;
    Tab *tab_aux = browser->tab;

    while (i != browser->current_tab_index)
    {
        tab_aux = tab_aux->next;
        i++;
    }
    if (tab_aux->current_page->name != NULL)
    {
        Resource *resources = tab_aux->current_page->resources;
        int i;
        for (i = 0; i < tab_aux->current_page->num_res; i++)
        {
            fprintf(fptr, "[%d - \"%s\" : %ld]\n", i, resources[i].name, resources[i].dimension);
            //printf("[%d - \"%s\" : %ld]\n", i, resources[i].name, resources[i].dimension);
        }
    }
}

void download_resource(Browser *browser, int resourceIndex)
{
    fill_resources_if_needed(browser);
    int i = 0;
    Tab *tab_aux = browser->tab;

    while (i != browser->current_tab_index)
    {
        tab_aux = tab_aux->next;
        i++;
    }
    if (tab_aux->current_page != NULL && tab_aux->current_page->num_res >= resourceIndex)
    {

        Resource resource = tab_aux->current_page->resources[resourceIndex];
        DownloadNode *node = (DownloadNode *)malloc(sizeof(DownloadNode));
        node->priority = resource.dimension;
        node->resource = resource;
        node->next = NULL;

        queueDownloadEntry(browser->downloadsInProgress, node);
    }
}

void set_bandwidth(Browser *browser, int bandwidth)
{
    browser->bandwith = bandwidth;
}

void show_downloads(Browser *browser, FILE *fptr)
{
    DownloadNode *entry = browser->downloadsInProgress->front;
    DownloadsPriorityQueue *aux1 = (DownloadsPriorityQueue *)malloc(sizeof(struct DownloadsPriorityQueue));

    while (entry != NULL)
    {
        entry = dequeueDownloadEntry(browser->downloadsInProgress);
        if (entry != NULL)
        {
            fprintf(fptr, "[\"%s\" : %ld/%ld]\n", entry->resource.name, entry->resource.dimension - entry->resource.currently_downloaded, entry->resource.dimension);
            entry->next = NULL;
            queueDownloadEntry(aux1, entry);
        }
    }
    browser->downloadsInProgress = aux1;

    DownloadNode *entry1 = browser->downloadsFinished->front;
    DownloadsPriorityQueue *aux2 = (DownloadsPriorityQueue *)malloc(sizeof(struct DownloadsPriorityQueue));
    while (entry1 != NULL)
    {
        entry1 = dequeueDownloadEntry(browser->downloadsFinished);
        if (entry1 != NULL)
        {
            fprintf(fptr, "[\"%s\" : \"completed\"]\n", entry1->resource.name);
            entry1->next = NULL;
            queueDownloadEntry(aux2, entry1);
        }
    }
    browser->downloadsFinished = aux2;
}

void delete_last_tab(Browser *browser)
{
    Tab *last_tab;
    Tab *penultimate_tab;
    Tab *aux = browser->tab;

    while (aux->next != NULL)
    {
        if (aux->next->next == NULL)
        {
            penultimate_tab = aux;
        }
        aux = aux->next;
    }

    last_tab = aux;
    if (last_tab->tab_index == browser->current_tab_index)
    {
        browser->current_tab_index = penultimate_tab->tab_index;
    }
    penultimate_tab->next = NULL;
}

void start(Browser **browser, char *fileInputName, char *fileOutputName)
{
    FILE *fpIn;
    FILE *fpOut;
    char *command = NULL;
    size_t len = 0;
    size_t read;

    fpIn = fopen(fileInputName, "r");
    if (fpIn == NULL)
        exit(EXIT_FAILURE);
    fpOut = fopen(fileOutputName, "w");
    if (fpOut == NULL)
        exit(EXIT_FAILURE);

    while ((read = getline(&command, &len, fpIn)) != -1)
    {
        command[strlen(command) - 1] = '\0';
        enum Action action = get_action(command);
        switch (action)
        {
        case NewTab:
            add_new_tab(*browser);
            break;
        case PrintOpenTabs:
            print_open_tabs(*browser, fpOut);
            break;
        case GoTo:
            strtok(command, " ");
            char *url = strtok(NULL, " ");
            go_to(*browser, url);
            break;
        case History:
            show_history(*browser, fpOut);
            break;
        case Back:
            go_to_previous(*browser);
            break;
        case Forward:
            go_to_next(*browser);
            break;
        case ChangeTab:
            strtok(command, " ");
            char *tabNo = strtok(NULL, " ");
            change_tab(browser, atoi(tabNo));
            break;
        case ClearHistory:
            strtok(command, " ");
            char *historyEntries = strtok(NULL, " ");
            clear_history(browser, atoi(historyEntries));
            break;
        case ListResources:
            show_resources(*browser, fpOut);
            break;
        case Download:
            strtok(command, " ");
            char *resourceIndex = strtok(NULL, " ");
            download_resource(*browser, atoi(resourceIndex));
            break;
        case ListDownloads:
            show_downloads(*browser, fpOut);
            break;
        case Wait:
            strtok(command, " ");
            char *time = strtok(NULL, " ");
            process_download(*browser, atoi(time));
            break;
        case SetBandWidth:
            strtok(command, " ");
            char *bandwitdh = strtok(NULL, " ");
            set_bandwidth(*browser, atoi(bandwitdh));
            break;
        case DelTab:
            delete_last_tab(*browser);
            break;
        default:
            break;
        }
    }
}

int main(int argc, char **argv)
{
    Browser *browser;
    init_browser(&browser);
    char *fileInputName = argv[1];
    char *fileOutputName = argv[2];
    start(&browser, fileInputName, fileOutputName);
    return 0;
}