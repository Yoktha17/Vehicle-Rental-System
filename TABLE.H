#ifndef table_h
#define table_h

/* Include custom headers */
#include "storable.cpp "
#include "error.cpp"
/* Include standard cpp headers */

#include<vector>
#include<string> 
#include<fstream> 
using namespace std; 
/*  This is templated (genric) class. It represents in - memory database table. 
Table can be of type 'Vehicle ' , ' User ' , 'Trip'.
*/
template < class T > class Table {
    private: 
    /* Name of database file */
    string fileName;
    /* File stream used to read and write data from database file */
    fstream fileStream ; 
    /*original data is stored here */
    /* 'vector' is a container type and behaves like dynamic array */

    vector<Storable *> * records = NULL ; 
    /*This is a private method */
    /* we will share pointer of record with recordId = 'recordId' */
    /* this is intentional ,hence it is kept as private method */
    T * getReferenceofRecordForId (long recordId) const throw ( NoSuchRecordError );
    /* this is a private function . It is called after inserting new record of updating data */
    /* this function writes data to file */

    void writeTofile () throw ( IOError ) ; 

    /*
    Add new record to database.
    input: fileName of database.
    This method can trhow 'MemoryError' or 'IOError'
    */
   
const T * const addNewRecord ( T data ) throw ( MemoryError, IOError ) ;
/*
Update record in database 
input: new Record of generic type 'T'
this method can throw 'IOError'
*/
void updateRecord ( T updatedRecord ) throw (IOError,NoSuchRecordError) ; // made some correction like wrote updatedRecord and some many errors showed
public :
/*
constructor 
input: fileName of database . 
*/

Table (string fileName ) throw ( MemoryError ); 
~Table (); 
/*
Get 'recordId' for next record 
*/
long getNextRecordId () const ; 

/*
Get record for particular 'recordId'
input: recordId of record 
we will return const T* const (constant pointer to constant record )
so user cannot modify that record accidently.
this method can throw 'NoSuchRecord' Exception 
*/
const T * const getRecordForId ( long recordId ) const throw (NoSuchRecordError );

/* Class database can use this class ' private methods and variables */
/* we will use 'getReferenceRecordForId' to get actual record reference */
  friend class Database ;
};
#endif 