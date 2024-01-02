/* include custom headers */
#include"table.h"
/* include standard cpp headers */
#include<iostream> 
using namespace std; 
template<class T > Table<T> :: Table ( string fileName ) throw ( MemoryError ) {
    /* Save file name for future use */
    this -> fileName = fileName ; 
    /* create memory to store all records */
    /* Remember we will store only addresses of records inside this vector */
    /* Actual record can be accessed by dereferencing data found at specific index of vector */
    /* do not forget to free up memory in destructor */
    this->records = new vector<Storable *>();
    if( !this->records ){
        throw MemoryError ();
    }
}

template <class T> long Table <T> :: getNextRecordId () const{
    /* Next recordId is total size of record + 1 */
    return this->records->size() + 1 ;
}
template <class T> const T * const Table <T> :: addNewRecord (T record ) throw (MemoryError ,IOError ) {
    /* We will create new record in memory , 'newRecord' is pointer to the new Record */
    T * newRecord = new T ( record );
    if ( !newRecord ){
        /* Throw an exception */
        throw new MemoryError();
    }
    newRecord->recordId = this->  getNextRecordId();
    /* store address of new record in 'record' vector */
    this->records->push_back ( newRecord );
    /*Write data to a file */
    try {
        this->writeTofile ();
    }
    catch (IOError error ) {
        /* Clean up things */
        this->records->pop_back();
        delete newRecord;
        /*Rethrow exception */
        throw ; 
    }
    /* Return newly created record as const so no one can modify it */
    return newRecord ; 
}
template <class T> void Table<T> :: updateRecord ( T updatedRecord ) throw (IOError , NoSuchRecordError ){
    /* First find the original record index */
    for ( auto & record : *this->records ){
        if( record->getRecordId () == updatedRecord .getRecordId ()){
            /* record is a pointer pointing at some record in heap memory */
            /* we will directly change data to that address */
            /* Now record is pointing at new updated record in memory */
            /* we will keep a backup record so if write fails ,we can restore from backup */
            T * pointerToRecord = dynamic_cast<T*> ( record ) ; 
            if ( pointerToRecord ){
                T oldRecord = T ( *pointerToRecord );
                record->setDataFrom ( &updatedRecord );
                /* Write data to file */
                try {
                    this->writeTofile();
                    return ;
                }
                catch ( IOError error ){
                    /* Clean up things */
                    record->setDataFrom ( &oldRecord );
                    /* Rethrow exception */
                    throw ; 
                }
            }
        }
    }
    throw NoSuchRecordError (); 
}
template <class T> void Table<T> :: writeTofile () throw ( IOError ){
    /* In this method, we will overwrite file with all the data that we have */
    /* so open file with mode 'ios::out | ios :: trunc' */
    this->fileStream.open ( fileName ,ios::out | ios::trunc );
    if ( !this->fileStream ){
        /*throw an exception */
        throw IOError ();
    }
    for ( auto & record : *records ){
        /* Write record to file */
        fileStream << record->toString() << endl ; 
    }
    /* Finally ,close the file */
    this->fileStream.close ();
}
template <class T> const T * const Table<T> :: getRecordForId ( long recordId) const throw ( NoSuchRecordError ){

    try{
        return this->getReferenceofRecordForId ( recordId );
    }
    catch ( NoSuchRecordError error ){
        throw ; 
    }
}
template <class T> T * Table<T> :: getReferenceofRecordForId ( long recordId ) const throw ( NoSuchRecordError ){
    for ( auto & record : *records ){
        if( record->getRecordId() == recordId ){
            return dynamic_cast<T*> ( record );
        }
    }
    /* We are out of the loop hence no record is found */
    throw NoSuchRecordError (); 
}

template <class T> Table<T> :: ~Table ( ) {
    /* Remove any memory which is dynamically created */

    for ( auto & record : *this->records ) {
        /* This is to just delete the in-memory data pointed to by 'record' */
        delete dynamic_cast<T*> ( record );
    }
    /* Now 'this->records' contains address of memory segments which has no data (or corrupted data )*/
    /* So clear all addresses from 'this->records' */

    this->records->clear();
    /*This will reduce memory size taken by vector 'this->records' */
    this->records->shrink_to_fit() ; 
    /* Finally , delete memory pointed to by vector 'this->records' */
    delete this->records; 
}