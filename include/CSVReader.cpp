#include "CSVReader.hpp"
#include <algorithm>

string CSVReader::removeQuotes(const string& input) {
    string result = input;
    result.erase(remove(result.begin(), result.end(), '\"'), result.end());
    return result;
}

// Lee un fichero CSV línea por línea, separando cada campo por comas
vector<vector<string>> CSVReader::readCSV(string filename) {
    vector<vector<string>> data;
    ifstream file(filename);
    string line;
    // Mientras podamos leer una línea completa, sigue el while 
    while (getline(file, line)) {
        stringstream lineStream(line);
        string cell;
        vector<string> rowData;

        while (getline(lineStream, cell, ',')) {
            rowData.push_back(removeQuotes(cell));
        }
        data.push_back(rowData);
    }

    file.close();
    return data;
}