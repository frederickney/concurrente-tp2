#include "tickets.h"

tickets_t get_tickets_t() {
	tickets_t tickets;
	tickets.count = 1;
	tickets.current = 0;
	tickets.nb_bankers = 1;
	tickets.opening_bank = 0;
	sem_init (&tickets.sem_count_id, 0, 1);
	sem_init (&tickets.sem_current_id, 0, 1);
	return tickets;
}
unsigned int get_ticket (tickets_t *ticket) {
	int count;
	sem_wait (&(ticket->sem_count_id));
	count = ticket->count++;
	sem_post (&(ticket->sem_count_id));
	return count;
}

unsigned int set_current (tickets_t *ticket) {
	int current;
	sem_wait (&(ticket->sem_current_id));
	current = ticket->current++;
	sem_post (&(ticket->sem_current_id));
	return current;
}

unsigned int get_current (tickets_t *ticket) {
	int current;
  sem_wait (&(ticket->sem_current_id));
  current = ticket->current;
  sem_post (&(ticket->sem_current_id));
  return current;
}
