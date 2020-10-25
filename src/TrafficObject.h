#ifndef TRAFFICOBJECT_H
#define TRAFFICOBJECT_H

#include <vector>
#include <thread>
#include <mutex>

enum ObjectType
{
    noObject,
    objectVehicle,
    objectIntersection,
    objectStreet,
};

class TrafficObject
{
public:
    // constructor / desctructor
    TrafficObject();
    ~TrafficObject();

    // getter and setter
    //Get the id of the traffic object
    int getID() { return _id; }
    //set the position of the vehicle
    void setPosition(double x, double y);
    // Get the position of the vehicle
    void getPosition(double &x, double &y);
    // Get the type of traffic object : vehicle, intersections, street, traffic lights
    ObjectType getType() { return _type; }

    // typical behaviour methods
    virtual void simulate(){};

protected:
    ObjectType _type;                 // identifies the class type
    int _id;                          // every traffic object has its own unique id
    double _posX, _posY;              // vehicle position in pixels
    std::vector<std::thread> threads; // holds all threads that have been launched within this object
    static std::mutex _mtx;           // mutex shared by all traffic objects for protecting cout 

private:
    static int _idCnt; // global variable for counting object ids
};

#endif