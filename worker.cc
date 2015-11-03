#include <iostream>
#include <string>
#include <cassert>
#include <zmqpp/zmqpp.hpp>
using namespace std;
using namespace zmqpp;
int main()
{
	cout << "Worker\n";
	context ctx;
	cout<<"Listening socket to tcp port 5557";
	socket server_worker(ctx, socket_type::pull);  // recive server-worker  
	server_worker.connect("tcp://localhost:5557");
	cout<<"Binding socket to tcp port 5558";
	socket worker_recollector(ctx, socket_type::push);  // socket worker-recollector  
	worker_recollector.bind("tcp://*:5558");
	
	int sumx=0;
	int sumy=0;
	while(true) 
	{	
		message server;                // recibe del servidor
	    server_worker.receive(server);
	    int nsumx;
	    int nsumy;
	    int part;
	    int ncant;
	    server >>ncant;
	    server >> nsumx;
	    sumx=sumx+nsumx;
	    server >> nsumy;
	    sumy=sumy+nsumy;
	    server >> part;
	    cout <<"recibido...";
	    
	    int centroidx=(sumx)/ncant;
		int centroidy=(sumy)/ncant;
	     
	    	 
		message recollector;                    // envia al recollector
		recollector << centroidx;
		recollector << centroidy;
		recollector << part;	    
		
	    server_worker.send(recollector);
	   
  	}	
  	
		
		    
  	return 0;
}
