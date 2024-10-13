#ifndef SEARCH_NODE_H
#define SEARCH_NODE_H
#include <utility>

#include <memory>
class SearchNode {
    public:
    SearchNode(std::shared_ptr<SearchNode> _parentPointer);
    SearchNode(std::shared_ptr<SearchNode> _parentPointer, std::pair<int, int> position);
    
    std::shared_ptr<SearchNode> getParent() const;
    int getX() const;
    int getY() const;
    int getLastValueTried() const;
    void setX(int x);
    void setY(int y);
    void setLastValueTried(int lastValueTried);

    private:
    std::shared_ptr<SearchNode> parent;
    int lastValueTried;
    int x, y;
};

#endif