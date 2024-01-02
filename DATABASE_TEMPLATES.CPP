/* Include custom headers */

#include "database.h"

template <class T> void Database :: addNewRecord ( T * record ) throw ( IOError ,MemoryError ){
    
    try {

        Vehicle * v = dynamic_cast<Vehicle *> ( record );
        if ( v ){
            auto savedRecord = this->vehicleTable->addNewRecord ( *v );
            record->recordId = savedRecord ->recordId; 
            return ; 
        }
        User * u = dynamic_cast<User *> (record);
        if( u ){
            auto savedRecord = this->userTable->addNewRecord (*u);
            record->recordId = savedRecord->recordId; 
            return; 
        }

        Trip * t = dynamic_cast<Trip *> ( record ); 
        if ( t ) {
            auto savedRecord = this->tripTable->addNewRecord ( *t );
            record->recordId = savedRecord ->recordId; 
            return; 
        }
    }
    catch(...){
        throw ; 
    }
}

template < class T > void Database :: updateRecord ( T * record ) throw ( IOError , NoSuchRecordError){

    try {
        
        Vehicle * v = dynamic_cast<Vehicle *> ( record );
        if ( v ){
            
            this->vehicleTable->updateRecord ( *v );
            return ; 
        }
        User * u = dynamic_cast<User *> ( record ); 
        if ( u ){
            this->userTable->updateRecord ( *u );
            return ; 
        }
        Trip * t = dynamic_cast<Trip *> (record);
        if(t){
            this->tripTable->updateRecord ( *t );
            return ; 
        }
    }
    catch(...){
        throw ; 
    }
}