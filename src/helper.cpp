#include "helper.h"
#include "kd-tree.h"

/*
  read points from csv file
  @param filename the name of the file. It's a constant becouse the file must be "rff.csv".
  @returns a matrix of the points, in the form vector<vector<int>>
*/
std::vector<std::vector<int>> read_from_csv(std::string filename)
{
    std::ifstream csv_data(filename, std::ios::in);
    std::string line;
    if (!csv_data.is_open())
    {
        std::cout << "Error: opening file fail" << std::endl;
        std::exit(1);
    }
    std::string elem;
    std::vector<std::vector<int>> points;

    // read header
    std::getline(csv_data, line);
    // read data
    while (std::getline(csv_data, line))
    {
        // Read the entire line of string line into the string stream sin
        std::istringstream line_stream(line);
        std::vector<int> point;
        for(int i = 0;i<K;i++){
            unsigned i_elem;
            // Read the characters in the string stream sin into the elem string, separated by ", "
            getline(line_stream, elem, ',');
            // transfer string to int.
            i_elem = atoi(elem.c_str());
            // add into point.
            point.push_back(i_elem);
        }
    // add into points.
    points.push_back(point);
    }
    csv_data.close();
    return points;
}

// overload "<<" operator to make print-out easier
std::ostream& operator<<(std::ostream& os, const std::vector<int>& vec) {
  if (!vec.empty()) {
    os << "(";
    for (int i = 0; i < vec.size()-1; i++) {
      os << vec[i] << ", ";
    }
    os << vec.back();
    os << ")";
  }
  return os;
} 

/*convert a vector to a string with brackets on two sides
  @param vec the vector to be converted
  @returns the converted string
*/
std::string vecToStr(const std::vector<int>& vec) {
  std::string s = "";

  if (!vec.empty()) {
    s.push_back('(');
    for (int i = 0; i < vec.size() - 1; i++) {
      s.append(std::to_string(vec[i]) + ",");
    }
    s.append(std::to_string(vec.back()) + ")");
  }

  return s;
}