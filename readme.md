This program will simulate a grocery store with N checkout counters, serving a randomly-generated population of shoppers who appear at a certain rate.

Input parameters:

1. Number of checkout counters.
2. Average number of shoppers per hour.
3. Minimum purchase quantity of each shopper.
4. Maximum purchase quantity of each shopper.
5. Number of hours to simulate.

Output data:

1. Input parameters.
2. Average wait time.
3. Average unhappiness level.
4. Every shopper's statistics:
   (a) Which counter served them.
   (b) Arrival time in queue.
   (c) Number of items in basket.
   (d) Time spent in queue in seconds.
   (e) Unhappiness level.
(See "output.txt" for a sample.)

Note: unhappiness level is calculated as the square of the time spent in queue.

Algorithm:

Every second, do these things sequentially:
(1) Roll the random number generator to check if a shopper is spawned.
    (a) If a shopper is spawned, add it to the queue.
	(b) If no shopper is spawned, do nothing for part (1).
(2) Attempt to serve the queue if the queue is not empty.
    (a) If a counter is free, pop a shopper from the queue to be served.
	(b) If no counter is free, do nothing for part(2).
(3) Make progress on the counters' currently-served customers (decrement the waiting time).

Compilation on MinGW: g++ gshopper.cpp simulate.cpp -o simulate.exe

Unresolved issue:

Initially, I attempted to use <vector> to hold my list of shoppers. However, vector::push_back method does not interact safely with my user-defined type. It causes a heap memory error that crashes the program.

If anyone knows how to fix my Shopper class for vector::push_back, please do let me know!
