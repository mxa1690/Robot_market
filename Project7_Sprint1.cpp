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

