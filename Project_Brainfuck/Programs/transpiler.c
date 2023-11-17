#include <stdio.h>
#include <dirent.h>

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
            } else {
                closedir(folder);
                return NULL;
            }
            
        }
    }

    return NULL;
}

FILE* createFile(char *file_path, char *file_name) {
    DIR *transpiled_folder = opendir(file_path);
    
    /*Creating a subfile name without .type*/
    char file_name_sub[1024];
    strcpy(file_name_sub, file_name);
    const char deli[] = ".";
    char *token;
    token = strtok(file_name_sub, deli);
    
    /*Concatinating the file name to a c file*/
    char transpiled_file_name[1024];
    strcpy(transpiled_file_name, token);
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

int fsize(FILE *fp){
    int prev=ftell(fp);
    fseek(fp, 0L, SEEK_END);
    int sz=ftell(fp);
    fseek(fp,prev,SEEK_SET); //go back to where we were
    return sz;
}

void initFile(FILE* transpiled, char *file_name) {
    fprintf(transpiled, "#include <stdio.h>\n");
    fprintf(transpiled, "#include <dirent.h>\n");
    fprintf(transpiled, "\n");
    fprintf(transpiled, "\n");

    /*Adding method to write the result to file in the transpiled file*/
    fprintf(transpiled, "FILE* createFile(char *file_path, char *file_name) {\n");
    fprintf(transpiled, "DIR *transpiled_folder = opendir(file_path);\n");
    fprintf(transpiled, "\n");
    fprintf(transpiled, "/*Creating a subfile name without .type*/\n");
    fprintf(transpiled, "char file_name_sub[1024];");
    fprintf(transpiled, "strcpy(file_name_sub, file_name);\n");
    fprintf(transpiled, "const char deli[] = \".\";\n");
    fprintf(transpiled, "char *token;\n");
    fprintf(transpiled, "token = strtok(file_name_sub, deli);\n");
    fprintf(transpiled, "\n");
    fprintf(transpiled, "/*Concatinating the file name to a txt file*/\n");
    fprintf(transpiled, "char transpiled_file_name[1024];\n");
    fprintf(transpiled, "strcpy(transpiled_file_name, token);\n");
    fprintf(transpiled, "strcat(transpiled_file_name, \"_naive.txt\");\n");
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

void transpiler(char *file_string, const int file_size, FILE* transpiled) {
        
    /*Runnning through program*/
    for (int i = 0; i < file_size; i++)
    {   
        char symbol = (char) file_string[i];
        
        switch (symbol)
        {
        case '+':
            fprintf(transpiled, "cells[idx]++;\n");
            break;
        
        case '-':
            fprintf(transpiled, "cells[idx]--;\n");
            break;

        case '>':
            fprintf(transpiled, "idx++;\n");
            fprintf(transpiled, "if(idx > cellCount) {");
            fprintf(transpiled, "printf(\"insufficient cellcount\"); return -1;}\n");
            break;

        case '<':
            fprintf(transpiled, "idx--;\n");
            fprintf(transpiled, "if(idx < 0) {");
            fprintf(transpiled, "printf(\"idx less than zero\"); return -1;}\n");
            break;
            
        case ',':
            fprintf(transpiled, "if (input_pointer <= input_len) {\n");
            fprintf(transpiled, "cells[idx] = input[input_pointer];\n");
            fprintf(transpiled, "input_pointer++;\n");
            fprintf(transpiled, "} else {\n");
            fprintf(transpiled, "printf(\"Insufficient input length\"); return -1;}\n");
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
    
    /*Creating new file to transpile into*/
    char *transpiled_folder_path = "../NaiveTranspiling";
    FILE *tranpiled_file = createFile(transpiled_folder_path,file_name);
    initFile(tranpiled_file, file_name);

    /*Starting the transpiler*/
    transpiler(file_string, file_size, tranpiled_file);

    return 0;
}