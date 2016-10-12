#ifndef GSHOPPER_H
#define GSHOPPER_H

using namespace std;

class Shopper
{
public:
  Shopper();
  // Constructor.
  Shopper(int arrival, int basket, int id);
  // Constructor with arguments.
  Shopper(const Shopper& copyee_object);
  // Need copy constructor despite not needing destructor because we want a queue of them!
  friend ostream& operator <<(ostream& outs, const Shopper& the_object);
  // Overloaded out stream operator for Shopper: displays all statistics for the shopper.
  void time_waited(int now, int counter_num);
  // Calculates time waited in queue and dissatisfaction level.
  int counter_number;
  // Shows the ID of the counter which served the shopper.
  int shopper_id;
  // Shopper ID. Determined at construction.
  int time_queued;
  // How long this customer waited in the queue.
  int service_time;
  // How long it takes, in seconds, to serve this customer at a counter. Function of basket_size.
  double dissatisfaction;
  // How unhappy this customer is because of the wait: calculated as square of time_queued.
private:
  int arrival_time;
  // Arrival time in seconds into the period. For example in a 2 hour period, an arrival time of
  // 7199 is 1 second before the end of the peak period.
  int basket_size;
  // Number of items in shopper's basket.
};

#endif
