#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

FILE *openFile(char *folder_path, char *file_name)
{
    DIR *folder = opendir(folder_path);
    FILE *b_program;
    struct dirent *entry;

    if (folder == NULL)
    {
        puts("Folder not found error\n");
        return NULL;
    }

    while ((entry = readdir(folder)))
    {
        /*Skippin the directory reference files*/
        if (!strcmp(entry->d_name, ".") || !strcmp(entry->d_name, ".."))
            continue;

        /*OPening only wanted file*/
        if (!strcmp(entry->d_name, file_name))
        {
            /*Concatinating the relative file directory string*/
            char file_path[1024];
            strcpy(file_path, folder_path);
            strcat(file_path, "/");
            strcat(file_path, entry->d_name);

            /*Opening the file to read it*/
            b_program = fopen(file_path, "r");
            if (b_program != NULL)
            {
                closedir(folder);
                return b_program;
            }
            else
            {
                closedir(folder);
                return NULL;
            }
        }
    }

    return NULL;
}

FILE *createFile(char *file_path, char *file_name, char *optimization, int optimization_count)
{
    /*Creating a subfile name without .type*/
    char file_name_sub[1024]; // WTF whry *2 - find out
    strcpy(file_name_sub, file_name);
    const char deli[] = ".";
    char *token;
    token = strtok(file_name_sub, deli);

    /*adding the optimization string on the file*/
    char optimization_string[1024];
    strcpy(optimization_string, "[");
    for (int i = 0; i < optimization_count; i++)
    {
        char op[2];
        sprintf(op, "%d", optimization[i]);
        strcat(optimization_string, op);
    }
    strcat(optimization_string, "]");

    /*Concatinating the file name to a c file*/
    char transpiled_file_name[1024];
    strcpy(transpiled_file_name, token);
    strcat(transpiled_file_name, optimization_string);
    strcat(transpiled_file_name, ".c");

    /*Concatinating to the path of storage*/
    char transpiled_file_path[1024];
    strcpy(transpiled_file_path, file_path);
    strcat(transpiled_file_path, "/");
    strcat(transpiled_file_path, transpiled_file_name);

    FILE *tFile = fopen(transpiled_file_path, "w+");
    if (tFile == NULL)
    {
        printf("Could not create file\n");
        return NULL;
    }

    return tFile;
}

int fsize(FILE *fp)
{
    int prev = ftell(fp);
    fseek(fp, 0L, SEEK_END);
    int sz = ftell(fp);
    fseek(fp, prev, SEEK_SET); // go back to where we were
    return sz;
}

void initFile(FILE *transpiled, char *file_name, char *optimization, int optimization_count, int time_measures)
{
    fprintf(transpiled, "#include <stdio.h>\n");
    fprintf(transpiled, "#include <dirent.h>\n");
    fprintf(transpiled, "#include <string.h>\n");
    fprintf(transpiled, "#include <time.h>\n");
    fprintf(transpiled, "#include <math.h>\n");
    fprintf(transpiled, "#include <stdlib.h>\n");
    fprintf(transpiled, "#include <ctype.h>\n");
    fprintf(transpiled, "\n");
    fprintf(transpiled, "\n");

    /*Adding method to write the result to file in the transpiled file*/
    fprintf(transpiled, "FILE* createFile(char *file_path, char *file_name) {\n");
    fprintf(transpiled, "DIR *transpiled_folder = opendir(file_path);\n");
    fprintf(transpiled, "\n");
    fprintf(transpiled, "/*Creating a subfile name without .type*/\n");
    fprintf(transpiled, "char file_name_sub[1024];\n");
    fprintf(transpiled, "strcpy(file_name_sub, file_name);\n");
    fprintf(transpiled, "const char deli[] = \".\";\n");
    fprintf(transpiled, "char *token;\n");
    fprintf(transpiled, "token = strtok(file_name_sub, deli);\n");
    fprintf(transpiled, "\n");
    fprintf(transpiled, "/*adding the optimization string on the file*/\n");
    fprintf(transpiled, "char optimization_string[256];\n", optimization_count);
    fprintf(transpiled, "strcpy(optimization_string, \"[\");\n");
    for (int i = 0; i < optimization_count; i++)
    {
        fprintf(transpiled, "strcat(optimization_string, \"%d\");\n", optimization[i]);
    }
    fprintf(transpiled, "strcat(optimization_string, \"]\");\n");
    fprintf(transpiled, "/*Concatinating the file name to a txt file*/\n");
    fprintf(transpiled, "char transpiled_file_name[1024];\n");
    fprintf(transpiled, "strcpy(transpiled_file_name, token);\n");
    fprintf(transpiled, "strcat(transpiled_file_name, optimization_string);\n");
    fprintf(transpiled, "strcat(transpiled_file_name, \".txt\");\n");
    fprintf(transpiled, "\n");
    fprintf(transpiled, "/*Concatinating to the path of storage*/\n");
    fprintf(transpiled, "char transpiled_file_path[1024];\n");
    fprintf(transpiled, "strcpy(transpiled_file_path, file_path);\n");
    fprintf(transpiled, "strcat(transpiled_file_path, \"/\");\n");
    fprintf(transpiled, "strcat(transpiled_file_path, transpiled_file_name);\n");
    fprintf(transpiled, "\n");
    fprintf(transpiled, "FILE *tFile = fopen(transpiled_file_path, \"w+\");\n");
    fprintf(transpiled, "if (tFile == NULL) { printf(\"Could not create file\\n\"); return NULL;}\n");
    fprintf(transpiled, "return tFile;\n");
    fprintf(transpiled, "}\n");

    /*adding main method*/
    fprintf(transpiled, "int main (int argc, char **argv) {\n");
    //testing correct input
    fprintf(transpiled, "if (argc != 5) {\n");
    fprintf(transpiled, "printf(\"the interpretor need exactly 'result_folder_in_UnitTestFiles input_string(non-empty use \" \" as empty) time_mesurements repetitions_per_time_mesurement'\\n\");\n");
    fprintf(transpiled, "return -1;}\n");
    //Creating new file to store result
    fprintf(transpiled, "char result_folder_path[1024];\n");
    fprintf(transpiled, "strcpy(result_folder_path, \"../UnitTestFiles/\");\n");
    fprintf(transpiled, "strcat(result_folder_path, argv[1]);\n");
    fprintf(transpiled, "FILE *result_file = createFile(result_folder_path,\"%s\");\n", file_name);
    //exstracting brainfuck input
    fprintf(transpiled, "int input_pointer = 0;\n");
    fprintf(transpiled, "char *input;\n");
    fprintf(transpiled, "int input_len = 0;\n");
    fprintf(transpiled, "input = argv[2];\n");
    fprintf(transpiled, "input_len = strlen(input);\n");
    fprintf(transpiled, "fprintf(result_file, \"Input: \");\n");
    fprintf(transpiled, "fprintf(result_file, input);\n");
    fprintf(transpiled, "fprintf(result_file, \"\\n\");\n");
    //exstracting timer options
    fprintf(transpiled, "int time_reps = 0;\n");
    fprintf(transpiled, "int time_mesures = 0;\n");
    fprintf(transpiled, "time_mesures = atoi(argv[3]);\n");
    fprintf(transpiled, "time_reps = atoi(argv[4]);\n");
    //initializying brinfuck invironment
    fprintf(transpiled, "const int cellCount = 500;\n");
    fprintf(transpiled, "unsigned char cells[cellCount];\n");
    fprintf(transpiled, "memset(cells, 0, cellCount*sizeof(char));\n");
    fprintf(transpiled, "int idx = 0;\n");
    fprintf(transpiled, "int outputLimit = 16384;\n");
    fprintf(transpiled, "unsigned char output[outputLimit];\n");
    fprintf(transpiled, "memset(output, 0, outputLimit*sizeof(char));\n");
    fprintf(transpiled, "int outputIdx = 0;\n");
}

void transpiler(char *file_string, const int file_size, FILE *transpiled, char *optimization)
{
    //initializing timer loops
    fprintf(transpiled, "double all_times[time_mesures];\n");
    fprintf(transpiled, "for (size_t t = 0; t < time_mesures; t++){\n");
    fprintf(transpiled, "clock_t start_time, end_time;\n");
    fprintf(transpiled, "start_time = clock();\n");
    fprintf(transpiled, "for (int k = 0; k < time_reps; k++) {\n");
    //reinitializing brainfuck invironment
    fprintf(transpiled, "input_pointer = 0;\n");
    fprintf(transpiled, "memset(cells, 0, cellCount*sizeof(char));\n");
    fprintf(transpiled, "idx = 0;\n");
    fprintf(transpiled, "memset(output, 0, outputLimit*sizeof(char));\n");
    fprintf(transpiled, "outputIdx = 0;\n");
    
    /*Runnning through program*/
    for (int i = 0; i < file_size; i++)
    {
        char symbol = (char)file_string[i];
        int c = 0;
        int tempi = i;

        /*Level 3 Simple loop optimizations*/
        // if no sub loops, no input/output, all increments/decrements of P[start] add up to -1, we are running the loop body p[0] times
        if (optimization[3] && symbol == '[') //(0) // change to 0
        {
            // WE HAVE A BUG!!!! - use gcc .\optimizedTranspiler.c -> ./a.exe Mandelbrot.txt 0 0 0 1 0 too see it when gcc .\Mandelbrot[00010].c -> ./a.exe O0 " " 1 1
            // Incrementing so we dont look at the start bracket.
            i++;
            symbol = (char)file_string[i];

            // printf("Testing Loop Optimization\n");
            int p_start_change = 0;
            char applicable = 1;
            int movements = 0;

            int multiplier_index = 0;
            int multiplier_movements[1000];
            unsigned char multipliers[1000];
            memset(multipliers, 0, 1000 * sizeof(char));
            memset(multiplier_movements, 0, 1000 * sizeof(int));
            while (symbol != ']')
            {
                // Optimization not applicable with subloops, input/output
                if (symbol == '[' || symbol == ',' || symbol == '.')
                {
                    applicable = 0;
                    break;
                }

                // All movements must add up to 0
                if (symbol == '>')
                    movements++;
                if (symbol == '<')
                    movements--;

                if (symbol == '-' && movements == 0)
                    p_start_change--;
                if (symbol == '+' && movements == 0)
                    p_start_change++;

                // Optimizing increments in loop
                while ((symbol == '+' || symbol == '-') && movements != 0)
                {
                    if (symbol == '+')
                        multipliers[multiplier_index]++;
                    else
                        multipliers[multiplier_index]--;

                    i++;
                    symbol = (char)file_string[i];
                }
                if (multipliers[multiplier_index] != 0)
                {
                    multiplier_movements[multiplier_index] = movements;
                    multiplier_index++;
                    if (multiplier_index > 1000) printf("insufficent multiplier_movements array size");
                    // rerole symbol after while loop fence problem
                    i--;
                    symbol = (char)file_string[i];
                }

                i++;
                symbol = (char)file_string[i];
            }

            if (!applicable || p_start_change != -1 || movements != 0)
            {
                // printf("Loop optimization not applicable");
                i = tempi;
                symbol = (char)file_string[i];
                c = 0;
            }
            else
            {
                // printf("Loop optimization applied");
                fprintf(transpiled, "/*Starting loop optimization*/\n");
                for (int j = 0; j < multiplier_index; j++)
                {
                    fprintf(transpiled, "if(idx+%d < 0 || idx+%d > cellCount) {printf(\"insufficient cell count - multiplier movement %d\\n\"); return -1;} \n", multiplier_movements[j], multiplier_movements[j], multiplier_movements[j]);
                    fprintf(transpiled, "cells[idx+%d] += %d*cells[idx]; \n", multiplier_movements[j], multipliers[j]);
                }
                fprintf(transpiled, "cells[idx] = 0;\n");
                fprintf(transpiled, "/*end loop optimization*/\n");

                // skipping ']' at end of loop
                i++;
                symbol = (char)file_string[i];

                // updating current tempi
                tempi = i;
            }
        } // end of optimization 3

        /*Level 2 Optimizations >++< -> cells[xxx]+=xxx;, cells[xxx]-=xxx; */
        if (optimization[2] && (symbol == '>' || symbol == '<' || symbol == '+' || symbol == '-')) //(0) //change to 0 for base result generation with unitTest.c
        {
            // New level 2 optimizations

            // Making an array doubled
            int cIdx = 500 - 1;
            int currentArray[500 * 2];                  // change to cell count
            memset(currentArray, 0, 1000 * sizeof(int)); // chnage to cell count

            while (symbol == '>' || symbol == '<' || symbol == '+' || symbol == '-')
            {
                if (cIdx < 0 || cIdx > 999)
                {
                    printf("non compilable brainfuck program");
                    return;
                }

                if (symbol == '+')
                    currentArray[cIdx] += 1;
                else if (symbol == '-')
                    currentArray[cIdx] += -1;
                else if (symbol == '>')
                    cIdx++;
                else
                    cIdx--;

                i++;
                symbol = (char)file_string[i];
            }
            i--;
            fprintf(transpiled, "/*Starting combined level 2 optimization*/\n");
            for (int j = 0; j < 500 * 2; j++)
            {
                if (currentArray[j] != 0)
                {
                    fprintf(transpiled, "if(idx+(%d) < 0 || idx+(%d) > cellCount) {printf(\"insufficient cell count - currentArray\"); return -1;} \n", j - 499, currentArray[j]);
                    fprintf(transpiled, "cells[idx+(%d)] = cells[idx+(%d)]+(%d); \n", j - 499, j - 499, currentArray[j]);
                }
            }
            if (cIdx != 499)
            {

                fprintf(transpiled, "idx += (%d);\n", cIdx - 499);
                fprintf(transpiled, "if(idx > cellCount && idx < 0) {");
                fprintf(transpiled, "printf(\"insufficient cellcount\"); return -1;}\n");
            }

            fprintf(transpiled, "/*Ending combined level 2 optimization*/\n");

            c = 0;
            symbol = (char)file_string[i];
            // Resetting initializations for the rest to run correctly
            continue;
        } // end of optimization level 2

        /*Level 0-1 optimizations + nonOptimized parts*/
        switch (symbol)
        {
        case '-':
        case '+':
            if (optimization[0]) //(0) //change to 0 for base result generation with unitTest.c
            {
                while (symbol == '+' || symbol == '-')
                {
                    if (symbol == '+')
                        c++;
                    else
                        c--;
                    i++;
                    symbol = (char)file_string[i];
                }
                i--;
                fprintf(transpiled, "/*Starting adding optimization*/\n");
                fprintf(transpiled, "cells[idx]+=(%d);\n", c);
                fprintf(transpiled, "/*ending adding optimization*/\n");
            }
            else
            {
                if (symbol == '+') fprintf(transpiled, "cells[idx]++;\n");
                else fprintf(transpiled, "cells[idx]--;\n");
            }

            break;

        case '>':
        case '<':
            if (optimization[1]) //(0) //change to 0 for base result generation with unitTest.c
            {
                while (symbol == '>' || symbol == '<')
                {
                    if (symbol == '>')
                        c++;
                    else
                        c--;
                    i++;
                    symbol = (char)file_string[i];
                }
                i--;
                fprintf(transpiled, "/*Starting right move level 1 optimization*/\n");
                fprintf(transpiled, "idx+=(%d);\n", c);
                fprintf(transpiled, "/*Ending right move level 1 optimization*/\n");
            }
            else
            {
                if (symbol == '>') fprintf(transpiled, "idx++;\n");
                else fprintf(transpiled, "idx--;\n");
            }

            fprintf(transpiled, "if(idx > cellCount && idx < 0) {");
            fprintf(transpiled, "printf(\"insufficient cellcount\"); return -1;}\n");

            break;

        case ',':
            fprintf(transpiled, "if (input_pointer <= 255) {\n");
            fprintf(transpiled, "cells[idx] = input[input_pointer];\n");
            fprintf(transpiled, "input_pointer++;\n");
            fprintf(transpiled, "} else {\n");
            fprintf(transpiled, "printf(\"Insufficient input length\"); return -1;}\n");
            break;

        case '.':
            fprintf(transpiled, "if(outputIdx > outputLimit) {printf(\"insuficient output length: %d\\n \", outputIdx); return -1;}\n");
            fprintf(transpiled, "output[outputIdx] = cells[idx];\n");
            fprintf(transpiled, "outputIdx++;\n");
            break;

        case '[':
            fprintf(transpiled, "while (cells[idx] != 0) {\n");
            break;

        case ']':
            fprintf(transpiled, "}\n");
            break;

        default:
            // Skip
            break;
        }
    }
    //ending timer loops
    fprintf(transpiled, "} //end of rep_per_time_mesure\n");
    fprintf(transpiled, "end_time = clock();\n");
    fprintf(transpiled, "printf(\"start-end time: %%f, %%f\\n\", (double) start_time/CLOCKS_PER_SEC, (double) end_time/CLOCKS_PER_SEC);\n");
    fprintf(transpiled, "all_times[t] = ((double)(end_time - start_time) / CLOCKS_PER_SEC) / (double) time_reps;\n");
    fprintf(transpiled, "all_times[t] = log(all_times[t]);\n");
    fprintf(transpiled, "} //end of mesurements\n");

    //exstract results
    fprintf(transpiled, "fprintf(result_file, \"Output: \");\n");
    fprintf(transpiled, "for (int i = 0; i < outputIdx; i++){\n");
    fprintf(transpiled, "fprintf(result_file,\"%%c\", (char) output[i]);\n");
    fprintf(transpiled, "}\n");
    fprintf(transpiled, "fprintf(result_file, \"\\n\");\n");
    fprintf(transpiled, "fprintf(result_file, \"Result:\");\n");
    fprintf(transpiled, "for (int i = 0; i < cellCount ; i++){\n");
    fprintf(transpiled, "if (i%%10 == 0) fprintf(result_file, \"\\n\");\n");
    fprintf(transpiled, "fprintf(result_file, \"[%%d]\",cells[i]);\n");
    fprintf(transpiled, "}\n");
    
    //exstracting time mesurements
    fprintf(transpiled, "if (time_reps != 1 || time_mesures != 1) {\n");
    fprintf(transpiled, "double sum_time = 0;\n");
    fprintf(transpiled, "fprintf(result_file, \"\\nTimes: \");\n");
    fprintf(transpiled, "for (int i = 0; i < time_mesures; i++){\n");
    fprintf(transpiled, "fprintf(result_file, \"%%f, \", all_times[i]);\n");
    fprintf(transpiled, "sum_time += all_times[i];}\n");
    fprintf(transpiled, "double mean_time = sum_time / (double)time_mesures;\n");
    fprintf(transpiled, "fprintf(result_file, \"\\nMean: %%f\", mean_time);\n");
    
    //exstracing std
    fprintf(transpiled, "double std = 0;\n");
    fprintf(transpiled, "for (int i = 0; i < time_mesures; i++){\n");
    fprintf(transpiled, "std += pow(all_times[i] - mean_time, 2);}\n");
    fprintf(transpiled, "std = sqrt(std / time_mesures);\n");
    fprintf(transpiled, "fprintf(result_file, \" +- %%f dBs\", std);\n");
    fprintf(transpiled, "}"); // end of if repeate
    
    fprintf(transpiled, "}"); // end of main
    fclose(transpiled);
}

int main(int argc, char **argv)
{
    
    char *program_folder_path = "../BrainFuck_Programs";
    int time_measurements = 10;

    /*Loading in file*/
    char *file_name = argv[1];
    FILE *b_program = openFile(program_folder_path, file_name);
    if (b_program == NULL)
    {
        printf("File not found\n");
        return -1;
    }
    const int file_size = fsize(b_program);

    /*Reading file to string*/
    char file_string[file_size];
    strcpy(file_string, "");
    const unsigned MAX_LENGTH = 256;
    char buffer[MAX_LENGTH];
    while (fgets(buffer, MAX_LENGTH, b_program))
        strcat(file_string, buffer);
    fclose(b_program);

    /*Parsing optimization options*/
    int optimization_count = 5;
    // Testing option validity
    if (argc != optimization_count + 2)
    {
        printf("You must parse exactly '(Brain_fuck_program) (5 optimization option numbers {1;0} for each number)'");
        return -1;
    }
    for (int i = 2; i < argc; i++) // testing the input is numbers 0,1
    {
        char *endptr;
        long num = strtol(argv[i], &endptr, 10);
        if (*endptr == '\0' && num >= 0 && num <= 1)
            continue;
        printf("All optimization options must be 0 or 1 error: input %d is %s", i - 2, argv[i]);
        return -1;
    }

    // Parsing options
    char optimizations[optimization_count];
    optimizations[0] = atoi(argv[2]);
    for (int i = 3; i < argc; i++)
    {
        optimizations[i - 2] = atoi(argv[i]);
    }

    /*Creating new file to transpile into*/
    char *transpiled_folder_path = "../OptimizedTranspiling";
    FILE *tranpiled_file = createFile(transpiled_folder_path, file_name, optimizations, optimization_count);
    initFile(tranpiled_file, file_name, optimizations, optimization_count, time_measurements); // initializing file methods

    /*Starting the transpiler*/
    transpiler(file_string, file_size, tranpiled_file, optimizations);

    return 0;
}