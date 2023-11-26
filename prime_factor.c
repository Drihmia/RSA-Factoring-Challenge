#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <math.h>
#include <gmp.h>

void prime_nums_of_large(mpz_t n);
void prime_nums_of_small(unsigned long long n);

/**
 * main - Entry point
 * @ac: counter argument.
 * @av: array of strings
 * Return: int
 */
int main(int ac, char **av)
{
	mpz_t num_elements;
	size_t size = 0;
	FILE *file;
	char *line = NULL;

	if (ac != 2)
	{
		fprintf(stderr, "Usage: factors <file>\n");
		return (1);
	}

	file = fopen(av[1], "r");
	if (file == NULL)
	{
		perror("Error opening file");
		return (1);
	}

	mpz_init(num_elements);

	while (getline(&line, &size, file) != -1)
	{
		if (line && strlen(line) > 1)
		{
			size_t len = strlen(line);

			if (len <= 20)
			{
				unsigned long long num = strtoull(line, NULL, 10);

				prime_nums_of_small(num);
			}
			else
			{
				mpz_init_set_str(num_elements, line, 10);
				prime_nums_of_large(num_elements);
				mpz_clear(num_elements);
			}
		}
	}

	free(line);
	fclose(file);
	return (0);
}

/**
 * prime_nums_of_large - Factorize the given number
 * using GMP and print the result.
 *
 * @n: The number to factorize.
 */
void prime_nums_of_large(mpz_t n)
{
	int is_prime_factor = 0;
	mpz_t i, sqrt_n, m;

	mpz_init(i);
	mpz_init(m);
	mpz_init(sqrt_n);
	mpz_sqrt(sqrt_n, n);

	for (mpz_init_set_ui(i, 2); mpz_cmp(i, sqrt_n) <= 0; mpz_add_ui(i, i, 1))
	{
		is_prime_factor = 1;
		if (mpz_divisible_p(n, i) != 0)
		{
			mpz_tdiv_q(m, n, i);
			gmp_printf("%Zd=%Zd*%Zd\n", n, m, i);
			is_prime_factor = 0;
			break;
		}
	}

	if (is_prime_factor == 1)
	{
		mpz_init_set_ui(i, 0);
		if (mpz_cmp(n, i) != 0)
			gmp_printf("%Zd=%Zd*%d\n", n, n, 1);
	}

	mpz_clear(i);
	mpz_clear(m);
	mpz_clear(sqrt_n);
}

/**
 * prime_nums_of_small - Factorize the given number using
 * unsigned long long and print the result.
 *
 * @n: The number to factorize.
 */
void prime_nums_of_small(unsigned long long n)
{
	int is_prime_factor = 0;
	unsigned long long i, sqrt_n, m;

	m = n;
	sqrt_n = (unsigned long long)sqrt(n);

	for (i = 2; i <= sqrt_n; i++)
	{
		is_prime_factor = 1;
		if (n % i == 0)
		{
			m = n / i;
			printf("%llu=%llu*%llu\n", n, m, i);
			is_prime_factor = 0;
			break;
		}
	}

	if (is_prime_factor == 1 && n != 0)
	{
		if (n != 1)
			printf("%llu=%llu*%d\n", n, n, 1);
	}
}

