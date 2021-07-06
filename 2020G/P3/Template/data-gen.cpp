#include<iostream>
#include<stdlib.h>

using namespace std;

int main(){
	int T=100;
	cout<<T<<endl;
	for(int c=0;c<T;c++){
		int N = rand()%1000;
		int W = rand()%1000;
		cout<<W<<" "<<N<<endl;
		for(int i=0;i<W;i++){
			cout<<rand()%N<<" ";
		}
		cout<<endl;
	}
}
