#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include <gmp.h>

#define ARRAY_SIZE 2

void prime_nums_of(mpz_t n);
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
		mpz_init_set_str(num_elements, line, 10);
		prime_nums_of(num_elements);
		mpz_clear(num_elements);
	}

	free(line);
	fclose(file);
	return (0);
}
/**
  * prime_nums_of - giving the prime numbers of number n.
  * this function gives  prime numbers fron 2 to the given n.
  * @n: the target number.
  * Return: None.
  */
void prime_nums_of(mpz_t n)
{
	int l, k, x, get_i;

	k = mpz_get_si(n);
	for (x = 1; x < 4; x++)
	{
		if (x == k)
		{
			printf("%d=%d*1\n", k, k);
			return;
		}
	}

	mpz_t i, j, sqrt_n, m;
	mpz_init(i);
	mpz_init(j);
	mpz_init(m);
	mpz_init(sqrt_n);
	mpz_sqrt(sqrt_n, n);

	for (mpz_init_set_ui(i, 2); mpz_cmp(i, sqrt_n) <= 0; mpz_add_ui(i, i, 1))
	{
		l = 0;
		/* check how many times n is divisible by i */
		if (mpz_divisible_p(n, i) != 0)
		{
			mpz_set(j, i);
			get_i = mpz_get_si(i);
			while (mpz_cmp_ui(j, 0) > 0)
			{
				if (mpz_divisible_p(i, j) != 0)
					l += 1;
				mpz_sub_ui(j, j, 1);

				if (l == 2)
				{
					mpz_tdiv_q_ui(m, n, get_i);
					gmp_printf("%Zd=%Zd*%Zd\n", n, m, i);
					break;
				}
			}
			if (l == 2)
				break;
		}
	}
	mpz_clear(i);
	mpz_clear(j);
	mpz_clear(m);
	mpz_clear(sqrt_n);
}

