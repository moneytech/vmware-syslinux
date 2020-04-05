/*
 * unistd.h
 *
 * Modified by VMware, Inc.
 *    Added getopt(), optind and optopt declarations.
 */

#ifndef _UNISTD_H
#define _UNISTD_H

#include <klibc/extern.h>
#include <klibc/compiler.h>
#include <stddef.h>
#include <sys/types.h>

__extern char *optarg;
__extern int optind, optopt;

__extern int getopt(int argc, char * const argv[],
                    const char *optstring);

__extern __noreturn _exit(int);

__extern int open(const char *, int, ...);
__extern int close(int);

__extern ssize_t read(int, void *, size_t);
__extern ssize_t write(int, const void *, size_t);

__extern int isatty(int);

__extern int getscreensize(int, int *, int *);

__extern char *getcwd(char *, int);
__extern int chdir(const char *);

/* Standard file descriptor numbers. */
#define STDIN_FILENO	0
#define STDOUT_FILENO	1
#define STDERR_FILENO	2

#endif /* _UNISTD_H */
