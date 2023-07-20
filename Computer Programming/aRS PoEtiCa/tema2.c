/* Nume: Mateescu F. Viorel-Cristian
   Grupa: 312 CB */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "util/task_helper.h"

#define MAX 6969

void uppercase(char* text) {
    char* aux = text;
    if (*aux >= 'a' && *aux <= 'z') {
        *aux -= 32;
        aux++;
    } else if (*aux >= 'A' && *aux <= 'Z') {
        aux++;
    }
    while (*aux) {
        if (*aux >= 'A' && *aux <= 'Z') {
            if (*(aux - 1) != '\n') {
                *aux += 32;
            }
        } else if (*aux >= 'a' && *aux <= 'z') {
            if (*(aux - 1) == '\n') {
                *aux -= 32;
            }
        }
        aux++;
    }
}

void trimming(char* str) {
    char aux[MAX];
    int j = 0;
    int ok = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z')) {
            aux[j] = str[i];
            j++;
            ok = 0;
        } else if (str[i] == '\n' || str[i] == '-' || str[i] == 39) {
            aux[j] = str[i];
            j++;
            ok = 0;
        } else if (str[i] == ' ' && ok == 0) {
            aux[j] = str[i];
            j++;
            ok = 1;
        }
    }
    aux[j] = '\0';
    strcpy(str, aux);
}

void silly(char* str, char* const prob) {
    char* c = str;
    while (*c) {
        if ((*c >= 'a' && *c <= 'z') || (*c >= 'A' && *c <= 'Z')) {
            float p = atof(prob);
            float sample = rand() % 100 / 99.0;
            if (p > sample) {
                if (*c >= 'a' && *c <= 'z') {
                    *c -= 32;
                } else {
                    *c += 32;
                }
            }
        }
        c++;
    }
}

void rhimy(char* str, char* rima) {
    char aux[MAX];
    char poem[MAX];
    strcpy(poem, str);
    char vers[200][200];
    int x = 0, j = 0, i;
    char cuv[200];
    char* tok = strtok(str, "\n");
    while (tok != NULL) {
        for (i = 0; tok[i] != '\0'; i++) {
            if ((tok[i] >= 'a' && tok[i] <= 'z') || (tok[i] >= 'A' && tok[i] <= 'Z') || tok[i] == '-') {
                cuv[j] = tok[i];
                j++;
                cuv[j] = '\0';
            } else {
                if (cuv[0] != '\0') {
                    strcpy(vers[x], cuv);
                }
                j = 0;
            }
        }
        if (cuv[0] != '\0') {
            strcpy(vers[x], cuv);
            x++;
        }
        for (int k = 0; cuv[k] != '\0'; k++) {
            cuv[k] = '\0';
        }
        j = 0;
        tok = strtok(NULL, "\n");
    }
    if (strcmp(rima, "imperecheata") == 0) {
        for (i = 0; i < x - 1; i += 2) {
            if (vers[i][strlen(vers[i]) - 1] != vers[i + 1][strlen(vers[i + 1]) - 1] &&
                vers[i][strlen(vers[i]) - 1] != vers[i + 1][strlen(vers[i + 1]) - 1] - 32 &&
                vers[i][strlen(vers[i]) - 1] != vers[i + 1][strlen(vers[i + 1]) - 1] + 32) {
                char** sinonime;
                int n;
                get_synonym(vers[i], &n, &sinonime);
                char sin[50] = "zz";
                for (int b = 0; b < n; b++) {
                    if (vers[i + 1][strlen(vers[i + 1]) - 1] == sinonime[b][strlen(sinonime[b]) - 1] ||
                        vers[i + 1][strlen(vers[i + 1]) - 1] == sinonime[b][strlen(sinonime[b]) - 1] - 32) {
                        if (strcmp(sin, sinonime[b]) > 0) {
                            strcpy(sin, sinonime[b]);
                        }
                    }
                }
                if (strcmp(sin, "zz") != 0) {
                    strcpy(vers[i], sin);
                } else {
                    get_synonym(vers[i + 1], &n, &sinonime);
                    for (int b = 0; b < n; b++) {
                        if (vers[i][strlen(vers[i]) - 1] == sinonime[b][strlen(sinonime[b]) - 1] ||
                            vers[i][strlen(vers[i]) - 1] == sinonime[b][strlen(sinonime[b]) - 1] - 32) {
                            if (strcmp(sin, sinonime[b]) > 0) {
                                strcpy(sin, sinonime[b]);
                            }
                        }
                    }
                    if (strcmp(sin, "zz") != 0) {
                        strcpy(vers[i + 1], sin);
                    }
                }
            }
        }
    } else if (strcmp(rima, "incrucisata") == 0) {
        for (i = 0; i < x - 2;) {
            if (vers[i][strlen(vers[i]) - 1] != vers[i + 2][strlen(vers[i + 2]) - 1] &&
                vers[i][strlen(vers[i]) - 1] != vers[i + 2][strlen(vers[i + 2]) - 1] - 32 &&
                vers[i][strlen(vers[i]) - 1] != vers[i + 2][strlen(vers[i + 2]) - 1] + 32) {
                char** sinonime;
                int n;
                get_synonym(vers[i], &n, &sinonime);
                char sin[50] = "zz";
                for (int b = 0; b < n; b++) {
                    if (vers[i + 2][strlen(vers[i + 2]) - 1] == sinonime[b][strlen(sinonime[b]) - 1] ||
                        vers[i + 2][strlen(vers[i + 2]) - 1] == sinonime[b][strlen(sinonime[b]) - 1] - 32) {
                        if (strcmp(sin, sinonime[b]) > 0) {
                            strcpy(sin, sinonime[b]);
                        }
                    }
                }
                if (strcmp(sin, "zz") != 0) {
                    strcpy(vers[i], sin);
                } else {
                    get_synonym(vers[i + 2], &n, &sinonime);
                    for (int b = 0; b < n; b++) {
                        if (vers[i][strlen(vers[i]) - 1] == sinonime[b][strlen(sinonime[b]) - 1] ||
                            vers[i][strlen(vers[i]) - 1] == sinonime[b][strlen(sinonime[b]) - 1] - 32) {
                            if (strcmp(sin, sinonime[b]) > 0) {
                                strcpy(sin, sinonime[b]);
                            }
                        }
                    }
                    if (strcmp(sin, "zz") != 0) {
                        strcpy(vers[i + 2], sin);
                    }
                }
            }
            if ((i + 1) % 4 == 2) {
                i += 3;
            } else {
                i++;
            }
        }
    } else if (strcmp(rima, "imbratisata") == 0) {
        for (i = 0; i < x - 2;) {
            int pas;
            if (i % 4 == 0) {
                pas = 3;
            } else {
                pas = 1;
            }
            if (vers[i][strlen(vers[i]) - 1] != vers[i + pas][strlen(vers[i + pas]) - 1] &&
                vers[i][strlen(vers[i]) - 1] != vers[i + pas][strlen(vers[i + pas]) - 1] - 32 &&
                vers[i][strlen(vers[i]) - 1] != vers[i + pas][strlen(vers[i + pas]) - 1] + 32) {
                char** sinonime;
                int n;
                get_synonym(vers[i], &n, &sinonime);
                char sin[50] = "zz";
                for (int b = 0; b < n; b++) {
                    if (vers[i + pas][strlen(vers[i + pas]) - 1] == sinonime[b][strlen(sinonime[b]) - 1] ||
                        vers[i + pas][strlen(vers[i + pas]) - 1] == sinonime[b][strlen(sinonime[b]) - 1] - 32) {
                        if (strcmp(sin, sinonime[b]) > 0) {
                            strcpy(sin, sinonime[b]);
                        }
                    }
                }
                if (strcmp(sin, "zz") != 0) {
                    strcpy(vers[i], sin);
                } else {
                    get_synonym(vers[i + pas], &n, &sinonime);
                    for (int b = 0; b < n; b++) {
                        if (vers[i][strlen(vers[i]) - 1] == sinonime[b][strlen(sinonime[b]) - 1] ||
                            vers[i][strlen(vers[i]) - 1] == sinonime[b][strlen(sinonime[b]) - 1] - 32) {
                            if (strcmp(sin, sinonime[b]) > 0) {
                                strcpy(sin, sinonime[b]);
                            }
                        }
                    }
                    if (strcmp(sin, "zz") != 0) {
                        strcpy(vers[i + pas], sin);
                    }
                }
            }
            if ((i + 1) % 4 == 2) {
                i += 3;
            } else {
                i++;
            }
        }
    }
    int pos = 0;
    int nr = 0;
    int nrvers = 0;
    for (i = 0; i < strlen(poem); i++) {
        if (poem[i] == ' ') {
            pos = i;
            nr = 0;
        } else if ((poem[i] >= 'a' && poem[i] <= 'z') || (poem[i] >= 'A' && poem[i] <= 'Z') || poem[i] == '-') {
            nr++;
        } else if (poem[i] == '\n' && pos != -1) {
            char aux1[MAX];
            strcpy(aux1, poem + pos + nr + 1);
            strcpy(poem + pos + 1, vers[nrvers]);
            strcpy(poem + strlen(poem), aux1);
            nrvers++;
            i += strlen(vers[nrvers - 1]) - nr;
            nr = 0;
            pos = -1;
        }
    }
    strcpy(str, poem);
}

void friendly(char* str) {
    char aux[MAX];
    aux[0] = '\0';
    char cuv[200];
    int j = 0;
    char* s;
    for (int i = 0; str[i] != '\0'; i++) {
        if ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z')) {
            cuv[j] = str[i];
            j++;
        } else {
            cuv[j] = '\0';
            get_friendly_word(cuv, &s);
            if (s == NULL) {
                strcat(aux, cuv);
            } else {
                strcat(aux, s);
            }
            j = 0;
            strcpy(cuv, "");
            aux[strlen(aux) + 1] = '\0';
            aux[strlen(aux)] = str[i];
        }
    }
    cuv[j] = '\0';
    get_friendly_word(cuv, &s);
    if (s == NULL) {
        strcat(aux, cuv);
    } else {
        strcat(aux, s);
    }
    strcpy(str, aux);
}

void print(char* text) {
    printf("%s\n\n", text);
}

int main(void) {
    srand(42);
    char text[MAX];
    char cuv1[MAX], cuv2[MAX];
    while (1) {
        scanf("%s", cuv1);
        char* tok = strtok(cuv1, " ");
        strcpy(cuv1, tok);
        tok = strtok(NULL, " ");
        if (tok != NULL) {
            strcpy(cuv2, tok);
        }
        if (strcmp(cuv1, "load") == 0) {
            scanf("%s", cuv2);
            load_file(cuv2, text);
        }
        if (strcmp(cuv1, "uppercase") == 0) {
            uppercase(text);
        }
        if (strcmp(cuv1, "make_it_friendlier") == 0) {
            friendly(text);
        }
        if (strcmp(cuv1, "trimming") == 0) {
            trimming(text);
        }
        if (strcmp(cuv1, "print") == 0) {
            print(text);
        }
        if (strcmp(cuv1, "make_it_silly") == 0) {
            scanf("%s", cuv2);
            silly(text, cuv2);
        }
        if (strcmp(cuv1, "make_it_rhyme") == 0) {
            scanf("%s", cuv2);
            rhimy(text, cuv2);
        }
        if (strcmp(cuv1, "quit") == 0) {
            return 0;
        }
    }
}
