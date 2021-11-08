#ifndef PIPEX_H
# define PIPEX_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "get_next_line.h"
#include <errno.h>
#include <sys/types.h>

char **ft_split(char *s, char separator);
char *ft_strjoin(char *s1, char *s2);

#endif