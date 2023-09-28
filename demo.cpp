#include<bits/stdc++.h>
using namespace std;

vector<int> zFunc(string& s){
    int n=s.length();
    vector<int> z(n,0);
    int l=0,r=0;
    for(int i=1;i<n;i++){
        if(i<r){
            z[i]=min(r-i,z[i-l]);
        }
        while(i+z[i]<n && s[i+z[i]]==s[z[i]]){
                z[i]++;
        }
        if(i+z[i]>r){
            l=i;
            r=i+z[i];
        }
        
    }
    return z;
}

int main(){
    string s;
    cin>>s;
    int n=s.length();
    vector<int> z=zFunc(s);
    for(int i=0;i<n;i++)cout<<z[i]<<" ";
    cout<<endl;

    return 0;
}