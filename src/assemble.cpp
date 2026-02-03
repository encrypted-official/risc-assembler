#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>

void fetch_file(const std::string& path, std::vector<std::string>& words)
{
    std::ifstream file(path);
    std::string line;
    
    words.clear();

    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        std::string word;

        while (iss >> word) {
            words.push_back(word);
        }
    }
}

int main(int argc, char* argv[])
{
    if (argc < 2) return 1;

    std::vector<std::string> words;

    fetch_file(argv[1], words);

    for (std::string str : words) {
        std::cout << str << " ";
    }

    std::cout << std::endl;

    return 0;
}
