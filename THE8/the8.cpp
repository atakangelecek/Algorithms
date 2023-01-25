#include "the8.h"

//DO NOT ADD OTHER LIBRARIES

int next_state(std::string pattern, int size, int state, int x, const std::pair<std::string,std::string> mapping)
{
    if ((state < size) && x == pattern[state]) {
        return state + 1;
    }
    else if((pattern[state] == mapping.first[0]) && (x == mapping.second[0])){
        return state + 1;
    }
    else if((pattern[state] == mapping.second[0]) && (x == mapping.first[0])){
         return state + 1;
    }
	int nxt_state, i;
	for (nxt_state = state; nxt_state > 0; nxt_state--)
	{   
		if ((pattern[nxt_state-1] == x) || ((pattern[nxt_state - 1] == mapping.first[0]) && (x == mapping.second[0])) || ((pattern[nxt_state - 1] == mapping.second[0]) && (x == mapping.first[0]))) {		
            for (i = 0; i < nxt_state-1; i++){
                if (((pattern[i] == pattern[state-nxt_state+1+i]) || ((pattern[i] == mapping.first[0]) && (pattern[state - nxt_state + 1 + i] == mapping.second[0])) || ((pattern[i] == mapping.second[0]) && (pattern[state - nxt_state + 1 + i] == mapping.first[0]))) == false){
                    break;
                }
            }
			if (i+1 == nxt_state){
				return nxt_state;
            }
		}
	}

	return 0;
}

void find_pattern(const std::string& pattern, std::vector<std::vector<int>>& fsa, const std::pair<std::string,std::string> mapping)
{
    int size = pattern.size();
    int range = fsa[0].size();
	
	for (int state = 0; state <= size; state++){
		for (int x = 0; x < range; x++){
			fsa[state][x] = next_state(pattern, size, state, x, mapping);
        }
    }
}

void matchPattern(const std::string& sequence, const std::pair<std::string,std::string> mapping, const std::string& pattern){

    std::vector<int> matches;
    int pat_size = pattern.size();
	int seq_size = sequence.size();

	std::vector<std::vector<int>> fsa(pat_size + 1, std::vector<int>(91,0));
    
	find_pattern(pattern, fsa, mapping);

	int i, state=0;
	for (i = 0; i < seq_size; i++)
	{
		state = fsa[state][sequence[i]];
		if (state == pat_size){
            matches.push_back(i - pat_size + 1);
        }
        
	}
    int res_size = matches.size();
    if(res_size == 0){
        std::cout<< "NONE";
        return ;
    }

    for(int i=0; i<res_size; i++){
        if(i == res_size-1){
            std::cout<<matches[i];
        }
        else{
            std::cout<<matches[i]<< " ";
        }
    }
    return;
}
