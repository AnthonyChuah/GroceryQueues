#include <iostream>
#include <cstdlib>
#include <vector>
#include <queue>
#include <fstream>
#include "gshopper.h"

using namespace std;

int main()
{
  int ncounters, flowrate, sim_length, min_purchases, max_purchases;
  // ncounters is the number of service counters.
  // flowrate is the number of shoppers per hour.
  // sim_length is the number of hours simulated.
  // Display a welcome message with instructions.
  cout << "Welcome to the Store Simulator!\n\n";
  // Ask for user input and collect simulation parameters from there.
  cout << "Please provide the number of counters in your store: ";
  cin >> ncounters; cin.ignore(80, '\n');
  cout << "Average number of shoppers coming through in an hour: ";
  cin >> flowrate; cin.ignore(80, '\n');
  cout << "Minimum number of items bought by each shopper: ";
  cin >> min_purchases; cin.ignore(80, '\n');
  cout << "Maximum number of items bought by each shopper: ";
  cin >> max_purchases; cin.ignore(80, '\n');
  cout << "How many hours would you like to simulate: ";
  cin >> sim_length; cin.ignore(80, '\n');
  cout << "\n";

  int simlength_seconds = sim_length * 3600;
  double arrival_prob = flowrate / 3600.0;
  if (arrival_prob > 1 || arrival_prob <= 0)
    {
      cout << "Illegal average rate of shopper arrival. Choose between 1 to 3600.\n";
      exit(1);
    }
  vector<int> counters; // List of counters' waiting times: if waiting time drops to 0 then it will serve.
  // Use a loop to create a list of shop counters' waiting times (initialized at 0).
  for (int i = 0; i < ncounters; i++)
    counters.push_back(0);
  vector<Shopper> shoppers; // A record of all the shoppers who've appeared.
  queue<Shopper> shop_queue; // Shoppers who actually need to get served.
  // Every time you spawn shoppers, they join the queue.
  // However if there are empty counters available to serve them, they will get instantly popped from queue.
  int id = 0;
  for (int sec = 0; sec < simlength_seconds; sec++)
    {
      // Spawn shopper (or not) - according to arrival_prob.
      double runif01 = static_cast<double>(rand()) / RAND_MAX;
      // cout << "Debug check rand() value " << static_cast<double>(rand()) << "\n";
      // cout << "Debug check RAND_MAX value " << static_cast<double>(RAND_MAX) << "\n";
      if (runif01 < arrival_prob)
	{
	  id++;
	  // Randomly generate number of items to be bought by shopper.
	  int basket_size = rand() % (max_purchases - min_purchases + 1) + min_purchases;
	  Shopper new_shopper(sec, basket_size, id);
	  shoppers.push_back(new_shopper);
	  shop_queue.push(new_shopper);
	}
      // If a counter is available, pop a shopper from the queue to be served.
      for (int i = 0; i < ncounters; i++)
	{
	  if (counters[i] == 0)
	    {
	      if (shop_queue.empty())
		{
		  // Do nothing.
		}
	      else
		{
		  // Calculate the shopper's time_queued, counter_number, dissatisfaction.
		  shoppers[shop_queue.front().shopper_id].time_waited(sec, i);
		  // Now the counter is busy serving this shopper. Set its wait_time accordingly.
		  counters[i] = shop_queue.front().service_time;
		  shop_queue.pop();
		}
	    }
	}
      // Decrement all counters' wait_times.
      for (int i = 0; i < ncounters; i++)
	{
	  if (counters[i] > 0)
	    counters[i]--;
	}
    }
  // Calculate average statistics.
  int total_waited = 0;
  double total_angry = 0;
  double average_wait = 0, average_angry = 0;
  for (int j = 0; j < id; j++)
    {
      total_waited += shoppers[j].time_queued;
      total_angry += shoppers[j].dissatisfaction;
    }
  average_wait = static_cast<double>(total_waited) / id;
  average_angry = total_angry / id;
  cout << "Average wait time: " << average_wait << "\n";
  cout << "Average unhappiness: " << average_angry << "\n";
  // Output results of the simulation in a text data dump.
  char outfilename[80];
  cout << "Specify name of file for data dump of all statistics: ";
  cin >> outfilename;
  ofstream outs;
  outs.open(outfilename);
  outs << "Store:\n\n";
  outs << "  Counters: " << ncounters << "\n";
  outs << "  Customers: " << id << "\n";
  outs << "  Arrival rate: " << flowrate << " customers per hour.\n";
  outs << "  Purchases per customer: " << min_purchases << " to " << max_purchases << "\n\n";
  outs << "ID,Counter_Used,Arrival,Basket_Size,Queue_Time,Unhappiness\n\n";
  for (int j = 0; j < id; j++)
    outs << shoppers[j];
  outs.close();
  return 0;
}
