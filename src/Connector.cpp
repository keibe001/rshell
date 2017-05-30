#include "Connector.h"

Connector::Connector() {} 

andConnector::andConnector(Base* left, Base* right) {
    this->left = left;
    this->right = right;
}

bool andConnector::run() {
    if (this->left->run()) {
        if (this->right->run()) {
            return true;
        }
    }
    
    return false;
}

Connector::Connector(Base* left, Base* right) {
    this->left = left;
    this->right = right;
}

SemiConnector::SemiConnector(Base* left, Base* right) {
    this->left = left;
    this->right = right;
    hasRight = true;
}

SemiConnector::SemiConnector(Base* left) {
    this->left = left;
    hasRight = false;
}

bool SemiConnector::run() {
    this->left->run();
    
    if (hasRight) {
        if (this->right->run()) {
            return true;
        }
        else {
            return false;
        }
    }
    
    return true;
    
}

orConnector::orConnector(Base* left, Base* right) {
    this->left = left;
    this->right = right;
}

bool orConnector::run() {
    if (this->left->run() == false) {
        if (this->right->run()) {
            return true;
        }
        else {
            return false;
        }
    }
    else {
        return true;
    }
    return false;
}
