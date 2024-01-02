#ifndef Date_h
#define Date_h
// include custom headers 
#include "storable.cpp"
// include standard cpp headers 
#include <ctime>
#include <string>
using namespace std;
typedef struct Date : Serializable {
    private :
    /*
    Structure holding date & time info 
    */
   struct tm date;
   bool empty;
   public:
   /* Constructor, create date from string*/
   Date ( string date );
   /*
   create date from current time 
   */
  Date( );
/*Add given number of dates in this date*/
Date operator + (int days);
// if this date is greater than the given date 
bool operator > (Date date ) const ; 
// if this date is greater than or equal to given date 
bool operator >= (Date date ) const ;
// if this date is less than give date 
bool operator < (Date date ) const; 
// if this date is less than or equal to given date 
bool operator <= (Date date )const;
bool isEmpty () const;
string toString () const;

} Date;
#endif 