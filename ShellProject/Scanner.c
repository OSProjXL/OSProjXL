#include <stdio.h>
#include <string.h>
#include "Scanner.h"
#include <unistd.h>
#include <stdlib.h>
#include "y.tab.h"

extern int yylex();
extern int yylineno;
extern char* yytext;
extern int yyparse();


extern char **environ;


void changedir(char*);
void print(void);
void shell_init();
void printPrompt();
int getCommand();
void init_scanner_and_parser();
void recover_from_errors();
void processCommand();
void do_it();
void gohome();
void printEnv();



//Need to actually declare the global variables here????
int builtin;
int bicmd;
char *bistr;

int CMD = 0;

int main(void) 
{
	//shell_init();
	while(1){
		printPrompt();

		//This calls yyparse()
		CMD = getCommand();
		switch(CMD)		//check if its a excutible command that follows all the rules.
		{
			//case BYE:		exit(1);
			case ERROR: 	recover_from_errors();
			case OK:		processCommand();
		}
		
	}
	return 0;
	
}




void print(void){	printf("word\n");}

void shell_init()
{	
	// init all variables.
	// define (allocate storage) for some var/tables 
	//init all tables (e.g., alias table)
	//get PATH environment variable (use getenv()) 
	//get HOME env variable (also use getenv()) 
	//disable anything that can kill your shell.
	// (the shell should never die; only can be exit) 
	// do anything you feel should be done as init
}

void printPrompt(){	 printf("%s :> ",getcwd(NULL, 0));}
// {
// 	printf("shell < ");
// }

int getCommand()
{
	init_scanner_and_parser(); 

	//The value is 1 if parsing failed because of invalid input, i.e., input that contains a syntax error or that causes YYABORT to be invoked.

	if (yyparse())								
		return (ERROR);
	else
		return (OK);		//The value returned by yyparse is 0 if parsing was successfu					
}


void init_scanner_and_parser(){
	bicmd = 0;
	builtin = 0;
	//set to null
	bistr = '\0';
}





void recover_from_errors()
{ 	
	//Find out if error occurs in middle of command 
	//That is the command still has a “tail”
	//In this case you have to recover by “eating” 
	// the rest of the command.
	// To do this: use yylex() directly.
	printf("recover_from_errors");
}

void processCommand()
{	
	// if (builtin) 
	// 	do_it();
	// else
	// 	execute_it();	
	
	printf("processCommand\n");
	printf("bicmd: %d", bicmd);
	printf("builtin: %d", builtin);

	if(builtin)
		do_it();	
}



void do_it(){
	switch(bicmd){
		case CDX :
			changedir(bistr);
			break;
		case CDHOME :
			gohome();
			break;
		case PRINTENV :
			printEnv();
			break;
		case BYE :
			exit(1);
			break;
	}
}



void changedir(char *s){
	if(chdir(s) == -1){
		printf("%s: ", s);
		printf("not a directory");
		return;
	}
}


void gohome(){
	chdir(getenv("HOME"));
}

void printEnv(){
	for (char **env = environ; *env; ++env)
        printf("%s\n", *env);
}
