# Student-Database-Management-System-using-C++
A simple **Student Database Management System** developed using **C++**. The project uses file handling to store and manage student records through a menu-driven console interface.

## Features

* Add new student records
* Display all student records
* Search for a student using Roll Number
* Modify existing student details
* Delete a student record
* Validate student email ID
* Validate Roll Number
* Validate 10-digit contact number
* Store records permanently in a text file

The main menu provides options to enter, display, modify, search, and delete student records.

## Student Information

The following details are stored for each student:

* Name
* Roll Number
* Course
* Email ID
* Contact Number
* Address

These details are written to `studentRecord.txt` using `|||` as the field delimiter.

## Technologies Used

* **C++**
* **Object-Oriented Programming**
* **File Handling**
* **Input Validation**

## Validation

The system performs basic validation before accepting student information:

* **Email:** Checks for a valid `@` and `.` placement.
* **Roll Number:** Allows 3–20 characters containing letters and numbers.
* **Contact Number:** Accepts a 10-digit number.

## File Structure

```text
Student-Database-Management-System/
│
├── student_database.cpp
├── studentRecord.txt
├── tempRecord.txt
└── README.md
```

`studentRecord.txt` is used to store student records, while `tempRecord.txt` is used temporarily when modifying or deleting records.

## How to Run

1. Make sure a C++ compiler is installed.
2. Open the project in a C++ IDE or VS Code.
3. Compile the source file.
4. Run the generated executable.
5. Select an option from the menu.

## Menu Options

```text
1. Enter New Record
2. Display Record
3. Modify Record
4. Search Record
5. Delete Record
6. Exit
```

## Project Purpose

This project demonstrates the practical use of **classes, functions, file handling, input validation, and basic CRUD operations** in C++. It is suitable as a beginner-level project for learning how student records can be managed using a console-based application.

##Author
Rhea Cathrine Chella
