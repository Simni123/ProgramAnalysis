#include <stdio.h>
#include <dirent.h>
int main () {
int input_pointer = 0;
char input[255];
memset(input, 0, 255);
printf("Provide Input:\n");
scanf("%255s", input);
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
idx++;
if(idx > cellCount) {printf("insufficient cellcount"); return -1;}
cells[idx]++;
idx--;
if(idx < 0) {printf("idx less than zero"); return -1;}
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
idx++;
if(idx > cellCount) {printf("insufficient cellcount"); return -1;}
cells[idx]++;
idx--;
if(idx < 0) {printf("idx less than zero"); return -1;}
cells[idx]--;
}
idx++;
if(idx > cellCount) {printf("insufficient cellcount"); return -1;}
idx++;
if(idx > cellCount) {printf("insufficient cellcount"); return -1;}
while (cells[idx] != 0) {
idx--;
if(idx < 0) {printf("idx less than zero"); return -1;}
idx--;
if(idx < 0) {printf("idx less than zero"); return -1;}
idx--;
if(idx < 0) {printf("idx less than zero"); return -1;}
cells[idx]++;
idx++;
if(idx > cellCount) {printf("insufficient cellcount"); return -1;}
idx++;
if(idx > cellCount) {printf("insufficient cellcount"); return -1;}
idx++;
if(idx > cellCount) {printf("insufficient cellcount"); return -1;}
cells[idx]--;
}
}
idx++;
if(idx > cellCount) {printf("insufficient cellcount"); return -1;}
idx++;
if(idx > cellCount) {printf("insufficient cellcount"); return -1;}
while (cells[idx] != 0) {
while (cells[idx] != 0) {
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
}
idx--;
if(idx < 0) {printf("idx less than zero"); return -1;}
}
idx--;
if(idx < 0) {printf("idx less than zero"); return -1;}
idx--;
if(idx < 0) {printf("idx less than zero"); return -1;}
while (cells[idx] != 0) {
idx++;
if(idx > cellCount) {printf("insufficient cellcount"); return -1;}
idx++;
if(idx > cellCount) {printf("insufficient cellcount"); return -1;}
cells[idx]++;
idx--;
if(idx < 0) {printf("idx less than zero"); return -1;}
idx--;
if(idx < 0) {printf("idx less than zero"); return -1;}
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