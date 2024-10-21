#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

std::vector<std::string> read(const std::string& file) {
    std::ifstream data(file);
    std::vector<std::string> balls;

    if (!data) {
        std::cerr << "Failed to open file" << std::endl;
    } else {
        std::string line;
        while (std::getline(data, line)) {
            balls.push_back(line);
        }
        data.close();
    }
    
    return balls;
}

std::vector<std::vector<float>> convert(const std::vector<std::string>& balls) {
    std::vector<std::vector<float>> convertedBalls;
    
    for (const auto& line : balls) {
        std::vector<float> numbers;
        std::istringstream stream(line);
        float number;
        
        while (stream >> number) {
            std::cout << number;
            numbers.push_back(number);
        }
        
        convertedBalls.push_back(numbers);
    }
    
    return convertedBalls;
}

std::vector<std::vector<float>> parse(const std::string& file) { return convert(read(file)); }