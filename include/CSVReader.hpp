#ifndef CSVREADER_HPP
#define CSVREADER_HPP

#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

class CSVReader {
public:
    static string removeQuotes(const string& input);
    vector<vector<string>> readCSV(string filename);
};


#endif // CSVREADER_HPP