#pragma once
#include "ATL.hpp"
#include <filesystem>
namespace fs = std::filesystem;
#pragma once
template<class T>
auto operator==(const T &a,const T &b)->decltype(a.begin(),false){
    if (a.size()!=b.size()) return false;
    for (auto ai=a.begin(),bi=b.begin();ai!=a.end();ai++,bi++)
        if (!(*ai==*bi))
            return false;
    return true;
}

struct tester{
    static fs::path working_path;
    string name;
    struct data_manager{
        fs::path data_dir;
        struct data_iter{
            int i;
            data_iter():i(0){}
            data_iter& operator++(){
                return ++i,*this;
            }
            bool operator!=(const data_iter &a)const{
                return i!=a.i;
            }
        };
    };
    tester(const string& name):name(name){}
    virtual bool benchmark()=0;
};
fs::path tester::working_path;