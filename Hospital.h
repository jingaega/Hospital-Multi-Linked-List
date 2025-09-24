#ifndef HOSPITAL_H
#define HOSPITAL_H

#include <string>
using namespace std;

// Typedefs for pointers
typedef struct Patient* adrPatient;
typedef struct Room* adrRoom;
typedef struct Doctor* adrDoctor;

// Room structure
struct Room {
    int roomNumber;       // Room number
    int currentPatients;  // Current number of patients in the room
    int maxCapacity;      // Maximum capacity of the room
    adrRoom nextRoom;     // Pointer to the next room
};

// Doctor structure
struct Doctor {
    int id;              // Doctor ID
    string name;         // Doctor name
    string specialty;    // Doctor's specialty
    adrRoom roomList;    // Pointer to the first room under this doctor
    adrDoctor nextDoctor;// Pointer to the next doctor
};

// Patient structure
struct Patient {
    int id;               // Patient ID
    string name;          // Patient name
    int age;              // Patient age
    string gender;        // Patient gender
    string disease;       // Disease type
    adrRoom assignedRoom; // Pointer to the room assigned to the patient
    adrPatient nextPatient;// Pointer to the next patient
};

// Function declarations
void initialize(adrPatient& firstPatient, adrDoctor& firstDoctor);
void addPatient(adrPatient& first, int id, string name, int age, string gender, string disease);
void addDoctor(adrDoctor& firstDoctor, int id, string name, string specialty);
void addRoom(adrDoctor firstDoctor, int doctorID, int roomNumber, int maxCapacity);
bool isRoomAvailable(adrRoom room);
void assignRoom(adrPatient first, adrDoctor firstDoctor, int patientId, int roomNumber);
void removePatient(adrPatient& first, int patientId);
void displayDoctors(adrDoctor firstDoctor);
void displayPatients(adrPatient first, adrDoctor firstDoctor);
adrPatient findPatient(adrPatient first, int id);
adrDoctor findDoctor(adrDoctor firstDoctor, int id);
adrRoom findRoom(adrRoom roomList, int roomNumber);
adrDoctor findDoctorForRoom(adrDoctor firstDoctor, adrRoom room);
#endif
