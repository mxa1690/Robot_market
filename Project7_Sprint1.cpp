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
void Controller::cli()
{
    int cmd=-1;
    while(cmd!=2){
    cout<<view.menu();
    cout<<"Command? ";
    cin>>cmd;
    cin.ignore();
    execute_cmd(cmd);
    }
}

void Controller::execute_cmd(int cmd)
{
    string robo_name, desc;
    int model_no, choice, compartment=0, max_arms=2;
    double cost, energy=0, max_power, power_available;
    if (cmd==1)
    {

            bool ans_part;
            do{
                cout<<"Which part?\n1. Head\n2. Locomotor\n3. Torso\n4. Battery\n5. Arm\n";
                ans_part=true;
                cin>>choice;
                if ((choice<1)||(choice>5))
                    {
                        cout<<"Error:Options are from 1 to 5!\n";
                        ans_part = false;
                    }
            } while (ans_part!=true);

            cout<<"Enter the part name - ";
            cin.ignore();
            getline(std::cin,robo_name);
            cout<<"Enter the model number - ";
            cin>>model_no;
            cout<<"Enter the cost - ";
            cin>>cost;
            cin.ignore();
            cout<<"Enter the description - ";
            cin.ignore();
            getline(std::cin,desc);
            if ((choice==2)||(choice==5)||(choice==1))
            {
                cout<<"Maximum power - ";
                cin>>max_power;
            }
            else if (choice==3)
            {
                bool ans_compartment;
                do{
                    ans_compartment=true;
                        cout<<"Enter the number of battery compartments (between 1 and 3) - ";
                        cin>>compartment;
                    if ((compartment<1)||(compartment>3))
                    {
                        cout<<"Error:Compartments should be between 1 and 3\n";
                        ans_compartment = false;
                    }

                }while(ans_compartment!=true);
              cout<<"Enter the max arms - ";
              cin>>max_arms;
            }
            else if (choice==4)
            {
                cout<<"Energy the battery contains (in kW h) - ";
                cin>>energy;
                cout<<"Power available";
                cin>>power_available;
            }
            shop.create_new_robot_part(robo_name, model_no, cost, desc, max_power, compartment, max_arms, energy, power_available, choice);
    }
       // "WILL CONTINUE HERE LATER"
}



int main()
{
    Shop sp;
    View view(sp);
    Controller controller (sp,view);
    controller.cli();
    return 0;
}

