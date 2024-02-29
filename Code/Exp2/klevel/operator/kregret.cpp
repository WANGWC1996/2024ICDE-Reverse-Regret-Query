#include "kregret.h"
#include <sys/time.h>

void kregret::single_query(level &idx, int k, vector<float> q, double epsilon)
{
    clock_t qb=clock();
    int ave_vertex=0;
    set<int> results; results.clear();
    for (int i = 0; i < idx.idx[k].size(); i++) //scan k-level
    {
        kcell cur = idx.idx[k][i];
        int p = cur.objID;
        for (auto it = cur.topk.begin(); it != cur.topk.end(); it++)
            idx.AddHS(p, *it, false, cur.r.H);
        for (auto it = cur.Stau.begin(); it != cur.Stau.end(); it++)
            idx.AddHS(p, *it,true,cur.r.H);
        idx.AddHS(p, q, false, epsilon, cur.r.H);
        bool isFeasible = lp_adapter::is_Feasible(cur.r.H, cur.r.innerPoint, idx.dim);
        if (isFeasible)
        {
            idx.UpdateV(cur, ave_vertex);
            cur.r.printVertices();
        }

    }
    clock_t qe=clock();
    cout << "query time: " << (qe - qb) / (float)CLOCKS_PER_SEC << endl;
    return;
}


void kregret::up_down_query(level &idx, int k, vector<float> q, double epsilon)
{
    timeval t1; gettimeofday(&t1, 0);

    set<int> results; results.clear();
    int visit = 0, result = 0, ave_vertex = 0;
    vector<vector<kcell>> queue;
    for (int i = 0; i <= k; i++)
    {
        queue.push_back({});
    }
    for (auto it= idx.idx[0][0].Next.begin(); it!=idx.idx[0][0].Next.end(); it++)
    {
        queue[1].push_back(idx.idx[1][*it]);
    }
    //queue[1].push_back(idx.idx[0][0]); // only contains rootcell
    for (int i = 1; i <= k; i++) //scan k-level
    {
        set<int> hash_set; hash_set.clear();
        idx.region_map.clear();
        for (int j = 0; j < queue[i].size(); j++) // check each level
        {
            kcell& cur = queue[i][j];
            int p = cur.objID;
            int relation = idx.Check_relation(p, q, false, epsilon, cur.r.V);
            if (relation == -1)
            {
                //cur.r.printVertices();
            }
            else
            {
                if (cur.curk < idx.ik)
                {
                    for (auto it= cur.Next.begin(); it!=cur.Next.end(); it++)
                    {
                        if (hash_set.find(*it)==hash_set.end())
                        {
                            queue[i+1].push_back(idx.idx[i+1][*it]);
                            hash_set.insert(*it);
                        }
                    }
                }
                else
                {
                    // for large k
                    if(relation == 0)
                    {
                        for (auto it = cur.topk.begin(); it != cur.topk.end(); it++)
                            idx.AddHS(p, *it, false, cur.r.H);
                        for (auto it = cur.Stau.begin(); it != cur.Stau.end(); it++)
                            idx.AddHS(p, *it, true, cur.r.H);
                        idx.AddHS(p, q, false, epsilon, cur.r.H);
                        bool isFeasible = lp_adapter::is_Feasible(cur.r.H, cur.r.innerPoint, idx.dim);
                        if (isFeasible)
                        {
                            idx.UpdateV(cur, ave_vertex);
                            //cur.r.printVertices();
                        }
                    }
                }
            }
        }
    }


    timeval t2; gettimeofday(&t2, 0);
    double time_cost = (double) t2.tv_sec + (double) t2.tv_usec / 1000000 - (double) t1.tv_sec - (double) t1.tv_usec / 1000000;
    cout << "Time: " << time_cost << "\n\n\n";
    //cout << get_mem_usage() - mem_baseline << "\n";

    std::ofstream out_cp("../result.txt");
    out_cp << time_cost;
    out_cp.close();

    return;
}
