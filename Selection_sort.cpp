// we swap minimum to first index and second minimum to second index and so on.....
// time complexity: O(n2)
// stable: NO
// internal sort

#include<bits/stdc++.h>
using namespace std;



void selection(vector<int>&v1,int size){
    int index;
    for(int i=0;i<size-1;i++){
        int min1=v1[i];
        for(int j=i+1;j<size;j++){
            if(v1[j]<min1){
                min1=v1[j];
                index=j;
            }
        }
        swap(v1[i],v1[index]);
        // print(v1,size);

    }
     for(int i=0;i<size;i++){
        cout<<v1[i]<<" ";
    }
}
// void print(vector<int>&v1, int size){
//     cout<<"Elements of array : ";
//     for(int i=0;i<size;i++){
//         cout<<v1[i]<<" ";
//     }
// }


int main(){
    vector<int> v1;
    int size,val;
    cout<<"Enter the size of array : ";
    cin>>size;
    cout<<"Enter the elements of array : "<<endl;
    for(int i=0;i<size;i++){
        cin>>val;
        v1.push_back(val);
    }
    selection(v1,size);
    // print(v1,size);5





    return 0;
}