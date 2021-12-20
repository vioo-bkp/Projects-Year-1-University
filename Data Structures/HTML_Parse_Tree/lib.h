#include "structures.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NoArguments 4
#define MaxLength 1000

typedef struct TNodAttr {
  char *name;
  char *value;
  struct TNodAttr *next;
} TNodAttr, *TAttr;

typedef struct TNodInfo {
  char *type;
  char *id;
  TAttr style;
  TAttr otherAttributes;
  int isSelfClosing;
  char *contents;
} TNodInfo, *TInfo;

typedef struct TNodArb {
  TInfo info;
  struct TNodArb *nextSibling;
  struct TNodArb *firstChild;
} TNodArb, *TArb;

typedef enum {
  PARSE_ERROR = 0,
  PARSE_CONTENTS = 1,
  PARSE_OPENING_BRACKET = 2,
  PARSE_TAG_TYPE = 3,
  PARSE_CLOSING_TAG = 4,
  PARSE_REST_OF_TAG = 5,
  PARSE_ATTRIBUTE_NAME = 6,
  PARSE_ATTRIBUTE_EQ = 7,
  PARSE_ATTRIBUTE_VALUE = 8,
  PARSE_SELF_CLOSING = 9,
} TParseState;

/* interpret.c */

TParseState Interpret(TParseState currentState, char c, char **At, char **AtVal,
                      TArb currentNode);

/* lib.c */

TArb NewNode();
int AddChild(TArb node, TArb new);
TArb GetCurrentNode(ACell *List);
int CreateNode(TParseState currentState, TParseState futureState, char c,
               char **AuxString, TArb *currentNode, TArb *aux, TArb *Root,
               ACell *List);
void DelNodeContent(TArb root);
void FreeElem(TArb root);
void Elim(TArb root);

/* style.c */

void Trim(char *s);
void Print(TArb root, int level, FILE *out);
void StripExtraSpaces(char *str);
void RemoveSpaces(char *str);
TAttr CreateAttribute(char *name, char *value);
void InsertAttribute(TAttr ant, TAttr Attr, ACell p);
int AppendStyle(ACell List, char *AtVal);
void DelStyleFromList(ACell List);
int OverrideStyle(ACell List, char *AtVal);
void PrintTab(int count, FILE *out);
void Print(TArb root, int level, FILE *out);
void GetnewID(TArb root, char *ID);
void AdaptID(TArb parent, TArb root);

/* getNodesByCriteria.c */

TArb GetNodeByID(TArb root, char *ID);
void GetNodesByTag(TArb root, ACell *List, char *tag);
void GetNodesByClass(TArb root, ACell *List, char *class);
void GetNodesByTagAndClass(TArb root, ACell *List, char *tag, char *class);
void GetNodesByTagAndParent(TArb root, TArb parent, ACell *List, char *tag,
                            char *name);
void GetNodesByTagAndRelative(TArb root, TArb relative, ACell *List, char *tag,
                              char *relative_name);

/* delNodesByCriteria.c */

void DelNodesByID(TArb root, TArb parent, char *ID);
void DelNodesBytag(TArb root, TArb parent, char *tag);
void DelNodesByTagAndRelative(TArb root, TArb relative, TArb parent, char *tag,
                              char *relative_name);
void DelNodesByTagAndParent(TArb root, TArb parent, char *tag, char *parent_name);
void DelNodesByClass(TArb root, TArb parent, char *class);
void DelNodesByTagAndClass(TArb root, TArb parent, char *tag, char *class);
