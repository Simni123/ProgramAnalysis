#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include<unistd.h>

FILE *createFile(char *file_path, char *file_name)
{
    DIR *transpiled_folder = opendir(file_path);

    /*Creating a subfile name without .type*/
    char file_name_sub[1024];
    strcpy(file_name_sub, file_name);
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
    if (tFile == NULL)
    {
        printf("Could not create file\n");
        return NULL;
    }
    return tFile;
}

int main(int argc, char **argv)
{
    char *result_folder_path = "../UnitTestFiles";
    FILE *result_file = createFile(result_folder_path, "HelloWorld.txt");
    int input_pointer = 0;
    char *input;
    int input_len = 0;
    if (argc == 2)
    {
        input = argv[1];
        input_len = strlen(input);
    }
    const int cellCount = 100;
    unsigned char cells[cellCount];
    memset(cells, 0, cellCount);
    int idx = 0;
    unsigned char output[1024];
    memset(output, 0, sizeof(output));
    int outputIdx = 0;
    int time_measures = 10;
    double all_times[time_measures];
    for (int t = 0; t < time_measures; t++)
    {
        clock_t start_time, end_time;
        start_time = clock();
        input_pointer = 0;
        memset(cells, 0, cellCount);
        idx = 0;
        memset(output, 0, sizeof(output));
        outputIdx = 0;
        while (cells[idx] != 0)
        {
            if (input_pointer <= input_len)
            {
                cells[idx] = input[input_pointer];
                input_pointer++;
                printf("Insufficient input length");
                return -1;
            }
            if (outputIdx > 1024)
            {
                printf("insuficient output length");
                return -1;
            }
            output[outputIdx] = cells[idx];
            outputIdx++;
            while (cells[idx] != 0)
            {
                if (outputIdx > 1024)
                {
                    printf("insuficient output length");
                    return -1;
                }
                output[outputIdx] = cells[idx];
                outputIdx++;
            }
            if (input_pointer <= input_len)
            {
                cells[idx] = input[input_pointer];
                input_pointer++;
                printf("Insufficient input length");
                return -1;
            }
            if (outputIdx > 1024)
            {
                printf("insuficient output length");
                return -1;
            }
            output[outputIdx] = cells[idx];
            outputIdx++;
            if (outputIdx > 1024)
            {
                printf("insuficient output length");
                return -1;
            }
            output[outputIdx] = cells[idx];
            outputIdx++;
            if (input_pointer <= input_len)
            {
                cells[idx] = input[input_pointer];
                input_pointer++;
                printf("Insufficient input length");
                return -1;
            }
            if (input_pointer <= input_len)
            {
                cells[idx] = input[input_pointer];
                input_pointer++;
                printf("Insufficient input length");
                return -1;
            }
            if (input_pointer <= input_len)
            {
                cells[idx] = input[input_pointer];
                input_pointer++;
                printf("Insufficient input length");
                return -1;
            }
            cells[idx]++;
            if (input_pointer <= input_len)
            {
                cells[idx] = input[input_pointer];
                input_pointer++;
                printf("Insufficient input length");
                return -1;
            }
            cells[idx]--;
            if (input_pointer <= input_len)
            {
                cells[idx] = input[input_pointer];
                input_pointer++;
                printf("Insufficient input length");
                return -1;
            }
            idx--;
            if (idx < 0)
            {
                printf("idx less than zero");
                return -1;
            }
            idx++;
            if (idx > cellCount)
            {
                printf("insufficient cellcount");
                return -1;
            }
            if (input_pointer <= input_len)
            {
                cells[idx] = input[input_pointer];
                input_pointer++;
                printf("Insufficient input length");
                return -1;
            }
            while (cells[idx] != 0)
            {
            }
            if (outputIdx > 1024)
            {
                printf("insuficient output length");
                return -1;
            }
            output[outputIdx] = cells[idx];
            outputIdx++;
            if (outputIdx > 1024)
            {
                printf("insuficient output length");
                return -1;
            }
            output[outputIdx] = cells[idx];
            outputIdx++;
        }
        cells[idx]++;
        cells[idx]++;
        cells[idx]++;
        cells[idx]++;
        cells[idx]++;
        cells[idx]++;
        cells[idx]++;
        cells[idx]++;
        while (cells[idx] != 0)
        {
            idx++;
            if (idx > cellCount)
            {
                printf("insufficient cellcount");
                return -1;
            }
            cells[idx]++;
            cells[idx]++;
            cells[idx]++;
            cells[idx]++;
            while (cells[idx] != 0)
            {
                idx++;
                if (idx > cellCount)
                {
                    printf("insufficient cellcount");
                    return -1;
                }
                cells[idx]++;
                cells[idx]++;
                idx++;
                if (idx > cellCount)
                {
                    printf("insufficient cellcount");
                    return -1;
                }
                cells[idx]++;
                cells[idx]++;
                cells[idx]++;
                idx++;
                if (idx > cellCount)
                {
                    printf("insufficient cellcount");
                    return -1;
                }
                cells[idx]++;
                cells[idx]++;
                cells[idx]++;
                idx++;
                if (idx > cellCount)
                {
                    printf("insufficient cellcount");
                    return -1;
                }
                cells[idx]++;
                idx--;
                if (idx < 0)
                {
                    printf("idx less than zero");
                    return -1;
                }
                idx--;
                if (idx < 0)
                {
                    printf("idx less than zero");
                    return -1;
                }
                idx--;
                if (idx < 0)
                {
                    printf("idx less than zero");
                    return -1;
                }
                idx--;
                if (idx < 0)
                {
                    printf("idx less than zero");
                    return -1;
                }
                cells[idx]--;
            }
            idx++;
            if (idx > cellCount)
            {
                printf("insufficient cellcount");
                return -1;
            }
            cells[idx]++;
            idx++;
            if (idx > cellCount)
            {
                printf("insufficient cellcount");
                return -1;
            }
            cells[idx]++;
            idx++;
            if (idx > cellCount)
            {
                printf("insufficient cellcount");
                return -1;
            }
            cells[idx]--;
            idx++;
            if (idx > cellCount)
            {
                printf("insufficient cellcount");
                return -1;
            }
            idx++;
            if (idx > cellCount)
            {
                printf("insufficient cellcount");
                return -1;
            }
            cells[idx]++;
            while (cells[idx] != 0)
            {
                idx--;
                if (idx < 0)
                {
                    printf("idx less than zero");
                    return -1;
                }
            }
            idx--;
            if (idx < 0)
            {
                printf("idx less than zero");
                return -1;
            }
            cells[idx]--;
        }
        idx++;
        if (idx > cellCount)
        {
            printf("insufficient cellcount");
            return -1;
        }
        idx++;
        if (idx > cellCount)
        {
            printf("insufficient cellcount");
            return -1;
        }
        if (outputIdx > 1024)
        {
            printf("insuficient output length");
            return -1;
        }
        output[outputIdx] = cells[idx];
        outputIdx++;
        idx++;
        if (idx > cellCount)
        {
            printf("insufficient cellcount");
            return -1;
        }
        cells[idx]--;
        cells[idx]--;
        cells[idx]--;
        if (outputIdx > 1024)
        {
            printf("insuficient output length");
            return -1;
        }
        output[outputIdx] = cells[idx];
        outputIdx++;
        cells[idx]++;
        cells[idx]++;
        cells[idx]++;
        cells[idx]++;
        cells[idx]++;
        cells[idx]++;
        cells[idx]++;
        if (outputIdx > 1024)
        {
            printf("insuficient output length");
            return -1;
        }
        output[outputIdx] = cells[idx];
        outputIdx++;
        if (outputIdx > 1024)
        {
            printf("insuficient output length");
            return -1;
        }
        output[outputIdx] = cells[idx];
        outputIdx++;
        cells[idx]++;
        cells[idx]++;
        cells[idx]++;
        if (outputIdx > 1024)
        {
            printf("insuficient output length");
            return -1;
        }
        output[outputIdx] = cells[idx];
        outputIdx++;
        idx++;
        if (idx > cellCount)
        {
            printf("insufficient cellcount");
            return -1;
        }
        idx++;
        if (idx > cellCount)
        {
            printf("insufficient cellcount");
            return -1;
        }
        if (outputIdx > 1024)
        {
            printf("insuficient output length");
            return -1;
        }
        output[outputIdx] = cells[idx];
        outputIdx++;
        idx--;
        if (idx < 0)
        {
            printf("idx less than zero");
            return -1;
        }
        cells[idx]--;
        if (outputIdx > 1024)
        {
            printf("insuficient output length");
            return -1;
        }
        output[outputIdx] = cells[idx];
        outputIdx++;
        idx--;
        if (idx < 0)
        {
            printf("idx less than zero");
            return -1;
        }
        if (outputIdx > 1024)
        {
            printf("insuficient output length");
            return -1;
        }
        output[outputIdx] = cells[idx];
        outputIdx++;
        cells[idx]++;
        cells[idx]++;
        cells[idx]++;
        if (outputIdx > 1024)
        {
            printf("insuficient output length");
            return -1;
        }
        output[outputIdx] = cells[idx];
        outputIdx++;
        cells[idx]--;
        cells[idx]--;
        cells[idx]--;
        cells[idx]--;
        cells[idx]--;
        cells[idx]--;
        if (outputIdx > 1024)
        {
            printf("insuficient output length");
            return -1;
        }
        output[outputIdx] = cells[idx];
        outputIdx++;
        cells[idx]--;
        cells[idx]--;
        cells[idx]--;
        cells[idx]--;
        cells[idx]--;
        cells[idx]--;
        cells[idx]--;
        cells[idx]--;
        if (outputIdx > 1024)
        {
            printf("insuficient output length");
            return -1;
        }
        output[outputIdx] = cells[idx];
        outputIdx++;
        idx++;
        if (idx > cellCount)
        {
            printf("insufficient cellcount");
            return -1;
        }
        idx++;
        if (idx > cellCount)
        {
            printf("insufficient cellcount");
            return -1;
        }
        cells[idx]++;
        if (outputIdx > 1024)
        {
            printf("insuficient output length");
            return -1;
        }
        output[outputIdx] = cells[idx];
        outputIdx++;
        idx++;
        if (idx > cellCount)
        {
            printf("insufficient cellcount");
            return -1;
        }
        cells[idx]++;
        cells[idx]++;
        if (outputIdx > 1024)
        {
            printf("insuficient output length");
            return -1;
        }
        output[outputIdx] = cells[idx];
        outputIdx++;
        if (outputIdx > 1024)
        {
            printf("insuficient output length");
            return -1;
        }
        output[outputIdx] = cells[idx];
        outputIdx++;
        cells[idx]++;
        sleep(1);
        end_time = clock();
        printf("start-end time: %f, %f\n", (double) start_time/CLOCKS_PER_SEC, (double) end_time/CLOCKS_PER_SEC);
        all_times[t] = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    }
    fprintf(result_file, "Output: ");
    for (int i = 0; i < outputIdx; i++)
    {
        fprintf(result_file, "%c", (char)output[i]);
    }
    fprintf(result_file, "\n");
    fprintf(result_file, "Result:");
    for (int i = 0; i < cellCount; i++)
    {
        if (i % 10 == 0)
            fprintf(result_file, "\n");
        fprintf(result_file, "[%d]", cells[i]);
    }
    double sum_time = 0;
    fprintf(result_file, "\nTimes: ");
    for (int i = 0; i < time_measures; i++)
    {
        fprintf(result_file, "%f, ", all_times[i]);
        sum_time += all_times[i];
    }
    double mean_time = sum_time / (double)time_measures;
    fprintf(result_file, "\nMean: %f", mean_time);
    double std = 0;
    for (int i = 0; i < time_measures; i++)
    {
        std += pow(all_times[i] - mean_time, 2);
    }
    std = sqrt(std / time_measures);
    fprintf(result_file, " +- %f dBs", std);
}