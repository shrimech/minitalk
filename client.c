#include "minitalk.h"

static int ft_isdigit(int c)
{
    if (c >= '0' && c <= '9')
        return (1);
    return (0);
}

static int ft_atoi(const char *str)
{
    int num;
    int n;
    int i;

    num = 0;
    n = 1;
    i = 0;
    while (str[i] && (str[i] == ' ' || str[i] == '\t'
            || str[i] == '\n' || str[i] == '\r'
            || str[i] == '\v' || str[i] == '\f'))
        i++;
    if (str[i] == '+')
        i++;
    else if (str[i] == '-')
    {
        n *= -1;
        i++;
    }
    while (ft_isdigit(str[i]))
    {
        num = (num * 10) + (str[i] - '0');
        i++;
    }
    return (num * n);
}

static void    ft_send_bits(int pid, char i)
{
    int bit;

    bit = 0;
    while (bit < 8)
    {
        if ((i & (0x01 << bit)) != 0)
            kill(pid, SIGUSR1);
        else
            kill(pid, SIGUSR2);
        usleep(500);
        bit++;
    }
}

int main(int argc, char **argv)
{
    int pid;
    int i;

    i = 0;
    if (argc == 3)
    {
        pid = ft_atoi(argv[1]);
        while (argv[2][i] != '\0')
        {
            ft_send_bits(pid, argv[2][i]);
            i++;
        }
        ft_send_bits(pid, '\n');
    }
    else
    {
        write(1, "\033[91mError: wrong format.\033[0m\n", 31);
        write(1, "\033[33mTry: ./client <PID> <MESSAGE>\033[0m\n", 40);
        return (1);
    }
    return (0);
}

