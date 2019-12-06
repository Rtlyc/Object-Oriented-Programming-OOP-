#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <fstream>
#include <set>
#include <map>
using namespace std;


//task9
/*
void printList(const list<int>& l){
    for(list<int>::iterator iter = l.begin(); iter != l.end(); ++iter){
        cout << *iter << " ";
    }
    cout << endl;
}
 */

void printList(const list<int>& l){
    for(list<int>::const_iterator iter = l.begin(); iter != l.end(); ++iter){
        cout << *iter << " ";
    }
    cout << endl;
}


//    task10
void printList_rangefor(const list<int>& l){
    for(int k: l){ cout << k << " ";}
    cout << endl;
}

//task11
void printList_auto(const list<int>& l){
    for(auto iter = l.begin(); iter != l.end(); ++++iter){ cout << *iter << " ";}
    cout << endl;
}

//task12
list<int>::const_iterator myFind(const list<int>& l, int target){
    for(list<int>::const_iterator iter = l.begin(); iter != l.end(); ++iter){
        if(*iter == target) return iter;
    }
    return l.end();
}

//task13
auto myFind2(const list<int>& l, int target){
    for(auto iter = l.begin(); iter != l.end(); ++iter){
        if(*iter == target) return iter;
    }
    return l.end();
}

//task15
bool isEven(int num){
    return !(num&1);
}


//task16
class IsDividedBy{
    int divisor;
public:
    IsDividedBy(int divisor):divisor(divisor){}
    bool operator()(int num)const{ return num%divisor == 0;}
};


//task19
list<int>::iterator ourFind(list<int>::iterator start, list<int>::iterator end, int target){
    cout<<"in ourfind（）"<<endl;
    for(list<int>::iterator iter = start; iter != end; ++iter){
        if(*iter == target){
            cout << " Found " << endl;
            return iter;
        }
    }
    return end;
}

//task20
template <typename T,typename U>
T ourFind(T start, T end, U target){
    cout<<"in ourfind（）template"<<endl;
    for(T iter = start; iter != end; ++iter){
        if(*iter == target){
            cout << " In the template" << endl;
            return iter;
        }
    }
    return end;
}

int main() {
    vector<int> v{34,13,35,2,1,5,3,52};
//    task1
    cout << "task 1" << endl;
    for(int k: v){ cout << k << " ";}
    cout << endl;

//    task2
    cout << endl << "task 2" << endl;
    list<int> l(v.begin(),v.end());
    for(int k: l){ cout << k << " ";}
    cout << endl;

//    task3
    cout << endl << "task 3" << endl;
    sort(v.begin(),v.end());
    for(int k: v){ cout << k << " ";}
    cout << endl;
    for(int k: l){ cout << k << " ";}
    cout << endl;

//    task4
    cout << endl << "task 4" << endl;
    for(size_t ind = 0; ind != v.size(); ++++ind){ cout << v[ind] << " ";}
    cout << endl;

//    task5
    cout << endl << "task 5" << endl;
    for(list<int>::iterator iter = l.begin(); iter != l.end(); ++++iter){ cout << *iter << " ";}
    cout << endl;

    //    task6
    cout << endl << "task 6" << endl;
    for(vector<int>::iterator iter = v.begin();iter != v.end(); iter+=2){ cout << *iter << " ";}
    cout << endl;

    //    task7
    cout << endl << "task 7" << endl;
    for(list<int>::iterator iter = l.begin(); iter != l.end(); ++++iter){ cout << *iter << " ";}
    cout << endl;

    //    task8
    cout << endl << "task 8" << endl;
    l.sort();
    for(list<int>::iterator iter = l.begin(); iter != l.end(); ++iter){ cout << *iter << " ";}
    cout << endl;

    //    task10
    cout << endl << "task 10" << endl;
    for(int k: l){ cout << k << " ";}
    cout << endl;

//    task12
    cout << endl << "task 12" << endl;
    auto result = myFind(l,3);
    if(result != l.end()){
        cout << *result;
    } else{
        cout << "Not Found";
    }
    cout << endl;

//    task14
    cout << endl << "task 14" << endl;
    result = find(l.begin(),l.end(),2);
    cout << *result;
    cout << endl;

    //    task15
    cout << endl << "task 15" << endl;
    result = find_if(l.begin(),l.end(),isEven);
    cout << *result;
    cout << endl;

    //    task16
    cout << endl << "task 16" << endl;
    result = find_if(l.begin(),l.end(),IsDividedBy(2));
    cout << *result;
    cout << endl;

    //    task17
    cout << endl << "task 17" << endl;
    result = find_if(l.begin(),l.end(),[](int k){return k % 2 == 0;});
    cout << *result;
    cout << endl;

//    task18
    cout << endl << "task 18" << endl;
    int arr[8];
    copy(l.begin(),l.end(),arr);
    for(int ind = 0; ind < 8; ++ind){ cout << arr[ind] << " ";}
    cout << endl;
    int* answer = find(arr,arr+8,34);
    cout << *answer;
    cout << endl;


    //    task19
    cout << endl << "task 19" << endl;
    result = ourFind(l.begin(),l.end(),13);
    cout << *result;
    cout << endl;


    //    task20
    cout << endl << "task 20" << endl;
    auto result2 = ourFind(v.begin(),v.end(),52);
    cout << *result2;
    cout << endl;

//    task21
    cout << endl << "task 21" << endl;
    vector<string> story;
    ifstream ifs("pooh-nopunc.txt");
    string each;
    while(ifs >> each){
        if(ourFind(story.begin(),story.end(),each) == story.end()){
            story.push_back(each);
        }
    }
    ifs.close();
    cout << story.size() << endl;

    //    task22
    cout << endl << "task 22" << endl;
    set<string> myset;
    ifs.open("pooh-nopunc.txt");
    while(ifs >> each){
        myset.insert(each);
    }
    ifs.close();
    cout << myset.size() << endl;


    //    task22
    cout << endl << "task 22" << endl;
    map<string,vector<int>> diction;
    ifs.open("pooh-nopunc.txt");
    int count = 0;
    while(ifs >> each){
        diction[each].push_back(count);
        count++;
    }
    ifs.close();
    for(pair<string,vector<int>> one:diction){
        cout << one.first << ":";
        for(int k:one.second){
            cout << k << " ";
        }
        cout << endl;
    }



}