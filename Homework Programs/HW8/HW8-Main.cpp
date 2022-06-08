#include <iostream>
#include <string>
#include <fstream>

#include "PriorityQueue.hpp"

////////////////////////////////////////////////////////////////////////////////

using namespace std;

void displayMenu();

void readFile(string file, PriorityQueue &queue);

void showPatient(PriorityQueue&);

int main(int argc, char const *argv[]) {
  int QueueSize = 0;

  ////////////////////////////////
  // Handling command line args //
  ////////////////////////////////
  if (argc < 2) {
    cout << "You need more command-line arguments!\n";
    return 1;
  }
  else {
    QueueSize = stoi(argv[1]);
  }

  ///////////////////////
  // Variable creation //
  ///////////////////////

  // creating the instance of my Priority Queue
  PriorityQueue HospitalQueue = PriorityQueue(QueueSize);

  // bool to exit the while loop once set to true
  bool quit = false;

  // input parameters for the switch statement
  int input; // I was having difficulty using standard cin, so I resorted to using getline
  string s_input; // basically used the switch statement implementation from assignment #3 & #6

  // input parameters
  string filename, patientName, severity, time;
  int injurySeverity, treatmentTime;

  // total time spent fixing patients
  int totalTime = 0;

  ///////////////////////
  // Main menu portion //
  ///////////////////////
  while (!quit) {
    displayMenu();

    try {
      getline(cin, s_input);
      input = stoi(s_input);
    }

    catch (exception a) {
      cout<<"Invalid input"<<endl;
      continue;
    }

    switch (input) {
      case 1:
        cout<<"Enter filename:"<<endl;
        getline(cin, filename);
        // implement file reading function
        readFile(filename, HospitalQueue);
        break;

      case 2:
        cout<<"Enter Patient Name:"<<endl;
        getline(cin, patientName);
        cout<<"Enter Injury Severity:"<<endl;
        getline(cin, severity);
        injurySeverity = stoi(severity);
        cout<<"Enter Treatment Time:"<<endl;
        getline(cin, time);
        treatmentTime = stoi(time);
        HospitalQueue.enqueue(patientName, injurySeverity, treatmentTime);
        break;

      case 3:
        if (!HospitalQueue.isEmpty()) {
          showPatient(HospitalQueue);
        }
        else {
          cout<<"Queue is empty\n";
        }
        break;

      case 4:
        if (!HospitalQueue.isEmpty()) {
          totalTime += HospitalQueue.peekTreatmentTime();
          cout<<"Patient Name: "<< HospitalQueue.peekName()<<" - Total Time Treating Patients: "<<totalTime<<endl;
          HospitalQueue.dequeue();
        }
        else {
          cout<<"Queue is empty\n";
        }

        break;

      case 5:

        while (!HospitalQueue.isEmpty()) {
          totalTime += HospitalQueue.peekTreatmentTime();
          cout<<"Patient Name: "<< HospitalQueue.peekName()<<" - Total Time Treating Patients: "<<totalTime<<endl;
          HospitalQueue.dequeue();
        }

        break;

      case 6:
        quit = true;

        cout<<"Goodbye!"<<endl;
        break;

      default:
        cout<<"Invalid input!"<<endl;
        break;
    }

  }

  cout<<"Total time fixing patients right up: "<<totalTime<<endl;

  return 0;
}

void displayMenu() {
  cout<<"======Main Menu======"<<endl
      <<"1. Get Patient Information from File"<<endl
      <<"2. Add Patient to Priority Queue"<<endl
      <<"3. Show Next Patient"<<endl
      <<"4. Treat Next Patient"<<endl
      <<"5. Treat Entire Queue"<<endl
      <<"6. Quit"<<endl;
}

void readFile(string file, PriorityQueue &queue) {
  fstream ifs(file);
  string name, injury, treatment;
  int injuryS = 0;
  int treatmentT = 0;

  bool ToContinue = false;

  while (!ifs.eof() && !ToContinue) {
    if (queue.isFull()) {
      cout<<"Priority Queue full. Send remaining patients to another hopsital."<<endl; // so the full message prints.....
      ToContinue = true;
      break;
    }

    getline(ifs, name, ' ');
    getline(ifs, injury, ' ');
    getline(ifs, treatment);
    injuryS = stoi(injury);
    treatmentT = stoi(treatment);

    queue.enqueue(name, injuryS, treatmentT);
  }
}

void showPatient(PriorityQueue &queue) {
  cout<<"Patient Name: "<< queue.peekName() <<endl
      <<"Injury Severity: "<< queue.peekInjurySeverity() <<endl
      <<"Treatment Time: "<< queue.peekTreatmentTime() <<endl;
}
