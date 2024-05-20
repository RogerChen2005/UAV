#include <iostream>
#include <fstream>
#include <matrix.h>

int speed = 2;

int main()
{
    matrix m(2000, 1000, 20, 30, 10);
    m.cut([](int x)
          { return x * 0.3; }, [](int x)
          { return 0; });
    m.cut([](int x)
          { return 2000; }, [](int x)
          { return 1000 - (x - 1000) * 0.7; });
    int original_area = m.calculate_coverage();
    m.addDrone();
    m.addDrone({500, 500});
    m.addDrone({1000, 200});
    std::vector<double> coverages;
    std::string filepath = "./output/";
    std::string ext = ".bmp";
    for (int i = 0; i < 21; i++)
    {
        int final_area = m.step_forward(100);
        std::string filename = std::to_string(i);
        std::string fullpath = filepath+filename+ext;
        std::cout << fullpath << std::endl;
        m.output(fullpath.c_str());
        coverages.push_back(1.0 - 1.0 * final_area / original_area);
    }
    std::ofstream file("./output/data.txt", std::ios::out);
    if (!file) {
        std::cerr << "Error occured when writing file." << std::endl;
        return 1;
    }
    int length = coverages.size();
    for(int i = 0;i<length;i++){
        file << coverages[i] << std::endl;
    }
    file.close();
    return 0;
}