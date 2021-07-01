#pragma region INCLUDE

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "structures.h"

#pragma endregion

#pragma region DATA TYPES

typedef enum
{
    INIT_DB,           // 0
    DELETE_DB,         // 1
    CREATE_TABLE,      // 2
    DELETE_TABLE,      // 3
    PRINT_DB,          // 4
    PRINT_TABLE,       // 5
    SEARCH_TABLE,      // 6
    ADD_TO_TABLE,      // 7
    DELETE_FROM_TABLE, // 8
    CLEAR_TABLE,       // 9
    INVALID_ACTION     // 10
} t_action;

typedef enum
{
    SUCCES,               // 0
    DATABASE_NOT_FOUND,   // 1
    COLUMN_NOT_FOUND,     // 2
    TABLE_ALREADY_EXISTS, // 3
    TABLE_NOT_FOUND,      // 4
    UNKNOWN_COMMAND,      // 5
    UNKNOWN_DATA_TYPE     // 6
} t_acion_result;

typedef struct int_relationship
{
    int column_index;
    char relation[3];
    int value;
} t_int_relationship;

typedef struct float_relationship
{
    int column_index;
    char relation[3];
    float value;
} t_float_relationship;

typedef struct string_relationship
{
    int column_index;
    char relation[3];
    char value[MAX_CMD_LEN];
} t_string_relationship;

#pragma endregion

#pragma region Helper Methods

int get_words_number(const char *command)
{
    int words = 1;
    for (int i = 0; i < strlen(command); i++)
        words += command[i] == ' ' ? 1 : 0;
    return words;
}

char *ltrim(char *s)
{
    while (isspace(*s))
        s++;
    return s;
}

char *rtrim(char *s)
{
    char *back = s + strlen(s);
    while (isspace(*--back))
        ;
    *(back + 1) = '\0';
    return s;
}

char *trim(char *s)
{
    return rtrim(ltrim(s));
}

t_action get_action(const char *command)
{
    char *action = (char *)malloc(MAX_CMD_LEN);
    strcpy(action, command);

    if (strcmp(action, "DELETE_DB") == 0)
        return DELETE_DB;

    if (strcmp(action, "PRINT_DB") == 0)
        return PRINT_DB;

    action = strtok(action, " ");

    int words_number = get_words_number(command);

    if (strcmp(action, "INIT_DB") == 0 && words_number == 2)
        return INIT_DB;
    else if (strcmp(action, "CREATE") == 0 && words_number > 3)
        return CREATE_TABLE;
    else if (strcmp(action, "PRINT") == 0 && words_number == 2)
        return PRINT_TABLE;
    else if (strcmp(action, "SEARCH") == 0 && words_number == 5)
        return SEARCH_TABLE;
    else if (strcmp(action, "ADD") == 0 && words_number > 2)
        return ADD_TO_TABLE;
    else if (strcmp(action, "CLEAR") == 0 && words_number == 2)
        return CLEAR_TABLE;
    else if (strcmp(action, "DELETE") == 0 && words_number == 2)
        return DELETE_TABLE;
    else if (strcmp(action, "DELETE") == 0 && words_number == 5)
        return DELETE_FROM_TABLE;

    return INVALID_ACTION;
}

t_cellType get_cell_type(char *type)
{
    if (strcmp(type, "INT") == 0)
        return INT;
    else if (strcmp(type, "FLOAT") == 0)
        return FLOAT;
    else if (strcmp(type, "STRING") == 0)
        return STRING;
    return -1;
}

char *get_database_name(char *command)
{
    char *db_name = command;
    db_name = strtok(db_name, " ");
    db_name = strtok(NULL, " ");
    return db_name;
}

bool exist_table(t_db *database, char *table_name)
{
    if (database == NULL)
    {
        return false;
    }
    t_table *table = database->tables;

    if (table_name == NULL)
        return false;

    while (table != NULL)
    {
        if (strcmp(table->name, table_name) == 0)
        {
            return true;
        }
        table = table->next;
    }
    return false;
}

int get_column_index(t_table *table, char *column_name)
{
    t_column *column = table->columns;
    int index = 0;
    while (column != NULL)
    {
        if (strcmp(column->name, column_name) == 0)
        {
            return index;
        }
        index++;
        column = column->next;
    }
    return -1;
}

t_table *get_table_by_name(t_db *database, char *table_name)
{
    t_table *table = database->tables;
    while (table != NULL)
    {
        if (strcmp(table->name, table_name) == 0) // if table is found
        {
            return table;
        }
        table = table->next;
    }
    return NULL;
}

bool int_line_satisfy_condition(t_intCell *cell, t_int_relationship *int_relationship)
{
    t_intCell *aux_cell = cell;
    int actual_column_index = 0;
    int search_value = int_relationship->value;
    while (aux_cell != NULL)
    {
        if (actual_column_index == int_relationship->column_index)
        {
            if (strcmp(int_relationship->relation, "==") == 0)
            {
                if (aux_cell->value != search_value)
                {
                    return false;
                }
            }
            else if (strcmp(int_relationship->relation, "!=") == 0)
            {
                if (aux_cell->value == search_value)
                {
                    return false;
                }
            }
            else if (strcmp(int_relationship->relation, "<=") == 0)
            {
                if (aux_cell->value > search_value)
                {
                    return false;
                }
            }
            else if (strcmp(int_relationship->relation, ">=") == 0)
            {
                if (aux_cell->value < search_value)
                {
                    return false;
                }
            }
            else if (strcmp(int_relationship->relation, "<") == 0)
            {
                if (aux_cell->value >= search_value)
                {
                    return false;
                }
            }
            else if (strcmp(int_relationship->relation, ">") == 0)
            {
                if (aux_cell->value <= search_value)
                {
                    return false;
                }
            }
            break;
        }
        actual_column_index++;
        aux_cell = aux_cell->next;
    }
    return true;
}

bool float_line_satisfy_condition(t_floatCell *cell, t_float_relationship *float_relationship)
{
    t_floatCell *aux_cell = cell;
    int actual_column_index = 0;
    float search_value = float_relationship->value;
    while (aux_cell != NULL)
    {
        if (actual_column_index == float_relationship->column_index)
        {
            if (strcmp(float_relationship->relation, "==") == 0)
            {
                if (aux_cell->value != search_value)
                {
                    return false;
                    ;
                }
            }
            else if (strcmp(float_relationship->relation, "!=") == 0)
            {
                if (aux_cell->value == search_value)
                {
                    return false;
                }
            }
            else if (strcmp(float_relationship->relation, "<=") == 0)
            {
                if (aux_cell->value > search_value)
                {
                    return false;
                }
            }
            else if (strcmp(float_relationship->relation, ">=") == 0)
            {
                if (aux_cell->value < search_value)
                {
                    return false;
                }
            }
            else if (strcmp(float_relationship->relation, "<") == 0)
            {
                if (aux_cell->value >= search_value)
                {
                    return false;
                }
            }
            else if (strcmp(float_relationship->relation, ">") == 0)
            {
                if (aux_cell->value <= search_value)
                {
                    return false;
                }
            }
            break;
        }
        actual_column_index++;
        aux_cell = aux_cell->next;
    }
    return true;
}

bool string_line_satisfy_condition(t_stringCell *cell, t_string_relationship *string_relationship)
{
    t_stringCell *aux_cell = cell;
    int actual_column_index = 0;
    char *search_value = string_relationship->value;
    while (aux_cell != NULL)
    {
        if (actual_column_index == string_relationship->column_index)
        {
            if (strcmp(string_relationship->relation, "==") == 0)
            {
                if (strcmp(aux_cell->value, search_value) != 0)
                {
                    return false;
                }
            }
            else if (strcmp(string_relationship->relation, "!=") == 0)
            {
                if ((strcmp(aux_cell->value, search_value) == 0))
                {
                    return false;
                }
            }
            else if (strcmp(string_relationship->relation, "<=") == 0)
            {
                if ((strcmp(aux_cell->value, search_value) > 0))
                {
                    return false;
                }
            }
            else if (strcmp(string_relationship->relation, ">=") == 0)
            {
                if ((strcmp(aux_cell->value, search_value) < 0))
                {
                    return false;
                }
            }
            else if (strcmp(string_relationship->relation, "<") == 0)
            {
                if ((strcmp(aux_cell->value, search_value) >= 0))
                {
                    return false;
                }
            }
            else if (strcmp(string_relationship->relation, ">") == 0)
            {
                if ((strcmp(aux_cell->value, search_value) <= 0))
                {
                    return false;
                }
            }
            break;
        }
        actual_column_index++;
        aux_cell = aux_cell->next;
    }
    return true;
}

#pragma endregion

#pragma region INIT_DATABASE

t_db *get_empty_database(char *command)
{
    char *database_name = get_database_name(command);
    if (database_name != NULL)
    {
        t_db *database = (t_db *)malloc(sizeof(t_db));
        strcpy(database->name, database_name);
        return database;
    }
    return NULL;
}

#pragma endregion

#pragma region PRINT TABLE

void print_int_cells(t_intCell *cell, char *paddingLines, char *paddingSpaces)
{
    while (cell != NULL)
    {
        char buffer[10];
        sprintf(buffer, "%d", cell->value);
        cell = cell->next;
        int padLen = MAX_COLUMN_NAME_LEN - strlen(buffer) + 1;
        if (padLen < 0)
            padLen = 0;
        printf("%s%*.*s", buffer, padLen, padLen, paddingSpaces); // RIGHT Padding
    }
}

void print_string_cells(t_stringCell *cell, char *paddingLines, char *paddingSpaces)
{
    while (cell != NULL)
    {
        int padLen = MAX_COLUMN_NAME_LEN - strlen(cell->value) + 1;
        if (padLen < 0)
            padLen = 0;
        printf("%s%*.*s", cell->value, padLen, padLen, paddingSpaces); // RIGHT Padding
        cell = cell->next;
    }
}

void print_float_cells(t_floatCell *cell, char *paddingLines, char *paddingSpaces)
{
    while (cell != NULL)
    {
        char buffer[10];
        sprintf(buffer, "%f", cell->value);
        cell = cell->next;
        int padLen = MAX_COLUMN_NAME_LEN - strlen(buffer) + 1;
        if (padLen < 0)
            padLen = 0;
        printf("%s%*.*s", buffer, padLen, padLen, paddingSpaces); // RIGHT Padding
    }
}

void print_int_line(t_intLine *intLine, char *paddingLines, char *paddingSpaces)
{
    while (intLine != NULL)
    {
        t_intCell *cell = intLine->cells;
        print_int_cells(cell, paddingLines, paddingSpaces);
        intLine = intLine->next;
        printf("\n");
    }
}

void print_float_line(t_floatLine *floatLine, char *paddingLines, char *paddingSpaces)
{
    while (floatLine != NULL)
    {
        t_floatCell *cell = floatLine->cells;
        print_float_cells(cell, paddingLines, paddingSpaces);
        floatLine = floatLine->next;
        printf("\n");
    }
}

void print_string_line(t_stringLine *stringLine, char *paddingLines, char *paddingSpaces)
{
    while (stringLine != NULL)
    {
        t_stringCell *cell = stringLine->cells;
        print_string_cells(cell, paddingLines, paddingSpaces);
        stringLine = stringLine->next;
        printf("\n");
    }
}

t_acion_result print_table(t_db *database, char *command)
{
    if (database == NULL)
    {
        return DATABASE_NOT_FOUND;
    }

    command = strtok(command, " ");
    command = strtok(NULL, " ");
    char *table_name = (char *)malloc(MAX_TABLE_NAME_LEN);
    strcpy(table_name, command);

    if (!exist_table(database, table_name))
    {
        printf("Table \"%s\" not found in database.\n", table_name);
        return TABLE_NOT_FOUND;
    }

    char *paddingLines = (char *)malloc(MAX_COLUMN_NAME_LEN + 1);    // --------------------------
    char *paddingSpaces = (char *)malloc(MAX_COLUMN_NAME_LEN + 1);   //                           
    for (int i = 0; i < MAX_COLUMN_NAME_LEN; i++)
    {
        paddingLines[i] = '-';
        paddingSpaces[i] = ' ';
    }

    t_table *table = get_table_by_name(database, table_name);

    printf("TABLE: %s\n", table->name);
    t_column *column = table->columns;
    int columnsNumber = 0;
    while (column != NULL)
    {
        int padLen = MAX_COLUMN_NAME_LEN - strlen(column->name) + 1;
        if (padLen < 0)
            padLen = 0;
        printf("%s%*.*s", column->name, padLen, padLen, paddingSpaces); // RIGHT Padding
        column = column->next;
        columnsNumber++;
    }
    printf("\n");
    for (int i = 0; i < columnsNumber; i++)
    {
        printf("%s ", paddingLines);
    }
    printf("\n");

    void *line = table->lines;
    switch (table->type)
    {
    case INT:
    {
        t_intLine *intLine = (t_intLine *)(line);
        print_int_line(intLine, paddingLines, paddingSpaces);
    }
    break;
    case FLOAT:
    {
        t_floatLine *floatLine = (t_floatLine *)(line);
        print_float_line(floatLine, paddingLines, paddingSpaces);
    }
    break;
    case STRING:
    {
        t_stringLine *stringLine = (t_stringLine *)(line);
        print_string_line(stringLine, paddingLines, paddingSpaces);
    }
    break;
    }
    printf("\n");
    return SUCCES;
}

#pragma endregion

#pragma region SEARCH TABLE

void print_int_cells_filtered(t_intCell *cell, char *paddingLines, char *paddingSpaces, t_int_relationship *int_relationship)
{
    bool satisfy_condition = int_line_satisfy_condition(cell, int_relationship);
    if (satisfy_condition)
    {
        while (cell != NULL)
        {
            char buffer[10];
            sprintf(buffer, "%d", cell->value);
            cell = cell->next;
            int padLen = MAX_COLUMN_NAME_LEN - strlen(buffer) + 1;
            if (padLen < 0)
                padLen = 0;
            printf("%s%*.*s", buffer, padLen, padLen, paddingSpaces); // RIGHT Padding
        }
        printf("\n");
    }
}

void print_float_cells_filtered(t_floatCell *cell, char *paddingLines, char *paddingSpaces, t_float_relationship *float_relationship)
{
    bool satisfy_condition = float_line_satisfy_condition(cell, float_relationship);
    if (satisfy_condition)
    {
        while (cell != NULL)
        {
            char buffer[10];
            sprintf(buffer, "%f", cell->value);
            cell = cell->next;
            int padLen = MAX_COLUMN_NAME_LEN - strlen(buffer) + 1;
            if (padLen < 0)
                padLen = 0;
            printf("%s%*.*s", buffer, padLen, padLen, paddingSpaces); // RIGHT Padding
        }
        printf("\n");
    }
}

void print_string_cells_filtered(t_stringCell *cell, char *paddingLines, char *paddingSpaces, t_string_relationship *string_relationship)
{
    bool satisfy_condition = string_line_satisfy_condition(cell, string_relationship);
    if (satisfy_condition)
    {
        while (cell != NULL)
        {
            int padLen = MAX_COLUMN_NAME_LEN - strlen(cell->value) + 1;
            if (padLen < 0)
                padLen = 0;
            printf("%s%*.*s", cell->value, padLen, padLen, paddingSpaces); // RIGHT Padding
            cell = cell->next;
        }
        printf("\n");
    }
}

void print_int_line_filtered(t_intLine *intLine, char *paddingLines, char *paddingSpaces, t_int_relationship *int_relationship)
{
    while (intLine != NULL)
    {
        t_intCell *cell = intLine->cells;
        print_int_cells_filtered(cell, paddingLines, paddingSpaces, int_relationship);
        intLine = intLine->next;
    }
}

void print_float_line_filtered(t_floatLine *floatLine, char *paddingLines, char *paddingSpaces, t_float_relationship *float_relationship)
{
    while (floatLine != NULL)
    {
        t_floatCell *cell = floatLine->cells;
        print_float_cells_filtered(cell, paddingLines, paddingSpaces, float_relationship);
        floatLine = floatLine->next;
    }
}

void print_string_line_filtered(t_stringLine *stringLine, char *paddingLines, char *paddingSpaces, t_string_relationship *string_relationship)
{
    while (stringLine != NULL)
    {
        t_stringCell *cell = stringLine->cells;
        print_string_cells_filtered(cell, paddingLines, paddingSpaces, string_relationship);
        stringLine = stringLine->next;
    }
}

t_acion_result print_table_filtered(t_db *database, char *command)
{
    if (database == NULL)
    {
        return DATABASE_NOT_FOUND;
    }

    command = strtok(command, " ");
    command = strtok(NULL, " ");
    char *table_name = (char *)malloc(MAX_TABLE_NAME_LEN);
    strcpy(table_name, command);

    if (!exist_table(database, table_name))
    {
        printf("Table \"%s\" not found in database.\n", table_name);
        return TABLE_NOT_FOUND;
    }

    t_table *table = get_table_by_name(database, table_name);

    char *column_name = (char *)malloc(MAX_COLUMN_NAME_LEN + 1);
    command = strtok(NULL, " ");
    strcpy(column_name, command);

    int column_index = get_column_index(table, column_name);
    if (column_index == -1)
    {
        printf("Table \"%s\" does not contain column \"%s\".\n", table->name, column_name);
        return COLUMN_NOT_FOUND;
    }

    /*  TABLE HEADER  START */

    char *paddingLines = (char *)malloc(MAX_COLUMN_NAME_LEN + 1);
    char *paddingSpaces = (char *)malloc(MAX_COLUMN_NAME_LEN + 1);
    for (int i = 0; i < MAX_COLUMN_NAME_LEN; i++)
    {
        paddingLines[i] = '-';
        paddingSpaces[i] = ' ';
    }

    printf("TABLE: %s\n", table->name);
    t_column *column = table->columns;
    int columnsNumber = 0;
    while (column != NULL)
    {
        int padLen = MAX_COLUMN_NAME_LEN - strlen(column->name) + 1;
        if (padLen < 0)
            padLen = 0;
        printf("%s%*.*s", column->name, padLen, padLen, paddingSpaces); // RIGHT Padding
        column = column->next;
        columnsNumber++;
    }
    printf("\n");
    for (int i = 0; i < columnsNumber; i++)
    {
        printf("%s ", paddingLines);
    }
    printf("\n");

    /*  TABLE HEADER END */

    char *relationship_sign = (char *)malloc(3);
    command = strtok(NULL, " ");
    strcpy(relationship_sign, command);


    char *value = (char *)malloc(MAX_CMD_LEN);
    command = strtok(NULL, " ");
    strcpy(value, command);

    void *line = table->lines;
    switch (table->type)
    {
    case INT:
    {
        t_intLine *intLine = (t_intLine *)(line);
        t_int_relationship *int_relationship = (t_int_relationship *)malloc(sizeof(t_int_relationship));
        int_relationship->column_index = column_index;
        strcpy(int_relationship->relation, relationship_sign);
        int_relationship->value = atoi(value);

        print_int_line_filtered(intLine, paddingLines, paddingSpaces, int_relationship);
    }
    break;
    case FLOAT:
    {
        t_floatLine *floatLine = (t_floatLine *)(line);
        t_float_relationship *float_relationship = (t_float_relationship *)malloc(sizeof(t_float_relationship));
        float_relationship->column_index = column_index;
        strcpy(float_relationship->relation, relationship_sign);
        float_relationship->value = atof(value);

        print_float_line_filtered(floatLine, paddingLines, paddingSpaces, float_relationship);
    }
    break;
    case STRING:
    {
        t_stringLine *stringLine = (t_stringLine *)(line);
        t_string_relationship *string_relationship = (t_string_relationship *)malloc(sizeof(t_string_relationship));
        string_relationship->column_index = column_index;
        strcpy(string_relationship->relation, relationship_sign);
        strcpy(string_relationship->value, value);

        print_string_line_filtered(stringLine, paddingLines, paddingSpaces, string_relationship);
    }
    break;
    }
    printf("\n");
    return SUCCES;
}

#pragma endregion

#pragma region DELETE TABLE BY CONDITION

void delete_int_line_if_needed(t_table *table, t_intLine *intLine, t_int_relationship *int_relationship)
{
    t_intLine *temp = (t_intLine *)table->lines, *prev;

    while (temp != NULL && int_line_satisfy_condition(temp->cells, int_relationship))
    {
        table->lines = temp->next;
        free(temp);
        temp = table->lines;
    }

    while (temp != NULL)
    {
        while (temp != NULL && !int_line_satisfy_condition(temp->cells, int_relationship))
        {
            prev = temp;
            temp = temp->next;
        }

        if (temp == NULL)
            return;
        prev->next = temp->next;
        free(temp);
        temp = prev->next;
    }
}

void delete_float_line_if_needed(t_table *table, t_floatLine *floatLine, t_float_relationship *float_relationship)
{
    t_floatLine *temp = (t_floatLine *)table->lines, *prev;

    while (temp != NULL && float_line_satisfy_condition(temp->cells, float_relationship))
    {
        table->lines = temp->next;
        free(temp);
        temp = table->lines;
    }

    while (temp != NULL)
    {
        while (temp != NULL && !float_line_satisfy_condition(temp->cells, float_relationship))
        {
            prev = temp;
            temp = temp->next;
        }

        if (temp == NULL)
            return;
        prev->next = temp->next;
        free(temp);
        temp = prev->next;
    }
}

void delete_string_line_if_needed(t_table *table, t_stringLine *stringLine, t_string_relationship *string_relationship)
{
    t_stringLine *temp = (t_stringLine *)table->lines, *prev;

    while (temp != NULL && string_line_satisfy_condition(temp->cells, string_relationship))
    {
        table->lines = temp->next;
        free(temp);
        temp = table->lines;
    }

    while (temp != NULL)
    {
        while (temp != NULL && !string_line_satisfy_condition(temp->cells, string_relationship))
        {
            prev = temp;
            temp = temp->next;
        }

        if (temp == NULL)
            return;
        prev->next = temp->next;
        free(temp);
        temp = prev->next;
    }
}

t_acion_result delete_table_filtered(t_db *database, char *command)
{
    if (database == NULL)
    {
        return DATABASE_NOT_FOUND;
    }

    command = strtok(command, " ");
    command = strtok(NULL, " ");
    char *table_name = (char *)malloc(MAX_TABLE_NAME_LEN);
    strcpy(table_name, command);

    if (!exist_table(database, table_name))
    {
        printf("Table \"%s\" not found in database.\n", table_name);
        return TABLE_NOT_FOUND;
    }

    t_table *table = get_table_by_name(database, table_name);

    char *column_name = (char *)malloc(MAX_COLUMN_NAME_LEN + 1);
    command = strtok(NULL, " ");
    strcpy(column_name, command);

    int column_index = get_column_index(table, column_name);
    if (column_index == -1)
    {
        printf("Table \"%s\" does not contain column \"%s\".\n", table->name, column_name);
        return COLUMN_NOT_FOUND;
    }

    char *relationship_sign = (char *)malloc(3);
    command = strtok(NULL, " ");
    strcpy(relationship_sign, command);


    char *value = (char *)malloc(MAX_CMD_LEN);
    command = strtok(NULL, " ");
    strcpy(value, command);

    void *line = table->lines;
    switch (table->type)
    {

    case INT:
    {
        t_intLine *intLine = (t_intLine *)(line);
        t_int_relationship *int_relationship = (t_int_relationship *)malloc(sizeof(t_int_relationship));
        int_relationship->column_index = column_index;
        strcpy(int_relationship->relation, relationship_sign);
        int_relationship->value = atoi(value);

        delete_int_line_if_needed(table, intLine, int_relationship);
    }
    break;
    case FLOAT:
    {
        t_floatLine *floatLine = (t_floatLine *)(line);
        t_float_relationship *float_relationship = (t_float_relationship *)malloc(sizeof(t_float_relationship));
        float_relationship->column_index = column_index;
        strcpy(float_relationship->relation, relationship_sign);
        float_relationship->value = atof(value);
        delete_float_line_if_needed(table, floatLine, float_relationship);
    }
    break;
    case STRING:
    {
        t_stringLine *stringLine = (t_stringLine *)(line);
        t_string_relationship *string_relationship = (t_string_relationship *)malloc(sizeof(t_string_relationship));
        string_relationship->column_index = column_index;
        strcpy(string_relationship->relation, relationship_sign);
        strcpy(string_relationship->value, value);
        delete_string_line_if_needed(table, stringLine, string_relationship);
    }
    break;
    }
    return SUCCES;
}

#pragma endregion

#pragma region CREATE TABLE

t_acion_result create_table(t_db *database, char *command)
{
    if (database == NULL)
    {
        return DATABASE_NOT_FOUND;
    }

    command = strtok(command, " ");
    command = strtok(NULL, " ");
    char *table_name = (char *)malloc(MAX_TABLE_NAME_LEN);
    strcpy(table_name, command);

    if (exist_table(database, table_name))
    {
        printf("Table \"%s\" already exists.\n", table_name);
        return TABLE_ALREADY_EXISTS;
    }

    command = strtok(NULL, " ");
    char *type = (char *)malloc(10);
    strcpy(type, command);

    t_cellType cell_type = get_cell_type(type);
    if (cell_type == -1)
    {
        printf("Unknown data type: \"<%s>\".\n", type);
        return UNKNOWN_DATA_TYPE;
    }

    t_table *table = (t_table *)malloc(sizeof(t_table));
    strcpy(table->name, table_name);
    table->type = cell_type;
    table->next = NULL;

    command = strtok(NULL, " ");

    /* ADDING COLUMNS START */
    while (command != NULL)
    {
        t_column *column = (t_column *)malloc(sizeof(t_column));
        strcpy(column->name, command);
        column->next = NULL;
        if (table->columns == NULL)
        {
            table->columns = column;
        }
        else
        {
            t_column *aux_col = table->columns;
            while (aux_col != NULL)
            {
                if (aux_col->next == NULL)
                {
                    aux_col->next = column;
                    break;
                }
                aux_col = aux_col->next;
            }
        }
        command = strtok(NULL, " ");
    }

    /* ADDING COLUMNS END */

    if (database->tables == NULL)
    {
        database->tables = table;
    }
    else
    {
        t_table *aux_table = database->tables;
        while (aux_table != NULL)
        {
            if (aux_table->next == NULL)
            {
                aux_table->next = table;
                break;
            }
            aux_table = aux_table->next;
        }
    }
    return SUCCES;
}

#pragma endregion

#pragma region DELETE TABLE

t_acion_result delete_table(t_db *database, char *command)
{
    if (database == NULL)
    {
        return DATABASE_NOT_FOUND;
    }

    command = strtok(command, " ");
    command = strtok(NULL, " ");
    char *table_name = (char *)malloc(MAX_TABLE_NAME_LEN);
    strcpy(table_name, command);

    if (!exist_table(database, table_name))
    {
        printf("Table \"%s\" not found in database.\n", table_name);
        return TABLE_NOT_FOUND;
    }

    t_table *table = database->tables, *prev;
    if (table != NULL && strcmp(table->name, table_name) == 0) // if first table is found then remake the link and free the table
    {
        database->tables = table->next;
        table->columns = NULL;
        table->lines = NULL;
        free(table);
        return SUCCES;
    }

    while (table != NULL && strcmp(table->name, table_name) != 0)
    {
        // if table is found then remake the link and free the table
        prev = table;
        table = table->next;
    }
    if (table == NULL)
        return SUCCES;

    prev->next = table->next;

    return SUCCES;
}

#pragma endregion

#pragma region CLEAR TABLE

t_acion_result clear_table(t_db *database, char *command)
{
    if (database == NULL)
    {
        return DATABASE_NOT_FOUND;
    }

    command = strtok(command, " ");
    command = strtok(NULL, " ");
    char *table_name = (char *)malloc(MAX_TABLE_NAME_LEN);
    strcpy(table_name, command);

    if (!exist_table(database, table_name))
    {
        printf("Table \"%s\" not found in database.\n", table_name);
        return TABLE_NOT_FOUND;
    }

    t_table *table = get_table_by_name(database, table_name);
    if (table != NULL)
    {
        table->lines = NULL;
    }

    return SUCCES;
}

#pragma endregion

#pragma region ADD DATA TO TABLE

t_acion_result add_data_to_table(t_db *database, char *command)
{
    if (database == NULL)
    {
        return DATABASE_NOT_FOUND;
    }

    command = strtok(command, " ");
    command = strtok(NULL, " ");
    char *table_name = (char *)malloc(MAX_TABLE_NAME_LEN);
    strcpy(table_name, command);

    if (!exist_table(database, table_name))
    {
        printf("Table \"%s\" not found in database.\n", table_name);
        return TABLE_NOT_FOUND;
    }

    t_table *table = get_table_by_name(database, table_name);
    if (table != NULL)
    {
        command = strtok(NULL, " ");
        switch (table->type)
        {
        case INT:
        {
            t_intLine *intLine = (t_intLine *)malloc(sizeof(t_intLine));
            intLine->next = NULL;
            while (command != NULL)
            {
                t_intCell *cell = (t_intCell *)malloc(sizeof(t_intCell));
                cell->value = atoi(command);
                cell->next = NULL;
                if (intLine->cells == NULL) // if there is no cell then cell will point to cell
                {
                    intLine->cells = cell;
                }
                else
                {
                    t_intCell *aux_cell = intLine->cells; // if exists cells then add after them
                    while (aux_cell != NULL)
                    {
                        if (aux_cell->next == NULL)
                        {
                            aux_cell->next = cell;
                            break;
                        }
                        aux_cell = aux_cell->next;
                    }
                }
                command = strtok(NULL, " ");
            }

            if (table->lines == NULL)
            {
                table->lines = intLine;
            }
            else
            {
                t_intLine *line = (t_intLine *)table->lines;
                while (line != NULL)
                {
                    if (line->next == NULL)
                    {
                        line->next = (void *)intLine;
                        break;
                    }
                    line = line->next;
                }
            }
            break;
        }
        case FLOAT:
        {
            t_floatLine *floatLine = (t_floatLine *)malloc(sizeof(t_floatLine));
            while (command != NULL)
            {
                t_floatCell *cell = (t_floatCell *)malloc(sizeof(t_floatCell));
                cell->value = atof(command);
                cell->next = NULL;
                if (floatLine->cells == NULL) // if there is no cell then cell will point to cell
                {
                    floatLine->cells = cell;
                }
                else
                {
                    t_floatCell *aux_cell = floatLine->cells; // if exists cells then add after them
                    while (aux_cell != NULL)
                    {
                        if (aux_cell->next == NULL)
                        {
                            aux_cell->next = cell;
                            break;
                        }
                        aux_cell = aux_cell->next;
                    }
                }
                command = strtok(NULL, " ");
            }

            if (table->lines == NULL)
            {
                table->lines = floatLine;
            }
            else
            {
                t_floatLine *line = (t_floatLine *)table->lines;
                while (line != NULL)
                {
                    if (line->next == NULL)
                    {
                        line->next = (void *)floatLine;
                        break;
                    }
                    line = line->next;
                }
            }
        }
        break;
        case STRING:
        {
            t_stringLine *stringLine = (t_stringLine *)malloc(sizeof(t_stringLine));
            while (command != NULL)
            {
                t_stringCell *cell = (t_stringCell *)malloc(sizeof(t_stringCell));

                cell->value = (char *)malloc(MAX_CMD_LEN);
                strcpy(cell->value, command);
                cell->next = NULL;
                if (stringLine->cells == NULL) // if there is no cell then cell will point to cell
                {
                    stringLine->cells = cell;
                }
                else
                {
                    t_stringCell *aux_cell = stringLine->cells; // if exists cells then add after them
                    while (aux_cell != NULL)
                    {
                        if (aux_cell->next == NULL)
                        {
                            aux_cell->next = cell;
                            break;
                        }
                        aux_cell = aux_cell->next;
                    }
                }
                command = strtok(NULL, " ");
            }
            if (table->lines == NULL)
            {
                table->lines = stringLine;
            }
            else
            {
                t_stringLine *line = (t_stringLine *)table->lines;
                while (line != NULL)
                {
                    if (line->next == NULL)
                    {
                        line->next = (void *)stringLine;
                        break;
                    }
                    line = line->next;
                }
            }
        }
        break;
        default:
            break;
        }
    }

    return SUCCES;
}

#pragma endregion

#pragma region PRINT DATABASE

t_acion_result print_db(t_db *database)
{
    printf("DATABASE: %s\n\n", database->name);
    t_table *table = database->tables;
    while (table != NULL)
    {
        char command[MAX_CMD_LEN];
        strcpy(command, "PRINT ");
        strcat(command, table->name);
        print_table(database, command);
        table = table->next;
    }
    return SUCCES;
}

#pragma endregion

#pragma region Start

void start(t_db *database)
{
    char command[MAX_CMD_LEN];
    t_acion_result action_result;

    while (1)
    {
        fgets(command, MAX_CMD_LEN, stdin);
        if (strlen(command) < 2)
            continue;

        command[strlen(command) - 1] = '\0';
        t_action action = get_action(command);
        switch (action)
        {
        case INIT_DB:
            database = get_empty_database(command);
            break;
        case DELETE_DB:
            free(database);
            database = NULL;
            return;
        case CREATE_TABLE:
            action_result = create_table(database, command);
            break;
        case PRINT_DB:
            print_db(database);
            break;
        case DELETE_TABLE:
            action_result = delete_table(database, command);
            break;
        case CLEAR_TABLE:
            action_result = clear_table(database, command);
            break;
        case ADD_TO_TABLE:
            action_result = add_data_to_table(database, command);
            break;
        case PRINT_TABLE:
            action_result = print_table(database, command);
            break;
        case SEARCH_TABLE:
            action_result = print_table_filtered(database, command);
            break;
        case DELETE_FROM_TABLE:
            action_result = delete_table_filtered(database, command);
            break;
        case INVALID_ACTION:
            printf("Unknown command: \"%s\"\n", command);
            break;
        default:
            break;
        }
    }
}

#pragma endregion

int main()
{
    t_db *database = NULL;
    start(database);
    return 0;
}
