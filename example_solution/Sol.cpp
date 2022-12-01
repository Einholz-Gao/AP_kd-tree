#include <bits/stdc++.h>
using namespace std;

#define k 2

// A structure to represent node of kd tree
struct Node {
  int point[k]; // To store k dimensional point
  Node *left, *right;
};

// A method to create a node of K D tree
struct Node *newNode(int arr[]) {
  struct Node *temp = new Node;

  for (int i = 0; i < k; i++)
    temp->point[i] = arr[i];

  temp->left = temp->right = NULL;
  return temp;
}

// Inserts a new node and returns root of modified tree
// The parameter depth is used to decide axis of comparison
Node *insertRec(Node *root, int point[], unsigned depth) {
  // Tree is empty?
  if (root == NULL)
    return newNode(point);

  // Calculate current dimension (cd) of comparison
  unsigned cd = depth % k;

  // Compare the new point with root on current dimension 'cd'
  // and decide the left or right subtree
  if (point[cd] < (root->point[cd]))
    root->left = insertRec(root->left, point, depth + 1);
  else
    root->right = insertRec(root->right, point, depth + 1);

  return root;
}

// Function to insert a new point with given point in
// KD Tree and return new root. It mainly uses above recursive
// function "insertRec()"
Node *insert(Node *root, int point[]) { return insertRec(root, point, 0); }

// A utility method to determine if two Points are same
// in K Dimensional space
bool arePointsSame(int point1[], int point2[]) {
  // Compare individual pointinate values
  for (int i = 0; i < k; ++i)
    if (point1[i] != point2[i])
      return false;

  return true;
}

// Driver program to test above functions
int main() {
  struct Node *root = NULL;
  int points[][k] = {{3, 6}, {17, 15}, {13, 15}, {6, 12},
                     {9, 1}, {2, 7},   {10, 19}};

  int n = sizeof(points) / sizeof(points[0]);

  for (int i = 0; i < n; i++)
    root = insert(root, points[i]);

  return 0;
}
