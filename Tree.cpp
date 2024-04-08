#include <bits/stdc++.h>

using namespace std;

class Tree
{
protected:
     struct Node
     {
          int val;
          Node *r;
          Node *l;
          Node(int a) : val(a), r(nullptr), l(nullptr) {}
     };
     void printCallee(Node *n)
     {
          if (!n)
               return;
          printCallee(n->l);
          cout << n->val << " ";
          printCallee(n->r);
     }

     // delete's helper's
     Node *getGreatest(Node *s) // returns greatest pre/parent node
     {
          Node *preGreat = nullptr;
          while (s->r)
          {
               preGreat = s;
               s = s->r;
          }
          return preGreat;
     }
     // find tree's height helper
     int myHeight(Node *n)
     {
          if (!n)
               return 0;
          return 1 + max(myHeight(n->l), myHeight(n->r));
     }
     // root node
     Node *root;

public:
     Tree()
     {
          this->root = nullptr;
     }
     // insert function
     void add(int a)
     {
          Node *n = new Node(a);
          if (!root)
          {
               root = n;
               return;
          }
          Node *curr = root;
          while (true)
          {
               if (curr->val < a)
               {
                    if (!curr->r)
                    {
                         curr->r = n;
                         break;
                    }
                    curr = curr->r;
               }
               else
               {
                    if (!curr->l)
                    {
                         curr->l = n;
                         break;
                    }
                    curr = curr->l;
               }
          }
     }
     void print()
     {
          Node *curr = root;
          printCallee(curr);
     }
     // delete function
     void del(int key)
     {
          Node *pre = root;
          Node *curr = root;
          // this loop finds the node to be deleted and its pre/parent node
          while (true)
          {
               if (!curr || curr->val == key)
                    break;
               // this here works to find pre
               pre = curr;
               if (key > curr->val)
               {
                    curr = curr->r;
               }
               else
                    curr = curr->l;
          }
          // only if node is found and pre/parent exist delete can be performed
          if (curr && pre)
          {
               // if left 0 , if right 1
               int indiactor;
               // check for indicator
               if (pre->l && pre->l->val == curr->val) // checks whether the found node is
                    indiactor = 0;                     // to the left of pre/parent or not
               else                                    // if in left set 0 of 1 indicates it
                    indiactor = 1;                     // is in right

               // only with indicator we can decide whether to delete on left or on right of pre

               // the following if-else checks the nature of curr(node to be deleted)
               // whether it is leaf node(with no child) or with left or right child
               // or with both (where both goes in else)
               if (!curr->l && !curr->r) // if leaf node
               {
                    if (indiactor)
                    {
                         pre->r = nullptr;
                    }
                    else
                    {
                         pre->l = nullptr;
                    }
                    delete curr; // to free up memory and setting its hooks to null so no subtree is lost
               }
               else if (curr->l && !curr->r) // if node with left child
               {
                    if (indiactor)
                    {
                         pre->r = curr->l;
                    }
                    else
                    {
                         pre->l = curr->l;
                    }
                    curr->l = nullptr;
                    delete curr; // to free up memory and setting its hooks to null so no subtree is lost
               }
               else if (curr->r && !curr->l) // if node with right child
               {
                    if (indiactor)
                    {
                         pre->r = curr->r;
                    }
                    else
                    {
                         pre->l = curr->r;
                    }
                    curr->r = nullptr;
                    delete curr; // to free up memory and setting its hooks to null so no subtree is lost
               }
               else // a sub FBT(full balanced tree)
               {
                    // as we know that the successive node have to be choosen from
                    // right subtree or from left sub tree
                    // if choosing from right then choose minimum from right sub tree
                    // if choosing from left then choose max from left sub tree
                    // where "getGreatest" return pre of the greatest of left sub tree
                    // thus we have choosen left sub tree
                    Node *t1 = getGreatest(curr->l);
                    // if pre don't exist
                    // then curr in pre
                    if (!t1)
                    {
                         // as no pre is found curr in pre and only one value exist in it left sub tree
                         // thus replace curr value with is left node's value
                         // then set curr's left to curr->l->l to prevent if any on curr->l->l
                         curr->val = curr->l->val;
                         Node *toBeDeleted = curr->l; // tracking the replaced node for freeing up memory
                         curr->l = curr->l->l;        // setting curr->l->l if it's l is null or sub tree
                         toBeDeleted->l->l = nullptr;
                         delete toBeDeleted;
                         return;
                    }
                    // else change curr to pre's greatest which is at right
                    // then set pre's right to pre's->r->l to prevent if any(Sub tree) on l
                    curr->val = t1->r->val;    // setting t1->r->l if it's l is null or sub tree
                    Node *toBeDeleted = t1->r; // tracking the replaced node for freeing up memory
                    t1->r = t1->r->l;
                    toBeDeleted->r->l = nullptr; // setting it's l to null so that no other nodes are lost
                    delete toBeDeleted;          // deleting it
               }
               return;
          }
          // if no node is found
          cout
              << "Value not found" << endl;
     }
     void BFS() // BFS or level order traversal
     {
          Node *temp = this->root;
          queue<Node *> q;
          q.push(temp);
          while (!q.empty())
          {
               Node *t = q.front();
               q.pop();
               cout << t->val << " ";
               if (t->l)
                    q.push(t->l);
               if (t->r)
                    q.push(t->r);
          }
     }
     int height() // find the height of the tree
     {
          // calling helper(myHeight) to keep the invoke of this funtion simple
          return this->myHeight(this->root);
     }
};

int main()
{
     Tree t;
     t.add(5);
     t.add(3);
     t.add(2);
     t.add(4);
     t.add(8);
     t.add(7);
     t.add(6);
     t.add(12);
     t.add(10);
     t.add(13);
     t.add(9);
     // t.del(12);
     // cout << endl
     //      << "After delete" << endl;
     // t.print();
     // t.BFS();
     cout << t.height();
}

/*

 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left),
 * right(right) {}
 * };

class Solution
{
public:
     TreeNode *deleteNode(TreeNode *root, int key)
     {
          if (!root)
               return root;
          if (root->val == key)
          {
               if (!root->left && !root->right)
               {
                    root = nullptr;
               }
               else if (root->left && !root->right)
               {
                    root = root->left;
               }
               else if (!root->left && root->right)
               {
                    root = root->right;
               }
               else
               {
                    TreeNode *temp = nullptr;
                    TreeNode *f = root->right;
                    while (f->left)
                    {
                         temp = f;
                         f = f->left;
                    }
                    root->val = f->val;
                    if (!temp)
                    {
                         root->right = f->right;
                    }
                    else
                    {
                         temp->left = f->right;
                    }
               }
               return root;
          }
          TreeNode *pre = root;
          TreeNode *r = root;
          while (root && root->val != key)
          {
               pre = root;
               if (root->val <= key)
               {
                    root = root->right;
               }
               else
               {
                    root = root->left;
               }
          }
          if (!root)
               return r;
          bool is_l = false;
          if (pre->left && pre->left->val == root->val)
               is_l = true;
          if (!root->left && !root->right)
          {
               if (is_l)
               {
                    pre->left = nullptr;
               }
               else
               {
                    pre->right = nullptr;
               }
          }
          else if (root->left && !root->right)
          {
               if (is_l)
               {
                    pre->left = root->left;
               }
               else
               {
                    pre->right = root->left;
               }
          }
          else if (!root->left && root->right)
          {
               if (is_l)
               {
                    pre->left = root->right;
               }
               else
               {
                    pre->right = root->right;
               }
          }
          else
          {
               TreeNode *rpl = nullptr;
               TreeNode *temp = root->right;
               while (temp->left)
               {
                    rpl = temp;
                    temp = temp->left;
               }
               root->val = temp->val;
               if (!rpl)
               {
                    root->right = temp->right;
               }
               else
                    rpl->left = temp->right;
          }
          return r;
     }
};
* /