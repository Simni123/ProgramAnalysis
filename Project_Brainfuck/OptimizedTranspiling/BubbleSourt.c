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
idx++;
if(idx > cellCount) {printf("insufficient cellcount"); return -1;}
idx++;
if(idx > cellCount) {printf("insufficient cellcount"); return -1;}
if (input_pointer <= 255) {
cells[idx] = input[input_pointer];
input_pointer++;
} else {
printf("Insufficient input length");}
while (cells[idx] != 0) {
idx++;
if(idx > cellCount) {printf("insufficient cellcount"); return -1;}
idx++;
if(idx > cellCount) {printf("insufficient cellcount"); return -1;}
if (input_pointer <= 255) {
cells[idx] = input[input_pointer];
input_pointer++;
} else {
printf("Insufficient input length");}
}
idx--;
if(idx < 0) {printf("idx less than zero"); return -1;}
idx--;
if(idx < 0) {printf("idx less than zero"); return -1;}
while (cells[idx] != 0) {
while (cells[idx] != 0) {
idx--;
if(idx < 0) {printf("idx less than zero"); return -1;}
idx--;
if(idx < 0) {printf("idx less than zero"); return -1;}
}
idx++;
if(idx > cellCount) {printf("insufficient cellcount"); return -1;}
idx++;
if(idx > cellCount) {printf("insufficient cellcount"); return -1;}
idx++;
if(idx > cellCount) {printf("insufficient cellcount"); return -1;}
idx++;
if(idx > cellCount) {printf("insufficient cellcount"); return -1;}
while (cells[idx] != 0) {
idx--;
if(idx < 0) {printf("idx less than zero"); return -1;}
idx--;
if(idx < 0) {printf("idx less than zero"); return -1;}
while (cells[idx] != 0) {
if(idx+1 > cellCount) {printf("insufficient cellcount"); return -1;}
cells[idx+1]+=1;
idx--;
if(idx < 0) {printf("idx less than zero"); return -1;}
cells[idx]++;
idx++;
if(idx > cellCount) {printf("insufficient cellcount"); return -1;}
cells[idx]--;
}
idx++;
if(idx > cellCount) {printf("insufficient cellcount"); return -1;}
idx++;
if(idx > cellCount) {printf("insufficient cellcount"); return -1;}
while (cells[idx] != 0) {
if(idx+1 > cellCount) {printf("insufficient cellcount"); return -1;}
cells[idx+1]+=1;
idx--;
if(idx < 0) {printf("idx less than zero"); return -1;}
idx--;
if(idx < 0) {printf("idx less than zero"); return -1;}
idx--;
if(idx < 0) {printf("idx less than zero"); return -1;}
while (cells[idx] != 0) {
cells[idx]--;
idx++;
if(idx > cellCount) {printf("insufficient cellcount"); return -1;}
}
idx++;
if(idx > cellCount) {printf("insufficient cellcount"); return -1;}
while (cells[idx] != 0) {
idx--;
if(idx < 0) {printf("idx less than zero"); return -1;}
}
idx++;
if(idx > cellCount) {printf("insufficient cellcount"); return -1;}
idx++;
if(idx > cellCount) {printf("insufficient cellcount"); return -1;}
cells[idx]--;
}
idx--;
if(idx < 0) {printf("idx less than zero"); return -1;}
idx--;
if(idx < 0) {printf("idx less than zero"); return -1;}
idx--;
if(idx < 0) {printf("idx less than zero"); return -1;}
while (cells[idx] != 0) {
while (cells[idx] != 0) {
cells[idx]--;
}
idx++;
if(idx > cellCount) {printf("insufficient cellcount"); return -1;}
idx++;
if(idx > cellCount) {printf("insufficient cellcount"); return -1;}
while (cells[idx] != 0) {
if(idx+1 > cellCount) {printf("insufficient cellcount"); return -1;}
cells[idx+1]+=1;
cells[idx]--;
}
idx++;
if(idx > cellCount) {printf("insufficient cellcount"); return -1;}
idx++;
if(idx > cellCount) {printf("insufficient cellcount"); return -1;}
while (cells[idx] != 0) {
if(idx-3 < 0) {printf("data pointer < zero"); return -1;}
cells[idx-3]+=1;
cells[idx]--;
}
}
idx++;
if(idx > cellCount) {printf("insufficient cellcount"); return -1;}
idx++;
if(idx > cellCount) {printf("insufficient cellcount"); return -1;}
while (cells[idx] != 0) {
while (cells[idx] != 0) {
if(idx-1 < 0) {printf("data pointer < zero"); return -1;}
cells[idx-1]+=1;
cells[idx]--;
}
idx++;
if(idx > cellCount) {printf("insufficient cellcount"); return -1;}
idx++;
if(idx > cellCount) {printf("insufficient cellcount"); return -1;}
}
idx--;
if(idx < 0) {printf("idx less than zero"); return -1;}
}
idx--;
if(idx < 0) {printf("idx less than zero"); return -1;}
idx--;
if(idx < 0) {printf("idx less than zero"); return -1;}
while (cells[idx] != 0) {
if(idx+2 > cellCount) {printf("insufficient cellcount"); return -1;}
cells[idx+2]+=1;
cells[idx]--;
}
idx--;
if(idx < 0) {printf("idx less than zero"); return -1;}
idx--;
if(idx < 0) {printf("idx less than zero"); return -1;}
}
idx++;
if(idx > cellCount) {printf("insufficient cellcount"); return -1;}
idx++;
if(idx > cellCount) {printf("insufficient cellcount"); return -1;}
idx++;
if(idx > cellCount) {printf("insufficient cellcount"); return -1;}
idx++;
if(idx > cellCount) {printf("insufficient cellcount"); return -1;}
while (cells[idx] != 0) {
printf("%c", (char) cells[idx]);
idx++;
if(idx > cellCount) {printf("insufficient cellcount"); return -1;}
idx++;
if(idx > cellCount) {printf("insufficient cellcount"); return -1;}
}
printf("\n");
printf("Result: \n");
for(int i = 0; i < cellCount; i++) {
printf("[%d]",cells[i]);
};
}