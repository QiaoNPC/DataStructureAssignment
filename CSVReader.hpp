#pragma once
#include "import.h"

// Function to parse monthly rent
double parseMonthlyRent(const string& rent) {
  string cleanRent = rent;
  cleanRent.erase(remove(cleanRent.begin(), cleanRent.end(), ' '), cleanRent.end());
  cleanRent.erase(remove(cleanRent.begin(), cleanRent.end(), ','), cleanRent.end());
  cleanRent.erase(remove(cleanRent.begin(), cleanRent.end(), 'R'), cleanRent.end());
  cleanRent.erase(remove(cleanRent.begin(), cleanRent.end(), 'M'), cleanRent.end());
  cleanRent.erase(remove_if(cleanRent.begin(), cleanRent.end(), [](char c) { return !isdigit(c) && c != '.'; }), cleanRent.end());
  if (cleanRent.empty()) {
    return 0;
  } else {
    return stod(cleanRent);
  }
}

// Function to parse size
double parseSize(const string& size) {
  string cleanSize = size;
  cleanSize.erase(remove_if(cleanSize.begin(), cleanSize.end(), [](char c) { return !isdigit(c) && c != '.'; }), cleanSize.end());
  return stod(cleanSize);
}

// Function to split a string by a delimiter
vector<string> split(const string& str, char delimiter) {
  vector<string> tokens;
  string token;
  istringstream tokenStream(str);
  while (getline(tokenStream, token, delimiter)) {
    tokens.push_back(token);
  }
  return tokens;
}

// Function to parse CSV line with quoted fields
vector<string> parseCSVLine(const string& line) {
  vector<string> result;
  string token;
  bool inQuotes = false;

  for (char c : line) {
    if (c == '"' && (token.empty() || token.back() != '\\')) {
      inQuotes = !inQuotes;
    } else if (c == ',' && !inQuotes) {
      result.push_back(token);
      token.clear();
    } else {
      token += c;
    }
  }

  result.push_back(token);
  return result;
}

// Function to read CSV file and store data in linked list
PropertyNode* readCSV(const string& filename) {
  ifstream file(filename);
  if (!file.is_open()) {
    cerr << "Failed to open file: " << filename << endl;
    return nullptr;
  }

  string line;
  PropertyNode* head = nullptr;
  PropertyNode* tail = nullptr;

  // Skip the header line
  getline(file, line);

  int count = 0;
  const int totalLines = 19990;

  while (getline(file, line)) {
    vector<string> tokens = parseCSVLine(line);
    if (tokens.size() < 14) continue;  // Ensure correct number of columns

    Property property;
    
    property.ads_id = stod(tokens[0]);
    property.prop_name = tokens[1];
    property.completion_year = tokens[2].empty() ? 0 : stoi(tokens[2]);
    property.monthly_rent = parseMonthlyRent(tokens[3]);
    property.location = tokens[4];
    property.property_type = tokens[5];
    property.rooms = tokens[6];
    property.parking = tokens[7].empty() ? 0 : stoi(tokens[7]);
    property.bathroom = tokens[8].empty() ? 0 : stoi(tokens[8]);
    property.size = parseSize(tokens[9]);
    property.furnished = tokens[10];

    property.facilities = split(tokens[11], ',');
    property.additional_facilities = split(tokens[12], ',');
    property.region = tokens[13];

    // Create a new PropertyNode
    PropertyNode* newPropertyNode = new PropertyNode{property, nullptr};

    // Insert the new PropertyNode into the linked list
    if (!head) {
      head = newPropertyNode;
      tail = newPropertyNode;
    } else {
      tail->next = newPropertyNode;
      tail = newPropertyNode;
    }

    cout << "Reading data: " << count << "/" << totalLines << endl;

    count++;
  }

  file.close();
  return head;
}