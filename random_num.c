#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char const *argv[])
{
    srand(time(NULL));
    int num_count, i;
    FILE *input = fopen("input.txt", "w");
    num_count = atoi(argv[1]);
    int *arr;
    int  pos , tmp;
    arr = (int *) malloc(sizeof(int) * num_count);

    for (i = 0; i < num_count; i++)
        arr[i] = i + 1;

    for (i = 0; i < num_count; i++) {
        pos = rand() % num_count;
        tmp = arr[i];
        arr[i] = arr [pos];
        arr[pos] = tmp;
    }

    for (i = 0; i < num_count; i++)
        fprintf(input, "%d\n",arr[i]);

    free(arr);
    fclose(input);

    return 0;
}
