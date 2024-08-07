#include<iostream>
#include<vector>
using namespace std;

class Banker{
   public:
   int maxNeedOfA;
   int maxNeedOfB;
   int maxNeedOfC;
   
   int avalableA;
   int avalableB;
   int avalableC;

   int processId;
};

bool isNotCompleted(Banker b[], int processes){
    for(int i=0;i<processes;i++){
        if(b[i].maxNeedOfA!=0 || b[i].maxNeedOfB!=0 || b[i].maxNeedOfC!=0){
            return true;
        }
    }
    return false;
}

bool isSafe(Banker bi, int resourceA, int resourceB, int resourceC){
    if(bi.maxNeedOfA==0 && bi.maxNeedOfB==0 && bi.maxNeedOfC==0){
        return false;
    }
    if(bi.maxNeedOfA-bi.avalableA > resourceA){
        return false;
    }
    if(bi.maxNeedOfB-bi.avalableB > resourceB){
        return false;
    }
    if(bi.maxNeedOfC-bi.avalableC > resourceC){
        return false;
    }
    return true;
}

void findRightSequence(vector<Banker>& sequence, Banker b[], int process, int resourceA, int resourceB, int resourceC, bool& found){
    
    while(isNotCompleted(b, process)){
        bool possible=false;
    
        for(int i=0;i<process;i++){
            
            if(isSafe(b[i], resourceA, resourceB, resourceC)){
                resourceA+=b[i].avalableA;
                resourceB+=b[i].avalableB;
                resourceC+=b[i].avalableC;
                
                b[i].maxNeedOfA=0;
                b[i].maxNeedOfB=0;
                b[i].maxNeedOfC=0;

                b[i].avalableA=0;
                b[i].avalableB=0;
                b[i].avalableC=0;

                possible=true;
                sequence.push_back(b[i]);
            }
         }
         if(possible==false){
            cout<<"\nCAN NOT FIND SAFE SEQUENCE....: "<<endl;
            found=false;
            return;
         }
    }
}
int main(){
    int procsses;
    cout<<"\nGive no. of processes: ";
    cin>>procsses;
    Banker b[procsses];
    
    int resourceA;
    int resourceB;
    int resourceC;

    cout<<"\nGive available value of resource A: ";
    cin>>resourceA;
    cout<<"\nGive available value of resource B: ";
    cin>>resourceB;
    cout<<"\nGive available value of resource C: ";
    cin>>resourceC;

    for(int i=0;i<procsses;i++){
        cout<<"\nGive process a unique ID: ";
        cin>>b[i].processId;
        cout<<"Give available source source A for process "<<b[i].processId<<" : ";
        cin>>b[i].avalableA;
        cout<<"Give available source source B for process "<<b[i].processId<<" : ";
        cin>>b[i].avalableB;
        cout<<"Give available source source C for process "<<b[i].processId<<" : ";
        cin>>b[i].avalableC;

        cout<<"Give maximum need of source source A for process "<<b[i].processId<<" : ";
        cin>>b[i].maxNeedOfA;
        cout<<"Give maximum need of source source B for process "<<b[i].processId<<" : ";
        cin>>b[i].maxNeedOfB;
        cout<<"Give maximum need of source source C for process "<<b[i].processId<<" : ";
        cin>>b[i].maxNeedOfC;
    }

    vector<Banker> sequence;
    bool found=true;
    findRightSequence(sequence, b, procsses, resourceA, resourceB, resourceC, found);
    
    if(found==true){
        cout<<"\nSafe sequence of processes is: ";
        for(int i=0;i<procsses;i++){
            cout<<sequence[i].processId;
            if(i<procsses-1){
                cout<<" -> ";
            }
        }
    }
    
    return 0;
}