#include <iostream>
#include <fstream>
#include <locale>
#include <string>
#include <list>
#include <codecvt>
#include <future>
#include <vector>
#include <thread>

int grep(std::string filename, std::wstring word) {
    std::locale loc("pl_PL.UTF-8");
    std::wfstream file(filename);
    file.imbue(loc);
    std::wstring line;
    unsigned int count = 0;
    while (getline(file, line)) {
        for (auto pos = line.find(word,0);
             pos != std::string::npos;
             pos = line.find(word, pos+1))
            count++;
    }
    return count;
}

void list_grep(const std::list<std::string>& filenames, std::wstring word, std::promise<unsigned int>& len_promise) {
    // TODO: implement
}

int main() {
    const unsigned int thread_count = 4;
    std::ios::sync_with_stdio(false); // block C-style IO, as streams will have a different locale
    std::locale loc("pl_PL.UTF-8");
    std::wcout.imbue(loc); // put our locale on I/O streams
    std::wcin.imbue(loc);

    std::wstring word;
    std::getline(std::wcin, word);

    std::wstring s_file_count;
    std::getline(std::wcin, s_file_count);
    int file_count = std::stoi(s_file_count);

    std::vector<std::list<std::string>> lists_filenames{};
    for (int thread = 0; thread < thread_count; thread++) {
        lists_filenames.push_back(std::list<std::string>{});
    }
    std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;

    for (int file_num = 0, thread = 0;
         file_num < file_count;
         file_num++, thread = (thread + 1) % thread_count) {
        std::wstring w_filename;
        std::getline(std::wcin, w_filename);
        std::string s_filename = converter.to_bytes(w_filename);
        lists_filenames[thread].push_back(s_filename);
    }

    // TODO: create and start threads
    int count = 0; 
    // TODO: collect results from threads
    std::wcout << count << std::endl;
}
