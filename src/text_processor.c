#include <stdio.h>
#include <stdlib.h>

/* Simple text formatter for -w mode.
   Reads integer width (first token) then a line of text (up to newline).
   Uses only stdio.h and stdlib.h.
*/

static int is_space(char c) { return c == ' ' || c == '\t' || c == '\n' || c == '\r'; }

/* Helper: trim leading/trailing spaces in buffer (in-place), return new length
 */
static int trim_buf(char* buf, int len) {
    int s = 0;
    while (s < len && is_space(buf[s])) ++s;
    int e = len - 1;
    while (e >= s && is_space(buf[e])) --e;
    int newlen = 0;
    for (int i = s; i <= e; ++i) buf[newlen++] = buf[i];
    buf[newlen] = '\0';
    return newlen;
}

/* read next token (word) from buffer, returns pointer to beginning and sets len
 */
static char* next_word(char* buf, int* pos) {
    int i = *pos;
    while (buf[i] && is_space(buf[i])) ++i;
    if (!buf[i]) {
        *pos = i;
        return NULL;
    }
    int start = i;
    while (buf[i] && !is_space(buf[i])) ++i;
    int len = i - start;
    /* allocate word */
    char* w = (char*)malloc((size_t)len + 1);
    if (!w) return NULL;
    for (int k = 0; k < len; ++k) w[k] = buf[start + k];
    w[len] = '\0';
    *pos = i;
    return w;
}

int main(int argc, char** argv) {
    if (argc != 2) {
        printf("n/a");
        return 0;
    }
    if (argv[1][0] != '-' || argv[1][1] != 'w' || argv[1][2] != '\0') {
        printf("n/a");
        return 0;
    }
    /* read width and rest of input line(s) from stdin */
    int width = 0;
    if (scanf("%d", &width) != 1 || width <= 0) {
        printf("n/a");
        return 0;
    }
    /* consume single char after number (space or newline) */
    int ch = getchar();
    /* read remaining line into buffer (up to reasonable size) */
    char buf[1024];
    int idx = 0;
    while ((ch = getchar()) != EOF && ch != '\n' && idx < (int)sizeof(buf) - 1) {
        buf[idx++] = (char)ch;
    }
    buf[idx] = '\0';

    /* tokenize into words */
    char* words[512];
    int wcount = 0;
    int pos = 0;
    char* w;
    while ((w = next_word(buf, &pos)) != NULL) {
        words[wcount++] = w;
        if (wcount >= 512) break;
    }

    /* prepare container for output lines */
    char** lines = (char**)malloc(sizeof(char*) * 1024);
    if (!lines) {
        for (int i = 0; i < wcount; ++i) free(words[i]);
        return 0;
    }
    int lcount = 0;

    /* process words into lines (greedy), handle hyphenation for too-long words */
    int cur = 0;
    while (cur < wcount) {
        int start = cur;
        int len = 0;
        int count = 0;
        while (cur < wcount) {
            int wl = 0;
            while (words[cur][wl]) ++wl;
            int needed = (count == 0) ? wl : (len + 1 + wl);
            if (needed <= width) {
                if (count == 0)
                    len = wl;
                else
                    len = len + 1 + wl;
                ++cur;
                ++count;
            } else
                break;
        }

        if (count == 0) {
            /* word longer than width: split into chunks width-1 + '-' as needed */
            char* longw = words[cur];
            int l = 0;
            while (longw[l]) ++l;
            int posw = 0;
            while (l - posw > width) {
                /* make chunk of width chars: width-1 content + '-' */
                char tmp[1024];
                int p = 0;
                for (int i = 0; i < width - 1; ++i) tmp[p++] = longw[posw + i];
                tmp[p++] = '-';
                tmp[p] = '\0';
                /* trim (shouldn't be spaces) and store */
                int newlen = trim_buf(tmp, p);
                char* store = (char*)malloc((size_t)newlen + 1);
                if (!store) break;
                for (int i = 0; i < newlen; ++i) store[i] = tmp[i];
                store[newlen] = '\0';
                lines[lcount++] = store;
                posw += width - 1;
            }
            /* remaining part */
            int rem = l - posw;
            if (rem > 0) {
                char* remw = (char*)malloc((size_t)rem + 1);
                for (int i = 0; i < rem; ++i) remw[i] = longw[posw + i];
                remw[rem] = '\0';
                free(words[cur]);
                words[cur] = remw;
            } else {
                free(words[cur]);
                cur++;
            }
            /* now next iteration will pack this remnant */
            continue;
        }

        /* build line from words[start..cur-1] */
        char line[4096];
        int p = 0;
        int words_in_line = cur - start;
        int len_words = 0;
        for (int i = start; i < cur; ++i) {
            int j = 0;
            while (words[i][j]) ++j;
            len_words += j;
        }
        int is_last = (cur >= wcount);
        if (is_last || words_in_line == 1) {
            for (int i = start; i < cur; ++i) {
                if (i > start) line[p++] = ' ';
                const char* s = words[i];
                for (int k = 0; s[k]; ++k) line[p++] = s[k];
            }
        } else {
            int total_spaces = width - len_words;
            int gaps = words_in_line - 1;
            int base = (gaps > 0) ? (total_spaces / gaps) : 0;
            int rem = (gaps > 0) ? (total_spaces % gaps) : 0;
            for (int i = start; i < cur; ++i) {
                const char* s = words[i];
                for (int k = 0; s[k]; ++k) line[p++] = s[k];
                if (i + 1 < cur) {
                    int sp = base + (rem > 0 ? 1 : 0);
                    if (rem > 0) --rem;
                    for (int q = 0; q < sp; ++q) line[p++] = ' ';
                }
            }
        }
        if (p >= (int)sizeof(line)) p = (int)sizeof(line) - 1;
        line[p] = '\0';
        /* trim leading/trailing spaces */
        int newlen = trim_buf(line, p);
        char* store = (char*)malloc((size_t)newlen + 1);
        if (!store) break;
        for (int i = 0; i < newlen; ++i) store[i] = line[i];
        store[newlen] = '\0';
        lines[lcount++] = store;
    }

    /* free words */
    for (int i = 0; i < wcount; ++i) free(words[i]);

    /* output lines without trailing newline */
    if (lcount > 0) {
        for (int i = 0; i < lcount; ++i) {
            fputs(lines[i], stdout);
            if (i + 1 < lcount) {
                putchar('\n');  // newline only between lines, not after last
            }
        }
    }

    /* free lines storage */
    for (int i = 0; i < lcount; ++i) free(lines[i]);
    free(lines);

    return 0;
}