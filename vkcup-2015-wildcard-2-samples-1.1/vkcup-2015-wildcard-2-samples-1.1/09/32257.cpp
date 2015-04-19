#include <bits/stdc++.h>
using namespace std;
struct node
{
	node *ptr[2];
	node()
	{
		ptr[0]=NULL;
		ptr[1]=NULL;
	}
};
int n,m,row_sum[6],col_sum[21],ans[21];
vector <int> mask_records[7];
node *roots[6];
void trie_insert(int x, int ind)
{
	node *pos = roots[ind];
	for (int i = 0; i < m; ++i)
	{
		int npos;
		if(x & (1<<i))
			npos=1;
		else
			npos=0;
		if(pos->ptr[npos] == NULL)
			pos->ptr[npos] = new node();
		pos = pos->ptr[npos];
	}
}
void row_preprocess()
{
	for (int mask = 0; mask < (1<<m); ++mask)
	{
		int ctr=0;
		bool seg=false;
		for (int i = 0; i < m; ++i)
		{
			if(mask & (1<<i))
			{
				if(!seg)
				{
					seg=true;
					ctr++;
				}
			}
			else
			{
				seg=false;
			}
		}
		for (int i = 0; i < n; ++i)
		{
			if(row_sum[i] == ctr)
			{
				bool isval=true;
				for (int j = 0; j < m; ++j)
				{
					bool found = false;
					for (int k = 0; k < mask_records[col_sum[j]].size(); ++k)
					{
						if((mask & (1<<j)) && (mask_records[col_sum[j]][k] & (1<<i)))
						{
							found = true;
							break;
						}
						if(!(mask & (1<<j)) && !(mask_records[col_sum[j]][k] & (1<<i)))
						{
							found = true;
							break;
						}
					}
					if(!found)
					{
						isval=false;
						break;
					}
				}
				if(isval)
					trie_insert(mask,i);
			}
		}
	}
}
void col_preprocess()
{
	for (int mask = 0; mask < (1<<n); ++mask)
	{
		int ctr=0;
		bool seg=false;
		for (int i = 0; i < n; ++i)
		{
			if(mask & (1<<i))
			{
				if(!seg)
				{
					seg=true;
					ctr++;
				}
			}
			else
			{
				seg=false;
			}
		}
		mask_records[ctr].push_back(mask);
	}
}
bool recurse(int pos, node *cpos[])
{
	if(pos == m)
		return true;
	for (int i = 0; i < mask_records[col_sum[pos]].size(); ++i)
	{
		bool isval=true;
		for (int j = 0; j < n; ++j)
		{
			if(mask_records[col_sum[pos]][i] & (1<<j))
			{
				if(cpos[j]->ptr[1] == NULL)
				{
					isval=false;
					break;
				}
			}
			else
			{
				if(cpos[j]->ptr[0] == NULL)
				{
					isval=false;
					break;
				}
			}
		}
		if(isval)
		{
			node *npos[n];
			for (int j = 0; j < n; ++j)
			{
				if(mask_records[col_sum[pos]][i] & (1<<j))
					npos[j] = cpos[j]->ptr[1];
				else
					npos[j] = cpos[j]->ptr[0];
			}
			bool found = recurse(pos+1,npos);
			if(found)
			{
				ans[pos]=mask_records[col_sum[pos]][i];
				return true;
			}
		}
	}
	return false;
}
int main()
{
	// freopen("input.txt", "r", stdin);
	ios_base::sync_with_stdio(0);
	for (int i = 0; i < 6; ++i)
	{
		roots[i] = new node();
	}
	cin>>n>>m;
	for (int i = 0; i < n; ++i)
	{
		cin>>row_sum[i];
	}
	for (int i = 0; i < m; ++i)
	{
		cin>>col_sum[i];
	}
	col_preprocess();
	row_preprocess();
	node *cpos[n];
	for (int i = 0; i < n; ++i)
	{
		cpos[i]=roots[i];
	}
	recurse(0,cpos);
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < m; ++j)
		{
			if(ans[j] & (1<<i))
				cout<<'*';
			else
				cout<<'.';
		}
		cout<<"\n";
	}
	return 0;
}