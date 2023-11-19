#include <stdio.h>
#include <dirent.h>
#include <string.h>


FILE* createFile(char *file_path, char *file_name) {
DIR *transpiled_folder = opendir(file_path);

/*Creating a subfile name without .type*/
char file_name_sub[1024];strcpy(file_name_sub, file_name);
const char deli[] = ".";
char *token;
token = strtok(file_name_sub, deli);

/*Concatinating the file name to a txt file*/
char transpiled_file_name[1024];
strcpy(transpiled_file_name, token);
strcat(transpiled_file_name, "_naive.txt");

/*Concatinating to the path of storage*/
char transpiled_file_path[1024];
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
memset(cells, 0, cellCount*sizeof(char));
int idx = 0;
char *result_folder_path = "../UnitTestFiles";
FILE *result_file = createFile(result_folder_path,"HelloWorld.txt");
fprintf(result_file,"Output: \n");
while (cells[idx] != 0) {
if (input_pointer <= input_len) {
cells[idx] = input[input_pointer];
input_pointer++;
} else {
printf("Insufficient input length");}
fprintf(result_file,"%c", (char) cells[idx]);
while (cells[idx] != 0) {
fprintf(result_file,"%c", (char) cells[idx]);
}
if (input_pointer <= input_len) {
cells[idx] = input[input_pointer];
input_pointer++;
} else {
printf("Insufficient input length");}
fprintf(result_file,"%c", (char) cells[idx]);
fprintf(result_file,"%c", (char) cells[idx]);
if (input_pointer <= input_len) {
cells[idx] = input[input_pointer];
input_pointer++;
} else {
printf("Insufficient input length");}
if (input_pointer <= input_len) {
cells[idx] = input[input_pointer];
input_pointer++;
} else {
printf("Insufficient input length");}
if (input_pointer <= input_len) {
cells[idx] = input[input_pointer];
input_pointer++;
} else {
printf("Insufficient input length");}
cells[idx]++;
if (input_pointer <= input_len) {
cells[idx] = input[input_pointer];
input_pointer++;
} else {
printf("Insufficient input length");}
cells[idx]--;
if (input_pointer <= input_len) {
cells[idx] = input[input_pointer];
input_pointer++;
} else {
printf("Insufficient input length");}
idx--;
if(idx < 0) {printf("idx less than zero"); return -1;}
idx++;
if(idx > cellCount) {printf("insufficient cellcount"); return -1;}
if (input_pointer <= input_len) {
cells[idx] = input[input_pointer];
input_pointer++;
} else {
printf("Insufficient input length");}
while (cells[idx] != 0) {
}
fprintf(result_file,"%c", (char) cells[idx]);
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
fprintf(result_file,"%c", (char) cells[idx]);
idx++;
if(idx > cellCount) {printf("insufficient cellcount"); return -1;}
cells[idx]--;
cells[idx]--;
cells[idx]--;
fprintf(result_file,"%c", (char) cells[idx]);
cells[idx]++;
cells[idx]++;
cells[idx]++;
cells[idx]++;
cells[idx]++;
cells[idx]++;
cells[idx]++;
fprintf(result_file,"%c", (char) cells[idx]);
fprintf(result_file,"%c", (char) cells[idx]);
cells[idx]++;
cells[idx]++;
cells[idx]++;
fprintf(result_file,"%c", (char) cells[idx]);
idx++;
if(idx > cellCount) {printf("insufficient cellcount"); return -1;}
idx++;
if(idx > cellCount) {printf("insufficient cellcount"); return -1;}
fprintf(result_file,"%c", (char) cells[idx]);
idx--;
if(idx < 0) {printf("idx less than zero"); return -1;}
cells[idx]--;
fprintf(result_file,"%c", (char) cells[idx]);
idx--;
if(idx < 0) {printf("idx less than zero"); return -1;}
fprintf(result_file,"%c", (char) cells[idx]);
cells[idx]++;
cells[idx]++;
cells[idx]++;
fprintf(result_file,"%c", (char) cells[idx]);
cells[idx]--;
cells[idx]--;
cells[idx]--;
cells[idx]--;
cells[idx]--;
cells[idx]--;
fprintf(result_file,"%c", (char) cells[idx]);
cells[idx]--;
cells[idx]--;
cells[idx]--;
cells[idx]--;
cells[idx]--;
cells[idx]--;
cells[idx]--;
cells[idx]--;
fprintf(result_file,"%c", (char) cells[idx]);
idx++;
if(idx > cellCount) {printf("insufficient cellcount"); return -1;}
idx++;
if(idx > cellCount) {printf("insufficient cellcount"); return -1;}
cells[idx]++;
fprintf(result_file,"%c", (char) cells[idx]);
idx++;
if(idx > cellCount) {printf("insufficient cellcount"); return -1;}
cells[idx]++;
cells[idx]++;
fprintf(result_file,"%c", (char) cells[idx]);
fprintf(result_file,"Result:");
for(int i = 0; i < cellCount; i++) {
if (i%10==0) fprintf(result_file,"\n");
fprintf(result_file,"[%d]",cells[i]);
}
}