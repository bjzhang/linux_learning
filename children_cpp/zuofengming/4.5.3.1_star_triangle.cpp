
#include <iostream>
#include <cstdio>

using namespace std;

int main()
{
	int n;
	int i,j;
	
	cin>>n; 

	for (i = 0; i < n; i++)
	{
		for ( j = 1; j < n - i; j++)
		{
			cout<<" ";
		}
		for ( j = 0; j < 2 * i + 1; j++)
		{
			cout<<"*";
		}
		cout<<endl;
	}
}
