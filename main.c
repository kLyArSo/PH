#include "header.h"

long    get_current_time_in_ms()
{
    struct timeval          current_time;
    int time;

    gettimeofday(&current_time, NULL);
    time = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
    return (time);
}

int main(int argc, char **argv)
{
    t_argv                  *game_args;
    pthread_t               *philosophers;
    t_philo_data            *philos_data;

    g_start_time = get_current_time_in_ms();
    if (argv_error_handling(argc, argv) == ERROR_DETECTED)
        return (ERROR_DETECTED);
    game_args = fetch_args(argc, argv);
    if (game_args == NULL)
    {
        printf("ERROR : MALLOC\n");
        return (ERROR_DETECTED);
    }
    if (last_check(game_args) == ERROR_DETECTED)
    {
        printf("ERROR : INVALID VALUE\n");
        return (ERROR_DETECTED);
    }
    /*------------------------------------------------------------ERROR HANDLING DONE------------------------------------------------------------*/
    philosophers = malloc(game_args->number_of_philosophers * sizeof(pthread_t));
    philos_data = malloc(game_args->number_of_philosophers * sizeof(t_philo_data));
    if (philosophers == NULL || philos_data == NULL)
        return (ERROR_DETECTED);
    pthread_mutex_init(&g_lock_1,NULL);
    pthread_mutex_init(&g_lock_2,NULL);
    set_philo_data(philos_data, game_args, forks_init(game_args));
    if (philos_data->forks == NULL)
        return (ERROR_DETECTED);
    /*-----------------------------------------------------------------INITIALZING DONE------------------------------------------------------------*/
    deploy_philosophers(game_args, philosophers, philos_data);
    checker_wave_deployment(philos_data);
    //join_the_bunch(philosophers, game_args);
    while(1)
    {
        if (g_notification == MIN_MEAL_REACHED && game_args->last_arg_presence == 1)
            return (1);
        if (g_notification == PHILO_DEATH)
            return (1);
    }
    return (0);
}
























































    //printf("%ld", game_args->number_of_philosophers);
    //printf(" %ld", game_args->time_to_die);
    //printf(" %ld", game_args->time_to_eat);
    //printf(" %ld", game_args->time_to_sleep);
    //if (game_args->last_arg_presence == LAST_ARG_PRESENT)
    //    printf(" %ld", game_args->number_of_times_each_philosopher_must_eat);
    //printf("\n");