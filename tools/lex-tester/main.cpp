#include <array>
#include <cassert>
#include <concepts>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>
#include <set>
#include <string>
#include <sstream>
#include <vector>

#include "DataFlex.h"
#include "DataFlex_target.h"

namespace fsys = std::filesystem;

int gDataLine;
fsys::path gCurrentPath;
std::unique_ptr<std::istream> gCurrentText;

void DataFail(const char *msg) {
    std::string path = !gCurrentPath.empty() ? gCurrentPath.string() : "<file>";
    std::cout << path << "(" << (gDataLine + 1) << "): " << msg << std::endl;
}

int DataInput(void *buffer, int size) {
    if (gCurrentText->fail() || gCurrentText->eof())
        return 0;

    gCurrentText->read((char *)buffer, size);
    if (gCurrentText->eof()) {
        return gCurrentText->gcount();
    } else if (gCurrentText->fail()) {
        DataFail("failed to read from file");
        return 0;
    }

    return size;
}

// clang-format off
const char *TokenToString(DataToken token) {
#define TOKENCASE(tok) case tok: return #tok
    switch (token) {
    // case kDataTokenFinished:

    case kDataTokenNotRecognized:
        return "(skipped)";

    TOKENCASE(kDataTokenNewline);
    TOKENCASE(kDataTokenCarriageReturn);

    TOKENCASE(kDataTokenComment);
    TOKENCASE(kDataTokenBlockCommentStart);
    TOKENCASE(kDataTokenBlockCommentText);
    TOKENCASE(kDataTokenBlockCommentSkip);
    TOKENCASE(kDataTokenBlockCommentNewline);
    TOKENCASE(kDataTokenBlockCommentEnd);

    TOKENCASE(kDataTokenHex);
    TOKENCASE(kDataTokenFloat);
    TOKENCASE(kDataTokenFloatExp);
    TOKENCASE(kDataTokenInt);

    TOKENCASE(kDataTokenString);
    TOKENCASE(kDataTokenSymbol);
    TOKENCASE(kDataTokenQuotedSymbol);
    TOKENCASE(kDataTokenVar);
    TOKENCASE(kDataTokenUnhandled);

    TOKENCASE(kDataTokenArrayOpen);
    TOKENCASE(kDataTokenArrayClose);
    TOKENCASE(kDataTokenPropertyOpen);
    TOKENCASE(kDataTokenPropertyClose);
    TOKENCASE(kDataTokenCommandOpen);
    TOKENCASE(kDataTokenCommandClose);

    TOKENCASE(kDataTokenDefine);
    TOKENCASE(kDataTokenUndef);
    TOKENCASE(kDataTokenInclude);
    TOKENCASE(kDataTokenIncludeOptional);
    TOKENCASE(kDataTokenMerge);
    TOKENCASE(kDataTokenAutorun);

    TOKENCASE(kDataTokenIfdef);
    TOKENCASE(kDataTokenIfndef);
    TOKENCASE(kDataTokenElse);
    TOKENCASE(kDataTokenEndif);

    default:
        return "<unknown>";
    }
#undef TOKENCASE
}
// clang-format on

void DumpTokens() {
    static std::set ignoreTokens = {
        kDataTokenNotRecognized,
        kDataTokenNewline,
        kDataTokenCarriageReturn,
        kDataTokenBlockCommentNewline,
    };

    gDataLine = 0;
    yytarget::yy_actually_restart();

    while (DataToken token = (DataToken)yytarget::yylex()) {
        if (ignoreTokens.contains(token)) {
            continue;
        }

        std::cout << std::format(
            "Token: {:35} Text: {}", TokenToString(token), yytarget::yytext
        ) << std::endl;
    }
}

void CompareTokens(bool printSuccess) {
    struct MatchedToken {
        DataToken token;
        std::string text;

        MatchedToken(DataToken token_, const char *text_) : token(token_), text(text_) {}
    };

    gDataLine = 0;
    yytarget::yy_actually_restart();
    std::vector<MatchedToken> targetTokens;
    while (DataToken token = (DataToken)yytarget::yylex()) {
        targetTokens.emplace_back(token, yytarget::yytext);
    }

    gCurrentText->clear();
    gCurrentText->seekg(0);
    gDataLine = 0;
    yy_actually_restart();
    std::vector<MatchedToken> currentTokens;
    while (DataToken token = (DataToken)yylex()) {
        currentTokens.emplace_back(token, yytext);
    }

    bool written = false;
    auto header = [&written]() {
        if (!written && !gCurrentPath.empty()) {
            std::cout << gCurrentPath.string() << ":" << std::endl;
            written = true;
        }
    };

    if (currentTokens.size() != targetTokens.size()) {
        header();
        std::cout << std::format(
            "Current token count ({}) mismatches target token count ({})!",
            currentTokens.size(),
            targetTokens.size()
        ) << std::endl;
    }

    size_t count = std::min(targetTokens.size(), currentTokens.size());
    for (size_t i = 0; i < count; i++) {
        auto &target = targetTokens[i];
        auto &current = currentTokens[i];

        if (current.token != target.token || current.text != target.text) {
            header();
            // clang-format off
            std::cout << std::format("Tokens differ at index {}!\n", i);
            std::cout << std::format("- Current: token: {}, text: {}\n", TokenToString(current.token), current.text);
            std::cout << std::format("- Target:  token: {}, text: {}\n", TokenToString(target.token), target.text);
            // clang-format on
            std::cout << std::flush;
            return;
        }
    }

    if (printSuccess) {
        std::cout << "Tokens are identical." << std::endl;
    }
}

void PromptTokenMode() {
    std::cout << "Select a token handling mode:\n";
    std::cout << "- 1: Dump tokens\n";
    std::cout << "- 2: Compare tokens\n";
    std::cout << "Selection: " << std::flush;

    int tokenMode;
    std::cin >> tokenMode;
    std::cin.ignore(1); // ignore newline
    std::cout << std::endl;

    switch (tokenMode) {
    case 1:
        DumpTokens();
        break;
    case 2:
        CompareTokens(true);
        break;
    }
}

void ReadInput() {
    std::cout << "Enter text to lex: ";

    std::string input;
    std::getline(std::cin, input);
    std::cout << std::endl;

    gCurrentPath.clear();
    gCurrentText = std::make_unique<std::istringstream>(input);
    PromptTokenMode();
}

void ReadFile() {
    std::cout << "Enter file path to read: ";

    std::string path;
    std::getline(std::cin, path);
    std::cout << std::endl;

    gCurrentPath = path;
    gCurrentText = std::make_unique<std::ifstream>(gCurrentPath, std::ios::binary);
    PromptTokenMode();
}

void ReadDirectory() {
    std::cout << "Enter directory to enumerate: ";

    std::string directory;
    std::getline(std::cin, directory);
    std::cout << std::endl;

    std::set<fsys::path> ignoreFolders;
    std::cout << "Enter any folder names to ignore (leave empty to end):\n";
    while (true) {
        std::string skip;
        std::cout << "- " << std::flush;
        std::getline(std::cin, skip);
        if (skip.empty()) {
            break;
        }

        ignoreFolders.insert(skip);
    }

    auto lex_file = [](const fsys::path &path) {
        gCurrentPath = path;
        gCurrentText = std::make_unique<std::ifstream>(path, std::ios::binary);
        CompareTokens(false);
    };

    for (const auto &entry : fsys::directory_iterator(directory)) {
        if (entry.is_directory()) {
            if (ignoreFolders.contains(entry.path().filename())) {
                std::cout << "Ignoring top-level folder " << entry << std::endl;
                continue;
            }

            std::cout << "Reading top-level folder " << entry << std::endl;
            for (const auto &inner : fsys::recursive_directory_iterator(entry)) {
                if (!inner.is_directory() && inner.path().extension() == ".dta") {
                    lex_file(inner.path());
                }
            }
        } else if (entry.path().extension() == ".dta") {
            lex_file(entry.path());
        }
    }
}

int main() {
    std::cout << "Select a read mode:\n";
    std::cout << "- 1: Enter text\n";
    std::cout << "- 2: Read file\n";
    std::cout << "- 3: Enumerate directory (compare tokens)\n";
    std::cout << "Selection: " << std::flush;

    int readMode;
    std::cin >> readMode;
    std::cin.ignore(1); // ignore newline
    std::cout << std::endl;

    switch (readMode) {
    case 1:
        ReadInput();
        break;
    case 2:
        ReadFile();
        break;
    case 3:
        ReadDirectory();
        break;
    }

    return 0;
}
