     PROJECT: VEHICLE RENTAL SYSTEM 
Vehilce Rental System is an application built using C++ that helps an operator to maintain records related to users, vehicles and trips at the vehicle rental office. The fuctionality provided by this application includes: 
        1.Addition of new vehicles ,trips and users 
        2.Editing vehicle and trip information 
        3.Viewing historical data of past trips or the trips scheduled in the future 
This application is built on the concepts of Object-Oriented Programming such as Inheritance, Abstraction, Virtualization, Templates, STL, Polymorphism, I/O opertions , among others.
      A Database class provides abstraction layer for I/O opertions . Data is brought  from files to the memory and can be accessed through a Generic class Table. Table can hold data of type Vehicle, User and Trip. The overload subscript opertaor [] is used inside the Table class to fetch record at a particular index. Further, exceptions have been added to handle invalid inputs. 
         While accessing the information, the acutal data is never shared; instead only the constant reference of the data are shared. This helps to prevent accidental data corruption.
Projetct Structure :
The Project code is segregated into several files with each file containing a specific class. The description of the various classes is given below:






[vehicle rental system report.docx](https://github.com/Yoktha17/Vehicle-Rental-System/files/13819745/vehicle.rental.system.report.docx)
