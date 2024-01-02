#ifndef database_cpp
#define database_cpp 
/* Include custom headers */

#include "database.h"
#include "string_helper.h"

/* Include standard cpp headers */

#include <bits/stdc++.h>
vector<string> spliter( const string & s, char delimiter) {
    vector<string> tokens; 
    string token; 
    istringstream tokenStream (s);
    while( getline ( tokenStream, token , delimiter )){
        tokens.push_back (token);
    }
    return tokens; 
} 
using namespace std; 
const char DELIMETER = ';';
Database :: Database() throw ( IOError , MemoryError ){
    try{

        this->vehicleTable = new Table<Vehicle> ( "vehicle.txt");
        this->userTable = new Table<User> ( "users.txt");
        this->tripTable = new Table<Trip> ("trips.txt");

        /*Fetch data for vehicles */
        this->fetchAllVehicles();
        /*Fetch data for users */
        this->fetchAllUsers();
        /* Fetch data for trips */
        this->fetchAllTrips();
    }catch(...){
        throw; 
    }
}
void Database :: fetchAllVehicles () throw (IOError,MemoryError){
    /* open file for reading */
    this->vehicleTable->fileStream.open ( this->vehicleTable->fileName);
    if(!this->vehicleTable->fileStream ){
        throw IOError();
    }
    /* Read all lines from file*/
    for( string line ; getline ( this->vehicleTable->fileStream,line );){
        /* Split string with given delimiter */
        vector<string> components = spliter( line, DELIMETER );

        /* Get all components from vector */
        auto recordId                     = stol( components[0]);
        auto registrationNumber           = components[1];
        auto type                         = VehicleType ( stoi ( components[2]));
        auto seats                        = stoi (components[3]);
        auto companyName                  = components[4];
        auto pricePerKm                   = stod ( components [5] );
        auto PUCExpirationDate            = Date ( components [6]);

        /* create record and store */  
        Storable * record = new Vehicle ( registrationNumber ,type,seats,companyName,pricePerKm,PUCExpirationDate,recordId);
        if( !record ){
            throw MemoryError();
        }
        this->vehicleTable->records->push_back ( record );
    }
    /* Close file */
    this->vehicleTable->fileStream.close();
}
void Database :: fetchAllUsers () throw ( IOError , MemoryError ) {
    /* Open file for reading */
    this->userTable->fileStream.open (this->userTable->fileName );
    if( !this->userTable->fileStream){
        throw IOError();
    }
    /* Read all lines from file */
    for ( string line ; getline (this->userTable->fileStream,line);){
        /* Split string with given delimiter */
        vector<string> components = spliter( line , DELIMETER );

        /* Get all components from vector */

        auto recordId          = stoi (components[0] ); 
        auto name              = components[1];
        auto contact           = components[2]; 
        auto email             = components[3];
        /* Create record and store */
        Storable * record = new User ( name, contact, email, recordId);
        if( !record){
            throw MemoryError ();
        } 
        this->userTable->records->push_back ( record );
    }
    /* close file */
    this->userTable->fileStream.close();
}

void Database :: fetchAllTrips () throw ( IOError,MemoryError){
    /* open file for reading */
    this->tripTable->fileStream.open ( this->tripTable->fileName );

    if ( !this->tripTable->fileStream ){
        throw IOError ();
    }

    /* Read all lines from file */
    for( string line; getline (this->tripTable->fileStream,line);){
        /* Split string with given delimiter */
        vector<string> components = spliter ( line,DELIMETER );
        /* Get all components from vector */
        try{
            auto recordId        = stoi (components[0] );
            auto vehiclePtr      =this->vehicleTable->getReferenceofRecordForId ( stoi ( components[1] ) );
            auto userPtr         =this->userTable->getReferenceofRecordForId (stoi ( components[2] ) ) ;
            auto startDate       = Date ( components[3] );
            auto endDate         = Date ( components[4] );
            auto startReading    = stol ( components[5] );
            auto endReading      = stol  ( components[6] );
            auto fare            = stod ( components[7] );
            auto isCompleted     = components[8] == "0" ? false : true ;

            /* Create record and Store */

         Storable * record = new Trip ( vehiclePtr, userPtr , startDate, endDate , recordId , startReading ,endReading ,fare ,isCompleted);
         if ( !record ){
            throw MemoryError();
         }    
         this->tripTable->records->push_back ( record );
        } catch(...){
            //just ignore this error 
        }
    }
    /* close file */
    this->tripTable->fileStream.close();
}
const Vehicle * const Database :: getVehicle ( string registrationNo )
const throw ( NoSuchRecordError ){
    for (auto & record : *this->vehicleTable->records ) {
        Vehicle * vehicle = dynamic_cast<Vehicle*> (record);
        if ( vehicle ){
            if ( vehicle->getRegistrationNumber() == registrationNo ){
                return vehicle; 
            }
        }
    }
    throw NoSuchRecordError ();
}

const User * const Database :: getUser (string contactNo ) const throw ( NoSuchRecordError ) {
    for( auto & record : *this->userTable->records ){
        User * user = dynamic_cast<User*> (record );
        if (user){
            if ( user->getContact() == contactNo) {
                return user ; 
            }
        }
    }
    throw NoSuchRecordError() ;
}
const vector<const Vehicle *> Database :: getVehicle ( Date startDate , Date endDate , VehicleType type ) const {

    vector<const Vehicle *> vehicles = vector<const Vehicle * > ();

    for ( auto & vrecord : * this->vehicleTable -> records ){

        Vehicle * vehicle = dynamic_cast<Vehicle*> ( vrecord );

        if ( vehicle && vehicle->getVehicleType() == type) {
            
            /* Check if this vehicle is free between startDate and endDate */
            bool tripFound = false ; 
            for ( auto & trecord : *this->tripTable->records ){
                Trip * trip = dynamic_cast< Trip*> ( trecord );
                if (
                    trip && 
                    !trip->isCompleted() && 
                    trip->getVehicle() .getRecordId() == vehicle->getRecordId() && 
                    !(trip->getStartDate() >= endDate && trip->getEndDate() >= endDate) && 
                    !(trip->getStartDate() <= startDate && trip->getEndDate() <= startDate)
                ){
                    tripFound = true ;
                    break ; 
                }
            }
            if ( !tripFound ) {
                vehicles.push_back ( vehicle );
            }
        }
    }
    return vehicles ; 
}

void Database :: cleanUp (){
    delete this->vehicleTable ; 
    delete this->userTable ; 
    delete this->tripTable ; 

}
Database :: ~Database (){
    this->cleanUp();

}
const Table<Vehicle> * const Database :: getVehicleRef () const {
    return this->vehicleTable; 
}

const Table< User > * const Database :: getUserRef ( ) const {
    return this->userTable;
}

const Table<Trip> * const Database :: getTripRef ( ) const {
    return this->tripTable ;
}
#endif