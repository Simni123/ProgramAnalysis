#include <stdio.h>
#include <dirent.h>


FILE* createFile(char *file_path, char *file_name) {
DIR *transpiled_folder = opendir(file_path);

/*Creating a subfile name without .type*/
char file_name_sub[sizeof(file_name)*2]; //WTF whry *2 - find out
strcpy(file_name_sub, file_name);
const char deli[] = ".";
char *token;
token = strtok(file_name_sub, deli);

/*adding the optimization string on the file*/
char optimization_string[5+2];
strcpy(optimization_string, "[");
strcat(optimization_string, "0");
strcat(optimization_string, "0");
strcat(optimization_string, "0");
strcat(optimization_string, "0");
strcat(optimization_string, "0");
strcat(optimization_string, "]");
/*Concatinating the file name to a txt file*/
char transpiled_file_name[sizeof(token)+sizeof(optimization_string)+2];
strcpy(transpiled_file_name, token);
strcat(transpiled_file_name, optimization_string);
strcat(transpiled_file_name, ".txt");

/*Concatinating to the path of storage*/
char transpiled_file_path[sizeof(file_path)*2+sizeof(transpiled_file_name)+2]; //Why *2 again
strcpy(transpiled_file_path, file_path);
strcat(transpiled_file_path, "/");
strcat(transpiled_file_path, transpiled_file_name);

FILE *tFile = fopen(transpiled_file_path, "w+");
if (tFile == NULL) { printf("Could not create file\n"); return NULL;}
return tFile;
}

int main (int argc, char **argv) {
int input_pointer = 0;
char *input;
int input_len = 0;
if (argc == 2) {input = argv[1]; input_len = strlen(input);}
const int cellCount = 100;
unsigned char cells[cellCount];
memset(cells, 0, cellCount);
int idx = 0;
printf("Cells: %d \n", cellCount);
printf("Output: ");
char *result_folder_path = "../UnitTestFiles";
FILE *result_file = createFile(result_folder_path,"HelloWorld.txt");
fprintf(result_file,"Output: ");
while (cells[idx] != 0) {
if (input_pointer <= 255) {
cells[idx] = input[input_pointer];
input_pointer++;
} else {
printf("Insufficient input length");}
printf("%c", (char) cells[idx]);
fprintf(result_file,"%c", (char) cells[idx]);
while (cells[idx] != 0) {
printf("%c", (char) cells[idx]);
fprintf(result_file,"%c", (char) cells[idx]);
}
if (input_pointer <= 255) {
cells[idx] = input[input_pointer];
input_pointer++;
} else {
printf("Insufficient input length");}
printf("%c", (char) cells[idx]);
fprintf(result_file,"%c", (char) cells[idx]);
printf("%c", (char) cells[idx]);
fprintf(result_file,"%c", (char) cells[idx]);
if (input_pointer <= 255) {
cells[idx] = input[input_pointer];
input_pointer++;
} else {
printf("Insufficient input length");}
if (input_pointer <= 255) {
cells[idx] = input[input_pointer];
input_pointer++;
} else {
printf("Insufficient input length");}
if (input_pointer <= 255) {
cells[idx] = input[input_pointer];
input_pointer++;
} else {
printf("Insufficient input length");}
cells[idx]++;
if (input_pointer <= 255) {
cells[idx] = input[input_pointer];
input_pointer++;
} else {
printf("Insufficient input length");}
cells[idx]--;
if (input_pointer <= 255) {
cells[idx] = input[input_pointer];
input_pointer++;
} else {
printf("Insufficient input length");}
idx--;
if(idx < 0) {printf("idx less than zero"); return -1;}
idx++;
if(idx > cellCount) {printf("insufficient cellcount"); return -1;}
if (input_pointer <= 255) {
cells[idx] = input[input_pointer];
input_pointer++;
} else {
printf("Insufficient input length");}
while (cells[idx] != 0) {
}
printf("%c", (char) cells[idx]);
fprintf(result_file,"%c", (char) cells[idx]);
printf("%c", (char) cells[idx]);
fprintf(result_file,"%c", (char) cells[idx]);
}
cells[idx]++;
cells[idx]++;
cells[idx]++;
cells[idx]++;
cells[idx]++;
cells[idx]++;
cells[idx]++;
cells[idx]++;
while (cells[idx] != 0) {
idx++;
if(idx > cellCount) {printf("insufficient cellcount"); return -1;}
cells[idx]++;
cells[idx]++;
cells[idx]++;
cells[idx]++;
while (cells[idx] != 0) {
idx++;
if(idx > cellCount) {printf("insufficient cellcount"); return -1;}
cells[idx]++;
cells[idx]++;
idx++;
if(idx > cellCount) {printf("insufficient cellcount"); return -1;}
cells[idx]++;
cells[idx]++;
cells[idx]++;
idx++;
if(idx > cellCount) {printf("insufficient cellcount"); return -1;}
cells[idx]++;
cells[idx]++;
cells[idx]++;
idx++;
if(idx > cellCount) {printf("insufficient cellcount"); return -1;}
cells[idx]++;
idx--;
if(idx < 0) {printf("idx less than zero"); return -1;}
idx--;
if(idx < 0) {printf("idx less than zero"); return -1;}
idx--;
if(idx < 0) {printf("idx less than zero"); return -1;}
idx--;
if(idx < 0) {printf("idx less than zero"); return -1;}
cells[idx]--;
}
idx++;
if(idx > cellCount) {printf("insufficient cellcount"); return -1;}
cells[idx]++;
idx++;
if(idx > cellCount) {printf("insufficient cellcount"); return -1;}
cells[idx]++;
idx++;
if(idx > cellCount) {printf("insufficient cellcount"); return -1;}
cells[idx]--;
idx++;
if(idx > cellCount) {printf("insufficient cellcount"); return -1;}
idx++;
if(idx > cellCount) {printf("insufficient cellcount"); return -1;}
cells[idx]++;
while (cells[idx] != 0) {
idx--;
if(idx < 0) {printf("idx less than zero"); return -1;}
}
idx--;
if(idx < 0) {printf("idx less than zero"); return -1;}
cells[idx]--;
}
idx++;
if(idx > cellCount) {printf("insufficient cellcount"); return -1;}
idx++;
if(idx > cellCount) {printf("insufficient cellcount"); return -1;}
printf("%c", (char) cells[idx]);
fprintf(result_file,"%c", (char) cells[idx]);
idx++;
if(idx > cellCount) {printf("insufficient cellcount"); return -1;}
cells[idx]--;
cells[idx]--;
cells[idx]--;
printf("%c", (char) cells[idx]);
fprintf(result_file,"%c", (char) cells[idx]);
cells[idx]++;
cells[idx]++;
cells[idx]++;
cells[idx]++;
cells[idx]++;
cells[idx]++;
cells[idx]++;
printf("%c", (char) cells[idx]);
fprintf(result_file,"%c", (char) cells[idx]);
printf("%c", (char) cells[idx]);
fprintf(result_file,"%c", (char) cells[idx]);
cells[idx]++;
cells[idx]++;
cells[idx]++;
printf("%c", (char) cells[idx]);
fprintf(result_file,"%c", (char) cells[idx]);
idx++;
if(idx > cellCount) {printf("insufficient cellcount"); return -1;}
idx++;
if(idx > cellCount) {printf("insufficient cellcount"); return -1;}
printf("%c", (char) cells[idx]);
fprintf(result_file,"%c", (char) cells[idx]);
idx--;
if(idx < 0) {printf("idx less than zero"); return -1;}
cells[idx]--;
printf("%c", (char) cells[idx]);
fprintf(result_file,"%c", (char) cells[idx]);
idx--;
if(idx < 0) {printf("idx less than zero"); return -1;}
printf("%c", (char) cells[idx]);
fprintf(result_file,"%c", (char) cells[idx]);
cells[idx]++;
cells[idx]++;
cells[idx]++;
printf("%c", (char) cells[idx]);
fprintf(result_file,"%c", (char) cells[idx]);
cells[idx]--;
cells[idx]--;
cells[idx]--;
cells[idx]--;
cells[idx]--;
cells[idx]--;
printf("%c", (char) cells[idx]);
fprintf(result_file,"%c", (char) cells[idx]);
cells[idx]--;
cells[idx]--;
cells[idx]--;
cells[idx]--;
cells[idx]--;
cells[idx]--;
cells[idx]--;
cells[idx]--;
printf("%c", (char) cells[idx]);
fprintf(result_file,"%c", (char) cells[idx]);
idx++;
if(idx > cellCount) {printf("insufficient cellcount"); return -1;}
idx++;
if(idx > cellCount) {printf("insufficient cellcount"); return -1;}
cells[idx]++;
printf("%c", (char) cells[idx]);
fprintf(result_file,"%c", (char) cells[idx]);
idx++;
if(idx > cellCount) {printf("insufficient cellcount"); return -1;}
cells[idx]++;
cells[idx]++;
printf("%c", (char) cells[idx]);
fprintf(result_file,"%c", (char) cells[idx]);
printf("\n");
printf("Result: \n");
fprintf(result_file,"Result:");
for(int i = 0; i < cellCount; i++) {
printf("[%d]",cells[i]);
if (i%10==0) fprintf(result_file,"\n");
fprintf(result_file,"[%d]",cells[i]);
}
}