#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <sstream>
using namespace std;

// Simple JSON parser - parses a flat JSON object with string values
// Example: {"name": "John", "age": "30", "city": "NYC"}
map<string, string> parseJsonObject(const string& json) {
    map<string, string> result;
    string s = json;
    
    // Remove whitespace, braces
    size_t start = s.find('{');
    size_t end = s.rfind('}');
    if (start == string::npos || end == string::npos) return result;
    
    s = s.substr(start + 1, end - start - 1);
    
    // Parse key-value pairs
    size_t pos = 0;
    while (pos < s.length()) {
        // Find key
        size_t keyStart = s.find('"', pos);
        if (keyStart == string::npos) break;
        size_t keyEnd = s.find('"', keyStart + 1);
        if (keyEnd == string::npos) break;
        string key = s.substr(keyStart + 1, keyEnd - keyStart - 1);
        
        // Find colon
        size_t colon = s.find(':', keyEnd);
        if (colon == string::npos) break;
        
        // Find value
        size_t valStart = s.find('"', colon);
        if (valStart == string::npos) break;
        size_t valEnd = s.find('"', valStart + 1);
        if (valEnd == string::npos) break;
        string value = s.substr(valStart + 1, valEnd - valStart - 1);
        
        result[key] = value;
        pos = valEnd + 1;
    }
    
    return result;
}

// Convert map to JSON string
string toJsonString(const map<string, string>& data) {
    string json = "{\n";
    bool first = true;
    for (const auto& pair : data) {
        if (!first) json += ",\n";
        json += "  \"" + pair.first + "\": \"" + pair.second + "\"";
        first = false;
    }
    json += "\n}";
    return json;
}

// Read and parse JSON from file
map<string, string> readJsonFromFile(const string& filename) {
    string content = "";
    ifstream inFile(filename);
    
    if (inFile.is_open()) {
        string line;
        while (getline(inFile, line)) {
            content += line;
        }
        inFile.close();
    } else {
        cerr << "Error: Unable to open JSON file: " << filename << endl;
    }
    
    return parseJsonObject(content);
}

// Write map as JSON to file
void writeJsonToFile(const string& filename, const map<string, string>& data) {
    ofstream outFile(filename);
    if (outFile.is_open()) {
        outFile << toJsonString(data);
        outFile.close();
        cout << "Successfully wrote JSON to " << filename << endl;
    } else {
        cerr << "Error: Unable to open file for writing: " << filename << endl;
    }
}

// Write content to a file
void writeToFile(string& filename, string& content){
    ofstream ofs(filename);
    if(ofs.is_open()){
        ofs<<content;
        ofs.close();
        cout<<"file write sucessful!"<<endl;
    } else {
        cout<<"file is closed!"<<endl;
    }
}

// Read content from a file
string readFromFile(const string& filename) {
    ifstream inFile(filename);
    string content;
    
    if (inFile.is_open()) {
        string line;
        while (getline(inFile, line)) {
            content += line + "\n";
        }
        inFile.close();
    } else {
        cerr << "Error: Unable to open file for reading: " << filename << endl;
    }
    
    return content;
}

// Tester method to demonstrate file I/O
void tester() {
    string filename = "test_io.txt";
    string testContent = "Hello, World!\nThis is a test file.\nLine 3 of the file.";
    
    // Write to file
    cout << "Writing to file..." << endl;
    writeToFile(filename, testContent);
    
    // Read from file
    cout << "\nReading from file..." << endl;
    string readContent = readFromFile(filename);
    
    cout << "Content read from file:\n" << readContent << endl;
    
    // JSON test
    cout << "\n--- JSON Test ---" << endl;
    
    // Create and write JSON
    map<string, string> person;
    person["name"] = "John Doe";
    person["age"] = "30";
    person["city"] = "New York";
    person["email"] = "john@example.com";
    
    string jsonFile = "test_data.json";
    writeJsonToFile(jsonFile, person);
    
    // Read and parse JSON
    cout << "\nReading JSON from file..." << endl;
    map<string, string> parsed = readJsonFromFile(jsonFile);
    
    cout << "Parsed JSON contents:" << endl;
    for (const auto& pair : parsed) {
        cout << "  " << pair.first << ": " << pair.second << endl;
    }
}

int main() {
    tester();
    return 0;
}
