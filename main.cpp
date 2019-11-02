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
	position(){}
	position(pair<int,int> p2){
		p=p2;
	}
};

struct moves
{
	int b,c,e,f;
	char a,d;	
};
vector<pair<pair<int,int>,int> >update_enemy_cannons(int **board,pair<int,int> *EnemySoldier,int n,int m){
	vector<pair<pair<int,int>,int> > res;
	int x,y;
	for (int i=1;i<=3*(m/2);i++){
		x=EnemySoldier[i].first;y=EnemySoldier[i].second;
		if(x!=-1){
			if(x-2>=0){
				if(board[x-1][y]==-1 && board[x-2][y]==-1 && x+1<m-1){
					if(board[x+1][y]==0)
					res.push_back(make_pair(make_pair(x,y),1));
				}
			}
			if(x+2<m){
				if(board[x+1][y]==-1 && board[x+2][y]==-1 && x-1>0){
					if(board[x-1][y]==0)
					res.push_back(make_pair(make_pair(x,y),-1));
				}
			}
			if(y-2>=0){
				if(board[x][y-1]==-1 && board[x][y-2]==-1 && y+1<n-1){
					if(board[x][y+1]==0)
					res.push_back(make_pair(make_pair(x,y),2));
				}
			}
			if(y+2<n){
				if(board[x][y+1]==-1 && board[x][y+2]==-1 && y-1>0){
					if(board[x][y-1]==0)
					res.push_back(make_pair(make_pair(x,y),-2));
				}
			}
			if(x-2>=0 && y-2>=0){
				if(board[x-1][y-1]==-1 && board[x-2][y-2]==-1 && x+1<m-1 && y+1<n-1){
					if(board[x+1][y+1]==0)
					res.push_back(make_pair(make_pair(x,y),3));
				}
			}
			if(x+2<m && y+2<n){
				if(board[x+1][y+1]==-1 && board[x+2][y+2]==-1 && x-1>0 && y-1>0){
					if(board[x-1][y-1]==0)
					res.push_back(make_pair(make_pair(x,y),-3));
				}
			}
			if(x-2>=0 && y+2<n){
				if(board[x-1][y+1]==-1 && board[x-2][y+2]==-1 && x+1<m-1 && y-1>0){
					if(board[x+1][y-1]==0)
					res.push_back(make_pair(make_pair(x,y),4));
				}
			}
			if(x+2<m && y-2>=0){
				if(board[x+1][y-1]==-1 && board[x+2][y-2]==-1 && x-1>0 && y+1<n-1){
					if(board[x-1][y+1]==0)
					res.push_back(make_pair(make_pair(x,y),-4));
				}
			}
		}
	}
	return res;

}
vector<pair<pair<int,int>,int> >update_cannons(int **board,pair<int,int> *Soldier,int n,int m){
	vector<pair<pair<int,int>,int> > res;
	int x,y;
	for (int i=1;i<=3*(m/2);i++){
		x=Soldier[i].first;y=Soldier[i].second;
		if(x!=-1){
			if(x-2>=0){
				if(board[x-1][y]==1 && board[x-2][y]==1 && x+1<m-1){
					if(board[x+1][y]==0)
					res.push_back(make_pair(make_pair(x,y),1));
				}
			}
			if(x+2<m){
				if(board[x+1][y]==1 && board[x+2][y]==1 && x-1>0){
					if(board[x-1][y]==0)
					res.push_back(make_pair(make_pair(x,y),-1));
				}
			}
			if(y-2>=0){
				if(board[x][y-1]==1 && board[x][y-2]==1 && y+1<n-1){
					if(board[x][y+1]==0)
					res.push_back(make_pair(make_pair(x,y),2));
				}
			}
			if(y+2<n){
				if(board[x][y+1]==1 && board[x][y+2]==1 && y-1>0){
					if(board[x][y-1]==0)
					res.push_back(make_pair(make_pair(x,y),-2));
				}
			}
			if(x-2>=0 && y-2>=0){
				if(board[x-1][y-1]==1 && board[x-2][y-2]==1 && x+1<m-1 && y+1<n-1){
					if(board[x+1][y+1]==0)
					res.push_back(make_pair(make_pair(x,y),3));
				}
			}
			if(x+2<m && y+2<n){
				if(board[x+1][y+1]==1 && board[x+2][y+2]==1 && x-1>0 && y-1>0){
					if(board[x-1][y-1]==0)
					res.push_back(make_pair(make_pair(x,y),-3));
				}
			}
			if(x-2>=0 && y+2<n){
				if(board[x-1][y+1]==1 && board[x-2][y+2]==1 && x+1<m-1 && y-1>0){
					if(board[x+1][y-1]==0)
					res.push_back(make_pair(make_pair(x,y),4));
				}
			}
			if(x+2<m && y-2>=0){
				if(board[x+1][y-1]==1 && board[x+2][y-2]==1 && x-1>0 && y+1<n-1){
					if(board[x-1][y+1]==0)
					res.push_back(make_pair(make_pair(x,y),-4));
				}
			}
		}
	}
	return res;

}
void do_move(moves M,int **board, pair<int,int> *Soldier,pair<int,int> *EnemySoldier,pair<int,int> *Townhall,pair<int,int> *EnemyTownhall){
	int x1=M.b;
	int y1=M.c;
	int x2=M.e;
	int y2=M.f;
	if(M.a=='S' && M.d=='M'){
		board[x1][y1]=0;
		int i=1;
		while(true){
			if(Soldier[i].first==x1 && Soldier[i].second==y1){
				Soldier[i]=make_pair(x2,y2);
				break;
			}
			i++;
		}
		i=1;
		if(board[x2][y2]==-1){
			while(true){
				if(EnemySoldier[i].first==x2 && EnemySoldier[i].second==y2){
					EnemySoldier[i]=make_pair(-1,-1);
					break;
				}
				i++;
			}
			EnemySoldier[0]=make_pair(EnemySoldier[0].first-1,0);
		}else if(board[x2][y2]==-2){
			while(true){
				if(EnemyTownhall[i].first==x2 && EnemyTownhall[i].second==y2){
					EnemyTownhall[i]=make_pair(-1,-1);
					break;
				}
				i++;
			}
			EnemyTownhall[0]=make_pair(EnemyTownhall[0].first-1,0);
		}
		board[x2][y2]=1;
	}
	else if(M.a=='S' && M.d=='B'){
		int i=1;
		if(board[x2][y2]==-1){
			while(true){
				if(EnemySoldier[i].first==x2 && EnemySoldier[i].second==y2){
					EnemySoldier[i]=make_pair(-1,-1);
					break;
				}
				i++;
			}
			EnemySoldier[0]=make_pair(EnemySoldier[0].first-1,0);
		}else if(board[x2][y2]==-2){
			while(true){
				if(EnemyTownhall[i].first==x2 && EnemyTownhall[i].second==y2){
					EnemyTownhall[i]=make_pair(-1,-1);
					break;
				}
				i++;
			}
			EnemyTownhall[0]=make_pair(EnemyTownhall[0].first-1,0);
		}
		board[x2][y2]=0;
	}
}
bool adjacent(int **board,int x, int y,int n,int m){
	if(y+1<n){
		if(board[x][y+1]==-2||board[x][y+1]==-1)
			return true;
		if(x+1<m){
			if(board[x+1][y+1]==-2||board[x+1][y+1]==-1)
				return true;
			if(board[x+1][y]==-2||board[x+1][y]==-1)
				return true;
		}
		if(x-1>=0){
			if(board[x-1][y+1]==-2||board[x-1][y+1]==-1)
				return true;
			if(board[x-1][y]==-2||board[x-1][y]==-1)
				return true;
		}
		return false;
	}
	return false;
}
vector<moves> valid_moves_for_soldier(int **board, pair<int,int> pos,int n,int m){
	moves vm;
	vector<moves> ans;
	int x = pos.first;
	int y = pos.second;
	//Normal moves
    if(x-1>=0 && y+1<n){
    	if(board[x-1][y+1]!=2 && board[x-1][y+1]!=1){
    		vm.a='S';vm.b=(x);vm.c=(y);vm.d='M';vm.e=(x-1);vm.f=(y+1);ans.push_back(vm);
    	}
    }
    if(x>=0 && y+1<n){
    	if(board[x][y+1]!=2 && board[x][y+1]!=1){
    		vm.a='S';vm.b=(x);vm.c=(y);vm.d='M';vm.e=(x);vm.f=(y+1);ans.push_back(vm);
    	}
    }
    if(x+1<m && y+1<n){
    	if(board[x+1][y+1]!=2 && board[x+1][y+1]!=1){
    		vm.a='S';vm.b=(x);vm.c=(y);vm.d='M';vm.e=(x+1);vm.f=(y+1);ans.push_back(vm);
    	}
    }
    //Sideways
    if(x-1>=0 && y<n){
    	if(board[x-1][y]==-2 || board[x-1][y]==1){
    		vm.a='S';vm.b=(x);vm.c=(y);vm.d='M';vm.e=(x-1);vm.f=(y);ans.push_back(vm);
    	}
    }
    if(x+1<m && y<n){
    	if(board[x+1][y]==-2 || board[x+1][y]==1){
    		vm.a='S';vm.b=(x);vm.c=(y);vm.d='M';vm.e=(x+1);vm.f=(y);ans.push_back(vm);
    	}
    }
    //Retreat
    if(adjacent(board,x, y,n,m)){
    	if(y-2>=0){
    		if(x-2>=0){
    			if(board[x-2][y-2]!=2 && board[x-2][y-2]!=1){
    				vm.a='S';vm.b=(x);vm.c=(y);vm.d='M';vm.e=(x-2);vm.f=(y-2);ans.push_back(vm);
    			}
    		}
	    	if(x>=0){
	    		if(board[x][y-2]!=2 && board[x][y-2]!=1){
    				vm.a='S';vm.b=(x);vm.c=(y);vm.d='M';vm.e=(x);vm.f=(y-2);ans.push_back(vm);
    			}
	    	}
	    	if(x+2<m){
	    		if(board[x+2][y-2]!=2 && board[x+2][y-2]!=1){
    				vm.a='S';vm.b=(x);vm.c=(y);vm.d='M';vm.e=(x+2);vm.f=(y-2);ans.push_back(vm);
    			}
	    	}
    	}   	
    }
    // vector<moves> cannon_moves=cannon_shift(s,x,y);
    // ans.insert(ans.end(), cannon_moves.begin(), cannon_moves.end());

    // vector<moveStruct> fire = bullet_fires(s, x, y);
    // ans.insert(ans.end(), fire.begin(), fire.end());

    return ans;
}
vector<moves> cannon_shift(int **board,vector<pair<pair<int,int>,int> > cannon,int n,int m){
	int x,y,head;
	vector<moves> ans;
	moves vm;
	for(int i=0;i<cannon.size();i++){
		x=(cannon[i].first).first;
		y=(cannon[i].first).second;
		head=cannon[i].second;
		if(head==1 && x-3>=0){
			if(board[x-3][y]==0){
				vm.a='S';vm.b=(x);vm.c=(y);vm.d='M';vm.e=(x-3);vm.f=(y);ans.push_back(vm);
		    }
		}
		else if(head==-1 && x+3<m){
			if(board[x+3][y]==0){
				vm.a='S';vm.b=(x);vm.c=(y);vm.d='M';vm.e=(x+3);vm.f=(y);ans.push_back(vm);
		    }
		}
		else if(head==2 && y-3>=0){
			if(board[x][y-3]==0){
				vm.a='S';vm.b=(x);vm.c=(y);vm.d='M';vm.e=(x);vm.f=(y-3);ans.push_back(vm);
		    }
		}
		else if(head==-2 && y+3<n){
			if(board[x][y+3]==0){
				vm.a='S';vm.b=(x);vm.c=(y);vm.d='M';vm.e=(x);vm.f=(y+3);ans.push_back(vm);
		    }
		}
		else if(head==3 && x-3>=0 && y-3>=0){
			if(board[x-3][y-3]==0){
				vm.a='S';vm.b=(x);vm.c=(y);vm.d='M';vm.e=(x-3);vm.f=(y-3);ans.push_back(vm);
		    }
		}
		else if(head==-3 && x+3<m && y+3<n){
			if(board[x+3][y+3]==0){
				vm.a='S';vm.b=(x);vm.c=(y);vm.d='M';vm.e=(x+3);vm.f=(y+3);ans.push_back(vm);
		    }
		}
		else if(head==4 && x-3>=0 && y+3<n){
			if(board[x-3][y+3]==0){
				vm.a='S';vm.b=(x);vm.c=(y);vm.d='M';vm.e=(x-3);vm.f=(y+3);ans.push_back(vm);
		    }
		}
		else if(head==-4 && x+3<m && y-3>=0){
			if(board[x+3][y-3]==0){
				vm.a='S';vm.b=(x);vm.c=(y);vm.d='M';vm.e=(x+3);vm.f=(y-3);ans.push_back(vm);
		    }
		}
	}
	return ans;
}
vector<moves> bullet_fires(int **board,vector<pair<pair<int,int>,int> > cannon,int n,int m){
	int x,y,head;
	vector<moves> ans;
	moves vm;
	for(int i=0;i<cannon.size();i++){
		x=(cannon[i].first).first;
		y=(cannon[i].first).second;
		head=cannon[i].second;
		if(head==1){
			if(x+1<m){
				if(board[x+1][y]==0){
					if(x+2<m && board[x+2][y]!=1 && board[x+2][y]!=2) {vm.a='S';vm.b=(x);vm.c=(y);vm.d='M';vm.e=(x+2);vm.f=(y);ans.push_back(vm);}
					if(x+3<m && board[x+3][y]!=1 && board[x+3][y]!=2) {vm.a='S';vm.b=(x);vm.c=(y);vm.d='M';vm.e=(x+3);vm.f=(y);ans.push_back(vm);}
				}
			}
		}
		else if(head==-1){
			if(x-1>=0){
				if(board[x-1][y]==0){
					if(x-2>=0 && board[x-2][y]!=1 && board[x-2][y]!=2) {vm.a='S';vm.b=(x);vm.c=(y);vm.d='M';vm.e=(x-2);vm.f=(y);ans.push_back(vm);}
					if(x-3>=0 && board[x-3][y]!=1 && board[x-3][y]!=2) {vm.a='S';vm.b=(x);vm.c=(y);vm.d='M';vm.e=(x-3);vm.f=(y);ans.push_back(vm);}
				}
			}
			
		}
		else if(head==2){
			if(y+1<n){
				if(board[x][y+1]==0){
					if(y+2<n && board[x][y+2]!=1 && board[x][y+2]!=2) {vm.a='S';vm.b=(x);vm.c=(y);vm.d='M';vm.e=(x);vm.f=(y+2);ans.push_back(vm);}
					if(y+3<n && board[x][y+3]!=1 && board[x][y+3]!=2) {vm.a='S';vm.b=(x);vm.c=(y);vm.d='M';vm.e=(x);vm.f=(y+3);ans.push_back(vm);}
				}
			}
			
		}
		else if(head==-2){
			if(y-1>=0){
				if(board[x][y-1]==0){
					if(y-2>=0 && board[x][y-2]!=1 && board[x][y-2]!=2) {vm.a='S';vm.b=(x);vm.c=(y);vm.d='M';vm.e=(x);vm.f=(y-2);ans.push_back(vm);}
					if(y-3>=0 && board[x][y-3]!=1 && board[x][y-3]!=2) {vm.a='S';vm.b=(x);vm.c=(y);vm.d='M';vm.e=(x);vm.f=(y-3);ans.push_back(vm);}
				}
			}
		}
		else if(head==3){
			if(x+1<m && y+1<n){
				if(board[x+1][y+1]==0){
					if(y+2<n && x+2<m && board[x+2][y+2]!=1 && board[x+2][y+2]!=2) {vm.a='S';vm.b=(x);vm.c=(y);vm.d='M';vm.e=(x+2);vm.f=(y+2);ans.push_back(vm);}
					if(y+3<n && x+3<m && board[x+3][y+3]!=1 && board[x+3][y+3]!=2) {vm.a='S';vm.b=(x);vm.c=(y);vm.d='M';vm.e=(x+3);vm.f=(y+3);ans.push_back(vm);}
				}
			}
		}
		else if(head==-3){
			if(x-1>=0 && y-1>=0){
				if(board[x-1][y-1]==0){
					if(y-2>=0 && x-2>=0 && board[x-2][y-2]!=1 && board[x-2][y-2]!=2) {vm.a='S';vm.b=(x);vm.c=(y);vm.d='M';vm.e=(x-2);vm.f=(y-2);ans.push_back(vm);}
					if(y-3>=0 && x-3>=0 && board[x-3][y-3]!=1 && board[x-3][y-3]!=2) {vm.a='S';vm.b=(x);vm.c=(y);vm.d='M';vm.e=(x-3);vm.f=(y-3);ans.push_back(vm);}
				}
			}
		}
		else if(head==4){
			if(x+1<m && y-1>=0){
				if(board[x+1][y-1]==0){
					if(y-2>=0 && x+2<m && board[x+2][y-2]!=1 && board[x+2][y-2]!=2) {vm.a='S';vm.b=(x);vm.c=(y);vm.d='M';vm.e=(x+2);vm.f=(y-2);ans.push_back(vm);}
					if(y-3>=0 && x+3<m && board[x+3][y-3]!=1 && board[x+3][y-3]!=2) {vm.a='S';vm.b=(x);vm.c=(y);vm.d='M';vm.e=(x+3);vm.f=(y-3);ans.push_back(vm);}
				}
			}
		}
		else if(head==-4){
			if(x-1>=0 && y+1<n){
				if(board[x-1][y+1]==0){
					if(y+2<n && x-2>=0 && board[x-2][y+2]!=1 && board[x-2][y+2]!=2) {vm.a='S';vm.b=(x);vm.c=(y);vm.d='M';vm.e=(x-2);vm.f=(y+2);ans.push_back(vm);}
					if(y+3<n && x-3>=0 && board[x-3][y+3]!=1 && board[x-3][y+3]!=2) {vm.a='S';vm.b=(x);vm.c=(y);vm.d='M';vm.e=(x-3);vm.f=(y+3);ans.push_back(vm);}
				}
			}
		}
	}
	return ans;
}
vector<moves> valid_moves(int **board, pair<int,int> *Soldier,int n,int m,vector<pair<pair<int,int>,int> > cannon){
	vector<moves> valid_mv;
	vector<moves> ans;
	for (int i=1;i<=3*(m/2);i++){
		if(Soldier[i].first!=-1){
			valid_mv = valid_moves_for_soldier(board,Soldier[i],n,m);
			ans.insert(ans.end(), valid_mv.begin(), valid_mv.end());
		}
	}
	valid_mv=cannon_shift(board,cannon,n,m);
	ans.insert(ans.end(), valid_mv.begin(), valid_mv.end());
	valid_mv=bullet_fires(board,cannon,n,m);
	ans.insert(ans.end(), valid_mv.begin(), valid_mv.end());
	return ans;
}
int main(int argc, char* argv[]){
	int id,n,m ,t;
	cin>>id>>n>>m>>t;
	int **board;
	
	board=new int*[n];
	for(int i=0;i<n;i++){
		board[i]=new int[m];
	}

	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			board[i][j]=0;
		}
	}
	
	vector<pair<pair<int,int>,int> > Cannon;
	vector<pair<pair<int,int>,int> >EnemyCannon;

	pair<int,int> *Soldier = new pair<int,int>[3*(m/2)+1];
	Soldier[0]=make_pair(3*(m/2),0);
	for(int i=0;i<3*(m/2);i++){
		Soldier[i+1]= (make_pair(2*i/3+1,i%3));
		if(i%3==0){
			Cannon.push_back(make_pair((make_pair(2*i/3+1,i%3)),2));
		}
		board[2*(i/3)+1][i%3]=1;
	}

	pair<int,int> *EnemySoldier=new pair<int,int>[3*(m/2)+1];
	EnemySoldier[0]=make_pair(3*(m/2),0);
	for(int i=0;i<3*(m/2);i++){
		EnemySoldier[i+1]= (make_pair(2*i/3,n-1-i%3));
		if(i%3==0){
			Cannon.push_back(make_pair((make_pair(2*i/3,n-1-i%3)),-2));
		}
		board[2*(i/3)][n-1-i%3]=-1;
	}

	pair<int,int> *Townhall=new pair<int,int>[(m/2)+1];
	Townhall[0]=make_pair((m/2),0);
	for(int i=0;i<(m/2);i++){
		Townhall[i+1]= (make_pair(2*i,0));
		board[2*i][0]=2;
	}

	pair<int,int> *EnemyTownhall=new pair<int,int>[(m/2)+1];
	EnemyTownhall[0]=make_pair((m/2),0);
	for(int i=0;i<(m/2);i++){
		EnemyTownhall[i+1]= (make_pair(2*i+1,n-1));
		board[2*i+1][n-1]=-2;
	}
	if(id==2){
		moves M;
		cin>>M.a>>M.b>>M.c>>M.d>>M.e>>M.f;
		do_move(M,board,Soldier,EnemySoldier,Townhall,EnemyTownhall); 
		Cannon =update_cannons(board,Soldier,n,m);
		EnemyCannon=update_enemy_cannons(board,EnemySoldier,n,m);
	}
	valid_moves(board,Soldier,n,m,Cannon);
	return 0;
}