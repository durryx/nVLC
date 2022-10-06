#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h> 
#include <time.h>
#include <stdbool.h>
#include <pthread.h>

/*get video information*/

#define BUFSIZE 128

double getdata(char name[]){
    char cmd[40];
    char buf[BUFSIZE];
    sprintf(cmd, "./info.sh %s\n", name);
    FILE *fp;
    if ((fp = popen(cmd, "r")) == NULL) {
        printf("Error opening pipe!\n");
        return -1;
    }
    while (fgets(buf, BUFSIZE, fp) != NULL) {}
    pclose(fp);
    double duration;
    sscanf(buf, "%lf", &duration);
    return duration;
}

struct args{
        int fps;
        int time;
        double time2;
        char name[30];
};


/*initialize converting function, multithreaded conversion */
struct interval{
        int fps;
        double time;
        double time2;
        char path[30];
};

void* convert(void* arg){
    struct interval* current = (struct interval*) arg;
    char cmd[500];
    sprintf(cmd, "ffmpeg -i %s -rle 1 -vf scale=740:-1 -ss %lf -t %lf -r %d -q:v 31 cache/IMG-%%010d.jpg > /dev/null 2>&1\n ", current->path, current->time, current->time2, current->fps);
    system(cmd);
    free(current);
    return NULL;
}


void* init(void* arg){
    struct args* thread = (struct args*) arg;
    struct interval* mem0 = malloc(sizeof(struct interval));
    strcpy(mem0->path, thread->name);
    mem0->fps = thread->fps;
    mem0->time = 0;
    mem0->time2 = thread->time2;
    pthread_t process0;
    pthread_create(&process0, NULL, convert, mem0);
    int k = pthread_join(process0, NULL);
    if (k){
        perror("process not joined correctly: ");
        return NULL;
    }
    free(thread);
    return NULL;
}


/*progression bar*/
void bar(){
    system("./bar.sh");
    system("clear");
    return;
}


/*jp2a converting and printing*/
int stamp(double time2, int fps, char name[]){
    int i = 0;
    double temp = 1/fps*(10^6);
    clock_t start, end;
    double wtime;
    while (i <= time2*fps)
    {
        start = clock();
        char command[35] = "jp2a ";
        char file[30];
        sprintf(file, "cache/IMG-%010d.jpg", i);
        strcat(command, file);
        system(command);
        if (remove(file) != 0){
            perror("error deleting file: ");
        }
        i++;
        end = clock();
        wtime = ((double)(end - start)*(10^6))/CLOCKS_PER_SEC;
        usleep(temp-wtime);
    }
    return 0;
}


