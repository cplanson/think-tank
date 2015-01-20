#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>


/**
 * Function returning true if a number is a perfect square, else false
 * @param n : integer, perfect square or not
 * @return : boolean, 1 if n is a perfect square, else 0
 */
int isPerfectSquare(uint64_t n)
{
	uint64_t i;
	for (i = 0 ; i * i < n ; i++)
	{
		if (n == i * i)
			return 1;
	}

	return 0;
}


/**
 * Function computing binomial coefficient
 * @param n : integer
 * @param k : integer
 * @return integer, /n\
 *                  \k/
 */
uint64_t C(uint64_t n, uint64_t k)
{
	uint64_t res = 1;
	uint64_t i;

	for (i = 1 ; i <= k ; i++)
	{
		res *= n - k + i;
		res /= i;
	}

	return res;
}


/**
 * Function returning the position (starting with 0) of the most significant bit 
 * set.
 * @param n : integer
 * @return the index of the most significant bit set in n. 0 is returned if n == 
 * 0and if n == 1.
 */
unsigned int strongestBit(uint64_t n)
{
	unsigned int i, pos = 0;

	for (i = 0 ; i < 8 * sizeof n ; i++)
	{
		if (n & 0x1)
			pos = i;
		n >>= 1;
	}

	return pos;
}

/**
 * Function computing the number of integers in an interval depending on the 
 * number of bits set.
 * @param a : integer
 * @param b : integer
 * @param d : integer
 * @return integer, number of integers in [a;b] whose number of bits set + d is 
 * a perfect square
 */
uint64_t perfectBits(uint64_t a, uint64_t b, uint64_t d)
{
	uint64_t i, n;
	uint64_t sum = 0;

	/* Get "good" intervals */
	if (b < a)
		return perfectBits(b, a, d);
	if (a != 0)
		return perfectBits(0, b, d) - perfectBits(0, a-1, d);

	/* Ending case */
	if (b == 0)
		return isPerfectSquare(d);

	n = strongestBit(b);
	for (i = 1 ; i * i <= n + d ; i++)
	{
		if (i * i >= d)
			sum += C(n, i * i - d);
	}

	return sum + perfectBits(a, b - ((uint64_t)1 << n), d + 1);
}


int main(int argc, char *argv[])
{
	uint64_t a, b;
	char *endptr;

	if (argc < 3)
	{
		printf("Usage : %s <a> <b>, with [a;b] the interval to consider.\n",
			argv[0]);
		exit(EXIT_SUCCESS);
	}

	a = strtoul(argv[1], &endptr, 0);
	if (endptr == argv[1])
	{
		fprintf(stderr, "ERROR : <a> is not a number\n");
		exit(EXIT_FAILURE);
	}

	b = strtoul(argv[2], &endptr, 0);
	if (endptr == argv[2])
	{
		fprintf(stderr, "ERROR : <b> is not a number\n");
		exit(EXIT_FAILURE);
	}

	printf("perfectBits(%lu, %lu) = %lu\n", a, b, perfectBits(a, b, 0));

	return EXIT_SUCCESS;
}

