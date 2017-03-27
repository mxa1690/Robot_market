#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;

class Robot_part
{
public:
    Robot_part(string robot_name,int robot_modelno, double price, string desc):name(robot_name),model_number(robot_modelno),cost(price),description(desc){}

protected:
    string name;
    int model_number;
    double cost;
    string description;
    string image_filename;
};
class Head:public Robot_part
{
public:
    Head (string robot_name,int robot_modelno, double price, string desc,double power_req):Robot_part(robot_name,robot_modelno,price,desc) {power = power_req;}
    double power;
};

class Locomotor:public Robot_part
{
public:
    Locomotor (string robot_name,int robot_modelno, double price, string desc, double power_req) :Robot_part(robot_name,robot_modelno,price,desc) {max_power = power_req;}
    double max_power;
};

class Torso:public Robot_part
{
public:
    Torso (string robot_name,int robot_modelno, double price, string desc, int compartments, int max_arms): Robot_part(robot_name,robot_modelno,price,desc) {battery_compartments = compartments ; MaxArms = max_arms;}
    int battery_compartments;
    int MaxArms;
};

class Battery:public Robot_part
{
public:
    Battery (string robot_name,int robot_modelno, double price, string desc, double power_available, double energy):Robot_part(robot_name,robot_modelno,price,desc) {PowerAvailable = power_available ; max_energy = energy;}
    double PowerAvailable;
    double max_energy;
};

class Arm:public Robot_part
{
public:
    Arm (string robot_name,int robot_modelno, double price, string desc, double max_power):Robot_part(robot_name,robot_modelno,price,desc) {MaxPower = max_power;}
    double MaxPower;
};

