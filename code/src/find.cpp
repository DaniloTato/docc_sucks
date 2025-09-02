#include "checks.hpp"

#include <string>
#include <vector>
#include <utility>

#define NO_OF_CHARS 256

typedef std::pair<size_t, size_t> range;

std::vector<range> find(std::string& txt, std::string& pat){
    int m = pat.size();
    int n = txt.size();

    std::vector<int> badchar(NO_OF_CHARS, -1);
    std::vector<range> answer;

    for (int i = 0; i < m; i++){
        badchar[(int)pat[i]] = i; 
    }

    int s = 0; //shift
    while (s + m < n) { //check that shfit + lenght < str.size()
        int j = m - 1;//iterator for pattern

        while (j >= 0 && pat[j] == txt[s + j])
            j--;

        //if the pattern was matched in this iteration
        char next_char_after_pattern = txt[s + m];
        int next_char_value = badchar[next_char_after_pattern];
        if (j < 0) {
            answer.push_back(std::make_pair(s,s+m-1));
            int next_char_value = badchar[next_char_after_pattern];
            if(s + m < n){
                s += m;
                s -= next_char_value;
            } else s+= 1;
                
        }else{
            //when a mismatch is found, move the pattern so the next match in str. 
            if(j - next_char_value > 1){
                s += j - next_char_value;
            }else{
                s+=1;
            }
        }
    }

    return answer;
}