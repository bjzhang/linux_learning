
#include <stdio.h>

int main(int argc, char *argv[])
{
    {
        char *args[6];

        printf("char *args[6]\n");
        printf("sizeof(args) is %lu\n", sizeof(args));
    }

    {
        char **args;

        printf("char **args\n");
        printf("sizeof(args) is %lu\n", sizeof(args));
    }

    {
        struct c {
            int a;
            char b[10];
        };
        struct c c1;

        printf("struct c c1\n");
        printf("sizeof(c1) is %lu\n", sizeof(c1));
    }

    {
        struct c {
            int a;
            char b[10];
        };
        struct c c1;

        printf("struct c c1\n");
        printf("sizeof(&c1) is %lu\n", sizeof(&c1));
    }
    return 0;
}
