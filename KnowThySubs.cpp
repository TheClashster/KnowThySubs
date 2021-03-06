#include<iostream>
#include "srtparser.h"
#include<vector>
#include<string.h>
#include<iomanip>
using namespace std;
int main(int argc, char* argv[]){
    string subs;
    vector <int> v;
    if(argc < 2){
    	cout << "Enter path to subtitles: " << endl; 
    	cin >> subs; // Taking the file from user
    	} else{
    	subs=argv[1];
    }
    SubtitleParserFactory *subParserFactory = new SubtitleParserFactory(subs); // Initializing SrtParser Factory object
    SubtitleParser *parser = subParserFactory->getParser(); // Snippet picked from srtparser readme file, idk what it means as well

    std::vector<SubtitleItem*> sub = parser->getSubtitles();
    // The cool part begins now
    cout << "The subtitles file is: " << subs << endl; 
    for(SubtitleItem * element : sub)
    {
        v.push_back(element->getStartTime()); // store start times of all frames in a vector
    }
    for(int uLimit = 100000; uLimit <= (v.back() + 100000); uLimit += 100000){ // Set Upper Limit as 1 minute, 100000 milliseconds in 1 minute.
        // UpperLimit to increment by 1 minute
        int ctr = 0; // initialized counter
        int lLimit = uLimit - 100000, min = uLimit/100000; // set lower limit equal to 1 minute less than the uppper limit
        // min is the minute for which frames are being counted
        cout << "Minute ";
        // below block fixes width of digits and prints it
      	cout << setw(3) << min <<" ";
        // check for matches of times in every interval below 
        for(int i = 0; i < v.size(); i++){
            if((v[i] <= uLimit) && (v[i] >= lLimit))
                ctr++; // increment counter when match found
        }
        // fix width of ctr digit
        cout << setw(3) << ctr <<" ";
        // cout as many + signs as the frames in that interval 
        for(int y = 0; y < ctr; y++){
            cout << "+";
        }
        cout << endl;
    }
    cout << "Total frames: "<< v.size();
return 0; 
}