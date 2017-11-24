#include<stdio.h>
#include "asgn2_header.h"
int main()
{

		//create set of tales
	struct tales *ptr_mytales;
		//insert tales into set
	ptr_mytales=insert_tales(&ptr_mytales);
		//create suffix trees
	create_suffix_tree(&ptr_mytales);	
		//create query_pattern	
	char* ptr_mypat=(char*)malloc(sizeof(char)*100);
		//1st case=completely found
	//ptr_mypat="exclaimed the";
		//2nd case=partially found,punctuations,substrings,subwords,etc
	ptr_mypat="the lion exclaimed to the lamb?";
	
	printf("Query String:%s\n\n",ptr_mypat);	
		//1)find all occurences of pattern in all tales
	all_occurences(&ptr_mytales,ptr_mypat);
		//2)find first occurences of pattern/substring in all tales 
	first_occurences(&ptr_mytales,ptr_mypat);
		//3)rank each tale according to relevance
	rank_tales(&ptr_mytales,ptr_mypat);
	
	//disp_tales(&ptr_mytales);
	
		//clear memory
	delete_tales(&ptr_mytales);
	return 0;
}
