#include <stdint.h>
#include <stdio.h>

long unsigned choose(unsigned n, unsigned k);
unsigned log_floor(long unsigned x);
long unsigned my_exp(unsigned x);
long unsigned test(long unsigned a, long unsigned b, int bits_fixed);
int isPerfect(unsigned n);
int squares[8] = {1, 4, 9, 16, 25, 36, 49, 64};

int main(int argc, char *argv[]) {  

	long unsigned a;
	long unsigned b;
	long unsigned scratch;

	if (argc < 3) {
		printf("Usage: $ pbits [a] [b]\n");
		return 0;
	}

	sscanf(argv[1], "%lu", &a);
	sscanf(argv[2], "%lu", &b);

	if (a > b) {
		printf("Error: b must not be less than a\n");
		return 0;
	}
	else if (b == 0) {
		printf("0\n");
		return 0;
	}
	

	printf("You entered a = %lu, b = %lu\n", a, b);
	
	if (a != 0) {
		scratch = test(0, b, 0)- test(0, a-1, 0);
	}
	else {
		scratch = test(0, b, 0);
	}
	printf("Final result: %lu\n", scratch);


}

long unsigned test(long unsigned a, long unsigned b, int bits_fixed) {

	long unsigned scratch;
	long unsigned accumulator;
	int log_floor_a;
	int log_floor_b;
	int i;

	printf("*** Beginning of a Recursion (%lu, %lu) w/ %d bit(s) fixed ***\n",
		a, b, bits_fixed);



	log_floor_b = log_floor(b+1);

	accumulator = 0;
	
	printf("Phase I:  Start with the log_floor of b+1 which is %d\n", 
		log_floor_b);

	i = 0 ;
	while (i < 8 && (squares[i]-bits_fixed) <= log_floor_b) {
		if ((squares[i]-bits_fixed) > 0) {
			printf("Calculating %d - %d = %d bit permutations...\n", 
				squares[i], bits_fixed, squares[i]-bits_fixed);
			scratch = choose(log_floor_b, (squares[i]-bits_fixed)); 
			printf("%u choose %u = %lu\n", log_floor_b, (squares[i]-bits_fixed), scratch);
			accumulator += scratch;
		}
		i++;
	}

	scratch = my_exp(log_floor_b);
	printf("Phase III:  accumulate test(0, b - my_exp(log_floor_b-1) = %lu)\n",
		b-scratch);
	printf("b= %lu; scratch= %lu\n", b, scratch);
	if(b >= scratch) {
		accumulator += test(0, b-scratch, bits_fixed+1);		
	}

	if (isPerfect(bits_fixed)==0) {
		printf("bits_fixed is a perfect square, +1\n");
		accumulator++;
	
	}	

	printf("*** Recursion Ending (%lu, %lu) w/ %d bit(s) fixed, returning %lu ***\n",
		a, b, bits_fixed, accumulator);
	return accumulator;
}

long unsigned choose(unsigned n, unsigned k) {
      long unsigned r = 1;
      long unsigned d;
      if (k > n) return 0;
      for (d=1; d <= k; d++) {
          r *= n--;
          r /= d;
      }
      return r;
}

unsigned log_floor(unsigned long x) {
	int i;
	unsigned leftmost_bit;
	if (x == 0) {
		return -1;
	}
	i = 0;
        leftmost_bit = 0;

        while (x > 0) {
                x >>= 1;
                leftmost_bit++;
        }
	leftmost_bit--;
	return leftmost_bit;
}

long unsigned my_exp(unsigned x) {
	long unsigned result = 1;
	return (result << x);
}

int isPerfect(unsigned n) {
	int i;
	i = 0;
	while (i < 8 && squares[i] <= n) {
		if (squares[i] == n) {
			return 0;
		}
		i++;
	}
	return 1;
}
