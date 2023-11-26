#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

void factorize_number(mpz_t n)
{
	mpz_t factor, m, ll;
	int kl = 0;

	mpz_init(factor);
	mpz_init(m);
	mpz_init(ll);
	mpz_sqrt(ll, n);

	mpz_set_ui(factor, 2);
	while (mpz_cmp_ui(factor, (unsigned long)ll) <= 0)
	{
		while (mpz_divisible_p(n, factor))
		{
			mpz_divexact(m, n, factor);
			gmp_printf("%Zd=%Zd*%Zd\n", n, m, factor);
			kl = 1;
			mpz_set(n, m);
			return;
		}
		mpz_nextprime(factor, factor);
	}

	if (kl == 0 && mpz_cmp_ui(n, 2) > 0)
	{
		gmp_printf("%Zd=%Zd*1\n", n, n);
	}

	mpz_clear(factor);
	mpz_clear(m);
}

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

	char buffer[100000];
	mpz_t number;

	mpz_init(number);

	if (fgets(buffer, sizeof(buffer), file) != NULL)
	{
		mpz_set_str(number, buffer, 10);
		factorize_number(number);
	}

	fclose(file);
	mpz_clear(number);
	return (0);
}
