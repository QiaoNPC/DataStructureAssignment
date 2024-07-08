#pragma once
#include "import.h"

int getMenuChoice() {
  int mainMenuChoice;

  cout << endl << endl;
  cout << "===== Main Menu =====" << endl;
  cout << "1. Sort by Merge Sort" << endl;
  cout << "2. Sort by Insertion Sort" << endl;
  cout << "3. Comparison" << endl;
  cout << "4. Exit" << endl;
  cout << "Enter your choice: ";
  cin >> mainMenuChoice;

  return mainMenuChoice;
}

int getColumnChoice() {
  int parameterChoice;

  cout << "===== Select Column To Sort =====" << endl;
  cout << "1. ID" << endl;
  cout << "2. Property Name" << endl;
  cout << "3. Completion Year" << endl;
  cout << "4. Monthy Rent" << endl;
  cout << "5. Location" << endl;
  cout << "6. Property Type" << endl;
  cout << "7. Rooms" << endl;
  cout << "8. Parking" << endl;
  cout << "9. Bathroom" << endl;
  cout << "10. Size" << endl;
  cout << "11. Furnished" << endl;
  cout << "12. Region" << endl;
  cout << "13. Exit" << endl;
  cout << "Enter your choice: ";
  cin >> parameterChoice;

  return parameterChoice;
}
