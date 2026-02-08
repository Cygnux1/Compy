#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUF_SIZE 16384

static char global_buf[BUF_SIZE];
static size_t global_len = 0;

static char func_buf[BUF_SIZE];
static char main_buf[BUF_SIZE];

static size_t func_len = 0;
static size_t main_len = 0;

static int func_indent = 0;
static int main_indent = 0;
static int in_function = 0;

// Helpers
static int starts_with(const char *s, const char *prefix) {
    return strncmp(s, prefix, strlen(prefix)) == 0;
}

static int count_indent(const char *line) {
    int spaces = 0;
    while (*line == ' ') {
        spaces++;
        line++;
    }
    return spaces / 4;
}

static int is_hash_comment(const char *s) {
    return s[0] == '#';
}

static int is_cpp_comment(const char *s) {
    return s[0] == '/' && s[1] == '/';
}

static int is_inline_c_block(const char *code) {
    return starts_with(code, "__inline_c__");
}

static int is_inline_c_global_block(const char *code) {
    return starts_with(code, "__inline_c_global__");
}

static void close_blocks(char *buf, size_t *len, int *indent_level, int target) {
    while (*indent_level > target) {
        *len += sprintf(buf + *len, "}\n");
        (*indent_level)--;
    }
}

static const char *find_matching_paren(const char *s) {
    int depth = 0;
    while (*s) {
        if (*s == '(') depth++;
        else if (*s == ')') {
            depth--;
            if (depth == 0) return s;
        }
        s++;
    }
    return NULL;
}

static const char *format_for_type(const char *type) {
    if (!type)                     return "%d";
    if (strcmp(type, "int") == 0)  return "%d";
    if (strcmp(type, "flt") == 0 || strcmp(type, "float") == 0) return "%f";
    if (strcmp(type, "double") == 0) return "%lf";
    if (strcmp(type, "char") == 0)   return "%c";
    if (strcmp(type, "str") == 0)    return "%s";
    if (strcmp(type, "bool") == 0)   return "%d";
    return "%d";
}

static int map_type(const char *line, char *out) {
    if (starts_with(line, "int ")) {
        sprintf(out, "int %s", line + 4);
    } else if (starts_with(line, "flt ")) {
        sprintf(out, "float %s", line + 4);
    } else if (starts_with(line, "char ")) {
        sprintf(out, "char %s", line + 5);
    } else if (starts_with(line, "str ")) {
        sprintf(out, "char* %s", line + 4);
    } else if (starts_with(line, "bool ")) {
        sprintf(out, "int %s", line + 5);
    } else if (starts_with(line, "double ")) {
        sprintf(out, "double %s", line + 7);
    } else if (starts_with(line, "long ")) {
        sprintf(out, "long long %s", line + 5);
    } else {
        return 0;
    }
    return 1;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "usage: compy <file.cmpy>\n");
        return 1;
    }

    FILE *in = fopen(argv[1], "r");
    if (!in) {
        fprintf(stderr, "file error\n");
        return 1;
    }

    char line[512];

    while (fgets(line, sizeof(line), in)) {
        line[strcspn(line, "\n")] = '\0';

        int indent = count_indent(line);
        const char *code = line + indent * 4;

        if (in_function) {
            close_blocks(func_buf, &func_len, &func_indent, indent);
            if (indent == 0) in_function = 0;
        } else {
            close_blocks(main_buf, &main_len, &main_indent, indent);
        }

        if (is_hash_comment(code)) {
            continue;
        }

        if (is_cpp_comment(code)) {
            if (in_function) {
                func_len += sprintf(func_buf + func_len, "%s\n", code);
            } else {
                main_len += sprintf(main_buf + main_len, "%s\n", code);
            }
            continue;
        }

        if (is_inline_c_global_block(code)) {
            int block_indent = indent;
            while (fgets(line, sizeof(line), in)) {
                line[strcspn(line, "\n")] = '\0';
                int cur_indent = count_indent(line);
                const char *content = line + cur_indent * 4;

                if (cur_indent == block_indent && strcmp(content, "}") == 0) {
                    break;
                }
                global_len += sprintf(global_buf + global_len, "%s\n", line);
            }
            continue;
        }

        if (is_inline_c_block(code)) {
            int block_indent = indent;

            if (in_function) {
                func_len += sprintf(func_buf + func_len, "{\n");
                func_indent++;
            } else {
                main_len += sprintf(main_buf + main_len, "{\n");
                main_indent++;
            }

            while (fgets(line, sizeof(line), in)) {
                line[strcspn(line, "\n")] = '\0';
                int cur_indent = count_indent(line);
                const char *content = line + cur_indent * 4;

                if (cur_indent == block_indent && strcmp(content, "}") == 0) {
                    break;
                }

                if (in_function) {
                    func_len += sprintf(func_buf + func_len, "%s\n", line);
                } else {
                    main_len += sprintf(main_buf + main_len, "%s\n", line);
                }
            }

            if (in_function) {
                func_len += sprintf(func_buf + func_len, "}\n");
                func_indent--;
            } else {
                main_len += sprintf(main_buf + main_len, "}\n");
                main_indent--;
            }
            continue;
        }

        if (starts_with(code, "def ")) {
            char name[64], args[256];
            sscanf(code, "def %[^ (](%[^)]):", name, args);

            func_len += sprintf(func_buf + func_len, "\nint %s(%s) {\n", name, args);

            in_function = 1;
            func_indent = 1;
            continue;
        }

        if (starts_with(code, "include ")) {
            const char *header = code + 8;
            while (*header == ' ') header++;

            char line_buf[256];
            if (*header == '"') {
                sprintf(line_buf, "#include %s\n", header);
            } else {
                sprintf(line_buf, "#include <%s>\n", header);
            }

            global_len += sprintf(global_buf + global_len, "%s", line_buf);
            continue;
        }

        if (starts_with(code, "if ")) {
            char cond[256];
            sscanf(code, "if %[^:]:", cond);

            if (in_function) {
                func_len += sprintf(func_buf + func_len, "if (%s) {\n", cond);
                func_indent++;
            } else {
                main_len += sprintf(main_buf + main_len, "if (%s) {\n", cond);
                main_indent++;
            }
            continue;
        }

        if (starts_with(code, "else:")) {
            if (in_function) {
                func_len += sprintf(func_buf + func_len, "else {\n");
                func_indent++;
            } else {
                main_len += sprintf(main_buf + main_len, "else {\n");
                main_indent++;
            }
            continue;
        }

        if (starts_with(code, "return ")) {
            func_len += sprintf(func_buf + func_len, "return %s;\n", code + 7);
            continue;
        }

        if (starts_with(code, "print(")) {
            char expr[256] = {0};
            char type[64] = {0};

            const char *start = code + 5;
            const char *end = find_matching_paren(start);
            if (!end) continue;

            strncpy(expr, start + 1, end - start - 1);
            expr[end - start - 1] = '\0';

            if (*(end + 1) == ':') {
                strcpy(type, end + 2);
            }

            const char *fmt = format_for_type(type[0] ? type : NULL);

            if (in_function) {
                func_len += sprintf(func_buf + func_len, "printf(\"%s\\n\", %s);\n", fmt, expr);
            } else {
                main_len += sprintf(main_buf + main_len, "printf(\"%s\\n\", %s);\n", fmt, expr);
            }
            continue;
        }

        if (starts_with(code, "fprint_str(") ||
            starts_with(code, "fprint_int(") ||
            starts_with(code, "fprint_flt(")) {

            char expr[256] = {0};
            const char *start = code + 6;

            const char *qstart = strchr(start, '"');
            const char *qend   = strrchr(start, '"');
            if (!qstart || !qend || qend <= qstart) continue;

            strncpy(expr, qstart + 1, qend - qstart - 1);
            expr[qend - qstart - 1] = '\0';

            char fmt[512] = {0};
            char vars[256] = {0};

            const char *p = expr;
            const char *specifier =
                starts_with(code, "fprint_int(") ? "%d" :
                starts_with(code, "fprint_flt(") ? "%f" : "%s";

            while (*p) {
                if (*p == '$' && *(p + 1) == '{') {
                    const char *vstart = p + 2;
                    const char *vend = strchr(vstart, '}');
                    if (!vend) break;

                    strncat(fmt, specifier, 511);
                    strncat(vars, vstart, vend - vstart);
                    strcat(vars, ",");

                    p = vend + 1;
                } else {
                    char tmp[2] = {*p, '\0'};
                    strncat(fmt, tmp, 511);
                    p++;
                }
            }

            size_t vlen = strlen(vars);
            if (vlen > 0 && vars[vlen - 1] == ',') vars[vlen - 1] = '\0';

            if (in_function) {
                func_len += sprintf(func_buf + func_len, "printf(\"%s\\n\", %s);\n", fmt, vars);
            } else {
                main_len += sprintf(main_buf + main_len, "printf(\"%s\\n\", %s);\n", fmt, vars);
            }
            continue;
        }

        // Variable declaration / assignment fallback
        if (*code) {
            char mapped[256];

            if (in_function) {
                if (map_type(code, mapped)) {
                    func_len += sprintf(func_buf + func_len, "%s;\n", mapped);
                } else if (strchr(code, '=') && !strstr(code, "==")) {
                    func_len += sprintf(func_buf + func_len, "int %s;\n", code);
                } else {
                    func_len += sprintf(func_buf + func_len, "%s\n", code);
                }
            } else {
                if (map_type(code, mapped)) {
                    main_len += sprintf(main_buf + main_len, "%s;\n", mapped);
                } else if (strchr(code, '=') && !strstr(code, "==")) {
                    main_len += sprintf(main_buf + main_len, "int %s;\n", code);
                } else {
                    main_len += sprintf(main_buf + main_len, "%s\n", code);
                }
            }
        }
    }

    fclose(in);

    close_blocks(func_buf, &func_len, &func_indent, 0);
    close_blocks(main_buf, &main_len, &main_indent, 0);

    FILE *out = fopen("out.c", "w");
    if (!out) {
        fprintf(stderr, "cannot write out.c\n");
        return 1;
    }

    fprintf(out, "#include <stdio.h>\n\n%s\n%s\nint main(void) {\n%s    return 0;\n}\n",
            global_buf, func_buf, main_buf);

    fclose(out);

    printf("Compy: Successfully Compiled\n\n");
    return 0;
}