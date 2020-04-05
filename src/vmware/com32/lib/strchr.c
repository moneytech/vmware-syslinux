/*
 * strchr.c
 *
 * Modified by VMware, Inc.
 *    Fixed broken strchr().
 */

#include <string.h>

char *strchr(const char *s, int c)
{
   do {
      if (*s == (char)c) {
         return (char *)s;
      }
   } while (*s++ != '\0');

   return NULL;
}
