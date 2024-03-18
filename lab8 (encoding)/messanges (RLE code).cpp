#include <iostream>
#include <cmath>
#include <vector>

// !a != !b  => XOR
//char - '0' => int
// переделать на массив из вектора (если будет ошибка по памяти) => надо считать количество проверяющих бит по формуле (которая с логарифмом)
// как минимум VecXor на массив переделать не сложно

std::string RawToStr(std::string const &RawData, int CurPow);
bool StrToXor (std::string const &StrBin);
int CheckError(std::string const &RawData, std::vector<bool> const &VecXor);
void DeleteUPrint(std::string &RawData, int NumContrBits, int Error);

int main() {
    std::string RawData;
    int Count;
    std::cin>>Count;
    while (std::cin>>RawData){
        std::vector<bool> VecXor;
        int CurPow = 0;
        for (int i = 0; i < RawData.size(); ++i) {
            if (i == pow(2,CurPow)) {
                VecXor.emplace_back(StrToXor(RawToStr(RawData, CurPow)));
                CurPow++; //// В самом конце if
            }
        }
        DeleteUPrint(RawData, (int)VecXor.size(), CheckError(RawData, VecXor));
    }
    return 0;
}

std::string RawToStr(std::string const &RawData, int CurPow){
    std::string StrBin;
    const int Step = (int)pow(2, CurPow);
    int Start = (int)pow(2, CurPow);
    if (CurPow == 0) Start--;
    int End = (int)(pow(2, CurPow) * 2) - 2;
    int pos = Start;
    while (pos < RawData.size()){
        if (pos <= End && pos != 0) {
            StrBin += RawData[pos];
        }
        if (pos == End){
            pos += (Step + 1);
            End += (Step * 2);
        }
        else{
            pos++;
        }
    }
    return StrBin;
}

bool StrToXor (std::string const &StrBin){
    bool Res;
    if (StrBin.size() > 2) {
        Res = StrBin[0] - '0' xor StrBin[1] - '0';
        for (int i = 2; i < StrBin.size(); ++i) {
            Res = Res xor StrBin[i] - '0';
        }
    }
    else if (StrBin.size() == 2){
        Res = StrBin[0] - '0' xor StrBin[1] - '0';
    }
    else{
        Res = StrBin[0] - '0';
    }
    return Res;
}

//возвращает номер бита с ошибкой
int CheckError(std::string const &RawData, std::vector<bool> const &VecXor){
    int Error = 0;
    for (int i = 0; i < VecXor.size(); ++i) {
        int Pow = (int)pow(2, i)-1;
        if (i == 0) Pow = 0;
        if (RawData[Pow] - '0' != VecXor[i]){ //            RawData[pow(2, i)] = (!(RawData[pow(2, i)]-'0'))+'0');
            Error += (int)pow(2, i);
        }
    }
    return Error;
}

void DeleteUPrint(std::string &RawData, int NumContrBits, int Error){
    if (Error == 0){
        for (int i = 0; i < NumContrBits; ++i) {
            RawData.erase(i==0?0:(int)pow(2, i)-i-1, 1);
        }
        std::cout << RawData << "\n";
    }
    else{
        if (RawData[Error-1] == '0'){
            RawData[Error-1] = '1';
        }
        else {
            RawData[Error-1] = '0';
        }
        for (int i = 0; i < NumContrBits; ++i) {
            RawData.erase(i==0?0:(int)pow(2, i)-i-1, 1);
        }
        std::cout << RawData << "\n";
    }
}
