#include <iostream>
#include <fstream>
using namespace std;

class Course 
{
public:
    string id, name;
    int capacity;
    int enrolled;

    void display() 
    {
        cout << id << " | " << name 
             << " | Seats Left: " << (capacity - enrolled) << endl;
    }
};

// 🔹 LOAD COURSES FROM FILE
void loadCourses(Course courses[], int &n)
{
    ifstream file("courses.txt");
    n = 0;

    while (file >> courses[n].id >> courses[n].name 
                >> courses[n].capacity >> courses[n].enrolled)
    {
        n++;
    }

    file.close();
}

// 🔹 SAVE COURSES TO FILE
void saveCourses(Course courses[], int n)
{
    ofstream file("courses.txt");

    for (int i = 0; i < n; i++)
    {
        file << courses[i].id << " "
             << courses[i].name << " "
             << courses[i].capacity << " "
             << courses[i].enrolled << endl;
    }

    file.close();
}

// 🔹 LOGIN FUNCTION
bool loginStudent(string username, string password)
{
    ifstream file("students.txt");
    string u, p;

    while (file >> u >> p)
    {
        if (u == username && p == password)
        {
            file.close();
            return true;
        }
    }

    file.close();
    return false;
}

// 🔹 REGISTER NEW STUDENT
void registerStudent(string username, string password)
{
    ofstream file("students.txt", ios::app);
    file << "\n"<< username << " " << password << endl;
    file.close();
}

class Student 
{
private:
    string username;
    string registeredCourses[2];
    int courseCount;

public:
    Student(string uname) 
    {
        username = uname;
        courseCount = 0;
    }

    void viewCourses(Course courses[], int n) 
    {
        cout << "\nAvailable Courses:\n";
        for (int i = 0; i < n; i++) 
        {
            courses[i].display();
        }
    }

    void registerCourse(Course courses[], int n) 
    {
        string cid;
        cout << "Enter Course ID: ";
        cin >> cid;

        // duplicate check
        for (int i = 0; i < courseCount; i++) 
        {
            if (registeredCourses[i] == cid) 
            {
                cout << "Already registered!\n";
                return;
            }
        }

        if (courseCount == 2) 
        {
            cout << "Max 2 courses allowed!\n";
            return;
        }

        for (int i = 0; i < n; i++) 
        {
            if (courses[i].id == cid) 
            {
                if (courses[i].enrolled >= courses[i].capacity) 
                {
                    cout << "Course is full!\n";
                    return;
                }

                registeredCourses[courseCount++] = cid;
                courses[i].enrolled++;

                saveCourses(courses, n); //  save update

                cout << "Registered successfully!\n";
                return;
            }
        }

        cout << "Course not found!\n";
    }

    void dropCourse(Course courses[], int n) 
    {
        string cid;
        cout << "Enter Course ID to drop: ";
        cin >> cid;

        for (int i = 0; i < courseCount; i++) 
        {
            if (registeredCourses[i] == cid) 
            {
                for (int j = 0; j < n; j++) 
                {
                    if (courses[j].id == cid) 
                    {
                        courses[j].enrolled--;
                    }
                }

                for (int j = i; j < courseCount - 1; j++) 
                {
                    registeredCourses[j] = registeredCourses[j + 1];
                }

                courseCount--;

                saveCourses(courses, n); // 🔥 save update

                cout << "Course dropped!\n";
                return;
            }
        }

        cout << "You are not registered in this course!\n";
    }

    void viewMyCourses() 
    {
        if (courseCount == 0) 
        {
            cout << "No courses registered.\n";
            return;
        }

        cout << "\nMy Courses:\n";
        for (int i = 0; i < courseCount; i++) 
        {
            cout << registeredCourses[i] << endl;
        }
    }

    void studentMenu(Course courses[], int n) 
    {
        int choice;

        do {
            cout << "\n----- STUDENT MENU -----\n";
            cout << "1. View Available Courses\n";
            cout << "2. Register for Course\n";
            cout << "3. Drop Course\n";
            cout << "4. View My Courses\n";
            cout << "5. Logout\n";
            cout << "Enter choice: ";
            cin >> choice;

            switch (choice) 
            {
                case 1: viewCourses(courses, n); break;
                case 2: registerCourse(courses, n); break;
                case 3: dropCourse(courses, n); break;
                case 4: viewMyCourses(); break;
                case 5: cout << "Logging out...\n"; break;
                default: cout << "Invalid choice!\n";
            }

        } while (choice != 5);
    }
};

int main() 
{
    Course courses[10];
    int n;

    loadCourses(courses, n);

    int role;
    cout << "1. Student\n2. Admin\nEnter role: ";
    cin >> role;

    if (role == 1) 
    {
        int opt;
        cout << "1. Login\n2. Register\nEnter: ";
        cin >> opt;

        string username, password;

        cout << "Enter username: ";
        cin >> username;

        cout << "Enter password: ";
        cin >> password;

        if (opt == 2)
        {
            registerStudent(username, password);
            cout << "Registered successfully!\n";
        }
        else{
            if (loginStudent(username, password)) 
            {
                cout << "Login successful!\n";

                Student s(username);
                s.studentMenu(courses, n);
            } 
            else 
            {
                cout << "Invalid credentials!\n";
            }
        }
    }
    else if (role == 2) 
    {
        cout << "Admin part not implemented yet 😌\n";
    }
    else 
    {
        cout << "Invalid role!\n";
    }

    return 0;
}
