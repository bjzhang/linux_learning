
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
	char s[] = "hello world";

	printf("sizeof %d\n", sizeof(s));
	printf("strlen %d\n", strlen(s));

	return 0;
}
