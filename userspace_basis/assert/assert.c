
#include <stdlib.h> //atoi, exit
#include <stdio.h>  //printf
#include <assert.h>

#ifndef TEST_NUM
#define TEST_NUM (10)
#endif // #ifndef TEST_NUM

int main(int argc, char *argv[])
{
    int num;

    if ( argc == 2 ) {
        num = atoi(argv[1]);
    } else {
        printf("usage: %s number\n", argv[0]);
        exit(1);
    }

    printf("test whether number is %d.\n", TEST_NUM);
    assert(num==TEST_NUM);
    printf("assert successful\n");

    return 0;
}

