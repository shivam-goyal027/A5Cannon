#include<fstream> 
#include<iostream> 
#include<algorithm>
#include<time.h>
#include<vector>
#include<chrono>
#include<limits.h> 
#include<math.h>
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
pair<moves, int> max_value(bool warn, moves saved,int player_num,bool townhall_kill, int **board, int n, int m, int alpha, int beta, moves ms, int max_val, pair<int,int> *Soldier, pair<int,int> *EnemySoldier, pair<int,int> *Townhall, pair<int,int> *EnemyTownhall, vector<pair<pair<int,int>,int> > cannon, vector<pair<pair<int,int>,int> > Enemycannon);
pair<moves, int> max_value_enemy(bool warn, moves saved,int player_num,bool townhall_kill,int **board, int n, int m, int alpha, int beta, moves ms, int max_val, pair<int,int> *Soldier, pair<int,int> *EnemySoldier, pair<int,int> *Townhall, pair<int,int> *EnemyTownhall, vector<pair<pair<int,int>,int> > cannon, vector<pair<pair<int,int>,int> > Enemycannon);

vector<pair<pair<int,int>,int> > update_enemy_cannons(int **board,pair<int,int> *EnemySoldier,int n,int m){
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

vector<pair<pair<int,int>,int> > update_cannons(int **board,pair<int,int> *Soldier,int n,int m){
	vector<pair<pair<int,int>,int> > res;
	int x,y;
	for (int i=1;i<=3*(m/2);i++){
		x=Soldier[i].first;y=Soldier[i].second;
		//cerr<<x<<","<<y<<endl;
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

void do_move_enemy(moves M,int **board, pair<int,int> *Soldier,pair<int,int> *EnemySoldier,pair<int,int> *Townhall,pair<int,int> *EnemyTownhall){
	int x1=M.b;
	int y1=M.c;
	int x2=M.e;
	int y2=M.f;
	if(M.a=='S' && M.d=='M'){
		board[x1][y1]=0;
		int i=1;
		while(true){
			if(EnemySoldier[i].first==x1 && EnemySoldier[i].second==y1){
				EnemySoldier[i]=make_pair(x2,y2);
				break;
			}
			i++;
		}
		i=1;
		if(board[x2][y2]==1){
			while(true){
				if(Soldier[i].first==x2 && Soldier[i].second==y2){
					Soldier[i]=make_pair(-1,-1);
					break;
				}
				i++;
			}
			Soldier[0]=make_pair(Soldier[0].first-1,0);
		}else if(board[x2][y2]==2){
			while(true){
				if(Townhall[i].first==x2 && Townhall[i].second==y2){
					Townhall[i]=make_pair(-1,-1);
					break;
				}
				i++;
			}
			Townhall[0]=make_pair(Townhall[0].first-1,0);
		}
		board[x2][y2]=-1;
	}
	else if(M.a=='S' && M.d=='B'){
		int i=1;
		if(board[x2][y2]==1){
			while(true){
				if(Soldier[i].first==x2 && Soldier[i].second==y2){
					Soldier[i]=make_pair(-1,-1);
					break;
				}
				i++;
			}
			Soldier[0]=make_pair(Soldier[0].first-1,0);
		}else if(board[x2][y2]==2){
			while(true){
				if(Townhall[i].first==x2 && Townhall[i].second==y2){
					Townhall[i]=make_pair(-1,-1);
					break;
				}
				i++;
			}
			Townhall[0]=make_pair(Townhall[0].first-1,0);
		}
		board[x2][y2]=0;
	}
}

void do_move(moves M,int **board, pair<int,int> *Soldier, pair<int,int> *EnemySoldier, pair<int,int> *Townhall, pair<int,int> *EnemyTownhall){
	int x1=M.b;
	int y1=M.c;
	int x2=M.e;
	int y2=M.f;
	if(M.a=='S' && M.d=='M'){
		board[x1][y1]=0;
		int i=1;
		while(true){
			if(i>15){
					cerr<<"move"<<M.a<<M.b<<M.c<<M.d<<M.e<<M.f<<endl;
					for(int k=0;k<8;k++){
						for(int j=0;j<8;j++){
							cerr<<board[j][k]<<".";
						}
						cerr<<endl;
					}
					for(int k=1;k<=12;k++){
						cerr<<Soldier[k].first<<","<<Soldier[k].second<<endl;
					}
					break;
				}
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

bool adjacent_enemy(int **board,int x, int y,int n,int m){
	if(y-1>=0 && x+1<m && board[x+1][y-1]==1) return true;
	else if(y-1>=0 && board[x][y-1]==1) return true;
	else if(y-1>=0 && x-1>=0 && board[x-1][y-1]==1) return true;
	else if(x+1<m && board[x+1][y]==1) return true;
	else if(x-1>=0 && board[x-1][y]==1) return true;
	return false;
}

bool adjacent(int **board,int x, int y,int n,int m){
	if(y+1<n && x+1<m && board[x+1][y+1]==-1) return true;
	else if(y+1<n && board[x][y+1]==-1) return true;
	else if(y+1<n && x-1>=0 && board[x-1][y+1]==-1) return true;
	else if(x+1<m && board[x+1][y]==-1) return true;
	else if(x-1>=0 && board[x-1][y]==-1) return true;
	return false;
}

pair<vector<moves>,vector<moves> > valid_moves_for_enemy_soldier(int **board, pair<int,int> pos,int n,int m){
	moves vm;
	vector<moves> ans1;
	vector<moves> ans2;
	int x = pos.first;
	int y = pos.second;
	//Normal moves
    if(x-1>=0 && y-1>=0){
    	if(board[x-1][y-1]!=-2 && board[x-1][y-1]!=-1){
    		vm.a='S';vm.b=(x);vm.c=(y);vm.d='M';vm.e=(x-1);vm.f=(y-1);if(board[x-1][y-1]==0) ans2.push_back(vm); else ans1.push_back(vm);
    	}
    }
    if(x>=0 && y-1>=0){
    	if(board[x][y-1]!=-2 && board[x][y-1]!=-1){
    		vm.a='S';vm.b=(x);vm.c=(y);vm.d='M';vm.e=(x);vm.f=(y-1);if(board[x][y-1]==0) ans2.push_back(vm); else ans1.push_back(vm);
    	}
    }
    if(x+1<m && y-1>=0){
    	if(board[x+1][y-1]!=-2 && board[x+1][y-1]!=-1){
    		vm.a='S';vm.b=(x);vm.c=(y);vm.d='M';vm.e=(x+1);vm.f=(y-1);if(board[x+1][y-1]==0) ans2.push_back(vm); else ans1.push_back(vm);
    	}
    }
    //Sideways
    if(x-1>=0 && y<n){
    	if(board[x-1][y]==2 || board[x-1][y]==1){
    		vm.a='S';vm.b=(x);vm.c=(y);vm.d='M';vm.e=(x-1);vm.f=(y);ans1.push_back(vm);
    	}
    }
    if(x+1<m && y<n){
    	if(board[x+1][y]==2 || board[x+1][y]==1){
    		vm.a='S';vm.b=(x);vm.c=(y);vm.d='M';vm.e=(x+1);vm.f=(y);ans1.push_back(vm);
    	}
    }
    //Retreat
    if(adjacent_enemy(board,x, y,n,m)){
    	if(y+2<n){
    		if(x-2>=0){
    			if(board[x-2][y+2]!=-2 && board[x-2][y+2]!=-1){
    				vm.a='S';vm.b=(x);vm.c=(y);vm.d='M';vm.e=(x-2);vm.f=(y+2);if(board[x-2][y+2]==0) ans2.push_back(vm); else ans1.push_back(vm);
    			}
    		}
	    	if(x>=0){
	    		if(board[x][y+2]!=-2 && board[x][y+2]!=-1){
    				vm.a='S';vm.b=(x);vm.c=(y);vm.d='M';vm.e=(x);vm.f=(y+2);if(board[x][y+2]==0) ans2.push_back(vm); else ans1.push_back(vm);
    			}
	    	}
	    	if(x+2<m){
	    		if(board[x+2][y+2]!=-2 && board[x+2][y+2]!=-1){
    				vm.a='S';vm.b=(x);vm.c=(y);vm.d='M';vm.e=(x+2);vm.f=(y+2);if(board[x+2][y+2]==0) ans2.push_back(vm); else ans1.push_back(vm);
    			}
	    	}
    	}   	
    }

	return make_pair(ans1,ans2);
}

pair<vector<moves>,vector<moves> > valid_moves_for_soldier(int **board, pair<int,int> pos,int n,int m){
	moves vm;
	vector<moves> ans1;
	vector<moves> ans2;
	int x = pos.first;
	int y = pos.second;
	//Normal moves
    if(x-1>=0 && y+1<n){
    	if(board[x-1][y+1]!=2 && board[x-1][y+1]!=1){
    		vm.a='S';vm.b=(x);vm.c=(y);vm.d='M';vm.e=(x-1);vm.f=(y+1);
    		if(board[x-1][y+1]==0) ans2.push_back(vm); else ans1.push_back(vm);
    	}
    }
    if(x>=0 && y+1<n){
    	if(board[x][y+1]!=2 && board[x][y+1]!=1){
    		vm.a='S';vm.b=(x);vm.c=(y);vm.d='M';vm.e=(x);vm.f=(y+1);if(board[x][y+1]==0) ans2.push_back(vm); else ans1.push_back(vm);
    	}
    }
    if(x+1<m && y+1<n){
    	if(board[x+1][y+1]!=2 && board[x+1][y+1]!=1){
    		vm.a='S';vm.b=(x);vm.c=(y);vm.d='M';vm.e=(x+1);vm.f=(y+1);if(board[x+1][y+1]==0) ans2.push_back(vm); else ans1.push_back(vm);
    	}
    }
    //Sideways
    if(x-1>=0 && y<n){
    	if(board[x-1][y]==-2 || board[x-1][y]==-1){
    		vm.a='S';vm.b=(x);vm.c=(y);vm.d='M';vm.e=(x-1);vm.f=(y);ans1.push_back(vm);
    	}
    }
    if(x+1<m && y<n){
    	if(board[x+1][y]==-2 || board[x+1][y]==-1){
    		vm.a='S';vm.b=(x);vm.c=(y);vm.d='M';vm.e=(x+1);vm.f=(y);ans1.push_back(vm);
    	}
    }
    //Retreat
    if(adjacent(board,x, y,n,m)){
    	if(y-2>=0){
    		if(x-2>=0){
    			if(board[x-2][y-2]!=2 && board[x-2][y-2]!=1){
    				vm.a='S';vm.b=(x);vm.c=(y);vm.d='M';vm.e=(x-2);vm.f=(y-2);if(board[x-2][y-2]==0) ans2.push_back(vm); else ans1.push_back(vm);
    			}
    		}
	    	if(x>=0){
	    		if(board[x][y-2]!=2 && board[x][y-2]!=1){
    				vm.a='S';vm.b=(x);vm.c=(y);vm.d='M';vm.e=(x);vm.f=(y-2);if(board[x][y-2]==0) ans2.push_back(vm); else ans1.push_back(vm);
    			}
	    	}
	    	if(x+2<m){
	    		if(board[x+2][y-2]!=2 && board[x+2][y-2]!=1){
    				vm.a='S';vm.b=(x);vm.c=(y);vm.d='M';vm.e=(x+2);vm.f=(y-2);if(board[x+2][y-2]==0) ans2.push_back(vm); else ans1.push_back(vm);
    			}
	    	}
    	}   	
    }

    return make_pair(ans1,ans2);
}

vector<moves> cannon_shift_enemy(int **board,vector<pair<pair<int,int>,int> > Enemycannon,int n,int m){
	int x,y,head;
	vector<moves> ans;
	moves vm;
	for(int i=0;i<Enemycannon.size();i++){
		x=(Enemycannon[i].first).first;
		y=(Enemycannon[i].first).second;
		head=Enemycannon[i].second;
		if(head==1 && x+1<m){
			if(board[x+1][y]==0){
				vm.a='S';vm.b=(x-2);vm.c=(y);vm.d='M';vm.e=(x+1);vm.f=(y);ans.push_back(vm);
		    }
		}
		else if(head==-1 && x-1>=0){
			if(board[x-1][y]==0){
				vm.a='S';vm.b=(x+2);vm.c=(y);vm.d='M';vm.e=(x-1);vm.f=(y);ans.push_back(vm);
		    }
		}
		else if(head==2 && y+1<n){
			if(board[x][y+1]==0){
				vm.a='S';vm.b=(x);vm.c=(y-2);vm.d='M';vm.e=(x);vm.f=(y+1);ans.push_back(vm);
		    }
		}
		else if(head==-2 && y-1>=0){
			if(board[x][y-1]==0){
				vm.a='S';vm.b=(x);vm.c=(y+2);vm.d='M';vm.e=(x);vm.f=(y-1);ans.push_back(vm);
		    }
		}
		else if(head==3 && x+1<m && y+1<n){
			if(board[x+1][y+1]==0){
				vm.a='S';vm.b=(x-2);vm.c=(y-2);vm.d='M';vm.e=(x+1);vm.f=(y+1);ans.push_back(vm);
		    }
		}
		else if(head==-3 && x-1>=0 && y-1>=0){
			if(board[x-1][y-1]==0){
				vm.a='S';vm.b=(x+2);vm.c=(y+2);vm.d='M';vm.e=(x-1);vm.f=(y-1);ans.push_back(vm);
		    }
		}
		else if(head==4 && x+1<m && y-1>=0){
			if(board[x+1][y-1]==0){
				vm.a='S';vm.b=(x-2);vm.c=(y+2);vm.d='M';vm.e=(x+1);vm.f=(y-1);ans.push_back(vm);
		    }
		}
		else if(head==-4 && x-1>=0 && y+1<n){
			if(board[x-1][y+1]==0){
				vm.a='S';vm.b=(x+2);vm.c=(y-2);vm.d='M';vm.e=(x-1);vm.f=(y+1);ans.push_back(vm);
		    }
		}
	}
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
		if(head==1 && x+1<m){
			if(board[x+1][y]==0){
				vm.a='S';vm.b=(x-2);vm.c=(y);vm.d='M';vm.e=(x+1);vm.f=(y);ans.push_back(vm);
		    }
		}
		else if(head==-1 && x-1>=0){
			if(board[x-1][y]==0){
				vm.a='S';vm.b=(x+2);vm.c=(y);vm.d='M';vm.e=(x-1);vm.f=(y);ans.push_back(vm);
		    }
		}
		else if(head==2 && y+1<n){
			if(board[x][y+1]==0){
				vm.a='S';vm.b=(x);vm.c=(y-2);vm.d='M';vm.e=(x);vm.f=(y+1);ans.push_back(vm);
		    }
		}
		else if(head==-2 && y-1>=0){
			if(board[x][y-1]==0){
				vm.a='S';vm.b=(x);vm.c=(y+2);vm.d='M';vm.e=(x);vm.f=(y-1);ans.push_back(vm);
		    }
		}
		else if(head==3 && x+1<m && y+1<n){
			if(board[x+1][y+1]==0){
				vm.a='S';vm.b=(x-2);vm.c=(y-2);vm.d='M';vm.e=(x+1);vm.f=(y+1);ans.push_back(vm);
		    }
		}
		else if(head==-3 && x-1>=0 && y-1>=0){
			if(board[x-1][y-1]==0){
				vm.a='S';vm.b=(x+2);vm.c=(y+2);vm.d='M';vm.e=(x-1);vm.f=(y-1);ans.push_back(vm);
		    }
		}
		else if(head==4 && x+1<m && y-1>=0){
			if(board[x+1][y-1]==0){
				vm.a='S';vm.b=(x-2);vm.c=(y+2);vm.d='M';vm.e=(x+1);vm.f=(y-1);ans.push_back(vm);
		    }
		}
		else if(head==-4 && x-1>=0 && y+1<n){
			if(board[x-1][y+1]==0){
				vm.a='S';vm.b=(x+2);vm.c=(y-2);vm.d='M';vm.e=(x-1);vm.f=(y+1);ans.push_back(vm);
		    }
		}
	}
	return ans;
}

pair<vector<moves>,vector<moves> > bullet_fires_enemy(int **board,pair<pair<int,int>,int> Enemycannon,int n,int m){
	int x,y,head;
	vector<moves> ans1;
	vector<moves> ans2;
	moves vm;
		x=(Enemycannon.first).first;
		y=(Enemycannon.first).second;
		head=Enemycannon.second;
		if(head==1){
			if(x+1<m){
				if(board[x+1][y]==0){
					if(x+2<m && board[x+2][y]!=-1 && board[x+2][y]!=-2) {vm.a='S';vm.b=(x);vm.c=(y);vm.d='B';vm.e=(x+2);vm.f=(y);if(board[x+2][y]==0) ans2.push_back(vm); else ans1.push_back(vm);}
					if(x+3<m && board[x+3][y]!=-1 && board[x+3][y]!=-2) {vm.a='S';vm.b=(x);vm.c=(y);vm.d='B';vm.e=(x+3);vm.f=(y);if(board[x+3][y]==0) ans2.push_back(vm); else ans1.push_back(vm);}
				}
			}
		}
		else if(head==-1){
			if(x-1>=0){
				if(board[x-1][y]==0){
					if(x-2>=0 && board[x-2][y]!=-1 && board[x-2][y]!=-2) {vm.a='S';vm.b=(x);vm.c=(y);vm.d='B';vm.e=(x-2);vm.f=(y);if(board[x-2][y]==0) ans2.push_back(vm); else ans1.push_back(vm);}
					if(x-3>=0 && board[x-3][y]!=-1 && board[x-3][y]!=-2) {vm.a='S';vm.b=(x);vm.c=(y);vm.d='B';vm.e=(x-3);vm.f=(y);if(board[x-3][y]==0) ans2.push_back(vm); else ans1.push_back(vm);}
				}
			}
			
		}
		else if(head==2){
			if(y+1<n){
				if(board[x][y+1]==0){
					if(y+2<n && board[x][y+2]!=-1 && board[x][y+2]!=-2) {vm.a='S';vm.b=(x);vm.c=(y);vm.d='B';vm.e=(x);vm.f=(y+2);if(board[x][y+2]==0) ans2.push_back(vm); else ans1.push_back(vm);}
					if(y+3<n && board[x][y+3]!=-1 && board[x][y+3]!=-2) {vm.a='S';vm.b=(x);vm.c=(y);vm.d='B';vm.e=(x);vm.f=(y+3);if(board[x][y+3]==0) ans2.push_back(vm); else ans1.push_back(vm);}
				}
			}
			
		}
		else if(head==-2){
			if(y-1>=0){
				if(board[x][y-1]==0){
					if(y-2>=0 && board[x][y-2]!=-1 && board[x][y-2]!=-2) {vm.a='S';vm.b=(x);vm.c=(y);vm.d='B';vm.e=(x);vm.f=(y-2);if(board[x][y-2]==0) ans2.push_back(vm); else ans1.push_back(vm);}
					if(y-3>=0 && board[x][y-3]!=-1 && board[x][y-3]!=-2) {vm.a='S';vm.b=(x);vm.c=(y);vm.d='B';vm.e=(x);vm.f=(y-3);if(board[x][y-3]==0) ans2.push_back(vm); else ans1.push_back(vm);}
				}
			}
		}
		else if(head==3){
			if(x+1<m && y+1<n){
				if(board[x+1][y+1]==0){
					if(y+2<n && x+2<m && board[x+2][y+2]!=-1 && board[x+2][y+2]!=-2) {vm.a='S';vm.b=(x);vm.c=(y);vm.d='B';vm.e=(x+2);vm.f=(y+2);if(board[x+2][y+2]==0) ans2.push_back(vm); else ans1.push_back(vm);}
					if(y+3<n && x+3<m && board[x+3][y+3]!=-1 && board[x+3][y+3]!=-2) {vm.a='S';vm.b=(x);vm.c=(y);vm.d='B';vm.e=(x+3);vm.f=(y+3);if(board[x+3][y+3]==0) ans2.push_back(vm); else ans1.push_back(vm);}
				}
			}
		}
		else if(head==-3){
			if(x-1>=0 && y-1>=0){
				if(board[x-1][y-1]==0){
					if(y-2>=0 && x-2>=0 && board[x-2][y-2]!=-1 && board[x-2][y-2]!=-2) {vm.a='S';vm.b=(x);vm.c=(y);vm.d='B';vm.e=(x-2);vm.f=(y-2);if(board[x-2][y-2]==0) ans2.push_back(vm); else ans1.push_back(vm);}
					if(y-3>=0 && x-3>=0 && board[x-3][y-3]!=-1 && board[x-3][y-3]!=-2) {vm.a='S';vm.b=(x);vm.c=(y);vm.d='B';vm.e=(x-3);vm.f=(y-3);if(board[x-3][y-3]==0) ans2.push_back(vm); else ans1.push_back(vm);}
				}
			}
		}
		else if(head==4){
			if(x+1<m && y-1>=0){
				if(board[x+1][y-1]==0){
					if(y-2>=0 && x+2<m && board[x+2][y-2]!=-1 && board[x+2][y-2]!=-2) {vm.a='S';vm.b=(x);vm.c=(y);vm.d='B';vm.e=(x+2);vm.f=(y-2);if(board[x+2][y-2]==0) ans2.push_back(vm); else ans1.push_back(vm);}
					if(y-3>=0 && x+3<m && board[x+3][y-3]!=-1 && board[x+3][y-3]!=-2) {vm.a='S';vm.b=(x);vm.c=(y);vm.d='B';vm.e=(x+3);vm.f=(y-3);if(board[x+3][y-3]==0) ans2.push_back(vm); else ans1.push_back(vm);}
				}
			}
		}
		else if(head==-4){
			if(x-1>=0 && y+1<n){
				if(board[x-1][y+1]==0){
					if(y+2<n && x-2>=0 && board[x-2][y+2]!=-1 && board[x-2][y+2]!=-2) {vm.a='S';vm.b=(x);vm.c=(y);vm.d='B';vm.e=(x-2);vm.f=(y+2);if(board[x-2][y+2]==0) ans2.push_back(vm); else ans1.push_back(vm);}
					if(y+3<n && x-3>=0 && board[x-3][y+3]!=-1 && board[x-3][y+3]!=-2) {vm.a='S';vm.b=(x);vm.c=(y);vm.d='B';vm.e=(x-3);vm.f=(y+3);if(board[x-3][y+3]==0) ans2.push_back(vm); else ans1.push_back(vm);}
				}
			}
		}
	
	return make_pair(ans1,ans2);
}

pair<vector<moves>,vector<moves> > bullet_fires(int **board,pair<pair<int,int>,int> cannon,int n,int m){
	int x,y,head;
	vector<moves> ans1;
	vector<moves> ans2;
	moves vm;
		x=(cannon.first).first;
		y=(cannon.first).second;
		head=cannon.second;
		if(head==1){
			if(x+1<m){
				if(board[x+1][y]==0){
					if(x+2<m && board[x+2][y]!=1 && board[x+2][y]!=2) {vm.a='S';vm.b=(x);vm.c=(y);vm.d='B';vm.e=(x+2);vm.f=(y);if(board[x+2][y]==0) ans2.push_back(vm); else ans1.push_back(vm);}
					if(x+3<m && board[x+3][y]!=1 && board[x+3][y]!=2) {vm.a='S';vm.b=(x);vm.c=(y);vm.d='B';vm.e=(x+3);vm.f=(y);if(board[x+3][y]==0) ans2.push_back(vm); else ans1.push_back(vm);}
				}
			}
		}
		else if(head==-1){
			if(x-1>=0){
				if(board[x-1][y]==0){
					if(x-2>=0 && board[x-2][y]!=1 && board[x-2][y]!=2) {vm.a='S';vm.b=(x);vm.c=(y);vm.d='B';vm.e=(x-2);vm.f=(y);if(board[x-2][y]==0) ans2.push_back(vm); else ans1.push_back(vm);}
					if(x-3>=0 && board[x-3][y]!=1 && board[x-3][y]!=2) {vm.a='S';vm.b=(x);vm.c=(y);vm.d='B';vm.e=(x-3);vm.f=(y);if(board[x-3][y]==0) ans2.push_back(vm); else ans1.push_back(vm);}
				}
			}
			
		}
		else if(head==2){
			if(y+1<n){
				if(board[x][y+1]==0){
					if(y+2<n && board[x][y+2]!=1 && board[x][y+2]!=2) {vm.a='S';vm.b=(x);vm.c=(y);vm.d='B';vm.e=(x);vm.f=(y+2);if(board[x][y+2]==0) ans2.push_back(vm); else ans1.push_back(vm);}
					if(y+3<n && board[x][y+3]!=1 && board[x][y+3]!=2) {vm.a='S';vm.b=(x);vm.c=(y);vm.d='B';vm.e=(x);vm.f=(y+3);if(board[x][y+3]==0) ans2.push_back(vm); else ans1.push_back(vm);}
				}
			}
			
		}
		else if(head==-2){
			if(y-1>=0){
				if(board[x][y-1]==0){
					if(y-2>=0 && board[x][y-2]!=1 && board[x][y-2]!=2) {vm.a='S';vm.b=(x);vm.c=(y);vm.d='B';vm.e=(x);vm.f=(y-2);if(board[x][y-2]==0) ans2.push_back(vm); else ans1.push_back(vm);}
					if(y-3>=0 && board[x][y-3]!=1 && board[x][y-3]!=2) {vm.a='S';vm.b=(x);vm.c=(y);vm.d='B';vm.e=(x);vm.f=(y-3);if(board[x][y-3]==0) ans2.push_back(vm); else ans1.push_back(vm);}
				}
			}
		}
		else if(head==3){
			if(x+1<m && y+1<n){
				if(board[x+1][y+1]==0){
					if(y+2<n && x+2<m && board[x+2][y+2]!=1 && board[x+2][y+2]!=2) {vm.a='S';vm.b=(x);vm.c=(y);vm.d='B';vm.e=(x+2);vm.f=(y+2);if(board[x+2][y+2]==0) ans2.push_back(vm); else ans1.push_back(vm);}
					if(y+3<n && x+3<m && board[x+3][y+3]!=1 && board[x+3][y+3]!=2) {vm.a='S';vm.b=(x);vm.c=(y);vm.d='B';vm.e=(x+3);vm.f=(y+3);if(board[x+3][y+3]==0) ans2.push_back(vm); else ans1.push_back(vm);}
				}
			}
		}
		else if(head==-3){
			if(x-1>=0 && y-1>=0){
				if(board[x-1][y-1]==0){
					if(y-2>=0 && x-2>=0 && board[x-2][y-2]!=1 && board[x-2][y-2]!=2) {vm.a='S';vm.b=(x);vm.c=(y);vm.d='B';vm.e=(x-2);vm.f=(y-2);if(board[x-2][y-2]==0) ans2.push_back(vm); else ans1.push_back(vm);}
					if(y-3>=0 && x-3>=0 && board[x-3][y-3]!=1 && board[x-3][y-3]!=2) {vm.a='S';vm.b=(x);vm.c=(y);vm.d='B';vm.e=(x-3);vm.f=(y-3);if(board[x-3][y-3]==0) ans2.push_back(vm); else ans1.push_back(vm);}
				}
			}
		}
		else if(head==4){
			if(x+1<m && y-1>=0){
				if(board[x+1][y-1]==0){
					if(y-2>=0 && x+2<m && board[x+2][y-2]!=1 && board[x+2][y-2]!=2) {vm.a='S';vm.b=(x);vm.c=(y);vm.d='B';vm.e=(x+2);vm.f=(y-2);if(board[x+2][y-2]==0) ans2.push_back(vm); else ans1.push_back(vm);}
					if(y-3>=0 && x+3<m && board[x+3][y-3]!=1 && board[x+3][y-3]!=2) {vm.a='S';vm.b=(x);vm.c=(y);vm.d='B';vm.e=(x+3);vm.f=(y-3);if(board[x+3][y-3]==0) ans2.push_back(vm); else ans1.push_back(vm);}
				}
			}
		}
		else if(head==-4){
			if(x-1>=0 && y+1<n){
				if(board[x-1][y+1]==0){
					if(y+2<n && x-2>=0 && board[x-2][y+2]!=1 && board[x-2][y+2]!=2) {vm.a='S';vm.b=(x);vm.c=(y);vm.d='B';vm.e=(x-2);vm.f=(y+2);if(board[x-2][y+2]==0) ans2.push_back(vm); else ans1.push_back(vm);}
					if(y+3<n && x-3>=0 && board[x-3][y+3]!=1 && board[x-3][y+3]!=2) {vm.a='S';vm.b=(x);vm.c=(y);vm.d='B';vm.e=(x-3);vm.f=(y+3);if(board[x-3][y+3]==0) ans2.push_back(vm); else ans1.push_back(vm);}
				}
			}
		}
	
	return make_pair(ans1,ans2);
}

vector<moves> valid_moves_enemy(int **board, pair<int,int> *EnemySoldier,int n,int m,vector<pair<pair<int,int>,int> > Enemycannon){
	pair<vector<moves>,vector<moves> > valid_mv;
	vector<moves> ans1;
	vector<moves> ans2;
	vector<moves> valid_mv1;
	for(int i=0;i<Enemycannon.size();i++){
		valid_mv=bullet_fires_enemy(board,Enemycannon[i],n,m);
		ans1.insert(ans1.end(), valid_mv.first.begin(), valid_mv.first.end());
		ans2.insert(ans2.end(), valid_mv.second.begin(), valid_mv.second.end());
	}
	for (int i=1;i<=3*(m/2);i++){
		if(EnemySoldier[i].first!=-1){
			valid_mv = valid_moves_for_enemy_soldier(board,EnemySoldier[i],n,m);
			ans1.insert(ans1.end(), valid_mv.first.begin(), valid_mv.first.end());
			ans2.insert(ans2.end(), valid_mv.second.begin(), valid_mv.second.end());
		}
	}
	valid_mv1=cannon_shift_enemy(board,Enemycannon,n,m);
	ans2.insert(ans2.end(), valid_mv1.begin(), valid_mv1.end());
	ans1.insert(ans1.end(), ans2.begin(), ans2.end());
	//cerr<<ans1.size()<<endl;
	return ans1;
}

vector<moves> valid_moves(int **board, pair<int,int> *Soldier,int n,int m,vector<pair<pair<int,int>,int> > cannon){
	pair<vector<moves>,vector<moves> > valid_mv;
	vector<moves> ans1;
	vector<moves> ans2;
	vector<moves> valid_mv1;
	for(int i=0;i<cannon.size();i++){
		valid_mv=bullet_fires(board,cannon[i],n,m);
		ans1.insert(ans1.end(), valid_mv.first.begin(), valid_mv.first.end());
		ans2.insert(ans2.end(), valid_mv.second.begin(), valid_mv.second.end());
	}
	for (int i=1;i<=3*(m/2);i++){
		if(Soldier[i].first!=-1){
			valid_mv = valid_moves_for_soldier(board,Soldier[i],n,m);
			ans1.insert(ans1.end(), valid_mv.first.begin(), valid_mv.first.end());
			ans2.insert(ans2.end(), valid_mv.second.begin(), valid_mv.second.end());
		}
	}
	valid_mv1=cannon_shift(board,cannon,n,m);
	ans2.insert(ans2.end(), valid_mv1.begin(), valid_mv1.end());
	ans1.insert(ans1.end(), ans2.begin(), ans2.end());
	return ans1;
}

////can be optimised by combining or checking just for 4 townhalls/////////////
int enemy_soldier_shoots(int **board, vector<pair<pair<int,int>,int> > Enemycannon, int n, int m){
	int count = 0;
	int x,y,head;
	
	for (int i=0;i<Enemycannon.size();i++){
		x = Enemycannon[i].first.first;
		y = Enemycannon[i].first.second;
		head = Enemycannon[i].second;
		if(head==1){
			if(board[x+2][y]==1)
				count++;
			if(x+3<m && board[x+3][y]==1)
				count++;
		}
		if(head==-1){
			if(board[x-2][y]==1)
				count++;
			if(x-3>=0 && board[x-3][y]==1)
				count++;
		}
		if(head==2){
			if(board[x][y+2]==1)
				count++;
			if(y+3<n && board[x][y+3]==1)
				count++;
		}
		if(head==-2){
			if(board[x][y-2]==1)
				count++;
			if(y-3>=0 && board[x][y-3]==1)
				count++;
		}
		if(head==3){
			if(board[x+2][y+2]==1)
				count++;
			if(y+3<n && x+3<m && board[x+3][y+3]==1)
				count++;
		}
		if(head==-3){
			if(board[x-2][y-2]==1)
				count++;
			if(y-3>=0 && x-3>=0 && board[x-3][y-3]==1)
				count++;
		}
		if(head==4){
			if(board[x+2][y-2]==1)
				count++;
			if(y-3>=0 && x+3<m && board[x+3][y-3]==1)
				count++;
		}
		if(head==-4){
			if(board[x-2][y+2]==1)
				count++;
			if(x-3>=0 && y+3<n && board[x-3][y+3]==1)
				count++;
		}
	}	
	return count;
}

int soldier_shoots(int **board, vector<pair<pair<int,int>,int> > cannon, int n, int m){
	int count = 0;
	int x,y,head;
	
	for (int i=0;i<cannon.size();i++){
		x = cannon[i].first.first;
		y = cannon[i].first.second;
		head = cannon[i].second;
		if(head==1){
			if(board[x+2][y]==-1)
				count++;
			if(x+3<m && board[x+3][y]==-1)
				count++;
		}
		if(head==-1){
			if(board[x-2][y]==-1)
				count++;
			if(x-3>=0 && board[x-3][y]==-1)
				count++;
		}
		if(head==2){
			if(board[x][y+2]==-1)
				count++;
			if(y+3<n && board[x][y+3]==-1)
				count++;
		}
		if(head==-2){
			if(board[x][y-2]==-1)
				count++;
			if(y-3>=0 && board[x][y-3]==-1)
				count++;
		}
		if(head==3){
			if(board[x+2][y+2]==-1)
				count++;
			if(y+3<n && x+3<m && board[x+3][y+3]==-1)
				count++;
		}
		if(head==-3){
			if(board[x-2][y-2]==-1)
				count++;
			if(y-3>=0 && x-3>=0 && board[x-3][y-3]==-1)
				count++;
		}
		if(head==4){
			if(board[x+2][y-2]==-1)
				count++;
			if(y-3>=0 && x+3<m && board[x+3][y-3]==-1)
				count++;
		}
		if(head==-4){
			if(board[x-2][y+2]==-1)
				count++;
			if(x-3>=0 && y+3<n && board[x-3][y+3]==-1)
				count++;
		}
	}	
	return count;
}

int enemy_townhall_shoots(int **board, vector<pair<pair<int,int>,int> > Enemycannon, int n, int m){
	int count = 0;
	int x,y,head;
	
	for (int i=0;i<Enemycannon.size();i++){
		x = Enemycannon[i].first.first;
		y = Enemycannon[i].first.second;
		head = Enemycannon[i].second;
		if(head==1){
			if(board[x+2][y]==2)
				count++;
			if(x+3<m && board[x+3][y]==2)
				count++;
		}
		if(head==-1){
			if(board[x-2][y]==2)
				count++;
			if(x-3>=0 && board[x-3][y]==2)
				count++;
		}
		if(head==2){
			if(board[x][y+2]==2)
				count++;
			if(y+3<n && board[x][y+3]==2)
				count++;
		}
		if(head==-2){
			if(board[x][y-2]==2)
				count++;
			if(y-3>=0 && board[x][y-3]==2)
				count++;
		}
		if(head==3){
			if(board[x+2][y+2]==2)
				count++;
			if(y+3<n && x+3<m && board[x+3][y+3]==2)
				count++;
		}
		if(head==-3){
			if(board[x-2][y-2]==2)
				count++;
			if(y-3>=0 && x-3>=0 && board[x-3][y-3]==2)
				count++;
		}
		if(head==4){
			if(board[x+2][y-2]==2)
				count++;
			if(y-3>=0 && x+3<m && board[x+3][y-3]==2)
				count++;
		}
		if(head==-4){
			if(board[x-2][y+2]==2)
				count++;
			if(x-3>=0 && y+3<n && board[x-3][y+3]==2)
				count++;
		}
	}	
	return count;
}

int townhall_shoots(int **board, vector<pair<pair<int,int>,int> > cannon, int n, int m){
	int count = 0;
	int x,y,head;
	
	for (int i=0;i<cannon.size();i++){
		x = cannon[i].first.first;
		y = cannon[i].first.second;
		head = cannon[i].second;
		if(head==1){
			if(board[x+2][y]==-2)
				count++;
			if(x+3<m && board[x+3][y]==-2)
				count++;
		}
		if(head==-1){
			if(board[x-2][y]==-2)
				count++;
			if(x-3>=0 && board[x-3][y]==-2)
				count++;
		}
		if(head==2){
			if(board[x][y+2]==-2)
				count++;
			if(y+3<n && board[x][y+3]==-2)
				count++;
		}
		if(head==-2){
			if(board[x][y-2]==-2)
				count++;
			if(y-3>=0 && board[x][y-3]==-2)
				count++;
		}
		if(head==3){
			if(board[x+2][y+2]==-2)
				count++;
			if(y+3<n && x+3<m && board[x+3][y+3]==-2)
				count++;
		}
		if(head==-3){
			if(board[x-2][y-2]==-2)
				count++;
			if(y-3>=0 && x-3>=0 && board[x-3][y-3]==-2)
				count++;
		}
		if(head==4){
			if(board[x+2][y-2]==-2)
				count++;
			if(y-3>=0 && x+3<m && board[x+3][y-3]==-2)
				count++;
		}
		if(head==-4){
			if(board[x-2][y+2]==-2)
				count++;
			if(x-3>=0 && y+3<n && board[x-3][y+3]==-2)
				count++;
		}
	}	
	return count;
}
/////////////////////////////////////////////////////////////////////////////////

int player_support_enemy(int **board, pair<int,int> *a, int n, int m, vector<pair<pair<int,int>,int> > Enemycannon){
	int count=0;
	int x,y,head;
	// set<pair<int, int>> positions;
	for(int i=1;i<=(3*(m/2))+1;i++){
		if(a[i].first!=-1 && a[i].second<=5){
			if(a[i].second-1>=0 && board[a[i].first][a[i].second-1]==-1){
				count++;
			}
			if(a[i].second-1>=0 && a[i].first+1<m && board[a[i].first+1][a[i].second-1]==-1){
				count++;
			}
			if(a[i].second-1>=0 && a[i].first-1>=0 && board[a[i].first-1][a[i].second-1]==-1){
				count++;
			}
			if(a[i].first+1<m && board[a[i].first+1][a[i].second]==-1){
				count++;
			}
			if(a[i].first-1>=0 && board[a[i].first-1][a[i].second]==-1){
				count++;
			}
		}
	}
	for(int i=0;i<Enemycannon.size();i++){
		x=Enemycannon[i].first.first;
		y=Enemycannon[i].first.second;
		head=Enemycannon[i].second;
		if(head==1){
			if(x+2<m && board[x+2][y]==-1 && y<=n-4)
				count++;
			if(x+3<m && board[x+3][y]==-1 && y<=n-4)
				count++;
		}else if(head==-1){
			if(x-2>=0 && board[x-2][y]==-1 && y<=n-4)
				count++;
			if(x-3>=0 && board[x-3][y]==-1 && y<=n-4)
				count++;
		}else if(head==2){
			if(y+2<n && board[x][y+2]==-1 && y+2<=n-4)
				count++;
			if(y+3<n && board[x][y+3]==-1 && y+3<=n-4)
				count++;
		}else if(head==-2){
			if(y-2>=0 && board[x][y-2]==-1 && y-2<=n-4)
				count++;
			if(y-3>=0 && board[x][y-3]==-1 && y-3<=n-4)
				count++;
		}else if(head==3){
			if(x+2<m && y-2>=0 && board[x+2][y-2]==-1 && y-2<=n-4)
				count++;
			if(x+3<m && y-3>=0 && board[x+3][y-3]==-1 && y-3<=n-4)
				count++;
		}else if(head==-3){
			if(x-2>=0 && y+2<n && board[x-2][y+2]==-1 && y+2<=n-4)
				count++;
			if(x-3>=0 && y+3<n && board[x-3][y+3]==-1 && y+3<=n-4)
				count++;
		}else if(head==4){
			if(y+2<n && x+2<m && board[x+2][y+2]==-1 && y+2<=n-4)
				count++;
			if(y+3<n && x+3<m && board[x+3][y+3]==-1 && y+3<=n-4)
				count++;
		}else if(head==-4){
			if(y-2>=0 && x-2>=0 && board[x-2][y-2]==-1 && y-2<=n-4)
				count++;
			if(y-3>=0 && x-3>=0 && board[x-3][y-3]==-1 && y-3<=n-4)
				count++;
		}
	}
	return count;
}

int player_support(int **board, pair<int,int> *a, int n, int m, vector<pair<pair<int,int>,int> > cannon){
	int count=0;
	int x,y,head;
	// set<pair<int, int>> positions;
	for(int i=1;i<=(3*(m/2))+1;i++){
		if(a[i].first!=-1 && a[i].second>=2){
			if(a[i].second+1<n && board[a[i].first][a[i].second+1]==1){
				count++;
			}
			if(a[i].second+1<n && a[i].first+1<m && board[a[i].first+1][a[i].second+1]==1){
				count++;
			}
			if(a[i].second+1<n && a[i].first-1>=0 && board[a[i].first-1][a[i].second+1]==1){
				count++;
			}
			if(a[i].first+1<m && board[a[i].first+1][a[i].second]==1){
				count++;
			}
			// cerr<<a[i].first<<" "<<endl;
			// cerr<<a[i].second<<endl;
			// cerr<<board[a[i].first-1][a[i].second]<<endl;
			if(a[i].first-1>=0 && board[a[i].first-1][a[i].second]==1){
				count++;
			}
		}
	}
	for(int i=0;i<cannon.size();i++){
		x=cannon[i].first.first;
		y=cannon[i].first.second;
		head=cannon[i].second;
		if(head==1){
			if(x+2<m && board[x+2][y]==1 && y>=3)
				count++;
			if(x+3<m && board[x+3][y]==1 && y>=3)
				count++;
		}else if(head==-1){
			if(x-2>=0 && board[x-2][y]==1 && y>=3)
				count++;
			if(x-3>=0 && board[x-3][y]==1 && y>=3)
				count++;
		}else if(head==2){
			if(y+2<n && board[x][y+2]==1 && y+2>=3)
				count++;
			if(y+3<n && board[x][y+3]==1 && y+3>=3)
				count++;
		}else if(head==-2){
			if(y-2>=0 && board[x][y-2]==1 && y-2>=3)
				count++;
			if(y-3>=0 && board[x][y-3]==1 && y-3>=3)
				count++;
		}else if(head==3){
			if(x+2<m && y-2>=0 && board[x+2][y-2]==1 && y-2>=3)
				count++;
			if(x+3<m && y-3>=0 && board[x+3][y-3]==1 && y-3>=3)
				count++;
		}else if(head==-3){
			if(x-2>=0 && y+2<n && board[x-2][y+2]==1 && y+2>=3)
				count++;
			if(x-3>=0 && y+3<n && board[x-3][y+3]==1 && y+3>=3)
				count++;
		}else if(head==4){
			if(y+2<n && x+2<m && board[x+2][y+2]==1 && y+2>=3)
				count++;
			if(y+3<n && x+3<m && board[x+3][y+3]==1 && y+3>=3)
				count++;
		}else if(head==-4){
			if(y-2>=0 && x-2>=0 && board[x-2][y-2]==1 && y-2>=3)
				count++;
			if(y-3>=0 && x-3>=0 && board[x-3][y-3]==1 && y-3>=3)
				count++;
		}
	}
	return count;
}

int eval(bool townhall_kill, int **board,int n,int m, pair<int,int> *Soldier,pair<int,int> *EnemySoldier, pair<int,int> *Townhall, pair<int,int> *EnemyTownhall, vector<pair<pair<int,int>,int> > cannon, vector<pair<pair<int,int>,int> > Enemycannon){
	// if(townhall_kill)
	// 	return INT_MAX-20;

	int weight_soldier = 25;
	int weight_soldier_fire = 15;
	int weight_cannon = 20;
	int weight_townhall = 100;
	int weight_townhall_fire = 65;
	if(EnemyTownhall[0].first==3 || Townhall[0].first==3){
		//cerr<<"here"<<endl;
		weight_townhall = 1000;
	}
	// if(EnemyTownhall[0].first==4 && Townhall[0].first==4){
	// 	weight_townhall_fire=60;
	// }

	
	if(Townhall[0].first<=2){
		return INT_MIN+10;
	}
	else if(EnemyTownhall[0].first<=2){
		return INT_MAX-10;
	}

	int ss = soldier_shoots(board, cannon, n, m);
	int ess = enemy_soldier_shoots(board, Enemycannon, n, m);
	int ts = townhall_shoots(board, cannon, n, m);
	int ets = enemy_townhall_shoots(board, Enemycannon, n, m);

	return weight_soldier*(Soldier[0].first-EnemySoldier[0].first)+weight_soldier_fire*(ss - ess)+ weight_cannon*(cannon.size()-Enemycannon.size()) + weight_townhall*(Townhall[0].first-EnemyTownhall[0].first)+ weight_townhall_fire*(ts-ets);
}

// int cutoff = 4;
int cutoff(int player_num){
	return 4;
	// if(player_num<6)
	// 	return 8;
	// if(player_num<8)
	// 	return 7;
	// if(player_num==12)
	// 	return 3;
	// if(player_num>10)
	// 	return 4;
	// if(player_num==10)
	// 	return 5;
	// return 6;
}

int eval_enemy(bool townhall_kill, int **board,int n,int m, pair<int,int> *Soldier,pair<int,int> *EnemySoldier, pair<int,int> *Townhall, pair<int,int> *EnemyTownhall, vector<pair<pair<int,int>,int> > cannon, vector<pair<pair<int,int>,int> > Enemycannon){
	// if(townhall_kill)
	// 	return INT_MAX-20;

	int weight_soldier = 25;
	int weight_soldier_fire = 15;
	int weight_cannon = 20;
	int weight_townhall = 100;
	int weight_townhall_fire = 65;	

	if(EnemyTownhall[0].first==3 || Townhall[0].first==3){
		//cerr<<"here"<<endl;
		weight_townhall = 1000;
	}
	if(EnemyTownhall[0].first<=2){
		return INT_MIN+10;
	}
	else if(Townhall[0].first<=2){
		return INT_MAX-10;
	}

	int ss = soldier_shoots(board, cannon, n, m);
	int ess = enemy_soldier_shoots(board, Enemycannon, n, m);
	int ts = townhall_shoots(board, cannon, n, m);
	int ets = enemy_townhall_shoots(board, Enemycannon, n, m);

	return -(weight_soldier*(Soldier[0].first-EnemySoldier[0].first)+weight_soldier_fire*(ss - ess)+ weight_cannon*(cannon.size()-Enemycannon.size()) + weight_townhall*(Townhall[0].first-EnemyTownhall[0].first)+ weight_townhall_fire*(ts-ets));
}

bool global_bool_enemy;
pair<moves,int> global_move_enemy;
int global_level_enemy;
bool global_bool_enemy_bad;
pair<moves,int> global_move_enemy_bad;
int global_level_enemy_bad;
int utility_enemy(bool flag,bool townhall_kill,pair<int,int> *Townhall, pair<int,int> *EnemyTownhall,int n,int m,int level){
	if(Townhall[0].first<=(m/2)-2 && EnemyTownhall[0].first>(m/2)-2){
		global_bool_enemy=true;
		global_level_enemy=level;
		return 5000;
	}else if(Townhall[0].first>(m/2)-2 && EnemyTownhall[0].first<=(m/2)-2){
		global_bool_enemy_bad=true;
		global_level_enemy_bad=level;
		return -5000;
	}else if(flag){
		return 1000;
	}
	return -1000;

	// if(townhall_kill && EnemyTownhall[0].first==4){
	// 	return 1000;
	// }
	// if(Townhall[0].first<=2 && EnemyTownhall[0].first==4){
	// 	return INT_MAX-10;
	// }
	// if(Townhall[0].first<=2 && EnemyTownhall[0].first==3){
	// 	return INT_MAX-20;
	// }
	// if(EnemyTownhall[0].first<=2 && Townhall[0].first==4){
	// 	return INT_MIN+10;
	// }
	// if(EnemyTownhall[0].first<=2 && Townhall[0].first==3){
	// 	return INT_MIN+20;
	// }
	// if(flag)
	// 	return INT_MAX-20;
	// else
	// 	return INT_MAX-20;
}

pair<moves, int> min_value_enemy(bool warn, moves saved,int player_num,bool townhall_kill,int **board, int n, int m, int alpha, int beta, moves ms, int min_val, pair<int,int> *Soldier, pair<int,int> *EnemySoldier, pair<int,int> *Townhall, pair<int,int> *EnemyTownhall, vector<pair<pair<int,int>,int> > cannon, vector<pair<pair<int,int>,int> > Enemycannon){
	min_val++;
	if(global_bool_enemy && min_val>=global_level_enemy){
		return (global_move_enemy);
	}
	if(min_val>cutoff(player_num)){
		int x = eval_enemy(townhall_kill,board,n,m, Soldier, EnemySoldier, Townhall, EnemyTownhall, cannon, Enemycannon);
		return make_pair(ms, x);
	}
	vector<moves> v = valid_moves(board,Soldier,n,m,cannon);
	if (v.size()==0 || EnemyTownhall[0].first<=(m/2)-2 ||  Townhall[0].first<=(m/2)-2){
		int val=utility_enemy(true,townhall_kill,Townhall,EnemyTownhall,n,m,min_val);
		if(global_bool_enemy){
			global_move_enemy=make_pair(ms,val);
			return global_move_enemy;
		}
		return make_pair(ms, val);
	}

	pair<moves, int> min_child;
	min_child.second=INT_MAX;
	pair<int, int> temp_soldier[(3*(m/2))+1];
	pair<int, int> temp_enemy_soldier[(3*(m/2))+1];
	pair<int, int> temp_townhall[(m/2)+1];
	pair<int, int> temp_enemy_townhall[(m/2)+1];
	int **a;
	a=new int*[n];
	for(int i=0;i<n;i++){
		a[i]=new int[m];
	}
	for(int i=0;i<v.size();i++){
		for(int l=0;l<=3*(m/2);l++)
			temp_soldier[l]=Soldier[l];
		for(int l=0;l<=3*(m/2);l++)
			temp_enemy_soldier[l]=EnemySoldier[l];
		for(int l=0;l<=(m/2);l++)
			temp_townhall[l]=Townhall[l];
		for(int l=0;l<=(m/2);l++)
			temp_enemy_townhall[l]=EnemyTownhall[l];

		for(int l=0;l<n;l++){
			for(int j=0;j<m;j++){
				a[l][j]=board[l][j];
			}
		}
		do_move(v[i], a, temp_soldier, temp_enemy_soldier, temp_townhall, temp_enemy_townhall);
		vector<pair<pair<int,int>,int> > new_cannon = update_cannons(a, temp_soldier, n, m);
		vector<pair<pair<int,int>,int> > new_enemy_cannon = update_enemy_cannons(a, temp_enemy_soldier, n, m);

		if(EnemyTownhall[0].first-temp_enemy_townhall[0].first>0)
			townhall_kill=true;
		
		pair<moves, int> child = max_value_enemy(warn,saved,player_num,townhall_kill,a, n, m, alpha, beta, v[i], min_val, temp_soldier, temp_enemy_soldier, temp_townhall, temp_enemy_townhall, new_cannon, new_enemy_cannon);

		if(global_bool_enemy){
			global_level_enemy=12;
		}

		if(min_child.second>child.second){
			min_child.second=child.second;
			min_child.first=v[i];
		}
		if(min_child.second<=alpha){
			return min_child;
		}
		beta = std::min(beta, min_child.second);
	}
	return min_child;
}

pair<moves, int> max_value_enemy(bool warn, moves saved,int player_num,bool townhall_kill,int **board, int n, int m, int alpha, int beta, moves ms, int max_val, pair<int,int> *Soldier, pair<int,int> *EnemySoldier, pair<int,int> *Townhall, pair<int,int> *EnemyTownhall, vector<pair<pair<int,int>,int> > cannon, vector<pair<pair<int,int>,int> > Enemycannon){
	max_val++;
	if(global_bool_enemy_bad && max_val>=global_level_enemy_bad){
		return (global_move_enemy_bad);
	}
	if(max_val>cutoff(player_num))
		return make_pair(ms, eval_enemy(townhall_kill,board,n,m, Soldier, EnemySoldier, Townhall, EnemyTownhall, cannon, Enemycannon));

	vector<moves> v = valid_moves_enemy(board,EnemySoldier,n,m,Enemycannon);
	// if(warn && std::find(v.begin(), v.end(), saved)!=v.end()){
	// 	cerr<<"moves repeating"<<endl;
	// 	v.erase(std::remove(v.begin(), v.end(), saved), v.end());
	// }
	if (v.size()==0 || EnemyTownhall[0].first<=(m/2)-2 ||  Townhall[0].first<=(m/2)-2){
		int val=utility_enemy(false,townhall_kill,Townhall,EnemyTownhall,n,m,max_val);
		if(global_bool_enemy_bad){
			global_move_enemy_bad=make_pair(ms,val);
			return global_move_enemy_bad;
		}
		return make_pair(ms, val);
		//return make_pair(ms, utility_enemy(false,townhall_kill,Townhall, EnemyTownhall,n,m,max_val));
	}

	pair<moves, int> max_child;
	max_child.second=INT_MIN;
	pair<int, int> temp_soldier[(3*(m/2))+1];
	pair<int, int> temp_enemy_soldier[(3*(m/2))+1];
	pair<int, int> temp_townhall[(m/2)+1];
	pair<int, int> temp_enemy_townhall[(m/2)+1];
	int **a;
	a=new int*[n];
	for(int i=0;i<n;i++){
		a[i]=new int[m];
	}
	for(int i=0;i<v.size();i++){
		if(warn && v[i].a==saved.a && v[i].b==saved.b && v[i].c==saved.c && v[i].d==saved.d && v[i].e==saved.e && v[i].f==saved.f){
			// cerr<<"same move found"<<endl;
			continue;
		}
		//copy(begin(Soldier), end(Soldier), begin(temp_soldier));

		for(int l=0;l<=3*(m/2);l++)
			temp_soldier[l]=Soldier[l];
		for(int l=0;l<=3*(m/2);l++)
			temp_enemy_soldier[l]=EnemySoldier[l];
		for(int l=0;l<=(m/2);l++)
			temp_townhall[l]=Townhall[l];
		for(int l=0;l<=(m/2);l++)
			temp_enemy_townhall[l]=EnemyTownhall[l];

		for(int l=0;l<n;l++){
			for(int j=0;j<m;j++){
				a[l][j]=board[l][j];
			}
		}

		do_move_enemy(v[i], a, temp_soldier, temp_enemy_soldier, temp_townhall, temp_enemy_townhall);

		vector<pair<pair<int,int>,int> > new_cannon = update_cannons(a, temp_soldier, n, m);
		
		vector<pair<pair<int,int>,int> > new_enemy_cannon = update_enemy_cannons(a, temp_enemy_soldier, n, m);

		
		if(temp_townhall[0].first<=2){
			return make_pair(v[i], INT_MIN+2);
		}
		
		pair<moves, int> child = min_value_enemy(warn,saved,player_num,townhall_kill,a, n, m, alpha, beta, v[i], max_val, temp_soldier, temp_enemy_soldier, temp_townhall, temp_enemy_townhall, new_cannon, new_enemy_cannon);

		if(global_bool_enemy_bad){
			global_level_enemy_bad=12;
		}

		if(max_child.second<child.second){
			max_child.second=child.second;
			max_child.first=v[i];
		}
		
		if(max_child.second>=beta)
			return max_child;
		alpha = std::max(alpha, max_child.second);
	}
	return max_child;
}

moves alpha_beta_enemy(bool warn, moves saved,int **board, int n, int m, pair<int,int> *Soldier,pair<int,int> *EnemySoldier, pair<int,int> *Townhall, pair<int,int> *EnemyTownhall, vector<pair<pair<int,int>,int> > cannon, vector<pair<pair<int,int>,int> > Enemycannon){
	cerr<<"depth "<<cutoff(Soldier[0].first)<<endl;
	cerr<<"saved move"<<saved.a<<saved.b<<saved.c<<saved.d<<saved.e<<saved.f<<" "<<warn<<endl;
	moves temp;
	temp.a='S'; temp.b=0; temp.c=0; temp.d='M'; temp.e=0; temp.f=0;
	global_bool_enemy=false;
	global_level_enemy=0;
	global_bool_enemy_bad=false;
	global_level_enemy_bad=0;
	pair<moves, int> ans = max_value_enemy(warn,saved,Soldier[0].first,false, board, n, m, INT_MIN, INT_MAX, temp, -1, Soldier, EnemySoldier, Townhall, EnemyTownhall, cannon, Enemycannon);
	// cerr<<"ans.second= "<<ans.second<<endl;
	return ans.first;
}
bool global_bool;
pair<moves,int> global_move;
int global_level;
bool global_bool_bad;
pair<moves,int> global_move_bad;
int global_level_bad;
int utility(bool flag,bool townhall_kill,pair<int,int> *Townhall, pair<int,int> *EnemyTownhall,int n,int m,int level){

	if(Townhall[0].first>(m/2)-2 && EnemyTownhall[0].first<=(m/2)-2){
		global_bool=true;
		global_level=level;
		return 5000;
	}else if(Townhall[0].first<=(m/2)-2 && EnemyTownhall[0].first>(m/2)-2){
		global_bool_bad=true;
		global_level_bad=level;
		return -5000;
	}else if(flag){
		return 1000;
	}
	return -1000;
	// if(townhall_kill && Townhall[0].first==4){
	// 	return INT_MAX-50;
	// }
	// if(Townhall[0].first<=2 && EnemyTownhall[0].first==4){
	// 	return INT_MIN+10;
	// }
	// if(Townhall[0].first<=2 && EnemyTownhall[0].first==3){
	// 	return INT_MIN+20;
	// }
	// if(EnemyTownhall[0].first<=2 && Townhall[0].first==4){
	// 	return INT_MAX-10;
	// }
	// if(EnemyTownhall[0].first<=2 && Townhall[0].first==3){
	// 	return INT_MAX-20;
	// }
	// if(flag)
	// 	return INT_MAX-50;
	// else
	// 	return INT_MAX-50;
}

pair<moves, int> min_value(bool warn, moves saved,int player_num,bool townhall_kill, int **board, int n, int m, int alpha, int beta, moves ms, int min_val, pair<int,int> *Soldier, pair<int,int> *EnemySoldier, pair<int,int> *Townhall, pair<int,int> *EnemyTownhall, vector<pair<pair<int,int>,int> > cannon, vector<pair<pair<int,int>,int> > Enemycannon){
	min_val++;
	if(global_bool && min_val>=global_level){
		return global_move;
	}
	if(min_val>cutoff(player_num))
		return make_pair(ms, eval(townhall_kill,board,n,m, Soldier, EnemySoldier, Townhall, EnemyTownhall, cannon, Enemycannon));
	vector<moves> v = valid_moves_enemy(board,EnemySoldier,n,m,Enemycannon);
	if (v.size()==0 || EnemyTownhall[0].first<=(m/2)-2 ||  Townhall[0].first<=(m/2)-2){
		int val=utility(true,townhall_kill,Townhall,EnemyTownhall,n,m,min_val);
		if(global_bool){
			global_move=make_pair(ms,val);
			return global_move;
		}
		return make_pair(ms, val);
		// return make_pair(ms, utility(true,townhall_kill,Townhall,EnemyTownhall));
	}

	pair<moves, int> min_child;
	min_child.second=INT_MAX;
	pair<int, int> temp_soldier[(3*(m/2))+1];
	pair<int, int> temp_enemy_soldier[(3*(m/2))+1];
	pair<int, int> temp_townhall[(m/2)+1];
	pair<int, int> temp_enemy_townhall[(m/2)+1];
	int **a;
	a=new int*[n];
	for(int i=0;i<n;i++){
		a[i]=new int[m];
	}
	for(int i=0;i<v.size();i++){
		for(int l=0;l<=3*(m/2);l++)
			temp_soldier[l]=Soldier[l];
		for(int l=0;l<=3*(m/2);l++)
			temp_enemy_soldier[l]=EnemySoldier[l];
		for(int l=0;l<=(m/2);l++)
			temp_townhall[l]=Townhall[l];
		for(int l=0;l<=(m/2);l++)
			temp_enemy_townhall[l]=EnemyTownhall[l];

		for(int l=0;l<n;l++){
			for(int j=0;j<m;j++){
				a[l][j]=board[l][j];
			}
		}
		do_move_enemy(v[i], a, temp_soldier, temp_enemy_soldier, temp_townhall, temp_enemy_townhall);
		vector<pair<pair<int,int>,int> > new_cannon = update_cannons(a, temp_soldier, n, m);
		
		vector<pair<pair<int,int>,int> > new_enemy_cannon = update_enemy_cannons(a, temp_enemy_soldier, n, m);

		if(Townhall[0].first-temp_townhall[0].first>0)
			townhall_kill=true;
		
		pair<moves, int> child = max_value(warn,saved,player_num,townhall_kill, a, n, m, alpha, beta, v[i], min_val, temp_soldier, temp_enemy_soldier, temp_townhall, temp_enemy_townhall, new_cannon, new_enemy_cannon);

		if(global_bool){
			global_level=12;
		}

		if(min_child.second>child.second){
			min_child.second=child.second;
			min_child.first=v[i];
		}
		if(min_child.second<=alpha){
			return min_child;
		}
		beta = std::min(beta, min_child.second);
	}
	return min_child;
}

pair<moves, int> max_value(bool warn, moves saved,int player_num,bool townhall_kill, int **board, int n, int m, int alpha, int beta, moves ms, int max_val, pair<int,int> *Soldier, pair<int,int> *EnemySoldier, pair<int,int> *Townhall, pair<int,int> *EnemyTownhall, vector<pair<pair<int,int>,int> > cannon, vector<pair<pair<int,int>,int> > Enemycannon){
	max_val++;
	if(global_bool_bad && max_val>=global_level_bad){
		return global_move_bad;
	}
	if(max_val>cutoff(player_num))
		return make_pair(ms, eval(townhall_kill,board,n,m, Soldier, EnemySoldier, Townhall, EnemyTownhall, cannon, Enemycannon));
	
	vector<moves> v = valid_moves(board,Soldier,n,m,cannon);
	// if(warn && std::find(v.begin(), v.end(), saved)!=v.end()){
	// 	cerr<<"moves repeating"<<endl;
	// 	v.erase(std::remove(v.begin(), v.end(), saved), v.end());
	// }

	if (v.size()==0 || EnemyTownhall[0].first<=(m/2)-2 || Townhall[0].first<=(m/2)-2){
		int val=utility(false,townhall_kill,Townhall,EnemyTownhall,n,m,max_val);
		if(global_bool_bad){
			global_move_bad=make_pair(ms,val);
			return global_move_bad;
		}
		return make_pair(ms, val);
		//return make_pair(ms, utility(false,townhall_kill,Townhall, EnemyTownhall,n,m,max_val));
	}

	pair<moves, int> max_child;
	max_child.second=INT_MIN;
	pair<int, int> temp_soldier[(3*(m/2))+1];
	pair<int, int> temp_enemy_soldier[(3*(m/2))+1];
	pair<int, int> temp_townhall[(m/2)+1];
	pair<int, int> temp_enemy_townhall[(m/2)+1];
	int **a;
	a=new int*[n];
	for(int i=0;i<n;i++){
		a[i]=new int[m];
	}
	for(int i=0;i<v.size();i++){
		if(warn && v[i].a==saved.a && v[i].b==saved.b && v[i].c==saved.c && v[i].d==saved.d && v[i].e==saved.e && v[i].f==saved.f){
			// cerr<<"same move found"<<endl;
			continue;
		}
		//copy(begin(Soldier), end(Soldier), begin(temp_soldier));

		for(int l=0;l<=3*(m/2);l++)
			temp_soldier[l]=Soldier[l];
		for(int l=0;l<=3*(m/2);l++)
			temp_enemy_soldier[l]=EnemySoldier[l];
		for(int l=0;l<=(m/2);l++)
			temp_townhall[l]=Townhall[l];
		for(int l=0;l<=(m/2);l++)
			temp_enemy_townhall[l]=EnemyTownhall[l];

		for(int l=0;l<n;l++){
			for(int j=0;j<m;j++){
				a[l][j]=board[l][j];
			}
		}
		do_move(v[i], a, temp_soldier, temp_enemy_soldier, temp_townhall, temp_enemy_townhall);

		vector<pair<pair<int,int>,int> > new_cannon = update_cannons(a, temp_soldier, n, m);
		
		vector<pair<pair<int,int>,int> > new_enemy_cannon = update_enemy_cannons(a, temp_enemy_soldier, n, m);
		
		pair<moves, int> child = min_value(warn,saved,player_num,townhall_kill, a, n, m, alpha, beta, v[i], max_val, temp_soldier, temp_enemy_soldier, temp_townhall, temp_enemy_townhall, new_cannon, new_enemy_cannon);

		if(global_bool_bad){
			global_level_bad=12;
		}

		if(max_child.second<child.second){
			max_child.second=child.second;
			max_child.first=v[i];
		}
		
		if(max_child.second>=beta){
			
			return max_child;
		}
		alpha = std::max(alpha, max_child.second);
	}
	return max_child;
}

moves alpha_beta(bool warn, moves saved,int **board, int n, int m, pair<int,int> *Soldier,pair<int,int> *EnemySoldier, pair<int,int> *Townhall, pair<int,int> *EnemyTownhall, vector<pair<pair<int,int>,int> > cannon, vector<pair<pair<int,int>,int> > Enemycannon){
	cerr<<"depth "<<cutoff(Soldier[0].first)<<endl;
	cerr<<"saved move"<<saved.a<<saved.b<<saved.c<<saved.d<<saved.e<<saved.f<<" "<<warn<<endl;
	moves temp;
	temp.a='S'; temp.b=0; temp.c=0; temp.d='M'; temp.e=0; temp.f=0;
	global_bool=false;
	global_level=0;
	global_bool_bad=false;
	global_level_bad=0;
	pair<moves, int> ans = max_value(warn,saved,Soldier[0].first,false, board, n, m, INT_MIN, INT_MAX, temp, -1, Soldier, EnemySoldier, Townhall, EnemyTownhall, cannon, Enemycannon);
	cerr<<ans.second<<endl;
	return ans.first;
}

int main(int argc, char* argv[]){
	int id,n,m ,t;
	cin>>id>>n>>m>>t;
	int **board;
	vector<moves> v;
	moves M;
	board=new int*[n];
	srand(unsigned(time(0)));
	int r;
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
		Soldier[i+1]= (make_pair((2*(i/3))+1,i%3));
		if(i%3==0){
			Cannon.push_back(make_pair((make_pair((2*(i/3))+1,(i%3) )),2));
		}
		board[(2*(i/3))+1][i%3]=1;
	}

	pair<int,int> *EnemySoldier=new pair<int,int>[3*(m/2)+1];
	EnemySoldier[0]=make_pair(3*(m/2),0);
	for(int i=0;i<3*(m/2);i++){
		EnemySoldier[i+1]= (make_pair(2*(i/3),n-1-i%3));
		if(i%3==0){
			Cannon.push_back(make_pair((make_pair((2*(i/3)),n-1-(i%3) )),-2));
		}
		board[2*(i/3)][n-1-(i%3)]=-1;
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
		EnemyTownhall[i+1]= (make_pair((2*i)+1,n-1));
		board[(2*i)+1][n-1]=-2;
	}
	moves save_move[2]; int it=0; bool warn=false;
	save_move[0].a='S';save_move[0].b=0;save_move[0].c=0;save_move[0].d='M';save_move[0].e=0;save_move[0].f=0;
	save_move[0].a='S';save_move[0].b=11;save_move[0].c=11;save_move[0].d='M';save_move[0].e=11;save_move[0].f=11;
	if(id==1){
		while(true){
			M=alpha_beta_enemy(warn,save_move[0],board,n,m,Soldier,EnemySoldier,Townhall,EnemyTownhall,Cannon,EnemyCannon);
			save_move[it].a=M.a;save_move[it].b=M.b;save_move[it].c=M.c;save_move[it].d=M.d;save_move[it].e=M.e;save_move[it].f=M.f;
			it++;
		
			if(save_move[0].a==save_move[1].a && save_move[0].b==save_move[1].b && save_move[0].c==save_move[1].c && save_move[0].d==save_move[1].d && save_move[0].e==save_move[1].e && save_move[0].f==save_move[1].f)
				warn = true;
			else
				warn = false;
			if(it==2)
				it=0;
			
			cout<<M.a<<" "<<M.b<<" "<<M.c<<" "<<M.d<<" "<<M.e<<" "<<M.f<<endl;
			do_move_enemy(M,board,Soldier,EnemySoldier,Townhall,EnemyTownhall);
			Cannon =update_cannons(board,Soldier,n,m);
			EnemyCannon=update_enemy_cannons(board,EnemySoldier,n,m);
			cin>>M.a>>M.b>>M.c>>M.d>>M.e>>M.f;
			do_move(M,board,Soldier,EnemySoldier,Townhall,EnemyTownhall); 
			Cannon =update_cannons(board,Soldier,n,m);
			EnemyCannon=update_enemy_cannons(board,EnemySoldier,n,m);
		}
	}
	else{
		while(true){
			cin>>M.a>>M.b>>M.c>>M.d>>M.e>>M.f;
			do_move_enemy(M,board,Soldier,EnemySoldier,Townhall,EnemyTownhall); 
			Cannon =update_cannons(board,Soldier,n,m);
			EnemyCannon=update_enemy_cannons(board,EnemySoldier,n,m);
			M=alpha_beta(warn,save_move[0],board,n,m,Soldier,EnemySoldier,Townhall,EnemyTownhall,Cannon,EnemyCannon);
			save_move[it].a=M.a;save_move[it].b=M.b;save_move[it].c=M.c;save_move[it].d=M.d;save_move[it].e=M.e;save_move[it].f=M.f;
			it++;
			if(save_move[0].a==save_move[1].a && save_move[0].b==save_move[1].b && save_move[0].c==save_move[1].c && save_move[0].d==save_move[1].d && save_move[0].e==save_move[1].e && save_move[0].f==save_move[1].f)
				warn = true;
			else
				warn = false;
			if(it==2)
				it=0;
			save_move[it].a=M.a;save_move[it].b=M.b;save_move[it].c=M.c;save_move[it].d=M.d;save_move[it].e=M.e;save_move[it].f=M.f;
			cout<<M.a<<" "<<M.b<<" "<<M.c<<" "<<M.d<<" "<<M.e<<" "<<M.f<<endl;
			do_move(M,board,Soldier,EnemySoldier,Townhall,EnemyTownhall);
			Cannon =update_cannons(board,Soldier,n,m);
			EnemyCannon=update_enemy_cannons(board,EnemySoldier,n,m);
		}
	}
	//valid_moves(board,Soldier,n,m,Cannon);
	return 0;
}