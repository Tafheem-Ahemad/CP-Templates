
// Templete of KMP search for vector

// return the occurance of string "s" which is match to string "t"

void computeLPSArray(vector<int>&pat, vector<int>&lps){
        
    for(int i=1;i<pat.size();i++){
        int len = lps[i-1];
        while(len>0 && pat[i]!=pat[len]){
            len = lps[len-1];
        }
        if(pat[i]==pat[len]){
            len++;
        }
        lps[i] = len;
    }
}

vector<int> KMPSearch(vector<int>&txt, vector<int>&pat){

    int n = (int) txt.size();
    int m = (int) pat.size();
    vector<int> lps (m,0);
    computeLPSArray(pat,lps);
    vector<bool> pos(n);
    for (int i = 0, j = 0; i < n; ) {
        if (pat[j] == txt[i]) {
            i++, j++;
        }
        if (j == m) {
            pos[i - j] = true;
            j = lps[j - 1];
        } else if (pat[j] != txt[i]) {
            if (j > 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
    }

    vector<int>occurance;
    for(int i=0;i<n;i++){
        if(pos[i]) occurance.push_back(i);
    }

    return occurance;
}


// KMP search for string

// Return all the occurance of string "s" which is match to string "t"


void LPS(string& s,vector<int> &lps) {
    int n = (int) s.length();
    for (int i = 1; i < n; i++) {
        int j = lps[i - 1];
        while (j > 0 && s[i] != s[j]) {
            j = lps[j - 1];
        }
        if (s[i] == s[j]) {
            j++;
        }
        lps[i] = j;
    }
}

vector<int> KMPSearch(string& txt, string& pat) {
    int n =txt.size();
    int m =pat.size();
    vector<int> pi (m,0) ;
    LPS(pat,pi);
    vector<bool> pos(n);
    int i=0,j=0;
    while(i<n){
        if(txt[i]==pat[j]){
            i++;
            j++;
        }else{
            if(j>0){
                j=pi[j-1];
            }else{
                i++;
            }
        }
        
        if(j==m){
            pos[i-j]=1;
            j=pi[j-1];
        }
    }

    vector<int>occurance;
    for(int i=0;i<n;i++){
        if(pos[i]) occurance.push_back(i);
    }

    return occurance;
}