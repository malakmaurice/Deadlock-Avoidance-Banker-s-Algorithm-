#include <iostream>
#include<vector>
#include <fstream>
#include <sstream>

using namespace std;
int no_resources,no_processes;

string req,process_name;
int x,process_req_num;
vector<int> request;
vector< vector<int> >Allocation;
vector< vector<int> >Max;
vector< vector<int> >Need;
vector<int> Available;
vector<int>work;
vector<int>safe;
vector<bool>finish;
bool Safty()
{
    int flag=0,t=0;
    for(int i=0; i<no_resources; i++)
        work.push_back(Available[i]);
    for(int i=0; i<no_processes; i++)
        finish.push_back(false);

    for(int i=0; i<no_processes; i++)
    {
        flag=0;
        for(int j=0; j<no_processes; j++)
        {
            if(finish[j]==false  )
            {
                int f=1;

                for(int h=0; h<no_resources; h++)
                {
                    if(Need[j][h] > work[h])
                        f=0;
                }
                if(f==1)
                {
                    flag=1;
                    finish[j]=true;
                    for(int i=0; i<no_resources; i++)
                        work[i]+=Allocation[j][i];
                    safe.push_back(j);
                    /* cout<<"\n\n";
                      for(int k=0; k<no_processes; k++)
                           cout<<finish[k]<<" ";
                       cout<<"\n";*/
                }
            }
        }

    }
    for(int i=0; i<no_processes; i++)
    {
        if(finish[i]==false)
        {
            return false;

        }
    }

    return true;
}
void printNeedMatrix()
{
    cout<<"\nNeed Matrix is...\n";
    for(int i=0; i<no_processes; i++)
    {
        for(int j=0; j<no_resources; j++)
        {
            cout<<Need[i][j]<<" ";
        }
        cout<<"\n";
    }
}
bool is_granted()
{
    bool f1=true;
    for(int i=0; i<no_resources; i++)
    {
        if(request[i]>Need[process_req_num][i])
            f1=false;
    }
    if(f1)
    {
        for(int i=0; i<no_resources; i++)
        {
            if(request[i]>Available[i])
                f1=false;
        }
        if(f1)
        {
            for(int i=0; i<no_resources; i++)
            {
                Available[i]=Available[i]-request[i];
                Allocation[process_req_num][i]+=request[i];
                Need[process_req_num][i]-=request[i];
            }

            f1=Safty();
            if(f1)
            {printNeedMatrix();
                cout<<"\nYes request can be granted with safe state , Safe state ";
                cout<<"<p"<<process_req_num<<"req,";
                for(int i=0; i<no_processes-1; i++)
                {
                    cout<<"p"<<safe[i]<<",";
                }
                cout<<"p"<<safe[no_processes - 1]<< ">";
            }
            else
            {
                printNeedMatrix();
                cout<<"\nNo,request can be not granted, since it will be unsafe state";
            }
        }
        else
        {
            printNeedMatrix();
            cout<<"\nNo,request can be not granted, since resources are not available";
            return false;
        }

    }
    else
    {
        printNeedMatrix();
        cout<<"\nNo,request can be not granted since process has exceeded its maximum claim";
        return false;
    }
}
int main()
{
    //freopen("input.txt","r",stdin);
    int x;
    cout<<"please enter number of processes and resources\n";
    cin>>no_processes>>no_resources;
    cout<<"\nplease enter Allocation matrices\n";
    for(int i=0; i<no_processes; i++)
    {
        vector<int>v;
        for(int j=0; j<no_resources; j++)
        {
            cin>>x;
            v.push_back(x);
        }
        Allocation.push_back(v);
    }
    cout<<"\nplease enter Max matrices\n";
    for(int i=0; i<no_processes; i++)
    {
        vector<int>v;
        for(int j=0; j<no_resources; j++)
        {
            cin>>x;
            v.push_back(x);
        }
        Max.push_back(v);
    }
    for(int i=0; i<no_processes; i++)
    {
        vector<int>v;
        for(int j=0; j<no_resources; j++)
        {
            v.push_back(Max[i][j]-Allocation[i][j]);
        }
        Need.push_back(v);
    }
    cout<<"\nplease enter Available matrices\n";
    for(int i=0; i<no_resources; i++)
    {
        cin>>x;
        Available.push_back(x);
    }
    int y;
    cout<<"\nto check safe state enter 1\nto check if the request of the process is granted or not enter 2";
    cin>>y;
    if(y==1)
    {
        printNeedMatrix();
        bool fg=Safty();
        if(fg)
        {
            cout<<"\nYes , Safe state <";
            for(int i=0; i<no_processes-1; i++)
            {
                cout<<"p"<<safe[i]<<",";
            }
            cout<<"p"<<safe[no_processes - 1]<< ">";
        }
        else
        {
            cout<<"\nNO,Unsafe state";
        }
    }
    else if(y==2)
    {
        cout<<"\n\nenter the request like that p2 (1,2,4,5)\n";
        cin>>process_name>>req;
        //filter the string request
        process_name.erase(0,process_name.length()-1);
        req.erase(0,1);
        req.erase(req.length()-1,1);
        //convert process name string to int
        stringstream s(process_name);
        s>>process_req_num;
        //split req string to int
        stringstream ss(req);
        while (ss.good())
        {
            string substr;
            getline(ss, substr, ',');
            stringstream s2(substr);
            s2>>x;
            request.push_back(x);
        }
        is_granted();
    }
    else
    {
        cout<<"\ni don't understand your request";
    }
    cin>>y;
    return 0;
}
