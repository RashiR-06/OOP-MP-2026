# OOP-MP-2026
# Course Registration System (C++ OOP Project)

A **console-based Course Registration System** built using **C++ and Object-Oriented Programming (OOP)** concepts.  
This system allows students to register/drop courses while admins manage course offerings.

---

## Features

### Student Features
- Register new account
- Login securely
- View available courses
- Register for courses (max 2 courses)
- Drop registered courses
- View enrolled courses

---

### Admin Features
- View all courses
- Add new courses
- Delete existing courses
- View system statistics (active sessions)

---

## OOP Concepts Used

- ✔ **Inheritance** → `Student` and `Admin` inherit from `Person`
- ✔ **Encapsulation** → Data handled via class methods
- ✔ **Abstraction** → Complex logic hidden inside functions
- ✔ **Polymorphism (basic design)** → Shared structure across classes
- ✔ **Static Members** → Track total active users (`totalUsers`)

---

## File Handling

The system uses text files for persistent storage:

| File Name         | Purpose |
|------------------|--------|
| `courses.txt`     | Stores course details |
| `students.txt`    | Stores login credentials |
| `enrollments.txt` | Stores student-course mappings |

---

## Data Format

### courses.txt
C101 DSA 50 10

C102 OS 40 20

### students.txt
user1 pass1

user2 pass2

### enrollments.txt
user1 C101 C102

user2 C102 None

---

## Functional Flow

### Student Flow
1. Register/Login
2. View available courses
3. Register (if seats available)
4. Drop course if needed
5. View enrolled courses

---

### Admin Flow
1. Login (default credentials)
2. Add/Delete courses
3. Monitor system usage

---

## Default Admin Credentials
Username: admin

Password: 123

---

## How to Run

### Step 1: Compile
```bash
g++ oopmp.cpp -o course_system
```
Step 2: Run
```bash
./course_system
```
