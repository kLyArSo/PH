#include <stdlib.h>
#include <stdio.h>
#define LAST_ARG_PRESENT 1
#define LAST_ARG_MISSING 0

#define NO_ERRORS_DETECTED 1
#define ERROR_DETECTED -1

typedef struct  s_argv
{
    int number_of_philosophers;
    int number_of_forks;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int last_arg_presence;
    int number_of_times_each_philosopher_must_eat;
}               t_argv;

int         ft_atoi(char *src);
t_argv      *fetch_args(int argc, char **argv);
int         check_ints(char *str);
int         argv_error_handling(int argc, char **argv);
int         last_check(t_argv  *game_args);
int         main(int argc, char **argv);
