#include <bits/stdc++.h>

using namespace std;

// Implementation of MAX heap;

class Heap
{
private:
     // this holds the heap array
     vector<int> heap;
     // this is the most general heapify function that is used across the programm
     void heapify(int i, int limit, int size)
     {
          //  this function gets i the position to heapify,
          // limit untill the last parent,and size of the array
          while (i <= limit)
          {
               // a and b are set to get two childs
               int a = (2 * i) + 1;
               int b = (2 * i);
               // following operation is set to perform
               // finding greatest of three number in indexes
               // i,a,b(parent,two child)
               int largest = i;
               if (a<size &&this->heap[a]> this->heap[largest])
                    largest = a;
               if (b<size &&this->heap[b]> this->heap[largest])
                    largest = b;
               if (largest != i)
               {
                    swap(this->heap[i], this->heap[largest]);
                    i = largest;
               }
               // untill here, if largest is found then swap it and
               // set i to its current position where it got swapped
               // if there exist no change in largest, then break
               else
                    break;
          }
     }

public:
     // this constructor is ment to handle creation of new heap from scratch
     Heap()
     {
          cout << "Heap is Ready" << endl;
     }
     // this constructor get a lst and heapify it
     Heap(vector<int> lst)
     {
          // every parent element are found and heapified
          int s = lst.size() - 1;
          int limit = floor(s / 2);
          this->heap = lst;
          // this loop iterate to every parent
          for (int i = limit; i >= 0; i--)
          {
               this->heapify(i, limit, this->heap.size());
          }
     }

     void insert(int a)
     {
          // as we know that every new element is inserted at the end
          //  in the beginning
          this->heap.push_back(a);
          int j = heap.size() - 1;
          int parent = floor(j / 2);
          // then its, parent is found
          // and heapified untill parent is less than its child
          while (j != 0 && this->heap[j] > this->heap[parent])
          {
               swap(this->heap[j], this->heap[parent]);
               j = parent;
               parent = floor(j / 2);
          }
     }
     int getMax()
     {
          // get max tipically refers to the delete operation
          // every 0th element is removed and heapified
          int s = this->heap.size();
          if (s == 0)
               return -1;
          int max = this->heap[0];
          int n = s - 1;
          // swaping the 0th element with nth element
          swap(this->heap[0], this->heap[n]);
          // poping it
          this->heap.pop_back();
          s = this->heap.size();
          n = s - 1;
          // heapify the resultant
          this->heapify(0, floor(n / 2), s);
          return max;
     }
     vector<int> heapSort()
     {
          // this is just like getMax
          // where instead of deleting the max
          // it is swaped to the end of instance array and maintained
          int s = this->heap.size();
          int n;
          while (s > 0)
          {
               swap(this->heap[0], this->heap[s - 1]);
               s--;
               n = s - 1;
               this->heapify(0, floor(n / 2), s);
          }
          // finally sorted heap is returned
          return this->heap;
     }
     void print()
     {
          for (auto i : this->heap)
               cout << i << " ";
          cout << endl;
     }
};

int main()
{
     vector<int> lst{10, 99, 15, 53, 72, 11};
     Heap h(lst);
     // int n;
     // while((n=h.getMax())!=-1)cout<<n<<" ";
     lst = h.heapSort();
     for (auto i : lst)
          cout << i << " ";
}