%{
#include<stdio.h>
#include<stdbool.h>
#include<string.h>
bool capital=false;
bool small=false;
bool digit=false;
bool charac=false;
char buffer[100];

%}


%%
[A-Z]+ {capital=true; strcat(buffer,yytext);}
[a-z]+ {small=true; strcat(buffer,yytext);}
[0-9]+  {digit=true; strcat(buffer,yytext);}
(@|$|%|#) {charac=true;strcat(buffer,yytext);}
.          {printf("INvalid Password\n"); return 0;}
\n         {if(capital==true && small==true && digit==true && charac==true && strlen(buffer)>=8 && strlen(buffer)<=12){
	printf("Valid Password\n");
	

	}
else printf("Invalid Password\n");}

%%

int yywrap(){
	return 1;
}

int main(){
	yylex();
	return 0;
}