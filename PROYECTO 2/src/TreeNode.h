#pragma once
#include <string>
#include <vector>

struct TreeNode {
    int id;
    std::string label;
    bool isTerminal;
    std::vector<TreeNode*> children;
};