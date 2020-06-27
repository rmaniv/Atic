# Atic
## About the System and the Interface

This is an airline ticketing system for the administrator of the airline and the passenger. The administrator can use the &#39;Admin&#39; menu option to add, view, delete, modify flights. The passenger, who is the &#39;User&#39; in this program, can use the &#39;User&#39; menu option to reserve, cancel and use the &#39;Reports&#39; menu option to view his/her details and status. A &#39;Help&#39; menu has also been provided to introduce the program and navigation to the user.

Functions under the &#39;Admin&#39; menu option:

1. &#39;Add Flight&#39; AddFlight() : The admin can enter the flight number, name, source, destination, date and fare to add a flight.
2. &#39;Display&#39; Display() : The admin can use this to view the details of all flights.
3. &#39;Delete&#39; Delete() : The admin can use this to delete any flight by entering the flight number.
4. &#39;Modify&#39; Edit() : The admin can use this function to modify the date, time and fare of any flight.

Functions under the &#39;User&#39; menu option:

1. &#39;Reserve&#39; reserve() : The user can enter the source, destination and date of the flight he/she wants to book. A list of options will be displayed in ascending order of price (using the SortPrice() function). He/she has to enter the number of the flight, his name, gender, contact number and address to book the flight. After entering these details, the flight will be booked and a message with the user&#39;s PNR number will be displayed. The user has to remember/note the number as it will be required for future operations, including cancellation of flight, viewing details and status of the flight.
2. &#39;Cancel&#39; cancel() : The user can enter his/her PNR number and the flight will be cancelled. A message, informing the user about the status of cancellation will be displayed.

Functions under &#39;Reports&#39; menu option:

1. &#39;Details&#39; details(): The user can enter his/her PNR number to view his/her details. He/she has to then press ENTER to view the details of the flight booked through that PNR number.
2. &#39;Status&#39; status(): The user can enter his/her PNR number to view the status of his/her booking. Status of a reserved flight will be displayed as &quot;booked&quot; and status of non-reserved/cancelled flight will be displayed as &quot;not booked&quot;.

## About the Program

The program follows the concept of Object-Oriented Programming through the use of Classes and Objects to create a class to define the properties of a flight. In addition, Structures have also been used to group different types of data.

The program a structure Passgnr and a class Flight:

1. The structure Passgnr is used for representing a passenger&#39;s details such as his name, gender, contact number, address, PNR and Flight Number.
2. The class Flight is used for representing the details of each flight registered on the system by the administrator.

The concept of File Handling through the use of binary files, is incorporated to create and maintain a record of the flights registered on the system and the details of the passengers.

1. All the flights are stored in a binary file, _Flight.DAT_, in the form of objects of the class which are appended, to maintain records of previously added flights as well.
2. The Flights which have been deleted by the administrator are stored in a binary file, _Trashcan.DAT_.
3. The passenger details are stored in the file _Res.DAT_.
4. The passenger details of cancelled reservations are stored in Cancel.DAT.

## Setup

The program was written in and run on Turbo C++. Changes are required to make it run on GCC compilers.
