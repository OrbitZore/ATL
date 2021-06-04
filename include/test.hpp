#pragma once
#include "ATL.hpp"
#include <filesystem>
namespace fs = std::filesystem;
#pragma once
struct Tester{
    static bool cmp(const string& a,const string &b){
        size_t i=0,j=0;
        while (i<a.size()&&j<b.size()){
            if (a[i]!=b[j]){
                while (i<a.size()&&a[i]==' ') i++;
                while (j<b.size()&&b[j]==' ') j++;
                if (i==a.size()||j==b.size()||(a[i]=='\n'&&a[j]=='\n')) continue;
                return false;
            }else i++,j++;
        }
        while (i<a.size()&&a[i]=='\n') i++;
        while (j<b.size()&&b[j]=='\n') j++;
        return i==a.size()&&j==b.size();
    }
    template<class funcT>
    static bool run(funcT func,istream &is,istream &as){
        ostringstream oss;
        func(is,oss);
        string output=oss.str();
        string ans;char c;
        while ((c=as.get())&&as.good()) ans+=c;
        return cmp(output,ans);
    }
};
map<string,function<void(istream&,ostream&)>> playground={
    {"ShortestPath",[](istream &in,ostream &out){
        int n,m,s,t;
        in>>n>>m>>s>>t;
        graph<wedge,ll> G;
        G.resize(n+1);
        for (int i=0;i<m;i++){
            int u,v;ll w;
            in>>u>>v>>w;
            G.add2Edge({u,v,w});
        }
        out<<dijkstra<ll>(G,s)[t]<<endl;
    }},
};
struct TesterManager{
    static fs::path working_path;
    bool benchmark(){
        size_t id=0;
        for (auto p: fs::directory_iterator(working_path)){
            fs::path subpath=p.path();
            cerr<<"Running Task:"<<p.path().filename()<<endl;
            cerr<<"subTask:";
            for (int i=1;;i++){
                fs::directory_entry in(subpath/(to_string(i)+".in"));
                fs::directory_entry ans(subpath/(to_string(i)+".ans"));
                if (!in.exists()||!ans.exists()) break;
                ifstream is(in.path()),as(ans.path());
                auto it=playground.find(p.path().filename());
                if (it!=playground.end()){
                    cerr<<"["<<i<<",";
                    bool status=Tester::run(it->second,is,as);
                    if (status) {
                        cerr<<"OK";
                    }
                    else {
                        cerr<<"NO";
                    }
                    cerr<<"]";
                }
            }
            cerr<<endl;
        }
        return true;
    }
};
fs::path TesterManager::working_path;

