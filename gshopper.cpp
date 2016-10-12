// Implementation file for Shopper class.
#include <iostream>
#include <fstream>
#include <cstdlib>
#include "gshopper.h"
using namespace std;

Shopper::Shopper()
{
  shopper_id = -1;
  counter_number = -1;
  time_queued = -1;
  dissatisfaction = -1;
  arrival_time = -1;
  basket_size = -1;
  service_time = -1;
}

Shopper::Shopper(int arrival, int basket, int id)
{
  if (basket <= 0)
    {
      cout << "Basket size should never be 0 or less.\n";
      exit(1);
    }
  arrival_time = arrival;
  basket_size = basket;
  shopper_id = id;
  service_time = 20 + basket_size * 5;
  // For other values: initialize them at -1.
  counter_number = -1;
  time_queued = -1;
  dissatisfaction = -1;
}

Shopper::Shopper(const Shopper& copyee_object)
{
  shopper_id = copyee_object.shopper_id;
  counter_number = copyee_object.counter_number;
  time_queued = copyee_object.time_queued;
  dissatisfaction = copyee_object.dissatisfaction;
  arrival_time = copyee_object.arrival_time;
  basket_size = copyee_object.basket_size;
  service_time = copyee_object.service_time;
}

ostream& operator <<(ostream& outs, const Shopper& the_object)
{
  outs << the_object.shopper_id << ","
       << the_object.counter_number << ","
       << the_object.arrival_time << ","
       << the_object.basket_size << ","
       << the_object.time_queued << ","
       << the_object.dissatisfaction << "\n";
  return outs;
}

void Shopper::time_waited(int time_now, int counter_num)
{
  time_queued = time_now - arrival_time;
  counter_number = counter_num;
  dissatisfaction = time_queued * time_queued;
}
