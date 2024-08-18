#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <vector>
#include <algorithm>

// Class to represent a date
class Date {
public:
    Date() : day(0), month(0), year(0) {}
    Date(int day, int month, int year) : day(day), month(month), year(year) {}
    Date(const std::string& date_str) {
        std::istringstream ss(date_str);
        char delimiter;
        ss >> day >> delimiter >> month >> delimiter >> year;
    }

    // Getter and setter methods for day, month, and year
    int getDay() const { return day; }
    void setDay(int day) { this->day = day; }
    int getMonth() const { return month; }
    void setMonth(int month) { this->month = month; }
    int getYear() const { return year; }
    void setYear(int year) { this->year = year; }

    // Method to convert Date object to string
    std::string toString() const {
        return std::to_string(day) + "/" + std::to_string(month) + "/" + std::to_string(year);
    }

private:
    int day;
    int month;
    int year;
};

// Class to represent a time
class Time {
public:
    Time() : hour(0), minute(0) {}
    Time(int hour, int minute) : hour(hour), minute(minute) {}
    Time(const std::string& time_str) {
        std::istringstream ss(time_str);
        char delimiter;
        ss >> hour >> delimiter >> minute;
    }

    // Getter and setter methods for hour and minute
    int getHour() const { return hour; }
    void setHour(int hour) { this->hour = hour; }
    int getMinute() const { return minute; }
    void setMinute(int minute) { this->minute = minute; }

    // Method to convert Time object to string
    std::string toString() const {
        std::string hour_str = (hour < 10) ? "0" + std::to_string(hour) : std::to_string(hour);
        std::string minute_str = (minute < 10) ? "0" + std::to_string(minute) : std::to_string(minute);
        return hour_str + ":" + minute_str;
    }

private:
    int hour;
    int minute;
};

// Struct to hold wind, temperature, and solar data for a specific date and time
struct WindTempSolar {
    Date date;
    Time time;
    float wind_speed;
    float temperature;
    float solar_radiation;
};

// Typedef for vector of WindTempSolar structs
typedef std::vector<WindTempSolar> WindTempSolarData;

// Function to calculate average wind speed from data
float calculateAverageWindSpeed(const WindTempSolarData& data) {
    float sum = 0;
    for (const auto& record : data) {
        sum += record.wind_speed;
    }
    return sum / data.size();
}

// Function to calculate average ambient temperature from data
float calculateAverageAmbientTemperature(const WindTempSolarData& data) {
    float sum = 0;
    for (const auto& record : data) {
        sum += record.temperature;
    }
    return sum / data.size();
}

// Function to calculate average solar radiation from data
float calculateAverageSolarRadiation(const WindTempSolarData& data) {
    float sum = 0;
    for (const auto& record : data) {
        sum += record.solar_radiation;
    }
    return sum / data.size();
}

// Function to print data to a file
void printDataToFile(const std::string& filename, const std::string& data) {
    std::ofstream outFile(filename);
    if (outFile.is_open()) {
        outFile << data;
        outFile.close();
        std::cout << "Data has been written to " << filename << std::endl;
    } else {
        std::cerr << "Unable to open file " << filename << " for writing." << std::endl;
    }
}

// Main function
int main() {
    WindTempSolarData data;

    // Read data from file
    std::ifstream file("data/MetData_Mar01-2014-Mar01-2015-ALL.csv");
    if (file.is_open()) {
        std::string line;
        std::getline(file, line); // Skip the header line

        // Parse each line of the file
        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string date, time;
            float wind_speed, temperature, solar_radiation;

            // Extract data from the line
            std::getline(ss, date, ',');
            std::getline(ss, time, ',');
            ss >> wind_speed;
            ss.ignore(); // Ignore the comma
            ss >> temperature;
            ss.ignore(); // Ignore the comma
            ss >> solar_radiation;

            // Create WindTempSolar record and add it to the data vector
            WindTempSolar record = {Date(date), Time(time), wind_speed, temperature, solar_radiation};
            data.push_back(record);
        }
        file.close();
    } else {
        std::cerr << "Unable to open file" << std::endl;
        return 1;
    }

    int choice;
    do {
        // Display menu
        std::cout << "Menu:\n"
                  << "1. Average Wind Speed\n"
                  << "2. Average Ambient Temperature\n"
                  << "3. Average Solar Radiation\n"
                  << "4. Average Wind Speed and print to file\n"
                  << "5. Exit\n"
                  << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                // Calculate and display average wind speed
                std::cout << "Average Wind Speed: " << calculateAverageWindSpeed(data) << std::endl;
                break;
            case 2:
                // Calculate and display average ambient temperature
                std::cout << "Average Ambient Temperature: " << calculateAverageAmbientTemperature(data) << std::endl;
                break;
            case 3:
                // Calculate and display average solar radiation
                std::cout << "Average Solar Radiation: " << calculateAverageSolarRadiation(data) << std::endl;
                break;
            case 4: {
                // Calculate average wind speed and print it to a file
                float avgWindSpeed = calculateAverageWindSpeed(data);
                std::stringstream windData;
                windData << "Average Wind Speed: " << avgWindSpeed << std::endl;
                std::string filename = "AverageWindSpeed.csv";
                printDataToFile(filename, windData.str());
                break;
            }
            case 5:
                std::cout << "Exiting program." << std::endl;
                break;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
        }
    } while (choice != 5);

    return 0;
}
