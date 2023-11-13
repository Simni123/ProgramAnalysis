#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <ctype.h>

FILE* openFile(char *folder_path, char *file_name) {
    DIR *folder = opendir(folder_path);
    FILE *b_program;
    struct dirent *entry;

    if (folder == NULL)
    {
        puts("Folder not found error\n");
        return NULL;
    } 

    while ((entry=readdir(folder)))
    {
        /*Skippin the directory reference files*/
        if (!strcmp(entry->d_name, ".") || !strcmp(entry->d_name, "..")) continue;

        /*OPening only wanted file*/
        if (!strcmp(entry->d_name,file_name))
        {
            /*Concatinating the relative file directory string*/
            char file_path[sizeof(folder_path)+sizeof(entry->d_name)+1];
            strcpy(file_path, folder_path);
            strcat(file_path, "/");
            strcat(file_path, entry->d_name);

            /*Opening the file to read it*/
            b_program = fopen(file_path, "r");
            if (b_program != NULL)
            {
                closedir(folder);
                return b_program;
            } else {
                closedir(folder);
                return NULL;
            }
        }
    }

    return NULL;
}

FILE* createFile(char *file_path, char *file_name, char *optimization, int optimization_count) {
    /*Creating a subfile name without .type*/
    char file_name_sub[sizeof(file_name)*2]; //WTF whry *2 - find out
    strcpy(file_name_sub, file_name);
    const char deli[] = ".";
    char *token;
    token = strtok(file_name_sub, deli);
    
    /*adding the optimization string on the file*/
    char optimization_string[optimization_count+2];
    strcpy(optimization_string, "[");
    for (int i = 0; i < optimization_count; i++)
    {
        char op[2];
        sprintf(op,"%d",optimization[i]);
        strcat(optimization_string, op);
    }
    strcat(optimization_string, "]");

    /*Concatinating the file name to a c file*/
    char transpiled_file_name[sizeof(token)+sizeof(optimization_string)+2];
    strcpy(transpiled_file_name, token);
    strcat(transpiled_file_name, optimization_string);
    strcat(transpiled_file_name, ".c");
    
    /*Concatinating to the path of storage*/
    char transpiled_file_path[sizeof(file_path)*2+sizeof(transpiled_file_name)+2]; //Why *2 again
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

int fsize(FILE *fp){
    int prev=ftell(fp);
    fseek(fp, 0L, SEEK_END);
    int sz=ftell(fp);
    fseek(fp,prev,SEEK_SET); //go back to where we were
    return sz;
}

void initFile(FILE* transpiled, char *file_name, char *optimization, int optimization_count) {
    fprintf(transpiled, "#include <stdio.h>\n");
    fprintf(transpiled, "#include <dirent.h>\n");
    fprintf(transpiled, "\n");
    fprintf(transpiled, "\n");

    /*Adding method to write the result to file in the transpiled file*/
    fprintf(transpiled, "FILE* createFile(char *file_path, char *file_name) {\n");
    fprintf(transpiled, "DIR *transpiled_folder = opendir(file_path);\n");
    fprintf(transpiled, "\n");
    fprintf(transpiled, "/*Creating a subfile name without .type*/\n");
    fprintf(transpiled, "char file_name_sub[sizeof(file_name)*2]; //WTF whry *2 - find out\n");
    fprintf(transpiled, "strcpy(file_name_sub, file_name);\n");
    fprintf(transpiled, "const char deli[] = \".\";\n");
    fprintf(transpiled, "char *token;\n");
    fprintf(transpiled, "token = strtok(file_name_sub, deli);\n");
    fprintf(transpiled, "\n");
    fprintf(transpiled, "/*adding the optimization string on the file*/\n");
    fprintf(transpiled, "char optimization_string[%d+2];\n", optimization_count);
    fprintf(transpiled, "strcpy(optimization_string, \"[\");\n");
    for (int i = 0; i < optimization_count; i++)
    {
        fprintf(transpiled, "strcat(optimization_string, \"%d\");\n", optimization[i]);
    }
    fprintf(transpiled, "strcat(optimization_string, \"]\");\n");
    fprintf(transpiled, "/*Concatinating the file name to a txt file*/\n");
    fprintf(transpiled, "char transpiled_file_name[sizeof(token)+sizeof(optimization_string)+2];\n");
    fprintf(transpiled, "strcpy(transpiled_file_name, token);\n");
    fprintf(transpiled, "strcat(transpiled_file_name, optimization_string);\n");
    fprintf(transpiled, "strcat(transpiled_file_name, \".txt\");\n");
    fprintf(transpiled, "\n");
    fprintf(transpiled, "/*Concatinating to the path of storage*/\n");
    fprintf(transpiled, "char transpiled_file_path[sizeof(file_path)*2+sizeof(transpiled_file_name)+2]; //Why *2 again\n");
    fprintf(transpiled, "strcpy(transpiled_file_path, file_path);\n");
    fprintf(transpiled, "strcat(transpiled_file_path, \"/\");\n");
    fprintf(transpiled, "strcat(transpiled_file_path, transpiled_file_name);\n");
    fprintf(transpiled, "\n");
    fprintf(transpiled, "FILE *tFile = fopen(transpiled_file_path, \"w+\");\n");
    fprintf(transpiled, "if (tFile == NULL) { printf(\"Could not create file\\n\"); return NULL;}\n");
    fprintf(transpiled, "return tFile;\n");
    fprintf(transpiled, "}\n");
    fprintf(transpiled, "\n");

    /*adding main method*/
    fprintf(transpiled, "int main (int argc, char **argv) {\n");
    fprintf(transpiled, "int input_pointer = 0;\n");
    fprintf(transpiled, "char *input;\n");
    fprintf(transpiled, "int input_len = 0;\n");
    fprintf(transpiled, "if (argc == 2) {input = argv[1]; input_len = strlen(input);}\n");
    fprintf(transpiled, "const int cellCount = 100;\n");
    fprintf(transpiled, "unsigned char cells[cellCount];\n");
    fprintf(transpiled, "memset(cells, 0, cellCount);\n");
    fprintf(transpiled, "int idx = 0;\n");
    
    /*Creating new file to transpile into*/
    fprintf(transpiled, "char *result_folder_path = \"../UnitTestFiles\";\n");
    fprintf(transpiled, "FILE *result_file = createFile(result_folder_path,\"%s\");\n", file_name);
    fprintf(transpiled, "fprintf(result_file,\"Output: \");\n");
}

void transpiler(char *file_string, const int file_size, FILE* transpiled, char *optimization) {
    
    /*Runnning through program*/
    for (int i = 0; i < file_size; i++)
    {   
        char symbol = (char) file_string[i];
        int c = 0;
        int tempi = i;
        
        /*Level 2 Optimizations cells[xxx]+=xxx;, cells[xxx]-=xxx; */
        if (optimization[2])
        {
            char optimizedString[5+2+4+3+2+3+3+73]; // cells[idx+xxx]+=xxx;\n

            //Counting the potential move fuse
            while (symbol == '>' || symbol == '<')
            {
                if (symbol == '>') c++;
                else c--;
                i++;
                symbol = (char) file_string[i];
            }
            int move_count = c;
            if (c < 0) move_count = -c;
            
            char subString[73];
            
            //Continuing only if movement was found
            if (c != 0)
            {
                //Initializing potential optimization string
                if (c > 0)
                {
                    snprintf(subString, sizeof(subString), "if(idx+%d > cellCount) {printf(\"insufficient cellcount\"); return -1;}\n", c);
                    strcpy(optimizedString, subString);
                    snprintf(subString, sizeof(subString), "cells[idx+%d]", c);
                    strcat(optimizedString, subString);
                } else {
                    snprintf(subString, sizeof(subString), "if(idx-%d < 0) {printf(\"data pointer < zero\"); return -1;}\n", -c);
                    strcpy(optimizedString, subString);
                    snprintf(subString, sizeof(subString), "cells[idx-%d]", -c);
                    strcat(optimizedString, subString);
                }
                
                
                //Counting additions/subtractions
                int inc = 0;
                while (symbol == '+' || symbol == '-')
                {
                    if (symbol == '+')
                        inc++;
                    else inc--;
                    i++;
                    symbol = (char) file_string[i];
                }

                //Adding addition/subtraction to potential optimization string
                if (inc < 0) {
                    snprintf(subString, sizeof(subString), "-=%d;\n", -inc);
                    strcat(optimizedString, subString);
                }
                else {
                    snprintf(subString, sizeof(subString), "+=%d;\n", inc);
                    strcat(optimizedString, subString);
                }

                //Testing if the ending movements corresponds to the start movements
                char valid = 0;
                for (int j = 0; j < move_count; j++)
                {
                    if (c > 0 && (symbol != '<' || i > file_size))
                    {
                        break;
                    } else if (c < 0 && (symbol != '>' || i > file_size))
                    {
                        break;
                    }
                    
                    i++;
                    symbol = (char) file_string[i];
                    if (j+1==move_count)
                    {
                    valid=1;
                    }
                }
                
                //Applying the valid optimization or resetting the reader to original symbol
                if (valid) fprintf(transpiled, optimizedString);
                else i = tempi;
            }

            //Resetting initializations for the rest to run correctly
            symbol = (char) file_string[i];
            c = 0;
        } //end of optimization level 2
        
        /*Level 0-1 optimizations + nonOptimized parts*/
        switch (symbol)
        {
        case '+':
            if (optimization[0]) 
            {
                while (symbol == '+')
                {
                    c++;
                    i++;
                    symbol = (char) file_string[i];
                }
                i--;
                fprintf(transpiled, "cells[idx]+=%d;\n",c);
            } else fprintf(transpiled, "cells[idx]++;\n");
            
            break;
        
        case '-':
            if (optimization[0]) 
            {
                while (symbol == '-')
                {
                    c++;
                    i++;
                    symbol = (char) file_string[i];
                }
                i--;
                fprintf(transpiled, "cells[idx]-=%d;\n", c);
            } else fprintf(transpiled, "cells[idx]--;\n");
            
            break;

        case '>':
            if (optimization[1]) 
            {
                while (symbol == '>')
                {
                    c++;
                    i++;
                    symbol = (char) file_string[i];
                }
                i--;
                fprintf(transpiled, "idx+=%d;\n", c);
            } else fprintf(transpiled, "idx++;\n");
            
            fprintf(transpiled, "if(idx > cellCount) {");
            fprintf(transpiled, "printf(\"insufficient cellcount\"); return -1;}\n");
            
            break;

        case '<':
            if (optimization[1])
            {
                while (symbol == '<')
                {
                    c++;
                    i++;
                    symbol = (char) file_string[i];
                }
                i--;
                fprintf(transpiled, "idx-=%d;\n", c);
            } else fprintf(transpiled, "idx--;\n");

            fprintf(transpiled, "if(idx < 0) {");
            fprintf(transpiled, "printf(\"idx less than zero\"); return -1;}\n");
            
            break;
            
        case ',':
            fprintf(transpiled, "if (input_pointer <= 255) {\n");
            fprintf(transpiled, "cells[idx] = input[input_pointer];\n");
            fprintf(transpiled, "input_pointer++;\n");
            fprintf(transpiled, "} else {\n");
            fprintf(transpiled, "printf(\"Insufficient input length\");}\n");
            break;
        
        case '.':
            fprintf(transpiled,"fprintf(result_file,\"%%c\", (char) cells[idx]);\n");
            break;
        
        case '[':
            fprintf(transpiled, "while (cells[idx] != 0) {\n");
            break;
        
        case ']':
           fprintf(transpiled, "}\n");
            break;
        
        default:
            //Skip
            break;
        }
    }
    // END OF MAIN
    fprintf(transpiled, "fprintf(result_file,\"Result:\");\n");
    fprintf(transpiled, "for(int i = 0; i < cellCount; i++) {\n");
    fprintf(transpiled, "if (i%%10==0) fprintf(result_file,\"\\n\");\n");
    fprintf(transpiled, "fprintf(result_file,\"[%%d]\",cells[i]);\n");
    fprintf(transpiled, "}\n");
    fprintf(transpiled, "}");
    fclose(transpiled);
}

int main(int argc, char **argv) {
    char *program_folder_path = "../BrainFuck_Programs";
    //char *file_name = "test1.txt";
    //char *file_name = "BubbleSourt.txt";
    //char *file_name = "HelloWorldMinimized.txt";
    //char *file_name = "HelloWorld.txt";

    /*Loading in file*/
    char *file_name = argv[1];
    FILE *b_program = openFile(program_folder_path, file_name);
    if (b_program == NULL) {printf("File not found\n"); return -1;}
    const int file_size = fsize(b_program);
    
    /*Reading file to string*/
    char file_string[file_size];
    strcpy(file_string, "");
    const unsigned MAX_LENGTH = 256;
    char buffer[MAX_LENGTH];
    while (fgets(buffer, MAX_LENGTH, b_program)) strcat(file_string, buffer);
    fclose(b_program);

    /*Parsing optimization options*/
    int optimization_count = 5;
    //Testing option validity
    if (argc != optimization_count+2)
    {
        printf("You must parse exactly 5 optimization option numbers {1;0} for each number");
        return -1;
    }
    for (int i = 2; i < argc; i++) //testing the input is numbers 0,1
    {
        char *endptr;
        long num = strtol(argv[i], &endptr, 10);
        if (*endptr == '\0' && num >= 0 && num <= 1) continue;
        printf("All optimization options must be 0 or 1 error: input %d is %s", i-2,argv[i]);
        return -1;
    }

    //Parsing options
    char optimizations[optimization_count];
    optimizations[0] = atoi(argv[2]);
    for (int i = 3; i < argc; i++)
    {
        optimizations[i-2] = atoi(argv[i]);
    }
    
    /*Creating new file to transpile into*/
    char *transpiled_folder_path = "../OptimizedTranspiling";
    FILE *tranpiled_file = createFile(transpiled_folder_path,file_name, optimizations, optimization_count);
    initFile(tranpiled_file, file_name, optimizations, optimization_count); //initializing file methods

    /*Starting the transpiler*/
    transpiler(file_string, file_size, tranpiled_file, optimizations);

    return 0;
}