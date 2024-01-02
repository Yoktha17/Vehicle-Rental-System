#ifndef vehicle_h
#define vehicle_h
// include coustom headers 
#include "date.h"
#include "storable.cpp"
// include standard cpp headers 
#include <string>
using namespace std;
/*
support for different types of vehicles for different purposes 
*/
typedef enum { bike = 1 , car = 2 , towera =3 } VehicleType; 
/* vehicle class which helps to manage vehicle-related data */
class Vehicle : public Storable {
    private : 
    // registration number given by RTO
    string registrationNumber;
    // Type of vehicle given by 'VehicleType' enum
    VehicleType type;
    //no of seats this vehicle has 
    int seats ;
    // Name of the vehicle manufaccturer
    string companyName ;
    /*Each vehicle has different price per km */
    /* This will be required to calculate fare when trip ends */
    double pricePerKm;
    // this is the date when PUC will expire 
    Date PUCExpirationDate ;

public : 
/*
constructor 
input:Registration no of vehicle 
input:Vehicle type 
input:No.of seats 
input:Company name 
input:price per km 
input:PUC Expiration date 
input:recordId (defaults to 0)
*/    

Vehicle( string registrationNumber , VehicleType type , int seats , string companyName, double pricePerKm, Date PUCExpirationDate,long recordId = 0);
/*
Getter methods with const attribute i.e. This method is not changing any data of the current object.
if this method is not marked as constant, then it cannot be called 
from constant object of this class .

Following snippet will give an error if 'getRegistrationNumber' is not marked with const keyword . 

const Vehicle * object = new Vehicle (...);
auto registrationNo = object->getRegistrationNumber();
*/
string getRegistrationNumber () const;
VehicleType getVehicleType () const; 
string getVehicleTypeName () const ; 
int getSeats () const;
string getCompanyName () const; 
double getPricePerKm () const; 
Date getPUCExpirationDate () const ; 
/* 
Function which sets new price of the vehicle 
input: New price of vehicle 
*/
void setPricePerKm ( double newPrice );
// display record on screen 
void display () const ;
// overridden virtual method 

string toString () const; 
void setDataFrom ( Storable * s);

};
#endif 