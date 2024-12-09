#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

class University;

class Student {
    string name;
    int ID;
    int enrolledHours = 0;
    vector<int> enrolledCourses;

public:
    Student() {
        ID = 0;
        name = " ";
    }
    Student(int id, string Name) {
        name = Name;
        ID = id;
    }

    int getID() {
        return ID;
    }
    string getName() {
        return name;
    }
    vector<int>& getEnrolledCourses() {
        return enrolledCourses;
    }
    int getEnrolledHours() {
        return enrolledHours;
    }
    void setEnrolledCourses(int courseID) {
        enrolledCourses.push_back(courseID);
    }
    void setEnrolledHours(int hours) {
        enrolledHours += hours;
    }
    void removeEnrolledHours(int hours) {
        enrolledHours -= hours;
    }

    void displayStudentData(University& university);
    void displayStudentCourses(University& university);

};

class Course {
    int ID;
    string name;
    int maxStudents;
    vector<int> enrolledStudents;
    int creditHours;

public:
    Course() {
        ID = 0;
        name = " ";
        maxStudents = 0;
        creditHours = 0;
    }
    Course(int id, string Name, int MaxStudents, int CreditHours) {
        ID = id;
        name = Name;
        maxStudents =  MaxStudents;
        creditHours = CreditHours;
    }
    void enrollStudent(int& studentID, University& university);
    void dropStudent(int& studentID, University& university);

    int getID() {
        return ID;
    }

    string getName() {
        return name;
    }

    int getCreditHours() {
        return creditHours;
    }

    int getMaxStudents() {
        return maxStudents;
    }

    void setEnrolledStudents(int studentID) {
        enrolledStudents.push_back(studentID);
    }

    vector<int>& getEnrolledStudents() {
        return enrolledStudents;
    }

};

class University {
    unordered_map<int, Student> students;
    unordered_map<int, Course> courses;
    int studentIDCounter = 1;

public:
    unordered_map<int, Student>& getUniStudents() {
        return students;
    }

    unordered_map<int, Course>& getUniCourses() {
        return courses;
    }

    void addStudent(string Name) {
        int newStudentID = studentIDCounter++;
        students[newStudentID] = Student(newStudentID, Name);   //In the map at the newStudentID key, create a student
                                                                  //object with the new ID and the Name
        cout << "Student " << Name << " added with ID " << newStudentID << endl;
    }

    bool addCourse(int id, string name = "", int maxStudents = 0, int creditHours = 0) {
        if (courses.find(id) != courses.end()) {    //if the course already exists, return false
            return false;
        }
        else if (!name.empty()) {   //if the course doesn't exist and name is set to a value, then add the course
            courses[id] = Course(id, name, maxStudents, creditHours);
            return true;
        }
        return true;
    }

    Student& getStudent(int studentID) {
        auto studentIter = students.find(studentID);
        return studentIter->second;
    }

    Course& getCourse(int courseID) {
        auto courseIter = courses.find(courseID);
        return courseIter->second;
    }

    void enrollStudentInCourse(int studentID, int courseID) {
        auto studentIter = students.find(studentID);
        auto courseIter = courses.find(courseID);

        if (studentIter == students.end()) {
            cout << "Student not found!" << endl;
            return;
        }

        if (courseIter == courses.end()) {
            cout << "Course not found!" << endl;
            return;
        }

        for (int enrolledStudentID : courseIter->second.getEnrolledStudents()) {
            if (enrolledStudentID == studentID) {   //checks if the student is already enrolled
                cout << "Student already enrolled in this course." << endl;
                return;
            }
        }
        courseIter->second.enrollStudent(studentID, *this);
    }

    void displayAllStudents() {
        for(auto& student : students) {
            cout << student.second.getID() << "   " << student.second.getName() << endl;
        }
    }
    void displayAllCourses() {
        for(auto& course : courses) {
            cout << course.second.getID() << "   " << course.second.getName() << endl;
        }
    }

    void displayStudentData(int studentID) {
        Student& student = getStudent(studentID);
        auto studentCourses = student.getEnrolledCourses();
        cout << "Student ID - Name: " << student.getID() << " - " << student.getName() << endl;
        cout << "Enrolled courses: " << endl;
        for(int course : studentCourses) {
            auto courseName  = getCourse(course).getName();
            cout << course << " - " << courseName << '\n';
        }
        cout << "Total enrolled hours: " <<  student.getEnrolledHours();
    }

};

void Course::enrollStudent(int& studentID, University& university) {    //the university parameter so we can get an
                                                                        //instance of the student object and update their data
    int enrolls = enrolledStudents.size();
    if (enrolls >= maxStudents) {
        cout << "Course has reached maximum capacity" << endl;
        return;
    }
    else{
        Student& student = university.getStudent(studentID); //getting an instance of Student
        student.setEnrolledCourses(ID);
        student.setEnrolledHours(creditHours);
        setEnrolledStudents(ID);
        cout << "Student " << student.getName() << " with ID " << student.getID() << " enrolled in course " << name << endl;
    }
}

void Course::dropStudent(int& studentID, University& university) {
    auto studentIter = university.getUniStudents().find(studentID);
    if(studentIter == university.getUniStudents().end()) {
        cout << "Student not found in university" << endl;
    }
    auto& student = studentIter->second;
    auto it = find(enrolledStudents.begin(), enrolledStudents.end(), studentID);

    if(it != enrolledStudents.end()) {  //if the student is in enrolledStudents, delete the student from enrolled students
        enrolledStudents.erase(it);
    }
    else {
        cout << "Student not enrolled in this course" << endl;
        return;
    }
    auto& studentCourses = student.getEnrolledCourses();
    //get the course from the vector and delete it
    auto courseIt = find(studentCourses.begin(), studentCourses.end(), this->ID);
    if (courseIt != studentCourses.end()) {
        studentCourses.erase(courseIt);  // erase the course by iterator
    }
    student.removeEnrolledHours(creditHours);
    cout << "Student " << student.getName() << " dropped " << this->getName() << " successfully" << endl;
}


void Student::displayStudentData(University& university) {
    cout << "Student ID - Name: " << ID << " - " << name << endl;
    cout << "Enrolled courses: " << endl;
    for(int course : enrolledCourses) {
        auto courseName  = university.getCourse(course).getName();
        cout << course << " - " << courseName << '\n';
    }
    cout << "Total enrolled hours: " <<  enrolledHours;
}

void Student::displayStudentCourses(University& university) {
    for(int course : enrolledCourses) {
        auto courseName  = university.getCourse(course).getName();
        cout << course << " - " << courseName << '\n';
    }
}


bool clearInvalidInput() {  //a function to handle invalid inputs
    if (cin.fail()) {
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cout << "Invalid input. Please try again.\n";
        return true;
    }
    return false;
}

int main()
{
    University university;

    university.addStudent("Nada");
    university.addStudent("Sara");
    university.addStudent("Ahmed");
    university.addStudent("ALi");
    university.addStudent("Noor");

    university.addCourse(101, "OOP", 700, 3);
    university.addCourse(102, "Math", 3, 3);
    university.addCourse(103, "Operation Research", 500, 2);
    university.addCourse(104, "Logic Design", 600, 3);
    university.addCourse(105, "Software Engineering", 25, 2);
    university.addCourse(106, "Data Structure", 700, 3);

    university.enrollStudentInCourse(1, 102);
    university.enrollStudentInCourse(2, 102);
    university.enrollStudentInCourse(3, 102);
    university.enrollStudentInCourse(1, 103);
    university.enrollStudentInCourse(1, 104);




    cout << "**********************************\n";
    cout << "Welcome to Tanta University!!\n";
    cout << "**********************************\n";

    int role;


    do {
        cout << "Are you\n";
        cout << "1. a student?\n";
        cout << "2. a faculty member?\n";
        cout << "3. Exit\n";
        cin >> role;

        if (cin.fail()) {
            clearInvalidInput();
            continue;
        }

        switch(role) {
            case 1: {
                int choice;
                int studentID;
                cout << "Enter your ID: ";
                cin >> studentID;
                if (cin.fail()) {
                    clearInvalidInput();
                    continue;
                }
                auto ID = university.getUniStudents().find(studentID);
                if(ID == university.getUniStudents().end()) {
                    cout << "No student with this ID";
                    return -1;
                }
                else {
                    cout << "Welcome, " << university.getStudent(studentID).getName() << endl;
                    do{
                        cout << "\n1. Enroll in a course\n";
                        cout << "2. Drop a course\n";
                        cout << "3. Show enrolled hours\n";
                        cout << "4. Show enrolled courses\n";
                        cout << "5. Exit\n";
                        cin >> choice;

                        if (cin.fail()) {
                            clearInvalidInput();
                            continue;
                        }

                        switch (choice) {
                            case 1: {
                                int courseID;
                                cout << "Enter course ID: ";
                                cin >> courseID;
                                if (cin.fail()) {
                                    clearInvalidInput();
                                    continue;
                                }
                                auto courseIter = university.getUniCourses().find(courseID);

                                if (courseIter == university.getUniCourses().end()) {
                                    cout << "Course not found!" << endl;
                                } else {
                                    university.enrollStudentInCourse(studentID, courseID);
                                }
                                break;
                            }

                            case 2: {
                                int courseID;
                                cout << "Enter course ID: ";
                                cin >> courseID;
                                if (cin.fail()) {
                                    clearInvalidInput();
                                    continue;
                                }
                                auto courseIter = university.getUniCourses().find(courseID);

                                if (courseIter == university.getUniCourses().end()) {
                                    cout << "Course not found!" << endl;
                                } else {
                                    university.getCourse(courseID).dropStudent(studentID, university);
                                }
                                break;
                            }

                            case 3: {
                                cout << university.getStudent(studentID).getEnrolledHours();
                                break;
                            }
                            case 4: {
                                university.getStudent(studentID).displayStudentCourses(university);
                                break;
                            }
                            case 5:
                                break;
                            default: std::cout << "invalid choice\n";
                        }
                    }while (choice != 5);
                }
                break;
            }
            case 2: {
                int choice;
                do {
                    cout << "\n1. Add a course\n";
                    cout << "2. Add a student\n";
                    cout << "3. Show all students\n";
                    cout << "4. Show all courses\n";
                    cout << "5. Show student's data\n";
                    cout << "6. Exit\n";

                    cin >> choice;

                    if (cin.fail()) {
                        clearInvalidInput();
                        continue;
                    }

                    switch (choice) {
                        case 1: {
                            int courseID;
                            string courseName;
                            int maxStudents;
                            int creditHours;
                            cout << "Course ID: ";
                            cin >> courseID;
                            if (cin.fail()) {
                                clearInvalidInput();
                                continue;
                            }
                            if(!university.addCourse(courseID)) {
                                cout << "Course with ID " << courseID << " already exists" << endl;
                            }
                            cout << "Course name: ";
                            cin.ignore();
                            getline(cin, courseName);
                            cout << "Max students capacity: ";
                            cin >> maxStudents;
                            cout << "Credit hours: ";
                            cin >> creditHours;

                            university.addCourse(courseID, courseName, maxStudents, creditHours);
                            cout << "Course " << courseName << " added with ID: " << courseID << endl;
                            break;
                        }
                        case 2: {
                            string studentName;
                            cout << "Enter student's name: ";
                            cin >> studentName;
                            university.addStudent(studentName);
                            break;
                        }
                        case 3: {
                            university.displayAllStudents();
                            break;
                        }
                        case 4: {
                            university.displayAllCourses();
                            break;
                        }
                        case 5: {
                            int studentID;
                            cout << "Enter student ID: ";
                            cin >> studentID;
                            if (cin.fail()) {
                                clearInvalidInput();
                                continue;
                            }
                            university.displayStudentData(studentID);
                            break;
                        }
                        case 6:
                            break;
                        default: cout << "invalid choice\n";
                    }
                }while(choice != 6);
                break;
            }
            case 3: {
                break;
            }
            default: cout << "invalid choice\n";
        }
    }while(role != 3);

    return 0;
}
