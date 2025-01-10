// convert the contents of stdin to their ASCII values (e.g.,
// '\n' = 10) and spit out the <prog> array used in Figure 1 in
// Thompson's paper.
#include <stdio.h>
#include <string.h>

#define MAX_SIZE 1000000

int main(void)
{
    char buffer[MAX_SIZE];
    int bytes_read = fread(buffer, 1, MAX_SIZE, stdin);
    fprintf(stdout, "char prog[] = {\n");
    for (int i = 0; i < bytes_read; i++)
    {
        fprintf(stdout, "\t%d,%c", buffer[i], (i + 1) % 8 == 0 ? '\n' : ' ');
    }
    printf("0 };\n");
    printf("%s", buffer);
    return 0;
}
