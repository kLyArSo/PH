#include "header.h"

ssize_t    get_current_time_micro_seconds()
{
    struct timeval  current_time;
    ssize_t         time;

    gettimeofday(&current_time, NULL);
    time = current_time.tv_sec * 1000 * 1000 + current_time.tv_usec;
    return (time);
}

int     game_args_error()
{
    printf("ERROR : MALLOC\n");
    //system("leaks a.out | grep bytes");
    return (ERROR_DETECTED);
}

int     invalid_value_error(t_argv  *game_args)
{
    free(game_args);
    printf("ERROR : INVALID VALUE\n");
    //system("leaks a.out | grep bytes");
    return (ERROR_DETECTED);
}

int     philo_malloc_err(t_argv  *game_args)
{
    free(game_args);
    //system("leaks a.out | grep bytes");
    return (ERROR_DETECTED);
}

int     philos_data_malloc_err(t_argv  *game_args, pthread_t    *philosophers)
{
        free(game_args);
        free(philosophers);
        system("leaks a.out | grep bytes");
        return (ERROR_DETECTED);
}

int     un_init_forks(t_philo_data  *philos_data, t_argv  *game_args, pthread_t *philosophers)
{
    pthread_mutex_destroy(&g_lock_1);
    free(philos_data);
    free(game_args);
    free(philosophers);
    system("leaks a.out | grep bytes");
    return (ERROR_DETECTED);
}

int main(int argc, char **argv)
{
    t_argv                  *game_args;
    pthread_t               *philosophers;
    t_philo_data            *philos_data;
    pthread_t               min_meal;
    pthread_t               death;
    int i;

    i = 0;
    g_start_time = get_current_time_micro_seconds();
    if (argv_error_handling(argc, argv) == ERROR_DETECTED)
        return (ERROR_DETECTED);
    game_args = fetch_args(argc, argv);
    if (game_args == NULL)
        return (game_args_error());
    if (last_check(game_args) == ERROR_DETECTED)
        return(invalid_value_error(game_args));
    /*------------------------------------------------------------ERROR HANDLING DONE------------------------------------------------------------*/
    philosophers = malloc(game_args->number_of_philosophers * sizeof(pthread_t));
    if (philosophers == NULL)
        return (philo_malloc_err(game_args));
    philos_data = malloc(game_args->number_of_philosophers * sizeof(t_philo_data));
    if (philos_data == NULL)
        return (philos_data_malloc_err(game_args, philosophers));
    pthread_mutex_init(&g_lock_1, NULL);
    set_philo_data(philos_data, game_args, forks_init(game_args));
    if (philos_data->forks == NULL)
        return (un_init_forks(philos_data, game_args, philosophers));
    /*-----------------------------------------------------------------INITIALZING DONE------------------------------------------------------------*/
    deploy_philosophers(game_args, philosophers, philos_data);
    checker_wave_deployment(philos_data, &min_meal, &death);
    while (1)
    {
        if ((g_notification == MIN_MEAL_REACHED
        && game_args->last_arg_presence == 1)
        || g_notification == PHILO_DEATH)
        {
            if (philos_data->game_args->last_arg_presence == 1)
                pthread_detach(min_meal);
            pthread_detach(death);
            while(i < philos_data->game_args->number_of_philosophers)
            {
                pthread_detach(philosophers[i]);
                i++;
            }
            i = 0;
            pthread_mutex_destroy(&g_lock_1);
            while(i < philos_data->game_args->number_of_forks)
            {
                pthread_mutex_destroy(&philos_data->forks[i]);
                i++;
            }
            free(game_args);
            free(philosophers);
            free(philos_data->forks);
            free(philos_data);
            system("leaks a.out | grep bytes");
            return (1);
        }
    }
    system("leaks a.out | grep bytes");
    return (0);
}