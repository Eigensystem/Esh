#include "esh.hpp"

int main(){
	// esh::read_config();
	while(1){
		esh::read_command();
		esh::exec_command();
		esh::clear_space();
	}
}