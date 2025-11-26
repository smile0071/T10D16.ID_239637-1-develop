#ifndef S21_STRING_H
#define S21_STRING_H

#include <stdlib.h> /* for size_t (permitted) */

/* Declaration of s21_strlen */
size_t s21_strlen(const char* str);

/* Declaration of s21_strcmp */
int s21_strcmp(const char* s1, const char* s2);

/* Declaration of s21_strcpy */
char* s21_strcpy(char* dest, const char* src);

/* Declaration of s21_strcat */
char* s21_strcat(char* dest, const char* src);

/* Declaration of s21_strchr */
char* s21_strchr(const char* s, int c);

/* Declaration of s21_strstr */
char* s21_strstr(const char* haystack, const char* needle);

/* Declaration of s21_strtok */
char* s21_strtok(char* str, const char* delim);

#endif /* S21_STRING_H */
