//
// Created by Michel on 04.06.2020.
//

#ifndef ACACIA_JUNIT_H
#define ACACIA_JUNIT_H

#include <report/report.h>
#include <fstream>

namespace acacia {

    void generateJUnitReport(Report &report, std::ofstream &file);

}

#endif //ACACIA_JUNIT_H
