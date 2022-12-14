#include <iostream>
#include <vector>
#include <list>

#include<sstream>
#include<fstream>
#include <iomanip>

#define K 3

// define a Node struct
struct Node {
  std::vector<int> data;
  Node *left = NULL, *right = NULL;

  Node(std::vector<int> vec) {
    data = vec;
  }

  Node() {}
};

/*
  read points from csv file
  @param filename the name of the file. It's a constant becouse the file must be "rff.csv".
*/
std::vector<std::vector<int>> read_from_csv( std::string filename="rff.csv")
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

/*
  Finds the smallest node of three nodes
  @param x the 1st node
  @param y the 2nd node
  @param z the 3rd node
  @param d the dimension of the smallest value you want to find(d'th dimension in KD tree)
*/
Node *minNode(Node* x, Node* y, Node* z, int d)
{
    Node* res = x;
    if (y != NULL && y->data[d] < res->data[d])
       res = y;
    if (z != NULL && z->data[d] < res->data[d])
       res = z;
    return res;
}
/*
  Recursively finds minimum of d'th dimension in KD tree
  @param node the root node of the tree or sub-tree
  @param d the dimension of the smallest value you want to find(d'th dimension in KD tree)
  @param depth the current depth(x,y,or z...) of the tree
*/
Node *findMin(Node* node, unsigned d, unsigned depth)
{
    if (node == NULL)
        return NULL;

    // cd -> current dimention
    unsigned cd = depth % K;

    // Compare point with node with respect to cd (Current dimension)
    if (cd == d)
    {
        if (node->left == NULL)
            return node;
        return findMin(node->left, d, depth+1);
    }
    else
    return minNode(node,
               findMin(node->left, d, depth+1),
               findMin(node->right, d, depth+1), d);
}

/*delete point to a kd-tree
  @param node the root node of the tree or sub-tree
  @param point the point to be inserted
  @param depth the current depth(dimension) of the tree
*/
Node *kd_delete(Node* node, std::vector<int> point, int depth)
{
    // Given point is not present
    if (node == NULL)
        return NULL;

    // Find dimension of current node
    int cd = depth % K;

    // If the point to be deleted is present at root
    if (node->data == point)
    {
        // If right subtree is not NULL
        if (node->right != NULL)
        {
            // Find minimum of root's dimension in right subtree
            Node *min = findMin(node->right, cd, 0);

            // Copy the minimum to node
            for (int i=0; i<K; i++)
                node->data[i] = min->data[i];

            // swap subtrees and use min(cd) from new right tree.
            node->right = kd_delete(node->right, min->data, depth+1);
        }
        // If the left is not NULL
        else if (node->left != NULL)
        {
            Node *min = findMin(node->left, cd, 0);
            for (int i=0; i<K; i++)
                node->data[i] = min->data[i];
            node->left = kd_delete(node->left, min->data, depth+1);
        }
        else // If node to be deleted is leaf node
        {
            delete node;
            return NULL;
        }
        return node;
    }

    // This is not the point:
    if (point[cd] < node->data[cd])
        node->left = kd_delete(node->left, point, depth+1);
    else
        node->right = kd_delete(node->right, point, depth+1);
    return node;
}

/*insert point to a kd-tree
  @param node the root node of the tree or sub-tree
  @param point the point to be inserted
*/
void kd_insert(Node* node, std::vector<int>& point) {
  int cd = 0;  // cutting dimension
  bool inserted = false;  // a flag indicating if insertion is completed
  while (!inserted) {
    // left branch
    if (point[cd] < node->data[cd]) {
      // if the left branch of the node is empty
      // insert the point to that branch
      if (node->left == NULL) {
        node->left = new Node(point);
        inserted = true;
      }
      // if not, then inspect the left branch in next iteration
      else {
        cd = (cd+1) % K;
        node = node->left;
      }
    }
    // right branch
    else if (point[cd] > node->data[cd]) {
      // if the right branch of the node is empty
      // insert the point to that branch
      if (node->right == NULL) {
        node->right = new Node(point);
        inserted = true;
      }
      // if not, then inspect the right branch in next iteration
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

// overload "<<" operator to make print-out easier
//template <typename T>
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

// convert a vector to a string
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

  Node root = Node(root_point);
  for (int i = 1; i < points.size(); i++) {
    kd_insert(&root, points[i]);
  }

  printKDTree(&root);

  std::vector<int> del_point = {1, 4, 5};
  Node *del_root = kd_delete(&root, del_point, 0);

  std::cout << "after deletion of point: " << del_point << std::endl;
  printKDTree(del_root);
  return 0;
}
