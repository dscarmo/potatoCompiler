#ifndef __CODEGEN_H__
#define __CODEGEN_H__

void codeGenBegins (no *ast);
void initializeOutput(char *args);
void generateCode (no *ast);
void getExpression (no *ast);
int checkConstruction(no *ast, const char *stype, const char *sdown, const char *snext);
void codeGen(no *ast);
void generateVar(no *ast);
void varGen(no *ast);
void callExpression(no* ast);

#endif 
