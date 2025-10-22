
#include "UI.h"

#include <cstring>
UI::UI() {
    this->controller=Controller();
    this->startUpData();
}

void UI::showSensorType() {
    string type;
    cout<<"Enter the sensor type you want to search"<<endl;
    cin>>type;

    this->controller.showSensorType(type);
}

void UI::printMenu() {
    cout<<"Menu:"<<endl;
    cout<<"1. Add weather station"<<endl;
    cout<<"2. Show weather locations"<<endl;
    cout<<"3. Show how many weather stations in each location have a sensor type"<<endl;
    cout<<"0. Exit"<<endl;
}
void UI::addWeather() {
    cout<<"Adding weather location"<<endl;

    string location,name,list_sensors;
    cout<<"Please enter the location:"<<endl;
    cin>>location;

    cout<<"Please enter the name:"<<endl;
    cin>>name;

    cout<<"Please enter the list of sensors:"<<endl;
    cin>>list_sensors;

    try {
        this->controller.addWeather(location,name,list_sensors);
        cout<<"Weather added successfully"<<endl;
    }
    catch (...) {
        cout<<"The weather location must be unique."<<endl;
    }
}
void UI::showWeather() {
    DynamicVector<Weather> array=this->controller.getWeatherController();
    for (int i=0;i<array.getSizeOfDynamicVector();i++)
        cout<<array[i].getLocation()<<" | "<<array[i].getName()<<" | "<<array[i].getListSensors()<<endl;
}
void UI::run() {
    while (true) {
        this->printMenu();
        int option;
        cin>>option;
        if (option==1) {
            addWeather();
        }
        else if (option==2) {
            showWeather();
        }
        else if (option==3) {
            showSensorType();
        }
        else if (option==0) {
            break;
        }
        else
            cout<<"Invalid option"<<endl;
    }
}

void UI::startUpData() {
    this->controller.addWeather("New York","Central Park", "Thermometer, Barometer");
    this->controller.addWeather("New York", "JFK Airport","Thermometer, Anemometer, Wind Vane");
    this->controller.addWeather("London","Heathrow Airport", "Thermometer, Anemometer, Wind Vane , Hygrometer");
    this->controller.addWeather("Cluj", "Cetatuie","Thermometer, Barometer");
}




