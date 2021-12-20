// Mateescu Viorel-Cristian

#include "lib.h"
#include "structures.h"

/* Functie pentru creearea unui nod.
   
   Se aloca memorie pentru nod si pentru campul info al acestuia.
   
   Se verifica alocarea si se returneaza adresa nodului(sau NULL). */  

TArb NewNode() {
  TArb aux = (TArb)calloc(1, sizeof(TNodArb));
  if (!aux)
    return NULL;
  aux->info = (TInfo)calloc(1, sizeof(TNodInfo));
  if (!aux->info) {
    free(aux);
    return NULL;
  }
  aux->nextSibling = NULL;
  aux->firstChild = NULL;

  return aux;
}

/* Functie pentru adaugarea unui nod in arbore si generarea id-ului acestuia 
  pe baza id-ului parintelui sau. */

int AddChild(TArb node, TArb new) {
  int count = 1;
  char *ID , *c, point = '.';
  
  ID = calloc(MaxLength, sizeof(char));
  if(!ID){
    return 1;
  }

  c = calloc(MaxLength, sizeof(char));
  if(!c){
    free(ID);
    return 1;
  }

  if (node->info->id == NULL) {
    if (node->firstChild == NULL) {
      ID[0] = '1';
    } else {
      ID[0] = '2';
    }
  } else {
    strcpy(ID, node->info->id);
  }
  
  if (node->firstChild != NULL) {
    count++;
    
    TArb auxNode = node->firstChild;
    for (; auxNode->nextSibling != NULL; auxNode = auxNode->nextSibling) {
      count++;
    }
    
    auxNode->nextSibling = new;
  } else {
    node->firstChild = new;
  }
  
  if (node->info->id != NULL) {
    sprintf(c, "%d", count);
    strncat(ID, &point, 1);
    strcat(ID, c);
  }

  new->info->id = ID;
  free(c);
  
  return 0;
}

/* Functie care returneaza(si elimina din lista) ultimul element(nodul curent). */

TArb GetCurrentNode(ACell *NodeList) {
  ACell ptr = *NodeList, antptr = NULL;
  
  if (ptr) {
    for(; ptr->urm != NULL; antptr = ptr, ptr = ptr->urm);

    if (antptr != NULL) {
      free(ptr);
      antptr->urm = NULL;
      
      return (TArb)(antptr->info);
    } else {
      return (TArb)(ptr->info);
    }
  }

  return NULL;
}

/* Functie pentru creearea unui nou nod, cat si pentru completarea campurilor 
  specifice acestuia(type, isSelfClosing, contents, style, otherAttributes) pe 
  baza automatului de stari din eneuntul temei. */

int CreateNode(TParseState currentState, TParseState futureState, char c,
                char **AuxString, TArb *currentNode, TArb *aux, TArb *Root,
                ACell *List) {
  int res = 0;

  if (currentState == PARSE_OPENING_BRACKET && futureState == PARSE_TAG_TYPE) {
    *aux = NewNode();
    if(!(*aux)){
      return 1;
    }
    
    *AuxString = calloc(MaxLength, sizeof(char));
    if(!(*AuxString)){
      return 1;
    }
    
    strncat(*AuxString, &c, 1);

    if (*Root == NULL) {
      *Root = *aux;
      *currentNode = *aux;
    }
  } else if (currentState == PARSE_TAG_TYPE && futureState == PARSE_TAG_TYPE) {
    strncat(*AuxString, &c, 1);
  } else if (currentState == PARSE_TAG_TYPE &&
             (futureState == PARSE_REST_OF_TAG ||
              futureState == PARSE_CONTENTS)) {

    (*aux)->info->type = *AuxString;
    
    res = InsLG(List, *aux);
    if(res == 1){
      return 1;
    }
    
    if (*Root != *aux) {
      res = AddChild(*currentNode, *aux);
      if(res == 1){
      return 1;
      }
      
      *currentNode = *aux;
    }
  } else if ((currentState == PARSE_OPENING_BRACKET &&
              futureState == PARSE_CLOSING_TAG) ||
             (futureState == PARSE_SELF_CLOSING &&
              currentState == PARSE_REST_OF_TAG)) {
    if (futureState == PARSE_SELF_CLOSING) {
      (*currentNode)->info->isSelfClosing = 1;
    }
    
    if ((*currentNode)->info->contents) {
      Trim((*currentNode)->info->contents);
      StripExtraSpaces((*currentNode)->info->contents);
    }
    
    *currentNode = GetCurrentNode(List);
    if(!(*currentNode)){
      return 1;
    }
  }
  return 0;
}

/* Functie pentru eliberarea memoriei ocupata de campurile specifice unui nod
  din arbore(style, otherAttributes, contents. */

void DelNodeContent(TArb root) {
  if (root->info->style) {
    TAttr style = root->info->style;
    
    while (style) {
      TAttr aux_style = style;
      style = style->next;
    
      free(aux_style->name);
      free(aux_style->value);
      free(aux_style);
    }
  }
  if (root->info->otherAttributes) {
    TAttr attribute = root->info->otherAttributes;
    
    while (attribute) {
      TAttr aux_attribute = attribute;
      attribute = attribute->next;
    
      free(aux_attribute->name);
      free(aux_attribute->value);
      free(aux_attribute);
    }
  }
  if (root->info->contents) {
    free(root->info->contents);
  }
}

/* Functii pentru distrugerea unui arbore, respectiv a unei parti din acesta.
   
   Nu am planificat sa aiba structura asta?("FreeElem" apeleaza "Elim", iar 
  "Elim" apeleaza "FreeElem").
   
   Dar isi fac bine treaba(0 memory leaks). */

void FreeElem(TArb root) {
  DelNodeContent(root);
  Elim(root->firstChild);
  
  free(root->info->type);
  free(root->info->id);
  free(root->info);
  free(root);
}

void Elim(TArb root) {
  TArb aux = NULL;
  
  if (root == NULL) {
    return;
  }
  
  while (root) {
    aux = root;
    root = root->nextSibling;
    FreeElem(aux);
  }
}




