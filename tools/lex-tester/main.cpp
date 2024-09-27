#include <atomic>
#include <array>
#include <cassert>
#include <chrono>
#include <concepts>
#include <filesystem>
#include <functional>
#include <fstream>
#include <iostream>
#include <memory>
#include <random>
#include <set>
#include <string>
#include <sstream>
#include <thread>
#include <vector>

#include "DataFlex.h"
#include "DataFlex_target.h"

namespace fsys = std::filesystem;

// not thread-local due to linker issues
int gDataLine;

thread_local fsys::path gCurrentPath;
thread_local std::unique_ptr<std::istream> gCurrentText;

thread_local std::unique_ptr<void, decltype(&yylex_destroy)> yy_current_globals(
    []() {
        void *ptr;
        yylex_init(&ptr);
        return ptr;
    }(),
    &yylex_destroy
);

thread_local std::unique_ptr<void, decltype(&yytarget::yylex_destroy)> yy_target_globals(
    []() {
        void *ptr;
        yytarget::yylex_init(&ptr);
        return ptr;
    }(),
    &yytarget::yylex_destroy
);

thread_local bool gSilenceFail = false;

void DataFail(const char *msg) {
    if (gSilenceFail) {
        return;
    }

    std::string path = !gCurrentPath.empty() ? gCurrentPath.string() : "<file>";
    std::cout << std::format("{}({}): {}\n", path, gDataLine + 1, msg) << std::flush;
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

std::string EscapeString(const std::string &str) {
    std::string escaped;
    for (auto c : str) {
        // clang-format off
        switch (c) {
            case '\0': escaped.append("\\0"); break;
            case '\a': escaped.append("\\a"); break;
            case '\b': escaped.append("\\b"); break;
            case '\f': escaped.append("\\f"); break;
            case '\n': escaped.append("\\n"); break;
            case '\r': escaped.append("\\r"); break;
            case '\t': escaped.append("\\t"); break;
            case '\v': escaped.append("\\v"); break;
            case '\\': escaped.append("\\\\"); break;
            case '\"': escaped.append("\\\""); break;
            case '\'': escaped.append("\\\'"); break;
            default: escaped.append(1, c); break;
        }
        // clang-format on
    }
    return escaped;
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
    yytarget::yy_actually_restart(yy_target_globals.get());

    while (DataToken token = (DataToken)yytarget::yylex(yy_target_globals.get())) {
        if (ignoreTokens.contains(token)) {
            continue;
        }

        std::cout << std::format(
            "Token: {:35} Text: {}\n",
            TokenToString(token),
            yytarget::yyget_text(yy_target_globals.get())
        ) << std::flush;
    }
}

bool CompareTokens(bool printSuccess) {
    struct MatchedToken {
        DataToken token;
        std::string text;

        MatchedToken(DataToken token_, const char *text_) : token(token_), text(text_) {}
    };

    gDataLine = 0;
    yytarget::yy_actually_restart(yy_target_globals.get());
    std::vector<MatchedToken> targetTokens;
    while (DataToken token = (DataToken)yytarget::yylex(yy_target_globals.get())) {
        targetTokens.emplace_back(token, yytarget::yyget_text(yy_target_globals.get()));
    }

    gCurrentText->clear();
    gCurrentText->seekg(0);
    gDataLine = 0;
    yy_actually_restart(yy_current_globals.get());
    std::vector<MatchedToken> currentTokens;
    while (DataToken token = (DataToken)yylex(yy_current_globals.get())) {
        currentTokens.emplace_back(token, yyget_text(yy_current_globals.get()));
    }

    bool success = true;
    if (currentTokens.size() != targetTokens.size()) {
        std::cout << std::format(
            "{}: Current token count ({}) mismatches target token count ({})!\n",
            gCurrentPath.string(),
            currentTokens.size(),
            targetTokens.size()
        ) << std::flush;
        success = false;
    }

    size_t count = std::min(targetTokens.size(), currentTokens.size());
    for (size_t i = 0; i < count; i++) {
        auto &target = targetTokens[i];
        auto &current = currentTokens[i];

        if (current.token != target.token || current.text != target.text) {
            // clang-format off
            std::cout << std::format(
                "{}: Tokens differ at index {}!\n"
                "- Current: token: {}, text: {}\n"
                "- Target:  token: {}, text: {}\n",
                gCurrentPath.string(), i,
                TokenToString(current.token), current.text,
                TokenToString(target.token), target.text
            ) << std::flush;
            // clang-format on
            success = false;
        }
    }

    if (success && printSuccess) {
        std::cout << "Tokens are identical.\n" << std::flush;
    }

    return success;
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

static void Parallelize(
    std::function<void(int threadCount, int threadIndex)> workProc,
    std::function<void()> monitorProc
) {
    unsigned int cores = std::thread::hardware_concurrency();
    if (cores > 1) {
        // Leave at least one core available to avoid tanking the OS completely
        cores--;
    }

    auto startTime = std::chrono::steady_clock::now();

    std::vector<std::thread> threads;
    for (int i = 0; i < cores; i++) {
        threads.emplace_back(workProc, cores, i);
    }

    bool finished = false;
    std::thread monitor([&finished, &monitorProc] {
        while (!finished) {
            monitorProc();
        }
    });

    for (auto &thread : threads) {
        thread.join();
    }

    finished = true;
    monitor.join();

    auto endTime = std::chrono::steady_clock::now();
    std::cout << std::format("Time elapsed: {0:%j}:{0:%T}\n", endTime - startTime)
              << std::flush;
}

const static std::vector<char> recurseChars = []() {
    // clang-format off
    std::vector<char> chars = { '\t', '\n', '\r' };
    // clang-format on
    for (int c = 32; c < 127; c++) {
        chars.push_back(c);
    }
    return chars;
}();

static void RecurseImpl(int depth, const std::string &str) {
    depth--;

    if (depth >= 3 && !str.empty()) {
        std::cout << std::format("Recursing \"{}\"\n", EscapeString(str)) << std::flush;
    }

    if (depth < 1) {
        gCurrentPath = str;
        gCurrentText = std::make_unique<std::istringstream>(str);
        gSilenceFail = true;
        CompareTokens(false);
    } else {
        for (char c : recurseChars) {
            RecurseImpl(depth, str + c);
        }
    }
}

void Recurse(int depth) {
    Parallelize(
        [depth](int threadCount, int threadIndex) {
            size_t count = std::ceil((float)recurseChars.size() / threadCount);
            size_t start = threadIndex * count;
            size_t end = std::min(start + count, recurseChars.size());

            for (size_t i = start; i < end; i++) {
                RecurseImpl(depth, std::string(1, recurseChars[i]));
            }
        },
        [] { std::this_thread::sleep_for(std::chrono::seconds(1)); }
    );
}

// clang-format off
const std::vector<std::string> fragments = {
    "0x12345678",
    "0x", "x1",

    "123", "+123", "-123",

    "1.0", "+2.0", "-3.0",
    "1.",  "+2.",  "-3.",
    ".1",  "+.2",  "-.3",
    ".",   "+.",   "-.",

    "1.0E1",  "+2.0E1",  "-3.0E1",      "1.0-E1",  "+2.0-E1",  "-3.0-E1",
    "1.0E+1", "+2.0E+1", "-3.0E+1",     "1.0-E+1", "+2.0-E+1", "-3.0-E+1",
    "1.0E-1", "+2.0E-1", "-3.0E-1",     "1.0-E-1", "+2.0-E-1", "-3.0-E-1",

    "1.E1",   "+2.E1",   "-3.E1",       "1.-E1",   "+2.-E1",   "-3.-E1",
    "1.E+1",  "+2.E+1",  "-3.E+1",      "1.-E+1",  "+2.-E+1",  "-3.-E+1",
    "1.E-1",  "+2.E-1",  "-3.E-1",      "1.-E-1",  "+2.-E-1",  "-3.-E-1",

    ".1E1",   "+.2E1",   "-.3E1",       ".1-E1",   "+.2-E1",   "-.3-E1",
    ".1E+1",  "+.2E+1",  "-.3E+1",      ".1-E+1",  "+.2-E+1",  "-.3-E+1",
    ".1E-1",  "+.2E-1",  "-.3E-1",      ".1-E-1",  "+.2-E-1",  "-.3-E-1",

    ".E1",    "+.E1",    "-.E1",        ".-E1",    "+.-E1",    "-.-E1",
    ".E+1",   "+.E+1",   "-.E+1",       ".-E+1",   "+.-E+1",   "-.-E+1",
    ".E-1",   "+.E-1",   "-.E-1",       ".-E-1",   "+.-E-1",   "-.-E-1",

    "\"asdf\"", "\"1234\"",
    "\'asdf\'", "\'1234\'",

    "$variable",
    "$index",
    "$count",
    "$name",
    "$id",

    "symbol",
    "../file.dta",
    "kDefine",

    "kDataUnhandled",

    "(array 1 2)",
    "{+ 1 2}",
    "[property]",

    "#include_opt",
    "#include",
    "#merge",
    "#ifdef",
    "#undef",
    "#endif",
    "#ifndef",
    "#define",
    "#else",
    "#autorun",
    "#endif",

    "; line comment\n",
    ";\n",
    "; ;\n",
    ";\t;\n",
    ";;;;;;;;\n",
    ";nospace\n",
    "asdf;jkl",

    "/* block comment */",
    "/*asdf*/",
    "/*jkl */",
    "/**/",
    "/* */",
    "/*\t*/",
    "/*****/",
    "/***** /* ***** ***/",

    "()", "{}", "[]",

    "/*", "*/",
};
// clang-format on

const std::vector<char> chars = [] {
    // clang-format off
    std::vector<char> chars = { '\n', '\r', '\t', };
    // clang-format on
    for (int c = 32; c < 127; c++) {
        chars.push_back(c);
    }
    return chars;
}();

std::atomic<size_t> gShuffleCount = 0;
std::atomic<bool> gShuffleSuccess = false;

static void ShuffleImpl(const std::string &insert, int seed) {
    std::mt19937 random(seed);

    std::uniform_int_distribution<unsigned int> fragCount(1, 10);
    std::uniform_int_distribution<unsigned int> fragPick(0, fragments.size() - 1);

    std::uniform_int_distribution<unsigned int> charStrCount(3, 15);
    std::uniform_int_distribution<unsigned int> charCount(1, 10);
    std::uniform_int_distribution<unsigned int> charPick(0, chars.size() - 1);

    // std::uniform_int_distribution<unsigned int> insertCount(1, 15);

    while (!gShuffleSuccess) {
        std::vector<std::string> picks;
        for (unsigned int frags = fragCount(random); frags > 0; frags--) {
            picks.push_back(fragments[fragPick(random)]);
        }

        for (unsigned int charStrs = charStrCount(random); charStrs > 0; charStrs--) {
            std::string str;
            for (unsigned int cc = charCount(random); cc > 0; cc--) {
                str += chars[charPick(random)];
            }

            picks.push_back(str);
        }

        for (auto &pick : picks) {
            assert(pick.length() > 0);
            std::uniform_int_distribution<unsigned int> strPick(0, pick.length() - 1);
            pick.insert(strPick(random), insert);
        }

        std::string str;
        for (size_t i = 0; i < picks.size(); i++) {
            if (random() % 2) {
                str += ' ';
            }
            str += picks[i];
        }

        gShuffleCount++;
        gCurrentPath = str;
        gCurrentText = std::make_unique<std::istringstream>(str);
        gSilenceFail = true;
        if (!CompareTokens(false)) {
            gShuffleSuccess = true;
            break;
        }
    }
}

void Shuffle(const std::string &insert) {
    std::random_device seeder;
    Parallelize(
        [&](int threadCount, int threadIndex) {
            ShuffleImpl(insert, seeder() * threadCount * threadIndex);
        },
        [] {
            std::cout << std::format("Shuffles tested: {}", gShuffleCount.load())
                      << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(10));
        }
    );
    // ShuffleImpl(insert, seeder());
}

void CharacterInsertions() {
    // clang-format off
    const std::vector<std::string> tests = {
        "0x12345678",
        "0x", "x1",

        "1", "+2", "-3",
        "012345",

        "1.0", "+2.0", "-3.0",
        "1.",  "+2.",  "-3.",
        ".1",  "+.2",  "-.3",
        ".",   "+.",   "-.",

        "1.0E1",  "+2.0E1",  "-3.0E1",      "1.0-E1",  "+2.0-E1",  "-3.0-E1",
        "1.0E+1", "+2.0E+1", "-3.0E+1",     "1.0-E+1", "+2.0-E+1", "-3.0-E+1",
        "1.0E-1", "+2.0E-1", "-3.0E-1",     "1.0-E-1", "+2.0-E-1", "-3.0-E-1",

        "1.E1",   "+2.E1",   "-3.E1",       "1.-E1",   "+2.-E1",   "-3.-E1",
        "1.E+1",  "+2.E+1",  "-3.E+1",      "1.-E+1",  "+2.-E+1",  "-3.-E+1",
        "1.E-1",  "+2.E-1",  "-3.E-1",      "1.-E-1",  "+2.-E-1",  "-3.-E-1",

        ".1E1",   "+.2E1",   "-.3E1",       ".1-E1",   "+.2-E1",   "-.3-E1",
        ".1E+1",  "+.2E+1",  "-.3E+1",      ".1-E+1",  "+.2-E+1",  "-.3-E+1",
        ".1E-1",  "+.2E-1",  "-.3E-1",      ".1-E-1",  "+.2-E-1",  "-.3-E-1",

        ".E1",    "+.E1",    "-.E1",        ".-E1",    "+.-E1",    "-.-E1",
        ".E+1",   "+.E+1",   "-.E+1",       ".-E+1",   "+.-E+1",   "-.-E+1",
        ".E-1",   "+.E-1",   "-.E-1",       ".-E-1",   "+.-E-1",   "-.-E-1",

        "\"asdf\"",
        "\'asdf\'",

        "$variable",
        "symbol",
        "kDataUnhandled",

        "(array 1 2)",
        "{+ 1 2}",
        "[property]",

        "#include_opt ../file.dta",
        "#include ../file.dta",
        "#merge ../file.dta",
        "#ifdef kDefine",
        "#undef kDefine",
        "#endif",
        "#ifndef kDefine",
        "#define kDefine",
        "#else",
        "#autorun {action}",
        "#endif",
        "#bad",
        "#",
        "##",
        "# #",
        "#\t#",
        "#(#)",
        "#{#}",
        "#[#]",

        "; line comment",
        ";;",
        "; ;",
        ";\t;",
        ";;;;;;;;",
        ";nospace",
        "asdf;jkl",

        "/* block comment */",
        "/*asdf*/",
        "/*jkl */",
        "/**/",
        "/* */",
        "/*\t*/",
        "*/",
        "/*****/",
        "/***** /* ***** ***/",
    };
    // clang-format on

    // clang-format off
    std::vector<char> insertChars = { '\0', '\n', '\r', '\t', };
    // clang-format on
    for (int c = 32; c < 127; c++) {
        insertChars.push_back(c);
    }

    for (auto &str : tests) {
        for (char c : insertChars) {
            for (size_t i = 0; i <= str.length(); i++) {
                std::string copy = str;
                copy.insert(i, 1, c);

                gCurrentPath = copy;
                gCurrentText = std::make_unique<std::istringstream>(copy);
                gSilenceFail = true;
                CompareTokens(false);
            }
        }
    }
}

void CompareText(const std::string &text) {
    gCurrentPath.clear();
    gCurrentText = std::make_unique<std::istringstream>(text);
    CompareTokens(true);
}

int main() {
    // Recurse(10);
    // CharacterInsertions();
    // CompareText("/*/*/");
    // return 0;

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
