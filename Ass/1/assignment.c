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

void ProcessParams(ProcessManager* pm, char* file_name)
{
    pm->p_Process = 0;
    pm->m_tasks = 0;

    FILE* fp = 0;
    fp = fopen(file_name, "r");

    printf("Opening file: %s\n", file_name);
    if(fp)
    {
        int c = 0;
        while(c != -1)
        {
            if(pm->m_tasks == 0)
            {
                pm->p_Process = (Process*)malloc(sizeof(Process));
            }
            else
            {
                size_t size = (sizeof(Process) * (size_t)(pm->m_tasks + 1));
                pm->p_Process = (Process*)realloc(pm->p_Process, size);
            }
            memset(pm->p_Process + pm->m_tasks, 0, sizeof(Process));

            c = fscanf(fp, "%u %u %u",  &pm->p_Process[pm->m_tasks].m_arrivalTime, 
                                        &pm->p_Process[pm->m_tasks].m_burstTime, 
                                        &pm->p_Process[pm->m_tasks].m_priorityLevel);
            ++pm->m_tasks;
        }
        printf("Number of processes loaded: %d\n", pm->m_tasks);
    }
    fclose(fp);
}

void PrintProcessVars(ProcessManager* pm)
{
    printf("\n");
    for(unsigned int i = 0; i < pm->m_tasks; ++i)
    {
        printf("Process: %d\n", i);
        printf("Arrival Time: %u\n", pm->p_Process[i].m_arrivalTime);
        printf("Burst Time: %u\n", pm->p_Process[i].m_burstTime);
        printf("Priority Level: %u\n\n", pm->p_Process[i].m_priorityLevel);
    }
}

void Cleanup(ProcessManager* pm)
{
    free(pm->p_Process);
}

int main(int argc, char* argv[])
{
    (void)argc;
    ProcessManager ProcessMgr;
    ProcessParams(&ProcessMgr, *(argv + 1));
    PrintProcessVars(&ProcessMgr);
    Cleanup(&ProcessMgr);

    return 0;
}