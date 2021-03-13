
#include <stdio.h>      //fprintf, printf
#include <stdlib.h>     //exit

void sort(int *array, int size);
void output(int *array, int size);

int main(int argc, char *argv[])
{
    int *a = NULL;
    int i;
    int size;

    if ( argc < 2 ) {
        fprintf(stderr,  "no number input\n");
        exit(2);
    }

    size = argc - 1;
    a = malloc(sizeof(*a) * size);
    if ( !a ) {
        fprintf(stderr, "oom: want: %lu(num: %d)\n", sizeof(*a) * size, size);
        exit(2);
    }

    for ( i = 0; i < size; i++ ) {
        a[i] = atoi(argv[i+1]);
    }
    printf("before sort: ");
    output(a, size);

    sort(a, size);
    printf("after sort: ");
    output(a, size);

    free(a);
    a = NULL;
    return 0;
}

void sort(int *array, int size)
{
    int i, j;
    int temp;

#if 1
    //increase
    for ( i = 0; i < size; i++ ) {
        for ( j = i; j < size; j++ ) {
            if ( array[i] > array[j] ) {
                temp = array[j];
                array[j] = array[i];
                array[i] = temp;
            }
        }
        printf("round %d: ", i + 1);
        output(array, size);
    }
#else
    //decrease
    for ( i = 0; i < size; i++ ) {
        for ( j = i; j < size; j++ ) {
            if ( array[i] < array[j] ) {
                temp = array[j];
                array[j] = array[i];
                array[i] = temp;
            }
        }
        printf("round %d: ", i + 1);
        output(array, size);
    }
#endif
}

void output(int *array, int size)
{
    int i;

    for ( i = 0; i < size; i++ ) {
        printf("%d ", array[i]);
    }
    printf("\n");
}
