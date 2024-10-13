#include "SearchNode.h"
#include <memory>

using namespace std;

SearchNode::SearchNode(shared_ptr<SearchNode> _parent) : parent{_parent}, lastValueTried{}, x{}, y{} {}
SearchNode::SearchNode(shared_ptr<SearchNode> _parent, pair<int, int> position) : parent{_parent}, x{position.first}, y{position.second}, lastValueTried{} {}

shared_ptr<SearchNode> SearchNode::getParent() const {
    return parent;
}

int SearchNode::getX() const {
    return x;
}

int SearchNode::getY() const {
    return y;
}

int SearchNode::getLastValueTried() const {
    return lastValueTried;
}

void SearchNode::setX(int x) {
    this->x=x;
}

void SearchNode::setY(int y) {
    this->y=y;
}

void SearchNode::setLastValueTried(int lastValueTried) {
    this->lastValueTried=lastValueTried;
}