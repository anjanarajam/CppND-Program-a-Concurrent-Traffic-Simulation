#include <algorithm>
#include <iostream>
#include <chrono>
#include "TrafficObject.h"

// init static variable
int TrafficObject::_idCnt = 0;

std::mutex TrafficObject::_mtx;

void TrafficObject::setPosition(double x, double y)
{
    _posX = x;
    _posY = y;
}

void TrafficObject::getPosition(double &x, double &y)
{
    x = _posX;
    y = _posY;
}

TrafficObject::TrafficObject()
{
    _type = ObjectType::noObject;
    _id = _idCnt++;
}

TrafficObject::~TrafficObject()
{
    // Task L1.1 : Set up a thread barrier that ensures that all the thread objects in the member vector _threads are joined.
    // Join makes sure that all the threads are termonated before the main function exits
    for (auto& t : _threads) {
        t.join();
    }
}
