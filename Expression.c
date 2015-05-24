/*
 * Expression.c
 * Implementation of functions used to build the syntax tree.
 */
 
#include "Expression.h"
 
#include <stdlib.h>

#include <stdio.h>
 
/**
 * @brief Allocates space for expression
 * @return The expression or NULL if not enough memory
 */
static SExpression *allocateExpression()
{
    SExpression *b = (SExpression *)malloc(sizeof(SExpression));
 
    if (b == NULL)
        return NULL;
 
    b->type = eVALUE;
    b->value = 0;
 
    b->left = NULL;
    b->right = NULL;
 
    return b;
}
 
SExpression *createNumber(int value)
{
    SExpression *b = allocateExpression();
 
    if (b == NULL)
        return NULL;
 
    b->type = eVALUE;
    b->value = value;
 
    return b;
}
 
SExpression *createOperation(EOperationType type, SExpression *left, SExpression *right)
{
    SExpression *b = allocateExpression();
 
    if (b == NULL)
        return NULL;
 
    b->type = type;
    b->left = left;
    b->right = right;
 
    return b;
}
 
void deleteExpression(SExpression *b)
{
    if (b == NULL)
        return;
 
    deleteExpression(b->left);
    deleteExpression(b->right);
 
    free(b);
}

//My code 
//Left most recursive print
void printExpression(SExpression *t)
{
	if (t == NULL)
		return;
	
	int op = t->type;
	
	if (t->value != 0)
		printf("Value: %d \n", t->value);
	else 
	{
		switch(op)
		{
			case 1: printf("Times \n"); break;
			case 2: printf("Plus \n"); break;
		}
	}
	printExpression(t->left);
	printExpression(t->right);
}
