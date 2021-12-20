// Mateescu Viorel-Cristian

#include "lib.h"
#include "structures.h"

/* Functie pentru stergerea recursiva a nodurilor pe baza id-ului. 
   
   Se sterge nodul cu id-ul precizat(in cazul in care acesta exista), 
  cat si urmasii acestuia.

   Se refac legaturile in arbore si se genereaza id-uri noi pentru nodurile
  afectate de operatia de stergere.

   In cazul in care nu se gaseste un nod cu id-ul respectiv se va afisa un
  mesaj de eroare din main. */ 

void DelNodesByID(TArb root, TArb parent, char *ID) {

  while (root) {
    if (root->info->id) {

      if (strcmp(root->info->id, ID) == 0) {
        AdaptID(parent, root);
        FreeElem(root);
        return;
      }

      unsigned int idLength = strlen(root->info->id);
      if (idLength <= strlen(ID) &&
          strncmp(root->info->id, ID, idLength) == 0) {
        DelNodesByID(root->firstChild, root, ID);
      }
    } else {
      DelNodesByID(root->firstChild, root, ID);
    }

    root = root->nextSibling;
  }
}

/* Functie pentru stergerea recursiva a nodurilor pe baza numelui acestora. 
   
   Se sterg nodurile cu numele precizat(in cazul in care exista), cat si urmasii
  acestora.

   Se refac legaturile in arbore si se genereaza id-uri noi pentru nodurile
  afectate de operatia de stergere.

   In cazul in care nu se gaseste niciun nod cu numele respectiv se va afisa un
  mesaj de eroare din main. */ 

void DelNodesBytag(TArb root, TArb parent, char *tag) {
  int check = 0;

  while (root) {
    check = 0;
    if (strcmp(root->info->type, tag) == 0) {
      AdaptID(parent, root);
      TArb aux = root;
      root = root->nextSibling;
      check = 1;
      FreeElem(aux);
    }
    if (check == 0) {
      DelNodesBytag(root->firstChild, root, tag);
      root = root->nextSibling;
    }
  }
}

/* Functie pentru stergerea recursiva a nodurilor pe baza numelui acestora si 
  care au un stramos cu un anumit nume. 
   
   Se sterg nodurile care respecta criteriile de mai sus(in cazul in care 
  exista), cat si urmasii acestora.

   Se refac legaturile in arbore si se genereaza id-uri noi pentru nodurile
  afectate de operatia de stergere.

   In cazul in care nu se gaseste niciun nod care sa respecte criteriile 
  precizate se va afisa un mesaj de eroare din main. */ 

void DelNodesByTagAndRelative(TArb root, TArb relative, TArb parent, char *tag,
                              char *relative_name) {

  int check = 0;

  while (root) {
    check = 0;
    if (strcmp(root->info->type, relative_name) == 0) {
      relative = root;
    }

    if (strcmp(root->info->type, tag) == 0 && relative != NULL) {
      AdaptID(parent, root);
      TArb aux = root;
      root = root->nextSibling;
      check = 1;
      FreeElem(aux);
    }
    if (check == 0) {
      DelNodesByTagAndRelative(root->firstChild, relative, root, tag,
                               relative_name);
      if (strcmp(root->info->type, relative_name) == 0) {
        relative = NULL;
      }

      root = root->nextSibling;
    }
  }
}

/* Functie pentru stergerea recursiva a nodurilor pe baza numelui acestora si
 care au un parinte cu un anumit nume. 
   
   Se sterg nodurile care respecta criteriile de mai sus in cazul(in care 
  exista), cat si urmasii acestora.

   Se refac legaturile in arbore si se genereaza id-uri noi pentru nodurile
  afectate de operatia de stergere.

   In cazul in care nu se gaseste niciun nod care sa respecte criteriile 
  precizate se va afisa un mesaj de eroare din main. */ 

void DelNodesByTagAndParent(TArb root, TArb parent, char *tag, char *parent_name) {
  int check = 0;

  while (root) {
    check = 0;
    if (strcmp(root->info->type, tag) == 0 && parent) {
      AdaptID(parent, root);

      TArb aux = root;
      root = root->nextSibling;
      check = 1;
      FreeElem(aux);
    }
    if (check == 0) {
      DelNodesByTagAndParent(root->firstChild, root, tag, parent_name);
      root = root->nextSibling;
    }
  }
}

/* Functie pentru stergerea recursiva a nodurilor pe baza atributului "class".
   
   Se sterg nodurile care au in lista de atribute un atribut cu numele "class"
  si o anumita valoare a acestuia (in cazul in care exista), cat si urmasii 
  acestora.

   Se refac legaturile in arbore si se genereaza id-uri noi pentru nodurile
  afectate de operatia de stergere.

   In cazul in care nu se gaseste niciun nod care sa aiba valoarea respectiva
  pentru atributul "class" se va afisa un mesaj de eroare din main. */ 

void DelNodesByClass(TArb root, TArb parent, char *class) {
  int check = 0;

  while (root) {
    TAttr ptr = root->info->otherAttributes;
    while (ptr) {
      if (strcmp(ptr->name, "class") == 0 && strcmp(ptr->value, class) == 0) {
        AdaptID(parent, root);
        TArb aux = root;
        root = root->nextSibling;
        check = 1;
        FreeElem(aux);
      }
      ptr = ptr->next;
    }

    if (check == 0) {
      DelNodesByClass(root->firstChild, root, class);
      root = root->nextSibling;
    }
  }
}

/* Functie pentru stergerea recursiva a nodurilor pe baza atributului "class" 
  si a numelui acestora.
   
   Se sterg nodurile care au un anumit nume si in lista de atribute a acestora 
   exista un atribut cu numele "class" cu o anumita valoare(in cazul in care 
   exista), cat si urmasii acestora.

   Se refac legaturile in arbore si se genereaza id-uri noi pentru nodurile
  afectate de operatia de stergere.

   In cazul in care nu se gaseste niciun nod care sa respecte criteriile de
   mai sus se va afisa un mesaj de eroare din main. */ 

void DelNodesByTagAndClass(TArb root, TArb parent, char *tag, char *class) {
  int check = 0;

  while (root) {
    if (strcmp(root->info->type, tag) == 0) {
      TAttr ptr = root->info->otherAttributes;
      while (ptr) {
        if (strcmp(ptr->name, "class") == 0 && strcmp(ptr->value, class) == 0) {
          AdaptID(parent, root);
          TArb aux = root;
          root = root->nextSibling;
          check = 1;
          FreeElem(aux);
        }
        ptr = ptr->next;
      }
    }
    if (check == 0) {
      DelNodesByTagAndClass(root->firstChild, root, tag, class);
      root = root->nextSibling;
    }
  }
}