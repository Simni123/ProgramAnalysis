#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
    #include <Windows.h>
#endif

void changeDir(char *dir) {
    // Change working directory (Windows)
    #ifdef _WIN32
    SetCurrentDirectory(dir);
    #endif
}

int command(char *cmd) {
    int result = system(cmd);
    if (result == 0) printf("success: %s\n", cmd);
    else printf("fail: %s\n", cmd);
    return result;
}

void compilePrograms() {
    command("gcc optimizedTranspiler.c -o optimizedTranspiler");
    command("gcc transpiler.c -o transpiler");
    command("gcc interpreter.c -o interpreter");
}

void executeInterpretor(char *program, char *input) {
    char cmd_string[sizeof("interpreter.exe ") + sizeof(program) + sizeof(input) + 1];
    strcpy(cmd_string, "interpreter.exe ");
    strcat(cmd_string, program);
    strcat(cmd_string, " ");
    strcat(cmd_string, input);
    command(cmd_string);
}

void executeTranspiler(char *program, char *input) {
    char cmd_string[1024];
    strcpy(cmd_string, "transpiler.exe ");
    strcat(cmd_string, program);
    command(cmd_string);

    /*Changing directory to NaiveTranspiling*/
    changeDir("..");
    changeDir("NaiveTranspiling");

    /*Creating a subfile name without .type*/
    char file_name_sub[1024]; //WTF whry *2 - find out
    strcpy(file_name_sub, program);
    const char deli[] = ".";
    char *token;
    token = strtok(file_name_sub, deli);

    /*Compiling tranpiled file*/
    strcpy(cmd_string, "gcc ");
    strcat(cmd_string, token);
    strcat(cmd_string, ".c -o ");
    strcat(cmd_string, token);
    command(cmd_string);

    /*Running transpiled executable*/
    strcpy(cmd_string, token);
    strcat(cmd_string, ".exe");
    strcat(cmd_string, " ");
    strcat(cmd_string, input);
    command(cmd_string);

    /*Returning to programs folder*/
    changeDir("..");
    changeDir("Programs");
}

int executeOptimizedTranspiler(char *program, char *input, int *optimization, int optimization_count) {
    int fail = 0;
    char cmd_string[1024];
    strcpy(cmd_string, "optimizedTranspiler.exe ");
    strcat(cmd_string, program);
    for (int i = 0; i < optimization_count; i++)
    {
        char op[2];
        sprintf(op," %d",optimization[i]);
        strcat(cmd_string, op);
    }
    fail = max(command(cmd_string),fail);
    
    /*Changing directory to NaiveTranspiling*/
    changeDir("..");
    changeDir("OptimizedTranspiling");

    /*Creating a subfile name without .type*/
    char file_name_sub[1024]; //WTF whry *2 - find out
    strcpy(file_name_sub, program);
    const char deli[] = ".";
    char *token;
    token = strtok(file_name_sub, deli);

    /*Extracting optimization string*/
    char optimization_string[optimization_count+2];
    strcpy(optimization_string, "[");
    for (int i = 0; i < optimization_count; i++)
    {
        char op[2];
        sprintf(op,"%d",optimization[i]);
        strcat(optimization_string, op);
    }
    strcat(optimization_string, "]");

    /*Compiling tranpiled file*/
    strcpy(cmd_string, "gcc ");
    strcat(cmd_string, token);
    strcat(cmd_string, optimization_string);
    strcat(cmd_string, ".c -o ");
    strcat(cmd_string, token);
    strcat(cmd_string, optimization_string);
    fail = max(command(cmd_string),fail);

    /*Running transpiled executable*/
    strcpy(cmd_string, token);
    strcat(cmd_string, optimization_string);
    strcat(cmd_string, ".exe");
    strcat(cmd_string, " ");
    strcat(cmd_string, input);
    fail = max(command(cmd_string),fail);

    /*Returning to programs folder*/
    changeDir("..");
    changeDir("Programs");
    return fail;
}

void executeAllOptimizedTranspilers(char *program, char *input) {
    int optimization_count = 5;
    int optimizations[optimization_count];
    int idx = 0;
    memset(optimizations,0,optimization_count*sizeof(int));

    while (1)
    {
        int fail = 1;
        while (fail)
        {
            fail = executeOptimizedTranspiler(program, input, optimizations, optimization_count);
        }
        
        //generate new binary number
        int carry = 1;
        int i = optimization_count-1;

        while (i >= 0 && carry)
        {
            if (optimizations[i] == 1) optimizations[i] = 0;
            else {optimizations[i] = 1; carry = 0;}
            i--; 
        }
        if (carry) break;
    }
}

void allTest(char *program, char *input) {
    executeTranspiler(program, input);

    executeInterpretor(program, input);

    executeAllOptimizedTranspilers(program, input);
}

int main()
{
    compilePrograms();

    allTest("HelloWorld.txt", "");
    allTest("BubbleSourt.txt", "baabz");
    allTest("Squares.txt", "");
    return 0;
}