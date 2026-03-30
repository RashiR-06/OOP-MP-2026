#include <iostream>
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

    // 🔹 VIEW AVAILABLE COURSES
    void viewCourses(Course courses[], int n) 
    {
        cout << "\nAvailable Courses:\n";
        for (int i = 0; i < n; i++) 
        {
            courses[i].display();
        }
    }

    // 🔹 REGISTER COURSE
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

        // max 2 courses
        if (courseCount == 2) 
        {
            cout << "Max 2 courses allowed!\n";
            return;
        }

        // find course
        for (int i = 0; i < n; i++) 
        {
            if (courses[i].id == cid) 
            {
                if (courses[i].enrolled >= courses[i].capacity) 
                {
                    cout << "Course is full!\n";
                    return;
                }

                registeredCourses[courseCount] = cid;
                courseCount++;
                courses[i].enrolled++;

                cout << "Registered successfully!\n";
                return;
            }
        }

        cout << "Course not found!\n";
    }

    // 🔹 DROP COURSE
    void dropCourse(Course courses[], int n) 
    {
        string cid;
        cout << "Enter Course ID to drop: ";
        cin >> cid;

        for (int i = 0; i < courseCount; i++) 
        {
            if (registeredCourses[i] == cid) 
            {
                // decrease enrollment
                for (int j = 0; j < n; j++) 
                {
                    if (courses[j].id == cid) 
                    {
                        courses[j].enrolled--;
                    }
                }

                // shift array
                for (int j = i; j < courseCount - 1; j++) 
                {
                    registeredCourses[j] = registeredCourses[j + 1];
                }

                courseCount--;

                cout << "Course dropped!\n";
                return;
            }
        }

        cout << "You are not registered in this course!\n";
    }

    // 🔹 VIEW MY COURSES
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

    // 🔹 STUDENT MENU
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
    Course courses[5] = 
    {
        {"C1", "AI/ML", 20, 0},
        {"C2", "CYBERSECURITY", 10, 0},
        {"C3", "WEB DEVELOPMENT", 5, 0},
        {"C4", "BLOCKCHAIN", 1, 0},
        {"C5", "CLOUD COMPUTING", 15, 0}
    };

    int role;
    cout << "1. Student\n2. Admin\nEnter role: ";
    cin >> role;

    if (role == 1) 
    {
        string username, password;

        cout << "Enter username: ";
        cin >> username;

        cout << "Enter password: ";
        cin >> password;

        string correctPass = username + "123";

        if (password == correctPass) 
        {
            cout << "Login successful!\n";

            Student s(username);
            s.studentMenu(courses, 5);
        } 
        else 
        {
            cout << "Invalid credentials!\n";
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
