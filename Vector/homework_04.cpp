#include<iostream>
#include<cassert>

using namespace std;

class Vector{

private:
    int*arr=nullptr;
    int size=0; //user size
    int capacity=0; //actual size

public:
    Vector(int size):size(size){
        if(size<0)
            size=1;
        capacity=size+10;
        arr=new int[capacity];
    }

    int get(int idx){
        assert(0<=idx&&idx<size);
        return arr[idx];
    }

    void set(int idx,int val){
        assert(0<=idx&&idx<size);
        arr[idx]=val;
    }

    void print(){
        for(int i=0;i<size;i++)
            cout<<arr[i]<<" ";
        cout<<"\n";
    }

    int find(int val){
         for(int i=0;i<size;i++)
            if(arr[i]==val)
                return i;
         return -1; //-1 for not found
    }

   int get_front(){
       return arr[0];
   }

   int get_back(){
       return arr[size-1];
   }


   void push_back(int value){

       if(capacity==size)
        expand_capacity();
       arr[size++]=value;
   }

   void expand_capacity(){
       capacity=capacity*2;
       int* arr2=new int[capacity];
       for(int i=0;i<size;i++)
        arr2[i]=arr[i];
        swap(arr,arr2);
       delete[] arr2;
   }

   void insert(int val,int idx){
    assert(0<=idx&&idx<size);

       if(size==capacity)
        expand_capacity();

    for(int i=size-1;i>=idx;i--)
        arr[i+1]=arr[i];

    arr[idx]=val;
    size++;
   }

   int pop(int idx){
       assert(0<=idx&&idx<size);

       int deleted=arr[idx];
       for(int i=idx+1;i<size;i++)
        arr[i-1]=arr[i];

       size--;
        return deleted;
}

    ~Vector(){
        delete[]arr;
        arr=nullptr;
    }


};

int main(){

    Vector v(0);
    v.push_back(4);
    v.push_back(0);
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);

    v.print();

    cout<<v.pop(2)<<endl;
    v.print();


    return 0;
}
