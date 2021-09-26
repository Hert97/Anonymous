#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct 
{
    unsigned int m_arrivalTime;
    unsigned int m_burstTime;
    unsigned int m_priorityLevel;

}Process;

typedef struct 
{
    Process* p_Process;
    unsigned int m_tasks;
}ProcessManager;

int tasks = 0;

Process* ProcessParams(char* file_name)
{
    Process* pTasks = 0;

    FILE* fp = 0;
    fp = fopen(file_name, "r");

    printf("Opening file: %s\n", file_name);
    if(fp)
    {
        int c = 0;
        while(c != -1)
        {
            if(tasks == 0)
            {
                pTasks = (Process*)malloc(sizeof(Process));
            }
            else
            {
                size_t size = (sizeof(Process) * (size_t)(tasks + 1));
                pTasks = (Process*)realloc(pTasks, size);
            }
            memset(pTasks + tasks, 0, sizeof(Process));

            c = fscanf(fp, "%u %u %u", &pTasks[tasks].m_arrivalTime, &pTasks[tasks].m_burstTime, 
                                &pTasks[tasks].m_priorityLevel);
            ++tasks;
        }
        printf("Number of processes loaded: %d\n", tasks);
    }
    fclose(fp);
    return pTasks;
}

void PrintProcessVars(Process* pProcess)
{
    printf("\n");
    for(int i = 0; i < tasks; ++i)
    {
        printf("Process: %d\n", i);
        printf("Arrival Time: %u\n", pProcess[i].m_arrivalTime);
        printf("Burst Time: %u\n", pProcess[i].m_burstTime);
        printf("Priority Level: %u\n\n", pProcess[i].m_priorityLevel);
    }
}

void Cleanup(Process* pProcess)
{
    free(pProcess);
}

int main(int argc, char* argv[])
{
    (void)argc;
    Process* pProcess = ProcessParams(*(argv + 1));
    PrintProcessVars(pProcess);
    Cleanup(pProcess);
    return 0;
}