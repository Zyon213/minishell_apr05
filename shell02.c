#include "shell.h"

char    *builtin_str[] = { "cd", "help", "exit"};
int     (*builtin_func[]) (char **) = {&ft_cd , &ft_help, &ft_exit};

int     ft_num_builtin()
{
    return (sizeof(builtin_str) / sizeof(char *));
}

int ft_cd(char **argv)
{
    if (argv[1] == NULL)
        fprintf(stderr, "lsh: expected argument.\n");
    else
    {
        if (chdir(argv[1]) != 0)
            perror("lsh");
    }
    return (1);
}

int ft_help(char **argv __attribute__((unused)))
{
    int i;

    printf("builtins \n");
    for (i = 0; i < ft_num_builtin(); i++)
        printf("%s\n", builtin_str[i]);
    printf("for documentation.\n");
    return (1);
}

int ft_exit(char **argv __attribute__((unused)))
{
    return (0);
}

int     ft_executes(char **argv)
{
    int i;

    if (argv[0] == NULL)
        return 1;
    for (i = 0; i < ft_num_builtin(); i++)
    {
        if (strcmp(argv[0], builtin_str[i]) == 0)
            return ((*builtin_func[i])(argv));
    }
    return (ft_launche(argv));
}

char    *ft_read_line(void)
{
    int bufsize = BUFFER_SIZE;
    int position = 0;
    char *buffer = malloc(sizeof(char) * bufsize);
    int c;

    if (!buffer)
    {
        fprintf(stderr, "lsh: allocation error\n");
        exit(EXIT_FAILURE);
    }
    while (1)
    {
        c = getchar();
        if (c == EOF || c == '\n') 
        {
            buffer[position] = '\0';
            return (buffer);
        }
        else
            buffer[position] = c;
        position++;

        if (position >= bufsize)
        {
            bufsize += BUFFER_SIZE;
            buffer = realloc(buffer, bufsize);
            {
                if (!buffer)
                {
                    fprintf(stderr, "lsh: allocation error.\n");
                    exit (EXIT_FAILURE);
                }
            }
        }
    }
}

char    **ft_split_line(char *line)
{
    int bufsize = TOK_BUF_SIZE;
    int position = 0;
    char *token;
    char **tokens = malloc(sizeof(char*) * bufsize);
    if (!tokens)
    {
        fprintf(stderr, "lsh: allocation error.\n");
        exit (EXIT_FAILURE);
    }

    token = strtok(line, TOK_DELIM);
    while (token != NULL)
    {
        tokens[position] = token;
        position++;

        if (position >= bufsize)
        {
            bufsize += TOK_BUF_SIZE;
            tokens = realloc(tokens, bufsize * sizeof(char*));
            if (!tokens)
            {
                fprintf(stderr, "lsh: allocation error.\n");
                exit (EXIT_FAILURE);
            }
        }
        token = strtok(NULL, TOK_DELIM);
    }
    tokens[position] = NULL;
    return (tokens);
}

int     ft_launche(char **argv)
{
    pid_t pid ,wpid;
    int status;

    pid = fork();
    if (pid == 0)
    {
        if (execvp(argv[0], argv) == -1)
            perror("lsh.");
        exit (EXIT_FAILURE);
    }
    else if (pid < 0)
        perror("lsh");
    else
    {
        do
        {
            wpid = waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
    return (1);
}

long int ft_current_time(void)
{
    long int ttime;
    struct timeval tv;

    gettimeofday(&tv, NULL);
    ttime = (tv.tv_sec * 1000 + tv.tv_usec / 1000);
    return (ttime);
}

void    ft_loop(void)
{
    char *line;
    char **argv;
    int status;

    do
    {
        write(STDOUT_FILENO, "minishell~$ ", 15);
        line = ft_read_line();
        argv = ft_split_line(line);
        status = ft_executes(argv);

        free(line);
        free(argv);
    } while (status);
}
int main(int argc __attribute__((unused)), char **argv __attribute__((unused)))
{
    ft_loop();
    return EXIT_SUCCESS;
}
