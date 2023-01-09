#include <iostream>
#include <vector>

#include<sstream>
#include<fstream>
#include <iomanip>

#define K 3

std::vector<std::vector<int>> read_from_csv(std::string filename="data/points.csv");

std::ostream& operator<<(std::ostream& os, const std::vector<int>& vec);

std::string vecToStr(const std::vector<int>& vec);

