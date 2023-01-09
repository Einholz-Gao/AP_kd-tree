#include "src/kd-tree.h"
#include "src/helper.h"

int main() {
  // std::list<std::vector<int>> points = {{2, 5, 0},
  //                                       {3, 8, -1},
  //                                       {6, 3, -2},
  //                                       {8, 9, -5},
  //                                       {1, 4, 5},
  //                                       {0, 3, 7},
  //                                       {-3, 5, 11},
  //                                       {-2, 10, -6}};

  std::vector<std::vector<int>> points = read_from_csv();
  auto root_point = points.front();

  std::shared_ptr<Node> root = std::make_shared<Node>(root_point);
  KD_Tree kd_tree = KD_Tree(root);
  for (auto const& pt : points) {
    kd_tree.kd_insert(root, pt);
  }

  kd_tree.printKDTree();

  std::vector<int> del_point = {1, 4, 5};
  std::shared_ptr<Node> del_root = kd_tree.kd_delete(root, del_point, 0);

  std::cout << "after deletion of point: " << del_point << std::endl;
  kd_tree.printKDTree();
  return 0;
}
