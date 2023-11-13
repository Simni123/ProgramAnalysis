#include <stdio.h>
#include <dirent.h>
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
while (cells[idx] != 0) {
if (input_pointer <= input_len) {
cells[idx] = input[input_pointer];
input_pointer++;
} else {
printf("Insufficient input length");}
printf("%c", (char) cells[idx]);
while (cells[idx] != 0) {
printf("%c", (char) cells[idx]);
}
if (input_pointer <= input_len) {
cells[idx] = input[input_pointer];
input_pointer++;
} else {
printf("Insufficient input length");}
printf("%c", (char) cells[idx]);
printf("%c", (char) cells[idx]);
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
printf("%c", (char) cells[idx]);
printf("%c", (char) cells[idx]);
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
idx++;
if(idx > cellCount) {printf("insufficient cellcount"); return -1;}
cells[idx]--;
cells[idx]--;
cells[idx]--;
printf("%c", (char) cells[idx]);
cells[idx]++;
cells[idx]++;
cells[idx]++;
cells[idx]++;
cells[idx]++;
cells[idx]++;
cells[idx]++;
printf("%c", (char) cells[idx]);
printf("%c", (char) cells[idx]);
cells[idx]++;
cells[idx]++;
cells[idx]++;
printf("%c", (char) cells[idx]);
idx++;
if(idx > cellCount) {printf("insufficient cellcount"); return -1;}
idx++;
if(idx > cellCount) {printf("insufficient cellcount"); return -1;}
printf("%c", (char) cells[idx]);
idx--;
if(idx < 0) {printf("idx less than zero"); return -1;}
cells[idx]--;
printf("%c", (char) cells[idx]);
idx--;
if(idx < 0) {printf("idx less than zero"); return -1;}
printf("%c", (char) cells[idx]);
cells[idx]++;
cells[idx]++;
cells[idx]++;
printf("%c", (char) cells[idx]);
cells[idx]--;
cells[idx]--;
cells[idx]--;
cells[idx]--;
cells[idx]--;
cells[idx]--;
printf("%c", (char) cells[idx]);
cells[idx]--;
cells[idx]--;
cells[idx]--;
cells[idx]--;
cells[idx]--;
cells[idx]--;
cells[idx]--;
cells[idx]--;
printf("%c", (char) cells[idx]);
idx++;
if(idx > cellCount) {printf("insufficient cellcount"); return -1;}
idx++;
if(idx > cellCount) {printf("insufficient cellcount"); return -1;}
cells[idx]++;
printf("%c", (char) cells[idx]);
idx++;
if(idx > cellCount) {printf("insufficient cellcount"); return -1;}
cells[idx]++;
cells[idx]++;
printf("%c", (char) cells[idx]);
printf("\n");
printf("Result: \n");
for(int i = 0; i < cellCount; i++) {
printf("[%d]",cells[i]);
};
}