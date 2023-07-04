#include <bits/stdc++.h>
#include <iostream>
#include <conio.h>
#include <vector>
#include <queue>
#include <algorithm>
#include <numeric>
#include <chrono>
using namespace std;
using namespace chrono;
queue<int> waitingQueue;      // Queue for task that has completed execution .
queue<int> computedTaskQueue; // Queue for the task that has completed execution.
// vector<int>CF;
vector<vector<int>> CFStatusTable; // {RAM,PE  number of processing element , BW , PS processing Speed}
vector<pair<int, vector<int>>> result;

/**************   Adding edges to graph    *****************/
void addadj(vector<int> adj[], int u, int v)
{
    adj[u].push_back(v);
}

/*******************    Inserting into vector of pair for dependencies  *********************/
//
void insertintopairofvector(vector<int> adj[], int v, vector<pair<int, vector<int>>> &vv)
{
    for (int i = 0; i < v; i++)
        vv.push_back({i, adj[i]});
}

/*********************    Graph printing     ***********************/
void printgraphVP(vector<pair<int, vector<int>>> vv)
{
    for (auto p : vv)
    {
        cout << "    " << p.first << " -> ";
        for (auto pp : p.second)
            cout << pp << " ";
        cout << endl;
    }
}

/************************  Merge Function according to Comparative Attribute Algorithm  ****************************/

void merge(vector<pair<int, vector<int>>> &UT, int l, int mid, int r, vector<int> noofrequests, vector<int> workload, int MNR, int WM)
{
    vector<pair<int, vector<int>>> UT1, UT2;
    for (int i = l; i <= mid; i++)
        UT1.push_back(UT[i]);

    for (int i = mid + 1; i <= r; i++)
        UT2.push_back(UT[i]);

    int i = l, l1 = 0, l2 = 0, r1 = UT1.size(), r2 = UT2.size();

    while (l1 < r1 && l2 < r2)
    {
        pair<int, vector<int>> Tu = UT1[l1], Tv = UT2[l2], P;

        if (find(Tu.second.begin(), Tu.second.end(), Tv.first) != Tu.second.end())
        {
            P = Tu;
            l1++;
        }
        else if (find(Tv.second.begin(), Tv.second.end(), Tu.first) != Tv.second.end())
        {
            P = Tv;
            l2++;
        }
        else
        {
            int Du = accumulate(Tu.second.begin(), Tu.second.end(), 0);
            int Dv = accumulate(Tv.second.begin(), Tv.second.end(), 0);
            if (Du > Dv)
            {
                P = Tu;
                l1++;
            }
            else if (Du < Dv)
            {
                P = Tv;
                l2++;
            }
            else
            {
                int NRRu = noofrequests[Tu.first] / MNR;
                int NRRv = noofrequests[Tv.first] / MNR;
                if (NRRu > NRRv)
                {
                    P = Tu;
                    l1++;
                }
                else if (NRRu < NRRv)
                {
                    P = Tv;
                    l2++;
                }
                else
                {
                    int WLRu = workload[Tu.first] / WM;
                    int WLRv = workload[Tv.first] / WM;
                    if (WLRu > WLRv)
                    {
                        P = Tv;
                        l2++;
                    }
                    else
                    {
                        P = Tu;
                        l1++;
                    }
                }
            }
        }

        UT[i] = P;
        i++;
    }

    while (l1 < r1)
    {
        UT[i] = UT1[l1++];
        i++;
    }
    while (l2 < r2)
    {
        UT[i] = UT2[l2++];
        i++;
    }
}

/******************   Merge Sort  ******************/

void mergesort(vector<pair<int, vector<int>>> &UT, int l, int r, vector<int> noofrequests, vector<int> workload, int MNR, int WM)
{
    if (l >= r)
        return;

    int mid = l + (r - l) / 2;
    mergesort(UT, l, mid, noofrequests, workload, MNR, WM);
    mergesort(UT, mid + 1, r, noofrequests, workload, MNR, WM);

    merge(UT, l, mid, r, noofrequests, workload, MNR, WM);
}

/*******  Citizen for are able to execute the task *******/
vector<int> taskexexuteinCF;
vector<pair<int, vector<int>>> UF;
vector<int> RR1;
vector<int> PR1;
vector<int> BR1;
vector<int> ETR1;
/****************   Citizen Fog Task Management Algorithm   *********/

void citizenfogmanager(vector<pair<int, vector<int>>> &UT, vector<int> RR, vector<int> PR, vector<int> BR, vector<int> ETR)
{
    // while (UT.size() != 0)
    for (int ss = UT.size() - 1; ss >= 0; ss--)
    {
        int task = UT[ss].first;
        if (RR[ss] < 200 || PR[ss] < 50 && BR[ss] < 50)
        {
            taskexexuteinCF.push_back(task);
        }
        else
        {
            UF.push_back(UT[ss]);
            RR1.push_back(RR[ss]);
            PR1.push_back(PR[ss]);
            BR1.push_back(BR[ss]);
            ETR1.push_back(ETR[ss]);
        }
    }
}

/************************  Merge Function according to Linear Attributes Summarized Algorithm(LASA)  ****************************/
void merge1(vector<pair<int, vector<int>>> &UF, int l, int mid, int r, vector<int> ETR1, vector<int> RR1, vector<int> PR1, vector<int> BR1, int METR, int MRR, int MPR, int MBR)
{
    vector<pair<int, vector<int>>> UF1, UF2;
    for (int i = l; i <= mid; i++)
        UF1.push_back(UF[i]);
    for (int i = mid + 1; i <= r; i++)
        UF2.push_back(UF[i]);

    int i = l, l1 = 0, l2 = 0, r1 = UF1.size(), r2 = UF2.size();

    while (l1 < r1 && l2 < r2)
    {
        pair<int, vector<int>> FogA = UF1[l1], FogB = UF2[l2], F;
        int a = FogA.first, b = FogB.first;
        int ETRa = ETR1[a] / METR, ETRb = ETR1[b] / METR;
        int RRa = RR1[a] / MRR, RRb = RR1[b] / MRR;
        int PRa = PR1[a] / MPR, PRb = PR1[b] / MPR;
        int BRa = BR1[a] / MBR, BRb = BR1[b] / MBR;
        double PointA = 1.0 / ETRa + PRa + RRa + BRa; // Use double to avoid integer division truncation
        double PointB = 1.0 / ETRb + PRb + RRb + BRb;

        if (PointA > PointB)
        {
            F = FogA;
            l1++;
        }
        else if (PointB > PointA)
        {
            F = FogB;
            l2++;
        }
        else
        {
            if (ETRa >= ETRb)
            {
                F = FogA;
                l1++;
            }
            else
            {
                F = FogB;
                l2++;
            }
        }

        UF[i] = F;
        i++;
    }

    while (l1 < r1)
    {
        UF[i] = UF1[l1++];
        i++;
    }
    while (l2 < r2)
    {
        UF[i] = UF2[l2++];
        i++;
    }
}

/******************   Merge1 Sort  ******************/
void mergesort1(vector<pair<int, vector<int>>> &UF, int l, int r, vector<int> ETR1, vector<int> RR1, vector<int> PR1, vector<int> BR1, int METR, int MRR, int MPR, int MBR)
{
    if (l >= r)
        return;
    int mid = l + (r - l) / 2;
    mergesort1(UF, l, mid, ETR1, RR1, PR1, BR1, METR, MRR, MPR, MBR);
    mergesort1(UF, mid + 1, r, ETR1, RR1, PR1, BR1, METR, MRR, MPR, MBR);

    merge1(UF, l, mid, r, ETR1, RR1, PR1, BR1, METR, MRR, MPR, MBR);
}

/**************** Algorithm 2     *****************/
void MasterFogManager(queue<int> &ITQ, vector<int> ComputableCF)
{
    int i = 0;
    while (!ITQ.empty())
    {
        int task = ITQ.front();
        ITQ.pop();
        if (ComputableCF[i] == 1)
        {
            int ack = task;
            computedTaskQueue.push(ack);
            CFStatusTable[i][4] = 1;
        }
        //  else if()  //possible to send to cloud than send to cloud
        else

        {
            waitingQueue.push(task);
        }
        i++;
    }
    while (!computedTaskQueue.empty())
    {
        int computedTask = computedTaskQueue.front();
        computedTaskQueue.pop();
        result.push_back({computedTask, CFStatusTable[computedTask]});
        // cfResource.push_back(computedTask);
        // updateCFStatusTable(cfResource)
    }
}

int main()
{

    srand(time(0));
    // cout << "Jaj Shree Ram\n";
    cout << "Enter the number of tasks\n";
    int n;
    cin >> n;
    vector<int> adj[n];

    int no_ofedges = rand() % ((n * (n - 1)));
    // cout<<"Number of edges is "<<no_ofedges<<endl;
    int cnt = 0;
    cout << "\nConnected edges\n";
    for (int i = 0; i < no_ofedges; i++)
    {
        int x = rand() % n;
        int y = rand() % n;

        if (x != y)
        {
            if (find(adj[x].begin(), adj[x].end(), y) == adj[x].end())
            {
                adj[x].push_back(y);
                // cout << x << " ->" << y << endl;
                cnt++;
            }
        }
    }
    // cout << "Number of edges is " << cnt << endl;
    // cout << endl;
    /*********************************************/

    vector<pair<int, vector<int>>> UT;  // UT sorted List of Task
    insertintopairofvector(adj, n, UT); // pair of int and vector<int>

    vector<int> noofrequests(n);
    vector<int> workload(n);
    // vector<int> noofrequests{1, 2, 5, 2, 4, 3}; //   request
    // vector<int> workload{2, 5, 4, 1, 2, 3};     // workload
    // vector<int> noofrequests(n), workload(n); // two vector's for number of workload and noofrequests  of task size;

    // int no_of_r = 10; // no_of_r is range from 0 to no_of_r  requests
    int no_of_r = 5;
    // cout << "Enter maximum number of request\n";
    // cin >> no_of_r;
    cout << "Number of requests are\n";
    for (int i = 0; i < n; i++)
    {
        noofrequests[i] = (rand() % no_of_r) + 1; // i added 1 because if we divide any number by 0 then it gives infinite value
                                                  // request is from 1 to 10
        cout << noofrequests[i] << " ";
    }

    // int work_l = 10;                     // workload is from 1 to work_l
    int work_l = 1024;
    // cout << "Enter workload from 4 to 1024   (it is in KB) \n";
    // cin >> work_l;
    cout << "\nWorkload\n";
    for (int i = 0; i < n; i++)
    {
        workload[i] = (rand() % work_l) + 1; // i added 1 because if we divide any number by 0 then it gives infinite value
        cout << workload[i] << " ";
    }

    int MNR = *min_element(noofrequests.begin(), noofrequests.end()); // minimum no. of request
    cout << "\nMinimum number of request " << MNR;
    int WM = *min_element(workload.begin(), workload.end()); // minimum workload
    cout << "\n Minimum workload " << WM << endl;
    cout << "************************ Before Comparative Attribute Algorithm(CAA) ******************************\n";
    printgraphVP(UT);
    cout << endl;

    // Start the timer
    auto startTime = high_resolution_clock::now();

    /*********************Camparative attribute Algorithm ****************************/

    int si = UT.size() - 1;
    mergesort(UT, 0, si, noofrequests, workload, MNR, WM); // here we get Sorted list of tasks

    /*****************************************************************************/
    cout << "************************ After Comparative Attribute Algorithm(CAA) ******************************\n";
    printgraphVP(UT);
    cout << endl; /*I used two diffrent function for printing into graph because i
                     take both task list sorted and unsorted into different file */

    vector<int> ETR(n), RR(n), PR(n), BR(n);
    // ETR Execution time ratio ,RR Ram ratio ,PR processor Ratio,BR Bandwidth Ratio
    /******************************************/
    int A = 250;
    // cout << "Enter the Execution time highest range\n";
    // cin >> A;
    cout << "\nExecution time ratio\n";
    for (int i = 0; i < n; i++)
    {
        ETR[i] = (rand() % A) + 1;
        cout << ETR[i] << " ";
    }
    // cout << endl;
    /******************************************/
    int B = 512;
    // cout << "Enter the RAM ratio\n";
    // cin >> B;
    cout << "\nRam ratio\n";
    for (int i = 0; i < n; i++)
    {
        RR[i] = (rand() % B) + 1;
        cout << RR[i] << " ";
    }
    // cout << endl;
    /******************************************/
    int C = 99;
    // cout << "Enter the Processor Ratio\n";
    // cin >> C;
    cout << "\nProcessor Ratio\n";
    for (int i = 0; i < n; i++)
    {
        PR[i] = (rand() % C) + 1;
        cout << PR[i] << " ";
    }
    // cout << endl;
    /******************************************/
    int D = 100;
    // cout << "Enter the Bandwidth Ratio\n";
    // cin >> D;
    cout << "\nBandwidth Ratio\n";
    for (int i = 0; i < n; i++)
    {
        BR[i] = (rand() % D) + 1;
        cout << BR[i] << " ";
    }
    cout << endl;

    /****************   citizenfogmanager ***********************/
    citizenfogmanager(UT, RR, PR, BR, ETR);

    int METR = *min_element(ETR1.begin(), ETR1.end());
    int MRR = *min_element(RR1.begin(), RR1.end());
    int MPR = *min_element(PR1.begin(), PR1.end());
    int MBR = *min_element(BR1.begin(), BR1.end());

    // Stop the timer
    auto endTime = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(endTime - startTime);

    // Output the elapsed time
    // cout << "\nExecution Time: For CF " << duration.count() << " minutes" << endl;

    // Start the timer
    auto startTime1 = high_resolution_clock::now();

    cout << "********** Before Linear Attributes Summarized Algorithm(LASA) ************\n";
    printgraphVP(UF);
    // printBinG(UT); // for printing unsorted task into text file
    cout << endl;
    /*********************Camparative attribute Algorithm ****************************/
    int si1 = UF.size() - 1;
    mergesort1(UF, 0, si1, ETR1, RR1, PR1, BR1, METR, MRR, MPR, MBR); // here we get Sorted list of tasks
    /*****************************************************************************/
    cout << "**************** After Linear Attributes Summarized Algorithm(LASA) ************\n";
    printgraphVP(UF);
    // printAinG(UT); // for printing sorted task into text file
    cout << endl; /*I used two diffrent function for printing into graph because i
                     take both task list sorted and unsorted into different file */

    queue<int> ITQ; // Incoming task queue of task from CF
    cout << "Task Recives from MNH\n";
    for (auto p : UF)
    {
        cout << p.first << " ";
        ITQ.push(p.first);
    }
    // cout<<"\nPE BW PS RAM\n";
    for (int i = 0; i < n; i++) //  CF status table under MF {RAM,PE,BW,PS}
    {
        vector<int> vv;
        int RAM, PE, BW, PS, R;
        R = 0;
        RAM = rand() % 512 + 1;
        PE = n;
        BW = rand() % 1024 + 1;
        PS = rand() % 1024 + 1;
        vv.push_back(RAM);
        vv.push_back(PE);
        vv.push_back(BW);
        vv.push_back(PS);
        vv.push_back(R);
        // cout << endl<< i << " " << RAM << " " << PE << " " << BW << " " <<PS;

        CFStatusTable.push_back(vv);
    }

    vector<int> ComputableCF;
    for (int i = 0; i < n; i++)
    {
        int x;
        x = rand() % 2;
        ComputableCF.push_back(x);
    }

    // vector<int> waitingQueue; // waiting  queue for task that could not be assigned to any CF
    // vector<int> result;       // Execution result of Task
    // vector<int> cfResource;   // Resource of a particular CF

    MasterFogManager(ITQ, ComputableCF);

    // Stop the timer
    auto endTime1 = high_resolution_clock::now();
    auto duration1 = duration_cast<milliseconds>(endTime1 - startTime1);

    // Output the elapsed time
    cout << "\nExecution Time: For MF " << duration1.count() << " minutes" << endl;

    cout << endl;
    for (auto p : result)
    {
        cout << "Task " << p.first << endl;
        cout << "              RAM " << p.second[0] << endl;
        cout << "               PE " << p.second[1] << endl;
        cout << "               BW " << p.second[2] << endl;
        cout << "               PS " << p.second[3] << endl;
    }

    cout << endl;
    cout << "Task Are executed by citizen fog " << taskexexuteinCF.size() << endl;

    for (auto p : taskexexuteinCF)
    {
        cout << p << " ";
    }
    cout << endl;

    cout << "Task are executed by master fog " << result.size() << endl;
    for (auto p : result)
    {
        cout << p.first << " ";
    }
    vector<int> vp;
    for (auto p : taskexexuteinCF)
    {
        vp.push_back(p);
    }
    for (auto p : result)
    {
        vp.push_back(p.first);
    }
    sort(vp.begin(), vp.end());
    cout << endl;

    cout << "Task that go to cloud for execution " << n - taskexexuteinCF.size() - result.size() << endl;
    for (int i = 0; i < n; i++)
    {
        if (find(vp.begin(), vp.end(), i) == vp.end())
            cout << i << " ";
    }
    cout << "\nExecution Time: For CF " << duration.count() << " miliseconds" << endl;
    cout << "Execution Time: For MF " << duration1.count() << " miliseconds" << endl;

    int temp1 = (taskexexuteinCF.size() + result.size());
    float temp2 = temp1 * 100.0;
    int dependencyOnC = (100-temp2 / n);
    cout << "depecdency on cloud reduced by " << dependencyOnC << " %" << endl;
    int Etime = (duration.count() + duration1.count());
    int Etime1 = Etime / temp1;
    int timedependOnC = (Etime1 * (n - temp1) * 100) / Etime;
    cout << "Execution Time decrease by " << 100 - timedependOnC << " %" << endl;

    fstream obj;
    obj.open("t1.txt", ios::app);
    // obj<<"Total Number of tasks  Task Executed by CF Task Executed by MF Dependency on Cloud Execution time decrease on Cloud By"<<endl;

    obj << n << "                     " << taskexexuteinCF.size() << "                       " << result.size() << "                       " << dependencyOnC << " %"
        << "                                 " <<timedependOnC<< " %" << endl;

    getch();
}
