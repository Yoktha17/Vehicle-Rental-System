#ifndef user_h
#define user_h
// include custom headers 
#include "storable.cpp"
// include standard cpp headers 
#include<string>
using namespace std; 
//user class which helps in managing user-releated data
class User : public Storable {
    private :
    // name of user 
    string name;
    // contact number of user 
    string contact ;
    // email id of user 
    string email;
    public : 
    /*
    constructor 
    input: Name of user 
    input: Contact number of user 
    input: Email Id of user 
    input: recordId(defaults to 0)
    */
User( string name, string contact, string email, long recordId =0 );
/*
Getter methods with const attribute i.e. this method is not changing any data of the current object
If this method is not marked as constant, then it cannot be called from constant object of this class 
the following snippet will give an error if 'getName' is not marked with const keyword.
const user * object = new user (....);
auto name = object->getName();
*/
string getName () const ;
string getContact () const ;
string getEmail () const; 
/*
Set name of user 
input: New name of user 
*/
void setName (string newName );
/*
set contact number of user 
input: new contact number of user 
*/
void setContact ( string newContact );
/*
set email-id of user 
input:New email-id of user 
*/
void setEmail ( string newEmail );
/*
Display record on screen 
*/

void display ( ) const ;
/*overridden virtual method */
string toString () const; 
void setDataFrom(Storable * s);

};
#endif