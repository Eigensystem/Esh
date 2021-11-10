#include <csignal>
#include "lib/esh.hpp"
#include "tools/signalHandler.hpp"
int main(){

	signal(SIGINT, SH_INThandler);
	esh::start_config();
	while(1){
		if(!esh::read_command()){
			continue;
		}
		esh::start_exec();
		esh::clear_space();
	}
}