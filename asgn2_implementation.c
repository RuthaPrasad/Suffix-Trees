#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include "asgn2_header.h"
int ptr_SA[350][2500];//global array to store suffix arrays of approx 350 tales of 2000 characters
int rank[350][2];//rank holder for each tale containing tale number and its rank
bool all_occurences_called=false;
bool first_occurences_called=false;

void create_SA(char* txt,int tale_no)
{
	int len=strlen(txt);
	int index;
	int word=1;
	//create suffix tree with words as nodes 
	for(index=0;index<len;index++)//scan text for words
	{
		if(isalpha(txt[index]))//if alphabet found/word has started
		{
			//store index of first letter of word
			ptr_SA[tale_no][word]=index; 
			//no_of_words
			word++;
			while(isalpha(txt[index]))//till end of word
			{	index++;	}
		}	

		if(ispunct(txt[index]))//if punctuation
		{
			//store punctuation
			ptr_SA[tale_no][word]=index; 
			//no_of_words
			word++;
		}			
	}
	//store no of words in index=0
	ptr_SA[tale_no][0]=word;			
	
	//sort indexes based on lexographical order of words
	//using bubble sort as txt size not great
	int i, j;
	for(i=1;i<word;i++)     
 	{
       		for (j=1;j<word-i;j++)
           	{	//ignore lower upper case difference
			//if (tolower(txt[ptr_SA[tale_no][j]])>tolower(txt[ptr_SA[tale_no][j+1]]))
              		//if (txt[ptr_SA[tale_no][j]]>txt[ptr_SA[tale_no][j+1]])
              		if(strncasecmp(txt+ptr_SA[tale_no][j],txt+ptr_SA[tale_no][j+1],2)>0)
			{
				int temp=ptr_SA[tale_no][j];
				ptr_SA[tale_no][j]=ptr_SA[tale_no][j+1];
				ptr_SA[tale_no][j+1]=temp;
			}
		}
	}
		#if 0
		for (j=1;j<word;j++)
           	{	//ignore lower upper case difference
				printf("%c->%d\t",txt[ptr_SA[tale_no][j]],ptr_SA[tale_no][j]);
		}printf("\n\n");
		#endif
	
}
void create_suffix_tree(struct tales** ptr_ptr_mytales)
{
	int i=0;
	for(i=0;i<((*ptr_ptr_mytales)->no_of_tales);i++)
	{
		create_SA((*ptr_ptr_mytales)->ptr_tale[i],i);	
	}
	for(i=0;i<((*ptr_ptr_mytales)->no_of_tales);i++)
	{
		rank[i][0]=i;	
		rank[i][1]=0;	
	}	
}	
struct tales* insert_tales(struct tales **ptr_ptr_mytales)
{
	int num_of_tales=0;
	int i=0;
	char k;
	//allote memory to set of pointers to tales
	ptr_ptr_mytales=(struct tales**)malloc(sizeof(struct tales*));
	(*ptr_ptr_mytales)=(struct tales*)malloc(sizeof(struct tales));
	//scan_lines
	char* prev_scan_line=(char*)malloc(sizeof(char)*100);
	scanf(" %[^\n]",prev_scan_line);
	char* pres_scan_line=(char*)malloc(sizeof(char)*100);
	scanf(" %[^\n]",pres_scan_line);
	while((k=getchar())!=EOF)
	{
		//allote memory to each tale 
		(*ptr_ptr_mytales)->ptr_tale[i]=(char*)malloc(sizeof(char)*3000);

		//scan paragraph
		do
		{
			int len=strlen(prev_scan_line);
			(*ptr_ptr_mytales)->ptr_tale[i]=strncat((*ptr_ptr_mytales)->ptr_tale[i],prev_scan_line,len-1);		
			(*ptr_ptr_mytales)->ptr_tale[i]=strcat((*ptr_ptr_mytales)->ptr_tale[i]," ");		
			prev_scan_line=strcpy(prev_scan_line,pres_scan_line);
			scanf(" %[^\n]",pres_scan_line);//scan next line
		}
		while((isupper(pres_scan_line[0])+isupper(pres_scan_line[1])+isupper(pres_scan_line[2]))<=256 &&(k=getchar())!=EOF );//till a sentence with ALL_CAPITAL starting words or EOF 
		
		//icrement number of tales
		num_of_tales++;
		i++;
	}
	(*ptr_ptr_mytales)->no_of_tales=i;	
	return *ptr_ptr_mytales;
}
void disp_tales(struct tales** ptr_ptr_mytales)
{
	printf("No of tales:%d\n\n",((*ptr_ptr_mytales)->no_of_tales));
	int i=0;
	for(i=0;i<((*ptr_ptr_mytales)->no_of_tales);i++)
	{
		printf("%s\n\n",((*ptr_ptr_mytales)->ptr_tale[i]));	
	}	
}
int return_index(char *pat,struct tales** ptr_ptr_mytales,int tale_no)
{
	int m = strlen(pat);
	//Binary search for atleast one occurence of pat in txt 
	int l=1;
	int r=ptr_SA[tale_no][0];//number of words stored in ptr_SA[tale_no][0]			
	char* txt=(*ptr_ptr_mytales)->ptr_tale[tale_no];
	while(l<=r && l<=ptr_SA[tale_no][0] && 1<=r)
    	{
        	int mid=l+(r-l)/2;
		//printf("%d",mid);
        	if((tolower(pat[0]))>(tolower(txt[ptr_SA[tale_no][mid]])))
              	{
			//starting alphabet higher
			l=mid+1;
		}
		else if((tolower(pat[0]))<(tolower(txt[ptr_SA[tale_no][mid]])))
              	{
			//staring alphabet lower
			r=mid-1;
		}
		else if((tolower(pat[0]))==(tolower(txt[ptr_SA[tale_no][mid]])))
              	{	
			//match found
     			return mid;
		}
		else//not found
			return -1;	
        }
}
void all_occurences(struct tales** ptr_ptr_mytales,char* ptr_mypat)
{	
	all_occurences_called=true;
	printf("--------------------------------ALL OCCURENCES---------------------\n\n");
	//search each tale
	int tale_no=0;
	int m=strlen(ptr_mypat);//length of pattern
	for(tale_no=0;tale_no<(*ptr_ptr_mytales)->no_of_tales;tale_no++)
	{
		//find any one occurence of pattern in txt
		int index=return_index(ptr_mypat,ptr_ptr_mytales,tale_no);
		if(index!=-1)//atleast one occurence found
		{	
		//store title of tale
			char* txt=(*ptr_ptr_mytales)->ptr_tale[tale_no];
			char* title=(char*)malloc(sizeof(char)*50);
			int c=0;
			do//till ALL_CAPITAL word appears(start of tale)
			{
				title=strncat(title,txt+c,1);
				c++;		
			}
			while((isupper(txt[c])+isupper(txt[c+1])+isupper(txt[c+2]))<=256);
				        
		//calculate span of indexes of possible occurences of pattern 
			int left=index-1;
			int right=index+1;
			while((tolower(ptr_mypat[0]))==(tolower(txt[ptr_SA[tale_no][left]])) && 0<left)//left index	
			{	left--;
			}	
			while((tolower(ptr_mypat[0]))==(tolower(txt[ptr_SA[tale_no][right]])) && 0<left)//right index	
			{	right++;
			}	
			
		//scan each possible occurence and return results
			int i;
			for(i=left;i<=right;i++)
			{
			//compare ignoring lower/upper case
				if(strncasecmp(ptr_mypat,txt+ptr_SA[tale_no][i],m)==0)
				{
					
				//print title
					printf("TITLE:%s\n",title);
				//print context leading to pattern
					if((i-m)==0)//start of tale, no context before pattern
						printf("...%.*s...\n\n",5*m,txt+ptr_SA[tale_no][i]);
					else//other substring of tale txt
						printf("...%.*s...\n\n",5*m,txt+ptr_SA[tale_no][i]-m);
				//incremement relevance of tale in rank array
				//sequence of text matches pattern more than subsequence of text
				//category a of relevance
					rank[tale_no][1]=rank[tale_no][1]+2;
				}
			}
			
		}
		
	}
}
void first_occurences(struct tales** ptr_ptr_mytales,char* ptr_mypat)
{
	first_occurences_called=true;
	printf("------------------------FIRST OCCURENCES------------------------------\n\n");
	//search each tale
	int tale_no=0;
	int ptr_len=strlen(ptr_mypat);
	int pat_words[50];
	int index=0;
	int word=0;
	for(index=0;index<ptr_len;index++)//scan text for words
	{
		if(isalpha(ptr_mypat[index]))//if alphabet found/word has started
		{
			//store index of first letter of word
			pat_words[word]=index; 
			//no_of_words
			word++;
			while(isalpha(ptr_mypat[index]))//till end of word
			{	index++;	}
		}	

		if(ispunct(ptr_mypat[index]))//if punctuation
		{
			//store punctuation
			pat_words[word]=index; 
			//no_of_words
			word++;
		}
	}
	for(index=0;index<word;index++)
			printf("%d,",pat_words[index]);			
	for(tale_no=0;tale_no<(*ptr_ptr_mytales)->no_of_tales;tale_no++)
	{
		//store title of tale
		char* txt=(*ptr_ptr_mytales)->ptr_tale[tale_no];
		char* title=(char*)malloc(sizeof(char)*50);
		int c=0;
		do//till ALL_CAPITAL word appears(start of tale)
		{
			title=strncat(title,txt+c,1);
			c++;		
		}
		while((isupper(txt[c])+isupper(txt[c+1])+isupper(txt[c+2]))<=256);
		
		int substring=pat_words[0];
		bool longest_substring_found=false;
		int longest_substring_length=0;
		int longest_substring_pat_word=0;
		int longest_substring_text_word=0;
		
		while(substring<word && !longest_substring_found)//check for all substrings
		{
			//find any one occurence of pattern in txt
			int index=return_index(ptr_mypat+pat_words[substring],ptr_ptr_mytales,tale_no);
			if(index!=-1)//atleast one occurence found
			{	
						
				//calculate span of indexes of possible occurences of pattern since case insensitive 
				int left=index-1;
				int right=index+1;
				while((tolower((ptr_mypat+pat_words[substring])[0]))==(tolower(txt[ptr_SA[tale_no][left]])) && 0<left)	
				{	
					//left index
					left--;
				}	
				while((tolower((ptr_mypat+pat_words[substring])[0]))==(tolower(txt[ptr_SA[tale_no][right]])) && 0<left)
				{	
					//right index
					right++;
				}	
			
				//scan each possible occurence
				int i;
				for(i=left;i<=right;i++)
				{
					if(substring==0 && strncasecmp(ptr_mypat,txt+ptr_SA[tale_no][i],strlen(ptr_mypat))==0)
					{
							longest_substring_found=true;
							longest_substring_length=strlen(ptr_mypat);
							longest_substring_pat_word=pat_words[substring];
							longest_substring_text_word=i;
						//incremement relevance of tale in rank array as whole string matched
						//category e of relevance
							rank[tale_no][1]++;				
							break;						
					}
					//compare ignoring lower/upper case
					int m=strlen(ptr_mypat+pat_words[substring]);
					int word_length=pat_words[substring+1]-pat_words[substring];
					//find longest substring of substring that has a match
					//LCP dynamic creation
					while(strncasecmp(ptr_mypat+pat_words[substring],txt+ptr_SA[tale_no][i],m)!=0 && m>0)
					{
						m--;
					}
						
					if(longest_substring_length<m && strncasecmp(ptr_mypat+pat_words[substring],txt+ptr_SA[tale_no][i],m)==0)
					{
						longest_substring_length=m;
						longest_substring_pat_word=pat_words[substring];
						longest_substring_text_word=i;
						if(word_length==m)
						{
						//incremement relevance of tale in rank array as whole word has matched
						//category f of relevance
						rank[tale_no][1]++;							
						}
					}	
				}
			}
			substring++;		
		}
		if(longest_substring_length>0)//atleast one character found	
		{
			//print title
			printf("TITLE:%s\n",title);
			printf("Pattern:(%.*s)\n",longest_substring_length,ptr_mypat+longest_substring_pat_word);		
			//print context leading to pattern
			if(ptr_SA[tale_no][longest_substring_text_word]==0)		
			{		
		printf("...%.*s...\n\n",3*longest_substring_length,txt+ptr_SA[tale_no][longest_substring_text_word]);
			}
			else//context appears before and after pat
			{
			printf("...%.*s...\n\n",3*longest_substring_length,txt+ptr_SA[tale_no][longest_substring_text_word]-longest_substring_length);
			}
		
			//incremement relevance of tale in rank array
			rank[tale_no][1]++;							
		}	
	}

}
void rank_tales(struct tales** ptr_ptr_mytales,char* ptr_mypat)
{
	//call all_occurences and first_occurences if not called
	//as rank and relevance are decided by them
	if(all_occurences_called==false)
		all_occurences(ptr_ptr_mytales,ptr_mypat);
	if(first_occurences_called==false)
		first_occurences(ptr_ptr_mytales,ptr_mypat);

	//sort rank array 
	//using bubble sort as n is not great
	int i,j;
	for(i=0;i<(*ptr_ptr_mytales)->no_of_tales;i++)     
 	{
       		for (j=0;j<(*ptr_ptr_mytales)->no_of_tales-i;j++)
           	{	
			if (rank[j][1]<=rank[j+1][1])
              		{
				int temp=rank[j][0];
				rank[j][0]=rank[j+1][0];
				rank[j+1][0]=temp;
				temp=rank[j][1];
				rank[j][1]=rank[j+1][1];
				rank[j+1][1]=temp;
			}
		}
	}
	//display ranks
	printf("----------------------RANKS OF TALES ACCORDING TO RELEVANCE-------------------------\n\n");
	for (j=0;j<(*ptr_ptr_mytales)->no_of_tales;j++)
        {	
		int tale_no=rank[j][0];
		int relevance=rank[j][1];
		if(relevance!=0)
		{
			//store title of tale
			char* txt=(*ptr_ptr_mytales)->ptr_tale[tale_no];
			char* title=(char*)malloc(sizeof(char)*50);
			int c=0;
			do
			{
				title=strncat(title,txt+c,1);
				c++;		
			}
			while((isupper(txt[c])+isupper(txt[c+1])+isupper(txt[c+2]))<=256);
			printf("%d references in %s\n",relevance,title);
		}
	}
	

}
void delete_tales(struct tales** ptr_ptr_mytales)
{
	free((*ptr_ptr_mytales));
}

