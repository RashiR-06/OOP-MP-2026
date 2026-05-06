#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>
#include <string>

using namespace std;

// --- ADVANCED OOP: INHERITANCE ---
class Person {
public:
    string username;
    static int totalUsers; 

    Person(string uname) : username(uname) {
        totalUsers++; 
    }
};

int Person::totalUsers = 0;

class Course {
public:
    string id, name;
    int capacity;
    int enrolled;

    void display() const {
        cout << id << " | " << name 
             << " | Seats Left: " << (capacity - enrolled) << " (" 
             << enrolled << "/" << capacity << ")" << endl;
    }
};

// --- FILE HANDLING FUNCTIONS ---
// Now uses vector: no need for 'int &n' as courses.size() handles it
void loadCourses(vector<Course> &courses) {
    ifstream file("courses.txt");
    courses.clear();
    Course temp;
    while (file >> temp.id >> temp.name >> temp.capacity >> temp.enrolled) {
        courses.push_back(temp);
    }
    file.close();
}

void saveCourses(const vector<Course> &courses) {
    ofstream file("courses.txt");
    for (const auto &c : courses) {
        file << c.id << " " << c.name << " "
             << c.capacity << " " << c.enrolled << endl;
    }
    file.close();
}

void saveEnrollments(string uname, const vector<string> &regs) {
    ifstream infile("enrollments.txt");
    string line_u, c1, c2;
    vector<string> otherData;
    
    while (infile >> line_u >> c1 >> c2) {
        if (line_u != uname) {
            otherData.push_back(line_u + " " + c1 + " " + c2);
        }
    }
    infile.close();

    ofstream outfile("enrollments.txt");
    for (const string& s : otherData) outfile << s << endl;
    
    // Using vector indices to save
    outfile << uname << " " << (regs.size() > 0 ? regs[0] : "None") << " " 
            << (regs.size() > 1 ? regs[1] : "None") << endl;
    outfile.close();
}

void loadMyEnrollments(string uname, vector<string> &regs) {
    ifstream file("enrollments.txt");
    string line_u, c1, c2;
    regs.clear();
    while (file >> line_u >> c1 >> c2) {
        if (line_u == uname) {
            if (c1 != "None") regs.push_back(c1);
            if (c2 != "None") regs.push_back(c2);
            break;
        }
    }
    file.close();
}

bool loginStudent(string username, string password) {
    ifstream file("students.txt");
    string u, p;
    while (file >> u >> p) {
        if (u == username && p == password) { file.close(); return true; }
    }
    file.close(); return false;
}

void registerStudent(string username, string password) {
    ofstream file("students.txt", ios::app);
    file << "\n" << username << " " << password << endl;
    file.close();
}

// --- STUDENT CLASS ---
class Student : public Person {
private:
    vector<string> registeredCourses; // Changed array to vector

public:
    Student(string uname) : Person(uname) {
        loadMyEnrollments(username, registeredCourses);
    }

    void viewCourses(const vector<Course> &courses) {
        cout << "\nAvailable Courses:\n";
        for (const auto &c : courses) c.display();
    }

    void registerCourse(vector<Course> &courses) {
        string cid;
        cout << "Enter Course ID: "; cin >> cid;
        
        for (const string &id : registeredCourses) {
            if (id == cid) { cout << "Already registered!\n"; return; }
        }
        
        if (registeredCourses.size() >= 2) { 
            cout << "Max 2 courses allowed!\n"; return; 
        }

        for (auto &c : courses) {
            if (c.id == cid) {
                if (c.enrolled >= c.capacity) { cout << "Course is full!\n"; return; }
                registeredCourses.push_back(cid);
                c.enrolled++;
                saveCourses(courses);
                saveEnrollments(username, registeredCourses);
                cout << "Registered successfully!\n";
                return;
            }
        }
        cout << "Course not found!\n";
    }

    void dropCourse(vector<Course> &courses) {
        string cid;
        cout << "Enter Course ID to drop: "; cin >> cid;
        
        for (size_t i = 0; i < registeredCourses.size(); i++) {
            if (registeredCourses[i] == cid) {
                for (auto &c : courses) {
                    if (c.id == cid) c.enrolled--;
                }
                registeredCourses.erase(registeredCourses.begin() + i);
                saveCourses(courses);
                saveEnrollments(username, registeredCourses);
                cout << "Course dropped!\n";
                return;
            }
        }
        cout << "Not registered in this course!\n";
    }

    void viewMyCourses(const vector<Course> &courses) {
        if (registeredCourses.empty()) { cout << "No courses registered.\n"; return; }
        cout << "\nMy Courses:\n";
        for (const string &regId : registeredCourses) {
            for (const auto &c : courses) {
                if (c.id == regId) {
                    cout << "- " << c.id << " : " << c.name << endl;
                }
            }
        }
    }

    void studentMenu(vector<Course> &courses) {
        int choice;
        do {
            cout << "\n--- STUDENT MENU (" << username << ") ---\n";
            cout << "1. View AllCourses\n2. Register Course\n3. Drop Course\n4. View My Courses\n5. Logout\nChoice: ";
            cin >> choice;
            if (choice == 1) viewCourses(courses);
            else if (choice == 2) registerCourse(courses);
            else if (choice == 3) dropCourse(courses);
            else if (choice == 4) viewMyCourses(courses);
        } while (choice != 5);
    }
};

// --- ADMIN CLASS ---
class Admin : public Person {
public:
    Admin(string uname) : Person(uname) {}

    void addCourse(vector<Course> &courses) {
        Course newC;
        cout << "New Course ID: "; cin >> newC.id;
        cout << "New Course Name: "; cin >> newC.name;
        cout << "Capacity: "; cin >> newC.capacity;
        newC.enrolled = 0;
        try {
            if (newC.capacity <= 0) throw runtime_error("Capacity must be positive!");
            courses.push_back(newC);
            saveCourses(courses);
            cout << "Course added!\n";
        } catch (const runtime_error& e) { cout << "[ERROR] " << e.what() << endl; }
    }

    void deleteCourse(vector<Course> &courses) {
        string cid;
        cout << "Enter ID to delete: "; cin >> cid;
        for (size_t i = 0; i < courses.size(); i++) {
            if (courses[i].id == cid) {
                courses.erase(courses.begin() + i);
                saveCourses(courses);
                cout << "Deleted.\n";
                return;
            }
        }
        cout << "Not found.\n";
    }

    void adminMenu(vector<Course> &courses) {
        int choice;
        do {
            cout << "\n--- ADMIN PANEL ---\n1. View All\n2. Add Course \n3. Delete Course\n4. Stats\n5. Logout\nChoice: ";
            cin >> choice;
            if (choice == 1) for(const auto &c : courses) c.display();
            else if (choice == 2) addCourse(courses);
            else if (choice == 3) deleteCourse(courses);
            else if (choice == 4) cout << "Total Active Sessions(Objects): " << totalUsers << endl;
        } while (choice != 5);
    }
};

int main() {
    vector<Course> courses; // Main container is now a vector
    loadCourses(courses);

    while (true) {
        int role;
        cout << "\n1. Student\n2. Admin\n3. Exit\nRole: "; cin >> role;
        if (role == 3) break;
        if (role == 1) {
            int opt;
            cout << "1. Login\n2. Register\nChoice: "; cin >> opt;
            string u, p;
            cout << "User: "; cin >> u; cout << "Pass: "; cin >> p;
            if (opt == 2) registerStudent(u, p);
            else if (loginStudent(u, p)) { 
                Student s(u); 
                s.studentMenu(courses); 
            }
            else cout << "Login Failed, Not a registered student.\n";
        } 
        else if (role == 2) {
            string u, p;
            cout << "Admin User: "; cin >> u; cout << "Admin Pass: "; cin >> p;
            if (u == "admin" && p == "123") { 
                Admin a(u); 
                a.adminMenu(courses); 
            }
            else cout << "Denied.\n";
        }
    }
    return 0;
}
