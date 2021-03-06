#include"bank.h"
#include"tickets.h"

void *banker (void *argv) {
	banker_t *bankers_data = (banker_t *) argv;
	while (true) {
		//TODO banker
		bankers_data->in_bank = 0;
		bankers_data->current = set_current (bankers_data->tickets);
		printf ("current %d ", bankers_data->current);
		for (int i = 0; i < bankers_data->nb_customers; i++) {
			// consulting array of list_t structure for calling the right customer
			if (bankers_data->customers_list[i].ticket == bankers_data->current) {
				bankers_data->in_bank = bankers_data->customers_list[i].in_bank; // testing if the customer is in bank see next if statement
				bankers_data->serve_customer = i; // remembering the right customer
				printf ("%d / ", bankers_data->serve_customer);
				break;
			}
		}
		if (bankers_data->in_bank) {
			printf ("calling %d %d\n", bankers_data->customers_list[bankers_data->serve_customer].ticket, bankers_data->serve_customer);
			sleep (bankers_data->tickets->serve_time); // serving customers
			sem_post (&(bankers_data->customers_list[bankers_data->serve_customer].sem_customer)); // making out the customer
			sem_wait (&(bankers_data->tickets->sem_banker)); // waiting for the next customers into list
		}
		else if (bankers_data->in_bank == 0) {
			if (bankers_data->tickets->current >= 0) {
				bankers_data->tickets->opening_bank = 1;
			}
			sem_wait (&(bankers_data->tickets->sem_banker));// initial waiting for the first customers into list
		}
	}
}

pthread_t *create_banks (banker_t *bankers_data) {
	// initialising array and allocating memory for pthread_t structure
	pthread_t *bankers;
	bankers = malloc (sizeof (pthread_t));

	//creating banker(s) threads
	for (int i = 0; i < bankers_data->tickets->nb_bankers; i++)
		if (pthread_create(bankers, NULL, banker, (void *) &bankers_data[i]) != 0) {
			perror ("Thread creation error");
      exit (EXIT_FAILURE);
		}

	return bankers;
}