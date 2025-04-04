/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shrimech <shrimech@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 01:56:58 by shrimech          #+#    #+#             */
/*   Updated: 2025/03/22 22:26:44 by shrimech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int	ft_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}

static int	ft_putnbr(long n)
{
	int	i;

	i = 0;
	if (n < 0)
	{
		ft_putchar('-');
		n = -n;
		i++;
	}
	if (n >= 10)
		i += ft_putnbr(n / 10);
	i += ft_putchar(n % 10 + '0');
	return (i);
}

static int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		i;
	int		count;

	i = 0;
	count = 0;
	va_start(ap, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			i++;
			if (format[i] == 'c')
				count += ft_putchar(va_arg(ap, int));
			else if ((format[i] == 'd') || (format[i] == 'i'))
				count += ft_putnbr(va_arg(ap, int));
		}
		else
			count += write(1, &format[i], 1);
		i++;
	}
	va_end(ap);
	return (count);
}

static void	ft_handler(int signal, siginfo_t *info, void *t)
{
	static int	bit;
	static int	i;
	static int	old_pid;

	(void)t;
	if (info->si_pid != old_pid)
	{
		ft_printf("\n");
		bit = 0;
		i = 0;
	}
	if (signal == SIGUSR1)
		i |= (1 << bit);
	bit++;
	if (bit == 8)
	{
		ft_printf("%c", i);
		bit = 0;
		i = 0;
	}
	old_pid = info->si_pid;
}

int	main(int argc, char **argv)
{
	int					pid;
	struct sigaction	sa;

	sa.sa_sigaction = ft_handler;
	sa.sa_flags = SA_SIGINFO;
	(void)argv;
	if (argc != 1)
	{
		ft_printf("Error: wrong format.\n");
		ft_printf("Try: ./server\n");
		return (0);
	}
	pid = getpid();
	ft_printf("PID : %d\n", pid);
	ft_printf("Waiting for a message...\n");
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
}
