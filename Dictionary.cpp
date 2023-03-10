//amanda yun akyun@ucsc.edu 1903241 pa7

#include <cstring>
#include <limits>
#include <sstream>
#include <stdexcept>
#include "Dictionary.h"
#include <string>
#include <iostream>


Dictionary::Node::Node(keyType k, valType v){
	key = k;
	val = v;
	parent = nullptr;
	left = nullptr;
	right = nullptr;
	
	
}


void Dictionary::inOrderString(std::string& s, Node* R)const{
	if(R!=nil){
		inOrderString(s, R->left);
		s+=(R->key) + " : " + std::to_string(R->val) + "\n";
		//s.append(R->key, ": ",R->val, "\n");
		inOrderString(s, R->right);
	}
}

void Dictionary::preOrderString(std::string& s, Node* R)const{
	if(R!=nil){
		s+=(R->key) + "\n";
		//s.append(R->key);
		preOrderString(s, R->left);
		preOrderString(s, R->right);
	}
}

void Dictionary::preOrderCopy(Node* R, Node* N){
	//R to N
	if(R!=N){
		setValue(R->key, R->val);
		preOrderCopy(R->left, N);
		preOrderCopy(R->right, N);
	}
}


void Dictionary::postOrderDelete(Node* R){
	
	if(R!=nil){
		postOrderDelete(R->left);
		postOrderDelete(R->right);
		delete R;
	}
	
}

Dictionary::Node* Dictionary::search(Node* R, keyType k) const{

	while(R!=nil){
		if(k == R->key || R== nil){
			return R;
		}else if(k < R->key){
			R = R->left;
		}else{
			R = R->right;
		}
	}
	
	return nil;
}

Dictionary::Node* Dictionary::findMin(Node* R){
	Node* temp = R;
	if(temp!=nil){
		while(temp->left!=nil){
			temp = temp->left;
		}

	}
	return temp;
}

Dictionary::Node* Dictionary::findMax(Node* R){
	Node* temp = R;
	if(temp!=nil){
		while(temp->right!=nil){
			temp = temp->right;
		}
	}
	
	return temp;
}

Dictionary::Node* Dictionary::findNext(Node* N){
	
	if(N==nil){//nothing to look for
		return nil;
	}else if(N->right != nil){
		return findMin(N->right);
	}else{
		Node* temp = N->parent;
		while(temp!=nil && N!=temp->right){
			N = temp;
			temp = temp->parent;
		}
		
		return temp;

	}


	
}
//changed from left to right

Dictionary::Node* Dictionary::findPrev(Node* N){
	if(N==nil){
		return nil;
	}else if(N->left != nil){
		return findMax(N->left);
	}else{
		Node* temp = N->parent;
		while(temp!=nil && N!=temp->right){
			N = temp;
			temp = temp->parent;
		}
		return temp;
	}
}

Dictionary::Dictionary(){
	nil  = new Node("abcdefghijklmnopqrstuvwxyz", 999);
	root = nil;
	current = nil;
	num_pairs = 0;
	
}

Dictionary::Dictionary(const Dictionary& D){
	nil = new Node("abcdefghijklmnopqrstuvwxyz", 999);
	root = nil;
	current = nil;
	num_pairs = 0;
	
	
	preOrderCopy(D.root, D.nil);
	
	//pre order copy from root of D to nil of D
}

Dictionary::~Dictionary(){
	postOrderDelete(this->root);
	delete this->nil;
}

int Dictionary::size() const{
	return num_pairs;
}

bool Dictionary::contains(keyType k) const{
	Node* temp;
	temp = search(this->root, k);
	
	if(temp!=nil){
		return true;
	}


	return false;

}

valType& Dictionary::getValue(keyType k) const{
	Node* temp = search(this->root, k);
	if(temp==nil){
		throw std::logic_error("Dictionary error: key k in getValue() does not exist in the dictionary\n");
	}
	
	return temp->val;

}

bool Dictionary::hasCurrent() const{
	if(this->current!=nil){
		return true;
	}
	
	
	return false;
}

keyType Dictionary::currentKey() const{
	if(!hasCurrent()){
		throw std::logic_error("Dictionary error: calling currentKey() when current is undefined\n");
	}
	
	return this->current->key;
}

valType& Dictionary::currentVal() const{
	if(!hasCurrent()){
		throw std::logic_error("Dictionary error: calling currentVal() when current is undefined\n");
	}
	
	return this->current->val;
}

void Dictionary::clear(){
	postOrderDelete(this->root);
	this->root = nil;
	this->current = nil;
	this->num_pairs = 0;
}

void Dictionary::setValue(keyType k, valType v){
	Node* temp1 = this->nil;
	Node* temp2 = this->root;
	
	while(temp2!=nil){
		temp1 = temp2;
		if(k < temp2->key){
			temp2 = temp2->left;
		}else if(k>temp2->key){
			temp2 = temp2->right;
		}else{
			temp2->val= v;
			return;
		}
	}
	
	
	Node* temp = new Node(k, v);
	if(temp1==nil){
		temp->parent = nil;
		temp->left = nil;
		temp->right = nil;
		this->root=temp;
	}else if(k<temp1->key){
		temp1->left = temp;
		temp->parent = temp1;
		temp->left = nil;
		temp->right = nil;
	}else{
		temp1->right = temp;
		temp->parent = temp1;
		temp->left = nil;
		temp->right = nil;
	}
	
	this->num_pairs++;
}

//from Mike's tutor session pseudcode
void Dictionary::transplant(Node* u, Node* v){
	if(u->parent == nil){
		this->root = v;
	}else if(u==u->parent->left){
		u->parent->left = v;
	}else{
		u->parent->right = v;
	}
	if(v!=nil){
		v->parent = u->parent;
	}
}

void Dictionary::remove(keyType k){
	Node* temp = search(this->root, k);
	if(temp == nil){
		throw std::logic_error("Dictionary: calling remove() when key does not exist\n");
	}
	if(temp == this->current){
		this->current = nil;
	}

	if(temp->left == nil){
		transplant(temp, temp->right);
		delete temp;
		num_pairs--;
	}else if(temp->right == nil){
		transplant(temp, temp->left);
		delete temp;
		num_pairs--;
	}else{
		Node* x = findMin(temp->right);

		if(x->parent != temp){
			transplant(x, x->right);
			x->right = temp->right;
			x->right->parent = x;
			delete x;
		}else{
			transplant(temp, x);
			x->left = temp->left;
			x->left->parent = x;
			delete temp;

		}

		//delete temp;
		num_pairs--;
	}
//	delete temp;
	
//	Node* temp = search(this->root, k);
//	if(temp == nil){ //not in the dictionary
//		throw std::logic_error("Dictionary: calling remove() when key does not exist in the dictionary\n");
//	}
//	
//	if(k < root->key){
//		root = root->left;
//		remove(k);
//	}else if(k>root->key){
//		root = root->right;
//		remove(k);
//	}else{ //reached note to remove
//		if(root->left == nil && root->right==nil){ //no children
//			delete root;
//			root = nullptr;
//		}else if(root->left == nil){
//			Node* r = root;
//			root = root->right;
//			delete r;
//		}else if(root->right == nil){
//			Node* r = root;
//			root = root->left;
//			delete r;
//		}else{
//			Node* minR = root->right;
//			while(minR->left!=nil){
//				minR = minR->left;
//			}
//			
//			root->key = minR->key;
//			Node* t = root;
//			root = root->right;
//			//t->right = remove(minR->key);
//		}
//	}
	
	
}

void Dictionary::begin(){
	this->current = findMin(this->root);
}

void Dictionary::end(){
	this->current = findMax(this->root);
}

void Dictionary::next(){
	if(!hasCurrent()){
		throw std::logic_error("Dictionary:: calling next() when current is undefined\n");
	}
	if(this->current != findMax(this->current)){
		this->current = findNext(this->current);
				
	}else{
		this->current = nil;
	}
//	this->current = findNext(this->current);
//	std::cout << "current within next(): " << this->current->key << std::endl;
}

void Dictionary::prev(){
	//same as next but use findPrev
	if(!hasCurrent()){
		throw std::logic_error("Dictionary:: calling prev() when current is undefined\n");
	}

	if(this->current != findMin(root)){
		this->current = findPrev(this->current);
		
	}else{
		this->current = nil;
	}
	
//	this->current = findPrev(this->current);
}

std::string Dictionary::to_string() const{
	std::string s;
	inOrderString(s, this->root);
	
	return s;
}

std::string Dictionary::pre_string() const{
	std::string s;
	preOrderString(s, this->root);
	return s;
}

bool Dictionary::equals(const Dictionary& D) const{
	if(this->num_pairs != D.num_pairs){
		return false;
	}
	
	if(this->to_string() != D.to_string()){
		return false;
	}
	
	return true;
}

std::ostream& operator<<(std::ostream& stream, Dictionary& D){
	return stream << D.to_string();
}

bool operator==(const Dictionary& A, const Dictionary& B){
	return A.equals(B);
}

Dictionary& Dictionary::operator=(const Dictionary& D){
	if(this!=&D){
		Dictionary temp = D;
	
	
		std::swap(nil, temp.nil);
		std::swap(this->root, temp.root);
		std::swap(current, temp.current);
		std::swap(num_pairs, temp.num_pairs);
	
	}
	
	return *this;
}