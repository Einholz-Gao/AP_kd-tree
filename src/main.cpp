#include <cstddef>
#include <iostream>
#include <vector>
#include <list>

#define K 3

struct Node {
  std::vector<int> data;
  Node *left = NULL, *right = NULL;
  
  Node(std::vector<int> vec) {
    data = vec;
  }

  Node() {}
};

std::vector<int> findmin(Node* node, int dim, int cd){
  if (node == NULL) std::cout << "node is NULL!" << std::endl;
  if (cd == dim){
    // current dim = dim, left subtree is the smaller.
    if (node->left == NULL) return node->data;
    else return findmin(node->left, dim, (cd+1) % K);
  }
  else{
    // current dim != dim, we must compare two subtrees.
    if (findmin(node->left, dim, (cd+1) % K) <findmin(node->right, dim, (cd+1) % K))
      return node->left->data;
    else
      return node->right->data;
  }
}

void kd_delete(Node* node, std::vector<int>& point, int cd){

  if (node == NULL){
    std::cout << "point not found!" << std::endl;
  }
  int next_cd = (cd+1) % K;
    // left branch
    if (point == node->data){
      // if the node is to delete
      if (node->left != NULL){
        node->data = findmin(node->left, cd, next_cd);
        kd_delete(node->left, node->data, next_cd);
      }
      else if (node->right != NULL){
        node->data = findmin(node->right, cd, next_cd);
        kd_delete(node->right, node->data, next_cd);
      }
      else {
        node = NULL;
        // this is a leaf, can be removed.
      }
    }
    else{
      // if the node is not to delete
      if (point[cd] < node->data[cd]) {
        kd_delete(node->left, point, next_cd);
        }
      else {
        kd_delete(node->right, point, next_cd);
        }
    }
}



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

/* print-out example:
       /-----(8, 9)
/-----(3, 8)
|      \-----(6, 3)
(2, 5)
|             /-----(-2, 10)
|      /-----(-3, 5)
\-----(1, 4)
       \-----(0, 3)
*/
void printKDTreeBranches(Node* node, bool left, const std::string& prefix) {
  if (node->right) {
    printKDTreeBranches(node->right, false, prefix + (left? "|      " : "       "));
  }
  std::cout << prefix;
  std::cout << (left? '\\' : '/');
  std::cout << "-----";
  std::cout << node->data << std::endl;
  if (node->left) {
    printKDTreeBranches(node->left, true, prefix + (left? "       " : "|      "));
  }
}

void printKDTree(Node* root) {
  if (root->right) {
    printKDTreeBranches(root->right, false, "");
  }
  std::cout << root->data << std::endl;
  if (root->left) {
    printKDTreeBranches(root->left, true, "");
  }
}

/*TODO: another print-out example:
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

int main() {
  std::list<std::vector<int>> points = {{2, 5, 0},
                                        {3, 8, -1},
                                        {6, 3, -2},
                                        {8, 9, -5},
                                        {1, 4, 5},
                                        {0, 3, 7},
                                        {-3, 5, 11},
                                        {-2, 10, -6}};
  auto root_point = points.front();
  points.pop_front();
  
  Node root = Node(root_point);
  for (auto& point : points) {
    kd_insert(&root, point);
  }

  // std::cout << vecToStr(std::vector<int> (6, 1));
  printKDTree(&root);
  auto del_p = points.end();
  kd_delete(&root, root_point, 0);
  return 0;
}
