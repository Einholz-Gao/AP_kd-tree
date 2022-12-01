#include <iostream>
#include <vector>
#include <list>

#define K 2

struct Node {
  std::vector<int> data;
  Node *left = NULL, *right = NULL;
  
  Node(std::vector<int> vec) {
    data = vec;
  }

  Node() {}
};

void kd_insert(Node* node, std::vector<int>& point) {
  int cd = 0;
  bool inserted = false;
  while (!inserted) {
    // left branch
    if (point[cd] < node->data[cd]) {
      if (node->left == NULL) {
        node->left = new Node(point);
        inserted = true;
      }
      else {
        cd = (cd+1) % K;
        node = node->left;
      }
    }
    // right branch
    else if (point[cd] > node->data[cd]) {
      if (node->right == NULL) {
        node->right = new Node(point);
        inserted = true;
      }
      else {
        cd = (cd+1) % K;
        node = node->right;
      }
    }
    // point lies on an existed edge
    else {
      std::cout << "point overlap at dimension " << cd << std::endl;
      break;
    }
  }
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec) {
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

/*TODO: print-out example:
            (51,75)
       ________|________
       |               |
    (25,40)         (70,70)
   ____|____       ____|____
   |       |       |       |
(10,30) (35,90) (55,1) (60,80)
                   |____
                       |
                     (56, 30)
*/

void printKDTree(Node* node) {
  // int level = 0;
  
  

}

int main() {
  std::list<std::vector<int>> points = {{2, 5},
                                        {3, 8},
                                        {6, 3},
                                        {8, 9}};
  auto root_point = points.front();
  points.pop_front();
  // std::cout << "root_point = " << root_point[0] << " " << root_point[1] << std::endl;
  // std::cout << "points = " << std::endl;
  // for (auto& elem : points) {
  //   std::cout << elem[0] << ' ' << elem[1] << std::endl;
  // }
  
  Node root = Node(root_point);
  for (auto& point : points) {
    kd_insert(&root, point);
  }

  // printKDTree(&root);
  std::cout << vecToStr(std::vector<int> (6, 1));

  return 0;
}