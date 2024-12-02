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
    char buffer[150];
    char *ptr = buffer;
    while (fgets(buffer, 150, file) != NULL)
    // while (!feof(file))
    {

        sscanf(buffer, "%f %f %f %f %f %f %f %f %f %f", &numbers[0], &numbers[1], &numbers[2],
               &numbers[3], &numbers[4], &numbers[5], &numbers[6], &numbers[7], &numbers[8], &numbers[9]);
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