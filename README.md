Vehicle Rental System is an application built using C++ that helps an operator to maintain records related to users, vehicles, and trips at the vehicle rental office
The functionality provided by this application includes:
Addition of new vehicles,trips and users,Editing vehicle and trip information, Viewing historical data of past trips or the trips scheduled in the future         
This application is built on the concepts of Object-Oriented Programming such as Inheritance, Abstraction, Virtualization, Templates, STL, Polymorphism, I/O operations, among others
A Database class provides abstraction layer for I/O operations. Data is brought from files to the memory and can be accessed through a Generic class Table. 
Table can hold data of type Vehicle, User and Trip. The overload subscript operator [] is used inside the Table class to fetch record at a particular index. Further, exceptions have been added to handle invalid inputs.
While accessing the information,the actual data is never shared; instead, only the constant references of the data are shared. This helps to prevent accidental data corruption.
