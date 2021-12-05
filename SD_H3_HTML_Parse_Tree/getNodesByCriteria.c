// Mateescu Viorel-Cristian

#include "lib.h"
#include "structures.h"

/* Functie pentru gasirea unui nod pe baza id-ului. 
   
   In cazul in care exista un nod cu id-ul respectiv se va returna adresa 
  acestuia, altfel se returneaza NULL.

   Functia este construita astfel incat sa fie parcursa doar partea din arbore
  care este posibil sa contina nodul cu id-ul cautat. */ 

TArb GetNodeByID(TArb root, char *ID) {
  TArb aux = NULL;
  if (root == NULL) {
    return NULL;
  }

  while (root) {
    if (root->info->id) {
      if (strcmp(root->info->id, ID) == 0) {
        return root;
      }

      unsigned int idLength = strlen(root->info->id);

      if (idLength <= strlen(ID) &&
          strncmp(root->info->id, ID, idLength) == 0) {
        aux = GetNodeByID(root->firstChild, ID);
      }

      if (aux) {
        return aux;
      }
    } else {
      return GetNodeByID(root->firstChild, ID);
    }

    root = root->nextSibling;
  }
  return NULL;
}

/* Functie pentru gasirea unui nod pe baza numelui. 

   Se cauta in arbore nodurile care au un anumit nume.
   
   In cazul in care exista un nod cu numele respectiv acesta va fi inserat
  intr-o lista de noduri. */ 

void GetNodesByTag(TArb root, ACell *List, char *tag) {
  while (root) {
    if (strcmp(root->info->type, tag) == 0) {
      InsLG(List, root);
    }
    
    GetNodesByTag(root->firstChild, List, tag);
    root = root->nextSibling;
  }
}

/* Functie pentru gasirea unui nod pe baza atributului "class" si a unei valori
  precizata pentru acesta.

   Se cauta in arbore nodurile in a caror lista de atribute exista atributul 
  "class" cu o anumita valoare precizata.
   
   In cazul in care exista un nod care respecta criteriile de mai sus acesta va
  fi inserat intr-o lista de noduri. */ 

void GetNodesByClass(TArb root, ACell *List, char *class) {
  while (root) {
    TAttr p = root->info->otherAttributes;
    for(;p != NULL; p = p->next){
      if (strcmp(p->name, "class") == 0 && strcmp(p->value, class) == 0) {
        InsLG(List, root);
        break;
      }
    }
    
    GetNodesByClass(root->firstChild, List, class);
    root = root->nextSibling;
  }
}

/* Functie pentru gasirea unui nod pe baza numelui si a atributului "class"

   Se cauta in arbore nodurile care au un anumit nume si in lista lor de
  atribute exista atributul "class" cu o anumita valoare precizata.
   
   In cazul in care exista un nod care respecta criteriile de mai sus acesta va
  fi inserat intr-o lista de noduri. */ 

void GetNodesByTagAndClass(TArb root, ACell *List, char *tag, char *class) {
  while (root) {
    if (strcmp(root->info->type, tag) == 0) {
      TAttr p = root->info->otherAttributes;
      for(;p != NULL; p = p->next) {
        if (strcmp(p->name, "class") == 0 && strcmp(p->value, class) == 0) {
          InsLG(List, root);
          break;
        }
      }
    }
    GetNodesByTagAndClass(root->firstChild, List, tag, class);
    root = root->nextSibling;
  }
}

/* Functie pentru gasirea unui nod pe baza numelui acestuia si a numelui
  parintelui sau.
   
   Se cauta in arbore nodurile care au un anumit nume si au ca parinte un nod
  cu un anumit nume precizat.

   In cazul in care exista un nod care respecta criteriile de mai sus acesta va
  fi inserat intr-o lista de noduri. */ 

void GetNodesByTagAndParent(TArb root, TArb parent, ACell *List, char *tag,
                            char *parent_name) {
  while (root) {
    if (strcmp(root->info->type, tag) == 0 && parent) {
      if (strcmp(parent->info->type, parent_name) == 0) {
        InsLG(List, root);
      }
    }
    GetNodesByTagAndParent(root->firstChild, root, List, tag, parent_name);
    root = root->nextSibling;
  }
}

/* Functie pentru gasirea unui nod pe baza numelui acestuia si a numelui
  unui stramos de-al sau.
   
   Se cauta in arbore nodurile care au un anumit nume si au un stramos  cu un
  anumit nume.

   In cazul in care exista un nod care respecta criteriile de mai sus acesta va
  fi inserat intr-o lista de noduri. */ 

void GetNodesByTagAndRelative(TArb root, TArb relative, ACell *List, char *tag,
                              char *relative_name) {
  while (root) {
    if (strcmp(root->info->type, relative_name) == 0) {
      relative = root;
    }

    if (strcmp(root->info->type, tag) == 0 && relative != NULL) {
      InsLG(List, root);
    }

    GetNodesByTagAndRelative(root->firstChild, relative, List, tag,
                             relative_name);

    if (strcmp(root->info->type, relative_name) == 0) {
      relative = NULL;
    }
    root = root->nextSibling;
  }
}