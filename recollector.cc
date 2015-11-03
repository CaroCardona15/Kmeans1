#include <iostream>
#include <string>
#include <cassert>
#include <zmqpp/zmqpp.hpp>
using namespace std;
using namespace zmqpp;
int main()
{
	cout << "Recollector\n";
	context ctx;
	cout<<"Listening socket to tcp port 5558";
	socket worker_recollector(ctx, socket_type::pull);  // recive worker-recollector  
	worker_recollector.connect("tcp://localhost:5558");
	
	while(true) 
	{
		message worker;                // recibe del worker
	    worker_recollector.receive(worker);
	    int centroidx;
	    int centroidy;
	    int part;
	    worker >> centroidx;
	    worker >> centroidy;
	    worker >> part;
	    
	    cout << "Cluster " << part;
	    cout << "centroide "<<centroidx << ":" << centroidy << endl;
		
		
		//server_workers.send(recollector);	    
  	}
  	return 0;
}
