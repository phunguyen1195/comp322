#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

void *worker(void *param);

#define NUMBER_OF_DARTS		50000000
#define NUMBER_OF_THREADS	2
pthread_mutex_t mutex;
/* TODO: This is the number of hits in the circle
ensure that there is no race condition on circle count */
int circle_count = 0;


double random_double()
{
	/* a double precision random number generator */
	return random() / ((double)RAND_MAX + 1);
}

int main (int argc, const char * argv[]) {

	/*TODO: Initialize data structures for the program*/
	int darts_per_thread = NUMBER_OF_DARTS/ NUMBER_OF_THREADS;
	int i;
	double estimated_pi;
	pthread_t  tids[NUMBER_OF_THREADS];

	/* seed the random number generator */
	srandom((unsigned)time(NULL));
	pthread_mutex_init(&mutex, NULL);
	/*TODO: Use multi-threading to update circle_count*/
	for (i = 0; i < NUMBER_OF_THREADS; i++) {
		pthread_create(&tids[i], NULL, worker, NULL);
	}

	//for (i = 0; i < NUM_THREADS; i++)
		//pthread_join(tids[i], NULL);

	/* estimate Pi */
	estimated_pi = 4.0 * circle_count / NUMBER_OF_DARTS;
	printf("Pi = %f\n",estimated_pi);

	return 0;
}

void *worker(void *param)
{
	int number_of_darts;
	number_of_darts = *((int *)param);
	int i;
	int hit_count = 0;
	double x,y;
	pthread_mutex_lock(&mutex);
	for (i = 0; i < NUMBER_OF_DARTS; i++) {

		/* TODO: generate random numbers between -1.0 and +1.0 (exclusive)
		and test if it is within the circle.*/
		if(random_double() <= 1.0 || random_double() >= -1.0)
			y = random_double();
		if(random_double() <= 1.0 || random_double() >= -1.0)
			x = random_double();
		if(sqrt(x*x + y*y) <= 1){
			hit_count ++;
			circle_count ++;
		}
	}
	pthread_mutex_unlock(&mutex);
	pthread_exit(0);
}
