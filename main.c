#include<stdio.h>
#include<stdlib.h>

#define ACCESS_ERROR "Access error: index %i does not exist\n"

struct Chain{
	int size_of_arrays;
	int next_index;
	int list_size;
	int** array_list;
};

void constructor(struct Chain* obj_core, int size_of_arrays){
	obj_core-> size_of_arrays = size_of_arrays;
	obj_core-> next_index = 0;
	obj_core-> list_size = 1;
	obj_core-> array_list = malloc(sizeof(int*)); // allocate an array of pointers to arrays of type int
	obj_core-> array_list[0] = malloc(size_of_arrays * sizeof(int)); // allocate an array of int
}
void destructor(struct Chain* obj_core){
	
	// free each of the dynamically allocated arrays
	for(int i=0; i < obj_core-> list_size; i++){
		free( obj_core-> array_list[i] );
	}
	
	// free the list containing all the array pointers
	free( obj_core-> array_list );
	
	// The struct itself will be destroyed wen it gets out of scope or when another destructor handles it
	// This is because the struct is meant to be a local variable in the stack. If it is in the heap, another
	// destructor will need to handle it.
}


void display_dbg(struct Chain* obj){
	printf("display_dbg!\nsize: %i\nnext: %i\nlist: %i\nptr: %i\n====================\n",obj->size_of_arrays,obj->next_index,obj->list_size,obj->array_list);
	
	for(int chain_node=0; chain_node < obj-> list_size; chain_node++){// to iterate through the list of pointers to arrays
		printf("Chain #%i:\n", chain_node);
		for(int i=0; i < obj-> size_of_arrays; i++){
			printf("%i\n",obj-> array_list[chain_node][i]);
		}
		printf("\n");
	}
}

int read_dbg(struct Chain* obj, int index){
	int chain_node = index / obj-> size_of_arrays;
	printf("access_dbg!\nchain_node: %i\n", chain_node);
	if(chain_node >= obj-> list_size){
		fprintf(stderr,ACCESS_ERROR,index);
		abort();
		
	}
	int internal_index = index % obj-> size_of_arrays;
	
	// debugg
	printf("internal index: %i\n", internal_index);
	if(chain_node == obj-> list_size - 1){
		if(internal_index >= obj-> next_index){
			fprintf(stderr,ACCESS_ERROR,index);
			abort();
		}
	}
	
	return *( *(obj-> array_list + chain_node) + internal_index );
}

int main(){
	printf("START OF PROGRAM\n\n");
	struct Chain test;
	constructor(&test,4);
	test.array_list[0][0] = 1;
	test.array_list[0][1] = 2;
	test.array_list[0][2] = 3;
	test.next_index = 3;
	
	display_dbg(&test);
	
	int v = read_dbg(&test,1);
	printf("v: %i\n",v);
	
	printf("\nEND OF PROGRAM\n");
	return 0;
}

