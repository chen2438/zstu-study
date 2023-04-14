%{
    //包含C头文件、定义全局变量、声明函数
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    int line=2;
%}


%x COMMENT

%%
[\n]*        {printf("\nline %d:\n",line); line++;}

"{"                     { BEGIN(COMMENT); }
<COMMENT>[^{}]*         {
                            printf("COMMENT BEGIN\n");
                            for(int i = 0; i < strlen(yytext); i++){
                                if(yytext[i] == '\n'){
                                    printf("\nline %d:\n",line); line++;
                                }
                                else{
                                    printf("%c",yytext[i]);
                                }
                            }
                            //printf("COMMENT BEGIN{ %s } COMMENT END\n",yytext); 
                            printf("COMMENT END\n");
                        }
<COMMENT>"}"            { BEGIN(INITIAL); }

"read"       printf("READ ");
"if"         printf("IF ");
"then"       printf("THEN ");
"else"       printf("ELSE ");
"repeat"     printf("REPEAT ");
"until"      printf("UNTIL ");
"write"      printf("WRITE ");
"end"        printf("END ");
":="         printf("ASSIGN ");
";"          printf("SEMICOLON\n");
"<"          printf("LESS_THAN ");
">"          printf("GREATER_THAN ");
"="          printf("EQUALS ");
"+"          printf("PLUS ");
"-"          printf("MINUS ");
"*"          printf("MULTIPLY ");
"/"          printf("DIVIDE ");
"%"          printf("MODULO ");

[0-9]+       printf("[NUMBER, Value = %s] ",yytext);
[a-zA-Z]+    printf("[IDENTIFIER, Name = %s] ",yytext);
[\t]         /* ignore*/
[ ]          /* ignore*/
.            printf("UNKNOWN ");

%%

int yywrap() {
    return 1;
}


int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "usage: %s filename\n", argv[0]);
        exit(1);
    }

    FILE *file = fopen(argv[1], "r");
    if (!file) {
        fprintf(stderr, "could not open file: %s\n", argv[1]);
        exit(1);
    }
    
    yyin = file;
    printf("line1:\n");
    yylex();

    fclose(file);
    return 0;
}
