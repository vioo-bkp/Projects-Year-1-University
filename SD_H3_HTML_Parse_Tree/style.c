// Mateescu Viorel-Cristian

#include "lib.h"
#include "structures.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Functie pentru eliminarea "leading, respectiv trailing spaces"("\t", "\n",
  " ") dintr-un sir de caractere. */

void Trim(char *s) {
  char *p = s;
  int length = strlen(p);

  while (isspace(p[length - 1])) {
    length--;
    p[length] = 0;
  }
  while (*p && isspace(*p)) {
    p++;
    length--;
  }

  memmove(s, p, length + 1);
}

/* Functie pentru eliminarea spatiilor extra dintr-un sir de caractere.
   De exemplu: "tema3    la     sd" -> "tema3 la sd" */

void StripExtraSpaces(char *s) {
  int i, count = 0;
  for (i = 0; s[i] != '\0'; i++) {
    if (!isspace(s[i]) || (i > 0 && !isspace(s[i - 1]))) {
      s[count] = s[i];
      count++;
    }
  }
  s[count] = '\0';
}

/* Functie pentru eliminarea tuturor spatiilor dintr-un sir de caractere.
   De exemplu: "tema3    la     sd" -> "tema3lasd" */

void RemoveSpaces(char *s) {
  int count = 0, i;
  for (i = 0; s[i] != '\0'; i++)
    if (!isspace(s[i])) {
      s[count] = s[i];
      count++;
    }
  s[count] = '\0';
}

/* Functie pentru creearea unui element de tip atribut. 
   Se aloca memorie pentru acesta si se verifica alocarea.
   Se returneaza adresa atributului sau NULL. */

TAttr CreateAttribute(char *name, char *value) {
  TAttr Attr = (TAttr)calloc(1, sizeof(TNodAttr));
  if (!Attr) {
    free(name);
    return NULL;
  }

  Attr->name = strdup(name);
  if (!Attr->name) {
    free(Attr);
    free(name);
    return NULL;
  }

  Attr->value = strdup(value);
  if (!Attr->value) {
    free(Attr->name);
    free(Attr);
    free(name);
    return NULL;
  }
  return Attr;
}

/* Functie pentru inserarea unui atribut in cadrul unei liste simplu inlantuite
  de atribute. */

void InsertAttribute(TAttr ant, TAttr Attr, ACell p) {
  if (ant == NULL) {
    TInfo ptr = ((TArb)(p->info))->info;
    ptr->style = Attr;
  } else {
    ant->next = Attr;
  }
}

/* Functie pentru operatia de "appendStyle" asupra unui arbore. 
   
   Aceasta se aplica asupra nodurilor care au respectat selectorul precizat in
  comanda(au fost stocate intr-o lista de noduri).
   
   In cazul in care un atribut ce se doreste a fi adaugat in cadrul unui nod
  deja exista in lista de atribute de stil a acestuia se actualizeaza valoarea
  atributului respectiv, altfel se creeaza un nou atribut si se insereaza 
  acesta in lista de stiluri a nodului respectiv. */

int AppendStyle(ACell List, char *AtVal) {
  char delim[] = ":;", *q, *name;
  q = strtok(AtVal, delim);
  if (!q) {
    return 1;
  }

  while (q) {
    ACell p = List;
    name = strdup(q);
    if (!name) {
      return 1;
    }

    q = strtok(NULL, delim);
    if (!q) {
      free(name);
      return 1;
    }

    for(p = List; p!= NULL; p = p->urm) {
      TAttr style = ((TArb)(p->info))->info->style, ant;
      int done = 0;

      for(ant = NULL; style != NULL; ant = style, style = style->next) {
        if (strcmp(style->name, name) == 0) {

           free(style->value);
           style->value = strdup(q);
           if (!style->value) {
             free(name);
             return 1;
           }
          done = 1;
          break;
        }
      }

      if (done == 0) {
        TAttr Attr = CreateAttribute(name, q);
        if (!Attr) {
          return 1;
        }
        InsertAttribute(ant, Attr, p);
      }
    }

    free(name);
    q = strtok(NULL, delim);
  }
  return 0;
}

/* Functie care goleste lista de stiluri a unui nod din arbore si elimina. 
  memoria ocupata de aceasta. */

void DelStyleFromList(ACell List) {
  ACell p = List;

  for(p = List; p != NULL; p = p->urm) {
    TArb ptr = (TArb)(p->info);
    
    if (ptr->info->style) {
      TAttr style = ptr->info->style;
      
      while (style) {
        TAttr aux_style = style;
        style = style->next;
        
        free(aux_style->name);
        free(aux_style->value);
        free(aux_style);
      }
      
      ptr->info->style = NULL;
    }
  }
}

/* Functie pentru operatia de "overrideStyle" asupra unui arbore.
   
   Aceasta se aplica asupra nodurilor care au respectat selectorul precizat in
  comanda(au fost stocate intr-o lista de noduri).
  
   Se goleste lista de atribute de stil a nodurilor selectate si se insereaza 
  in aceasta noile atribute de stil precizate. */

int OverrideStyle(ACell List, char *AtVal) {
  char delim[] = ":;", *q, *name;
  q = strtok(AtVal, delim);
  if(!q){
    return 1;
  }

  DelStyleFromList(List);

  while (q) {
    ACell p;
    name = strdup(q);
    if(!name){
      return 1;
    }
    
    q = strtok(NULL, delim);
    if(!q){
      free(name);
      return 1;
    }

    for(p = List; p != NULL; p = p->urm) {
      TAttr style = ((TArb)(p->info))->info->style, ant = NULL;
      for(ant = NULL; style != NULL; ant = style, style = style->next);

      TAttr Attr = CreateAttribute(name, q);
      if (!Attr) {
         return 1;
      }
      InsertAttribute(ant, Attr, p);
    }

    free(name);
    q = strtok(NULL, delim);
  }
  return 0;
}

/* Functie care afiseaza "\t" de un anumit numar de ori. */

void PrintTab(int count, FILE *out){
  int i;
  for (i = 0; i < count; i++) {
      fprintf(out, "\t");
  }
}

/* Functie pentru afisarea "pe niveluri" a arborelui. 

   Se afiseaza arborele conform continutului nodurilor acestuia. */

void Print(TArb root, int level, FILE *out) {
  while (root) {
    PrintTab(level, out);
    fprintf(out, "<%s", root->info->type);
    
    if (root->info->style) {
      TAttr style = root->info->style;
      fprintf(out, " style=\"");
      
      while (style) {
        fprintf(out, "%s: %s;", style->name, style->value);
        
        style = style->next;
        if (style) {
          fprintf(out, " ");
        }
      }
      fprintf(out, "\"");
    }

    if (root->info->otherAttributes) {
      TAttr attribute = root->info->otherAttributes;
      for (;attribute != NULL; attribute = attribute->next) {
        fprintf(out, " %s=\"%s\"", attribute->name, attribute->value);
      }
    }

    if (root->info->isSelfClosing) {
      fprintf(out, "/>\n");
    } else {
      fprintf(out, ">\n");
    
      if (root->info->contents) {
        PrintTab(level + 1, out);
        fprintf(out, "%s", root->info->contents);
        fprintf(out, "\n");
      }
    }
    
    Print(root->firstChild, level + 1, out);
    
    if (root->info->isSelfClosing == 0) {
      PrintTab(level , out);
      fprintf(out, "</%s>\n", root->info->type);
    }
    root = root->nextSibling;
  }
}

/* Functii care genereaza id-uri noi pentru nodurile din arbore dupa operatia
  de stergere a unor noduri din acesta.

   Se reconstruiesc id-urile doar pentru nodurile ce "au avut de suferit" dupa 
  operatia de stergere recursiva un stramos de-al lor si-a pierdut un frate :( 
*/

void GetnewID(TArb root, char *ID){
  if(root == NULL){
    return;
  }

  int count = 1;
  char point = '.', *aux;

  while(root){
    strcpy(root->info->id, ID);
    strncat(root->info->id, &point, 1);
    aux = strrchr(root->info->id, point);
    sprintf(aux + 1, "%d", count);
    count++;
    
    GetnewID(root->firstChild, root->info->id);
    root = root->nextSibling;
  }

}

void AdaptID(TArb parent, TArb root) {
  if (parent) {
    TArb p = parent->firstChild, ant, ptr;
    for (ant = NULL; p != root; ant = p, p = p->nextSibling);

    if (ant == NULL) {
      parent->firstChild = root->nextSibling;
      ptr = parent->firstChild;
    } else {
      ant->nextSibling = p->nextSibling;
      ptr = ant->nextSibling;
    }

    for (; ptr != NULL; ptr = ptr->nextSibling) {
      char *aux = strrchr(ptr->info->id, '.');
      int value;
      sscanf(aux + 1, "%d", &value);
      value--;
      sprintf(aux + 1, "%d", value);
      GetnewID(ptr->firstChild, ptr->info->id);
    }
  }
}