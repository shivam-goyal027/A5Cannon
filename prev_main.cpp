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
#include "Soldier.h"
#include "EnemySoldier.h"
#include "Townhall.h"
#include<map>
#include<string.h>
using namespace std;

char **board;
map<pair<int,int>,Soldier*> smap;
map<pair<int,int>,EnemySoldier*> emap;
map<pair<int,int>,Townhall*> tmap;
map<pair<int,int>,Townhall*> etmap;
int n,m,t,id; //id==1 is black=>move first and bottom of board
vector<Soldier> vs;
vector<EnemySoldier> ves;
vector<Townhall> vth;
struct moveStruct
{
	char a[6]={};
};

pair<moveStruct, int> max_value(int alpha, int beta, moveStruct ms, int xl);


vector<moveStruct> cannon_shift(Soldier* s, int x, int y){
	moveStruct vm;
	vector<moveStruct> ans;
	vector<int> k = s->getHead();
	for(int j=0;j<((s->getHead()).size());j++){
		if(s->getHead()[j]==1 && x-3>=0){
			if(board[x-3][y]=='E'){
		    	vm.a[0]='S';vm.a[1]=(char)(x+'0');vm.a[2]=(char)(y+'0');vm.a[3]='M';vm.a[4]=(char)(x-3+'0');vm.a[5]=(char)(y+'0');ans.push_back(vm);
		    }
		}
		else if(s->getHead()[j]==-1 && x+3<m){
			if(board[x+3][y]=='E'){
		    	vm.a[0]='S';vm.a[1]=(char)(x+'0');vm.a[2]=(char)(y+'0');vm.a[3]='M';vm.a[4]=(char)(x+3+'0');vm.a[5]=(char)(y+'0');ans.push_back(vm);
		    }
		}
		else if(s->getHead()[j]==2 && y-3>=0){
			if(board[x][y-3]=='E'){
		    	vm.a[0]='S';vm.a[1]=(char)(x+'0');vm.a[2]=(char)(y+'0');vm.a[3]='M';vm.a[4]=(char)(x+'0');vm.a[5]=(char)(y-3+'0');ans.push_back(vm);
		    }
		}
		else if(s->getHead()[j]==-2 && y+3<n){
			if(board[x][y+3]=='E'){
		    	vm.a[0]='S';vm.a[1]=(char)(x+'0');vm.a[2]=(char)(y+'0');vm.a[3]='M';vm.a[4]=(char)(x+'0');vm.a[5]=(char)(y+3+'0');ans.push_back(vm);
		    }
		}
		else if(s->getHead()[j]==3 && x-3>=0 && y-3>=0){
			if(board[x-3][y-3]=='E'){
		    	vm.a[0]='S';vm.a[1]=(char)(x+'0');vm.a[2]=(char)(y+'0');vm.a[3]='M';vm.a[4]=(char)(x-3+'0');vm.a[5]=(char)(y-3+'0');ans.push_back(vm);
		    }
		}
		else if(s->getHead()[j]==-3 && x+3<m && y+3<n){
			if(board[x+3][y+3]=='E'){
		    	vm.a[0]='S';vm.a[1]=(char)(x+'0');vm.a[2]=(char)(y+'0');vm.a[3]='M';vm.a[4]=(char)(x+3+'0');vm.a[5]=(char)(y+3+'0');ans.push_back(vm);
		    }
		}
		else if(s->getHead()[j]==4 && x-3>=0 && y+3<n){
			if(board[x-3][y+3]=='E'){
		    	vm.a[0]='S';vm.a[1]=(char)(x+'0');vm.a[2]=(char)(y+'0');vm.a[3]='M';vm.a[4]=(char)(x-3+'0');vm.a[5]=(char)(y+3+'0');ans.push_back(vm);
		    }
		}
		else if(s->getHead()[j]==-4 && x+3<m && y-3>=0){
			if(board[x+3][y-3]=='E'){
		    	vm.a[0]='S';vm.a[1]=(char)(x+'0');vm.a[2]=(char)(y+'0');vm.a[3]='M';vm.a[4]=(char)(x+3+'0');vm.a[5]=(char)(y-3+'0');ans.push_back(vm);
		    }
		}
	}
	return ans;
}

bool adjacent(int x, int y){
	if(y+1<n){
		if(board[x][y+1]=='X'||board[x][y+1]=='O')
			return true;
		if(x+1<m){
			if(board[x+1][y+1]=='X'||board[x+1][y+1]=='O')
				return true;
			if(board[x+1][y]=='X'||board[x+1][y]=='O')
				return true;
		}
		if(x-1>=0){
			if(board[x-1][y+1]=='X'||board[x-1][y+1]=='O')
				return true;
			if(board[x-1][y]=='X'||board[x-1][y]=='O')
				return true;
		}
		return false;
	}
	return false;
}

vector<moveStruct> bullet_fires(Soldier* s, int x, int y){ 
	moveStruct vm;
	vector<moveStruct> ret;
	for(int j=0;j<((s->getHead()).size());j++){
		if(s->getHead()[j]==1){
			if(x+1<m){
				if(board[x+1][y]=='E'){
					if(x+2<m && board[x+2][y]!='S' && board[x+2][y]!='T') {vm.a[0]='S';vm.a[1]=(char)(x+'0');vm.a[2]=(char)(y+'0');vm.a[3]='B';vm.a[4]=(char)(x+2+'0');vm.a[5]=(char)(y+'0'); ret.push_back(vm);}
					if(x+3<m && board[x+3][y]!='S' && board[x+3][y]!='T') {vm.a[0]='S';vm.a[1]=(char)(x+'0');vm.a[2]=(char)(y+'0');vm.a[3]='B';vm.a[4]=(char)(x+3+'0');vm.a[5]=(char)(y+'0'); ret.push_back(vm);}
				}
			}
		}
		else if(s->getHead()[j]==-1){
			if(x-1>=0){
				if(board[x-1][y]=='E'){
					if(x-2>=0 && board[x-2][y]!='S' && board[x-2][y]!='T') {vm.a[0]='S';vm.a[1]=(char)(x+'0');vm.a[2]=(char)(y+'0');vm.a[3]='B';vm.a[4]=(char)(x-2+'0');vm.a[5]=(char)(y+'0'); ret.push_back(vm);}
					if(x-3>=0 && board[x-3][y]!='S' && board[x-3][y]!='T') {vm.a[0]='S';vm.a[1]=(char)(x+'0');vm.a[2]=(char)(y+'0');vm.a[3]='B';vm.a[4]=(char)(x-3+'0');vm.a[5]=(char)(y+'0'); ret.push_back(vm);}
				}
			}
			
		}
		else if(s->getHead()[j]==2){
			if(y+1<n){
				if(board[x][y+1]=='E'){
					if(y+2<n && board[x][y+2]!='S' && board[x][y+2]!='T') {vm.a[0]='S';vm.a[1]=(char)(x+'0');vm.a[2]=(char)(y+'0');vm.a[3]='B';vm.a[4]=(char)(x+'0');vm.a[5]=(char)(y+2+'0'); ret.push_back(vm);}
					if(y+3<n && board[x][y+3]!='S' && board[x][y+3]!='T') {vm.a[0]='S';vm.a[1]=(char)(x+'0');vm.a[2]=(char)(y+'0');vm.a[3]='B';vm.a[4]=(char)(x+'0');vm.a[5]=(char)(y+3+'0'); ret.push_back(vm);}
				}
			}
			
		}
		else if(s->getHead()[j]==-2){
			if(y-1>=0){
				if(board[x][y-1]=='E'){
					if(y-2>=0 && board[x][y-2]!='S' && board[x][y-2]!='T') {vm.a[0]='S';vm.a[1]=(char)(x+'0');vm.a[2]=(char)(y+'0');vm.a[3]='B';vm.a[4]=(char)(x+'0');vm.a[5]=(char)(y-2+'0'); ret.push_back(vm);}
					if(y-3>=0 && board[x][y-3]!='S' && board[x][y-3]!='T') {vm.a[0]='S';vm.a[1]=(char)(x+'0');vm.a[2]=(char)(y+'0');vm.a[3]='B';vm.a[4]=(char)(x+'0');vm.a[5]=(char)(y-3+'0'); ret.push_back(vm);}
				}
			}
		}
		else if(s->getHead()[j]==3){
			if(x+1<m && y+1<n){
				if(board[x+1][y+1]=='E'){
					if(y+2<n && x+2<m && board[x+2][y+2]!='S' && board[x+2][y+2]!='T') {vm.a[0]='S';vm.a[1]=(char)(x+'0');vm.a[2]=(char)(y+'0');vm.a[3]='B';vm.a[4]=(char)(x+2+'0');vm.a[5]=(char)(y+2+'0'); ret.push_back(vm);}
					if(y+3<n && x+3<m && board[x+3][y+3]!='S' && board[x+3][y+3]!='T') {vm.a[0]='S';vm.a[1]=(char)(x+'0');vm.a[2]=(char)(y+'0');vm.a[3]='B';vm.a[4]=(char)(x+3+'0');vm.a[5]=(char)(y+3+'0'); ret.push_back(vm);}
				}
			}
		}
		else if(s->getHead()[j]==-3){
			if(x-1>=0 && y-1>=0){
				if(board[x-1][y-1]=='E'){
					if(y-2>=0 && x-2>=0 && board[x-2][y-2]!='S' && board[x-2][y-2]!='T') {vm.a[0]='S';vm.a[1]=(char)(x+'0');vm.a[2]=(char)(y+'0');vm.a[3]='B';vm.a[4]=(char)(x-2+'0');vm.a[5]=(char)(y-2+'0'); ret.push_back(vm);}
					if(y-3>=0 && x-3>=0 && board[x-3][y-3]!='S' && board[x-3][y-3]!='T') {vm.a[0]='S';vm.a[1]=(char)(x+'0');vm.a[2]=(char)(y+'0');vm.a[3]='B';vm.a[4]=(char)(x-3+'0');vm.a[5]=(char)(y-3+'0'); ret.push_back(vm);}
				}
			}
		}
		else if(s->getHead()[j]==4){
			if(x+1<m && y-1>=0){
				if(board[x+1][y-1]=='E'){
					if(y-2>=0 && x+2<m && board[x+2][y-2]!='S' && board[x+2][y-2]!='T') {vm.a[0]='S';vm.a[1]=(char)(x+'0');vm.a[2]=(char)(y+'0');vm.a[3]='B';vm.a[4]=(char)(x+2+'0');vm.a[5]=(char)(y-2+'0'); ret.push_back(vm);}
					if(y-3>=0 && x+3<m && board[x+3][y-3]!='S' && board[x+3][y-3]!='T') {vm.a[0]='S';vm.a[1]=(char)(x+'0');vm.a[2]=(char)(y+'0');vm.a[3]='B';vm.a[4]=(char)(x+3+'0');vm.a[5]=(char)(y-3+'0'); ret.push_back(vm);}
				}
			}
		}
		else if(s->getHead()[j]==-4){
			if(x-1>=0 && y+1<n){
				if(board[x-1][y+1]=='E'){
					if(y+2<n && x-2>=0 && board[x-2][y+2]!='S' && board[x-2][y+2]!='T') {vm.a[0]='S';vm.a[1]=(char)(x+'0');vm.a[2]=(char)(y+'0');vm.a[3]='B';vm.a[4]=(char)(x-2+'0');vm.a[5]=(char)(y+2+'0'); ret.push_back(vm);}
					if(y+3<n && x-3>=0 && board[x-3][y+3]!='S' && board[x-3][y+3]!='T') {vm.a[0]='S';vm.a[1]=(char)(x+'0');vm.a[2]=(char)(y+'0');vm.a[3]='B';vm.a[4]=(char)(x-3+'0');vm.a[5]=(char)(y+3+'0'); ret.push_back(vm);}
				}
			}
		}
	}
	return ret;
}

vector<moveStruct> valid_move_for_soldier(pair<int, int> pos, Soldier* s){
	moveStruct vm;
	vector<moveStruct> ans;
	int x = pos.first;
	int y = pos.second;
	//Normal moves
    if(x-1>=0 && y+1<n){
    	if(board[x-1][y+1]!='T' && board[x-1][y+1]!='S'){
    		vm.a[0]='S';vm.a[1]=(char)(x+'0');vm.a[2]=(char)(y+'0');vm.a[3]='M';vm.a[4]=(char)(x-1+'0');vm.a[5]=(char)(y+1+'0');ans.push_back(vm);
    	}
    }
    if(x>=0 && y+1<n){
    	if(board[x][y+1]!='T' && board[x][y+1]!='S'){
	    	vm.a[0]='S';vm.a[1]=(char)(x+'0');vm.a[2]=(char)(y+'0');vm.a[3]='M';vm.a[4]=(char)(x+'0');vm.a[5]=(char)(y+1+'0');ans.push_back(vm);
	    }
    }
    if(x+1<m && y+1<n){
    	if(board[x+1][y+1]!='T' && board[x+1][y+1]!='S'){
    		vm.a[0]='S';vm.a[1]=(char)(x+'0');vm.a[2]=(char)(y+'0');vm.a[3]='M';vm.a[4]=(char)(x+1+'0');vm.a[5]=(char)(y+1+'0');ans.push_back(vm);
    	}
    }
    //Sideways
    if(x-1>=0 && y<n){
    	if(board[x-1][y]=='X'||board[x-1][y]=='O'){
    		vm.a[0]='S';vm.a[1]=(char)(x+'0');vm.a[2]=(char)(y+'0');vm.a[3]='M';vm.a[4]=(char)(x-1+'0');vm.a[5]=(char)(y+'0');ans.push_back(vm);
    	}
    }
    if(x+1<m && y<n){
    	if(board[x+1][y]=='X'||board[x+1][y]=='O'){
    		vm.a[0]='S';vm.a[1]=(char)(x+'0');vm.a[2]=(char)(y+'0');vm.a[3]='M';vm.a[4]=(char)(x+1+'0');vm.a[5]=(char)(y+'0');ans.push_back(vm);
    	}
    }
    //Retreat
    if(adjacent(x, y)){
    	if(y-2>=0){
    		if(x-2>=0){
    			if(board[x-2][y-2]!='T' && board[x-2][y-2]!='S'){
    				vm.a[0]='S';vm.a[1]=(char)(x+'0');vm.a[2]=(char)(y+'0');vm.a[3]='M';vm.a[4]=(char)(x-2+'0');vm.a[5]=(char)(y-2+'0');ans.push_back(vm);
    			}
    		}
	    	if(x>=0){
	    		if(board[x][y-2]!='T' && board[x][y-2]!='S'){
	    			vm.a[0]='S';vm.a[1]=(char)(x+'0');vm.a[2]=(char)(y+'0');vm.a[3]='M';vm.a[4]=(char)(x+'0');vm.a[5]=(char)(y-2+'0');ans.push_back(vm);
	    		}
	    	}
	    	if(x+2<m){
	    		if(board[x+2][y-2]!='T' && board[x+2][y-2]!='S'){
	    			vm.a[0]='S';vm.a[1]=(char)(x+'0');vm.a[2]=(char)(y+'0');vm.a[3]='M';vm.a[4]=(char)(x+2+'0');vm.a[5]=(char)(y-2+'0');ans.push_back(vm);
	    		}
	    	}
    	}   	
    }
    vector<moveStruct> cannon_moves=cannon_shift(s,x,y);
    ans.insert(ans.end(), cannon_moves.begin(), cannon_moves.end());

    vector<moveStruct> fire = bullet_fires(s, x, y);
    ans.insert(ans.end(), fire.begin(), fire.end());

    return ans;
}
vector<moveStruct> valid_moves(){
	vector<moveStruct> valid_mv;
	vector<moveStruct> ans;
	map<pair<int,int>,Soldier*>::iterator it;

	for (it=smap.begin();it!=smap.end();it++){
		valid_mv = valid_move_for_soldier(it->first, it->second);
		ans.insert(ans.end(), valid_mv.begin(), valid_mv.end());
	}
	return ans;
}

void do_move(moveStruct visit){
	if(visit.a[3]=='M'){
		EnemySoldier* es= emap[(make_pair((int)visit.a[1]-48,(int)visit.a[2]-48))];
		// cout<<es->getPosy()<<endl;
		es->setPosx((int)(visit.a[4]-48));
		// cout<<111<<endl;
		es->setPosy((int)(visit.a[5]-48));

		emap.erase((make_pair((int)(visit.a[1])-48,(int)(visit.a[2])-48)));
		// cout<<2<<endl;
		emap.insert({(make_pair((int)(visit.a[4])-48,(int)(visit.a[5])-48)),es});
		// cout<<3<<endl;

		if(smap.find(make_pair((int)(visit.a[4])-48,(int)(visit.a[5])-48))!=smap.end()){
			//cout<<4<<endl;
			Soldier* s=smap[(make_pair((int)(visit.a[4])-48,(int)(visit.a[5])-48))];
			s->setIsAlive(false);
			smap.erase((make_pair((int)(visit.a[4])-48,(int)(visit.a[5])-48)));
		}
		else if(tmap.find(make_pair((int)(visit.a[4])-48,(int)(visit.a[5])-48))!=tmap.end()){
			Townhall* th=tmap[(make_pair((int)(visit.a[4])-48,(int)(visit.a[5])-48))];
			th->setIsAlive(false);
			tmap.erase((make_pair((int)(visit.a[4])-48,(int)(visit.a[5])-48)));
		}
		board[(int)(visit.a[1])-48][(int)(visit.a[2])-48]='E';
		board[(int)(visit.a[4])-48][(int)(visit.a[5])-48]='O';
		//update valid visit.as
	}
	else{
		if(smap.find(make_pair((int)(visit.a[4])-48,(int)(visit.a[5])-48))!=smap.end()){
			Soldier* s=smap[(make_pair((int)(visit.a[4])-48,(int)(visit.a[5])-48))];
			s->setIsAlive(false);
			smap.erase((make_pair((int)(visit.a[4])-48,(int)(visit.a[5])-48)));
		}
		else if(tmap.find(make_pair((int)(visit.a[4])-48,(int)(visit.a[5])-48))!=tmap.end()){
			Townhall* th=tmap[(make_pair((int)(visit.a[4])-48,(int)(visit.a[5])-48))];
			th->setIsAlive(false);
			tmap.erase((make_pair((int)(visit.a[4])-48,(int)(visit.a[5])-48)));
		}
		board[(int)visit.a[4]-48][(int)visit.a[5]-48]='E';
		//update valid moves
	}
}
void do_move2(moveStruct visit){
	if(visit.a[3]=='M'){
		Soldier* es=smap[(make_pair((int)visit.a[1]-48,(int)visit.a[2]-48))];

		es->setPosx((int)(visit.a[4])-48);
		es->setPosy((int)(visit.a[5])-48);

		smap.erase((make_pair((int)(visit.a[1])-48,(int)(visit.a[2])-48)));
		smap.insert({(make_pair((int)(visit.a[4])-48,(int)(visit.a[5])-48)),es});

		if(emap.find(make_pair((int)(visit.a[4])-48,(int)(visit.a[5])-48))!=emap.end()){
			EnemySoldier* s=emap[(make_pair((int)(visit.a[4])-48,(int)(visit.a[5])-48))];
			s->setIsAlive(false);
			emap.erase((make_pair((int)(visit.a[4])-48,(int)(visit.a[5])-48)));
		}
		else if(etmap.find(make_pair((int)(visit.a[4])-48,(int)(visit.a[5])-48))!=etmap.end()){
			Townhall* th=etmap[(make_pair((int)(visit.a[4])-48,(int)(visit.a[5])-48))];
			th->setIsAlive(false);
			etmap.erase((make_pair((int)(visit.a[4])-48,(int)(visit.a[5])-48)));
		}
		board[(int)(visit.a[1])-48][(int)(visit.a[2])-48]='E';
		board[(int)(visit.a[4])-48][(int)(visit.a[5])-48]='S';
		//update valid visit.as
	}
	else{
		if(emap.find(make_pair((int)(visit.a[4])-48,(int)(visit.a[5])-48))!=emap.end()){
			EnemySoldier* s=emap[(make_pair((int)(visit.a[4])-48,(int)(visit.a[5])-48))];
			s->setIsAlive(false);
			emap.erase((make_pair((int)(visit.a[4])-48,(int)(visit.a[5])-48)));
		}
		else if(etmap.find(make_pair((int)(visit.a[4])-48,(int)(visit.a[5])-48))!=etmap.end()){
			Townhall* th=etmap[(make_pair((int)(visit.a[4])-48,(int)(visit.a[5])-48))];
			th->setIsAlive(false);
			etmap.erase((make_pair((int)(visit.a[4])-48,(int)(visit.a[5])-48)));
		}
		board[(int)visit.a[4]-48][(int)visit.a[5]-48]='E';
		//update valid moves
	}
}
void update_heads(){
	map<pair<int,int>,Soldier*>::iterator it;
	int x;
	int y;
	
	for (it=smap.begin();it!=smap.end();it++){
		vector<int> v;
		x=it->first.first;
		y=it->first.second;
		if(x-2>=0){
			if(board[x-1][y]=='S' && board[x-2][y]=='S' && x+1<m-1){
				if(board[x+1][y]=='E')
				v.push_back(1);
			}
		}
		if(x+2<m){
			if(board[x+1][y]=='S' && board[x+2][y]=='S' && x-1>0){
				if(board[x-1][y]=='E')
				v.push_back(-1);
			}
		}
		if(y-2>=0){
			if(board[x][y-1]=='S' && board[x][y-2]=='S' && y+1<n-1){
				if(board[x][y+1]=='E')
				v.push_back(2);
			}
		}
		if(y+2<n){
			if(board[x][y+1]=='S' && board[x][y+2]=='S' && y-1>0){
				if(board[x][y-1]=='E')
				v.push_back(-2);
			}
		}
		if(x-2>=0 && y-2>=0){
			if(board[x-1][y-1]=='S' && board[x-2][y-2]=='S' && x+1<m-1 && y+1<n-1){
				if(board[x+1][y+1]=='E')
				v.push_back(3);
			}
		}
		if(x+2<m && y+2<n){
			if(board[x+1][y+1]=='S' && board[x+2][y+2]=='S' && x-1>0 && y-1>0){
				if(board[x-1][y-1]=='E')
				v.push_back(-3);
			}
		}
		if(x-2>=0 && y+2<n){
			if(board[x-1][y+1]=='S' && board[x-2][y+2]=='S' && x+1<m-1 && y-1>0){
				if(board[x+1][y-1]=='E')
				v.push_back(4);
			}
		}
		if(x+2<m && y-2>=0){
			if(board[x+1][y-1]=='S' && board[x+2][y-2]=='S' && x-1>0 && y+1<n-1){
				if(board[x-1][y+1]=='E')
				v.push_back(-4);
			}
		}
		it->second->setHead(v);
	}

	map<pair<int,int>,EnemySoldier*>::iterator itr;
	for (itr=emap.begin();itr!=emap.end();itr++){
		vector<int> v;
		x=itr->first.first;
		y=itr->first.second;
		if(x-2>=0){
			if(board[x-1][y]=='O' && board[x-2][y]=='O'&& x+1<m-1){
				if(board[x+1][y]=='E')
				v.push_back(1);
			}
		}
		if(x+2<m){
			if(board[x+1][y]=='O' && board[x+2][y]=='O'&& x-1>0){
				if(board[x-1][y]=='E')
				v.push_back(-1);
			}
		}
		if(y-2>=0){
			if(board[x][y-1]=='O' && board[x][y-2]=='O'&& y+1<n-1){
				if(board[x][y+1]=='E')
				v.push_back(2);
			}
		}
		if(y+2<n){
			if(board[x][y+1]=='O' && board[x][y+2]=='O'&& y-1>0){
				if(board[x][y-1]=='E')
				v.push_back(-2);
			}
		}
		if(x-2>=0 && y-2>=0){
			if(board[x-1][y-1]=='O' && board[x-2][y-2]=='O'&& x+1<m-1 && y+1<n-1){
				if(board[x+1][y+1]=='E')
				v.push_back(3);
			}
		}
		if(x+2<m && y+2<m){
			if(board[x+1][y+1]=='O' && board[x+2][y+2]=='O'&& x-1>0 && y-1>0){
				if(board[x-1][y-1]=='E')
				v.push_back(-3);
			}
		}
		if(x-2>=0 && y+2<n){
			if(board[x-1][y+1]=='O' && board[x-2][y+2]=='O' && x+1<m-1 && y-1>0){
				if(board[x+1][y-1]=='E')
				v.push_back(4);
			}
		}
		if(x+2<m && y-2>=0){
			if(board[x+1][y-1]=='O' && board[x+2][y-2]=='O' && x-1>0 && y+1<n-1){
				if(board[x-1][y+1]=='E')
				v.push_back(-4);
			}
		}
		itr->second->setHead(v);
	}
	return;
}

vector<moveStruct> cannon_shift_enemy(EnemySoldier* s, int x, int y, char** arr){
	moveStruct vm;
	vector<moveStruct> ans;
	vector<int> k = s->getHead();
	for(int j=0;j<((s->getHead()).size());j++){
		if(s->getHead()[j]==1 && x-3>=0){
			if(arr[x-3][y]=='E'){
		    	vm.a[0]='S';vm.a[1]=(char)(x+'0');vm.a[2]=(char)(y+'0');vm.a[3]='M';vm.a[4]=(char)(x-3+'0');vm.a[5]=(char)(y+'0');ans.push_back(vm);
		    }
		}
		else if(s->getHead()[j]==-1 && x+3<m){
			if(arr[x+3][y]=='E'){
		    	vm.a[0]='S';vm.a[1]=(char)(x+'0');vm.a[2]=(char)(y+'0');vm.a[3]='M';vm.a[4]=(char)(x+3+'0');vm.a[5]=(char)(y+'0');ans.push_back(vm);
		    }
		}
		else if(s->getHead()[j]==2 && y-3>=0){
			if(arr[x][y-3]=='E'){
		    	vm.a[0]='S';vm.a[1]=(char)(x+'0');vm.a[2]=(char)(y+'0');vm.a[3]='M';vm.a[4]=(char)(x+'0');vm.a[5]=(char)(y-3+'0');ans.push_back(vm);
		    }
		}
		else if(s->getHead()[j]==-2 && y+3<n){
			if(arr[x][y+3]=='E'){
		    	vm.a[0]='S';vm.a[1]=(char)(x+'0');vm.a[2]=(char)(y+'0');vm.a[3]='M';vm.a[4]=(char)(x+'0');vm.a[5]=(char)(y+3+'0');ans.push_back(vm);
		    }
		}
		else if(s->getHead()[j]==3 && x-3>=0 && y-3>=0){
			if(arr[x-3][y-3]=='E'){
		    	vm.a[0]='S';vm.a[1]=(char)(x+'0');vm.a[2]=(char)(y+'0');vm.a[3]='M';vm.a[4]=(char)(x-3+'0');vm.a[5]=(char)(y-3+'0');ans.push_back(vm);
		    }
		}
		else if(s->getHead()[j]==-3 && x+3<m && y+3<n){
			if(arr[x+3][y+3]=='E'){
		    	vm.a[0]='S';vm.a[1]=(char)(x+'0');vm.a[2]=(char)(y+'0');vm.a[3]='M';vm.a[4]=(char)(x+3+'0');vm.a[5]=(char)(y+3+'0');ans.push_back(vm);
		    }
		}
		else if(s->getHead()[j]==4 && x-3>=0 && y+3<n){
			if(arr[x-3][y+3]=='E'){
		    	vm.a[0]='S';vm.a[1]=(char)(x+'0');vm.a[2]=(char)(y+'0');vm.a[3]='M';vm.a[4]=(char)(x-3+'0');vm.a[5]=(char)(y+3+'0');ans.push_back(vm);
		    }
		}
		else if(s->getHead()[j]==-4 && x+3<m && y-3>=0){
			if(arr[x+3][y-3]=='E'){
		    	vm.a[0]='S';vm.a[1]=(char)(x+'0');vm.a[2]=(char)(y+'0');vm.a[3]='M';vm.a[4]=(char)(x+3+'0');vm.a[5]=(char)(y-3+'0');ans.push_back(vm);
		    }
		}
	}
	return ans;
}

bool adjacent_enemy(int x, int y, char** arr){
	if(y-1>=0){
		if(arr[x][y-1]=='T'||arr[x][y-1]=='S')
			return true;
		if(x+1<m){
			if(arr[x+1][y-1]=='T'||arr[x+1][y-1]=='S')
				return true;
			if(arr[x+1][y]=='T'||arr[x+1][y]=='S')
				return true;
		}
		if(x-1>=0){
			if(arr[x-1][y-1]=='T'||arr[x-1][y-1]=='S')
				return true;
			if(arr[x-1][y]=='T'||arr[x-1][y]=='S')
				return true;
		}
		return false;
	}
	return false;
}

vector<moveStruct> bullet_fires_enemy(EnemySoldier* s, int x, int y, char** arr){ 
	moveStruct vm;
	vector<moveStruct> ret;
	for(int j=0;j<((s->getHead()).size());j++){
		if(s->getHead()[j]==1){
			if(x+1<m){
				if(arr[x+1][y]=='E'){
					if(x+2<m && arr[x+2][y]!='O' && arr[x+2][y]!='X') {vm.a[0]='S';vm.a[1]=(char)(x+'0');vm.a[2]=(char)(y+'0');vm.a[3]='B';vm.a[4]=(char)(x+2+'0');vm.a[5]=(char)(y+'0'); ret.push_back(vm);}
					if(x+3<m && arr[x+3][y]!='O' && arr[x+3][y]!='X') {vm.a[0]='S';vm.a[1]=(char)(x+'0');vm.a[2]=(char)(y+'0');vm.a[3]='B';vm.a[4]=(char)(x+3+'0');vm.a[5]=(char)(y+'0'); ret.push_back(vm);}
				}
			}
		}
		else if(s->getHead()[j]==-1){
			if(x-1>=0){
				if(arr[x-1][y]=='E'){
					if(x-2>=0 && arr[x-2][y]!='O' && arr[x-2][y]!='X') {vm.a[0]='S';vm.a[1]=(char)(x+'0');vm.a[2]=(char)(y+'0');vm.a[3]='B';vm.a[4]=(char)(x-2+'0');vm.a[5]=(char)(y+'0'); ret.push_back(vm);}
					if(x-3>=0 && arr[x-3][y]!='O' && arr[x-3][y]!='X') {vm.a[0]='S';vm.a[1]=(char)(x+'0');vm.a[2]=(char)(y+'0');vm.a[3]='B';vm.a[4]=(char)(x-3+'0');vm.a[5]=(char)(y+'0'); ret.push_back(vm);}
				}
			}
			
		}
		else if(s->getHead()[j]==2){
			if(y+1<n){
				if(arr[x][y+1]=='E'){
					if(y+2<n && arr[x][y+2]!='O' && arr[x][y+2]!='X') {vm.a[0]='S';vm.a[1]=(char)(x+'0');vm.a[2]=(char)(y+'0');vm.a[3]='B';vm.a[4]=(char)(x+'0');vm.a[5]=(char)(y+2+'0'); ret.push_back(vm);}
					if(y+3<n && arr[x][y+3]!='O' && arr[x][y+3]!='X') {vm.a[0]='S';vm.a[1]=(char)(x+'0');vm.a[2]=(char)(y+'0');vm.a[3]='B';vm.a[4]=(char)(x+'0');vm.a[5]=(char)(y+3+'0'); ret.push_back(vm);}
				}
			}
			
		}
		else if(s->getHead()[j]==-2){
			if(y-1>=0){
				if(arr[x][y-1]=='E'){
					if(y-2>=0 && arr[x][y-2]!='O' && arr[x][y-2]!='X') {vm.a[0]='S';vm.a[1]=(char)(x+'0');vm.a[2]=(char)(y+'0');vm.a[3]='B';vm.a[4]=(char)(x+'0');vm.a[5]=(char)(y-2+'0'); ret.push_back(vm);}
					if(y-3>=0 && arr[x][y-3]!='O' && arr[x][y-3]!='X') {vm.a[0]='S';vm.a[1]=(char)(x+'0');vm.a[2]=(char)(y+'0');vm.a[3]='B';vm.a[4]=(char)(x+'0');vm.a[5]=(char)(y-3+'0'); ret.push_back(vm);}
				}
			}
		}
		else if(s->getHead()[j]==3){
			if(x+1<m && y+1<n){
				if(arr[x+1][y+1]=='E'){
					if(y+2<n && x+2<m && arr[x+2][y+2]!='O' && arr[x+2][y+2]!='X') {vm.a[0]='S';vm.a[1]=(char)(x+'0');vm.a[2]=(char)(y+'0');vm.a[3]='B';vm.a[4]=(char)(x+2+'0');vm.a[5]=(char)(y+2+'0'); ret.push_back(vm);}
					if(y+3<n && x+3<m && arr[x+3][y+3]!='O' && arr[x+3][y+3]!='X') {vm.a[0]='S';vm.a[1]=(char)(x+'0');vm.a[2]=(char)(y+'0');vm.a[3]='B';vm.a[4]=(char)(x+3+'0');vm.a[5]=(char)(y+3+'0'); ret.push_back(vm);}
				}
			}
		}
		else if(s->getHead()[j]==-3){
			if(x-1>=0 && y-1>=0){
				if(arr[x-1][y-1]=='E'){
					if(y-2>=0 && x-2>=0 && arr[x-2][y-2]!='O' && arr[x-2][y-2]!='X') {vm.a[0]='O';vm.a[1]=(char)(x+'0');vm.a[2]=(char)(y+'0');vm.a[3]='B';vm.a[4]=(char)(x-2+'0');vm.a[5]=(char)(y-2+'0'); ret.push_back(vm);}
					if(y-3>=0 && x-3>=0 && arr[x-3][y-3]!='O' && arr[x-3][y-3]!='X') {vm.a[0]='S';vm.a[1]=(char)(x+'0');vm.a[2]=(char)(y+'0');vm.a[3]='B';vm.a[4]=(char)(x-3+'0');vm.a[5]=(char)(y-3+'0'); ret.push_back(vm);}
				}
			}
		}
		else if(s->getHead()[j]==4){
			if(x+1<m && y-1>=0){
				if(arr[x+1][y-1]=='E'){
					if(y-2>=0 && x+2<m && arr[x+2][y-2]!='O' && arr[x+2][y-2]!='X') {vm.a[0]='S';vm.a[1]=(char)(x+'0');vm.a[2]=(char)(y+'0');vm.a[3]='B';vm.a[4]=(char)(x+2+'0');vm.a[5]=(char)(y-2+'0'); ret.push_back(vm);}
					if(y-3>=0 && x+3<m && arr[x+3][y-3]!='O' && arr[x+3][y-3]!='X') {vm.a[0]='S';vm.a[1]=(char)(x+'0');vm.a[2]=(char)(y+'0');vm.a[3]='B';vm.a[4]=(char)(x+3+'0');vm.a[5]=(char)(y-3+'0'); ret.push_back(vm);}
				}
			}
		}
		else if(s->getHead()[j]==-4){
			if(x-1>=0 && y+1<n){
				if(arr[x-1][y+1]=='E'){
					if(y+2<n && x-2>=0 && arr[x-2][y+2]!='O' && arr[x-2][y+2]!='X') {vm.a[0]='O';vm.a[1]=(char)(x+'0');vm.a[2]=(char)(y+'0');vm.a[3]='B';vm.a[4]=(char)(x-2+'0');vm.a[5]=(char)(y+2+'0'); ret.push_back(vm);}
					if(y+3<n && x-3>=0 && arr[x-3][y+3]!='O' && arr[x-3][y+3]!='X') {vm.a[0]='S';vm.a[1]=(char)(x+'0');vm.a[2]=(char)(y+'0');vm.a[3]='B';vm.a[4]=(char)(x-3+'0');vm.a[5]=(char)(y+3+'0'); ret.push_back(vm);}
				}
			}
		}
	}
	return ret;
}

vector<moveStruct> valid_move_for_enemy_soldier(pair<int, int> pos, EnemySoldier* s, char** arr){
	moveStruct vm;
	vector<moveStruct> ans;
	int x = pos.first;
	int y = pos.second;
	//Normal moves
    if(x-1>=0 && y-1>=0){
    	if(arr[x-1][y-1]!='O' && arr[x-1][y-1]!='X'){
    		vm.a[0]='S';vm.a[1]=(char)(x+'0');vm.a[2]=(char)(y+'0');vm.a[3]='M';vm.a[4]=(char)(x-1+'0');vm.a[5]=(char)(y-1+'0');ans.push_back(vm);
    	}
    }
    if(x>=0 && y-1>=0){
    	if(arr[x][y-1]!='O' && arr[x][y+1]!='X'){
	    	vm.a[0]='S';vm.a[1]=(char)(x+'0');vm.a[2]=(char)(y+'0');vm.a[3]='M';vm.a[4]=(char)(x+'0');vm.a[5]=(char)(y-1+'0');ans.push_back(vm);
	    }
    }
    if(x+1<m && y-1<n){
    	if(arr[x+1][y-1]!='O' && arr[x+1][y-1]!='X'){
    		vm.a[0]='S';vm.a[1]=(char)(x+'0');vm.a[2]=(char)(y+'0');vm.a[3]='M';vm.a[4]=(char)(x+1+'0');vm.a[5]=(char)(y-1+'0');ans.push_back(vm);
    	}
    }
    //Sideways
    if(x-1>=0 && y<n){
    	if(arr[x-1][y]=='S'||arr[x-1][y]=='T'){
    		vm.a[0]='S';vm.a[1]=(char)(x+'0');vm.a[2]=(char)(y+'0');vm.a[3]='M';vm.a[4]=(char)(x-1+'0');vm.a[5]=(char)(y+'0');ans.push_back(vm);
    	}
    }
    if(x+1<m && y<n){
    	if(arr[x+1][y]=='S'||arr[x+1][y]=='T'){
    		vm.a[0]='S';vm.a[1]=(char)(x+'0');vm.a[2]=(char)(y+'0');vm.a[3]='M';vm.a[4]=(char)(x+1+'0');vm.a[5]=(char)(y+'0');ans.push_back(vm);
    	}
    }
    //Retreat
    if(adjacent_enemy(x, y, arr)){
    	if(y+2<n){
    		if(x-2>=0){
    			if(arr[x-2][y+2]!='X' && arr[x-2][y+2]!='O'){
    				vm.a[0]='S';vm.a[1]=(char)(x+'0');vm.a[2]=(char)(y+'0');vm.a[3]='M';vm.a[4]=(char)(x-2+'0');vm.a[5]=(char)(y+2+'0');ans.push_back(vm);
    			}
    		}
	    	if(x>=0){
	    		if(arr[x][y+2]!='X' && arr[x][y+2]!='O'){
	    			vm.a[0]='S';vm.a[1]=(char)(x+'0');vm.a[2]=(char)(y+'0');vm.a[3]='M';vm.a[4]=(char)(x+'0');vm.a[5]=(char)(y+2+'0');ans.push_back(vm);
	    		}
	    	}
	    	if(x+2<m){
	    		if(arr[x+2][y+2]!='X' && arr[x+2][y+2]!='O'){
	    			vm.a[0]='S';vm.a[1]=(char)(x+'0');vm.a[2]=(char)(y+'0');vm.a[3]='M';vm.a[4]=(char)(x+2+'0');vm.a[5]=(char)(y+2+'0');ans.push_back(vm);
	    		}
	    	}
    	}   	
    }
    vector<moveStruct> cannon_moves=cannon_shift_enemy(s,x,y,arr);
    ans.insert(ans.end(), cannon_moves.begin(), cannon_moves.end());

    vector<moveStruct> fire = bullet_fires_enemy(s, x, y, arr);
    ans.insert(ans.end(), fire.begin(), fire.end());

    return ans;
}
vector<moveStruct> valid_moves_enemy(char** arr){
	vector<moveStruct> valid_mv;
	vector<moveStruct> ans;
	map<pair<int,int>,EnemySoldier*>::iterator it;

	for (it=emap.begin();it!=emap.end();it++){
		valid_mv = valid_move_for_enemy_soldier(it->first, it->second, arr);
		ans.insert(ans.end(), valid_mv.begin(), valid_mv.end());
	}
	return ans;
}

int utility(){
	if(tmap.size()<=2 && etmap.size()==4){
		return INT_MIN+10;
	}
	if(tmap.size()<=2 && etmap.size()==3){
		return INT_MIN+20;
	}
	if(etmap.size()<=2 && tmap.size()==4){
		return INT_MAX-10;
	}
	if(etmap.size()<=2 && tmap.size()==3){
		return INT_MAX-20;
	}
	else{
		return 0; //weigthForOurTownhall*(NumberofourTownhall) - weigthForTheirTownhall*(NumberoftheirTownhall);
	}
	return 0;
}
bool terminal(){
	vector<moveStruct> v = valid_moves();
	if(v.size()==0)
		return true;
	return false;
}
bool terminal_emeny(){
	vector<moveStruct> v = valid_moves_enemy(board);
	if(v.size()==0)
		return true;
	return false;
}
int townhall_shoots(){
	int count = 0;
	int x,y;
	map<pair<int,int>,Soldier*>::iterator it;
	
	for (it=smap.begin();it!=smap.end();it++){
		x=it->first.first;
		y=it->first.second;
		for(int i=0;i<((it->second)->getHead()).size();i++){
			if(((it->second)->getHead())[i]==1){
				if(board[x+2][y]=='X')
					count++;
				if(x+3<m && board[x+3][y]=='X')
					count++;
			}
			else if(((it->second)->getHead())[i]==-1){
				if(board[x-2][y]=='X')
					count++;
				if(x-3>=0 && board[x-3][y]=='X')
					count++;
			}
			else if(((it->second)->getHead())[i]==2){
				if(board[x][y+2]=='X')
					count++;
				if(y+3<n && board[x][y+3]=='X')
					count++;
			}
			else if(((it->second)->getHead())[i]==-2){
				if(board[x][y-2]=='X')
					count++;
				if(y-3>=0 && board[x][y-3]=='X')
					count++;
			}
			else if(((it->second)->getHead())[i]==3){
				if(board[x+2][y+2]=='X')
					count++;
				if(y+3<n && x+3<m && board[x+3][y+3]=='X')
					count++;
			}
			else if(((it->second)->getHead())[i]==-3){
				if(board[x-2][y-2]=='X')
					count++;
				if(y-3>=0 && x-3>=0 && board[x-3][y-3]=='X')
					count++;
			}
			else if(((it->second)->getHead())[i]==4){
				if(board[x+2][y-2]=='X')
					count++;
				if(y-3>=0 && x+3<m && board[x+3][y-3]=='X')
					count++;
			}
			else if(((it->second)->getHead())[i]==-4){
				if(board[x-2][y+2]=='X')
					count++;
				if(y+3<n && x-3>=0 && board[x-3][y+3]=='X')
					count++;
			}
		}
	}	
	return count;
}
int enemy_townhall_shoots(){
	int count = 0;
	int x,y;
	map<pair<int,int>,EnemySoldier*>::iterator it;
	
	for (it=emap.begin();it!=emap.end();it++){
		x=it->first.first;
		y=it->first.second;
		for(int i=0;i<((it->second)->getHead()).size();i++){
			if(((it->second)->getHead())[i]==1){
				if(board[x+2][y]=='T')
					count++;
				if(x+3<m && board[x+3][y]=='T')
					count++;
			}
			else if(((it->second)->getHead())[i]==-1){
				if(board[x-2][y]=='T')
					count++;
				if(x-3>=0 && board[x-3][y]=='T')
					count++;
			}
			else if(((it->second)->getHead())[i]==2){
				if(board[x][y+2]=='T')
					count++;
				if(y+3<n && board[x][y+3]=='T')
					count++;
			}
			else if(((it->second)->getHead())[i]==-2){
				if(board[x][y-2]=='T')
					count++;
				if(y-3>=0 && board[x][y-3]=='T')
					count++;
			}
			else if(((it->second)->getHead())[i]==3){
				if(board[x+2][y+2]=='T')
					count++;
				if(y+3<n && x+3<m && board[x+3][y+3]=='T')
					count++;
			}
			else if(((it->second)->getHead())[i]==-3){
				if(board[x-2][y-2]=='T')
					count++;
				if(y-3>=0 && x-3>=0 && board[x-3][y-3]=='T')
					count++;
			}
			else if(((it->second)->getHead())[i]==4){
				if(board[x+2][y-2]=='T')
					count++;
				if(y-3>=0 && x+3<m && board[x+3][y-3]=='T')
					count++;
			}
			else if(((it->second)->getHead())[i]==-4){
				if(board[x-2][y+2]=='T')
					count++;
				if(y+3<n && x-3>=0 && board[x-3][y+3]=='T')
					count++;
			}
		}
	}	
	return count;
}
int soldier_shoots(){
	int count = 0;
	int x,y;
	map<pair<int,int>,Soldier*>::iterator it;
	
	for (it=smap.begin();it!=smap.end();it++){
		x=it->first.first;
		y=it->first.second;
		//cout<<"check"<<endl;
		for(int i=0;i<((it->second)->getHead()).size();i++){
		//	cout<<x<<","<<y<<((it->second)->getHead())[i]<<endl;
			if(((it->second)->getHead())[i]==1){
				if(board[x+2][y]=='O'){
					count++;
				}
				if(x+3<m && board[x+3][y]=='O')
					count++;
			}
			else if(((it->second)->getHead())[i]==-1){
				if(board[x-2][y]=='O')
					count++;
				if(x-3>=0 && board[x-3][y]=='O')
					count++;
			}
			else if(((it->second)->getHead())[i]==2){
				if(board[x][y+2]=='O')
					count++;
				if(y+3<n && board[x][y+3]=='O')
					count++;
			}
			else if(((it->second)->getHead())[i]==-2){
				if(board[x][y-2]=='O')
					count++;
				if(y-3>=0 && board[x][y-3]=='O')
					count++;
			}
			else if(((it->second)->getHead())[i]==3){
				if(board[x+2][y+2]=='O')
					count++;
				if(y+3<n && x+3<m && board[x+3][y+3]=='O')
					count++;
			}
			else if(((it->second)->getHead())[i]==-3){
				if(board[x-2][y-2]=='O')
					count++;
				if(y-3>=0 && x-3>=0 && board[x-3][y-3]=='O')
					count++;
			}
			else if(((it->second)->getHead())[i]==4){
				if(board[x+2][y-2]=='O')
					count++;
				if(y-3>=0 && x+3<m && board[x+3][y-3]=='O')
					count++;
			}
			else if(((it->second)->getHead())[i]==-4){
				if(board[x-2][y+2]=='O')
					count++;
				if(y+3<n && x-3>=0 && board[x-3][y+3]=='O')
					count++;
			}
		}
	}	
	return count;
}
int enemy_soldier_shoots(){
	int count = 0;
	int x,y;
	map<pair<int,int>,EnemySoldier*>::iterator it;
	
	for (it=emap.begin();it!=emap.end();it++){
		x=it->first.first;
		y=it->first.second;
		for(int i=0;i<((it->second)->getHead()).size();i++){
			if(((it->second)->getHead())[i]==1){
				if(board[x+2][y]=='S')
					count++;
				if(x+3<m && board[x+3][y]=='S')
					count++;
			}
			else if(((it->second)->getHead())[i]==-1){
				if(board[x-2][y]=='S')
					count++;
				if(x-3>=0 && board[x-3][y]=='S')
					count++;
			}
			else if(((it->second)->getHead())[i]==2){
				if(board[x][y+2]=='S')
					count++;
				if(y+3<n && board[x][y+3]=='S')
					count++;
			}
			else if(((it->second)->getHead())[i]==-2){
				if(board[x][y-2]=='S')
					count++;
				if(y-3>=0 && board[x][y-3]=='S')
					count++;
			}
			else if(((it->second)->getHead())[i]==3){
				if(board[x+2][y+2]=='S')
					count++;
				if(y+3<n && x+3<m && board[x+3][y+3]=='S')
					count++;
			}
			else if(((it->second)->getHead())[i]==-3){
				if(board[x-2][y-2]=='S')
					count++;
				if(y-3>=0 && x-3>=0 && board[x-3][y-3]=='S')
					count++;
			}
			else if(((it->second)->getHead())[i]==4){
				if(board[x+2][y-2]=='S')
					count++;
				if(y-3>=0 && x+3<m && board[x+3][y-3]=='S')
					count++;
			}
			else if(((it->second)->getHead())[i]==-4){
				if(board[x-2][y+2]=='S')
					count++;
				if(y+3<n && x-3>=0 && board[x-3][y+3]=='S')
					count++;
			}
		}
	}	
	return count;
}

int cannon_count(){
	int count = 0;
	map<pair<int,int>,Soldier*>::iterator it;
	
	for (it=smap.begin();it!=smap.end();it++){
		count+=((it->second)->getHead()).size();
	}
	
	return count;
}
int cannon_count_enemy(){
	int count = 0;
	map<pair<int,int>,EnemySoldier*>::iterator it;
	
	for (it=emap.begin();it!=emap.end();it++){
		count+=((it->second)->getHead()).size();
	}
	return count;
}
int eval(){
	int weight_soldier = 2;
	int weight_soldier_fire = 0.5;
	int weight_cannon = 0;
	int weight_townhall = 100;
	int weight_townhall_fire = 30;	
	
	if(tmap.size()<=2){
		return INT_MIN+10;
	}
	else if(etmap.size()<=2){
		return INT_MAX-10;
	}
	return weight_soldier*(smap.size()-emap.size()) +weight_soldier_fire*(soldier_shoots() - enemy_soldier_shoots())+ weight_cannon*(cannon_count()-cannon_count_enemy()) + weight_townhall*(tmap.size()-etmap.size())+ weight_townhall_fire*(townhall_shoots() - enemy_townhall_shoots());
}
int cutoff = 3;


pair<moveStruct, int> min_value(int alpha, int beta, moveStruct ms, int yl){
	yl++;
	if (terminal_emeny())
		return make_pair(ms, -1*utility());
	if(yl>cutoff)
		return make_pair(ms, eval());

	vector<moveStruct> v = valid_moves_enemy(board);
	//cout<<"enemy "<<v.size()<<endl;
	pair<moveStruct, int> min_child;
	min_child.second=INT_MAX;

	for(int i=0;i<v.size();i++){
		//cout<<"v.size() = "<<v.size()<<endl;
		// cout<<"Enemy Move "<<v[i].a[0]<<v[i].a[1]<<v[i].a[2]<<v[i].a[3]<<v[i].a[4]<<v[i].a[5]<<"    level = "<<yl<<endl;

		map<pair<int,int>,Soldier*> temp_smap = smap;
		map<pair<int,int>,EnemySoldier*> temp_emap = emap;
		map<pair<int,int>,Townhall*> temp_tmap = tmap;
		map<pair<int,int>,Townhall*> temp_etmap = etmap;
		int a[n][m];
		for(int i=0;i<n;i++){
			for(int j=0;j<m;j++){
				a[i][j]=board[i][j];
			}
		}
		// cout<<"p ";
		do_move(v[i]);
		// cout<<"q ";
		update_heads();
		// cout<<"r "<<endl;
		// for(int i=0;i<m;i++){
		// 	for(int j=0;j<n;j++){
		// 		cout<<board[j][i]<<" ";
		// 	}
		// 	cout<<endl;
		// }
		// cout<<endl;

		pair<moveStruct, int> child = max_value(alpha, beta, v[i], yl);
		smap = temp_smap; emap = temp_emap; tmap = temp_tmap; etmap = temp_etmap;
		for(int i=0;i<n;i++){
			for(int j=0;j<m;j++){
				board[i][j]=a[i][j];
			}
		}
		update_heads();
		// cout<<"Print this"<<endl;
		if(min_child.second>child.second){
			// cout<<"here    4"<<endl;
			min_child.second=child.second;
			min_child.first=v[i];
		}
		beta = std::min(beta, child.second);
		if(alpha>=beta){
			return child;
		}
	}
	return min_child;
}

pair<moveStruct, int> max_value(int alpha, int beta, moveStruct ms, int xl){
	xl++;
	if (terminal())
		return make_pair(ms, utility());
	if(xl>cutoff)
		return make_pair(ms, eval());

	vector<moveStruct> v = valid_moves();
	//cout<<v.size()<<endl;
	pair<moveStruct, int> max_child;
	max_child.second=INT_MIN;

	for(int i=0;i<v.size();i++){
		//cout<<"v.size() = "<<v.size()<<endl;
		// cout<<"Our Move "<<v[i].a[0]<<v[i].a[1]<<v[i].a[2]<<v[i].a[3]<<v[i].a[4]<<v[i].a[5]<<"    level = "<<xl<<endl;

		map<pair<int,int>,Soldier*> temp_smap = smap;
		map<pair<int,int>,EnemySoldier*> temp_emap = emap;
		map<pair<int,int>,Townhall*> temp_tmap = tmap;
		map<pair<int,int>,Townhall*> temp_etmap = etmap;
		int a[n][m];
		for(int i=0;i<n;i++){
			for(int j=0;j<m;j++){
				a[i][j]=board[i][j];
			}
		}
		// cout<<"a ";
		do_move2(v[i]);
		// cout<<"b ";
		update_heads();
		// cout<<"c "<<endl;

		pair<moveStruct, int> child = min_value(alpha, beta, v[i], xl);
		
		smap = temp_smap; emap = temp_emap; tmap = temp_tmap; etmap = temp_etmap;
		for(int i=0;i<n;i++){
			for(int j=0;j<m;j++){
				board[i][j]=a[i][j];
			}
		}
		update_heads();
		if(max_child.second<child.second){
			max_child.second=child.second;
			max_child.first=v[i];
		}
		
		alpha = std::max(alpha, child.second);
		if(alpha>=beta)
			return child;
	}
	// cout<<max_child.first.a<<endl;
	return max_child;

}

moveStruct alpha_beta(){
	
	int a[n][m];
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			a[i][j]=board[i][j];
		}
	}

	moveStruct temp;
	temp.a[0]='S'; temp.a[1]='0'; temp.a[2]='0'; temp.a[3]='M'; temp.a[4]='0'; temp.a[5]='0';

	map<pair<int,int>,Soldier*> temp_smap = smap;
	map<pair<int,int>,EnemySoldier*> temp_emap = emap;
	map<pair<int,int>,Townhall*> temp_tmap = tmap;
	map<pair<int,int>,Townhall*> temp_etmap = etmap;

	pair<moveStruct, int> ans = max_value(INT_MIN, INT_MAX, temp, -1);
	// cout<<"Complete"<<endl;
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			board[i][j]=a[i][j];
		}
	}
	smap = temp_smap; emap = temp_emap; tmap = temp_tmap; etmap = temp_etmap;
	// cout<<"yes"<<endl;
	// cout<<ans.first.a[0]<<" ";
	// cout<<ans.first.a[1]<<" ";
	// cout<<ans.first.a[2]<<" ";
	// cout<<ans.first.a[3]<<" ";
	// cout<<ans.first.a[4]<<" ";
	// cout<<ans.first.a[5]<<endl;
	// cout<<"no"<<endl;
	// cout<<"now"<<endl;
	return ans.first;
}

int main(int argc, char* argv[]){
	moveStruct visit;
	moveStruct firstmoves;
	cin>>id>>n>>m>>t;
	board=new char*[n];
	for(int i=0;i<n;i++){
		board[i]=new char[m];
	}
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			board[i][j]='E';
		}
	}
	char a1;
	
	vector<int> v1;
	v1.push_back(2);
	vector<int> v2;
	v2.push_back(-2);
	vector<int> v3;
		Soldier *s;
	EnemySoldier *es;
	Townhall *th;
	if(id==2){
		for(int j=0;j<3;j++){
			for(int i=0;i<m;i=i+2){
				if(j==0){
					th = new Townhall(i,0,true);
					board[i][0]='T'; //vth.push_back(th);
					tmap.insert({make_pair(i,0),th});
					th = new Townhall(i+1,n-1,false);
					board[i+1][n-1]='X'; //vth.push_back(th);
					etmap.insert({make_pair(i+1,n-1),th});
					s=new Soldier(i+1,0,v3);
					board[i+1][0]='S'; //vs.push_back(s);
					smap.insert({make_pair(i+1,0),s});
					es=new EnemySoldier(i,n-1,v3);
					board[i][n-1]='O'; //ves.push_back(es);
					emap.insert({make_pair(i,n-1),es});
				}else{
					if(j==1){
						s=new Soldier(i+1,j,v3);
						smap.insert({make_pair(i+1,j),s});
					}
					else{
						s=new Soldier(i+1,j,v1);
						smap.insert({make_pair(i+1,j),s});
					}
					board[i+1][j]='S'; //vs.push_back(s);
					
					if(j==1){
						es=new EnemySoldier(i,n-j-1,v3);
						emap.insert({make_pair(i,n-j-1),es});
					}
					else{
						es=new EnemySoldier(i,n-j-1,v2);
						emap.insert({make_pair(i,n-j-1),es});
					}
					board[i][n-j-1]='O';	
				}
			}
		}

		cin>>a1;visit.a[0]=a1;
		cin>>a1;visit.a[1]=a1;
		cin>>a1;visit.a[2]=a1;
		cin>>a1;visit.a[3]=a1;
		cin>>a1;visit.a[4]=a1;
		cin>>a1;visit.a[5]=a1;

		do_move(visit);

		update_heads();
	}
	else{
		for(int j=0;j<3;j++){
			for(int i=0;i<m;i=i+2){
				if(j==0){
					th = new Townhall(i,0,false);
					board[i][0]='X'; //vth.push_back(th);
					etmap.insert({make_pair(i,0),th});
					th = new Townhall(i+1,n-1,true);
					board[i+1][n-1]='T'; //vth.push_back(th);
					tmap.insert({make_pair(i+1,n-1),th});
					es=new EnemySoldier(i+1,0,v3);
					board[i+1][0]='O'; //vs.push_back(s);
					emap.insert({make_pair(i+1,0),es});
					s=new Soldier(i,n-1,v3);
					board[i][n-1]='S'; //ves.push_back(es);
					smap.insert({make_pair(i,n-1),s});
				}else{
					if(j==1){
						es=new EnemySoldier(i+1,j,v3);
						emap.insert({make_pair(i+1,j),es});
					}
					else{
						es=new EnemySoldier(i+1,j,v1);
						emap.insert({make_pair(i+1,j),es});
					}
					board[i+1][j]='O'; //vs.push_back(s);
					
					if(j==1){
						s=new Soldier(i,n-j-1,v3);
						smap.insert({make_pair(i,n-j-1),s});
					}
					else{
						s=new Soldier(i,n-j-1,v2);
						smap.insert({make_pair(i,n-j-1),s});
					}
					board[i][n-j-1]='S';
					
				}
			}
		}
	}
	int i=0;
	while(true){
		if(i==0 && id==1){
			firstmoves.a[0]='S';firstmoves.a[1]='4';firstmoves.a[2]='7';firstmoves.a[3]='M';firstmoves.a[4]='5';firstmoves.a[5]='6';
			cout<<firstmoves.a[0]<<" ";
			cout<<firstmoves.a[1]<<" ";
			cout<<firstmoves.a[2]<<" ";
			cout<<firstmoves.a[3]<<" ";
			cout<<firstmoves.a[4]<<" ";
			cout<<firstmoves.a[5]<<endl;

			do_move2(firstmoves);
			update_heads();
			i++;
			continue;
		}

		else if(i==0 && id==2){
			if(visit.a[0]=='S' && visit.a[1]=='4' && visit.a[2]=='7' && visit.a[3]=='M' && visit.a[4]=='5' && visit.a[5]=='6'){
				firstmoves.a[0]='S';firstmoves.a[1]='3';firstmoves.a[2]='0';firstmoves.a[3]='M';firstmoves.a[4]='2';firstmoves.a[5]='1';
				cout<<"S 3 0 M 2 1"<<endl;
			}
			else if(visit.a[0]=='S' && visit.a[1]=='2' && visit.a[2]=='7' && visit.a[3]=='M' && visit.a[4]=='1' && visit.a[5]=='6'){
				firstmoves.a[0]='S';firstmoves.a[1]='5';firstmoves.a[2]='2';firstmoves.a[3]='M';firstmoves.a[4]='5';firstmoves.a[5]='3';
				cout<<"S 5 2 M 5 3"<<endl;
			}
			else if(visit.a[0]=='S' && visit.a[1]=='4' && visit.a[2]=='7' && visit.a[3]=='M' && visit.a[4]=='3' && visit.a[5]=='6'){
				firstmoves.a[0]='S';firstmoves.a[1]='7';firstmoves.a[2]='2';firstmoves.a[3]='M';firstmoves.a[4]='7';firstmoves.a[5]='3';
				cout<<"S 7 2 M 7 3"<<endl;
			}
			else if(visit.a[0]=='S' && visit.a[1]=='2' && visit.a[2]=='7' && visit.a[3]=='M' && visit.a[4]=='2' && visit.a[5]=='4'){
				firstmoves.a[0]='S';firstmoves.a[1]='5';firstmoves.a[2]='0';firstmoves.a[3]='M';firstmoves.a[4]='6';firstmoves.a[5]='1';
				cout<<"S 5 0 M 6 1"<<endl;
			}
			else{
				firstmoves.a[0]='S';firstmoves.a[1]='3';firstmoves.a[2]='0';firstmoves.a[3]='M';firstmoves.a[4]='2';firstmoves.a[5]='1';
				cout<<"S 3 0 M 2 1"<<endl;
			}
			do_move2(firstmoves);
			update_heads();
			i++;
			continue;
		}
		else{
			cin>>a1;visit.a[0]=a1;
			cin>>a1;visit.a[1]=a1;
			cin>>a1;visit.a[2]=a1;
			cin>>a1;visit.a[3]=a1;
			cin>>a1;visit.a[4]=a1;
			cin>>a1;visit.a[5]=a1;
			do_move(visit);

			update_heads();

			moveStruct result = alpha_beta();

			cout<<result.a[0]<<" ";
			cout<<result.a[1]<<" ";
			cout<<result.a[2]<<" ";
			cout<<result.a[3]<<" ";
			cout<<result.a[4]<<" ";
			cout<<result.a[5]<<endl;

			do_move2(result);
			update_heads();
			i++;
		}
		
	}
	return 0;
}

