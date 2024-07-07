#pragma once
#include "import.h"

using namespace std;

class csvReader {
public:
    // Constructor
    csvReader(const string& filename) {
        this->filename = filename;
    }

    // Function to read CSV file and return linked list of properties
    PropertyNode* readCSV() {
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
            if (tokens.size() < 14) {
                continue;
            }

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
            property.facilities_size = split(tokens[11], ',', property.facilities);
            property.additional_facilities_size = split(tokens[12], ',', property.additional_facilities);
            property.region = tokens[13];

            PropertyNode* newPropertyNode = new PropertyNode{ property, nullptr };

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

    void writePropertiesToCSV(PropertyNode* properties, const string& filename) {
        ofstream outFile(filename);

        if (!outFile.is_open()) {
            cerr << "Error opening file " << filename << " for writing." << endl;
            return;
        }

        // Write CSV header
        outFile << "ads_id,prop_name,completion_year,monthly_rent,location,property_type,rooms,parking,bathroom,size,furnished,facilities,additional_facilities,region" << endl;

        // Write each property
        PropertyNode* current = properties;
        while (current != nullptr) {
            Property prop = current->property;
            outFile << fixed << setprecision(0) << prop.ads_id << ","
                    << "\"" << prop.prop_name << "\","
                    << prop.completion_year << ","
                    << prop.monthly_rent << ","
                    << "\"" << prop.location << "\","
                    << "\"" << prop.property_type << "\","
                    << "\"" << prop.rooms << "\","
                    << (prop.parking ? "true" : "false") << ","
                    << prop.bathroom << ","
                    << prop.size << ","
                    << "\"" << prop.furnished << "\","
                    << "\"";
            
            // Writing facilities
            for (size_t i = 0; i < prop.facilities_size; ++i) {
                outFile << prop.facilities[i];
                if (i < prop.facilities_size - 1)
                    outFile << ",";
            }
            outFile << "\",";

            // Writing additional facilities
            outFile << "\"";
            for (size_t i = 0; i < prop.additional_facilities_size; ++i) {
                outFile << prop.additional_facilities[i];
                if (i < prop.additional_facilities_size - 1)
                    outFile << ",";
            }
            outFile << "\",";

            outFile << "\"" << prop.region << "\"" << endl;

            current = current->next;
        }

        outFile.close();
    }

private:
    string filename;

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

    // function to parse monthly rent to remove the RM and spaces
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

    // Function to split a string by a delimiter and store in a dynamic array
    size_t split(const string& str, char delimiter, string*& outArray) {
        vector<string> tokens;
        string token;
        istringstream tokenStream(str);
        while (getline(tokenStream, token, delimiter)) {
            tokens.push_back(token);
        }

        outArray = new string[tokens.size()];
        for (size_t i = 0; i < tokens.size(); ++i) {
            outArray[i] = tokens[i];
        }

        return tokens.size();
    }
};
