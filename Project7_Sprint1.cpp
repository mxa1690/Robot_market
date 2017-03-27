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

class Shop
{
public:
    void create_new_robot_part(string robo_name,int model_no,double price,string description, double max_power,int compartment,int max_arms,double energy,double power_available,int choice);
    void create_new_robot_model();
};
void Shop::create_new_robot_part(string robo_name,int model_no,double price, string description, double max_power, int compartment, int max_arms, double energy, double power_available, int choice)
{
    if (choice ==1)
        Head head(robo_name,model_no,price,description,max_power);
    else if (choice ==2)
        Locomotor locomotor(robo_name,model_no,price,description,max_power);
    else if (choice ==3)
        Torso torso(robo_name,model_no,price,description,compartment,max_arms);
    else if (choice ==4)
        Battery battery(robo_name,model_no,price,description, power_available, energy);
    else if (choice ==5)
        Arm arm(robo_name,model_no,price,description, max_power);
}
class View
{
public:
    View(Shop& sp):shop(sp){}
    string menu();
private:
    Shop& shop;
};
string View::menu()
{
    string menu = "\n--Menu--\n1. Create a new robot part\n2. Exit\n";
    return menu;
}

class Controller
{
public:
    Controller (Shop& sp, View& view):shop (sp), view (view) {}
    void cli();
    void execute_cmd(int cmd);
private:
    Shop& shop;
    View& view;
};


int main()
{
    Shop sp;
    View view(sp);
    Controller controller (sp,view);
    return 0;
}

