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

void command(char *cmd) {
    int result = system(cmd);
    if (result == 0) printf("success: %s\n", cmd);
    else printf("fail: %s\n", cmd);
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

void executeOptimizedTranspiler(char *program, char *input, int *optimization, int optimization_count) {
    char cmd_string[1024];
    strcpy(cmd_string, "optimizedTranspiler.exe ");
    strcat(cmd_string, program);
    for (int i = 0; i < optimization_count; i++)
    {
        char op[2];
        sprintf(op," %d",optimization[i]);
        strcat(cmd_string, op);
    }
    command(cmd_string);

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
    command(cmd_string);

    /*Running transpiled executable*/
    strcpy(cmd_string, token);
    strcat(cmd_string, optimization_string);
    strcat(cmd_string, ".exe");
    strcat(cmd_string, " ");
    strcat(cmd_string, input);
    command(cmd_string);

    /*Returning to programs folder*/
    changeDir("..");
    changeDir("Programs");
}

int main()
{
    compilePrograms();
    int optimization_count = 5;
    int optimizations[optimization_count];
    memset(optimizations,0,optimization_count*sizeof(int));
    executeOptimizedTranspiler("HelloWorld.txt", "", optimizations, optimization_count);
    
    executeTranspiler("HelloWorld.txt", "");

    executeInterpretor("HelloWorld.txt", "");

    return 0;
}