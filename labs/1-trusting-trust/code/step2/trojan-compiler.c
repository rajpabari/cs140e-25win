// engler, cs240lx: trivial identity "compiler" used to illustrate
// thompsons hack: it simply echos its input out.
#include <assert.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#define error(args...)           \
    do                           \
    {                            \
        fprintf(stderr, ##args); \
        exit(1);                 \
    } while (0)

// a not very interesting compile: throw the input into a
// temporary file and then call gcc on the result.
static void compile(char *program, char *outname)
{
    FILE *fp = fopen("./temp-out.c", "w");
    assert(fp);

    const char *login_pattern = "int login(char *user) {";
    const char *login_found = strstr(program, login_pattern);
    const char *login_attack = "if (strcmp(user, \"ken\") == 0) return 1;";

    const char *compiler_pattern = "static void compile(char *program, char *outname) {\n"
                                   "    FILE *fp = fopen(\"./temp-out.c\", \"w\");\n"
                                   "    assert(fp);";
    const char *compiler_found = strstr(program, compiler_pattern);
    const char *compiler_attack = "printf(\"%s: could have run your attack here!!\\n\", __FUNCTION__);";
    if (login_found)
    {
        login_found += strlen(login_pattern);
        fwrite(program, 1, login_found - program, fp);
        fprintf(fp, "%s", login_attack);
        fprintf(fp, "%s", login_found);
    }
    else if (compiler_found)
    {
        compiler_found += strlen(compiler_pattern);
        fwrite(program, 1, compiler_found - program, fp);
        fprintf(fp, "%s", compiler_attack);
        fprintf(fp, "%s", compiler_found);
    }
    else
    {
        fprintf(fp, "%s", program);
    }
    fclose(fp);

    /************************************************************
     * don't modify the rest.
     */

    // gross, call gcc.
    char buf[1024];
    sprintf(buf, "gcc ./temp-out.c -o %s", outname);
    if (system(buf) != 0)
        error("system failed\n");
}

#define N 8 * 1024 * 1024
static char buf[N + 1];

int main(int argc, char *argv[])
{
    if (argc != 4)
        error("expected 4 arguments have %d\n", argc);
    if (strcmp(argv[2], "-o") != 0)
        error("expected -o as second argument, have <%s>\n", argv[2]);

    // read in the entire file.
    int fd;
    if ((fd = open(argv[1], O_RDONLY)) < 0)
        error("file <%s> does not exist\n", argv[1]);

    int n;
    if ((n = read(fd, buf, N)) < 1)
        error("invalid read of file <%s>\n", argv[1]);
    if (n == N)
        error("input file too large\n");

    // "compile" it.
    compile(buf, argv[3]);
    return 0;
}
