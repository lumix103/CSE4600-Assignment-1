#include <pthread.h>
#include <stdio.h>
#include <cstdint>

int matrix_a[4][3] = {
    {5, 2, 3},
    {4, 5, 7},
    {6, 3, 7},
    {1, 3, 4},
};

int matrix_b[3][4] = {
    {4, 5, 6, 1},
    {3, 2, 3, 5},
    {2, 8, 7, 7},
};

int matrix_c[4][4] = {
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
};

void* calculate_matrix(void* data);

void print_matrix_c();

int main(int argc, char** argv) {

    pthread_t col1, col2, col3, col4;
    pthread_attr_t col1_attr, col2_attr, col3_attr, col4_attr;

    pthread_attr_init(&col1_attr);
    pthread_attr_init(&col2_attr);
    pthread_attr_init(&col3_attr);
    pthread_attr_init(&col4_attr);

    pthread_create(&col1, &col1_attr, calculate_matrix, (void*) 0);
    pthread_create(&col2, &col2_attr, calculate_matrix, (void*) 1);
    pthread_create(&col3, &col3_attr, calculate_matrix, (void*) 2);
    pthread_create(&col4, &col4_attr, calculate_matrix, (void*) 3);

    pthread_join(col1, NULL);
    pthread_join(col2, NULL);
    pthread_join(col3, NULL);
    pthread_join(col4, NULL);

    print_matrix_c();
    return 0;
}

void* calculate_matrix(void* data) {
    int k = (intptr_t)data;
    for(int i = 0; i < 4; i++)
        for(int j = 0; j< 4; j++)
                matrix_c[i][j] += matrix_a[i][k] * matrix_b[k][j];
    return NULL;
}

void print_matrix_c() {
    for(int i =0; i < 4; i++) {
        for(int j=0; j < 4; j++)
            printf("%d ", matrix_c[i][j]);
        printf("\n");
    }
}