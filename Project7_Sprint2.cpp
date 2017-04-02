#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>

using namespace std;

class Robot_part
{
public:
    Robot_part(){};
    Robot_part(string robot_name,int robot_modelno, double price, string desc, string what_part):name(robot_name),model_number(robot_modelno),cost(price),description(desc), type(what_part){}
    friend void print_parts (Robot_part, int i);
    string type;
protected:

    string name;
    int model_number;
    double cost;
    string description;
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
void print_models(Robot_models model, int i)
{
    cout<<"\n->Name: "<<model.name<<"\tModel number: "<<model.model_number<<"\tContains the following parts: ";
    if((model.head)==0)
    {
        //cout<<"Hello";
        //cout<<(model.head)->type;
    }
}

class Head:public Robot_part
{
public:
    Head (string robot_name,int robot_modelno, double price, string desc,double power_req, string type):Robot_part(robot_name,robot_modelno,price,desc,"Head") {power = power_req;}
    double power;
};

class Locomotor:public Robot_part
{
public:
    Locomotor (string robot_name,int robot_modelno, double price, string desc, double power_req, string type) :Robot_part(robot_name,robot_modelno,price,desc, "Locomotor") {max_power = power_req;}
    double max_power;
};

class Torso:public Robot_part
{
public:
    Torso (string robot_name,int robot_modelno, double price, string desc, int compartments, int max_arms, string type): Robot_part(robot_name,robot_modelno,price,desc,"Torso") {battery_compartments = compartments ; MaxArms = max_arms;}
    int battery_compartments;
    int MaxArms;
};

class Battery:public Robot_part
{
public:
    Battery (string robot_name,int robot_modelno, double price, string desc, double power_available, double energy, string type):Robot_part(robot_name,robot_modelno,price,desc, "Battery") {PowerAvailable = power_available ; max_energy = energy;}
    double PowerAvailable;
    double max_energy;
};

class Arm:public Robot_part
{
public:
    Arm (string robot_name,int robot_modelno, double price, string desc, double max_power, string type):Robot_part(robot_name,robot_modelno,price,desc, "Arm") {MaxPower = max_power;}
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
    void create_new_robot_model(string model_name,int model_number,Robot_part *head, Robot_part *locomotor, Robot_part *torso, Robot_part *battery, Robot_part *arm);
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
void Shop::create_new_robot_model(string model_name,int number,Robot_part *head, Robot_part *locomotor, Robot_part *torso, Robot_part *battery, Robot_part *arm)
{
    //Robot_models model(model_name);
    store.push_back(new Robot_models{model_name, number, head, torso, locomotor, arm, battery});
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
        if (!shop.store_head.empty())
        {
           cout<<"\nAvailable robot heads are: ";
            for ( auto & val: shop.store_head)
            {
                int i=1;
                print_parts(*val,i);
                i++;
            }
            cout<<"Option?";
            cin>>head_select;
        }
        if (!shop.store_locomotor.empty())
        {
            cout<<"\nAvailable robot locomotors are: ";
            for ( auto & val: shop.store_locomotor)
            {
                 int i=1;
                print_parts(*val,i);
                i++;
            }
            cout<<"Option?";
            cin>>locomotor_select;
        }
        if (!shop.store_torso.empty())
        {
            cout<<"\nAvailable robot torsos are: ";
            for ( auto & val: shop.store_torso)
            {
                 int i=1;
                print_parts(*val,i);
                ++i;
            }
            cout<<"Option?";
            cin>>torso_select;
        }
        if (!shop.store_battery.empty())
        {
            cout<<"\nAvailable robot batteries are: ";
            for ( auto & val: shop.store_battery)
            {
                 int i=1;
                print_parts(*val,i);
                i++;
            }
            cout<<"Option?";
            cin>>battery_select;
        }
        if (!shop.store_arm.empty())
        {
            cout<<"\nAvailable robot arms are: ";
            for ( auto & val: shop.store_arm)
            {
                 int i=1;
                print_parts(*val,i);
                i++;
            }
            cout<<"Option?";
            cin>>arm_select;
        }
        Robot_part *h=0, *l=0,*t=0, *b=0, *a=0;
        if (!shop.store_head.empty())
            Robot_part *h =(shop.store_head[head_select-1]);
        if (!shop.store_locomotor.empty())
            Robot_part *l =(shop.store_locomotor[locomotor_select-1]);
        if (!shop.store_torso.empty())
            Robot_part *t =(shop.store_torso[torso_select-1]);
        if (!shop.store_battery.empty())
            Robot_part *b =(shop.store_battery[battery_select-1]);
        if (!shop.store_arm.empty())
            Robot_part *a =(shop.store_arm[arm_select-1]);
        //if ((!shop.store_head.empty())&&(!shop.store_locomotor.empty())&&(!shop.store_torso.empty())&&(!shop.store_battery.empty())&&(!shop.store_arm.empty()))
        //shop.create_new_robot_model(model_name,model_number,*(shop.store_head[head_select-1]),*(shop.store_locomotor[locomotor_select-1]),*(shop.store_torso[torso_select-1]),*(shop.store_battery[battery_select-1]), *(shop.store_arm[arm_select-1]));
        shop.create_new_robot_model(model_name,model_number,h,l,t,b,a);
    }
    else if (cmd==3)
    {
        cout<<"Available robot models are\n";
        for ( auto & val: shop.store)
        {
            int i=1;
            print_models(*val,i);
            i++;
        }
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
