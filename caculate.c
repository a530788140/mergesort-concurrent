#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    FILE *fp = fopen("exe_time.txt", "r");
    FILE *output = fopen("output.txt", "w");
    if (!fp) {
        printf("ERROR opening input file exe_time.txt\n");
        exit(0);
    }
    int i = 0,thread_num = 0;
    double sum[7] = {0}, sum_t = 0.0;
    for(i=0; i<700; i++) {
        if (feof(fp)) {
            printf("ERROR: You need 100 datum instead of %d\n", i);
            printf("run 'make run' longer to get enough information\n\n");
            exit(0);
        }
        fscanf(fp,"%d %lf\n",&thread_num,&sum_t);
        //printf("thread_num = %d \n",thread_num);
        switch(thread_num) {
            case 1:
                sum[0]+=sum_t;
                break;
            case 2:
                sum[1]+=sum_t;
                break;
            case 4:
                sum[2]+=sum_t;
                break;
            case 8:
                sum[3]+=sum_t;
                break;
            case 16:
                sum[4]+=sum_t;
                break;
            case 32:
                sum[5]+=sum_t;
                break;
            case 64:
                sum[6]+=sum_t;
                break;
        }
    }
    fclose(fp);
    int tmp = 1;
    for(i=0; i<7; i++) {
        fprintf(output,"%d %lf\n",tmp,sum[i]/100);
        tmp = tmp*2;
    }
    fclose(output);


    return 0;
}
