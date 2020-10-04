#include "chain.h"
#include "chain_given.cpp"
#include <cmath>
#include <iostream>

// PA1 functions

/**
 * Destroys the current Chain. This function should ensure that
 * memory does not leak on destruction of a chain.
 */
Chain::~Chain()
{
/* your code here */
clear();
length_ = 0;
width_ = 0;
height_ = 0;
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
void Chain::insertBack(const Block &ndata)
{
/* your code here */
Node * nNode = new Node(ndata);
if (length_ == 0){
    head_->next = nNode;
    nNode->next = head_;
    length_++;
} else {
    Node * temp = walk(head_, size());
    temp->next = nNode;
    nNode->next = head_;
    length_++;
    height_ = ndata.height();
    width_ = ndata.width();
}
}


/**
 * Swaps the two nodes at the indexes "node1" and "node2".
 * The indexes of the nodes are 1 based.
 * assumes i and j are valid (in {1,length_} inclusive)
 * p
 */
void Chain::swap(int i, int j)
{
/* your code here */

if (i != j && length_ > 1){
    if (i == j-1 || j == i-1){
        Node * temp1 = walk(head_,i-1);
        Node * temp2 = walk(head_,i);
        Node * temp3 = walk(head_,j);
        temp2->next = temp3->next;
        temp3->next = temp2;
        temp1->next = temp3;
    } else if (i<j) {
        Node * temp1 = walk(head_, i-1);
        Node * temp2 = walk(head_, i);
        Node * temp3 = walk(head_, j-1);
        Node * temp4 = walk(head_, j);
        Node * temp5 = walk(head_, j+1);
        temp4->next = temp2->next;
        temp2->next = temp5;
        temp3->next = temp2;
        temp1->next = temp4;
    } else {
        Node * temp1 = walk(head_, j-1);
        Node * temp2 = walk(head_, j);
        Node * temp3 = walk(head_, i-1);
        Node * temp4 = walk(head_, i);
        Node * temp5 = walk(head_, i+1);
        temp4->next = temp2->next;
        temp2->next = temp5;
        temp3->next = temp2;
        temp1->next = temp4;
    }
} else {
    return;
}
}

/**
 * Reverses the chain
 */
void Chain::reverse()
{
/* your code here */
Node * temp = walk(head_,length_);
for (int i = length_; i > 0; i--){
    Node * temp = walk(head_, i);
    Node * temp1 = walk(head_, i-1);
    temp->next = temp1;
}
head_->next = temp;
}

/*
* Modifies the current chain by "rotating" every group of k nodes by one position.
* In every k-node sub-chain, remove the first node, and place it in the last 
* position of the sub-chain. If the  last sub-chain has length less than k,
* then don't change it at all. 
* Some examples with the chain a b c d e:
*   k = 1: a b c d e
*   k = 2: b a d c e
*   k = 3: b c a d e
*   k = 4: b c d a e
*/
void Chain::rotate(int k)
{
/* your code here */
if (k > length_ || k < 2){
    return;
}

int r = length_ % k;
for (int j = 1; j < length_ - r; j = j+k){
    for (int i = 0; i < k - 1; i++){
        swap (j+i,j+i+1);
    }
}
}

/**
 * Destroys all dynamically allocated memory associated with the
 * current Chain class.
 */
void Chain::clear()
{
/* your code here */
for (int i = length_; i > 0; i--){
    delete(walk(head_,i));
}
length_ = 0;
delete head_;
head_ = NULL;
}

/* makes the current object into a copy of the parameter:
 * All member variables should have the same value as
 * those of other, but the memory should be completely
 * independent. This function is used in both the copy
 * constructor and the assignment operator for Chains.
 */
void Chain::copy(Chain const &other)
{
/* your code here */
if (other.head_ == NULL){
    return;
}

height_ = other.height_;
width_ = other.width_;
head_ = new Node();
Node * curr = head_;
Node * otherCurr = other.head_->next;
while (otherCurr != other.head_){
    Node * newNode = new Node(otherCurr->data);
    curr->next = newNode;
    curr = curr->next;
    otherCurr = otherCurr->next;
}

length_ = other.length_;
Node * temp = walk(head_, length_);
temp->next = head_;
}
