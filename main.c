#define _GNU_SOURCE
#include <stdio.h>
#include <string.h> 
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "header.h"

struct stat st = {0};

int main (){
    if (stat("/cache", &st) == -1)
    {
        mkdir("/cache", 0700);
    }
    struct args f;
    f.fps = 18;
    strcpy(f.name, "test1.mp4");
    f.time = 0;
    f.time2 = getdata("test1.mp4");
    struct args *threadmem = malloc(sizeof(struct args));
    strcpy(threadmem->name, f.name);
    threadmem->time = f.time;
    threadmem->fps = f.fps;
    threadmem->time2 = f.time2;
    pthread_t pid;
    pthread_create(&pid, NULL, init, threadmem);
    bar();
    stamp(f.time2, f.fps, f.name);
    pthread_join(pid, NULL);
    system("clear");
    
    return 0;
}
