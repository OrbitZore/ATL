#include "ATL.hpp"
#include "test.hpp"

using namespace std;

int main(int argc,char *argv[]){
    {
        TesterManager::working_path=fs::path(argv[0]);
        do{
            TesterManager::working_path=TesterManager::working_path.parent_path();
        }while (![&](){
            auto dir=fs::directory_iterator(TesterManager::working_path);
            for (auto &i:dir){
                if (i.path().filename()=="data"){
                    return true;
                }
            }
            return false;
        }());
        TesterManager::working_path/="data";
    }
    cerr << TesterManager::working_path << endl;
    TesterManager test;
    bool f=test.benchmark();
    cerr << "Complete! Status:" << f << endl;
}