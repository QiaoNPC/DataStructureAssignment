#include "import.h"

using namespace std;
using namespace chrono;

PropertyNode* copyProperties(PropertyNode* original) {
    if (original == nullptr) return nullptr;
    PropertyNode* newHead = new PropertyNode(*original);
    PropertyNode* currentNew = newHead;
    PropertyNode* currentOriginal = original->next;
    while (currentOriginal != nullptr) {
        currentNew->next = new PropertyNode(*currentOriginal);
        currentNew = currentNew->next;
        currentOriginal = currentOriginal->next;
    }
    currentNew->next = nullptr;  // Ensure the new list is properly terminated
    return newHead;
}

void compareSortingSpeeds(PropertyNode* properties, int parameterChoice) {
    PropertyNode* sorted = nullptr;
    PropertyNode* sorted2 = nullptr;

    PropertyNode* propertiesCopy1 = copyProperties(properties);
    PropertyNode* propertiesCopy2 = copyProperties(properties);

    auto start = high_resolution_clock::now();
    sorted = sortProperties(propertiesCopy1, parameterChoice, true);
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start).count();
    cout << "Merge Sort time: " << duration << " ms" << endl;

    start = high_resolution_clock::now();
    sorted2 = sortProperties(propertiesCopy2, parameterChoice, false);
    end = high_resolution_clock::now();
    duration = duration_cast<milliseconds>(end - start).count();
    cout << "Quick Sort time: " << duration << " ms" << endl;

    freeList(sorted);
    freeList(sorted2);
}   

// Main function
int main() {
    csvReader reader("mudah-apartment-kl-selangor mmz.csv");
    PropertyNode* properties = reader.readCSV();

    int mainMenuChoice;

    do {
        PropertyNode* sorted = nullptr;
        // Display menu
        mainMenuChoice = getMenuChoice();

        int parameterChoice;
        vector<int> columnChoices;

        if (mainMenuChoice == 1 || mainMenuChoice == 2 || mainMenuChoice == 3) {
            do {
                parameterChoice = getColumnChoice();
                columnChoices.push_back(parameterChoice);
            } while (parameterChoice < 0 || parameterChoice > 13);

            if (parameterChoice == 13) {
                break;
            }
        } 

        // Process user mainMenuChoice
        switch (mainMenuChoice) {
            case 1:
                sorted = sortProperties(copyProperties(properties), parameterChoice, true);
                displayProperties(sorted, columnChoices);
                reader.writePropertiesToCSV(sorted, "sorted_properties.csv");
                freeList(sorted);
                break;
            case 2:
                sorted = sortProperties(copyProperties(properties), parameterChoice, false);
                displayProperties(sorted, columnChoices);
                reader.writePropertiesToCSV(sorted, "sorted_properties.csv");
                freeList(sorted);
                break;
            case 3: 
                compareSortingSpeeds(properties, parameterChoice);
                break;
            case 4:
                cout << "Exiting program." << endl;
                break;
            default:
                cout << "Invalid mainMenuChoice. Please enter again." << endl;
                break;
        }
    } while (mainMenuChoice != 4);

    freeList(properties);

    return 0;
}