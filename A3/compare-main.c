/* Complete the C version of the driver program for compare. This C code does
 * not need to compile. */

#include <stdio.h>

extern long compare(long, long);

int main(int argc, char *argv[]) {

// First, check to see if the total number of args is strictly 2
// If it isn't, print the error statement and return 1
if (argv.length() > 2 || argv.length() < 1) {
  printf("Two arguments required");
  return 1;
}

else {
	// First, convert both of the args to longs for further calculations
 	long x = atol(argv[1]);
 	long y = atol(argv[2]);
	// Using if/else statements, compare first value to second value
	// Print the respective statement based on the comparison
	// Return 0 after each so that we know the function worked as intended for 2 args
	if (x > y) {
  		printf("greater");
		return 0;
	}	
	else if (x == y) {
  		printf("equal");
		return 0;
	}
	else (x < y) {
  		printf("less");
		return 0;
	}
}
}

