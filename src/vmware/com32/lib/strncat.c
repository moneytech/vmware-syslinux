/*
 * strncat.c
 *
 * Modified by VMware, Inc.
 *    Fixed broken strncat().
 */

#include <string.h>

char *strncat(char *dest, const char *src, size_t n)
{
   char *str;

   str = dest + strlen(dest);

   while (n--) {
      if (*src == '\0') {
         break;
      }
      *str++ = *src++;
   }

   *str = '\0';

   return dest;
}
