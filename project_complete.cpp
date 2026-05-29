#include "my_inf_arith.h"
#include <algorithm>
#include <stdexcept>
#include <vector>

using namespace std;

namespace InfiniteArithmetic {

static string strip(string s){
    bool neg=false;
    if(!s.empty() && s[0]=='-'){ neg=true; s=s.substr(1); }
    size_t p=s.find_first_not_of('0');
    s=(p==string::npos)?"0":s.substr(p);
    return (neg && s!="0") ? "-"+s : s;
}

static int absCmp(string a,string b){
    if(a.size()!=b.size()) return a.size()<b.size()?-1:1;
    if(a==b) return 0;
    return a<b?-1:1;
}

static string absAdd(string a,string b){
    string r="";
    int c=0,i=a.size()-1,j=b.size()-1;
    while(i>=0||j>=0||c){
        int s=c;
        if(i>=0) s+=a[i--]-'0';
        if(j>=0) s+=b[j--]-'0';
        r.push_back(char('0'+s%10));
        c=s/10;
    }
    reverse(r.begin(),r.end());
    return strip(r);
}

static string absSub(string a,string b){
    string r="";
    int br=0,i=a.size()-1,j=b.size()-1;
    while(i>=0){
        int d=(a[i]-'0')-br-(j>=0?(b[j]-'0'):0);
        if(d<0){ d+=10;br=1;} else br=0;
        r.push_back(char('0'+d));
        i--;j--;
    }
    reverse(r.begin(),r.end());
    return strip(r);
}

static string absMul(string a,string b){
    vector<int> v(a.size()+b.size(),0);
    for(int i=a.size()-1;i>=0;i--)
      for(int j=b.size()-1;j>=0;j--){
        int p=(a[i]-'0')*(b[j]-'0');
        p+=v[i+j+1];
        v[i+j+1]=p%10;
        v[i+j]+=p/10;
      }
    string r="";
    for(int x:v) if(!(r.empty()&&x==0)) r+=char('0'+x);
    return r.empty()?"0":r;
}

static string absDiv(string a,string b){
    if(b=="0") throw runtime_error("Division by zero");
    string cur="",q="";
    for(char c:a){
        cur+=c;
        cur=strip(cur);
        int digit=0;
        while(absCmp(cur,b)>=0){
            cur=absSub(cur,b);
            digit++;
        }
        q+=char('0'+digit);
    }
    return strip(q);
}

Integer::Integer():value("0"){}
Integer::Integer(string s):value(strip(s)){}

Integer Integer::operator+(const Integer& o) const{
    string a=value,b=o.value;
    bool na=a[0]=='-', nb=b[0]=='-';
    if(na) a=a.substr(1);
    if(nb) b=b.substr(1);

    if(na==nb){
        string r=absAdd(a,b);
        return Integer((na && r!="0"?"-":"")+r);
    }

    int cmp=absCmp(a,b);
    if(cmp==0) return Integer("0");
    if(cmp>0){
        string r=absSub(a,b);
        return Integer((na?"-":"")+r);
    }
    string r=absSub(b,a);
    return Integer((nb?"-":"")+r);
}

Integer Integer::operator-(const Integer& o) const{
    Integer t=o;
    t.value=(t.value[0]=='-')?t.value.substr(1):"-"+t.value;
    return *this+t;
}

Integer Integer::operator*(const Integer& o) const{
    string a=value,b=o.value;
    bool neg=(a[0]=='-')^(b[0]=='-');
    if(a[0]=='-') a=a.substr(1);
    if(b[0]=='-') b=b.substr(1);
    string r=absMul(a,b);
    return Integer((neg&&r!="0"?"-":"")+r);
}

Integer Integer::operator/(const Integer& o) const{
    string a=value,b=o.value;
    bool neg=(a[0]=='-')^(b[0]=='-');
    if(a[0]=='-') a=a.substr(1);
    if(b[0]=='-') b=b.substr(1);
    string r=absDiv(a,b);
    return Integer((neg&&r!="0"?"-":"")+r);
}

Float::Float():value("0.0"){}
Float::Float(string s):value(s){}

static long double toLD(const string&s){ return stold(s); }

Float Float::operator+(const Float& o) const { return Float(to_string(toLD(value)+toLD(o.value))); }
Float Float::operator-(const Float& o) const { return Float(to_string(toLD(value)-toLD(o.value))); }
Float Float::operator*(const Float& o) const { return Float(to_string(toLD(value)*toLD(o.value))); }
Float Float::operator/(const Float& o) const {
    if(toLD(o.value)==0.0L) throw runtime_error("Division by zero");
    return Float(to_string(toLD(value)/toLD(o.value)));
}

ostream& operator<<(ostream& os,const Integer& o){ os<<o.value; return os; }
istream& operator>>(istream& is,Integer& o){ is>>o.value; o.value=strip(o.value); return is; }

ostream& operator<<(ostream& os,const Float& o){ os<<o.value; return os; }
istream& operator>>(istream& is,Float& o){ is>>o.value; return is; }

}
