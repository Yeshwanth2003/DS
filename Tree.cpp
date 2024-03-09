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
                         // then set curr's left to null
                         curr->val = curr->l->val;
                         if (curr->l->l) // whether the node has left subtree
                         {
                              curr->l = curr->l->l;
                              return;
                         }
                         curr->l = nullptr;
                         return;
                    }
                    // else change curr to pre's greatest which is at right
                    // then set pre's right to null
                    curr->val = t1->r->val;
                    if (t1->r->l) // whether the node has left subtree
                    {
                         t1->r = t1->r->l;
                         return;
                    }
                    t1->r = nullptr;
               }
               return;
          }
          // if no node is found
          cout
              << "Value not found" << endl;
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
     t.print();
     t.del(5);
     cout << endl
          << "After delete" << endl;
     t.print();
}