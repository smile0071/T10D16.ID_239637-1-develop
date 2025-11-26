#include "s21_string.h"

#include <stdio.h>
#include <stdlib.h>

/* Helper to print a representation of input string (handles NULL) */
static void print_input(const char* s) {
    if (s == NULL) {
        printf("Input: NULL\n");
    } else {
        printf("Input: \"%s\"\n", s);
    }
}

void s21_strlen_test(void) {
    /* Test cases: normal, empty (boundary), embedded NUL, abnormal (NULL) */
    const char* tests[] = {"hello", "", "a\0b", NULL};
    size_t expected[] = {5u, 0u, 1u, 0u};
    const size_t num = sizeof(tests) / sizeof(tests[0]);

    printf("Running s21_strlen_test (total %zu tests)\n\n", num);
    for (size_t i = 0; i < num; ++i) {
        const char* in = tests[i];
        size_t out = s21_strlen(in);
        print_input(in);
        printf("Output: %zu\n", out);
        if (out == expected[i]) {
            printf("Result: SUCCESS\n");
        } else {
            printf("Result: FAIL (expected %zu)\n", expected[i]);
        }
        if (i + 1 < num) printf("\n");
    }
}

/* s21_strcmp_test: test cases include equal strings, lexicographic difference,
   empty vs non-empty, and NULL handling (matches s21_strcmp contract above). */
void s21_strcmp_test(void) {
    const char* a_tests[][2] = {
        {"hello", "hello"}, /* equal -> 0 */
        {"abc", "abd"},     /* differ at last char -> negative (-1 expected) */
        {"abc", "ab"},      /* longer -> positive ('c' - '\0' = 99) */
        {NULL, "non"},      /* NULL vs non-NULL -> -1 per implementation */
        {NULL, NULL}        /* both NULL -> 0 */
    };
    int expected[] = {0, -1, (int)('c' - '\0'), -1, 0};
    const size_t num = sizeof(a_tests) / sizeof(a_tests[0]);

    printf("\nRunning s21_strcmp_test (total %zu tests)\n\n", num);
    for (size_t i = 0; i < num; ++i) {
        const char* s1 = a_tests[i][0];
        const char* s2 = a_tests[i][1];
        if (s1 == NULL)
            printf("Input s1: NULL\n");
        else
            printf("Input s1: \"%s\"\n", s1);
        if (s2 == NULL)
            printf("Input s2: NULL\n");
        else
            printf("Input s2: \"%s\"\n", s2);
        int out = s21_strcmp(s1, s2);
        printf("Output: %d\n", out);
        if (out == expected[i]) {
            printf("Result: SUCCESS\n");
        } else {
            printf("Result: FAIL (expected %d)\n", expected[i]);
        }
        if (i + 1 < num) printf("\n");
    }
}

/* s21_strcpy_test: normal, empty src, src == NULL */
void s21_strcpy_test(void) {
    const char* src_tests[] = {"sample", "", NULL};
    const size_t num = sizeof(src_tests) / sizeof(src_tests[0]);

    printf("\nRunning s21_strcpy_test (total %zu tests)\n\n", num);
    for (size_t i = 0; i < num; ++i) {
        const char* src = src_tests[i];
        /* prepare destination buffer */
        char dest[32];
        /* fill dest with a marker to observe changes */
        for (size_t j = 0; j < sizeof(dest); ++j) dest[j] = '#';
        /* call */
        char* ret = s21_strcpy(dest, src);
        if (src == NULL) {
            printf("Input src: NULL\n");
        } else {
            printf("Input src: \"%s\"\n", src);
        }
        printf("Output dest: \"%s\"\n", (ret != NULL) ? dest : "NULL");
        /* expected */
        const char* expected = (src == NULL) ? "" : src;
        if (ret != NULL && s21_strcmp(dest, expected) == 0) {
            printf("Result: SUCCESS\n");
        } else if (ret == NULL && expected == NULL) {
            printf("Result: SUCCESS\n");
        } else {
            printf("Result: FAIL (expected \"%s\")\n", expected);
        }
        if (i + 1 < num) printf("\n");
    }
}

/* s21_strcat_test: normal append, empty dest, empty src, src NULL, dest NULL */
void s21_strcat_test(void) {
    const struct {
        const char* d;
        const char* s;
        const char* expect;
    } tests[] = {
        {"Hello, ", "World!", "Hello, World!"},
        {"", "abc", "abc"},
        {"start", "", "start"},
        {"X", NULL, "X"},
    };
    const size_t num = sizeof(tests) / sizeof(tests[0]);

    printf("\nRunning s21_strcat_test (total %zu tests)\n\n", num + 1);
    for (size_t i = 0; i < num; ++i) {
        const char* init_dest = tests[i].d;
        const char* src = tests[i].s;
        const char* expected = tests[i].expect;
        /* prepare destination buffer */
        char dest[64];
        if (init_dest) {
            /* copy initial content */
            size_t j = 0;
            while (init_dest[j]) {
                dest[j] = init_dest[j];
                ++j;
            }
            dest[j] = '\0';
        } else {
            dest[0] = '\0';
        }
        /* print inputs */
        printf("Input dest: \"%s\"\n", dest);
        if (src == NULL)
            printf("Input src: NULL\n");
        else
            printf("Input src: \"%s\"\n", src);
        /* call */
        char* ret = s21_strcat(dest, src);
        if (ret == NULL) {
            printf("Output: NULL\n");
        } else {
            printf("Output dest: \"%s\"\n", dest);
        }
        /* verify */
        if (ret != NULL && s21_strcmp(dest, expected) == 0) {
            printf("Result: SUCCESS\n");
        } else if (ret == NULL && expected == NULL) {
            printf("Result: SUCCESS\n");
        } else {
            printf("Result: FAIL (expected \"%s\")\n", expected ? expected : "NULL");
        }
        if (i + 1 < num) printf("\n");
    }

    /* additional test: dest == NULL should return NULL */
    printf("\nInput dest: NULL\nInput src: \"a\"\n");
    char* r = s21_strcat(NULL, "a");
    if (r == NULL) {
        printf("Output: NULL\nResult: SUCCESS\n");
    } else {
        printf("Output: non-NULL\nResult: FAIL (expected NULL)\n");
    }
}

void s21_strchr_test(void) {
    /* Tests:
       1) find existing char -> expect pointer to substring
       2) char not found -> expect NULL
       3) search for '\\0' -> expect pointer to empty string at end
       4) s == NULL -> expect NULL
    */
    const char* tests_s[] = {
        "hello", /* case 0 */
        "abc",   /* case 1 */
        "xyz",   /* case 2 (will search '\0') */
        NULL     /* case 3 */
    };
    int tests_c[] = {'l', 'z', '\0', 'a'};
    /* expected substrings (NULL means expect NULL) */
    const char* expected[] = {"llo", NULL, "", NULL};
    const size_t num = sizeof(tests_s) / sizeof(tests_s[0]);

    printf("\nRunning s21_strchr_test (total %zu tests)\n\n", num);
    for (size_t i = 0; i < num; ++i) {
        const char* s = tests_s[i];
        int c = tests_c[i];
        if (s == NULL)
            printf("Input s: NULL\n");
        else
            printf("Input s: \"%s\"\n", s);
        printf("Input c: '%c' (code %d)\n", (char)c, c);
        char* out = s21_strchr(s, c);
        if (out == NULL) {
            printf("Output: NULL\n");
        } else {
            printf("Output: \"%s\"\n", out);
        }
        /* verify */
        if (expected[i] == NULL) {
            if (out == NULL) {
                printf("Result: SUCCESS\n");
            } else {
                printf("Result: FAIL (expected NULL)\n");
            }
        } else {
            /* expected is a substring; compare via s21_strcmp */
            if (out != NULL && s21_strcmp(out, expected[i]) == 0) {
                printf("Result: SUCCESS\n");
            } else {
                printf("Result: FAIL (expected \"%s\")\n", expected[i]);
            }
        }
        if (i + 1 < num) printf("\n");
    }
}

/* s21_strstr_test: cases: found, not found, empty needle, needle longer, NULLs
 */
void s21_strstr_test(void) {
    const struct {
        const char* h;
        const char* n;
        const char* expect;
    } tests[] = {
        {"hello world", "world", "world"}, /* found */
        {"abcd", "ef", NULL},              /* not found */
        {"abc", "", "abc"},                /* empty needle -> haystack */
        {"short", "longneedle", NULL},     /* needle longer -> NULL */
        {NULL, "a", NULL},                 /* haystack NULL -> NULL */
        {"abc", NULL, NULL}                /* needle NULL -> NULL */
    };
    const size_t num = sizeof(tests) / sizeof(tests[0]);

    printf("\nRunning s21_strstr_test (total %zu tests)\n\n", num);
    for (size_t i = 0; i < num; ++i) {
        const char* h = tests[i].h;
        const char* n = tests[i].n;
        const char* expected = tests[i].expect;
        if (h == NULL)
            printf("Input haystack: NULL\n");
        else
            printf("Input haystack: \"%s\"\n", h);
        if (n == NULL)
            printf("Input needle: NULL\n");
        else
            printf("Input needle: \"%s\"\n", n);
        char* out = s21_strstr(h, n);
        if (out == NULL) {
            printf("Output: NULL\n");
        } else {
            printf("Output: \"%s\"\n", out);
        }
        if (expected == NULL) {
            if (out == NULL) {
                printf("Result: SUCCESS\n");
            } else {
                printf("Result: FAIL (expected NULL)\n");
            }
        } else {
            if (out != NULL && s21_strcmp(out, expected) == 0) {
                printf("Result: SUCCESS\n");
            } else {
                printf("Result: FAIL (expected \"%s\")\n", expected);
            }
        }
        if (i + 1 < num) printf("\n");
    }
}

/* s21_strtok_test: several cases
   1) normal comma-separated
   2) multiple whitespace delimiters
   3) empty-token-result (only delimiters)
   4) continuation via NULL (verify subsequent calls) */
void s21_strtok_test(void) {
    printf("\nRunning s21_strtok_test\n\n");

    /* Test 1: normal comma-separated */
    {
        char buf[] = "hello,world,this,is";
        const char* delim = ",";
        const char* expected[] = {"hello", "world", "this", "is", NULL};
        printf("Input: \"%s\"\nDelim: \"%s\"\n", buf, delim);
        int ok = 1;
        char* t = s21_strtok(buf, (char*)delim); /* cast only for readability; s21_strtok
                                                    signature expects char* */
        size_t i = 0;
        while (t != NULL && expected[i] != NULL) {
            printf("Token %zu: \"%s\"\n", i, t);
            if (s21_strcmp(t, expected[i]) != 0) ok = 0;
            ++i;
            t = s21_strtok(NULL, (char*)delim);
        }
        if (expected[i] != NULL || t != NULL) ok = 0;
        printf("Result: %s\n\n", ok ? "SUCCESS" : "FAIL");
    }

    /* Test 2: whitespace delimiters */
    {
        char buf[] = "  a b\tc";
        const char* delim = " \t";
        const char* expected[] = {"a", "b", "c", NULL};
        printf("Input: \"%s\"\nDelim: \"%s\"\n", buf, delim);
        int ok = 1;
        char* t = s21_strtok(buf, (char*)delim);
        size_t i = 0;
        while (t != NULL && expected[i] != NULL) {
            printf("Token %zu: \"%s\"\n", i, t);
            if (s21_strcmp(t, expected[i]) != 0) ok = 0;
            ++i;
            t = s21_strtok(NULL, (char*)delim);
        }
        if (expected[i] != NULL || t != NULL) ok = 0;
        printf("Result: %s\n\n", ok ? "SUCCESS" : "FAIL");
    }

    /* Test 3: only delimiters -> no tokens */
    {
        char buf[] = ",,,";
        const char* delim = ",";
        printf("Input: \"%s\"\nDelim: \"%s\"\n", buf, delim);
        char* t = s21_strtok(buf, (char*)delim);
        printf("Output: %s\n", t ? t : "NULL");
        printf("Result: %s\n\n", (t == NULL) ? "SUCCESS" : "FAIL");
    }

    /* Test 4: continuation with NULL (ensure state preserved) */
    {
        char buf[] = "one:two:three";
        const char* delim = ":";
        const char* expected[] = {"one", "two", "three", NULL};
        printf("Input: \"%s\"\nDelim: \"%s\"\n", buf, delim);
        int ok = 1;
        char* t = s21_strtok(buf, (char*)delim);
        size_t i = 0;
        printf("Token %zu: \"%s\"\n", i, t ? t : "NULL");
        if (!t || s21_strcmp(t, expected[i]) != 0) ok = 0;
        ++i;
        /* continue by passing NULL */
        t = s21_strtok(NULL, (char*)delim);
        while (t != NULL && expected[i] != NULL) {
            printf("Token %zu: \"%s\"\n", i, t);
            if (s21_strcmp(t, expected[i]) != 0) ok = 0;
            ++i;
            t = s21_strtok(NULL, (char*)delim);
        }
        if (expected[i] != NULL || t != NULL) ok = 0;
        printf("Result: %s\n\n", ok ? "SUCCESS" : "FAIL");
    }
}

int main(void) {
    s21_strlen_test();
    s21_strcmp_test();
    s21_strcpy_test();
    s21_strcat_test();
    s21_strchr_test();
    s21_strstr_test();
    s21_strtok_test();
    return 0;
}
