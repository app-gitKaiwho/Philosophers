/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minilib.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvon-war <lvonwar42@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 13:58:32 by lvon-war          #+#    #+#             */
/*   Updated: 2023/09/01 13:58:32 by lvon-war         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_power(int nb, int power)
{
	int	val;

	val = 1;
	if (power < 0)
		return (0);
	if (power > 0)
		val = nb * ft_power(nb, power - 1);
	return (val);
}

int	is_whitespace(const char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

int	ft_strlen(const char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

int	ft_wdcount(char **str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	return (len - 1);
}

int	ft_atoi(const char *str)
{
	int		signe;
	int		size;
	long	val;
	int		i;

	signe = 1;
	val = 0;
	i = 0;
	size = ft_strlen(str);
	while (is_whitespace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i] == '-')
			signe *= -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		val += (str[i] - '0') * ft_power((10), size - i - 1);
		i++;
	}
	if (size != i)
		val /= ft_power((10), size - i);
	return (val * signe);
}
