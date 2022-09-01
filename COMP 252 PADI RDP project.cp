#include <iostream>
#include <list>
#include <string>

using namespace std;

class ListNode{  //linkedList for pressure group letter
public:
    ListNode *next;
    int time;
    char pressureGroup;
    ListNode(int timeOfDive, char PressureGroupletter){
        time= timeOfDive;
        pressureGroup = PressureGroupletter;
        next = NULL;
    }

};

class RNTNode{  //class for RNT
public:
    RNTNode *next;
    int time;
    int newDepth;
    RNTNode( int RNT, int depth){
        time=RNT;
        newDepth=depth;
        next=NULL;
    }
};

class RDPTable1{    //RDP table
public:
    RDPTable1(){
        initializeDepthChart();
        initializeSurfaceInterval();
        initializeRNT();
    }

    char pressureGroup (int depth, int time);
    char newDiveGroup (char firstGroup, int timeOutofWater);
    int RNT (char group, int newDepth);  //residual nitrogren time

private:
    
    
    int findPressureGroupIndex(char letter);
    void initializeSurfaceInterval();
    void initializeDepthChart();
    int depthToIndex(int depth);
    int depths[12]={35,40,50,60,70,80,90,100,110,120,130,140};
    void initializeRNT();
    RNTNode * initializeRNTLinkedList(int timearr[]);
    RNTNode * RNTime[26];
    ListNode *initializeSurfaceIntervalLinkedList(int surfacearr[], int size);
    ListNode* intializedDepthLinkedList(int arr[]);
    int FindTableIndex(int depth);
    
    
    ListNode* depthChart[12];
    void intializedPressureGroup();
    int pressureGroupChart[26]={'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
    ListNode *surfaceInterval[26];
 
    
};

int RDPTable1::findPressureGroupIndex(char letter){
    for (int i=0; i<26; i++) {
        if (pressureGroupChart[i]==letter) {
            return i;
        }
    }
    return -1;
}
void RDPTable1::initializeSurfaceInterval(){
    int surfaceInterval_A[1]={180};
    surfaceInterval[0]=initializeSurfaceIntervalLinkedList(surfaceInterval_A, 1);
    int surfaceInterval_B[2]={228,47};
    surfaceInterval[1]=initializeSurfaceIntervalLinkedList(surfaceInterval_B, 2);
    int surfaceInterval_C[3]={250,69,21};
    surfaceInterval[2]=initializeSurfaceIntervalLinkedList(surfaceInterval_C, 3);
    int surfaceInterval_D[4]={259,78, 30, 8};
    surfaceInterval[3]=initializeSurfaceIntervalLinkedList(surfaceInterval_D, 4);
    int surfaceInterval_E[5]={268, 87, 38, 16, 7};
    surfaceInterval[4]=initializeSurfaceIntervalLinkedList(surfaceInterval_E, 5);
    int surfaceInterval_F[6]={275, 94, 46, 24, 15, 7};
    surfaceInterval[5]=initializeSurfaceIntervalLinkedList(surfaceInterval_F, 6);
    int surfaceInterval_G[7]={282,101, 53, 32, 22, 13, 6};
    surfaceInterval[6]=initializeSurfaceIntervalLinkedList(surfaceInterval_G, 7);
    int surfaceInterval_H[8]={288, 107, 59, 37, 28, 20, 12, 5};
    surfaceInterval[7]=initializeSurfaceIntervalLinkedList(surfaceInterval_H, 8);
    int surfaceInterval_I[9]={294, 113, 65, 43, 34, 26, 18, 11, 5};
    surfaceInterval[8]=initializeSurfaceIntervalLinkedList(surfaceInterval_I, 9);
    int surfaceInterval_J[10]={300, 119, 71, 49, 40, 31, 24, 17, 11, 5};
    surfaceInterval[9]=initializeSurfaceIntervalLinkedList(surfaceInterval_J, 10);
    int surfaceInterval_K[11]={305, 124, 76, 54, 45, 37, 29, 22, 16, 10, 4};
    surfaceInterval[10]=initializeSurfaceIntervalLinkedList(surfaceInterval_K, 11);
    int surfaceInterval_L[12]={310, 129, 81, 59, 50, 42, 34, 27, 21, 15, 9, 4};
    surfaceInterval[11]=initializeSurfaceIntervalLinkedList(surfaceInterval_L, 12);
    int surfaceInterval_M[13]={315, 134, 85, 64, 55, 46, 39, 32, 25, 19, 14, 9, 4};
    surfaceInterval[12]=initializeSurfaceIntervalLinkedList(surfaceInterval_M, 13);
    int surfaceInterval_N[14]={319, 138, 90, 68, 59, 51, 43, 36, 30, 24, 18, 13, 8, 3};
    surfaceInterval[13]=initializeSurfaceIntervalLinkedList(surfaceInterval_N, 14);
    int surfaceInterval_O[15]={324, 143, 94, 72, 63, 55, 47, 41, 34, 28, 23, 17, 12, 8, 3};
    surfaceInterval[14]=initializeSurfaceIntervalLinkedList(surfaceInterval_O, 15);
    int surfaceInterval_P[16]={328, 147, 98, 76, 67, 59, 51, 45, 38, 32, 27, 21, 16, 12, 7, 3};
    surfaceInterval[15]=initializeSurfaceIntervalLinkedList(surfaceInterval_P, 16);
    int surfaceInterval_Q[17]={331, 150, 102, 80, 71, 63, 55, 48, 42, 36, 30, 25, 20, 16, 11, 7, 3};
    surfaceInterval[16]=initializeSurfaceIntervalLinkedList(surfaceInterval_Q, 17);
    int surfaceInterval_R[18]={335, 154, 106, 84, 75, 67, 59, 52, 46, 40, 34, 29, 24, 19, 15, 11, 7, 3};
    surfaceInterval[17]=initializeSurfaceIntervalLinkedList(surfaceInterval_R, 18);
    int surfaceInterval_S[19]={339, 158, 109, 87, 78, 70, 60, 56, 49, 43, 38, 32, 27, 23, 16, 14, 10, 6, 3};
    surfaceInterval[18]=initializeSurfaceIntervalLinkedList(surfaceInterval_S, 19);
    int surfaceInterval_T[20]={342, 161, 113, 91, 82, 73, 66, 59, 53, 47, 41, 36, 31, 26, 22, 17, 13, 10, 6, 2};
    surfaceInterval[19]=initializeSurfaceIntervalLinkedList(surfaceInterval_T, 20);
    int surfaceInterval_U[21]={345, 164, 116, 94, 87, 77, 69, 62, 56, 50, 44, 39, 34, 29, 25, 21, 17, 13, 9, 6, 2};
    surfaceInterval[20]=initializeSurfaceIntervalLinkedList(surfaceInterval_U, 21);
    int surfaceInterval_V[22]={348, 167, 119, 97, 88, 80, 72, 65, 59, 53, 47, 42, 37, 33, 28, 24, 20, 16, 12, 9, 5, 2};
    surfaceInterval[21]=initializeSurfaceIntervalLinkedList(surfaceInterval_V, 22);
    int surfaceInterval_W[23]={351, 170, 122, 100, 91, 83, 75, 68, 62, 56, 50, 45, 40, 36, 31, 27, 23, 19, 15, 12, 8, 5, 2};
    surfaceInterval[22]=initializeSurfaceIntervalLinkedList(surfaceInterval_W, 23);
    int surfaceInterval_X[24]={354, 173, 125, 103, 94, 86, 78, 71, 65, 59, 53, 48, 43, 39, 34, 30, 26, 22, 18, 15, 11, 8, 5, 2};
    surfaceInterval[23]=initializeSurfaceIntervalLinkedList(surfaceInterval_X, 24);
    int surfaceInterval_Y[25]={357, 176, 128, 106, 97, 89, 81, 74, 68, 62, 56, 51, 46, 41, 37, 33, 29, 25, 21, 18, 14, 11, 8, 5, 2};
    surfaceInterval[24]=initializeSurfaceIntervalLinkedList(surfaceInterval_Y, 25);
    int surfaceInterval_Z[26]={360, 179, 131, 109, 100, 91, 84, 77, 71, 65, 59, 54, 49, 44, 40, 35, 31, 28, 24, 20, 17, 14, 11, 8, 5, 2};
    surfaceInterval[25]=initializeSurfaceIntervalLinkedList(surfaceInterval_Z, 26);
}
ListNode * RDPTable1::initializeSurfaceIntervalLinkedList(int surfacearr[], int size){
    ListNode *head =NULL;
    ListNode *previous=NULL;
    for (int i=0; i<size; i++) {
        int surfaceIntervalTime=surfacearr[i];
        char pressureGroup=pressureGroupChart[i];
        ListNode * current= new ListNode(surfaceIntervalTime, pressureGroup);
        if (previous==NULL) {
            head=current;
        }
        else{
            previous->next=current;
        }
        
        previous=current;
        
    };
    return head;
}


void RDPTable1::initializeDepthChart(){
    int depth_35[26]={10,19,25,29,32,36,40,44,48,53,57,62,67,73,79,85,92,100,108,117,127,139,152,168,188,205};
    depthChart[0]=intializedDepthLinkedList(depth_35);
    int depth_40[26]={9,16,22,25,27,31,34,37,40,44,48,51,55,60,64,69,74,79,85,91, 97, 104, 111, 120, 129, 140 };
    depthChart[1]=intializedDepthLinkedList(depth_40);
    int depth_50[24]={7,13,17,19,21,24,26,28,31,33,36,39,41,44,47,50,53,57,60,63,67,71,75,80};
    depthChart[2]=intializedDepthLinkedList(depth_50);
    int depth_60[23]={6, 11, 14, 16, 17, 19, 21, 23, 25, 27, 29, 31, 33, 35, 37, 39, 42, 44, 47, 49, 52, 54, 55};
    depthChart[3]=intializedDepthLinkedList(depth_60);
    int depth_70[20]={ 5, 9 ,12, 13, 15, 16, 18, 19, 21, 22, 24, 26, 27, 29, 31, 33, 35, 36, 38, 40};
    depthChart[4]=intializedDepthLinkedList(depth_70);
    int depth_80[18]={4, 8 ,10, 11, 13, 14, 15, 17, 18, 19, 21, 22, 23, 25, 26, 28, 29, 30};
    depthChart[5]=intializedDepthLinkedList(depth_80);
    int depth_90[17]={4 ,7 ,9 ,10, 11, 12, 13, 15, 16, 17, 18, 19, 21, 22, 23, 24, 25};
    depthChart[6]=intializedDepthLinkedList(depth_90);
    int depth_100[16]={3, 6, 8, 9, 10, 11, 12, 13, 14, 15 ,16, 17, 18 ,19 ,20 };
    depthChart[7]=intializedDepthLinkedList(depth_100);
    int depth_110[15]={3 ,6 ,7 ,8 ,9 ,10 ,11, 12, 13, 0, 14, 15, 16};
    depthChart[8]=intializedDepthLinkedList(depth_110);
    int depth_120[11]={3, 5, 6, 7, 8, 9 ,10 ,11, 0 ,12 ,13};
    depthChart[9]=intializedDepthLinkedList(depth_120);
    int depth_130[8]={3, 5, 6, 7, 0, 8, 9, 10 };
    depthChart[10]=intializedDepthLinkedList(depth_130);
    int depth_140[6]={0, 4, 5, 6, 7, 8};
    depthChart[11]=intializedDepthLinkedList(depth_140);

}
ListNode* RDPTable1::intializedDepthLinkedList(int deptharr[]){
        ListNode *previous = NULL;
        ListNode *head = NULL;
        for (int i=0; i <26; i++) {
            int time=deptharr[i];
            if (time==0) {
                continue;
            }
            char pressureGroup=pressureGroupChart[i];
            ListNode *current = new ListNode(time,pressureGroup);
            if (previous==NULL) {
                head=current;
            }
            else{
                previous->next=current;
            }
            
            previous=current;
    };
    
    return head;//return residual nitrogren time
}

void RDPTable1:: initializeRNT(){//build the RNT list
    int RNT_A[11]={10,9,7,6,5,4,4,3,3,3,3};
    RNTime[0]=initializeRNTLinkedList(RNT_A);
    int RNT_B[11]={19,16,13,11,9,8,7,6,5,5};
    RNTime[1]=initializeRNTLinkedList(RNT_B);
    int RNT_C[11]={25,22,17,14,12,10,9,8,7,6,6};
    RNTime[2]=initializeRNTLinkedList(RNT_C);
    int RNT_D[11]={29,25,19,16,13,11,10,9,8,7,7};
    RNTime[3]=initializeRNTLinkedList(RNT_D);
    int RNT_E[11]={32,27,21,17,15,13,11,10,9,8,8};
    RNTime[4]=initializeRNTLinkedList(RNT_E);
    int RNT_F[11]={36,31,24,19,16,14,12,11,10,9,8};
    RNTime[5]=initializeRNTLinkedList(RNT_F);
    int RNT_G[11]={40,34,26,21,18,15,13,12,11,10,9 };
    RNTime[6]=initializeRNTLinkedList(RNT_G);
    int RNT_H[11]={44,37,28,23,19,17,15,13,12,11,10};
    RNTime[7]=initializeRNTLinkedList(RNT_H);
    int RNT_I[10]={48,40,31,25,21,18,16,14,13,12};
    RNTime[8]=initializeRNTLinkedList(RNT_I);
    int RNT_J[10]={52,44,33,27,22,19,17,15,14,12};
    RNTime[9]=initializeRNTLinkedList(RNT_J);
    int RNT_K[10]={19,16,13,11,9,8,7,6,5,5};
    RNTime[19]=initializeRNTLinkedList(RNT_K);
    int RNT_L[9]={62,51,38,31,26,22,19,17,15};
    RNTime[11]=initializeRNTLinkedList(RNT_L);
    int RNT_M[9]={67,55,41,33,27,23,21,18,16};
    RNTime[12]=initializeRNTLinkedList(RNT_M);
    int RNT_N[8]={73,60,44,35,29,25,22,19};
    RNTime[13]=initializeRNTLinkedList(RNT_N);
    int RNT_O[8]={79,64,47,37,31,26,23,20};
    RNTime[14]=initializeRNTLinkedList(RNT_O);
    int RNT_P[7]={85,69,50,39,33,28,24};
    RNTime[15]=initializeRNTLinkedList(RNT_P);
    int RNT_Q[7]={92,74,53,42,34,28,24};
    RNTime[16]=initializeRNTLinkedList(RNT_Q);
    int RNT_R[6]={100,79,57,44,36,30};
    RNTime[17]=initializeRNTLinkedList(RNT_R);
    int RNT_S[9]={108,85,60,37,38};
    RNTime[18]=initializeRNTLinkedList(RNT_S);
    int RNT_T[8]={117,91,63,49,40};
    RNTime[19]=initializeRNTLinkedList(RNT_T);
    int RNT_U[8]={127,97,67,52};
    RNTime[20]=initializeRNTLinkedList(RNT_U);
    int RNT_V[7]={139,104,71,54};
    RNTime[21]=initializeRNTLinkedList(RNT_V);
    int RNT_W[7]={152,111,75,55};
    RNTime[22]=initializeRNTLinkedList(RNT_W);
    int RNT_X[6]={168,120,80};
    RNTime[23]=initializeRNTLinkedList(RNT_X);
    int RNT_Y[2]={188,129};
    RNTime[24]=initializeRNTLinkedList(RNT_Y);
    int RNT_Z[2]={205,140};
    RNTime[25]=initializeRNTLinkedList(RNT_Z);
}

RNTNode * RDPTable1::initializeRNTLinkedList(int timearr[]){
    RNTNode * head=NULL;
    RNTNode * previous = NULL;
    
    for (int i=0; i<26; i++) {
        int time=timearr[i];
        int newDepth= depths[i];
        RNTNode* current = new RNTNode(time, newDepth);
        if (i==0) {
            head= current;
        }
        else{
            previous->next=current;

        }
        
        previous=current;
}
    
    return head;
    
}
int RDPTable1::FindTableIndex(int depth){
    for (int i=0; i < 12; i++) {
        if (depths[i]==depth||depths[i]>depth ) {
            return i;
        }
    }
    
    return -1;
}
    
char RDPTable1::pressureGroup(int depth, int time){

    int index=FindTableIndex(depth);


    ListNode *head= depthChart[index];

    
    ListNode * current = head;
    while (current != NULL&& current->time<time) {
        current = current ->next;
    }
    return current->pressureGroup;
  
}

char RDPTable1::newDiveGroup(char firstGroup, int TimeOutOfWater){
    //Find NEw Pressure group for table 3
    char previouse = NULL;
    int index=findPressureGroupIndex(firstGroup);   //spelled previous wrong
    ListNode * current =surfaceInterval[index];
    while (current != NULL&&TimeOutOfWater <=current ->time) {
        previouse= current -> pressureGroup;
        current=current ->next;
        
    }
    return previouse;
    
    
}
    

int RDPTable1::RNT(char group, int newDepth){
    int RNTindex = findPressureGroupIndex(group);
    RNTNode* residualNitrogenTime=RNTime[RNTindex];
   
    
    while (residualNitrogenTime != NULL&&residualNitrogenTime-> newDepth < newDepth) {
        residualNitrogenTime=residualNitrogenTime->next;
        }                                                  //traverse

    int time=residualNitrogenTime->time;
    return time;
    
}


int main(int argc, const char * argv[]) { //main function
    
    
    int numOfDives;
    
    
    int meters;
    int bottomTime;
    int surfaceInterval;

    cout<<"How many times are you diving >> " ;
    cin>>numOfDives;
    int diveDepths[numOfDives];
    int diveTime[numOfDives];
    int diveSurfaceInterval[numOfDives-1];
    for (int i=0; i<numOfDives; i++) {
        int currentDive=i+1;
        if (i>0) {
            cout<<"What is your surface interval(in min) before dive #"<<currentDive<<"? >> ";//when i =0 current dive = 1,
            cin>> surfaceInterval;
            diveSurfaceInterval[i>1]=surfaceInterval;
        }
        cout<<"What is the depth (in meters) of your dive #"<< currentDive<<"? >> ";//dive numbers
        cin>> meters;
        if (meters>140) {
            cout<<"That depth is not in the RDP table!"<<endl;
            cout<< "Please restart program";
            return -1;
        }
        diveDepths[i]=meters;
        cout<<"What is the bottom time of your dive #"<<currentDive<<"? >> ";
        cin >> bottomTime;
        diveTime[i]=bottomTime;
        
    }
    
    RDPTable1 table;
    
    int newDiveTime=diveTime[0];
    
    for (int i=0; i<numOfDives;i++){
        char pressureGroup= table.pressureGroup(diveDepths[i], newDiveTime); //calculating table 1 for dive #1 because index 0
        cout<<"Your pessure group for dive #"<< i+1<< " : " <<pressureGroup << endl;
        if (numOfDives>1 && numOfDives-i!=1) {
            char newDiveGroup= table.newDiveGroup(pressureGroup, diveSurfaceInterval[i]); // calculating table 2 for dive #2 aka first surfaceInterval
            cout<<"Your new pressure group at end of surface interval for dive #"<<i+1<<" : " <<newDiveGroup << endl;
            int RNT=table.RNT( newDiveGroup , diveDepths[i+1]);
            int TBT=RNT+diveTime[i+1];
            cout<<"Your total bottom time for dive #"<< i + 2 << " : " << TBT << endl;
            
            newDiveTime=TBT;
        }
        
    }
    
    
    return 0;
}
