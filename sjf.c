#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<stdbool.h>

typedef struct _Process {
    int pid;
    int bt;
    int art;
} Process;

void findWaitingTime(Process *proc, int n, int *wt) {
    bool check = false;
    int complete = 0, t = 0, minm = INT_MAX, shortest = 0, finish_time, *rt = (int *)malloc(n * sizeof(int));
    for(int i = 0; i < n; i++)
        rt[i] = proc[i].bt;
    while(complete != n) {
        for(int j = 0; j < n; j++) {
            if((proc[j].art <= t) &&
            (rt[j] < minm) && rt[j] > 0) {
                minm = rt[j];
                shortest = j;
                check = true;
            }
        }
        if(!check) {
            t++;
            continue;
        }
        rt[shortest]--;
        minm = rt[shortest];
        if(!minm) minm = INT_MAX;
        if(!rt[shortest]) {
            complete++;
            check = false;
            finish_time = t + 1;
            wt[shortest] = finish_time - proc[shortest].bt - proc[shortest].art;
            if(wt[shortest] < 0) wt[shortest] = 0;
        }
        t++;
    }
}

void findTurnAroundTime(Process *proc, int n, int *wt, int *tat) {
    for(int i = 0; i < n; i++)
        tat[i] = proc[i].bt + wt[i];
}

void findavgTime(Process *proc, int n) {
    int total_wt = 0, total_tat = 0, *wt = (int *)malloc(n * sizeof(int)), *tat = (int *)malloc(n * sizeof(int));
    findWaitingTime(proc, n, wt);
    findTurnAroundTime(proc, n, wt, tat);
    for(int i = 0; i < n; i++) {
        total_wt = total_wt + wt[i];
        total_tat = total_tat + tat[i];
        // printf("%d\n%d\n%d\n%d\n", &proc[i].pid, &proc[i].bt, &wt[i], &tat[i]);
    }
    // printf("%f\n%f\n", (float)total_wt / (float)n, (float)total_tat / (float)n);
}

int main(int argc, char **argv) {
    int n;
    scanf("%d", &n);
    Process *proc = (Process *)malloc(n * sizeof(Process));
    for(int i = 0; i < n; i++)
        scanf("%d%d%d", &proc[i].pid, &proc[i].bt, &proc[i].art);
    findavgTime(proc, n);
    return 0;
}