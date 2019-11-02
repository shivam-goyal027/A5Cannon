#include<fstream> 
#include<iostream> 
#include<algorithm> 
#include<vector> 
#include<time.h>
#include<vector>
#include<time.h>
#include<chrono>
#include<limits.h> 
#include<math.h>
#include<map>
#include<string.h>
using namespace std;

struct position
{
	pair<int,int> p;
	position(pair<int,int> p2){
		p=p2;
	}
	position(const position& o)
};


int main(int argc, char* argv[]){
	int id,n,m ,t;
	cin>>id>>n>>m>>t;
	position ***board;
	
	board=new position**[n];
	for(int i=0;i<n;i++){
		board[i]=new position*[m];
	}

	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			position* a1=new position(make_pair(-1,-1));
			board[i][j]=a1;
		}
	}
	pair<int,int> p1=make_pair(-1,-1);
	position Soldier = new position[3*(m/2)];
	
	// Soldier=new position[3*(m/2)];
	for(int i=0;i<3*(m/2);i++){
		Soldier[i]=position(make_pair(2*i/3,i%3));
		board[2*i/3][i%3]=&Soldier[i];
	}
	position *EnemySoldier;
	
	EnemySoldier=new position[3*(m/2)];
	for(int i=0;i<3*(m/2);i++){
		EnemySoldier[i]=new postion(make_pair(2*i/3+1,n-1-i%3));
		board[2*i/3+1][n-1-i%3]=&EnemySoldier[i];
	}
	position *Townhall;
	
	Townhall=new position[(m/2)];
	for(int i=0;i<(m/2);i++){
		Townhall[i]=new postion(make_pair(2*i+1,0));
		board[2*i+1][0]=&Townhall[i];
	}
	position *EnemyTownhall;
	
	EnemyTownhall=new position[(m/2)];
	for(int i=0;i<(m/2);i++){
		EnemyTownhall[i]=new postion(make_pair(2*i,n-1));
		board[2*i][n-1]=&EnemyTownhall[i];
	}
	
	return 0;
}
