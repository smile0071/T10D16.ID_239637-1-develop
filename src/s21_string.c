#include "s21_string.h"

/* s21_strlen: count characters before the first '\\0'.
   If str is NULL, return 0 to avoid crashes in abnormal tests. */
size_t s21_strlen(const char *str) {
  if (!str)
    return 0;
  const char *s = str;
  size_t len = 0;
  while (*s++)
    ++len;
  return len;
}

/* s21_strcmp: lexicographical compare.
   Returns 0 if equal, negative if s1 < s2, positive if s1 > s2.
   Safe handling for NULL: both NULL -> 0, NULL < non-NULL. */
int s21_strcmp(const char *s1, const char *s2) {
  if (s1 == s2)
    return 0;
  if (!s1)
    return -1;
  if (!s2)
    return 1;
  while (*s1 && *s2 && (unsigned char)*s1 == (unsigned char)*s2) {
    ++s1;
    ++s2;
  }
  return (int)((unsigned char)*s1 - (unsigned char)*s2);
}

/* s21_strcpy: copy src into dest including terminating '\\0'.
   Behavior for NULL: if dest == NULL -> return NULL;
   if src == NULL -> set dest[0] = '\\0' and return dest. */
char *s21_strcpy(char *dest, const char *src) {
  if (!dest)
    return NULL;
  if (!src) {
    dest[0] = '\0';
    return dest;
  }
  char *d = dest;
  const char *s = src;
  while ((*d++ = *s++) != '\0') {
  }
  return dest;
}

/* s21_strcat: append src to dest including terminating '\0'.
   Behavior: if dest == NULL -> return NULL; if src == NULL -> return dest
   unchanged. */
char *s21_strcat(char *dest, const char *src) {
  if (!dest)
    return NULL;
  if (!src)
    return dest;
  char *d = dest;
  while (*d)
    ++d; /* move to end of dest */
  const char *s = src;
  while ((*d++ = *s++) != '\0') {
  }
  return dest;
}

/* s21_strchr: return pointer to first occurrence of c in s, or NULL.
   Safe: if s == NULL -> return NULL. Handles searching for '\0'. */
char *s21_strchr(const char *s, int c) {
  if (!s)
    return NULL;
  unsigned char uc = (unsigned char)c;
  while (*s) {
    if ((unsigned char)*s == uc) {
      /* cast away const to match signature */
      return (char *)s;
    }
    ++s;
  }
  /* check terminating '\0' */
  if (uc == (unsigned char)'\0')
    return (char *)s;
  return NULL;
}

/* s21_strstr: naive substring search.
   Safe behavior: if haystack==NULL or needle==NULL -> return NULL.
   If needle is empty -> return (char*)haystack. */
char *s21_strstr(const char *haystack, const char *needle) {
  if (!haystack || !needle)
    return NULL;
  /* empty needle -> return haystack */
  if (*needle == '\0')
    return (char *)haystack;
  const char *h = haystack;
  while (*h) {
    const char *p = h;
    const char *q = needle;
    while (*p && *q && (unsigned char)*p == (unsigned char)*q) {
      ++p;
      ++q;
    }
    if (*q == '\0')
      return (char *)h; /* found */
    ++h;
  }
  return NULL;
}

/* helper: check if ch is in delim */
static int s21_is_delim(unsigned char ch, const char *delim) {
  if (!delim)
    return 0;
  const char *d = delim;
  while (*d) {
    if ((unsigned char)*d == ch)
      return 1;
    ++d;
  }
  return 0;
}

/* s21_strtok: tokenization similar to standard strtok.
   - If str != NULL, start new tokenization from str.
   - If str == NULL, continue from previous position.
   - delim is a null-terminated string of delimiter characters.
   - Returns pointer to token (modifies input buffer by inserting '\\0') or NULL
   if no more tokens.
   - Safe with NULL pointers: if delim == NULL -> NULL; if both str and saved
   state NULL -> NULL. */
char *s21_strtok(char *str, const char *delim) {
  /* ...existing code... */
  static char *saveptr = NULL;
  char *p;

  if (!delim)
    return NULL;
  p = str ? str : saveptr;
  if (!p)
    return NULL;

  /* skip leading delimiters */
  while (*p && s21_is_delim((unsigned char)*p, delim))
    ++p;
  if (*p == '\0') {
    saveptr = NULL;
    return NULL;
  }

  /* token start */
  char *token = p;
  /* find token end */
  while (*p && !s21_is_delim((unsigned char)*p, delim))
    ++p;
  if (*p) {
    /* terminate token and save next position */
    *p = '\0';
    saveptr = p + 1;
  } else {
    /* end of string */
    saveptr = NULL;
  }
  return token;
}