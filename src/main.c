/************************************************************************************
 * 	
 * 	@file     main.c
 *  @author   Mario Lanzilotta
 * 	@brief    Interview Problem for Ascent
 *  
************************************************************************************/

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

uint16_t sum_primes(uint16_t n);


/************************************************************************************
 *   
 * @brief main
 * @returns error code
 *  
************************************************************************************/
int main(void) {
    //Test inputs and expected outputs
    int inputs[] = {0, 2, 32, 17, 258, 30359};
    int outputs[] = {0, 2, 160, 58, 6338, 35124};

    int size = sizeof(inputs) / sizeof(inputs[0]);
    for (int i = 0; i < size; i++) {
        if (sum_primes(inputs[i]) == outputs[i]) { 
            printf("Sum of primes to %d: %d\n", inputs[i], sum_primes(inputs[i]));
        }
        else {
            printf("ERR: incorrect sum: %d (Should be %d)\n", sum_primes(inputs[i]), outputs[i]);
        }
    }
    return 0;
}

/************************************************************************************
 *   
 * @brief Sums prime numbers up to n
 * @param n Highest possible prime number 
 * @returns sum of prime numbers up to n
 *  
************************************************************************************/
uint16_t sum_primes(uint16_t n) {
    //If less then 2, sum is 0 because 2 is the first prime
    if (n < 2) {
        return 0;
    }
    uint16_t sum = 0;

    //Create an array from 2 to n and set all values to true
    bool primes[n-1]; 
    memset(primes, true, sizeof(primes));

    //Use the Sieve of Eratosthenes to find all primes up to n
    for (uint16_t i = 2; i * i <= n; i++) {
        if (primes[i-2] == true) {
            //Start traversing array from i^2 to reduce total cycles
            for(uint16_t j = i * i; j <= n; j += i) {
                primes[j-2] = false;
            }
        }
    }
    //Using the resulting array, calculate the sum 
    //printf("\nPrimes:");
    for (uint16_t i = 0; i < sizeof(primes); i++) {
        if (primes[i] == true) {
            //printf("%d,", i+2);
            sum += i+2;
        }
    }
    //printf("\n");
    return sum;
}

/*optimizations:
use a dynamic array (still worse when n = 100000)
*/