///code for MULTILEVEL FEEDBACK QUEUE SCHEDULING
///TAKING 3 QUEUES
/// queue name is used to display name of the queue from which system has completed its task
///qsystem-priority based   qinteractive-round robin qbatch-fcfs
#include <bits/stdc++.h>
#include<chrono>
#include<thread>
#define ll long long int
#define max_system_process_priority 5   ///range  0-5
#define max_interactive_process_priority 10 ///range 6-10
#define max_batch_process_priority 15  ///range 11-15
#define t_quantum_system 8
#define t_quantum_interactive 16
#define t_quantum_batch 30
#define t_quantum_roundrobin 7
using namespace std;
 class process
{
public:
string pname;
string qname;
ll cpu_burst_time;
ll priority;
};
class compare
{
public:
    bool operator()(process a,process b)
    {
       if(a.priority>=b.priority) return true;
       return false;
    }
};
compare comp;
queue<process> qinteractive,qbatch;
priority_queue<process,vector<process>,compare> qsystem;

void process_execution()
{
    ll time;
    if(!qsystem.empty())
    {   cout<<"entering inside qsystem loop for \n";
        time=t_quantum_system;
        while(time>0 and qsystem.empty()==false)
        {   process p=qsystem.top();
            cout<<"entering inside while loop of qsystem  for "<<p.pname<<"\n";

            if(p.cpu_burst_time<= time) {
                cout<<"entering inside if block of system\n";
                time-=p.cpu_burst_time;
                p.cpu_burst_time=0;
                cout<<"process "<<p.pname<<" completed from "<<p.qname<<"\n";
                qsystem.pop();
                //return true;
            }
            else{
                cout<<"entering inside else block of system\n";
                p.cpu_burst_time-=time;
                time=0;
                qsystem.pop();
                p.qname="qinteractive";
                qinteractive.push(p);
             //   return false;
            }
        }
        //return ;
    }
    if(  qsystem.empty() and qinteractive.empty()==false)
    {   cout<<"entering inside qinteractive loop\n";
        time=t_quantum_interactive;
        int time1=t_quantum_roundrobin;
        while(time>0 and qinteractive.empty()==false)
        {   process p=qinteractive.front();
            cout<<"entering inside while loop of qinteractive  for "<<p.pname<<"\n";

                if(p.cpu_burst_time<=time1 and p.cpu_burst_time<=time)
                {   cout<<"entering inside if block of interactive\n";
                    time-=p.cpu_burst_time;
                    p.cpu_burst_time=0;
                    cout<<"process "<<p.pname<<" completed from "<<p.qname<<"\n";
                    time1=t_quantum_roundrobin;
                    qinteractive.pop();
                    //return true;
                }
                else if (p.cpu_burst_time>time1 and p.cpu_burst_time<=time)   ///    #1
                    {
                    cout<<"entering inside else-if block of interactive #1\n";
                    time-=time1;
                    p.cpu_burst_time-=time1;
                    p.qname="qbatch";
                    qbatch.push(p);
                    qinteractive.pop();
                    time1=t_quantum_roundrobin;
                    //return true;

                }
                else if(p.cpu_burst_time>time1 and p.cpu_burst_time>time)   /// #2
                {   cout<<"entering inside else-if block of interactive #2\n";
                    if(time1>time)
                    {   ///not popped because process didnt get whole t_quantum_roundrobin
                        cout<<"entering inside if block of interactive # 2\n";
                        p.cpu_burst_time-=time;
                        time=0;
                        time1=t_quantum_roundrobin;

                    }
                    else
                    {   cout<<"entering inside else block of interactive # 2\n";
                        p.cpu_burst_time-=time1;
                        time-=time1;
                        time1=t_quantum_roundrobin;
                        qinteractive.pop();
                        p.qname="qbatch";
                        qbatch.push(p);
                    }
                }
                else{
                    cout<<"entering inside else block of interactive \n";
                    p.cpu_burst_time-=time;
                    time=0;
                    time1=t_quantum_roundrobin;
                    ///not popped because process didnt get whole t_quantum_roundrobin
                }

        }
    //cout<<"exiting from interactive loop\n";
     return;
    }
    if(qsystem.empty() and qinteractive.empty() and qbatch.empty()==false)
    {   cout<<"entering inside qbatch loop\n";
        time=t_quantum_batch;
        while(time>0 and qbatch.empty()==false)
        {  process p=qbatch.front();
            cout<<"entering inside while loop of qbatch  for "<<p.pname<<"\n";

            if(p.cpu_burst_time<= time) {
                cout<<"entering inside if block of batch\n";
                time-=p.cpu_burst_time;
                p.cpu_burst_time=0;
                cout<<"process "<<p.pname<<" completed from "<<p.qname<<"\n";
                qbatch.pop();
            }
            else{
                cout<<"enter inside else block of batch\n";
                p.cpu_burst_time-=time;
                time=0;
                qbatch.pop();
                p.qname="qsystem";
                qsystem.push(p);
            }
        }
     return ;
    }
}
bool assign_queue( process p )
{    //cout<<"priority while inserting in queue is "<<p.priority<<endl;
    if(p.priority<=max_system_process_priority){
       //cout<<"insertd in system block\n";
        p.qname="qsystem";
        qsystem.push(p);
                return true;
    }

    if(p.priority<=max_interactive_process_priority){
       //cout<<"insertd in interactive block\n";
        p.qname="qinteractive";
        qinteractive.push(p);
                return true;
    }

    if(p.priority<=max_batch_process_priority){
        //cout<<"insertd in batch block\n";
        p.qname="qbatch";
        qbatch.push(p);
        return true;
    }
    return false;
}
bool insert_process()
{   cout<<"enter the no of process you want to enter\n";
    int np;
    cin>>np;
    cout<<"ENTER PROCESS NAME,BURST TIME,PRIORITY\n";
    int response,i=1; bool check;
    while(i++<=np)
    {
      process p;
      cin>>p.pname>>p.cpu_burst_time>>p.priority;
      //tring name;
      //ll prio,btime;
      //cin>>name>>btime>>prio;
      check=assign_queue(p);
      if(check== false) return check;
      //cout<<"PRESS ZERO TO STOP ENTERING PROCESS\n";
      //cin>>response;
      //if(response==0) break;
    }
    return true;
}

int main()
{
    int user_response;
    //ios::sync_with_stdio(0);
    //cin.tie(0);
    //cout.tie(0); cout.flush();
    //cout.flush();
    cout<<"SYSTEM WILL PROMPT TO ENTER A VALUE AFTER A FIXED TIME INTERVAL\n";
    //cout.flush();
    cout<<"WHENEVER SYSTEM PROMPTS TO ENTER A VALUE\n";
    //cout.flush();
    cout<<"PRESS 1 TO ENTER THE NEW PROCESSES\n";
    //cout.flush();
    cout<<"PRESS 2 IF YOU DONT WANT TO ENTER ANY PROCESS AND SYSTEM WILL CONTINUE ITS EXECUTION ON THE PROCESS WHICH WERE GIVEN EARLIER\n";
    //cout.flush();
    cout<<"IF YOU ENTER ANY OTHER VALUE SYSTEM WILL NOT ACCEPT IT AND IT WILL PROMPT YOU TO ENTER AGAIN\n";
    //cout.flush();
    cout<<"BUT IF ALL THE QUEUES ARE EMPTY THEN SYSTEM WII ALLOW YOU TO ENTER ANOTHER VALUE 3 WHICH WILL TERMINATE THE PROGRAM\n";
    //cout.flush();

    //cout.flush();
    cout<<"IF YOU DO NOT PRESS 3 SYSTEM WILL NOT TERMINATE AND GO IN WAIT STATE IT WILL AGAIN START ITS EXECUTION WHEN YOU ENTER A NEW PROCESS "<<endl;
    //cout.flush();
    cout<<"INITIALLY WHEN NO PROCESS IS ENTERED THEN YOU MUST PRESS 1 AS NEW VALUE TO BEGIN THE EXECUTION OF PROGRAM ANY OTHER VALUE WILL BE IGNORED BY THE PROGRAM\n";
    cout<<"ENTER A NEW VALUE\n";
    cout.flush();
    //char ch;cin>>ch;
    while(true)
    {
    cin>>user_response;
    if(user_response==1) break;
    if(user_response==2) continue;
    if(user_response==3) exit(0);
    cout.flush();
    cout<<"NOT A VALID CHOICE,ENTER YOUR CHOICE AGAIN\n";
    cout.flush();
    }
    bool check=false;           ///check is used to confirm weather process insertion takes place correctly or not
    //cout<<"going in inser process\n";
    check=insert_process();
    if(check==false ) cout<<"ERROR IN PROCESS INSERTION\n";

    while(true)
    {   for(int i=1;i<=5 and (qsystem.empty()==false or qinteractive.empty()==false or qbatch.empty()==false) ;i++)  ///USED TO CREATE A TIME SLICE LIKE EFFECT
        process_execution();

        cout<<"DO YOU WANT TO ENTER NEW PROCESSES\n";
        cin>>user_response;
        if(user_response==1) insert_process();
        if(user_response==2);
        if(user_response==3 and qsystem.empty()==true and qinteractive.empty()==true and qbatch.empty()==true) exit(0);
        while(qsystem.empty()==true and qinteractive.empty()==true and qbatch.empty()==true)
        {
            cout<<"DO YOU WANT TO ENTER NEW PROCESSES YOU CAN ALSO PRESS 3 TO QUIT THE PROGRAM\n";
            cin>>user_response;
            if(user_response==1)
            {
                insert_process();
                break;
            }
            else if(user_response==3) exit(0);
            else {
                cout<<"GOING IN WAIT STATE\n";
                this_thread::sleep_for(3s);
                continue;
            }
        }


    }
/*while(!qbatch.empty())
    {
        process p=qbatch.front();
        cout<<p.pname<<" ";
        qbatch.pop();
    }*/
 cout<<endl;
/* while(!qinteractive.empty())
 {
     process p=qinteractive.front();
     cout<<p.pname<<" ";
     qinteractive.pop();
 }*/
    return 0;
}
/*
ENTER A VALUE
NOT A VALID CHOICE,ENTER YOUR CHOICE AGAIN
10
p1 60 5
p2 7 3
p3 80 2
p4 100 8
p5 120 9
p6 90 6
p7 13 8
p8 28 12
p9 200 14
p10 150 15*/
