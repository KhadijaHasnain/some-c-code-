#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>

class Date {
public:
    Date() : day(0), month(0), year(0) {}
    Date(int day, int month, int year) : day(day), month(month), year(year) {}
    Date(const std::string& date_str) {
        std::istringstream ss(date_str);
        char delimiter;
        ss >> day >> delimiter >> month >> delimiter >> year;
    }

    int getDay() const { return day; }
    void setDay(int day) { this->day = day; }

    int getMonth() const { return month; }
    void setMonth(int month) { this->month = month; }

    int getYear() const { return year; }
    void setYear(int year) { this->year = year; }

    std::string toString() const {
        return std::to_string(day) + "/" + std::to_string(month) + "/" + std::to_string(year);
    }

private:
    int day;
    int month;
    int year;
};

class Time {
public:
    Time() : hour(0), minute(0) {}
    Time(int hour, int minute) : hour(hour), minute(minute) {}
    Time(const std::string& time_str) {
        std::istringstream ss(time_str);
        char delimiter;
        ss >> hour >> delimiter >> minute;
    }

    int getHour() const { return hour; }
    void setHour(int hour) { this->hour = hour; }

    int getMinute() const { return minute; }
    void setMinute(int minute) { this->minute = minute; }

    std::string toString() const {
        std::string hour_str = (hour < 10) ? "0" + std::to_string(hour) : std::to_string(hour);
        std::string minute_str = (minute < 10) ? "0" + std::to_string(minute) : std::to_string(minute);
        return hour_str + ":" + minute_str;
    }

private:
    int hour;
    int minute;
};

template<typename T>
class Vector {
public:
    Vector() : elements(nullptr), capacity(0), num_elements(0) {}
    Vector(const Vector<T>& other) : capacity(other.capacity), num_elements(other.num_elements) {
        elements = new T[capacity];
        for (int i = 0; i < num_elements; ++i) {
            elements[i] = other.elements[i];
        }
    }
    ~Vector() { delete[] elements; }

    void push_back(const T& element) {
        if (num_elements == capacity) {
            int new_capacity = (capacity == 0) ? 1 : capacity * 2;
            T* new_elements = new T[new_capacity];
            for (int i = 0; i < num_elements; ++i) {
                new_elements[i] = elements[i];
            }
            delete[] elements;
            elements = new_elements;
            capacity = new_capacity;
        }
        elements[num_elements++] = element;
    }
    void pop_back() {
        if (num_elements > 0) {
            --num_elements;
        }
    }
    T& operator[](int index) { return elements[index]; }
    const T& operator[](int index) const { return elements[index]; }
    int size() const { return num_elements; }

private:
    T* elements;
    int capacity;
    int num_elements;
};

typedef struct {
    Date d;
    Time t;
    float speed;
} WindRecType;

typedef Vector<WindRecType> WindlogType;

int main() {
    WindlogType wind_data;

    std::ifstream file("data/MetData_Mar01-2014-Mar01-2015-ALL.csv");
    if (file.is_open()) {
        std::string line;
        std::getline(file, line); // Skip the header line

        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string date, time;
            float speed;

            std::getline(ss, date, ',');
            std::getline(ss, time, ',');
            ss >> speed;

            Date d(date);
            Time t(time);

            WindRecType record = {d, t, speed};
            wind_data.push_back(record);
        }
        file.close();
    } else {
        std::cerr << "Unable to open file" << std::endl;
        return 1;
    }

    float sum = 0;
    for (int i = 0; i < wind_data.size(); i++) {
        sum += wind_data[i].speed;
    }
    float average_speed = sum / wind_data.size();

    float variance = 0;
    for (int i = 0; i < wind_data.size(); i++) {
        variance += pow(wind_data[i].speed - average_speed, 2);
    }
    float sample_sd = sqrt(variance / (wind_data.size() - 1));

    average_speed *= 3.6;
    sample_sd *= 3.6;

    std::cout << "Average wind speed: " << average_speed << " km/h" << std::endl;
    std::cout << "Sample standard deviation: " << sample_sd << " km/h" << std::endl;

    for (int i = 0; i < wind_data.size(); i++) {
        if (std::abs(wind_data[i].speed - average_speed / 3.6) < 0.0001) {
            std::cout << "Matching speed found at: " << wind_data[i].d.toString() << " " << wind_data[i].t.toString() << std::endl;
        }
    }

    return 0;
}
