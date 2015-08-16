#ifndef __CODEGEN_H__
#define __CODEGEN_H__

void checkAssign (no *ast);
int checkConstruction(no *ast, const char *stype, const char *sdown, const char *snext);
void codeGen(no *ast);

#endif 
