#include <iostream>
#include <filesystem>   // std::tr2::sys::path etc.
#include <fstream>

namespace sys = std::tr2::sys;

int main()
{
    std::cout << "Current path: " << sys::current_path() << std::endl;

    const sys::path filepath("assets/test.txt");
    std::ifstream ifs(filepath.string(), std::ios::in | std::ios::binary);
    if(ifs.fail()){
        std::cout << "Could not open file: " << filepath.filename().string() << std::endl;
        getchar();
        return 1;
    }
    std::string field;
    while(std::getline(ifs, field)){
        std::cout << field << std::endl;
    }
    std::cout << "Succeeded." << std::endl;
    getchar();
    return 0;
}