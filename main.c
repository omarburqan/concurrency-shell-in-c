#include<stdio.h> 
#include<string.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<sys/wait.h> 

#define MAX 100
#define SPACES 10
void init_shell() 
{ 
	char* username = getenv("USER"); 
    printf("\n\n\n\n******************"
        "************************"); 
    printf("\n\n\n\t****MY SHELL****"); 
    printf("\n\n\t-USE AT YOUR OWN RISK-"); 
    printf("\n\n\n\n*******************"
        "***********************"); 
    printf("\n\n\nUSER is: @%s", username); 
    printf("\n"); 
} 

void parseInput(char* str, char *parsed[])
{
	int i = 0;
	char *found;
    while( (found = strsep(&str," ")) != NULL ){
		parsed[i++] = found;
	}
}

void execArgs(char *input[]) 
{ 
    pid_t pid = fork();  
    if (pid == -1) { 
        printf("\nFailed forking child.."); 
        return; 
    } else if (pid == 0) { 
     	if (execvp(input[0],input) < 0) { 
            printf("\nCould not execute command.."); 
        } 
        exit(0); 	
    } else { 
        wait(NULL);  
        return; 
    } 
}

int main(){
	char input[MAX];
	init_shell();
	printf( "Enter a Command :\n");
	while(1){
		printf(">>>");
   		fgets(input, MAX, stdin); 
    	input[strlen(input)-1] = '\0';
    	char *result[SPACES];
    	parseInput(input,result); 
   		if( strcmp(result[0],"exit") == 0 )
   			break;
		execArgs(result);
		printf("\n");
	}
	return 0;
}
