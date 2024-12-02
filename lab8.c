#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>

float compute_exp(float *n)
{
    //(a/b + cd + ef) (g + h/k) m
    return (n[0] / n[1] + n[2] * n[3] + n[4] * n[5]) * (n[6] + n[7] / n[8]) * n[9];
}

int main()
{
    srand(time(NULL));
    float numbers[10];
    pid_t pid;
    FILE *file = fopen("input.txt", "r");
    if (file == NULL)
    {
        printf("Error opening file!\n");
        return 1;
    }
    while (!feof(file))
    {
        for (int i = 0; i < 10; i++)
        {
            fscanf(file, "%f", &numbers[i]);
        }
        pid = fork();

        if (pid == 0)
        {
            sleep(rand() % 10);
            printf("PID = %d, PPID = %d, result = %f\n", getpid(), getppid(), compute_exp(numbers));
            _exit(0);
        }
    }
    while (wait(NULL) > 0)
    {
    }
    printf("Main PID %d\n", getpid());
    fclose(file);
    return 0;
}