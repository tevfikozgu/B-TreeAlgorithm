#include<iostream>
#include <vector> 
#include <stdlib.h>

using namespace std;
static char key_type;

//TEVFIK OZGU 150180082

class Node{
    public:
    vector<int> x;
    vector<int> y;
    vector<char> z;
    int degree;
    int number_of_keys;
    Node** childs;
    bool is_leaf;
    Node(bool,int);
    void BTree_Split(int, Node*);
    void BTree_Insert_Nonfull(int,int,char);
};

Node::Node(bool is_leaf, int degree){
    this->degree = degree;
    this->is_leaf = is_leaf;

    for(int i=0;i<2*degree-1;i++){
        x.push_back(0);
        y.push_back(0);
        z.push_back('\0');
    }

    childs = new Node* [2*degree]; 
    number_of_keys = 0;
}

class BTree{
    public:
    Node* root;
    int tree_degree;
    void insert(int,int,char);
    BTree(int degree){
        root = NULL;
        tree_degree = degree;
    }
    
};

void print(Node* temp){
    if (temp != NULL){
        int i;
        for(int i=0;i<temp->number_of_keys;i++){
            cout << '(' << temp->x[i] << ',' << temp->y[i] << ',' << temp->z[i] << ')';
            
        }
        cout << endl;
        for(i=0;i<temp->number_of_keys;i++){
            if (temp->is_leaf == false) 
                print(temp->childs[i]);
        }
        
        if (temp->is_leaf == false) 
            print(temp->childs[i]);
    }
}

void Node::BTree_Insert_Nonfull(int x,int y,char z){
    //cout << "CPINSERTICINONFULL" << endl; 
    int i = number_of_keys-1;
    if(is_leaf == true){
        //cout << "IS_LEAF == TRUE" << endl;
        if (key_type == 'x'){
            while(i>=0 && x < this->x[i]){
                this->z[i+1] = this->z[i];
                this->x[i+1] = this->x[i];
                this->y[i+1] = this->y[i];
                i -= 1;
            }
        } else if (key_type == 'y'){
            while(i>=0 && y < this->y[i]){
                this->z[i+1] = this->z[i];
                this->x[i+1] = this->x[i];
                this->y[i+1] = this->y[i];
                i -= 1;
            }
        } else if (key_type == 'z'){
            while(i>=0 && z < this->z[i]){
                this->z[i+1] = this->z[i];
                this->x[i+1] = this->x[i];
                this->y[i+1] = this->y[i];
                i -= 1;
            }
        } else {
            exit(1);
        }
        this->z[i+1] = z;
        this->x[i+1] = x;
        this->y[i+1] = y;
        number_of_keys += 1;

    } else {
        //cout << "ELSE INSERTNONFULL" << endl; 

        if (key_type == 'x'){
            while (i >= 0 && x < this->x[i]){
			    i--; 
            }
            if (childs[i+1]->number_of_keys == 2*degree - 1){
                //cout << "ESIT OLMALI" << endl; 
                this->BTree_Split(i+1,childs[i+1]);
                if(this->x[i+1] < x){
                    i++;
                } 
            }
        } else if (key_type == 'y'){
            while (i >= 0 && y < this->y[i]){
			    i--; 
            }
            if (childs[i+1]->number_of_keys == 2*degree - 1){
                //cout << "ESIT OLMALI" << endl; 
                this->BTree_Split(i+1,childs[i+1]);
                if(this->y[i+1] < y){
                    i++;
                } 
            }
        } else if (key_type == 'z'){
            while (i >= 0 && z < this->z[i]){
			    i--; 
            }
            if (childs[i+1]->number_of_keys == 2*degree - 1){
                //cout << "ESIT OLMALI" << endl; 
                this->BTree_Split(i+1,childs[i+1]);
                if(this->z[i+1] < z){
                    i++;
                } 
            }
        } else {
            exit(1);
        }
        //cout << "BOLUM ZAMANI" << endl; 
        childs[i+1]->BTree_Insert_Nonfull(x,y,z);
    }
}

void Node::BTree_Split(int num, Node* ex_root){
    //cout << "NOT_NULL GIRDI!" << endl;
    Node *right = new Node(ex_root->is_leaf, ex_root->degree);
    right->number_of_keys = 0;
    right->number_of_keys = this->degree - 1;
    
    for(int i=0;i<degree-1;i++){
        right->x[i] = ex_root->x[i+degree];
        right->y[i] = ex_root->y[i+degree];
        right->z[i] = ex_root->z[i+degree];
    }

    if (ex_root->is_leaf == false){
        for(int i=0;i<degree;i++){
            //cout << "BUNUN OLMAMASI LAZIM" << endl;
            right->childs[i] = ex_root->childs[i+degree];
        }
    }

    ex_root->number_of_keys = this->degree-1;

    for(int i=number_of_keys;i>=num+1;i--){
        this->childs[i+1] = this->childs[i];
    }
    
    this->childs[num+1] = right;

    for (int i=number_of_keys-1;i>=num;i--){
        this->x[i+1] = this->x[i];    
        this->y[i+1] = this->y[i];
        this->z[i+1] = this->z[i];
    }
    
    this->x[num] = ex_root->x[this->degree-1];    
    this->y[num] = ex_root->y[this->degree-1];
    this->z[num] = ex_root->z[this->degree-1];
    this->number_of_keys += 1;
}

void BTree::insert(int x,int y, char z){
    Node* tree_root = root;
    if (tree_root == NULL){
        root = new Node(true,tree_degree);
        root->number_of_keys = 0;
        
        root->x[0] = x;
        root->y[0] = y;
        root->z[0] = z;
        
        root->number_of_keys += 1;
    } else if (tree_root->number_of_keys == 2*tree_degree - 1){
        Node* new_node = new Node(false,tree_degree);
        new_node->number_of_keys = 0;
        new_node->childs[0] = root;
        new_node->BTree_Split(0, root);

        int i = 0; 

        if (key_type == 'x'){
            if (new_node->x[0] < x) 
                i++; 
        } else if (key_type == 'y'){
            if (new_node->y[0] < y) 
                i++; 
        } else if (key_type == 'z'){
            if (new_node->z[0] < z) 
                i++; 
        } else {
            exit(1);
        }
        new_node->childs[i]->BTree_Insert_Nonfull(x,y,z); 
        root = new_node;
    } else {
        root->BTree_Insert_Nonfull(x,y,z); 
    }
}


int main(){
    int num_of_element,degree;
    cin >> num_of_element;
    cin >> degree;
    cin >> key_type;
    BTree my_tree(degree);
    for(int i=0;i<num_of_element;i++){
        int x,y;
        char z;
        cin >> x;
        cin >> y;
        cin >> z;
        my_tree.insert(x,y,z);
    }

    print(my_tree.root);
    
    return 0;
}