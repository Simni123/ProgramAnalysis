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

int fsize(FILE *fp){
    int prev=ftell(fp);
    fseek(fp, 0L, SEEK_END);
    int sz=ftell(fp);
    fseek(fp,prev,SEEK_SET); //go back to where we were
    return sz;
}

void interpreter(char *cells, const int cellCount, char *file_string, const int file_size) {
    int data_pointer = 0;
    int input_pointer = 0;
    int loop_array[100];
    memset(loop_array, 0, 100);
    int loop_pointer = -1;
    char input[255];
    printf("Provide Input:\n");
    memset(input, 0, 255);
    scanf("%255s", input);

    printf("Starting Interpreter\n");
    printf("filesize %d\n", file_size);
        
    /*Runnning through program*/
    for (int i = 0; i < file_size; i++)
    {
        printf("%d\n",i);
        char symbol = (char) file_string[i];
        switch (symbol)
        {
        case '+':
            cells[data_pointer] += 1;
            break;
        
        case '-':
            cells[data_pointer] -= 1;
            break;

        case '>':
            data_pointer += 1;
            if (data_pointer > cellCount)
            {
                printf("Insufficient cellcount");
                return;
            }
            break;

        case '<':
            data_pointer -= 1;
            break;
            
        case ',':
            if (input_pointer <= 255)
            {
                cells[data_pointer] = input[input_pointer];
                input_pointer++;
            } else {
                cells[data_pointer] = 0;
            }
            break;
        
        case '.':
            printf("%c", (char) cells[data_pointer]);
            break;
        
        case '[':
            loop_pointer++;
            loop_array[loop_pointer] = i;
            break;
        
        case ']':
            if (cells[data_pointer] != 0)
            {
                i = loop_array[loop_pointer];
            } else {
                loop_array[loop_pointer] = 0;
                loop_pointer--;
            }
            break;
        
        default:
            break;
        }
    }
    
    printf("\n");
    /*Printing the cell results*/
    for (int i = 0; i < cellCount ; i++)
    {
        printf("[%d]",cells[i]);
    }
}

int main() {
    char *folder_path = "../BrainFuck_Programs";
    char *file_name = "SimpleTest1.txt";
    FILE *b_program = openFile(folder_path, file_name);
    const int file_size = fsize(b_program);
    
    /*Reading file to string*/
    char file_string[file_size];
    strcpy(file_string, "");
    const unsigned MAX_LENGTH = 256;
    char buffer[MAX_LENGTH];
    while (fgets(buffer, MAX_LENGTH, b_program)) strcat(file_string, buffer);
    fclose(b_program);
    

    /*Starting the interpreter*/
    const int cellCount = 100;
    char byteArray[cellCount];
    memset(byteArray, 0, cellCount);
    interpreter(byteArray, cellCount, file_string, file_size);

    return 0;
}

