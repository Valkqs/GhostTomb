#include<bits/stdc++.h>
#include<string> 
#include<map>
#include<vector>
#include<windows.h>
#include<time.h>
using namespace std;

const int SENCENUM=4;

string sence[SENCENUM]={"BeginArea","AncientTomb","Temple","HardwareStore"};//,"Hospital","Grocery"
struct PlaceItem
{
	vector<string> ItemName;
	vector<int> ItemNum;
};

class player
{
	public:
		string name;
		int blood=10;
		int hurt=1;
		int control=0;
		int chance=0;
		string place="BeginArea";
		int head=0,tail=0;	
		
		multiset<string> Nthing;
		
		void get(string GetThing)
		{Nthing.insert(GetThing);}
		
		void discard(string DiscardThing)
		{
			multiset<string>::iterator DiscardI=Nthing.find(DiscardThing);
			Nthing.erase(DiscardI);
		}
		
		void search()
		{
			int s=1;
			for(multiset<string>::iterator i=Nthing.begin();i!=Nthing.end();i++)
			{
				cout<<*i<<":"<<s<<endl;
				s++;
			}
		}
		
		void move(string GoPlace)
		{
			place=GoPlace;
		}	
		
		player rob(string RobThing,player RobbedPlayer)
		{
			get(RobThing);
			RobbedPlayer.discard(RobThing);
			return RobbedPlayer;
		}			
};

int newrand()  
{
	time_t myt=time(NULL);
    int tmp=(myt%1000)*(rand()%100)+sqrt(rand()); 
    return tmp;
}

struct LaserPointer
{
	int QualityNumber=0;
	string name="LaserPointer";
	int change=1;
	int hurt=2;
	
	void LPInitialize()
	{
		hurt=2;
		change=1;
	}
			
	player laserpointer(player TheOne)
	{
		TheOne.blood-=hurt;
		hurt+=change;
		change=-change;
		return TheOne;
	} 
}LP;

struct Hammer
{
	string name="Hammer";
	int hurt=2;
	int control=1;
	
	player hammer(player TheOne)
	{
		TheOne.blood-=hurt;
		TheOne.control+=control;
		return TheOne;
	}
}H;

struct Plier
{
	string name="Plier";
	int hurtR=4;
	int hurtS=2;
	
	player plier(player TheOne,player TheOperatingOne)
	{
		if(TheOne.place==TheOperatingOne.place)TheOne.blood-=hurtS;
		else TheOne.blood-=hurtR;
	}
}P;

struct FlashLight
{
	string name="FlashLight";
	int control=2;
	bool IfEnergetic=false;
	
	void FLInitialize()
	{
		IfEnergetic=false;
	}
	
	player flashlight(player TheOne)
	{
		if(IfEnergetic)TheOne.control+=control;
		IfEnergetic=!IfEnergetic;
		return TheOne;
	}
}FL;

struct ElectricSaw
{
	string name="ElectricSaw";
	int hurt=1;
	
	void ESInitialize()
	{
		hurt=1;
	}
	
	player electricsaw(player TheOne)
	{
		TheOne.blood-=hurt;
		hurt=hurt%4+1;
		return TheOne;
	}
}ES;

player use(string Item,player ThePlayer,player TheOperatingPlayer)
{
	if(Item=="LaserPointer")ThePlayer=LP.laserpointer(ThePlayer);
	if(Item=="Hammer")ThePlayer=H.hammer(ThePlayer);
	if(Item=="Plier")ThePlayer=P.plier(ThePlayer,TheOperatingPlayer);
	if(Item=="FlashLight")ThePlayer=FL.flashlight(ThePlayer);
	if(Item=="ElectricSaw")ThePlayer=ES.electricsaw(ThePlayer);
	return ThePlayer;
}

const int SHORTNUM=3;
string ShortItem[SHORTNUM]={"Hammer","FlashLight","ElectricSaw"};
bool ShortSearch(string IfS)
{
	for(int i=0;i<SHORTNUM;i++)
		if(IfS==ShortItem[i])return true;
	return false;
}

int* FingerGuessing(int n,player ThePlaying[])
{
	int Finger[n];
	int Judge[3]={0};
	bool E=false;
	while(!E)
	{
		memset(Judge,0,sizeof(int)*3);
		for(int i=0;i<n;i++)
		{
			Finger[i]=newrand()%3;
			cout<<ThePlaying[i].name<<":"<<Finger[i]<<endl;
			Judge[Finger[i]]++;
		}
		int T=0;
		for(int i=0;i<3;i++)if(Judge[i]!=0)T++;
		if(T==2)E=true;
		else cout<<"No result!"<<endl;
	}
	cout<<"Success!"<<endl;
	int* Result=new int[n];
	for(int i=0;i<n;i++)Result[i]=0;
	if(Judge[0]!=0&&Judge[1]!=0)
	{
		for(int i=0;i<n;i++)
		if(Finger[i]==0)Result[i]=Judge[1];
	}
	else if(Judge[1]!=0&&Judge[2]!=0)
	{
		for(int i=0;i<n;i++)
		if(Finger[i]==1)Result[i]=Judge[2];
	}
	else if(Judge[0]!=0&&Judge[2]!=0)
	{
		for(int i=0;i<n;i++)
		if(Finger[i]==2)Result[i]=Judge[0];
	}
	cout<<"Each Player's chance:"<<endl;
	for(int i=0;i<n;i++)cout<<ThePlaying[i].name<<":"<<Result[i]<<endl; 
	return Result;
}

map<string,PlaceItem> ItemInPlace;

void initialize()
{	
	PlaceItem IniItem1;
	IniItem1.ItemName.push_back("FangMace");IniItem1.ItemNum.push_back(1);
	IniItem1.ItemName.push_back("ShadowBoomerang");IniItem1.ItemNum.push_back(1);
	ItemInPlace.insert(make_pair("AncientTomb",IniItem1));
	
	PlaceItem IniItem2;
	IniItem2.ItemName.push_back("BowOfTheSolar");IniItem2.ItemNum.push_back(1);
	IniItem2.ItemName.push_back("LaserPointer");IniItem2.ItemNum.push_back(1);
	ItemInPlace.insert(make_pair("Temple",IniItem2));  
	LP.LPInitialize();
	
	PlaceItem IniItem3;
	IniItem3.ItemName.push_back("Plier");IniItem3.ItemNum.push_back(100);
	IniItem3.ItemName.push_back("Toilet");IniItem3.ItemNum.push_back(100);
	IniItem3.ItemName.push_back("FlashLight");IniItem3.ItemNum.push_back(1);
	IniItem3.ItemName.push_back("Hammer");IniItem3.ItemNum.push_back(1);
	IniItem3.ItemName.push_back("ElectricSaw");IniItem3.ItemNum.push_back(1);
	ItemInPlace.insert(make_pair("HardwareStore",IniItem3)); 
	FL.FLInitialize();
	ES.ESInitialize();
}

int main()
{
	cout<<"Welcome to the GhostTomb!"<<endl;
	while(1)
	{
		initialize();
		int Num;
		cout<<"Please input the number of the players."<<endl;
		cin>>Num;
		player Player[Num];
		cout<<"Please input each Player's name."<<endl;
		for(int i=0;i<Num;i++)
		{
			cout<<"Player"<<i+1<<":"<<endl;
			cin>>Player[i].name;
		} 
		int IfFinish;
		do
		{
			IfFinish=0;
			int* Chance=FingerGuessing(Num,Player);
			for(int i=0;i<Num;i++)Player[i].chance+=Chance[i];
			delete[] Chance;
			int IfPlayerFinish[Num];
			for(int i=0;i<Num;i++)IfPlayerFinish[i]=0;
			for(int i=0;i<Num;i++)
			{
				int WhoseTurn;
				bool J=false;
				
				do
				{
					WhoseTurn=newrand()%Num;
					if(IfPlayerFinish[WhoseTurn]==0)J=true;
				}while(!J);
				IfPlayerFinish[WhoseTurn]=1;
				
				while(Player[WhoseTurn].chance>0)
				{
					Player[WhoseTurn].chance--;
					if(Player[WhoseTurn].control>0)
					{
						cout<<"You must release control on this turn,"<<Player[WhoseTurn].name<<"!"<<endl;
						Player[WhoseTurn].control--;
					}
					else
					{
						int J1;
						cout<<Player[WhoseTurn].name<<",what would you like to do?"<<endl;
						cout<<"Inquire your condition:0  Move:1  Get:2  Rob:3  Use:4"<<endl;

						cin>>J1;	
						if(J1==0)
						{
							Player[WhoseTurn].chance++;
							cout<<Player[WhoseTurn].name<<":"<<endl
								<<"Blood:"<<Player[WhoseTurn].blood<<"  Place:"<<Player[WhoseTurn].place<<endl
								<<"Control:"<<Player[WhoseTurn].control<<"  Chance:"<<Player[WhoseTurn].chance<<endl;
							Player[WhoseTurn].search();
						}

						if(J1==1)
						{
							vector<string> PlaceCanGo;
							for(int i=0;i<SENCENUM;i++)
								if(sence[i]!=Player[WhoseTurn].place)
									PlaceCanGo.push_back(sence[i]);
							for(int i=0;i<SENCENUM-1;i++)
								cout<<PlaceCanGo[i]<<":"<<i+1<<endl;
							int J2;cin>>J2;
							Player[WhoseTurn].move(PlaceCanGo[J2-1]);
							cout<<"You have moved to "<<Player[WhoseTurn].place<<endl;
							continue;
						}

						if(J1==2)
						{
							vector<string> ThingCanGet;
							for(int i=0;i<ItemInPlace[Player[WhoseTurn].place].ItemNum.size();i++)
								if(ItemInPlace[Player[WhoseTurn].place].ItemNum[i]>0)
									ThingCanGet.push_back(ItemInPlace[Player[WhoseTurn].place].ItemName[i]);
							for(int i=0;i<ThingCanGet.size();i++)
								cout<<ThingCanGet[i]<<":"<<i+1<<endl;
							int J2;cin>>J2;
							Player[WhoseTurn].get(ThingCanGet[J2-1]);
							ItemInPlace[Player[WhoseTurn].place].ItemNum[J2-1]--;
							cout<<"You have gotten the "<<ThingCanGet[J2-1]<<endl;
							continue;
						}
						
						if(J1==3)
						{
							vector<int> PlayerCanRob;
							for(int i=0;i<Num;i++)
								if(i!=WhoseTurn&&Player[i].place==Player[WhoseTurn].place)
									PlayerCanRob.push_back(i);
							if(PlayerCanRob.size()!=0)
							{
								cout<<"Choice the one you want to rob."<<endl;
								for(int i=0;i<PlayerCanRob.size();i++)
									cout<<Player[PlayerCanRob[i]].name<<":"<<PlayerCanRob[i]+1<<endl;
																		
								int J2;cin>>J2;
								Player[J2-1].search();
								int J3;cin>>J3;
								
								
								int s=1;
								string RobThing;
								for(multiset<string>::iterator i=Player[J2-1].Nthing.begin();i!=Player[J2-1].Nthing.end();i++)
								{
									if(s==J3)
									{
										RobThing=*i;
										break;
									}
									s++;
								}
								
								Player[J2-1]=Player[WhoseTurn].rob(RobThing,Player[J2-1]);
								cout<<"You have robbed the "<<RobThing<<" from "<<Player[J2-1].name<<endl;
								continue;																
							}														
						}
										
						if(J1==4)
						{
							cout<<"Choice the thing you want to use."<<endl;														
							Player[WhoseTurn].search();
							int J2;cin>>J2;
							string UseThing;
							int s=1;
							for(multiset<string>::iterator i=Player[WhoseTurn].Nthing.begin();i!=Player[WhoseTurn].Nthing.end();i++)
							{
								if(s==J2)
								{
									UseThing=*i;
									break;
								}
								s++;
							}
							
							if(ShortSearch(UseThing))
							{
								int J3=0;							
								for(int i=0;i<Num;i++)
									if(Player[i].place==Player[WhoseTurn].place)
										J3++;
								if(J3==1)
								{
									cout<<"You can't use it!"<<endl;
									Player[WhoseTurn].chance++;
									continue;
								}
							}
							
							cout<<"Choice the Player."<<endl;
							for(int i=0;i<Num;i++)
							{
								if(i==WhoseTurn)continue;
								if(ShortSearch(UseThing))
								if(Player[i].place!=Player[WhoseTurn].place)continue;
								cout<<Player[i].name<<":"<<i+1<<endl;
							}
							cin>>J2;
							Player[J2-1]=use(UseThing,Player[J2-1],Player[WhoseTurn]);
							if(UseThing=="Plier"&&Player[WhoseTurn].place!=Player[J2-1].place)
								Player[WhoseTurn].discard(UseThing);
							continue;
						}
					}
				}
			}
			
			for(int i=0;i<Num;i++)
			if(Player[i].blood>0)IfFinish++;
			else 
			{
				cout<<Player[i].name<<" is out!"<<endl;
				for(int j=i;j<Num-1;j++)Player[j]=Player[j+1];
				i--;Num--;
			}
		}while(IfFinish!=1);
		cout<<Player[0].name<<" win!!!!!"<<endl;
		ItemInPlace.erase(ItemInPlace.begin(),ItemInPlace.end());
	}
	return 0;
}
