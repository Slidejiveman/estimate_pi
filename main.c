#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <time.h>

/**
 * Generates a random double between -1.0 and 1.0
 *
 * @return the random value
 */
double generate_random() {
    return (double)rand() / RAND_MAX*2.0-1.0;
}

/**
 * Calculates the number of dart tosses that result in a hit.
 *
 * @param number_tosses - accepts the number of throwing attempts
 * @return the number of tosses that result in a hit
 */
long long int calculate_number_of_hits(long long int number_tosses) {

    long long int number_of_hits = 0;
    double x, y, distance_squared;

    // Parallelize this loop
    // number_of_hits must be a reduction variable
    // the threads will join implicitly after the completion of this block
# pragma omp parallel for num_threads(8) reduction(+:number_of_hits)
    for (int toss = 0; toss < number_tosses; toss++) {
        x = generate_random();
        y = generate_random();
        distance_squared = x*x + y*y;
        if (distance_squared <= 1) {
            number_of_hits++;
        }
    }
    return number_of_hits;
}

/**
 * Estimates the value of pi
 *
 * @param number_of_hits - the number of successful dart tosses
 * @param number_of_tosses - the total number of dart tosses
 * @return the estimate of pi
 */
double estimate_pi(long long int number_of_hits, long long int number_of_tosses) {
    return 4 * number_of_hits / ((double) number_of_tosses);
}

int main() {
    srand(time(NULL));
    double pi_estimate;
    long long int number_of_tosses = 0;
    long long int number_of_hits;

    // read in the number of tosses to attempt as a long long int
    while (number_of_tosses != -1) {
        printf("Please input the number of attempts to make at the dart board. Enter -1 to stop. : \n");
        scanf("%lld", &number_of_tosses);
        if (number_of_tosses != -1) {
            // calculate the estimate of pi
            number_of_hits = calculate_number_of_hits(number_of_tosses);
            pi_estimate = estimate_pi(number_of_hits, number_of_tosses);

            printf("The estimate for pi is: %f\n", pi_estimate);
        }
    }
    return 0;
}
