# 42core_03_philosopher

42 school's project on the Dining Philosophers Problem.

### Notes

1. parse_args
```
./philo {number_of_philosophers} {time_to_die} {time_to_eat} {time_to_sleep} {OPTIONAL: number_of_times_each_philosopher_must_eat}
```
- parse the argument counts => either 5 or 6
- check arguments => then check is it greater than 0 and less than int_max

2. init
```C
typedef struct s_args
{
	unsigned int	n_philos;
	unsigned int	t_die_starving;
	unsigned int	t_eating;
	unsigned int	t_sleeping;
	unsigned int	n_eat_times;
	pthread_mutex_t	mutex_writing;
	unsigned long	t_start;
	pthread_mutex_t	*forks_array;
	t_philo			**philo_array;
	bool			run_simulation;
}	t_args;
```
- use t_args struct to contain the arguments of the entire programme
```C
	pthread_mutex_init(&(args->mutex_writing), NULL);
```
- uses args->mutsex_writing to store the mutex to write to the screen (NULL means using default attribute)
```C
pthread_mutex_t	*init_forks(unsigned int n_philos)
{
	pthread_mutex_t	*forks_array;
	unsigned int	i;

	i = 0;
	forks_array = malloc(sizeof(pthread_mutex_t) * n_philos);
	if (!forks_array)
		return (NULL);
	while (i < n_philos)
	{
		pthread_mutex_init(&forks_array[i], NULL);
		i++;
	}
	return (forks_array);
}
```
- init forks_array as an array of mutexes, same amount as number of philosophers
	```C
	typedef struct s_philo
	{
		pthread_t			philo_thread;
		pthread_t			check_death_thread;
		t_args				*args;
		unsigned int		id;
		pthread_mutex_t		mutex_is_eating;
		long long unsigned	last_eat_timestamp;
		unsigned int		eat_count;
		unsigned int		left_fork_id;
		unsigned int		right_fork_id;
		bool				is_eating;
	}	t_philo;
	```
- init philo_array
	- Using t_philo struct to store a philosopher
	- assign_fork_ids() => Assign left - right fork id to each philo

3. get_timestamp
```C
	struct timespec	timestamp;
```
- using struct timespec to store time (using time.h)
```C
	clock_gettime(CLOCK_REALTIME, &timestamp);
```
- clock_gettime => CLOCK_REALTIME get the real_world time
```C
	return (((long long unsigned)timestamp.tv_sec * 1000)
		+ (timestamp.tv_nsec / 1000000));
```
- converting seconds and nano seconds into miliseconds to match the project requirement

4. run_simulation

```C
	while (args->run_simulation)
		continue ;
```
- Keeps the main thread running, without this the main thread will end while philo threads will still be running in the backend
```C
int pthread_create(pthread_t *thread, const pthread_attr_t *attr, 
                   void *(*start_routine)(void *), void *arg);
```
- phtread_create()'s arguments
	- thread => ptr to thread
	- attr => attribute of the thread (NULL to use default attributes)
	- ptr to the function for the thread to execute
	- arguments passed to the previous function
```C
void	grab_fork_and_eat(t_philo *philo)
{
	pthread_mutex_lock(&(philo->args->forks_array[philo->left_fork_id]));
	print_msg(philo->args, philo->id, "has taken a fork");
	pthread_mutex_lock(&(philo->args->forks_array[philo->right_fork_id]));
	print_msg(philo->args, philo->id, "has taken a fork");
	pthread_mutex_lock(&(philo->mutex_is_eating));
	philo->last_eat_timestamp = get_timestamp();
	philo->is_eating = true;
	print_msg(philo->args, philo->id, "is eating");
	usleep(philo->args->t_eating * 1000);
	pthread_mutex_unlock(&(philo->mutex_is_eating));
	philo->is_eating = false;
	pthread_mutex_unlock(&(philo->args->forks_array[philo->left_fork_id]));
	pthread_mutex_unlock(&(philo->args->forks_array[philo->right_fork_id]));
	philo->eat_count++;
}

void	*simulate_philo(void *philo_v_ptr)
{
	t_philo	*philo;

	philo = (t_philo *)philo_v_ptr;
	while (philo->args->run_simulation)
	{
		grab_fork_and_eat(philo);
		print_msg(philo->args, philo->id, "is sleeping");
		usleep(philo->args->t_sleeping * 1000);
		print_msg(philo->args, philo->id, "is thinking");
	}
	return (NULL);
}
```
- simulate_philo() runs a philo_thread
- grab_fork_and_eat() will grab the forks and eat once available
- if the fork is locked by abother thread, pthread_mutex_lock() will make the current thread wait for the resources to be free
```C
void	check_eat(t_args *args)
{
	unsigned int	i;
	unsigned int	n_eat_times;

	i = 0;
	n_eat_times = args->n_eat_times;
	while (i < args->n_philos)
	{
		if (args->philo_array[i]->eat_count < n_eat_times)
			break ;
		i++;
	}
	if (i == args->n_philos && args->philo_array[i - 1]->eat_count
		>= n_eat_times)
	{
		pthread_mutex_lock(&(args->mutex_writing));
		args->run_simulation = false;
	}
}

void	*check_death(void *philo_v_ptr)
{
	t_philo			*philo;
	unsigned int	t_die_starving;

	philo = (t_philo *)philo_v_ptr;
	t_die_starving = philo->args->t_die_starving;
	while (philo->args->run_simulation)
	{
		if (!(philo->is_eating) && get_timestamp() - philo->last_eat_timestamp
			>= t_die_starving)
		{
			print_msg(philo->args, philo->id, "died");
			philo->args->run_simulation = false;
		}
		if (philo->args->n_eat_times != INT_MAX && philo->eat_count
			>= philo->args->n_eat_times)
			check_eat(philo->args);
		usleep(100 * 1000);
	}
	return (NULL);
}
```
- check_death were run as a seperate seperate thread
- repeteadly checks every 100 miliseconds (usleep 100 * 1000)
	- Check any philo die of starting, if yes, then stop the simulation
	- Alternatively if maximum eat_time is set (!= INT_MAX), then uses check_eat to check whether all philo_threads has eaten the required times. If yes, lock the writing_mutex and stop the simulation
	 

