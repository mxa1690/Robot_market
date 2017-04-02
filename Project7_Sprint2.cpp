//Mohammed Ali 
//1001241690

#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;

class Robot_part
{
public:
    Robot_part(string robot_name,int robot_modelno, double price, string desc):name(robot_name),model_number(robot_modelno),cost(price),description(desc){}
    friend void print_parts (Robot_part, int i);

protected:
    string name;
    int model_number;
    double cost;
    string description;
    string image_filename;
};
void print_parts(Robot_part robot, int i)
{
    cout<<"\n"<<i<<". "<<robot.name<<"\t";
    cout<<robot.model_number<<"\t";
    cout<<robot.description<<"\t";
    cout<<robot.cost<<"\n";
}
class Robot_models
{
    string name;
    int model_number;
    Robot_part *head;
    Robot_part *torso;
    Robot_part *locomotor;
    Robot_part *arm;
    Robot_part *battery;
public:
    Robot_models (string Name, int modelN, Robot_part *Hd, Robot_part *T, Robot_part *l, Robot_part *a, Robot_part *bat):name(Name),model_number(modelN), head(Hd), torso(T), locomotor(l), arm(a), battery(bat){}
    //Robot_models (string Name, int modelN, Robot_part Hd):name (Name),model_number (modelN), head(Hd){}
    friend void print_models(Robot_models model, int i);
    double cost();
    double max_speed();
    double max_battery_life();
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
    vector <Robot_models*> store;
    vector <Robot_part*> store_head;
    vector <Robot_part*> store_locomotor;
    vector <Robot_part*> store_torso;
    vector <Robot_part*> store_battery;
    vector <Robot_part*> store_arm;
    void create_new_robot_part(string robo_name,int model_no,double price,string description, double max_power,int compartment,int max_arms,double energy,double power_available,int choice);
    void create_new_robot_model();
};
void Shop::create_new_robot_part(string robo_name,int model_no,double price, string description, double max_power, int compartment, int max_arms, double energy, double power_available, int choice)
{
    if (choice ==1)
        store_head.push_back(new Head{robo_name,model_no,price,description,max_power,"Head"});
    else if (choice ==2)
        store_locomotor.push_back(new Locomotor{robo_name,model_no,price,description,max_power,"Locomotor"});
        //Locomotor locomotor(robo_name,model_no,price,description,max_power);
    else if (choice ==3)
        store_torso.push_back(new Torso{robo_name,model_no,price,description,compartment,max_arms,"Torso"});
        //Torso torso(robo_name,model_no,price,description,compartment,max_arms);
    else if (choice ==4)
        store_battery.push_back(new Battery{robo_name,model_no,price,description, power_available, energy, "Battery"});
        //Battery battery(robo_name,model_no,price,description, power_available, energy);
    else if (choice ==5)
        store_arm.push_back(new Arm{robo_name,model_no,price,description, max_power,"Arm"});
        //Arm arm(robo_name,model_no,price,description, max_power);
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
    string menu = "\n--Menu--\n1. Create a new robot part\n2. Create a new robot model\n3. View robot models\n4. Exit\n";
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
    while(cmd!=4){
    cout<<view.menu();
    cout<<"Command? ";
    cin>>cmd;
    cin.ignore();
    execute_cmd(cmd);
    }
}

void Controller::execute_cmd(int cmd)
{
    string robo_name, desc, model_name;
    int model_no, choice, compartment=0, max_arms=2, model_number, head_select, torso_select, locomotor_select, battery_select, arm_select;
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
    else if (cmd==2)
    {
        cout<<"Enter the model name: ";
        //cin.ignore();
        getline(cin,model_name);
        cout<<"Enter model number: ";
        cin>>model_number;
    else if (cmd==3)
	{

	}
    else if (cmd==4)
        cout<<"Thank you and have a great day!!\n";
    else
        cout<<"Invalid!!\n";
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

