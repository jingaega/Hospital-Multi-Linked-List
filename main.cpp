#include "Hospital.h"
#include <iostream>
using namespace std;

void displayMenu() {
    cout << "\n--- Hospital Management System ---\n";
    cout << "1. Add Patient\n";
    cout << "2. Add Doctor\n";
    cout << "3. Add Room to Doctor\n";
    cout << "4. Assign Room to Patient\n";
    cout << "5. Remove Patient\n";
    cout << "6. Display All Doctors\n";
    cout << "7. Display All Patients\n";
    cout << "8. Find Doctor by ID\n";
    cout << "9. Find Patient by ID\n";
    cout << "10. Exit\n";
    cout << "Enter your choice: ";
}

int main() {
    adrPatient firstPatient;
    adrDoctor firstDoctor;
    initialize(firstPatient, firstDoctor);

    int choice = 0;

    while (choice != 10) {
        displayMenu();
        cin >> choice;

        if (choice == 1) {
            int id, age;
            string name, gender, disease;
            cout << "Enter Patient ID: ";
            cin >> id;
            cout << "Enter Name: ";
            cin >> name;
            cout << "Enter Age: ";
            cin >> age;
            cout << "Enter Gender (Male/Female): ";
            cin >> gender;
            cout << "Enter Disease: ";
            cin >> disease;
            addPatient(firstPatient, id, name, age, gender, disease);
            cout << "Patient added successfully!\n";

        } else if (choice == 2) {
            int id;
            string name, specialty;
            cout << "Enter Doctor ID: ";
            cin >> id;
            cout << "Enter Doctor Name: ";
            cin >> name;
            cout << "Enter Specialty: ";
            cin >> specialty;
            addDoctor(firstDoctor, id, name, specialty);
            cout << "Doctor added successfully!\n";

        } else if (choice == 3) {
            int doctorID, roomNumber, maxCapacity;
            cout << "Enter Doctor ID: ";
            cin >> doctorID;
            cout << "Enter Room Number: ";
            cin >> roomNumber;
            cout << "Enter Max Capacity of the Room: ";
            cin >> maxCapacity;
            addRoom(firstDoctor, doctorID, roomNumber, maxCapacity);

        } else if (choice == 4) {
            int patientId, roomNumber;
            cout << "Enter Patient ID: ";
            cin >> patientId;
            cout << "Enter Room Number: ";
            cin >> roomNumber;
            assignRoom(firstPatient, firstDoctor, patientId, roomNumber);

        } else if (choice == 5) {
            int patientId;
            cout << "Enter Patient ID to Remove: ";
            cin >> patientId;
            removePatient(firstPatient, patientId);

        } else if (choice == 6) {
            displayDoctors(firstDoctor);

        } else if (choice == 7) {
            displayPatients(firstPatient, firstDoctor);

        } else if (choice == 8) { // Find Doctor by ID
            int doctorID;
            cout << "Enter Doctor ID: ";
            cin >> doctorID;
            adrDoctor doctor = findDoctor(firstDoctor, doctorID);
            if (doctor != NULL) {
                cout << "Doctor ID: " << doctor->id << "\n"
                     << "Name: " << doctor->name << "\n"
                     << "Specialty: " << doctor->specialty << "\n";

                adrRoom room = doctor->roomList;
                while (room != NULL) {
                    cout << "  - Room Number: " << room->roomNumber
                         << ", Current Patients: " << room->currentPatients
                         << ", Max Capacity: " << room->maxCapacity << "\n";
                    room = room->nextRoom;
                }
            } else {
                cout << "Doctor with ID " << doctorID << " not found.\n";
            }

        } else if (choice == 9) { // Find Patient by ID
            int patientID;
            cout << "Enter Patient ID: ";
            cin >> patientID;
            adrPatient patient = findPatient(firstPatient, patientID);
            if (patient != NULL) {
                cout << "Patient ID: " << patient->id << "\n"
                     << "Name: " << patient->name << "\n"
                     << "Age: " << patient->age << "\n"
                     << "Gender: " << patient->gender << "\n"
                     << "Disease: " << patient->disease << "\n";

                if (patient->assignedRoom != NULL) {
                    adrRoom room = patient->assignedRoom;
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
            } else {
                cout << "Patient with ID " << patientID << " not found.\n";
            }

        } else if (choice != 10) {
            cout << "Invalid choice. Please try again.\n";
        }
    }

    cout << "Exiting the program. Goodbye!\n";
    return 0;
}
