#ifndef GSHOPPER_H
#define GSHOPPER_H

using namespace std;

class Shopper
{
public:
  Shopper();
  // Constructor.
  Shopper(int arrival_time, basket_size);
  // Constructor with arguments.
  void join_shortest_queue();
  // Makes the shopper join the shortest queue.
  int counter_number;
  // Shows the ID of the counter at which the shopper is queued.
  int shopper_id;
  // Shows shopper ID.
  double calc_service_time();
  // Calculates how long a counter would take to process shopper's items.
private:
  int arrival_time;
  // Arrival time in seconds into the peak period. For example in a 2 hour peak period, an arrival time of
  // 7199 is 1 second before the end of the peak period.
  int basket_size;
  // Number of items in shopper's basket.
};

class Store
{
public:
  Store();
  // Constructor sets default.
  Store(int number_counters, int number_shoppers, int peak_period);
  // Constructor with arguments.
private:
  int counters;
  // Number of counters in the store.
  int number_shoppers;
  // Number of shoppers in the store.
  int peak_period;
  // The length of the peak period in seconds.
};

#endif
