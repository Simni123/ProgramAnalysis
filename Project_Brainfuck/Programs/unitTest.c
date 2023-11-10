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
    char cmd_string[sizeof("interpreter.exe") + sizeof(program) + sizeof(input) + 2];
    strcpy(cmd_string, "interpreter.exe ");
    strcat(cmd_string, program);
    strcat(cmd_string, " ");
    strcat(cmd_string, input);
    printf("cmd: %s\n",cmd_string);
    command(cmd_string);
}

int main()
{
    compilePrograms();
    executeInterpretor("test1.txt", "bha");

    /*
    const char *command1 = "gcc optimizedTranspiler.c -o optrans";
    const char *command2 = "dir";
    const char *command3 = "optrans.exe BubbleSourt.txt 0 0 0 0 0";
    const char *command4 = "dir";
    const char *command5 = "dir";
    const char *command6 = "gcc BubbleSourt[00000].c -o BubbleSourt[00000]";
    const char *command7 = "BubbleSourt[00000].exe zzbaab";

    int result;

    result = system(command1);
    if (result == 0) printf("success: cmd1\n");
    else printf("fail: cmd1\n");

    result = system(command2);
    if (result == 0) printf("success cmd2\n");
    else printf("fail: cmd2\n");

    result = system(command3);
    if (result == 0) printf("success cmd3\n");
    else printf("fail: cmd3\n");

    changeDir("..");
    
    result = system(command4);
    if (result == 0) printf("success cmd3\n");
    else printf("fail: cmd3\n");

    changeDir("OptimizedTranspiling");
    
    result = system(command5);
    if (result == 0) printf("success cmd3\n");
    else printf("fail: cmd3\n");

    result = system(command6);
    if (result == 0) printf("success cmd3\n");
    else printf("fail: cmd3\n");
    */

    return 0;
}




/*
#include <stdio.h>
#include <stdlib.h>

int main()
{
    //const char *command1 = "gcc optimizedTranspiler.c -o optrans";
    //const char *command2 = "./optrans.exe BubbleSourt.txt 0 0 0 0 0";
    const char *command1 = "dir";
    const char *command2 = "cd ..";
    //const char *command5 = "gcc BubbleSourt[00000].c";
    //const char *command6 = "./a.exe hello";
    const char *command3 = "dir";
    const char *command4 = "cd ..";
    const char *command5 = "dir";
    
    
    
    int result = system(command1);
    if (result == 0) printf("success: cmd1\n");
    else printf("fail: cmd1\n");
    result = system(command2);
    if (result == 0) printf("success cmd2\n");
    else printf("fail: cmd2\n");
    result = system(command3);
    if (result == 0) printf("success cmd3\n");
    else printf("fail: cmd3\n");
    result = system(command4);
    if (result == 0) printf("success cmd4\n");
    else printf("fail: cmd4\n");
    result = system(command5);
    if (result == 0) printf("success cmd5\n");
    else printf("fail: cmd5\n");
    
    return 0;
}
*/
