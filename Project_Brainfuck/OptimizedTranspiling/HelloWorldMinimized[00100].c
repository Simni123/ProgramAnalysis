#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <time.h>
#include <math.h>


FILE* createFile(char *file_path, char *file_name) {
DIR *transpiled_folder = opendir(file_path);

/*Creating a subfile name without .type*/
char file_name_sub[1024];
strcpy(file_name_sub, file_name);
const char deli[] = ".";
char *token;
token = strtok(file_name_sub, deli);

/*adding the optimization string on the file*/
char optimization_string[5+2];
strcpy(optimization_string, "[");
strcat(optimization_string, "0");
strcat(optimization_string, "0");
strcat(optimization_string, "1");
strcat(optimization_string, "0");
strcat(optimization_string, "0");
strcat(optimization_string, "]");
/*Concatinating the file name to a txt file*/
char transpiled_file_name[1024];
strcpy(transpiled_file_name, token);
strcat(transpiled_file_name, optimization_string);
strcat(transpiled_file_name, ".txt");

/*Concatinating to the path of storage*/
char transpiled_file_path[1024];
strcpy(transpiled_file_path, file_path);
strcat(transpiled_file_path, "/");
strcat(transpiled_file_path, transpiled_file_name);

FILE *tFile = fopen(transpiled_file_path, "w+");
if (tFile == NULL) { printf("Could not create file\n"); return NULL;}
return tFile;
};
int main (int argc, char **argv) {
char *result_folder_path = "../UnitTestFiles";
FILE *result_file = createFile(result_folder_path,"HelloWorldMinimized.txt");
int input_pointer = 0;
char *input;
int input_len = 0;
if (argc == 2) {input = argv[1]; input_len = strlen(input);}
const int cellCount = 100;
unsigned char cells[cellCount];
memset(cells, 0, cellCount*sizeof(char));
int idx = 0;
unsigned char output[1024];
memset(output, 0, 1024*sizeof(char));
int outputIdx = 0;
/*Starting combined level 2 optimization*/
if(idx+(0) < 0 || idx+(8) > cellCount) {printf("insufficient cell count"); return -1;} 
cells[idx+(0)] = cells[idx+(0)]+(8); 
/*Ending combined level 2 optimization*/
while (cells[idx] != 0) {
/*Starting combined level 2 optimization*/
if(idx+(1) < 0 || idx+(4) > cellCount) {printf("insufficient cell count"); return -1;} 
cells[idx+(1)] = cells[idx+(1)]+(4); 
idx += (1);
if(idx > cellCount && idx < 0) {printf("insufficient cellcount"); return -1;}
/*Ending combined level 2 optimization*/
while (cells[idx] != 0) {
/*Starting combined level 2 optimization*/
if(idx+(0) < 0 || idx+(-1) > cellCount) {printf("insufficient cell count"); return -1;} 
cells[idx+(0)] = cells[idx+(0)]+(-1); 
if(idx+(1) < 0 || idx+(2) > cellCount) {printf("insufficient cell count"); return -1;} 
cells[idx+(1)] = cells[idx+(1)]+(2); 
if(idx+(2) < 0 || idx+(3) > cellCount) {printf("insufficient cell count"); return -1;} 
cells[idx+(2)] = cells[idx+(2)]+(3); 
if(idx+(3) < 0 || idx+(3) > cellCount) {printf("insufficient cell count"); return -1;} 
cells[idx+(3)] = cells[idx+(3)]+(3); 
if(idx+(4) < 0 || idx+(1) > cellCount) {printf("insufficient cell count"); return -1;} 
cells[idx+(4)] = cells[idx+(4)]+(1); 
/*Ending combined level 2 optimization*/
}
/*Starting combined level 2 optimization*/
if(idx+(1) < 0 || idx+(1) > cellCount) {printf("insufficient cell count"); return -1;} 
cells[idx+(1)] = cells[idx+(1)]+(1); 
if(idx+(2) < 0 || idx+(1) > cellCount) {printf("insufficient cell count"); return -1;} 
cells[idx+(2)] = cells[idx+(2)]+(1); 
if(idx+(3) < 0 || idx+(-1) > cellCount) {printf("insufficient cell count"); return -1;} 
cells[idx+(3)] = cells[idx+(3)]+(-1); 
if(idx+(5) < 0 || idx+(1) > cellCount) {printf("insufficient cell count"); return -1;} 
cells[idx+(5)] = cells[idx+(5)]+(1); 
idx += (5);
if(idx > cellCount && idx < 0) {printf("insufficient cellcount"); return -1;}
/*Ending combined level 2 optimization*/
while (cells[idx] != 0) {
/*Starting combined level 2 optimization*/
idx += (-1);
if(idx > cellCount && idx < 0) {printf("insufficient cellcount"); return -1;}
/*Ending combined level 2 optimization*/
}
/*Starting combined level 2 optimization*/
if(idx+(-1) < 0 || idx+(-1) > cellCount) {printf("insufficient cell count"); return -1;} 
cells[idx+(-1)] = cells[idx+(-1)]+(-1); 
idx += (-1);
if(idx > cellCount && idx < 0) {printf("insufficient cellcount"); return -1;}
/*Ending combined level 2 optimization*/
}
/*Starting combined level 2 optimization*/
idx += (2);
if(idx > cellCount && idx < 0) {printf("insufficient cellcount"); return -1;}
/*Ending combined level 2 optimization*/
if(outputIdx > 1024) {printf("insuficient output length"); return -1;}
output[outputIdx] = cells[idx];
outputIdx++;
/*Starting combined level 2 optimization*/
if(idx+(1) < 0 || idx+(-3) > cellCount) {printf("insufficient cell count"); return -1;} 
cells[idx+(1)] = cells[idx+(1)]+(-3); 
idx += (1);
if(idx > cellCount && idx < 0) {printf("insufficient cellcount"); return -1;}
/*Ending combined level 2 optimization*/
if(outputIdx > 1024) {printf("insuficient output length"); return -1;}
output[outputIdx] = cells[idx];
outputIdx++;
/*Starting combined level 2 optimization*/
if(idx+(0) < 0 || idx+(7) > cellCount) {printf("insufficient cell count"); return -1;} 
cells[idx+(0)] = cells[idx+(0)]+(7); 
/*Ending combined level 2 optimization*/
if(outputIdx > 1024) {printf("insuficient output length"); return -1;}
output[outputIdx] = cells[idx];
outputIdx++;
if(outputIdx > 1024) {printf("insuficient output length"); return -1;}
output[outputIdx] = cells[idx];
outputIdx++;
/*Starting combined level 2 optimization*/
if(idx+(0) < 0 || idx+(3) > cellCount) {printf("insufficient cell count"); return -1;} 
cells[idx+(0)] = cells[idx+(0)]+(3); 
/*Ending combined level 2 optimization*/
if(outputIdx > 1024) {printf("insuficient output length"); return -1;}
output[outputIdx] = cells[idx];
outputIdx++;
/*Starting combined level 2 optimization*/
idx += (2);
if(idx > cellCount && idx < 0) {printf("insufficient cellcount"); return -1;}
/*Ending combined level 2 optimization*/
if(outputIdx > 1024) {printf("insuficient output length"); return -1;}
output[outputIdx] = cells[idx];
outputIdx++;
/*Starting combined level 2 optimization*/
if(idx+(-1) < 0 || idx+(-1) > cellCount) {printf("insufficient cell count"); return -1;} 
cells[idx+(-1)] = cells[idx+(-1)]+(-1); 
idx += (-1);
if(idx > cellCount && idx < 0) {printf("insufficient cellcount"); return -1;}
/*Ending combined level 2 optimization*/
if(outputIdx > 1024) {printf("insuficient output length"); return -1;}
output[outputIdx] = cells[idx];
outputIdx++;
/*Starting combined level 2 optimization*/
idx += (-1);
if(idx > cellCount && idx < 0) {printf("insufficient cellcount"); return -1;}
/*Ending combined level 2 optimization*/
if(outputIdx > 1024) {printf("insuficient output length"); return -1;}
output[outputIdx] = cells[idx];
outputIdx++;
/*Starting combined level 2 optimization*/
if(idx+(0) < 0 || idx+(3) > cellCount) {printf("insufficient cell count"); return -1;} 
cells[idx+(0)] = cells[idx+(0)]+(3); 
/*Ending combined level 2 optimization*/
if(outputIdx > 1024) {printf("insuficient output length"); return -1;}
output[outputIdx] = cells[idx];
outputIdx++;
/*Starting combined level 2 optimization*/
if(idx+(0) < 0 || idx+(-6) > cellCount) {printf("insufficient cell count"); return -1;} 
cells[idx+(0)] = cells[idx+(0)]+(-6); 
/*Ending combined level 2 optimization*/
if(outputIdx > 1024) {printf("insuficient output length"); return -1;}
output[outputIdx] = cells[idx];
outputIdx++;
/*Starting combined level 2 optimization*/
if(idx+(0) < 0 || idx+(-8) > cellCount) {printf("insufficient cell count"); return -1;} 
cells[idx+(0)] = cells[idx+(0)]+(-8); 
/*Ending combined level 2 optimization*/
if(outputIdx > 1024) {printf("insuficient output length"); return -1;}
output[outputIdx] = cells[idx];
outputIdx++;
/*Starting combined level 2 optimization*/
if(idx+(2) < 0 || idx+(1) > cellCount) {printf("insufficient cell count"); return -1;} 
cells[idx+(2)] = cells[idx+(2)]+(1); 
idx += (2);
if(idx > cellCount && idx < 0) {printf("insufficient cellcount"); return -1;}
/*Ending combined level 2 optimization*/
if(outputIdx > 1024) {printf("insuficient output length"); return -1;}
output[outputIdx] = cells[idx];
outputIdx++;
/*Starting combined level 2 optimization*/
if(idx+(1) < 0 || idx+(2) > cellCount) {printf("insufficient cell count"); return -1;} 
cells[idx+(1)] = cells[idx+(1)]+(2); 
idx += (1);
if(idx > cellCount && idx < 0) {printf("insufficient cellcount"); return -1;}
/*Ending combined level 2 optimization*/
if(outputIdx > 1024) {printf("insuficient output length"); return -1;}
output[outputIdx] = cells[idx];
outputIdx++;
fprintf(result_file, "Output: ");
for (int i = 0; i < outputIdx; i++){
fprintf(result_file,"%c", (char) output[i]);
}
fprintf(result_file, "\n");
fprintf(result_file, "Result:");
for (int i = 0; i < cellCount ; i++){
if (i%10 == 0) fprintf(result_file, "\n");
fprintf(result_file, "[%d]",cells[i]);
}
}