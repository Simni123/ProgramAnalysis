#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    command("gcc interpreter.c -o interpreter");
}

void executeInterpretor(char *program, char *input, int time_measures, int time_reps) {
    char cmd_string[1024];
    //passing time options to string
    char time_measures_str[512];
    char time_reps_str[512];
    sprintf(time_measures_str, "%d", time_measures);
    sprintf(time_reps_str, "%d", time_reps);

    //collecting command
    strcpy(cmd_string, "interpreter.exe ");
    strcat(cmd_string, program);
    strcat(cmd_string, " ");
    strcat(cmd_string, " \"");
    strcat(cmd_string, input);
    strcat(cmd_string, "\" ");
    strcat(cmd_string, " ");
    strcat(cmd_string, time_measures_str);
    strcat(cmd_string, " ");
    strcat(cmd_string, time_reps_str);
    command(cmd_string);
}

int executeOptimizedTranspiler(char *program, char *input, int *optimization, int optimization_count, int time_measures, int time_reps, char compiler) {
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

    //adding compiler option
    char compiler_str[4];
    if (compiler) strcpy(compiler_str, "O3");
    else strcpy(compiler_str, "O0");
    /*Compiling tranpiled file*/
    //Todo: add optimiation -O0 or -O3
    strcpy(cmd_string, "gcc ");
    strcat(cmd_string, token);
    strcat(cmd_string, optimization_string);
    strcat(cmd_string, ".c -");
    strcat(cmd_string, compiler_str);
    strcat(cmd_string, " -o ");
    strcat(cmd_string, token);
    strcat(cmd_string, optimization_string);
    fail = max(command(cmd_string),fail);

    //passing time options to string
    char time_measures_str[512];
    char time_reps_str[512];
    sprintf(time_measures_str, "%d", time_measures);
    sprintf(time_reps_str, "%d", time_reps);

    /*Running transpiled executable*/
    strcpy(cmd_string, token);
    strcat(cmd_string, optimization_string);
    strcat(cmd_string, ".exe");
    strcat(cmd_string, " ");
    if (time_measures == 1 || time_reps == 1) strcat(cmd_string, "UnitTest"); //Saving no times only result in UnitTest folder
    else if ((optimization[0] != 0 || optimization[1] != 0 || optimization[2] != 0 || optimization[3] != 0 || optimization[4] != 0)) strcat(cmd_string, "Optimized"); //saving the optimized time
    else strcat(cmd_string, compiler_str); //saving times in O0/O3 folder
    strcat(cmd_string, " ");
    strcat(cmd_string, " \"");
    strcat(cmd_string, input);
    strcat(cmd_string, "\" ");
    strcat(cmd_string, " ");
    strcat(cmd_string, time_measures_str);
    strcat(cmd_string, " ");
    strcat(cmd_string, time_reps_str);
    fail = max(command(cmd_string),fail);

    /*Returning to programs folder*/
    changeDir("..");
    changeDir("Programs");
    return fail;
}

void executeAllOptimizedTranspilers(char *program, char *input, int time_measures, int time_reps) {
    int optimization_count = 5;
    int optimizations[optimization_count];
    int idx = 0;
    memset(optimizations,0,optimization_count*sizeof(int));

    while (1)
    {
        int fail = 1;
        while (fail)
        {
            fail = executeOptimizedTranspiler(program, input, optimizations, optimization_count, time_measures, time_reps, 0);
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

void executeDataCollector(char *program, char *input, int time_measures, int interpret_time_reps){
    executeInterpretor(program, input, time_measures, interpret_time_reps);

    int optimization_count = 5;
    int optimizations[optimization_count];
    int idx = 0;
    memset(optimizations,0,optimization_count*sizeof(int));
    //Optimized O0
    for (int i = 0; i < optimization_count; i++)
    {
        optimizations[i] = 1;
    }

    int fail = 1;
    while (fail)
    {
        fail = executeOptimizedTranspiler(program, input, optimizations, optimization_count, time_measures, interpret_time_reps*10, 0);
    }

    //NonOptimized O0
    memset(optimizations,0,optimization_count*sizeof(int));
    fail = 1;
    while (fail)
    {
        fail = executeOptimizedTranspiler(program, input, optimizations, optimization_count, time_measures, interpret_time_reps*10, 0);
    }
    
    //NonOptimized O3
    memset(optimizations,0,optimization_count*sizeof(int));
    fail = 1;
    while (fail)
    {
        fail = executeOptimizedTranspiler(program, input, optimizations, optimization_count, time_measures, interpret_time_reps*10, 1);
    }

}

void allTest(char *program, char *input, int time_measures, int interpret_time_reps) {
    executeAllOptimizedTranspilers(program, input, 1, 1);

    executeDataCollector(program, input, time_measures, interpret_time_reps);
}

int main()
{
    compilePrograms();

    allTest("HelloWorld.txt", " ", 10, 100000);
    //allTest("BubbleSourt.txt", "baabz", 10, 10000);
    allTest("BubbleSourt.txt", "this will be sorted", 10, 1000);
    allTest("Squares.txt", " ", 10, 1000);
    //allTest("Mandelbrot.txt", " ", 10, 1); //Encounters bug in optimization
    allTest("Serpinski.txt", " ", 10, 10000);
    allTest("99Bottles.txt", " ", 10, 1000);
    allTest("WriteInBrainfuck.txt", "this is a test", 10, 10000); //output out of bounds
    allTest("WrittenByBrainfuck.txt", " ", 10, 10000); //output out of bounds
    allTest("CountInput.txt", "this text has 65 bytes\\n it has 14 words\\n moreover it has 3 lines\\n", 10, 10000);
    allTest("LargeShiftLoop.txt", " ", 10, 100000);
    allTest("LargeAddition.txt", " ", 10, 100000);
    
    return 0;
}