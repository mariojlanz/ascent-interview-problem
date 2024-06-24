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

struct Bits {
    unsigned b0:1, b1:1, b2:1, b3:1, b4:1, b5:1, b6:1, b7:1;
};
union Bytes {
    struct Bits bits;
    unsigned char byte;
};

uint32_t sum_primes(uint16_t n);
unsigned char get_bit_value(uint16_t i, union Bytes *primes);
void set_bit_value(uint16_t i, unsigned value, union Bytes *primes);

/************************************************************************************
 *   
 * @brief main
 * @returns error code
 *  
************************************************************************************/
int main(void) {
    //Test inputs and expected outputs
    uint16_t inputs[] = {0, 2, 17, 32, 258, 30359, 65000};
    uint32_t outputs[] = {0, 2, 58, 160, 6338, 46762292, 199091012};
    uint32_t sum = 0;

    uint16_t size = sizeof(inputs) / sizeof(inputs[0]);
    //for each test case, sum the primes and check against expected output
    for (int i = 0; i < size; i++) {
        sum = sum_primes(inputs[i]);
        if (sum == outputs[i]) { 
            printf("Sum of primes to %d: %d\n", inputs[i], sum);
        }
        else {
            printf("ERR: incorrect sum: %d (Should be %d)\n", sum, outputs[i]);
            return 1;
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
uint32_t sum_primes(uint16_t n) {
    //If less then 2, sum is 0 because 2 is the first prime
    if (n < 2) {
        return 0;
    }
    uint32_t sum = 0;

    //Create an array from 2 to n and set all values to true
    union Bytes primes[(n + 6) / 8]; 
    memset(primes, 255, ((n+6)/8) * sizeof(primes[0]));

    //Use the Sieve of Eratosthenes to find all primes up to n
    for (uint16_t i = 2; i * i <= n; i++) {
        if (get_bit_value(i-2, primes) == 1) {
            //Start traversing array from i^2 to reduce total cycles
            for(uint16_t j = i * i; j <= n; j += i) {
                set_bit_value(j-2, 0, primes);
            }
        }
    }
    //Using the resulting array of primes, calculate the sum 
    //printf("\nPrimes:");
    for (uint16_t k = 0; k < n-1; k++) {
        if (get_bit_value(k, primes) == 1) {
            //printf("%d,", i+2);
            sum += k+2;
        }
    }
    //printf("\n");
    return sum;
}

/************************************************************************************
 *   
 * @brief gets the value of the ith bit in primes
 * @param i bit to get value of
 * @param primes array of bits representing numbers
 * @returns value of ith bit in params (0 or 1)
 *  
************************************************************************************/
unsigned char get_bit_value(uint16_t i, union Bytes *primes) {
    unsigned char value = 0;
    switch (i%8) {
        case 0:
            value = primes[i/8].bits.b0;
            break;
        case 1:
            value = primes[i/8].bits.b1;
            break;
        case 2:
            value = primes[i/8].bits.b2;
            break;
        case 3:
            value = primes[i/8].bits.b3;
            break;
        case 4: 
            value = primes[i/8].bits.b4;
            break;
        case 5:
            value = primes[i/8].bits.b5;
            break;
        case 6:
            value = primes[i/8].bits.b6;
            break;
        case 7:
            value = primes[i/8].bits.b7;
            break;
    }
    return value;
}

/************************************************************************************
 *   
 * @brief sets the value of the ith bit in primes to value
 * @param i bit to get value of
 * @param value value to set the bit to (0 or 1)
 * @param primes array of bits representing numbers
 *  
************************************************************************************/
void set_bit_value(uint16_t i, unsigned value, union Bytes *primes) {
    switch (i%8) {
        case 0:
            primes[i/8].bits.b0 = value;
            break;
        case 1:
            primes[i/8].bits.b1 = value;
            break;
        case 2:
            primes[i/8].bits.b2 = value;
            break;
        case 3:
            primes[i/8].bits.b3 = value;
            break;
        case 4: 
            primes[i/8].bits.b4 = value;
            break;
        case 5:
            primes[i/8].bits.b5 = value;
            break;
        case 6:
            primes[i/8].bits.b6 = value;
            break;
        case 7:
            primes[i/8].bits.b7 = value;
            break;
    }
}