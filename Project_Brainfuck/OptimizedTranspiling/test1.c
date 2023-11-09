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
if(idx+2 > cellCount) {printf("insufficient cellcount"); return -1;}
cells[idx+2]+=3;
cells[idx]--;
idx++;
if(idx > cellCount) {printf("insufficient cellcount"); return -1;}
idx++;
if(idx > cellCount) {printf("insufficient cellcount"); return -1;}
idx++;
if(idx > cellCount) {printf("insufficient cellcount"); return -1;}
idx++;
if(idx > cellCount) {printf("insufficient cellcount"); return -1;}
while (cells[idx] != 0) {
cells[idx]--;
}
if(idx-3 < 0) {printf("data pointer < zero"); return -1;}
cells[idx-3]-=3;
printf("\n");
printf("Result: \n");
for(int i = 0; i < cellCount; i++) {
printf("[%d]",cells[i]);
};
}