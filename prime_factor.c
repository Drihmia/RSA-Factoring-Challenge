#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <gmp.h>

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
	/* initiliaze mpz_t variable */
	mpz_init(num_elements);

	while (getline(&line, &size, file) != -1)
	{
		if (line && strlen(line) > 1)
		{
			mpz_init_set_str(num_elements, line, 10);
			prime_nums_of(num_elements);
			mpz_clear(num_elements);
		}
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
	int l;
	mpz_t i, sqrt_n, m;


	mpz_init(i);
	mpz_init(m);
	mpz_init(sqrt_n);
	mpz_sqrt(sqrt_n, n);


	for (mpz_init_set_ui(i, 2); mpz_cmp(i, sqrt_n) <= 0; mpz_add_ui(i, i, 1))
	{
		l = 1;
		if (mpz_divisible_p(n, i) != 0)
		{
			mpz_tdiv_q(m, n, i);
			gmp_printf("%Zd=%Zd*%Zd\n", n, m, i);
			l = 0;
			break;
		}
	}
	if (l == 1)
		gmp_printf("%Zd=%Zd*%d\n", n, n, 1);
	mpz_clear(i);
	mpz_clear(m);
	mpz_clear(sqrt_n);
}


