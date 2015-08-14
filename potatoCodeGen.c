#include "ast.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void codeGen(no *ast){
	if (ast -> value != NULL)
		printf("Nucleo e numero");
	else
		printf("Value null hue");
}
