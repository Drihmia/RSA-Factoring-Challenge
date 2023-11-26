#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

/**
 * faize_number - Factorize the given number and print the result.
 *
 * @n: The number to faize.
 */
void faize_number(mpz_t n)
{
	mpz_t fa, m;

	if (mpz_cmp_ui(n, 1) == 0 || mpz_cmp_ui(n, 2) == 0 || mpz_cmp_ui(n, 3) == 0)
	{
		gmp_printf("%Zd=%Zd*1\n", n, n);
		return;
	}

	mpz_init(fa);
	mpz_init(m);

	for (mpz_set_ui(fa, 2); mpz_cmp(fa, n) <= 0; mpz_nextprime(fa, fa))
	{
		if (mpz_divisible_p(n, fa))
		{
			mpz_divexact(m, n, fa);
			gmp_printf("%Zd=%Zd*%Zd\n", n, m, fa);
			mpz_clear(fa);
			mpz_clear(m);
			return;
		}
	}

	gmp_printf("%Zd=%Zd*1\n", n, n);

	mpz_clear(fa);
	mpz_clear(m);
}

/**
 * main - Main function to read numbers from a file and factorize them.
 *
 * @argc: Number of command-line arguments.
 * @argv: Command-line arguments.
 * Return: 0 on success, 1 otherwise
 */

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
		return (1);
	}

	FILE *file = fopen(argv[1], "r");

	if (file == NULL)
	{
		perror("Error opening file");
		return (1);
	}

	char buffer[10000];
	mpz_t number;


	while (fgets(buffer, sizeof(buffer), file) != NULL)
	{
		mpz_init(number);
		mpz_set_str(number, buffer, 10);
		faize_number(number);
		mpz_clear(number);
	}

	fclose(file);
	return (0);
}

