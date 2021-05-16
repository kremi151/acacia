//
// Created by Michel on 13.05.2021.
//

#include "scan_file.h"

#include <fstream>
#include <regex>
#include <sstream>
#include <functional>
#include "scan_suite.h"
#include "utils.h"
#include "logging.h"

namespace acacia::generator {

    std::string stripComments(const std::string &inContent) {
        std::stringstream ss;

        // Flags to indicate that single line and multiple line comments
        // have started or not.
        bool s_cmt = false;
        bool m_cmt = false;

        // Traverse the given program
        for (size_t i = 0; i < inContent.length(); i++) {
            if (s_cmt && inContent[i] == '\n') {
                // If single line comment flag is on, then check for end of it
                s_cmt = false;
            } else if (m_cmt && inContent[i] == '*' && inContent[i + 1] == '/') {
                // If multiple line comment is on, then check for end of it
                m_cmt = false;
                i++;
            } else if (s_cmt || m_cmt) {
                // If this character is in a comment, ignore it
                continue;
            } else if (inContent[i] == '/' && inContent[i + 1] == '/') {
                // Check for beginning of comments and set the appropriate flags
                s_cmt = true;
                i++;
            } else if (inContent[i] == '/' && inContent[i + 1] == '*') {
                m_cmt = true;
                i++;
            } else {
                // If current character is a non-comment character, write it to the string stream
                ss << inContent[i];
            }
        }
        return ss.str();
    }

    int analyzeByMacros(const std::string &inContent, const std::function<int (const std::string &, const std::vector<std::string> &)>& callback) {
        std::regex macroRegex(R"(^[ \t]*(#[\S]+)(?:[ \t]+(.+))?$)");
        std::smatch macroMatch;
        std::smatch nextMacroMatch;

        std::string content = inContent;
        std::vector<std::string> activeMacros;

        bool firstMatch = true;
        bool hasMacros = false;
        int status = 0;

        while (std::regex_search(content, macroMatch, macroRegex)) {
            hasMacros = true;

            if (firstMatch) {
                firstMatch = false;
                status = callback(macroMatch.prefix(), activeMacros);
                if (status != 0) {
                    return status;
                }
                content = content.substr(macroMatch.position());
                continue;
            }

            std::string macroName = macroMatch.str(1);
            std::string macroArg = macroMatch.str(2);
            if (macroName == "#if" || macroName == "#ifdef" || macroName == "#ifndef" || macroName == "#elif") {
                std::string macro = macroName;
                macro += " ";
                macro += macroArg;
                activeMacros.emplace_back(macro);
            } else if (macroName == "#else") {
                activeMacros.emplace_back("#else");
            } else if (macroName == "#endif") {
                popBackToStartingIfMacro(activeMacros);
            }

            std::string suffix = macroMatch.suffix();
            if (!std::regex_search(suffix, nextMacroMatch, macroRegex)) {
                status = callback(suffix, activeMacros);
                if (status != 0) {
                    return status;
                }
                break;
            }

            status = callback(suffix.substr(0, nextMacroMatch.position()), activeMacros);
            if (status != 0) {
                return status;
            }
            content = suffix.substr(nextMacroMatch.position());
        }

        if (!hasMacros) {
            status = callback(inContent, activeMacros);
            if (status != 0) {
                return status;
            }
        }

        return status;
    }

}

int acacia::generator::analyzeFile(const std::string &inputPath, std::vector<FileTestSuite> &suitesOut) {
    fprintf(stdout, PRINT_BLUE "Analyzing test source file %s...\n" PRINT_RESET, inputPath.c_str());

    std::ifstream ifstream(inputPath);
    if (!ifstream) {
        fprintf(stderr, "Cannot read test source file at %s\n", inputPath.c_str());
        return 2;
    }

    std::string content((std::istreambuf_iterator<char>(ifstream)),
                        std::istreambuf_iterator<char>());
    ifstream.close();

    content = stripComments(content);

    return analyzeByMacros(content, [&](const std::string &code, const std::vector<std::string> &activeMacros) {
        std::regex suiteRegex(R"(TEST_SUITE\s*\(([^)]+)\)\s*\{)");
        std::smatch suiteMatch;

        std::string innerContent = code;
        while (std::regex_search(innerContent, suiteMatch, suiteRegex)) {
            std::string suiteName = suiteMatch.str(1);
            printf("- Found test suite " PRINT_GREEN "%s" PRINT_RESET "\n", suiteName.c_str());

            innerContent = suiteMatch.suffix();
            size_t suiteEndPosition = findClosingCurly(innerContent);

            // TODO: Re-enable for AOT test case code generation
            /*if (suiteEndPosition == 0) {
                fprintf(stderr, "Syntax error in %s: No closing curly found for test suite %s\n", inputPath.c_str(), suiteName.c_str());
                return 3;
            }*/

            int status = scanSuite(innerContent, suiteEndPosition, suiteName, inputPath, suitesOut, activeMacros);
            if (status != 0) {
                return status;
            }

            innerContent = innerContent.substr(suiteEndPosition + 1);
        }

        return 0;
    });
}
