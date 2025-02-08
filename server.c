#include "minitalk.h"

static int ft_putchar(char c)
{
    write(1, &c, 1);
    return (1);
}

static int ft_putstr(char *str)
{
    int i;

    i = 0;
    if (!str)
        return (ft_putstr("(null)"));
    while (*str)
    {
        ft_putchar(*str);
        str++;
        i++;
    }
    return (i);
}

static int ft_putnbr(long n)
{
    int     i;

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

static int ft_printf(const char *format, ...)
{
    va_list ap;
    int     i;
    int     count;

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
            else if (format[i] == 's')
                count += ft_putstr(va_arg(ap, char *));
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

static void    ft_handler(int signal)
{
    static int  bit;
    static int  i;

    if (signal == SIGUSR1)
        i |= (0x01 << bit);
    bit++;
    if (bit == 8)
    {
        ft_printf("%c", i);
        bit = 0;
        i = 0;
    }
}

int main(int argc, char **argv)
{
    int pid;

    (void)argv;
    if (argc != 1)
    {
        ft_printf("\033[91mError: wrong format.\033[0m\n");
        ft_printf("\033[33mTry: ./server\033[0m\n");
        return (0);
    }
    pid = getpid();
    ft_printf("\033[94mPID\033[0m \033[96m->\033[0m %d\n", pid);
    ft_printf("\033[90mWaiting for a message...\033[0m\n");
    while (argc == 1)
    {
        signal(SIGUSR1, ft_handler);
        signal(SIGUSR2, ft_handler);
        pause ();
    }
    return (0);
}

