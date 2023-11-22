#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>


FILE* createFile(char *file_path, char *file_name) {
DIR *transpiled_folder = opendir(file_path);

/*Creating a subfile name without .type*/
char file_name_sub[1024];
strcpy(file_name_sub, file_name);
const char deli[] = ".";
char *token;
token = strtok(file_name_sub, deli);

/*adding the optimization string on the file*/
char optimization_string[256];
strcpy(optimization_string, "[");
strcat(optimization_string, "1");
strcat(optimization_string, "1");
strcat(optimization_string, "0");
strcat(optimization_string, "1");
strcat(optimization_string, "1");
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
}
int main (int argc, char **argv) {
if (argc != 5) {
printf("the interpretor need exactly 'result_folder_in_UnitTestFiles input_string(non-empty use " " as empty) time_mesurements repetitions_per_time_mesurement'\n");
return -1;}
char result_folder_path[1024];
strcpy(result_folder_path, "../UnitTestFiles/");
strcat(result_folder_path, argv[1]);
FILE *result_file = createFile(result_folder_path,"CountInput.txt");
int input_pointer = 0;
char *input;
int input_len = 0;
input = argv[2];
input_len = strlen(input);
fprintf(result_file, "Input: ");
fprintf(result_file, input);
fprintf(result_file, "\n");
int time_reps = 0;
int time_mesures = 0;
time_mesures = atoi(argv[3]);
time_reps = atoi(argv[4]);
const int cellCount = 500;
unsigned char cells[cellCount];
memset(cells, 0, cellCount*sizeof(char));
int idx = 0;
int outputLimit = 16384;
unsigned char output[outputLimit];
memset(output, 0, outputLimit*sizeof(char));
int outputIdx = 0;
double all_times[time_mesures];
for (size_t t = 0; t < time_mesures; t++){
clock_t start_time, end_time;
start_time = clock();
for (int k = 0; k < time_reps; k++) {
input_pointer = 0;
memset(cells, 0, cellCount*sizeof(char));
idx = 0;
memset(output, 0, outputLimit*sizeof(char));
outputIdx = 0;
/*Starting right move level 1 optimization*/
idx+=(3);
/*Ending right move level 1 optimization*/
if(idx > cellCount && idx < 0) {printf("insufficient cellcount"); return -1;}
/*Starting adding optimization*/
cells[idx]+=(1);
/*ending adding optimization*/
/*Starting right move level 1 optimization*/
idx+=(5);
/*Ending right move level 1 optimization*/
if(idx > cellCount && idx < 0) {printf("insufficient cellcount"); return -1;}
/*Starting adding optimization*/
cells[idx]+=(1);
/*ending adding optimization*/
/*Starting right move level 1 optimization*/
idx+=(2);
/*Ending right move level 1 optimization*/
if(idx > cellCount && idx < 0) {printf("insufficient cellcount"); return -1;}
/*Starting adding optimization*/
cells[idx]+=(1);
/*ending adding optimization*/
/*Starting right move level 1 optimization*/
idx+=(2);
/*Ending right move level 1 optimization*/
if(idx > cellCount && idx < 0) {printf("insufficient cellcount"); return -1;}
/*Starting adding optimization*/
cells[idx]+=(1);
/*ending adding optimization*/
while (cells[idx] != 0) {
/*Starting right move level 1 optimization*/
idx+=(-2);
/*Ending right move level 1 optimization*/
if(idx > cellCount && idx < 0) {printf("insufficient cellcount"); return -1;}
}
if (input_pointer <= 255) {
cells[idx] = input[input_pointer];
input_pointer++;
} else {
printf("Insufficient input length"); return -1;}
while (cells[idx] != 0) {
/*Starting adding optimization*/
cells[idx]+=(-1);
/*ending adding optimization*/
while (cells[idx] != 0) {
/*Starting adding optimization*/
cells[idx]+=(-1);
/*ending adding optimization*/
while (cells[idx] != 0) {
/*Starting adding optimization*/
cells[idx]+=(-1);
/*ending adding optimization*/
while (cells[idx] != 0) {
/*Starting adding optimization*/
cells[idx]+=(-1);
/*ending adding optimization*/
while (cells[idx] != 0) {
/*Starting adding optimization*/
cells[idx]+=(-1);
/*ending adding optimization*/
while (cells[idx] != 0) {
/*Starting adding optimization*/
cells[idx]+=(-1);
/*ending adding optimization*/
while (cells[idx] != 0) {
/*Starting adding optimization*/
cells[idx]+=(-1);
/*ending adding optimization*/
while (cells[idx] != 0) {
/*Starting adding optimization*/
cells[idx]+=(-1);
/*ending adding optimization*/
while (cells[idx] != 0) {
/*Starting right move level 1 optimization*/
idx+=(-1);
/*Ending right move level 1 optimization*/
if(idx > cellCount && idx < 0) {printf("insufficient cellcount"); return -1;}
/*Starting adding optimization*/
cells[idx]+=(1);
/*ending adding optimization*/
/*Starting right move level 1 optimization*/
idx+=(1);
/*Ending right move level 1 optimization*/
if(idx > cellCount && idx < 0) {printf("insufficient cellcount"); return -1;}
/*Starting adding optimization*/
cells[idx]+=(-1);
/*ending adding optimization*/
while (cells[idx] != 0) {
/*Starting right move level 1 optimization*/
idx+=(1);
/*Ending right move level 1 optimization*/
if(idx > cellCount && idx < 0) {printf("insufficient cellcount"); return -1;}
/*Starting adding optimization*/
cells[idx]+=(1);
/*ending adding optimization*/
/*Starting right move level 1 optimization*/
idx+=(-1);
/*Ending right move level 1 optimization*/
if(idx > cellCount && idx < 0) {printf("insufficient cellcount"); return -1;}
/*Starting adding optimization*/
cells[idx]+=(-1);
/*ending adding optimization*/
while (cells[idx] != 0) {
/*Starting right move level 1 optimization*/
idx+=(1);
/*Ending right move level 1 optimization*/
if(idx > cellCount && idx < 0) {printf("insufficient cellcount"); return -1;}
/*Starting adding optimization*/
cells[idx]+=(-1);
/*ending adding optimization*/
/*Starting right move level 1 optimization*/
idx+=(-1);
/*Ending right move level 1 optimization*/
if(idx > cellCount && idx < 0) {printf("insufficient cellcount"); return -1;}
/*Starting adding optimization*/
cells[idx]+=(-1);
/*ending adding optimization*/
while (cells[idx] != 0) {
/*Starting adding optimization*/
cells[idx]+=(-1);
/*ending adding optimization*/
while (cells[idx] != 0) {
/*Starting adding optimization*/
cells[idx]+=(-1);
/*ending adding optimization*/
while (cells[idx] != 0) {
/*Starting right move level 1 optimization*/
idx+=(-1);
/*Ending right move level 1 optimization*/
if(idx > cellCount && idx < 0) {printf("insufficient cellcount"); return -1;}
/*Starting adding optimization*/
cells[idx]+=(2);
/*ending adding optimization*/
/*Starting loop optimization*/
if(idx+-1 < 0 || idx+-1 > cellCount) {printf("insufficient cell count - multiplier movement -1\n"); return -1;} 
cells[idx+-1] += 6*cells[idx]; 
cells[idx] = 0;
/*end loop optimization*/
/*Starting right move level 1 optimization*/
idx+=(-1);
/*Ending right move level 1 optimization*/
if(idx > cellCount && idx < 0) {printf("insufficient cellcount"); return -1;}
while (cells[idx] != 0) {
/*Starting right move level 1 optimization*/
idx+=(2);
/*Ending right move level 1 optimization*/
if(idx > cellCount && idx < 0) {printf("insufficient cellcount"); return -1;}
while (cells[idx] != 0) {
/*Starting adding optimization*/
cells[idx]+=(-1);
/*ending adding optimization*/
/*Starting right move level 1 optimization*/
idx+=(-1);
/*Ending right move level 1 optimization*/
if(idx > cellCount && idx < 0) {printf("insufficient cellcount"); return -1;}
}
/*Starting right move level 1 optimization*/
idx+=(-1);
/*Ending right move level 1 optimization*/
if(idx > cellCount && idx < 0) {printf("insufficient cellcount"); return -1;}
while (cells[idx] != 0) {
/*Starting right move level 1 optimization*/
idx+=(1);
/*Ending right move level 1 optimization*/
if(idx > cellCount && idx < 0) {printf("insufficient cellcount"); return -1;}
}
/*Starting right move level 1 optimization*/
idx+=(-1);
/*Ending right move level 1 optimization*/
if(idx > cellCount && idx < 0) {printf("insufficient cellcount"); return -1;}
/*Starting adding optimization*/
cells[idx]+=(-1);
/*ending adding optimization*/
}
/*Starting right move level 1 optimization*/
idx+=(2);
/*Ending right move level 1 optimization*/
if(idx > cellCount && idx < 0) {printf("insufficient cellcount"); return -1;}
while (cells[idx] != 0) {
/*Starting right move level 1 optimization*/
idx+=(-1);
/*Ending right move level 1 optimization*/
if(idx > cellCount && idx < 0) {printf("insufficient cellcount"); return -1;}
/*Starting adding optimization*/
cells[idx]+=(1);
/*ending adding optimization*/
/*Starting right move level 1 optimization*/
idx+=(1);
/*Ending right move level 1 optimization*/
if(idx > cellCount && idx < 0) {printf("insufficient cellcount"); return -1;}
/*Starting adding optimization*/
cells[idx]+=(-1);
/*ending adding optimization*/
while (cells[idx] != 0) {
/*Starting right move level 1 optimization*/
idx+=(-1);
/*Ending right move level 1 optimization*/
if(idx > cellCount && idx < 0) {printf("insufficient cellcount"); return -1;}
/*Starting adding optimization*/
cells[idx]+=(-1);
/*ending adding optimization*/
/*Starting right move level 1 optimization*/
idx+=(1);
/*Ending right move level 1 optimization*/
if(idx > cellCount && idx < 0) {printf("insufficient cellcount"); return -1;}
/*Starting loop optimization*/
cells[idx] = 0;
/*end loop optimization*/
}
}
}
}
}
}
}
}
}
}
}
}
}
}
}
/*Starting right move level 1 optimization*/
idx+=(-1);
/*Ending right move level 1 optimization*/
if(idx > cellCount && idx < 0) {printf("insufficient cellcount"); return -1;}
while (cells[idx] != 0) {
/*Starting adding optimization*/
cells[idx]+=(-1);
/*ending adding optimization*/
/*Starting right move level 1 optimization*/
idx+=(-2);
/*Ending right move level 1 optimization*/
if(idx > cellCount && idx < 0) {printf("insufficient cellcount"); return -1;}
/*Starting loop optimization*/
cells[idx] = 0;
/*end loop optimization*/
/*Starting adding optimization*/
cells[idx]+=(1);
/*ending adding optimization*/
/*Starting right move level 1 optimization*/
idx+=(1);
/*Ending right move level 1 optimization*/
if(idx > cellCount && idx < 0) {printf("insufficient cellcount"); return -1;}
}
/*Starting right move level 1 optimization*/
idx+=(-2);
/*Ending right move level 1 optimization*/
if(idx > cellCount && idx < 0) {printf("insufficient cellcount"); return -1;}
/*Starting loop optimization*/
if(idx+6 < 0 || idx+6 > cellCount) {printf("insufficient cell count - multiplier movement 6\n"); return -1;} 
cells[idx+6] += 1*cells[idx]; 
cells[idx] = 0;
/*end loop optimization*/
/*Starting right move level 1 optimization*/
idx+=(1);
/*Ending right move level 1 optimization*/
if(idx > cellCount && idx < 0) {printf("insufficient cellcount"); return -1;}
while (cells[idx] != 0) {
/*Starting right move level 1 optimization*/
idx+=(1);
/*Ending right move level 1 optimization*/
if(idx > cellCount && idx < 0) {printf("insufficient cellcount"); return -1;}
}
/*Starting right move level 1 optimization*/
idx+=(7);
/*Ending right move level 1 optimization*/
if(idx > cellCount && idx < 0) {printf("insufficient cellcount"); return -1;}
/*Starting adding optimization*/
cells[idx]+=(1);
/*ending adding optimization*/
/*Starting right move level 1 optimization*/
idx+=(1);
/*Ending right move level 1 optimization*/
if(idx > cellCount && idx < 0) {printf("insufficient cellcount"); return -1;}
while (cells[idx] != 0) {
/*Starting right move level 1 optimization*/
idx+=(-1);
/*Ending right move level 1 optimization*/
if(idx > cellCount && idx < 0) {printf("insufficient cellcount"); return -1;}
/*Starting adding optimization*/
cells[idx]+=(1);
/*ending adding optimization*/
while (cells[idx] != 0) {
/*Starting right move level 1 optimization*/
idx+=(1);
/*Ending right move level 1 optimization*/
if(idx > cellCount && idx < 0) {printf("insufficient cellcount"); return -1;}
/*Starting adding optimization*/
cells[idx]+=(9);
/*ending adding optimization*/
/*Starting right move level 1 optimization*/
idx+=(-1);
/*Ending right move level 1 optimization*/
if(idx > cellCount && idx < 0) {printf("insufficient cellcount"); return -1;}
/*Starting adding optimization*/
cells[idx]+=(-1);
/*ending adding optimization*/
/*Starting loop optimization*/
if(idx+1 < 0 || idx+1 > cellCount) {printf("insufficient cell count - multiplier movement 1\n"); return -1;} 
cells[idx+1] += -1*cells[idx]; 
cells[idx] = 0;
/*end loop optimization*/
/*Starting adding optimization*/
cells[idx]+=(2);
/*ending adding optimization*/
/*Starting right move level 1 optimization*/
idx+=(1);
/*Ending right move level 1 optimization*/
if(idx > cellCount && idx < 0) {printf("insufficient cellcount"); return -1;}
while (cells[idx] != 0) {
/*Starting right move level 1 optimization*/
idx+=(-1);
/*Ending right move level 1 optimization*/
if(idx > cellCount && idx < 0) {printf("insufficient cellcount"); return -1;}
/*Starting adding optimization*/
cells[idx]+=(7);
/*ending adding optimization*/
/*Starting right move level 1 optimization*/
idx+=(1);
/*Ending right move level 1 optimization*/
if(idx > cellCount && idx < 0) {printf("insufficient cellcount"); return -1;}
/*Starting adding optimization*/
cells[idx]+=(-1);
/*ending adding optimization*/
/*Starting loop optimization*/
if(idx+-1 < 0 || idx+-1 > cellCount) {printf("insufficient cell count - multiplier movement -1\n"); return -1;} 
cells[idx+-1] += -1*cells[idx]; 
cells[idx] = 0;
/*end loop optimization*/
/*Starting adding optimization*/
cells[idx]+=(1);
/*ending adding optimization*/
while (cells[idx] != 0) {
/*Starting adding optimization*/
cells[idx]+=(1);
/*ending adding optimization*/
/*Starting right move level 1 optimization*/
idx+=(6);
/*Ending right move level 1 optimization*/
if(idx > cellCount && idx < 0) {printf("insufficient cellcount"); return -1;}
}
}
/*Starting right move level 1 optimization*/
idx+=(-1);
/*Ending right move level 1 optimization*/
if(idx > cellCount && idx < 0) {printf("insufficient cellcount"); return -1;}
/*Starting loop optimization*/
if(idx+1 < 0 || idx+1 > cellCount) {printf("insufficient cell count - multiplier movement 1\n"); return -1;} 
cells[idx+1] += 1*cells[idx]; 
cells[idx] = 0;
/*end loop optimization*/
/*Starting right move level 1 optimization*/
idx+=(1);
/*Ending right move level 1 optimization*/
if(idx > cellCount && idx < 0) {printf("insufficient cellcount"); return -1;}
while (cells[idx] != 0) {
/*Starting right move level 1 optimization*/
idx+=(5);
/*Ending right move level 1 optimization*/
if(idx > cellCount && idx < 0) {printf("insufficient cellcount"); return -1;}
/*Starting adding optimization*/
cells[idx]+=(2);
/*ending adding optimization*/
/*Starting right move level 1 optimization*/
idx+=(1);
/*Ending right move level 1 optimization*/
if(idx > cellCount && idx < 0) {printf("insufficient cellcount"); return -1;}
/*Starting loop optimization*/
cells[idx] = 0;
/*end loop optimization*/
}
/*Starting adding optimization*/
cells[idx]+=(1);
/*ending adding optimization*/
/*Starting right move level 1 optimization*/
idx+=(-1);
/*Ending right move level 1 optimization*/
if(idx > cellCount && idx < 0) {printf("insufficient cellcount"); return -1;}
}
/*Starting right move level 1 optimization*/
idx+=(1);
/*Ending right move level 1 optimization*/
if(idx > cellCount && idx < 0) {printf("insufficient cellcount"); return -1;}
while (cells[idx] != 0) {
/*Starting adding optimization*/
cells[idx]+=(-1);
/*ending adding optimization*/
/*Starting right move level 1 optimization*/
idx+=(-6);
/*Ending right move level 1 optimization*/
if(idx > cellCount && idx < 0) {printf("insufficient cellcount"); return -1;}
}
/*Starting right move level 1 optimization*/
idx+=(4);
/*Ending right move level 1 optimization*/
if(idx > cellCount && idx < 0) {printf("insufficient cellcount"); return -1;}
}
if (input_pointer <= 255) {
cells[idx] = input[input_pointer];
input_pointer++;
} else {
printf("Insufficient input length"); return -1;}
}
/*Starting adding optimization*/
cells[idx]+=(1);
/*ending adding optimization*/
/*Starting right move level 1 optimization*/
idx+=(-1);
/*Ending right move level 1 optimization*/
if(idx > cellCount && idx < 0) {printf("insufficient cellcount"); return -1;}
/*Starting adding optimization*/
cells[idx]+=(2);
/*ending adding optimization*/
/*Starting right move level 1 optimization*/
idx+=(3);
/*Ending right move level 1 optimization*/
if(idx > cellCount && idx < 0) {printf("insufficient cellcount"); return -1;}
while (cells[idx] != 0) {
while (cells[idx] != 0) {
/*Starting adding optimization*/
cells[idx]+=(5);
/*ending adding optimization*/
/*Starting right move level 1 optimization*/
idx+=(6);
/*Ending right move level 1 optimization*/
if(idx > cellCount && idx < 0) {printf("insufficient cellcount"); return -1;}
}
/*Starting right move level 1 optimization*/
idx+=(-1);
/*Ending right move level 1 optimization*/
if(idx > cellCount && idx < 0) {printf("insufficient cellcount"); return -1;}
/*Starting adding optimization*/
cells[idx]+=(1);
/*ending adding optimization*/
/*Starting right move level 1 optimization*/
idx+=(1);
/*Ending right move level 1 optimization*/
if(idx > cellCount && idx < 0) {printf("insufficient cellcount"); return -1;}
/*Starting adding optimization*/
cells[idx]+=(1);
/*ending adding optimization*/
while (cells[idx] != 0) {
/*Starting loop optimization*/
if(idx+-1 < 0 || idx+-1 > cellCount) {printf("insufficient cell count - multiplier movement -1\n"); return -1;} 
cells[idx+-1] += 8*cells[idx]; 
cells[idx] = 0;
/*end loop optimization*/
/*Starting right move level 1 optimization*/
idx+=(-1);
/*Ending right move level 1 optimization*/
if(idx > cellCount && idx < 0) {printf("insufficient cellcount"); return -1;}
if(outputIdx > outputLimit) {printf("insuficient output length: 3\n ", outputIdx); return -1;}
output[outputIdx] = cells[idx];
outputIdx++;
/*Starting right move level 1 optimization*/
idx+=(-5);
/*Ending right move level 1 optimization*/
if(idx > cellCount && idx < 0) {printf("insufficient cellcount"); return -1;}
}
/*Starting right move level 1 optimization*/
idx+=(8);
/*Ending right move level 1 optimization*/
if(idx > cellCount && idx < 0) {printf("insufficient cellcount"); return -1;}
}
while (cells[idx] != 0) {
if (input_pointer <= 255) {
cells[idx] = input[input_pointer];
input_pointer++;
} else {
printf("Insufficient input length"); return -1;}
if (input_pointer <= 255) {
cells[idx] = input[input_pointer];
input_pointer++;
} else {
printf("Insufficient input length"); return -1;}
if(outputIdx > outputLimit) {printf("insuficient output length: 3\n ", outputIdx); return -1;}
output[outputIdx] = cells[idx];
outputIdx++;
/*Starting adding optimization*/
cells[idx]+=(-1);
/*ending adding optimization*/
/*Starting adding optimization*/
cells[idx]+=(-1);
/*ending adding optimization*/
/*Starting adding optimization*/
cells[idx]+=(-1);
/*ending adding optimization*/
/*Starting adding optimization*/
cells[idx]+=(-1);
/*ending adding optimization*/
/*Starting right move level 1 optimization*/
idx+=(1);
/*Ending right move level 1 optimization*/
if(idx > cellCount && idx < 0) {printf("insufficient cellcount"); return -1;}
if(outputIdx > outputLimit) {printf("insuficient output length: 3\n ", outputIdx); return -1;}
output[outputIdx] = cells[idx];
outputIdx++;
if(outputIdx > outputLimit) {printf("insuficient output length: 3\n ", outputIdx); return -1;}
output[outputIdx] = cells[idx];
outputIdx++;
if(outputIdx > outputLimit) {printf("insuficient output length: 3\n ", outputIdx); return -1;}
output[outputIdx] = cells[idx];
outputIdx++;
}
} //end of rep_per_time_mesure
end_time = clock();
printf("start-end time: %f, %f\n", (double) start_time/CLOCKS_PER_SEC, (double) end_time/CLOCKS_PER_SEC);
all_times[t] = ((double)(end_time - start_time) / CLOCKS_PER_SEC) / (double) time_reps;
all_times[t] = log(all_times[t]);
} //end of mesurements
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
if (time_reps != 1 || time_mesures != 1) {
double sum_time = 0;
fprintf(result_file, "\nTimes: ");
for (int i = 0; i < time_mesures; i++){
fprintf(result_file, "%f, ", all_times[i]);
sum_time += all_times[i];}
double mean_time = sum_time / (double)time_mesures;
fprintf(result_file, "\nMean: %f", mean_time);
double std = 0;
for (int i = 0; i < time_mesures; i++){
std += pow(all_times[i] - mean_time, 2);}
std = sqrt(std / time_mesures);
fprintf(result_file, " +- %f dBs", std);
}}