#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>
#include <fstream>
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Shared_Image.H>
#include <FL/Fl_JPEG_Image.H>
#include <FL/fl_ask.H>

using namespace std;

class Robot_part
{
public:
    Robot_part(){};
    Robot_part(string robot_name,int robot_modelno, double price, string desc, string what_part):name(robot_name),model_number(robot_modelno),cost(price),description(desc), type(what_part){}
    friend void print_parts (Robot_part, int i);
    string type;
    double cost;
protected:
    //double cost;
    string name;
    int model_number;
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
    Robot_models (string Name, int modelN, Robot_part *Hd, Robot_part *T, Robot_part *l, Robot_part *a, Robot_part *bat, double m_cost):name(Name),model_number(modelN), head(Hd), torso(T), locomotor(l), arm(a), battery(bat), cost(m_cost){}
    friend void print_models(Robot_models model, int i);
    double cost;
    double max_speed();
    double max_battery_life();
};
void print_models(Robot_models model, int i)
{
    cout<<"\n"<<i<<". Name: "<<model.name<<"\tModel number: "<<model.model_number<<"\tCost: $"<<model.cost;
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

class SA
{
    string name;
    int employee_number;
public:
    void fillSA(string SA_name, int SA_no)
    {
        name=SA_name;
        employee_number=SA_no;
    }
};


class Customer
{
    string name;
    int customer_number;
    string email;
    string phone;
public:
    Customer(string Name,int customer_no, string Email, string Phone):name(Name),customer_number(customer_no),email(Email), phone(Phone){}

};

class Order
{

    int order_number;
    int day;
    int month;
    int choice;
    int quantity;
    double total_price;
public:
    Order(int ch, int q, int order_no,int d,int m,double cost):choice (ch), quantity(q), order_number(order_no), day(d), month(m), total_price(cost){}
};



class Shop
{
public:
    vector <Order*> order;
    vector <Customer*> customer;
    vector <Robot_models*> store;
    vector <Robot_part*> store_head;
    vector <Robot_part*> store_locomotor;
    vector <Robot_part*> store_torso;
    vector <Robot_part*> store_battery;
    vector <Robot_part*> store_arm;
    void create_new_robot_part(string robo_name,int model_no,double price,string description, double max_power,int compartment,int max_arms,double energy,double power_available,int choice);
    void create_new_robot_model(string model_name,int model_number,Robot_part *head, Robot_part *locomotor, Robot_part *torso, Robot_part *battery, Robot_part *arm, double cost);
    void create_new_beloved_customer(string name,int cust_no, string email, string phone);
    void create_new_order(int choice, int quantity, int order_no, int d, int m, double cost);
};
void Shop::create_new_robot_part(string robo_name,int model_no,double price, string description, double max_power, int compartment, int max_arms, double energy, double power_available, int choice)
{

    if (choice ==1)
        store_head.push_back(new Head{robo_name,model_no,price,description,max_power,"Head"});
    else if (choice ==2)
        store_locomotor.push_back(new Locomotor{robo_name,model_no,price,description,max_power,"Locomotor"});
    else if (choice ==3)
        store_torso.push_back(new Torso{robo_name,model_no,price,description,compartment,max_arms,"Torso"});
    else if (choice ==4)
        store_battery.push_back(new Battery{robo_name,model_no,price,description, power_available, energy, "Battery"});
    else if (choice ==5)
        store_arm.push_back(new Arm{robo_name,model_no,price,description, max_power,"Arm"});
}
void Shop::create_new_robot_model(string model_name,int number,Robot_part *head, Robot_part *locomotor, Robot_part *torso, Robot_part *battery, Robot_part *arm, double cost)
{
    store.push_back(new Robot_models{model_name, number, head, torso, locomotor, arm, battery, cost});
}
void Shop::create_new_beloved_customer(string name,int cust_no, string email, string phone)
{
    customer.push_back(new Customer{name,cust_no,email,phone});
}
void Shop::create_new_order(int choice, int quantity, int order_number, int d, int m, double cost)
{
    order.push_back(new Order{choice, quantity, order_number, d, m, cost});
}



class View
{
public:
    View(Shop& sp):shop(sp){}
    string menu();
    string PD_menu();
    string BC_menu();
    string SA_menu();
private:
    Shop& shop;
};
string View::menu()
{
    string menu = "\n--Menu--\n1. Product Manger\n2. Beloved Customer\n3. Sales Associate\n4. Exit\n";
    return menu;
}
string View::PD_menu()
{
    string menu = "\n--Menu--\n1. Create a new robot part\n2. Create a new robot model\n3. View robot models\n4. Logout\n";
    return menu;
}
string View::BC_menu()
{
    string menu = "\n1. New Customer\n2. View available robot model\n3. Logout\n";
    return menu;
}
string View::SA_menu()
{
    string menu = "\n1. Create an order\n2. Logout\n";
    return menu;
}

class Controller
{
public:
    Controller (Shop& sp, View& view):shop (sp), view (view) {}
    void cli();
    void execute_cmd(int cmd, int choice, int ch);
private:
    Shop& shop;
    View& view;
 	int get_int(string title, string prompt, int max_int);
    string get_string(string title, string prompt);
};

int Controller::get_int(string title, string prompt, int max_int) {


  string error = "Please enter an integer between 0 and " + max_int;
  int result;
  while(true) {
    fl_message_title(title.c_str());
    fl_message_icon()->label("I");
    result = atoi(fl_input(prompt.c_str(), 0));
    if (0 <= result && result <= max_int) break;
    fl_message_title("Invalid input");
    fl_message_icon()->label("!");
    fl_message(error.c_str());
  }
  return result;
}

string Controller::get_string(string title, string prompt) {
  fl_message_title(title.c_str());
  fl_message_icon()->label("S");
  string result{fl_input(prompt.c_str(), 0)};
  return result;
}

/*void Controller::cli()
{
    int choice = -1;
    while(choice!=4)
    {   int cmd=-1, choice=-1;
        cout<<view.menu();
        cout<<"Command? ";
        cin>>choice;
        if (choice==1)
        {
            while (cmd!=4)
            {
                cout<<view.PD_menu();
                cin>>cmd;
                execute_cmd(cmd,choice);
            }

        }
        else if(choice == 2)
        {
            while (cmd!=3)
            {
                cout<<view.BC_menu();
                cin>>cmd;
                execute_cmd(cmd,choice);
            }

        }
        else if (choice == 3)
        {
            while (cmd!=2)
            {
                cout<<view.SA_menu();
                cin>>cmd;
                execute_cmd(cmd,choice);
            }

        }
        else if (choice == 4)
        {
            exit(0);
        }
        else cout<<"Wrong option";
}
}*/
void Controller::execute_cmd(int cmd,int ch, int choice)
{
    string robo_name, desc, model_name, customer_name, customer_email, customer_phone;
    int model_no, compartment=0, max_arms=2, model_number, head_select, torso_select, locomotor_select, battery_select, arm_select, customer_number, model_choice, order_no, month ,day, quantity;
    double cost, energy=0, max_power, power_available, least_model_cost=0, model_cost, order_cost;
    if (ch == 1)
    {
        if (cmd==1)
        {

		robo_name = get_string("Publication Title", "Part name? ");

		model_no = get_int(robo_name, "Part number?",10000);

    		cost = get_int(robo_name, "Cost?",10000);


    		desc = get_string(robo_name, "Description? ");
		

                /*bool ans_part;
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
                cout<<"Enter the description - ";
                cin.ignore();
                getline(std::cin,desc);*/
                if ((choice==2)||(choice==5)||(choice==1))
                {
 	    		max_power = get_int(robo_name, "Maximum Power?",10000);
                }
                else if (choice==3)
                {
                    bool ans_compartment;
                    do{
                        ans_compartment=true;
                            compartment = get_int(robo_name, "Number of compartments?",4);
                        if ((compartment<1)||(compartment>3))
                        {
			    string error = "The number of compartments should be between 1 & 3!";
                            fl_message(error.c_str());
                            ans_compartment = false;
                        }

                    }while(ans_compartment!=true);
                  max_arms = get_int(robo_name, "Maximum number of arms?",3);
                }
                else if (choice==4)
                {
                    energy = get_int(robo_name, "Energy the battery contains?",10000);
                    power_available = get_int(robo_name, "Power available",10000);
                }
                shop.create_new_robot_part(robo_name, model_no, cost, desc, max_power, compartment, max_arms, energy, power_available, choice);
        }
        else if (cmd==2)
        {
            cin.ignore();
            cout<<"Enter the model name: ";
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
                least_model_cost+=(shop.store_head[head_select-1])->cost;
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
                least_model_cost+=(shop.store_locomotor[locomotor_select-1])->cost;

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
                least_model_cost+=(shop.store_torso[torso_select-1])->cost;

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
                least_model_cost+=(shop.store_battery[battery_select-1])->cost;

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
                least_model_cost+=(shop.store_arm[arm_select-1])->cost;

            }
            cout<<"The cost of all the parts to make this particular robot model is: $"<<least_model_cost;
            cout<<"\nEnter the cost of the robot (considering profit)\n$ ";
            cin>>model_cost;
            Robot_part *h=0, *l=0,*t=0, *b=0, *a=0;
            if (!shop.store_head.empty()){
                h =(shop.store_head[head_select-1]);}
            if (!shop.store_locomotor.empty())
                l =(shop.store_locomotor[locomotor_select-1]);
            if (!shop.store_torso.empty())
                t =(shop.store_torso[torso_select-1]);
            if (!shop.store_battery.empty())
                b =(shop.store_battery[battery_select-1]);
            if (!shop.store_arm.empty())
                a =(shop.store_arm[arm_select-1]);
            shop.create_new_robot_model(model_name,model_number,h,l,t,b,a,model_cost);
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
    }
    else if(ch == 2)
    {
        if (cmd==1)
        {
            cin.ignore();
            static int customer_number = 0;
            cout<<"Customer name: ";
            getline(cin,customer_name);
            cout<<"\nPhone number: ";
            getline(cin,customer_phone);
            cout<<"\nEmail: ";
            getline(cin,customer_email);
            customer_number++;
            cout<<"Your customer number is: "<<customer_number;
            shop.create_new_beloved_customer(customer_name,customer_number,customer_email,customer_phone);
            //Order order;
            //order.sales.create_new_order(customer_name,customer_number,customer_email,customer_phone);
        }
        if (cmd==2)
        {
            if (!shop.store.empty())
            {
                cout<<"\nThe available robot models are\n";
                for ( auto & val: shop.store)
                {
                    int i=1;
                    print_models(*val,i);
                    i++;
                }
            }
            else cout<<"\nNo robot models in stock at this moment! Please check back at a later time\n";

        }
    }
    else if(ch==3)
    {
        if (cmd==1)
        {
            month = 0; day=0;
            for ( auto & val: shop.store)
            {
                int i=1;
                print_models(*val,i);
                i++;
            }
            if (!shop.store.empty())
            {   cout<<"\nWhich robot model has been requested?";
                cin>>model_choice;
                cout<<"\nQuantity: ";
                cin>>quantity;
                cout<<"\nOrder number: ";
                cin>>order_no;
                do
                {
                    cout<<"\nEnter the date:\n\tMonth: ";
                    cin>>month;
                    if (month >12||month<=0)
                        cout<<"Enter the correct value of month!";
                }while(month>12||month<=0);
                do
                {
                    cout<<"\n\tDay: ";
                    cin>>day;
                    if(day>30||day<=0)
                        cout<<"Enter the correct value of day!";
                }while(day>30||day<=0);
                order_cost = (shop.store[model_choice-1]->cost)*quantity;
                shop.create_new_order(model_choice,quantity,order_no,day,month,order_cost);

            }
            else cout<<"\n***No robot models in stock !***\n";

        }
    }
}


Fl_Window *win;
//Fl_Box *box;
//Fl_Box *box1;
Fl_Menu_Bar *menubar;
const int X = 500;
const int Y = 400;
	Shop sp;
    View view(sp);
    Controller controller (sp,view);

void Close (Fl_Widget* w, void* p) {
int selection =1;
selection = fl_choice("Are you sure you want to quit?", fl_no, fl_yes, 0);
if (selection ==1) {
win ->hide();
}
}

void create_part (Fl_Widget* w, void* p)
{string which_part = "Which part?\n1. Head\n2. Locomotor\n3. Torso\n4. Battery\n5. Arm\n";
   int choice = atoi(fl_input(which_part.c_str(), 0));
controller.execute_cmd(1,1,choice);}

Fl_Menu_Item menuitems[] = {
    {"&Create new Part", FL_ALT + 'h', (Fl_Callback*)create_part},
    {"&Quit", FL_ALT + 'h', (Fl_Callback*)Close},
      { 0 },};


int main()
{

    win = new Fl_Window{X, Y, "Robot Market"};
    win->color(FL_WHITE);
    win->resizable(*win);
    //box = new Fl_Box{0,0,X,Y,l.c_str()};
    menubar = new Fl_Menu_Bar(0, 0, X, 30);
    menubar->menu(menuitems);
    win->end();
    win->show();

    Shop sp;
    View view(sp);
    //Controller controller (sp,view);
    //controller.cli();
    return (Fl::run());
}
