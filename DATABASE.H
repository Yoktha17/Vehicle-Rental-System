#ifndef database_h 
#define database_h

/* Include custom headers */
#include "vehicle.h"
#include "user.h"
#include "trip.h"
#include "table.cpp"
#include "error.cpp"

using namespace std ; 

/*  
This is a Database class and acts as middleware, so we can hide low-level details like file handling 
  add, update records, etc. 
*/

class Database {
    private: 
    /* Database have multiple tables */
    /* Vehicle table */
    Table<Vehicle> * vehicleTable ;
    /* User table */
    Table<User> *userTable ;
    /* Trip table */
    Table<Trip> * tripTable ; 
    /*
    Fetch all data from files 
    Can throw 'IOError' or 'MemoryError' 
    */
   void fetchAllVehicles() throw (IOError, MemoryError ); 
   void fetchAllUsers () throw ( IOError, MemoryError );
   void fetchAllTrips () throw ( IOError , MemoryError );

   void cleanUp () ;
   public : 
   /* 
   Constructor can throw 'MemoryError' or 'IOError'
   If the system is our of memory , or I/O operator cannot be performed , then this error will be thrown 
   */
  Database() throw (MemoryError, IOError) ;
  ~Database();
  /* Get reference to database tables */
  /* All are constant pointers to constant objects . So, user can neither 
   can change the pointer nor the data */
   const Table<Vehicle> * const getVehicleRef () const; 
   const Table<User> * const getUserRef() const; 
   const Table<Trip> * const getTripRef() const; 
   /* Query vehicle by 'regestrationNo'*/
   const Vehicle * const getVehicle ( string registrationNo ) const throw (NoSuchRecordError) ;

   /* Query user by contact no.*/
   const User *const getUser (string contactNo) const throw (NoSuchRecordError);

   /* Find a vehicle of given type, which is avilable in a given duration */
   const vector<const Vehicle * > getVehicle ( Date startDate, Date endDate , VehicleType type) const;
   
   /* Add new record of type T in database */
template <class T> void addNewRecord ( T * record ) throw (IOError,MemoryError);

/* Update record in data(base */
template <class T> void updateRecord ( T * record ) throw ( IOError,NoSuchRecordError);

};
#endif 