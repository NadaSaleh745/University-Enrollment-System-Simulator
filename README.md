# University Course Management System

## Table of Contents
- [Description](#description)
- [Features](#features)
- [Technologies Used](#technologies-used)
- [Project Structure](#project-structure)
- [User Guide](#user-guide)
- [Error Handling](#error-handling)
- [Support](#support)  


## Description
This is a simple C++ console application that simulates a basic university course management system. It allows students to enroll in courses, drop courses, view their enrolled courses and credit hours, while faculty members can add new students, add new courses, and view student/course information.

## Features

### Student Functionalities:
- Enroll in courses
- Drop enrolled courses
- View total enrolled credit hours
- Display enrolled courses

### Faculty Functionalities:
- Add new courses
- Add new students
- Display all students
- Display all courses
- View specific student details

## Technologies Used
- **C++**
- **Standard Template Library (STL):** `vector`, `unordered_map`, `algorithm`

## Project Structure

### Classes:
- **Student:** Manages student information, enrolled courses, and credit hours.
- **Course:** Handles course details, enrolled students, and credit hours.
- **University:** Manages all students and courses, providing core functionality for enrollment and data display.


## User Guide
When you run the program, you'll be prompted to choose between:

- **Student:** Allows you to log in with your student ID to enroll/drop courses and view details.
- **Faculty Member:** Provides options to add students/courses, and view information.
- **Exit:** Closes the program.


## Error Handling
- **Input Validation:** Handles invalid entries to prevent errors.
- **Duplicate Enrollment Check:** Ensures students can't enroll in the same course twice.
- **Course Capacity Validation:** Checks for maximum course capacity during enrollment.

## Support  
If you found this project useful, feel free to give it a ⭐ star! ⭐  
