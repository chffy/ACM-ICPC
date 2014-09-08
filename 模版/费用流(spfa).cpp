int ans1=0,ans2=0;     //ans1:flow£¬ans2:value

namespace Flow{
    
queue <int> q;

    int value_flow(){              
        for (int i=s; i<=t; ++i){
            bo[i]=0;
            dis[i]=INF;
            max_flow[i]=0;
        }
        q.push(s);
        dis[s]=0;
        max_flow[s]=INF;
        while (!q.empty()){
            int x=q.front();
            q.pop();
            bo[x]=0;
            for (int k=first[x]; k!=-1; k=next[k]){
                int l=end[k];
                if (w1[k]>0 && dis[l]>dis[x]+w2[k]){
                    max_flow[l]=min(w1[k],max_flow[x]);
                    pre[l]=x;  prd[l]=k;
                    dis[l]=dis[x]+w2[k];
                    if (!bo[l]) bo[l]=1,q.push(l);
                }
            }
        }
        return max_flow[t]>0;
    }
    void back_flow(){                     
        ans1+=max_flow[t];
        ans2+=dis[t]*max_flow[t];
        for (int x=t; x!=s; x=pre[x]){
            w1[prd[x]]-=max_flow[t];
            w1[prd[x]^1]+=max_flow[t];
        }
    }
}
 
int main(){
    ...//input and build edge
    while (Flow::value_flow()) Flow::back_flow();
    return 0;
}
