#include<string>
using namespace std;
//this is a serilizable class and it is an abstract class
//Any class derived from this class must implement 'toString' method
class Serializable {
    public:
    /* Pure virtual function 
    serializable class does not know what 'toString' method will do 
    It is the responsibility of derived class to implement this method 
    Each derived class has its won 'toString' implementation
    */
   virtual string toString() const = 0 ;
}; 