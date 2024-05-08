/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrapper_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 10:05:04 by wiferrei          #+#    #+#             */
/*   Updated: 2024/05/08 10:51:20 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*my_malloc(size_t bytes)
{
	void	*ptr;

	ptr = malloc(bytes);
	if (!ptr)
		philo_error_exit("Malloc failed");
	return (ptr);
}

static void	handle_thread_error(int status, t_opcode opcode)
{
	if (status == 0)
		return ;
	if (status == EAGAIN)
		philo_error_exit("No resources to create another thread");
	else if (status == EPERM)
		philo_error_exit("No permission to set the scheduling policy and parameters specified in attr");
	else if (status == EINVAL && opcode == CREATE)
		philo_error_exit("The value specified by attr is invalid.");
	else if (status == EINVAL && (opcode == JOIN || opcode == DETACH))
		philo_error_exit("The value specified by thread is not joinable\n");
	else if (status == ESRCH)
		philo_error_exit("No thread could be found corresponding to that specified by the given thread ID");
	else if (status == EDEADLK)
		philo_error_exit("A deadlock was detected or the value of thread specifies the calling thread");
	else
		philo_error_exit("Thread error");
}

void	mutex_handler(t_mtx *mtx, t_opcode opcode)
{
	if (opcode == LOCK)
		handle_mutex_error(pthread_mutex_lock(mtx), opcode);
	else if (opcode == UNLOCK)
		handle_mutex_error(pthread_mutex_unlock(mtx), opcode);
	else if (opcode == INIT)
		handle_mutex_error(pthread_mutex_init(mtx, NULL), opcode);
	else if (opcode == DESTROY)
		handle_mutex_error(pthread_mutex_destroy(mtx), opcode);
}

static void	handle_thread_error(int status, t_opcode opcode)
{
	if (status == 0)
		return ;
	if (status == EAGAIN)
		philo_error_exit("No resources to create another thread");
	else if (status == EPERM)
		philo_error_exit("The caller does not have appropriate permission\n");
	else if (status == EINVAL && opcode == CREATE)
		philo_error_exit("The value specified by attr is invalid.");
	else if (status == EINVAL && (opcode == JOIN || opcode == DETACH))
		philo_error_exit("The value specified by thread is not joinable\n");
	else if (status == ESRCH)
		philo_error_exit("No thread could be found corresponding to that"
							"specified by the given thread ID, thread.");
	else if (status == EDEADLK)
		philo_error_exit("A deadlock was detected or the value of"
							"thread specifies the calling thread.");
}

void	thread_handler(pthread_t *thread, void *(*foo)(void *), void *data,
		t_opcode opcode)
{
	if (opcode == CREATE)
		handle_thread_error(pthread_create(thread, NULL, foo, data), opcode);
	else if (opcode == JOIN)
		handle_thread_error(pthread_join(*thread, NULL), opcode);
	else if (opcode == DETACH)
		handle_thread_error(pthread_detach(*thread), opcode);
	else
		philo_error_exit("Wrong opcode");
}
