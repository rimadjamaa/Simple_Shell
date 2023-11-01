#include "shell.h"

/**
 * main - Simple Shell
 * Return: Always 0.
 */
int main(void)
{
char *arg_list[] = { NULL };
char *buffer = NULL;
size_t bufsize = 0;
ssize_t characters;
pid_t child_pid;
int status;
while (1)
{
printf("($) ");
characters = getline(&buffer, &bufsize, stdin);
if (characters == -1)
{
perror("Error reading command");
exit(EXIT_FAILURE);
}
if (characters > 1)
{
buffer[characters - 1] = '\0';
child_pid = fork();
if (child_pid == -1)
{
perror("Error forking process");
exit(EXIT_FAILURE);
}
if (child_pid == 0)
{
if (execve(buffer, arg_list, NULL) == -1)
{
perror("Error executing command");
exit(EXIT_FAILURE);
}
}
else
{
waitpid(child_pid, &status, 0);
}
}
}
free(buffer);
return (0);
}
