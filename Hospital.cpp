#include "Hospital.h"
#include <iostream>
using namespace std;

// Initialize pointers for patient and doctor lists
void initialize(adrPatient& firstPatient, adrDoctor& firstDoctor) {
    firstPatient = NULL;
    firstDoctor = NULL;
}

// Add a new patient
void addPatient(adrPatient& first, int id, string name, int age, string gender, string disease) {
    adrPatient newPatient = new Patient;
    newPatient->id = id;
    newPatient->name = name;
    newPatient->age = age;
    newPatient->gender = gender;
    newPatient->disease = disease;
    newPatient->assignedRoom = NULL;
    newPatient->nextPatient = NULL;

    if (first == NULL) {
        first = newPatient;
    } else {
        adrPatient temp = first;
        while (temp->nextPatient != NULL) {
            temp = temp->nextPatient;
        }
        temp->nextPatient = newPatient;
    }
}

// Remove a patient
void removePatient(adrPatient& first, int patientId) {
    adrPatient prev = NULL;
    adrPatient current = first;

    while (current != NULL && current->id != patientId) {
        prev = current;
        current = current->nextPatient;
    }

    if (current == NULL) {
        cout << "Patient with ID " << patientId << " not found.\n";
        return;
    }

    // Update the room's current patient count if assigned
    if (current->assignedRoom != NULL) {
        current->assignedRoom->currentPatients--;
    }

    // Remove the patient from the list
    if (prev == NULL) { // Removing the first patient
        first = current->nextPatient;
    } else {
        prev->nextPatient = current->nextPatient;
    }

    delete current;
    cout << "Patient with ID " << patientId << " has been removed successfully.\n";
}

// Add a new doctor
void addDoctor(adrDoctor& firstDoctor, int id, string name, string specialty) {
    adrDoctor newDoctor = new Doctor;
    newDoctor->id = id;
    newDoctor->name = name;
    newDoctor->specialty = specialty;
    newDoctor->roomList = NULL;
    newDoctor->nextDoctor = NULL;

    if (firstDoctor == NULL) {
        firstDoctor = newDoctor;
    } else {
        adrDoctor temp = firstDoctor;
        while (temp->nextDoctor != NULL) {
            temp = temp->nextDoctor;
        }
        temp->nextDoctor = newDoctor;
    }
}

// Add a new room under a doctor
void addRoom(adrDoctor firstDoctor, int doctorID, int roomNumber, int maxCapacity) {
    adrDoctor doctor = findDoctor(firstDoctor, doctorID);
    if (doctor == NULL) {
        cout << "Doctor with ID " << doctorID << " not found.\n";
        return;
    }

    // Check if the room number already exists across all doctors
    adrDoctor currentDoctor = firstDoctor;
    while (currentDoctor != NULL) {
        if (findRoom(currentDoctor->roomList, roomNumber) != NULL) {
            cout << "Room " << roomNumber << " has already been assigned to Doctor ID " << currentDoctor->id << ".\n";
            return;
        }
        currentDoctor = currentDoctor->nextDoctor;
    }

    adrRoom newRoom = new Room;
    newRoom->roomNumber = roomNumber;
    newRoom->currentPatients = 0;  // Start with no patients
    newRoom->maxCapacity = maxCapacity;
    newRoom->nextRoom = NULL;

    if (doctor->roomList == NULL) {
        doctor->roomList = newRoom;
    } else {
        adrRoom temp = doctor->roomList;
        while (temp->nextRoom != NULL) {
            temp = temp->nextRoom;
        }
        temp->nextRoom = newRoom;
    }

    cout << "Room " << roomNumber << " with max capacity " << maxCapacity
         << " added under Doctor ID " << doctorID << ".\n";
}

// Check if a room is available for a new patient
bool isRoomAvailable(adrRoom room) {
    return room->currentPatients < room->maxCapacity;
}

// Assign a room to a patient
void assignRoom(adrPatient first, adrDoctor firstDoctor, int patientId, int roomNumber) {
    adrPatient patient = findPatient(first, patientId);
    if (patient == NULL) {
        cout << "Patient with ID " << patientId << " not found.\n";
        return;
    }

    adrRoom assignedRoom = NULL;
    adrDoctor doctor = firstDoctor;

    // Find the room and its associated doctor
    while (doctor != NULL && assignedRoom == NULL) {
        assignedRoom = findRoom(doctor->roomList, roomNumber);
        if (assignedRoom != NULL) {
            break;
        }
        doctor = doctor->nextDoctor;
    }

    if (assignedRoom == NULL) {
        cout << "Room " << roomNumber << " not found.\n";
        return;
    }

    if (isRoomAvailable(assignedRoom)) {
        assignedRoom->currentPatients++;
        patient->assignedRoom = assignedRoom;
        cout << "Room " << roomNumber << " assigned to Patient ID " << patientId << ".\n";
    } else {
        cout << "Room " << roomNumber << " is at full capacity. Cannot assign to Patient ID " << patientId << ".\n";
    }
}

// Display all doctors
void displayDoctors(adrDoctor firstDoctor) {
    adrDoctor currentDoctor = firstDoctor;
    while (currentDoctor != NULL) {
        cout << "Doctor ID: " << currentDoctor->id
             << ", Name: " << currentDoctor->name
             << ", Specialty: " << currentDoctor->specialty << "\n";

        adrRoom currentRoom = currentDoctor->roomList;
        while (currentRoom != NULL) {
            cout << "  - Room Number: " << currentRoom->roomNumber
                 << ", Current Patients: " << currentRoom->currentPatients
                 << ", Max Capacity: " << currentRoom->maxCapacity << "\n";
            currentRoom = currentRoom->nextRoom;
        }
        currentDoctor = currentDoctor->nextDoctor;
    }
}

// Display all patients
void displayPatients(adrPatient first, adrDoctor firstDoctor) {
    adrPatient currentPatient = first;
    while (currentPatient != NULL) {
        cout << "Patient ID: " << currentPatient->id
             << ", Name: " << currentPatient->name
             << ", Age: " << currentPatient->age
             << ", Gender: " << currentPatient->gender
             << ", Disease: " << currentPatient->disease << "\n";

        if (currentPatient->assignedRoom != NULL) {
            adrRoom room = currentPatient->assignedRoom;
            adrDoctor doctor = findDoctorForRoom(firstDoctor, room);

            cout << "  - Room Number: " << room->roomNumber
                 << ", Current Patients: " << room->currentPatients
                 << ", Max Capacity: " << room->maxCapacity << "\n";

            if (doctor != NULL) {
                cout << "  - Assigned Doctor: " << doctor->name
                     << ", Specialty: " << doctor->specialty << "\n";
            }
        } else {
            cout << "  - No room assigned.\n";
        }
        currentPatient = currentPatient->nextPatient;
    }
}

// Find a patient by ID
adrPatient findPatient(adrPatient first, int id) {
    adrPatient temp = first;
    while (temp != NULL) {
        if (temp->id == id) {
            return temp;
        }
        temp = temp->nextPatient;
    }
    return NULL;
}

// Find a doctor by ID
adrDoctor findDoctor(adrDoctor firstDoctor, int id) {
    adrDoctor temp = firstDoctor;
    while (temp != NULL) {
        if (temp->id == id) {
            return temp;
        }
        temp = temp->nextDoctor;
    }
    return NULL;
}

// Find a room by room number
adrRoom findRoom(adrRoom roomList, int roomNumber) {
    adrRoom temp = roomList;
    while (temp != NULL) {
        if (temp->roomNumber == roomNumber) {
            return temp;
        }
        temp = temp->nextRoom;
    }
    return NULL;
}

// Find the doctor associated with a room
adrDoctor findDoctorForRoom(adrDoctor firstDoctor, adrRoom room) {
    adrDoctor currentDoctor = firstDoctor;
    while (currentDoctor != NULL) {
        adrRoom currentRoom = currentDoctor->roomList;
        while (currentRoom != NULL) {
            if (currentRoom == room) {
                return currentDoctor;
            }
            currentRoom = currentRoom->nextRoom;
        }
        currentDoctor = currentDoctor->nextDoctor;
    }
    return NULL;
}
