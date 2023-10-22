#include <iostream>
#include <string>
#include <regex>
#include <vector>
#include <unordered_map>
using namespace std;

const string DIRECTIVE = "Directive";
const string COMMENT = "Comment";
const string KEYWORD = "Keyword";
const string OPERATOR = "Operator";
const string PUNCTUATION = "Punctuation sign";
const string STRING = "String";
const string NUMBER = "Number";
const string VARIABLE = "Variable";

struct Lexeme {
    string value;
    string lexemeClass;
};

unordered_map<string, string> regexPatterns = {
        {DIRECTIVE, R"(<\?php|<\?|\?>)"},
        {COMMENT, R"(\/\/[^\n]*|/\*[\s\S]*?\*/)"},
        {STRING, R"(@?\"([^\"\n]*)\")"},
        {NUMBER, R"(\b\d+(\.\d+)?\b)"},
        {PUNCTUATION, R"(\(|\)|\{|\}|\[|\]|\;|\,)"},
        {OPERATOR, R"(\+|\-|\*|\/|\=|\==|\<|\>)"},
        {KEYWORD, R"(\b(abstract|and|array|as|break|case|catch|class|clone|const|continue|declare|default|do|echo|else|elseif|empty|enddeclare|endfor|endforeach|endif|endswitch|endwhile|eval|exit|extends|final|for|foreach|function|global|goto|if|implements|include|instanceof|insteadof|interface|isset|list|namespace|new|or|print|private|protected|public|require|return|static|switch|throw|trait|try|unset|use|var|while|xor)\b)"},
        {VARIABLE, R"(\$[a-zA-Z_][a-zA-Z0-9_]*)"}
};

vector<Lexeme> findLexemes(const string& text) {

    vector<Lexeme> lexemes;

    for (const auto& entry : regexPatterns) {
        regex pattern(entry.second);
        auto words_begin = sregex_iterator(text.begin(), text.end(), pattern);
        auto words_end = sregex_iterator();
        for (auto i = words_begin; i != words_end; ++i) {
            Lexeme lexeme;
            lexeme.value = i->str();
            lexeme.lexemeClass = entry.first;
            lexemes.push_back(lexeme);
        }
    }

    return lexemes;
}

void printLexemes(const vector<Lexeme>& lexemes) {
    for (const auto& lexeme : lexemes) {
        cout << lexeme.value << " ---> " << lexeme.lexemeClass << "\n";
    }
}

int main() {
    string sampleText = R"(
        <?php
            $x = 42;
            echo "Hello, world!";
    
            // Comment

            if ($x == 42) {
                echo "x equals 42";
            } else {
                echo "x not equal 42";
            }
        ?>
    )";

    printLexemes(findLexemes(sampleText));
    return 0;
}