#pragma once
#include <string>
#include "BoardModel.h"

struct ResponsableStats {
    int total = 0;
    int alta = 0;
    int media = 0;
    int baja = 0;
};

class ReportGenerator {
private:
    Board board;

public:
    ReportGenerator(const Board& board);

    void generateKanbanReport(const std::string& filename);
    void generateResponsableReport(const std::string& filename);
};