#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

/**
 * factorize_number - Factorize the given number and print the result.
 *
 * @n: The number to factorize.
 */
void factorize_number(mpz_t n)
{
	mpz_t fa, qu, sqrt_n;

	mpz_init(fa), mpz_init(qu), mpz_init(sqrt_n), mpz_sqrt(sqrt_n, n);
	if (mpz_divisible_ui_p(n, 2))
	{
		mpz_divexact_ui(qu, n, 2);
		gmp_printf("%Zd=%Zd*2\n", n, qu), mpz_clear(fa);
		mpz_clear(qu), mpz_clear(sqrt_n);
		return;
	}

	if (mpz_divisible_ui_p(n, 3))
	{
		mpz_divexact_ui(qu, n, 3);
		gmp_printf("%Zd=%Zd*3\n", n, qu), mpz_clear(fa);
		mpz_clear(qu), mpz_clear(sqrt_n);
		return;
	}

	for (mpz_set_ui(fa, 5); mpz_cmp(fa, sqrt_n) <= 0; mpz_nextprime(fa, fa))
	{
		if (mpz_divisible_p(n, fa))
		{
			mpz_divexact(qu, n, fa);
			gmp_printf("%Zd=%Zd*%Zd\n", n, qu, fa);
			mpz_clear(fa);
			mpz_clear(qu);
			mpz_clear(sqrt_n);
			return;
		}
	}

	gmp_printf("%Zd=%Zd*1\n", n, n);

	mpz_clear(fa);
	mpz_clear(qu);
	mpz_clear(sqrt_n);
}
/**
 * main - Main function to read numbers from a file and factorize them.
 *
 * @argc: Number of command-line arguments.
 * @argv: Command-line arguments.
 * Return: 0 on success, 1 otherwise.
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
		factorize_number(number);
		mpz_clear(number);
	}

	fclose(file);
	return (0);
}

