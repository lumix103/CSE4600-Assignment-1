#include <pthread.h>
#include <stdio.h>
#include <cstdint>

using namespace std;

void* csu(void* data);
void* sb(void* data);
void* csusb(void* data);
void* number(void* data);

bool is_done = false;
bool not_solved = true;
pthread_mutex_t lock;
pthread_cond_t done;
pthread_condattr_t done_attr;

int main(int argc, char** argv) {

    int n = 10; //Chnage me to see other results

    pthread_t csu_id, sb_id, csusb_id, number_id;
    pthread_attr_t csu_attr, sb_attr, csusb_attr, number_attr;

    pthread_attr_init(&csu_attr);
    pthread_attr_init(&sb_attr);
    pthread_attr_init(&csusb_attr);
    pthread_attr_init(&number_attr);

    pthread_condattr_init(&done_attr);

    pthread_cond_init(&done, &done_attr);

    pthread_create(&csu_id, &csu_attr, csu, (void *)n);
    pthread_create(&sb_id, &sb_attr, sb, (void *)n);
    pthread_create(&csusb_id, &csusb_attr, csusb, (void *)n);
    pthread_create(&number_id, &number_attr, number, (void *)n);


    pthread_join(csusb_id, NULL);
    pthread_join(csu_id, NULL);
    pthread_join(sb_id, NULL);
    pthread_join(number_id, NULL);

    printf("Done!\n");
    return 0;
}

void* csu(void* data) {
    int n = (intptr_t)data;
    pthread_mutex_lock(&lock);
    while(!is_done)
        pthread_cond_wait(&done, &lock);
    is_done = false;
    if(not_solved) {
        if(n % 2 == 0) {
            printf("CSU\n");
            not_solved = false;
        }
    }
    is_done = true;
    pthread_cond_signal(&done);
    pthread_mutex_unlock(&lock);
    return NULL;
}

void* sb(void* data) {
    int n = (intptr_t)data;
    pthread_mutex_lock(&lock);
    while(!is_done)
        pthread_cond_wait(&done, &lock);
    is_done = false;
    if(not_solved) {
        if(n % 5 == 0) {
            printf("SB\n");
            not_solved = false;
        }
    }
    is_done = true;
    pthread_cond_signal(&done);
    pthread_mutex_unlock(&lock);
    return NULL;
}

void* csusb(void* data) {
    int n = (intptr_t)data;
    pthread_mutex_lock(&lock);
    if(n % 2 == 0 && n % 5 == 0) {
        printf("CSUSB\n");
        not_solved = false;
    }
    is_done = true;
    pthread_cond_signal(&done);
    pthread_mutex_unlock(&lock);
    return NULL;
}

void* number(void* data) {
    int n = (intptr_t)data;
    pthread_mutex_lock(&lock);
    while(!is_done)
        pthread_cond_wait(&done, &lock);
    is_done = false;
    if(not_solved) {     
        if(n % 2 != 0 && n % 5 != 0) {
            printf("%d\n", n);
            not_solved = false;
        }
    }
    is_done = true;
    pthread_cond_signal(&done);
    pthread_mutex_unlock(&lock);
    return NULL;
}