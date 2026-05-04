#pragma once
#include <string>
#include "BoardModel.h"

class ReportGenerator {
private:
    Board board;

public:
    ReportGenerator(const Board& board);

    void generateKanbanReport(const std::string& filename);
};