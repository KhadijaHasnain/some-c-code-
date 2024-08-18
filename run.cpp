#include <iostream>
#include <valarray>


//QUESTION 1:

//PART A

class Run {
public:
    double t_start;
    double t_end;
    int duration;
    double distance;
    std::valarray<double> t_data;
    std::valarray<double> lat_data;
    std::valarray<double> lon_data;

Run(double t_s) : t_start(t_s) {
    startRun();
}

void startRun() {}
void pauseRun() {}
void endRun() {}

void printRunInfo() {
     std::cout << "Run Data:" <<std::endl;
     std::cout << "Beginning Time:" << t_start << "seconds" << std::endl;
     std::cout << "Completion Time:" << t_end << "seconds" << std::endl;
     std::cout << "Duration:" << duration << "seconds" << std::endl;
     std::cout << "Distance:" << distance << "meters" << std::endl;
}

double get_avg_pace() {
    return 0.0;
}

double get_fastest_pace() {
    return 0.0;
}
};


//DO NOT NEED FOR FINAL
               
int main() {
    Run myRun(1704067200.0); // Example start time
    myRun.endRun(); // End the run to set the end time and duration
    myRun.printRunInfo(); // Output the run info

    // Display pace information
    std::cout << "Average Pace: " << myRun.get_avg_pace() << " min/km" << std::endl;
    std::cout << "Fastest Pace: " << myRun.get_fastest_pace() << " min/km" << std::endl;

    return 0;
}    
