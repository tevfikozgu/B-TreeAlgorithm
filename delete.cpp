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
    int find_index_of_key(int,int,char);
    void remove_node(int,int, char);
    void remove_leaf(int);
    void remove_inner(int,int,int,char);
    void merge_childs(int);
    void fill_child(int);
    void borrow_prev(int);
    void borrow_next(int);
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

    void remove(int,int,char);
    
};

int Node::find_index_of_key(int key_x,int key_y, char key_z){
    int index = 0;
    if (key_type == 'x'){
        while(index < number_of_keys && x[index] < key_x){
            index += 1;     //BURADA O ++i yapmis dikkat et!
        }
    } else if (key_type == 'y'){
        while(index < number_of_keys && y[index] < key_y){
            index += 1;     //BURADA O ++i yapmis dikkat et!
        }
    } else if (key_type == 'z'){
        while(index < number_of_keys && z[index] < key_z){
            index += 1;     //BURADA O ++i yapmis dikkat et!
        }
    }
    return index;
}

void Node::remove_node(int key_x,int key_y, char key_z){
    int index = find_index_of_key(key_x,key_y,key_z);

    if (key_type == 'x'){
        if (index < number_of_keys && x[index] == key_x){
            if (is_leaf){
                remove_leaf(index);
            } else {
                remove_inner(index,key_x,key_y,key_z);
            }
        } else {
            if (is_leaf){
                return;
            }

            bool last_child = false;

            if (index == number_of_keys){
                last_child = true;
            }

            if (childs[index]->number_of_keys < degree){
                fill_child(index);
            }

            if(last_child && index > number_of_keys){
                childs[index-1]->remove_node(key_x,key_y,key_z);
            } else {
                childs[index]->remove_node(key_x,key_y,key_z);
            }
        }
    } else if (key_type == 'y'){
        if (index < number_of_keys && y[index] == key_y){
            if (is_leaf){
                remove_leaf(index);
            } else {
                remove_inner(index,key_x,key_y,key_z);
            }
        } else {
            if (is_leaf){
                return;
            }

            bool last_child = false;

            if (index == number_of_keys){
                last_child = true;
            }

            if (childs[index]->number_of_keys < degree){
                fill_child(index);
            }


            if(last_child && index > number_of_keys){
                childs[index-1]->remove_node(key_x,key_y,key_z);
            } else {
                childs[index]->remove_node(key_x,key_y,key_z);
            }

        }
    } else if (key_type == 'z'){
        if (index < number_of_keys && z[index] == key_z){
            if (is_leaf){
                remove_leaf(index);
            } else {
                remove_inner(index,key_x,key_y,key_z);
            }
        } else {
            if (is_leaf){
                return;
            }

            bool last_child = false;

            if (index == number_of_keys){
                last_child = true;
            }

            if (childs[index]->number_of_keys < degree){
                fill_child(index);
            }

            if(last_child && index > number_of_keys){
                childs[index-1]->remove_node(key_x,key_y,key_z);
            } else {
                childs[index]->remove_node(key_x,key_y,key_z);
            }
        }
    }

}

void Node::remove_leaf(int index){
    for (int i=index+1;i<number_of_keys;++i){
        if (key_type == 'x'){
            this->x[i-1] = this->x[i];
            this->y[i-1] = this->y[i];
            this->z[i-1] = this->z[i];
        } else if (key_type == 'y'){
            this->x[i-1] = this->x[i];
            this->y[i-1] = this->y[i];
            this->z[i-1] = this->z[i];
        } else if (key_type == 'z'){
            this->x[i-1] = this->x[i];
            this->y[i-1] = this->y[i];
            this->z[i-1] = this->z[i];
        }
    }
    number_of_keys -= 1;
}

void Node::remove_inner(int index,int key_x, int key_y, char key_z){
    
    if (key_type == 'x'){

        int deleting_key = this->x[index];
        if (childs[index]->number_of_keys >= degree ){
            Node* current_node = childs[index];
            while(!current_node->is_leaf){
                current_node = current_node->childs[current_node->number_of_keys];
            }
            int predecessor_x = current_node->x[current_node->number_of_keys - 1];
            int predecessor_y = current_node->y[current_node->number_of_keys - 1];
            char predecessor_z = current_node->z[current_node->number_of_keys - 1];
            this->x[index] = predecessor_x;
            this->y[index] = predecessor_y;
            this->z[index] = predecessor_z;
            childs[index]->remove_node(predecessor_x,predecessor_y,predecessor_z);
        } else if (childs[index+1]->number_of_keys >= degree){
            Node* current_node = childs[index+1];
            while(!current_node->is_leaf){
                current_node = current_node->childs[0];
            }
            int successor_x = current_node->x[0];
            int successor_y = current_node->y[0];
            char successor_z = current_node->z[0];
            this->x[index] = successor_x;
            this->y[index] = successor_y;
            this->z[index] = successor_z;
            childs[index+1]->remove_node(successor_x,successor_y,successor_z);
        } else{
            merge_childs(index);
            childs[index]->remove_node(deleting_key,key_y,key_z);
        }
        
    } else if (key_type == 'y'){
        int deleting_key = this->y[index];
        if (childs[index]->number_of_keys>= degree ){
            Node* current_node = childs[index];
            while(!current_node->is_leaf){
                current_node = current_node->childs[current_node->number_of_keys];
            }
            int predecessor_x = current_node->x[current_node->number_of_keys - 1];
            int predecessor_y = current_node->y[current_node->number_of_keys - 1];
            char predecessor_z = current_node->z[current_node->number_of_keys - 1];
            this->x[index] = predecessor_x;
            this->y[index] = predecessor_y;
            this->z[index] = predecessor_z;
            childs[index]->remove_node(predecessor_x,predecessor_y,predecessor_z);
        } else if (childs[index+1]->number_of_keys >= degree){
            Node* current_node = childs[index+1];
            while(!current_node->is_leaf){
                current_node = current_node->childs[0];
            }
            int successor_x = current_node->x[0];
            int successor_y = current_node->y[0];
            char successor_z = current_node->z[0];
            this->x[index] = successor_x;
            this->y[index] = successor_y;
            this->z[index] = successor_z;
            childs[index+1]->remove_node(successor_x,successor_y,successor_z);
        } else{
            merge_childs(index);
            childs[index]->remove_node(key_x,deleting_key,key_z);
        }
    } else if (key_type == 'z'){
        char deleting_key = this->z[index];
        if (childs[index]->number_of_keys >= degree ){
            Node* current_node = childs[index];
            while(!current_node->is_leaf){
                current_node = current_node->childs[current_node->number_of_keys];
            }
            int predecessor_x = current_node->x[current_node->number_of_keys - 1];
            int predecessor_y = current_node->y[current_node->number_of_keys - 1];
            char predecessor_z = current_node->z[current_node->number_of_keys - 1];
            this->x[index] = predecessor_x;
            this->y[index] = predecessor_y;
            this->z[index] = predecessor_z;
            childs[index]->remove_node(predecessor_x,predecessor_y,predecessor_z);
        } else if (childs[index+1]->number_of_keys >= degree){
            Node* current_node = childs[index+1];
            while(!current_node->is_leaf){
                current_node = current_node->childs[0];
            }
            int successor_x = current_node->x[0];
            int successor_y = current_node->y[0];
            char successor_z = current_node->z[0];
            this->x[index] = successor_x;
            this->y[index] = successor_y;
            this->z[index] = successor_z;
            childs[index+1]->remove_node(successor_x,successor_y,successor_z);
        } else{
            merge_childs(index);
            childs[index]->remove_node(key_x,key_y,deleting_key);
        }
    }
    
}

void Node::merge_childs(int index){
    Node* sibling = childs[index+1];
    Node* child = childs[index];

    if (key_type == 'x'){
        child->x[degree-1] = this->x[index];
        child->y[degree-1] = this->y[index];
        child->z[degree-1] = this->z[index];

        for (int i=0;i<sibling->number_of_keys;++i){
            child->x[i+degree] = sibling->x[i];
            child->y[i+degree] = sibling->y[i];
            child->z[i+degree] = sibling->z[i];
        }
        if (!child->is_leaf){
            for(int i=0; i<= sibling->number_of_keys;++i){
                child->childs[i+degree] = sibling->childs[i];
            }
        }
        for(int i = index+1;i<number_of_keys;++i){
            this->x[i-1] = this->x[i];
            this->y[i-1] = this->y[i];
            this->z[i-1] = this->z[i];
        }
    } else if (key_type == 'y'){
        child->x[degree-1] = this->x[index];
        child->y[degree-1] = this->y[index];
        child->z[degree-1] = this->z[index];

        for (int i=0;i<sibling->number_of_keys;++i){
            child->x[i+degree] = sibling->x[i];
            child->y[i+degree] = sibling->y[i];
            child->z[i+degree] = sibling->z[i];
        }
        if (!child->is_leaf){
            for(int i=0; i<= sibling->number_of_keys;++i){
                child->childs[i+degree] = sibling->childs[i];
            }
        }
        for(int i = index+1;i<number_of_keys;++i){
            this->x[i-1] = this->x[i];
            this->y[i-1] = this->y[i];
            this->z[i-1] = this->z[i];
        }
    } else if (key_type == 'z'){
        child->x[degree-1] = this->x[index];
        child->y[degree-1] = this->y[index];
        child->z[degree-1] = this->z[index];

        for (int i=0;i<sibling->number_of_keys;++i){
            child->x[i+degree] = sibling->x[i];
            child->y[i+degree] = sibling->y[i];
            child->z[i+degree] = sibling->z[i];
        }
        if (!child->is_leaf){
            for(int i=0; i<= sibling->number_of_keys;++i){
                child->childs[i+degree] = sibling->childs[i];
            }
        }
        for(int i = index+1;i<number_of_keys;++i){
            this->x[i-1] = this->x[i];
            this->y[i-1] = this->y[i];
            this->z[i-1] = this->z[i];
        }
    }


    for(int i=index+2;i<=number_of_keys;++i){
        childs[i-1] = childs[i];
    }

    child->number_of_keys += sibling->number_of_keys+1;
    number_of_keys -= 1;

    delete sibling;
}

void Node::fill_child(int index){
    if(index != 0 && childs[index-1]->number_of_keys >= degree){
        borrow_prev(index);
    } else if (index != number_of_keys && childs[index+1]->number_of_keys >= degree){
        borrow_next(index);
    } else {
        if (index != number_of_keys){
            merge_childs(index);
        } else {
            merge_childs(index-1);
        }
    }
}

void Node::borrow_next(int index){
    Node* sibling = childs[index+1];
    Node* child = childs[index];

    if (key_type == 'x'){
        child->x[child->number_of_keys] = this->x[index];
        child->y[child->number_of_keys] = this->y[index];
        child->z[child->number_of_keys] = this->z[index];

        if(!child->is_leaf){
            child->childs[child->number_of_keys+1] = sibling->childs[0];
        }

        this->x[index] = sibling->x[0];
        this->y[index] = sibling->y[0];
        this->z[index] = sibling->z[0];

        for (int i=1;i<sibling->number_of_keys;++i){
            sibling->x[i-1] = sibling->x[i];
            sibling->y[i-1] = sibling->y[i];
            sibling->z[i-1] = sibling->z[i];
        }

        

    } else if (key_type == 'y'){

        child->x[child->number_of_keys] = this->x[index];
        child->y[child->number_of_keys] = this->y[index];
        child->z[child->number_of_keys] = this->z[index];

        if(!child->is_leaf){
            child->childs[child->number_of_keys+1] = sibling->childs[0];
        }

        this->x[index] = sibling->x[0];
        this->y[index] = sibling->y[0];
        this->z[index] = sibling->z[0];

        for (int i=1;i<sibling->number_of_keys;++i){
            sibling->x[i-1] = sibling->x[i];
            sibling->y[i-1] = sibling->y[i];
            sibling->z[i-1] = sibling->z[i];
        }

    } else if (key_type == 'z'){
        child->x[child->number_of_keys] = this->x[index];
        child->y[child->number_of_keys] = this->y[index];
        child->z[child->number_of_keys] = this->z[index];

        if(!child->is_leaf){
            child->childs[child->number_of_keys+1] = sibling->childs[0];
        }

        this->x[index] = sibling->x[0];
        this->y[index] = sibling->y[0];
        this->z[index] = sibling->z[0];

        for (int i=1;i<sibling->number_of_keys;++i){
            sibling->x[i-1] = sibling->x[i];
            sibling->y[i-1] = sibling->y[i];
            sibling->z[i-1] = sibling->z[i];
        }
    }

    if (!sibling->is_leaf){
        for(int i=1;i<=sibling->number_of_keys;i++){
            sibling->childs[i-1] = sibling->childs[i];
        }
    }

    child->number_of_keys += 1;
    sibling->number_of_keys -= 1;
}

void Node::borrow_prev(int index){
    Node* sibling = childs[index-1];
    Node* child = childs[index];

    if (key_type == 'x'){
        for (int i =child->number_of_keys-1; i>= 0; --i){
            child->x[i+1] = child->x[i]; 
            child->y[i+1] = child->y[i]; 
            child->z[i+1] = child->z[i]; 
        }
        if (!child->is_leaf){
            for (int i=child->number_of_keys;i>=0;--i){
                child->childs[i+1] = child->childs[i];
            }
        }

        child->x[0] = this->x[index-1];
        child->y[0] = this->y[index-1];
        child->z[0] = this->z[index-1];

        if (!child->is_leaf){
            child->childs[0] = sibling->childs[sibling->number_of_keys];
        }

        this->x[index-1] = sibling->x[sibling->number_of_keys - 1];
        this->y[index-1] = sibling->y[sibling->number_of_keys - 1];
        this->z[index-1] = sibling->z[sibling->number_of_keys - 1];

    } else if (key_type == 'y'){

        for (int i =child->number_of_keys-1; i>= 0; --i){
            child->x[i+1] = child->x[i]; 
            child->y[i+1] = child->y[i]; 
            child->z[i+1] = child->z[i]; 
        }
        if (!child->is_leaf){
            for (int i=child->number_of_keys;i>=0;--i){
                child->childs[i+1] = child->childs[i];
            }
        }

        child->x[0] = this->x[index-1];
        child->y[0] = this->y[index-1];
        child->z[0] = this->z[index-1];

        if (!child->is_leaf){
            child->childs[0] = sibling->childs[sibling->number_of_keys];
        }

        this->x[index-1] = sibling->x[sibling->number_of_keys - 1];
        this->y[index-1] = sibling->y[sibling->number_of_keys - 1];
        this->z[index-1] = sibling->z[sibling->number_of_keys - 1];

    } else if (key_type == 'z'){

        for (int i =child->number_of_keys-1; i>= 0; --i){
            child->x[i+1] = child->x[i]; 
            child->y[i+1] = child->y[i]; 
            child->z[i+1] = child->z[i]; 
        }
        if (!child->is_leaf){
            for (int i=child->number_of_keys;i>=0;--i){
                child->childs[i+1] = child->childs[i];
            }
        }

        child->x[0] = this->x[index-1];
        child->y[0] = this->y[index-1];
        child->z[0] = this->z[index-1];

        if (!child->is_leaf){
            child->childs[0] = sibling->childs[sibling->number_of_keys];
        }

        this->x[index-1] = sibling->x[sibling->number_of_keys - 1];
        this->y[index-1] = sibling->y[sibling->number_of_keys - 1];
        this->z[index-1] = sibling->z[sibling->number_of_keys - 1];

    }

    child->number_of_keys += 1;
    sibling->number_of_keys -= 1;
}


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

void BTree::remove(int key_x=0,int key_y=0,char key_z='0'){
    if (!this->root){
        return;
    }
    root->remove_node(key_x,key_y,key_z);

    if (root->number_of_keys == 0){
        Node* temp = root;
        if (root->is_leaf){
            root = NULL;
        } else {
            root = root->childs[0];
        }
        delete temp;
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
    
    if (key_type == 'x'){
        int deleting_key;
        cin >> deleting_key;
        my_tree.remove(deleting_key);
    } else if (key_type == 'y'){
        int deleting_key;
        cin >> deleting_key;
        my_tree.remove(0,deleting_key);
    } else if (key_type == 'z'){
        char deleting_key;
        cin >> deleting_key;
        my_tree.remove(0,0,deleting_key);
    }

    print(my_tree.root);

    return 0;
}