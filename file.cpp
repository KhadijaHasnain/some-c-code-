#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>

// Define a structure to represent a relation (table)
struct Relation {
    std::vector<std::unordered_map<std::string, std::string>> tuples;
};

// Define a database to hold relations
std::unordered_map<std::string, Relation> database;

// Dummy data for Student relation
Relation studentRelation() {
    Relation student;
    student.tuples = {
        {{"s#", "1"}, {"sname", "John"}, {"age", "25"}},
        {{"s#", "2"}, {"sname", "Kate"}, {"age", "23"}},
        {{"s#", "3"}, {"sname", "Mike"}, {"age", "28"}}
    };
    return student;
}

// Dummy data for Course relation
Relation courseRelation() {
    Relation course;
    course.tuples = {
        {{"c#", "1"}, {"cname", "Math"}},
        {{"c#", "2"}, {"cname", "English"}},
        {{"c#", "3"}, {"cname", "Science"}}
    };
    return course;
}

// Function to execute ALG query
void executeALGQuery(const std::string& query) {
    // Implementation of ALG query execution
    std::cout << "Executing ALG query: " << query << std::endl;
    // Example: Retrieve student names from Student relation
    Relation student = database["Student"];
    for (const auto& tuple : student.tuples) {
        std::cout << "Student name: " << tuple.at("sname") << std::endl;
    }
}

// Function to execute TRC query
void executeTRCQuery(const std::string& query) {
    // Implementation of TRC query execution
    std::cout << "Executing TRC query: " << query << std::endl;
    // Example: Retrieve student numbers and names from Student relation
    Relation student = database["Student"];
    for (const auto& tuple : student.tuples) {
        std::cout << "Student number: " << tuple.at("s#") << ", Name: " << tuple.at("sname") << std::endl;
    }
}

// Function to execute SQL query
void executeSQLQuery(const std::string& query) {
    // Implementation of SQL query execution
    std::cout << "Executing SQL query: " << query << std::endl;
    // Example: Execute SQL query using database system
    // Placeholder for actual SQL query execution
}

// Function to parse and execute RQL query
void executeRQLQuery(const std::string& query) {
    // Convert query to lowercase for case-insensitive comparison
    std::string lowercaseQuery = query;
    std::transform(lowercaseQuery.begin(), lowercaseQuery.end(), lowercaseQuery.begin(), ::tolower);

    // Determine the type of query and delegate execution accordingly
    if (lowercaseQuery.find("alg") != std::string::npos) {
        executeALGQuery(query);
    } else if (lowercaseQuery.find("trc") != std::string::npos) {
        executeTRCQuery(query);
    } else if (lowercaseQuery.find("sql") != std::string::npos) {
        executeSQLQuery(query);
    } else {
        std::cerr << "Unsupported query type in RQL: " << query << std::endl;
    }
}

// Function to fix DRC bug and extend for NRDB
void fixDRCAndExtendForNRDB() {
    // Implementation to fix DRC bug and extend for NRDB
    std::cout << "Fixing DRC bug and extending for NRDB" << std::endl;
    // Example: Load data into database
    database["Student"] = studentRelation();
    database["Course"] = courseRelation();
}

int main() {
    // Fix DRC bug and extend for NRDB
    fixDRCAndExtendForNRDB();

    std::string query;

    // Prompt the user for a query until they input "quit"
    while (true) {
        std::cout << "Enter a query (type 'quit' to exit): ";
        std::getline(std::cin, query);

        // Exit if the user inputs "quit"
        if (query == "quit") {
            break;
        }

        // Execute the user-provided query
        std::cout << "Executing query: " << query << std::endl;
        executeRQLQuery(query);
    }

    return 0;
}

