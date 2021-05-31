#include "ATL.hpp"
#include "test.hpp"

using namespace std;

int main(int argc,char *argv[]){
    {
        tester::working_path=fs::path(argv[0]);
        do{
            tester::working_path=tester::working_path.parent_path();
        }while (![&](){
            auto dir=fs::directory_iterator(tester::working_path);
            for (auto &i:dir){
                if (i.path().filename()=="data"){
                    return true;
                }
            }
            return false;
        }());
        tester::working_path/="data";
    }
    cout << tester::working_path << endl;
}