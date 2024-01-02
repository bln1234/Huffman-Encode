#include "frequency_counter.h"


FrequencyCounter::FrequencyCounter() {}


FrequencyCounter::FrequencyCounter(const std::wstring& filename) {
    // 在构造函数中计算字符频率
    this->frequencyTable = countFrequency(filename);
}


FrequencyCounter::~FrequencyCounter() {}


// 计算字符频率
std::map<std::wstring, int> FrequencyCounter::countFrequency(const std::wstring& filename) {
    std::wifstream file(filename);
    
    // 设置当前文件流为UTF-8
    file.imbue(std::locale(file.getloc(), new std::codecvt_utf8<wchar_t>));

    if (!file.is_open()) {
        throw std::runtime_error("FrequencyCounter无法打开文件");
    }

    std::map<std::wstring, int> frequencyTable;
    std::wstring line;
    while (std::getline(file, line)) {
        for (wchar_t ch : line) {
            frequencyTable[std::wstring(1, ch)]++;
        }
    }
    file.close();
    return frequencyTable;
}


void FrequencyCounter::writeFrequency(const std::wstring& outputFilename) {
    std::wofstream outFile(outputFilename);
    outFile.imbue(std::locale(outFile.getloc(), new std::codecvt_utf8<wchar_t>));

    if (!outFile.is_open()) {
        throw std::runtime_error("FrequencyCounter无法创建文件: ");
    }

    for (auto& pair : frequencyTable) {
        outFile << pair.first << L": " << pair.second << L"\n";
    }
    outFile.close();
}


