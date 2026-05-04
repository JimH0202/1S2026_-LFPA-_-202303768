#pragma once
#include <string>
#include <vector>

struct Task {
    std::string name;
    std::string priority;
    std::string responsible;
    std::string deadline;
};

struct Column {
    std::string name;
    std::vector<Task> tasks;
};

struct Board {
    std::string name;
    std::vector<Column> columns;
};
