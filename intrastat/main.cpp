#include <bits/stdc++.h>

using namespace std;

ifstream fin("fisier.in");
ofstream fout("fisier.out");

class data{
    public:
        string deliveryMethod;
        string tariffCode;
        double weight;
        double price;
};

vector <data> goods;
string word;

int main(){
    bool found_deliveryMethod=false;
    bool found_tariffCode=false;
    bool same_data=false;
    bool ok=false;
    double value1,value2;
    int poz;

    data good;

    while(fin>>word){
        if(found_deliveryMethod){
            good.deliveryMethod.assign(word);
            found_deliveryMethod=false;
        }

        if(word=="delivery:")
            found_deliveryMethod=true;

        if(word.size()==8){
            found_tariffCode=true;

            for(int i=0;i<word.size();i++){
                if(word[i]<'0' || word[i]>'9')
                    found_tariffCode=false;
            }

            if(found_tariffCode){
                good.tariffCode.assign(word);
                ok=true;
                poz=0;
            }
        }
        else
            if(ok)
                poz++;

        if(poz==2){
            bool point=false;
            value1=0;
            value2=0;

            for(int i=0;i<word.size();i++){
                if(point && word[i]>='0' && word[i]<='9')
                    value2=value2*10+(word[i]-'0');
                else if(!point && word[i]>='0' && word[i]<='9')
                    value1=value1*10+(word[i]-'0');

                if(word[i]=='.')
                    point=true;
            }

            value1=value1+value2/1000;
            good.weight=value1;
        }

        if(poz==5){
            bool point=false;
            value1=0;
            value2=0;

            for(int i=0;i<word.size();i++){
                if(point && word[i]>='0' && word[i]<='9')
                    value2=value2*10+(word[i]-'0');
                else if(!point && word[i]>='0' && word[i]<='9')
                    value1=value1*10+(word[i]-'0');

                if(word[i]=='.')
                    point=true;
            }

            value1=value1+value2/100;
            good.price=value1;

            same_data=false;

            for(int i=0;i<goods.size();i++)
                if(good.deliveryMethod==goods[i].deliveryMethod && good.tariffCode==goods[i].tariffCode){
                    goods[i].weight+=good.weight;
                    goods[i].price+=good.price;
                    same_data=true;
                }

            if(!same_data)
                goods.push_back(good);

            ok=false;
            poz=0;
        }
    }

    for(int i=0;i<goods.size();i++)
        fout<<fixed<<setprecision(2)<<goods[i].deliveryMethod<<" "<<goods[i].tariffCode<<" "<<goods[i].weight<<" "<<goods[i].price<<"\n";

    return 0;
}
