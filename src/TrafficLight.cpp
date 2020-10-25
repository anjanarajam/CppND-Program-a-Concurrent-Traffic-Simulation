#include <iostream>
#include <random>
#include "TrafficLight.h"
#include <future>

/* Implementation of class "MessageQueue" */

/*
template <typename T>
T MessageQueue<T>::receive()
{
    // FP.5a : The method receive should use std::unique_lock<std::mutex> and _condition.wait() 
    // to wait for and receive new messages and pull them from the queue using move semantics. 
    // The received object should then be returned by the receive function. 
}

*/

template <typename T>
void MessageQueue<T>::send(T &&msg)
{
    // FP.4a : The method send should use the mechanisms std::lock_guard<std::mutex> 
    // as well as _condition.notify_one() to add a new message to the queue and afterwards send a notification.
    // Add lock guard for automatic locking and unlocking
    std::lock_guard<std::mutex> lck(_mutex);

    //Push messages to the queue
    _queue.emplace_back(std::move(msg));

    // notify client after pushing msg into queue
    _cond.notify_one();
}


/* Implementation of class "TrafficLight" */

/* 
TrafficLight::TrafficLight()
{
    _currentPhase = TrafficLightPhase::red;
}

void TrafficLight::waitForGreen()
{
    // FP.5b : add the implementation of the method waitForGreen, in which an infinite while-loop 
    // runs and repeatedly calls the receive function on the message queue. 
    // Once it receives TrafficLightPhase::green, the method returns.
}

*/

TrafficLightPhase TrafficLight::getCurrentPhase()
{
    return _currentPhase;
}



void TrafficLight::simulate()
{
    // FP.2b : Finally, the private method „cycleThroughPhases“ should be started in a thread when the public method „simulate“ is called. To do this, use the thread queue in the base class. 
    threads.emplace_back(std::thread(&TrafficLight::cycleThroughPhases, this));
 }

/* virtual function which is executed in a thread */
void TrafficLight::cycleThroughPhases()
{
    // FP.2a : Implement the function with an infinite loop that measures the time between two loop cycles 
    // and toggles the current phase of the traffic light between red and green and sends an update method 
    // to the message queue using move semantics. The cycle duration should be a random value between 4 and 6 seconds. 
    // Also, the while-loop should use std::this_thread::sleep_for to wait 1ms between two cycles.

    // Variables to get the time difference between two loop cycles
    long timeSinceLastUpdate{};
    std::chrono::time_point<std::chrono::system_clock> lastUpdate;

    // Get the random duration cycle between 4 and 6
    std::random_device rd;
    std::mt19937 eng(rd());
    std::uniform_int_distribution<> distr(4, 6);
    int cycle_duration = distr(eng);    

    // Get the current value of time
    lastUpdate = std::chrono::system_clock::now();

    while (true) {
        // Sleep for 1 milliseonds
        std::this_thread::sleep_for(std::chrono::milliseconds(1));

        // Get the time difference between two loop cycles
        timeSinceLastUpdate = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - lastUpdate).count();

        // Check if time difference is greater than cycle duration
        if (timeSinceLastUpdate >= cycle_duration) {

            //Toggle between red and green light
            if (_currentPhase == green) {
                _currentPhase = red;
            }
            else {
                _currentPhase = green;
            }

            //std::future<void> update_phase_ftr = std::async(std::launch::async, &MessageQueue<TrafficLightPhase>::send, _currentPhase);


        }

        // Reset the last update variable at the end of the cycle 
        lastUpdate = std::chrono::system_clock::now();
    }
}

