#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/time.h>

#define TOK_BUF_SIZE 64
#define TOK_DELIM " \t\r\n\a"
#define BUFFER_SIZE 1024


int ft_cd(char **argv);
int ft_help(char **argv);
int ft_exit(char **argv);
int     ft_num_builtin();
int ft_cd(char **argv);
int ft_help(char **argv __attribute__((unused)));
int ft_exit(char **argv __attribute__((unused)));
int     ft_executes(char **argv);
char    *ft_read_line(void);
char    **ft_split_line(char *line);
int     ft_launche(char **argv);
void    ft_loop(void);
int main(int argc __attribute__((unused)), char **argv __attribute__((unused)));
int ft_history(char **argv);

#endif