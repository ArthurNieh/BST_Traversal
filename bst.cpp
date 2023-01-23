#include <algorithm>
#include <iostream>
#include <vector>
#include <fstream>
#include <queue>

using namespace std;

void post_to_pre(int start, int end, int& max_height, int height, vector<int>& pre_tree, const int* post_tree, vector<int>& maximum_value){
    pre_tree.push_back(post_tree[end]);
    height+=1;

    //getting tree height
    if(height > max_height){
        max_height = height;
    }

    // handling maimum values on the BST
    if(maximum_value.size() == height-1){
        maximum_value.push_back(post_tree[end]);
    }
    else if(maximum_value[height-1] < post_tree[end]){
        maximum_value[height-1] = post_tree[end];
    }
    else{
        cout<<"error for maximum value"<<endl;
    }
    
    // recursion for subtrees
    // no subtree
    if(start == end) return; 
    // only one subtree
    else if(post_tree[end] < post_tree[start] || post_tree[end] > post_tree[end-1]){
        post_to_pre(start, end-1, max_height, height, pre_tree, post_tree, maximum_value);
        return;
    }
    //two subtree
    else{
        int left_subtree_index; // rightest node of left subtree
        for(int i=start;i<end;i++){
            if(post_tree[end]<post_tree[i]){
                left_subtree_index = i-1;
                break;
            }
        }
        post_to_pre(start, left_subtree_index, max_height, height, pre_tree, post_tree, maximum_value); // for left subtree
        post_to_pre(left_subtree_index+1, end-1, max_height, height, pre_tree, post_tree, maximum_value); // for right subtree
        return;
    }
}

int main(int argc, char *argv[]){
    ifstream infile; 
    infile.open(argv[1]);
    ofstream outfile;
    outfile.open(argv[2]);

    // TODO: Please code here
    
    int tree_num;//tree number
    infile >> tree_num;

    for(int i=0;i<tree_num;i++){
        int node_num; //node number
        infile >> node_num;
        
        int* post_order_tree = new int [node_num]; //post-order tree
        vector<int> pre_order_tree; //pre-order tree
        vector<int> max_at_each_height; //maximun number at each level
        
        for(int j=0;j<node_num;j++){
            infile >> post_order_tree[j];
        }

        int max_height = 0; // tree height
        post_to_pre(0, node_num-1, max_height, 0, pre_order_tree, post_order_tree, max_at_each_height);

        // output
        //print pre-order tree
        outfile<<pre_order_tree[0];
        for(int j=1;j<node_num;j++){
            outfile<<" "<<pre_order_tree[j];
        }
        // print tree height
        outfile<<endl<<max_height;
        //print maximum value at each level
        for(int j=0;j<max_height;j++){
            outfile<<endl<<max_at_each_height[j];
        }
        if(i != tree_num-1) outfile<<endl; // for output format

        // print for debug
        // cout<<"tree:"<<endl;
        // for(int j=0;j<node_num;j++){
        //     cout<<pre_order_tree[j]<<" ";
        // }
        // cout<<endl<<"max height: "<<max_height<<endl<<"max values: "<<endl;
        // for(int j=0;j<max_height;j++){
        //     cout<<max_at_each_height[j]<<" ";
        // }
        // cout<<endl;

    }

    infile.close();
    outfile.close();
}