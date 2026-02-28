{%
#include<stdio.h>
int open=0;
int close=0;

%}

%%

(() {open++;}
()) {if(open>0) open--; else close++;}
.   {}

%%

int yywrap(){
	return 1;

}

int main(){
	yylex();
	return 0;
}
 
