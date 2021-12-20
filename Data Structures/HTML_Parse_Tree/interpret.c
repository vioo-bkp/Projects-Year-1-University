// Mateescu Viorel-Cristian

#include "lib.h"

/*
 *  Pentru a ușura citirea codului HTML din fișier, vi se pune la dispoziție
 *  următoarea funcție. Aceasta primeste un singur caracter (fișierul va fi
 *  citit caracter cu caracter în afara acestei funcții, iar ea va fi apelată
 *  de fiecare dată) și, în funcție de caracter, trece dintr-o stare în alta.
 *  Comentariile din cod arată o sugestie (neobligatorie) despre cum ar trebui
 *  completată funcția pentru a construi arborele. 
 * 
 *  Este, cu alte cuvinte, un automat de stări, unde starea inițială este PARSE_CONTENTS.
 */

TParseState Interpret(TParseState currentState, char c, char **At, char **AtVal, TArb currentNode)
{
    TParseState nextState = PARSE_ERROR;

    switch (currentState)
    {
    case PARSE_CONTENTS:
        if (c == '<')           {   nextState = PARSE_OPENING_BRACKET;
                                }
        else                    {   nextState = PARSE_CONTENTS;

                                    /* Se aloca memorie pentru campul contents
                                      al nodului curent. 
                                       
                                       Se concateaza caractere in campul 
                                      contents al nodului curent. */

                                    if(currentNode->info->contents){
                                        strncat(currentNode->info->contents, &c, 1);
                                    }
                                    else if(!isspace(c)){
                                        currentNode->info->contents = calloc(1000, sizeof(char));
                                        if(!currentNode->info->contents){
                                            return PARSE_ERROR;
                                        }
                                        strncpy(currentNode->info->contents, &c, 1);
                                    }
                                }
        break;
    case PARSE_OPENING_BRACKET:
        if (isspace(c))         {   nextState = PARSE_OPENING_BRACKET;  }
        else if (c == '>')      {   nextState = PARSE_ERROR;            }
        else if (c == '/')      {   nextState = PARSE_CLOSING_TAG;      }
        else                    {   nextState = PARSE_TAG_TYPE; }
        break;
    case PARSE_TAG_TYPE:
        if (isspace(c))         {   nextState = PARSE_REST_OF_TAG;      }
        else if (c == '>')      {   nextState = PARSE_CONTENTS;         }
        else                    {   nextState = PARSE_TAG_TYPE; }
        break;
    case PARSE_CLOSING_TAG:
        if (c == '>')           {   nextState = PARSE_CONTENTS; }
        else                    {   nextState = PARSE_CLOSING_TAG;      }
        break;
    case PARSE_REST_OF_TAG:
        if (isspace(c))         {   nextState = PARSE_REST_OF_TAG;      }
        else if (c == '>')      {   nextState = PARSE_CONTENTS;         }
        else if (c == '/')      {   nextState = PARSE_SELF_CLOSING;     }
        else                    {   nextState = PARSE_ATTRIBUTE_NAME;  

                                    /* Se aloca memorie pentru numele 
                                      atributelor nodului curent. */

                                    *At = calloc(MaxLength, sizeof(char));
                                    if(!(*At)){
                                        if(*AtVal){
                                            free(*AtVal);
                                        }
                                        return PARSE_ERROR;
                                    }
                                    strncpy(*At, &c, 1);
                                }
        break;
    case PARSE_ATTRIBUTE_NAME:
        if (c == '=')           {   nextState = PARSE_ATTRIBUTE_EQ;

                                    /* Se aloca memorie pentru valorile 
                                      atributelor nodului curent. */

                                    *AtVal = calloc(MaxLength, sizeof(char));
                                    if(!(*AtVal)){
                                        if(*At){
                                            free(*At);
                                        }
                                        return PARSE_ERROR;
                                    }  

                                }
        else                    {   nextState = PARSE_ATTRIBUTE_NAME; 

                                    /* Se concateneaza caractere la numele
                                      atributelor. */

                                    strncat(*At, &c, 1); }
        break;
    case PARSE_ATTRIBUTE_EQ:
        if (c == '\"')          {   nextState = PARSE_ATTRIBUTE_VALUE;  }
        break;
    case PARSE_ATTRIBUTE_VALUE:
        if (c == '\"')          {   nextState = PARSE_REST_OF_TAG; 

                                    /* Se construiesc listele de atribute si de
                                      stiluri ale nodului curent. */

                                    TAttr ant = NULL, p;
                                    int aux = strcmp(*At, "style");
                                    
                                    if(aux == 0){
                                        Trim(*AtVal);
                                        RemoveSpaces(*AtVal);
                                        char delim[] = ":;", *q;
                                        
                                        q = strtok(*AtVal, delim);
                                        if(!q){
                                            free(*At);
                                            free(*AtVal);
                                            return PARSE_ERROR;
                                        }
                                        while(q){
                                            char *cpy = strdup(q);
                                            if(!cpy){
                                                free(*At);
                                                free(*AtVal);
                                                return PARSE_ERROR;
                                            }
                                            
                                            q = strtok(NULL, delim);
                                            if(!q){
                                                free(*At);
                                                free(*AtVal);
                                                free(cpy);
                                                return PARSE_ERROR;
                                            }

                                            TAttr Attr = (TAttr)calloc(1, sizeof(TNodAttr));
                                            if(!Attr){
                                                free(*At);
                                                free(*AtVal);
                                                free(cpy);
                                                return PARSE_ERROR;
                                            }
                                            
                                            Attr->name = cpy;
                                            
                                            Attr->value = strdup(q);
                                            if(!(Attr->value)){
                                                free(*At);
                                                free(*AtVal);
                                                free(Attr);
                                                free(cpy);
                                                return PARSE_ERROR;
                                            }
                                            
                                            Trim(Attr->name);
                                            Trim(Attr->value);

                                            p = currentNode->info->style;

                                            while(p){
                                                ant = p;
                                                p = p->next;
                                            }

                                            if(ant == NULL){
                                                currentNode->info->style = Attr;
                                            }
                                            else{
                                                ant->next = Attr;
                                            }

                                            q = strtok(NULL, delim);
                                        }

                                        free(*At);
                                        free(*AtVal);

                                    } else {
                                        TAttr Attr = (TAttr)calloc(1, sizeof(TNodAttr));
                                        if(!Attr){
                                            free(*At);
                                            free(*AtVal);
                                        }

                                        Attr->name = *At;
                                        Attr->value = *AtVal;
                                        p = currentNode->info->otherAttributes;

                                        while(p){
                                            ant = p;
                                            p = p->next;
                                        }

                                        if(ant == NULL){
                                            currentNode->info->otherAttributes = Attr;
                                        }
                                        else{
                                            ant->next = Attr;
                                        }
                                    }
                                }
        else                    {   nextState = PARSE_ATTRIBUTE_VALUE; 
                                    
                                    /* Se concateneaza caractere la valorile
                                      atributelor. */

                                    strncat(*AtVal, &c, 1); 
                                }
        break;
    case PARSE_SELF_CLOSING:
        if (c == '>')           {   nextState = PARSE_CONTENTS; }
        else                    {   nextState = PARSE_ERROR;    }
        break;
    default:
        break;
    }

    return nextState;
}
