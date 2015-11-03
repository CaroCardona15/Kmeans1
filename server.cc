#include <iostream>
#include <string>
#include <cassert>
#include <zmqpp/zmqpp.hpp>
#include <fstream>
using namespace std;
using namespace zmqpp;
int main()
{
	
	cout << "Servidor\n";
	context ctx;
	cout<<"Binding socket to tcp port 5557 \n";
	socket server_worker(ctx, socket_type::push);  // socket server-worker 
	server_worker.bind("tcp://*:5557");
	
	int listx[88234];
	int listy[88234];
	
	ifstream file;
	int num=0;
	file.open("facebook_combined.txt");
	while(!file.eof()){
		file >>listx[num];
		file >>listy[num];
		++num;
	}
	file.close();
	int k=4;
	cout << "ingrese el numero de k:" ;
	cin >> k;
	int ncant= (88234/k)+1;
	cout << "ncant " << ncant;
	int nlistx[22059];
	int nlisty[22059];
	while(true)
	{
		cout<<"=========MENU========="<<endl;
		message worker;                    // envia al worker
		worker << ncant;
		int ni=0;
		int part=1;
		int part1=1;
		for (int i=0; i<88234; i++){
			nlistx[ni]= listx[i];
			nlisty[ni]= listy[i];
			worker << nlistx[ni];
			worker << nlisty[ni];
			if (ni < ncant){
				ni++;
				part=part1;
				}
				else{
					worker << part;
					part1= part1+1;					
					ni=0;
					}
			
			
		}			
		cout << "send to worker...: \n" ;  
		server_worker.send(worker);	
		  
  	}
  	return 0;
}
