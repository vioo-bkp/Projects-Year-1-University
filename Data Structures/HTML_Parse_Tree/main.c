// Mateescu Viorel-Cristian
// Grupa: 332CB

#include "lib.h"
#include "structures.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
  TParseState currentState = PARSE_CONTENTS;
  TArb Root = NULL, aux = NULL, currentNode = NULL;
  ACell NodeList = NULL;

  unsigned int i;
  int res = 0, count, k;
  char c, *At = NULL, *AtVal = NULL, *AuxString = NULL, *cmd = NULL,
          *ptr = NULL;

  if (argc != NoArguments) {
    return 1;
  }

  /* Se deschide fisierul html + verificare. */

  FILE *html = fopen(argv[1], "rt");
  if (!html) {
    return 1;
  }

  /* Se citeste fisierul html caracter cu caracter si se interpreteaza acesta 
    pentru a construi arborele. */ 

  while ((c = fgetc(html)) != EOF) {
    TParseState futureState =
        Interpret(currentState, c, &At, &AtVal, currentNode);

    if (futureState == PARSE_ERROR) {
      fclose(html);
      return 1;
    }

    res = CreateNode(currentState, futureState, c, &AuxString, &currentNode,
                     &aux, &Root, &NodeList);

    if (res == 1) {
      if (AuxString) {
        free(AuxString);
      }
      if (currentNode) {
        free(currentNode);
      }
      if (aux) {
        free(aux);
      }
      DistrLG(&NodeList);
      Elim(Root);
      fclose(html);
      return 1;
    }

    currentState = futureState;
  }

  fclose(html);

  cmd = calloc(MaxLength, sizeof(char));

  if (!cmd) {
    return 1;
  }

  /* Se deschide fisierul de comenzi si cel de iesire + verificare. */

  FILE *in_cmd = fopen(argv[2], "rt");
  if (!in_cmd) {
    free(cmd);
    return 1;
  }

  FILE *out = fopen(argv[3], "wt");
  if (!in_cmd) {
    fclose(in_cmd);
    free(cmd);
    return 1;
  }

  /* Se citeste numarul de comenzi. */

  fgets(cmd, MaxLength, in_cmd);
  cmd[strlen(cmd) - 1] = '\0';
  sscanf(cmd, "%d", &count);

  /* Se citesc comenzile din fisier si se executa acestea. */

  for (k = 0; k < count; k++) {
    fgets(cmd, MaxLength, in_cmd);
    cmd[strlen(cmd) - 1] = '\0';

    ptr = strtok(cmd, " ");
    if (!ptr) {
      break;
    }

    /* Se adauga un nou nod in arbore. */

    if (strcmp(ptr, "add") == 0) {
      for (i = 0 ; i < 2; i++){
      ptr = strtok(NULL, "= ");
      if (!ptr) {
        res = 1;
        break;
      }
    }

      currentNode = GetNodeByID(Root, ptr);
      if (currentNode) {
        for (i = 0; i < 2; i++) {
          ptr = strtok(NULL, "\"");
          if (!ptr) {
            res = 1;
            break;
          }
        }

        if(res == 1){
          break;
        }

        currentState = PARSE_CONTENTS;

        /* Se interpreteaza fiecare caracter pentru a creea si adauga un nou 
          nod in arbore. */
        
        for (i = 0; i < strlen(ptr); i++) {
          c = ptr[i];

          TParseState futureState =
              Interpret(currentState, c, &At, &AtVal, currentNode);
          if (futureState == PARSE_ERROR) {
            res = 1;
            break;
          }

          res = CreateNode(currentState, futureState, c, &AuxString,
                           &currentNode, &aux, &Root, &NodeList);
          currentState = futureState;

          if (res == 1) {
            if (AuxString) {
              free(AuxString);
            }
            if (currentNode) {
              free(currentNode);
            }
            if (aux) {
              free(aux);
            }
            break;
          }
        }
      } else {
        fprintf(out, "Add tag failed: node with id %s not found!\n", ptr);
      }
    } else if (strcmp(ptr, "format") == 0) {
      /* Se afiseaza arborele. */
      Print(Root, 0, out);
    } else {

      /* Operatii pe arbore */

      int appendSearch = strcmp(ptr, "appendStyle");
      int overrideSearch = strcmp(ptr, "overrideStyle");
      int deleteSearch = strcmp(ptr, "deleteRecursively");

      if (overrideSearch == 0 || appendSearch == 0 || deleteSearch == 0) {
        ACell auxList = NULL;

        for (i = 0; i < 2; i++) {
          ptr = strtok(NULL, "\"");
          if (!ptr) {
            res = 1;
            break;
          }
        }
        if(res == 1){
          break;
        }

        if (ptr[0] == '#') {
          TArb new = GetNodeByID(Root, ptr + 1);
          
          if (new) {
            InsLG(&auxList, new);
          
            if (deleteSearch == 0) {
              DelNodesByID(Root, NULL, ptr + 1);
            }
          
          }
        } else if (ptr[0] == '.') {
          GetNodesByClass(Root, &auxList, ptr + 1);
          
          if (auxList && deleteSearch == 0) {
            DelNodesByClass(Root, NULL, ptr + 1);
          }
        } else if (strchr(ptr, '.')) {
          char *point = strchr(ptr, '.');
          char *class = strdup(point + 1);
          if(!class){
            res = 1;
            break;
          }

          char *name = calloc(MaxLength, sizeof(char));
          if(!name){
            free(class);
            res = 1;
            break;
          }

          int j = 0;
          while (ptr[j] != '.' && ptr[j] != '\0') {
            strncat(name, &(ptr[j]), 1);
            j++;
          }
          name[strlen(name)] = '\0';
          
          GetNodesByTagAndClass(Root, &auxList, name, class);
          if (auxList && deleteSearch == 0) {
            DelNodesByTagAndClass(Root, NULL, name, class);
          }
          
          free(class);
          free(name);
        } else if (strchr(ptr, '>')) {
          char *point = strchr(ptr, '>');
          char *tag = strdup(point + 1);
          if(!tag){
            res = 1;
            break;
          }

          char *name = calloc(MaxLength, sizeof(char));
          if(!name){
            free(tag);
            res = 1;
            break;
          }

          int j = 0;
          while (ptr[j] != '>' &&  ptr[j] != '\0') {
            strncat(name, &(ptr[j]), 1);
            j++;
          }
          name[strlen(name)] = '\0';
          
          GetNodesByTagAndParent(Root, NULL, &auxList, tag, name);
          if (auxList && deleteSearch == 0) {
            DelNodesByTagAndParent(Root, NULL, tag, name);
          }
          
          free(name);
          free(tag);
        } else if (strchr(ptr, ' ')) {
          char *point = strchr(ptr, ' ');
          char *tag = strdup(point + 1);
          if(!tag){
            res = 1;
            break;
          }

          char *name = calloc(MaxLength, sizeof(char));
          if(!name){
            free(tag);
            res = 1;
            break;
          }
          
          int j = 0;
          while (ptr[j] != ' ' && ptr[j] != '\0') {
            strncat(name, &(ptr[j]), 1);
            j++;
          }
          name[strlen(name)] = '\0';
          
          GetNodesByTagAndRelative(Root, NULL, &auxList, tag, name);
          if (auxList && deleteSearch == 0) {
            DelNodesByTagAndRelative(Root, NULL, NULL, tag, name);
          }
          
          free(name);
          free(tag);
        } else {
          GetNodesByTag(Root, &auxList, ptr);
          
          if (auxList && deleteSearch == 0) {
            DelNodesBytag(Root, NULL, ptr);
          }
        }

        if (auxList) {
          if (deleteSearch == 0) {
            DistrLG(&auxList);
          } else {
            for (i = 0; i < 2; i++) {
              ptr = strtok(NULL, "\"");
              if (!ptr) {
                res = 1;
                break;
              }
            }

            Trim(ptr);
            RemoveSpaces(ptr);

            if (appendSearch == 0) {
              res = AppendStyle(auxList, ptr);
            } else {
              res = OverrideStyle(auxList, ptr);
            }
            
            DistrLG(&auxList);
            if(res == 1){
              break;
            }
          }
        } else {
          if (appendSearch == 0) {
            fprintf(out,
                    "Append to style failed: no node found for selector %s!\n",
                    ptr);
          } else if (overrideSearch == 0) {
            fprintf(out,
                    "Override style failed: no node found for selector %s!\n",
                    ptr);
          } else if (deleteSearch == 0) {
            fprintf(
                out,
                "Delete recursively failed: no node found for selector %s!\n",
                ptr);
          }
        }
      }
    }
  }

  free(cmd);
  fclose(in_cmd);
  fclose(out);
  Elim(Root);
  DistrLG(&NodeList);
  return res;
}