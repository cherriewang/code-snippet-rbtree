/*
 * rbbst.h
 *
 * Date        Author    Notes
 * =====================================================
 * 2014-04-14  Kempe     Initial version
 * 2015-04-06  Redekopp  Updated formatting and removed
 *                         KeyExistsException
 *             Cherrie   Implements insert
 */
#ifndef RBBST_H
#define RBBST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include "bst.h"

/* -----------------------------------------------------
 * Red-Black Nodes and Search Tree
 ------------------------------------------------------*/

enum Color {red, black};

template <class KeyType, class ValueType>
class RedBlackNode : public Node<KeyType, ValueType>
{
public:
  RedBlackNode (KeyType k, ValueType v, RedBlackNode<KeyType, ValueType> *p)
    : Node<KeyType, ValueType> (k, v, p)
    { color = red; }
  
  virtual ~RedBlackNode () {}
  
  Color getColor () const
    { return color; }
  
  void setColor (Color c)
    { color = c; }
  
  virtual RedBlackNode<KeyType, ValueType> *getParent () const
    { return (RedBlackNode<KeyType,ValueType>*) this->_parent; }
  
  virtual RedBlackNode<KeyType, ValueType> *getLeft () const
    { return (RedBlackNode<KeyType,ValueType>*) this->_left; }
  
  virtual RedBlackNode<KeyType, ValueType> *getRight () const
    { return (RedBlackNode<KeyType,ValueType>*) this->_right; }
  
 protected:
  Color color;
};

/* -----------------------------------------------------
 * Red-Black Search Tree
 ------------------------------------------------------*/

template <class KeyType, class ValueType>
class RedBlackTree : public BinarySearchTree<KeyType, ValueType>
{

public:

  /* This one is yours to implement.
   It should insert the (key, value) pair to the tree, 
   making sure that it remains a valid Red-Black Tree.
   If the key is already in the tree
   (with a possibly different associated value),
   then it should overwrite the value with the new one.
   We strongly recommend defining suitable (private) helper functions. */
  void insert (const std::pair<const KeyType, ValueType>& new_item) {

    // make a new node with the pair ???
    RedBlackNode<KeyType,ValueType>* rbnode = new RedBlackNode<KeyType,ValueType>(new_item.first, new_item.second, NULL);
    // default color of inserting node is always red
    rbnode->setColor(red);
    // make the left and right also null to start with
    rbnode->setLeft(NULL);
    rbnode->setRight(NULL);

    // if there isn't a tree huh
    if(this->root == NULL) {
      this->root = rbnode;
    }

    // ok so a tree exists, we just got to add to it
    else {
      RedBlackNode<KeyType,ValueType>* holdroot = static_cast<RedBlackNode<KeyType,ValueType>*>(this->root);
      while(true){
        // keys are the same!!!
        if(rbnode->getKey() == holdroot->getKey()) {
          holdroot->setValue(rbnode->getValue());
          return;
        }
        else if (rbnode->getKey() < holdroot->getKey()){
          // hit a null end? GREAT
          if(holdroot->getLeft() == NULL) {
            // setting this as the left node
            holdroot->setLeft(rbnode);
            // get out of while loop
            break;
          }
          else {
            holdroot = holdroot->getLeft();
            // now continue through while loop again
          }
        }
        else {
          // hit a null end? GREAT
          if(holdroot->getRight() == NULL){
            // setting this as the right node
            holdroot->setRight(rbnode);
            // get out of while loop
            break;
          }
          else {
            holdroot = holdroot->getRight();
          }
        }
      } // end of while loop is here
      // setting the parent properly
      rbnode->setParent(holdroot);
    }

    // starts the waterfall of stuffs
    this->insert1(rbnode);

  } // end of function

private:
  // helper function for insert
  RedBlackNode<KeyType,ValueType>* findMyUncle(RedBlackNode<KeyType,ValueType>* rbnode){
    
    RedBlackNode<KeyType,ValueType>* gramps = findMyGrandpa(rbnode);
    // if the node has no grandparent, then there is no uncle
    if (gramps == NULL) {
      return NULL; 
    }
    if (rbnode->getParent() == gramps->getLeft()) {
      return gramps->getRight();
    }
    else {
      return gramps->getLeft();
    }

  }

  // helper function for insert
  RedBlackNode<KeyType,ValueType>* findMyGrandpa(RedBlackNode<KeyType,ValueType>* rbnode){
   
    // getting the parent of the parent provided that neither are null
    if ((rbnode != NULL) && (rbnode->getParent() != NULL) && (rbnode->getParent()->getParent() != NULL)) {
      return ((rbnode->getParent())->getParent());
    }
    else {
      return NULL;
    }

  }

  // helper function for insert
  void RightRotate(RedBlackNode<KeyType,ValueType>* rbnode){

    // implementing by replacing
    RedBlackNode<KeyType,ValueType>* holdleft = rbnode->getLeft();
 

    if (rbnode->getParent() == NULL) {
      this->root = holdleft;
    }
    else {
      if (rbnode == rbnode->getParent()->getLeft()) {
        //rbnode->getParent()->getLeft() = holdleft;
        rbnode->getParent()->setLeft(holdleft);
      }
      else {
        //rbnode->getParent()->getRight() = holdleft;
        rbnode->getParent()->setRight(holdleft);
      }
    }
    if (holdleft != NULL) {
      //holdleft->getParent() = rbnode->getParent();
      holdleft->setParent(rbnode->getParent());
    }

    //rbnode->getLeft() = holdleft->getRight();
    rbnode->setLeft(holdleft->getRight());

    if(holdleft->getRight() != NULL){
      //holdleft->getRight()->getParent() = rbnode;
      holdleft->getRight()->setParent(rbnode);
    }
    holdleft->setRight(rbnode);
    rbnode->setParent(holdleft);

  }

  // helper function for insert
  void LeftRotate(RedBlackNode<KeyType,ValueType>* rbnode){

    // IMPLEMENT by replacement
    RedBlackNode<KeyType,ValueType>* holdright = rbnode->getRight();

    if (rbnode->getParent() == NULL) {
      this->root = holdright;
    }
    else {
      if (rbnode == rbnode->getParent()->getLeft()) {
        //rbnode->getParent()->getLeft() = holdleft;
        rbnode->getParent()->setLeft(holdright);
      }
      else {
        //rbnode->getParent()->getRight() = holdleft;
        rbnode->getParent()->setRight(holdright);
      }
    }
    if (holdright != NULL) {
      //holdleft->getParent() = rbnode->getParent();
      holdright->setParent(rbnode->getParent());
    }

    rbnode->setRight(holdright->getLeft());
    if(holdright->getLeft() != NULL ){
      holdright->getLeft()->setParent(rbnode);
    }
    holdright->setLeft(rbnode);
    rbnode->setParent(holdright);

  }

  // case 1
  void insert1(RedBlackNode<KeyType,ValueType>* rbnode){
    if(rbnode->getParent() == NULL){
      rbnode->setColor(black);
    }
    else {
      insert2(rbnode);
    }
  }

  // case 2
  void insert2(RedBlackNode<KeyType,ValueType>* rbnode){
    if( (rbnode->getParent())->getColor() == black) {
      // tree is ok!!!!!!
      return;
    }
    else {
      insert3(rbnode);
    }

  }

  // case 3
  void insert3(RedBlackNode<KeyType,ValueType>* rbnode){
    
    RedBlackNode<KeyType,ValueType>* unc = findMyUncle(rbnode);
    RedBlackNode<KeyType,ValueType> *gramps;

    if ((unc != NULL) && (unc->getColor() == red)) {
      (rbnode->getParent())->setColor(black);
      unc->setColor(black);
      gramps = findMyGrandpa(rbnode);
      gramps->setColor(red);
      insert1(gramps);
    } 
    else {
      insert4(rbnode);
    }

  }

  // case 4
  void insert4(RedBlackNode<KeyType,ValueType>* rbnode){
    
    RedBlackNode<KeyType,ValueType>* gramps = findMyGrandpa(rbnode);

    if ((rbnode == rbnode->getParent()->getRight()) && (rbnode->getParent() == gramps->getLeft())) {
      
      LeftRotate(rbnode->getParent());

      rbnode = rbnode->getLeft();

    } 

    else if ((rbnode == rbnode->getParent()->getLeft()) && (rbnode->getParent() == gramps->getRight())) {
      RightRotate(rbnode->getParent());
      rbnode = rbnode->getRight(); 
    }

    insert5(rbnode);
 
  }  

  // case 5
  void insert5(RedBlackNode<KeyType,ValueType>* rbnode){
    
    RedBlackNode<KeyType,ValueType>* gramps = findMyGrandpa(rbnode);
    // appropriating colors ~~~
    gramps->setColor(red);
    (rbnode->getParent())->setColor(black); 
    
    if (rbnode == (rbnode->getParent())->getLeft() && rbnode->getParent() == gramps->getLeft()) {
      RightRotate(gramps);
    }
    else {
      LeftRotate(gramps);
    }

  }


};

#endif