#include "stack.h"

#include <iostream>
#include <spdlog/spdlog.h>

#include "Calculator.h"
int main() {

    spdlog::set_level(spdlog::level::err);

    while (true) {
        std::cout<<"Enter expression: \n";
        std::string input;
        std::cin >> input;
        Calculator calculatorDevice;
        try {
            std::cout<<calculatorDevice.processString(input)<<'\n';
        } catch (const std::exception& e) {
            spdlog::error("Exception occured: {}", e.what());
            std::cout<<'\n';

        }
    }
}
