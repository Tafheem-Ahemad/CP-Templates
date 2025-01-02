
// It precompute at O(n) , give is_palindrom in O(1)

class Manacher {
public:
    string s;
    vector<int> palindromeRadii;

    string preprocess(string &s) {
        string result = "#";
        for (char c : s) {
            result += c;
            result += "#";
        }
        return result;
    }

    Manacher(string _s) {
        s = preprocess(_s);
        int n =s.size();
        palindromeRadii.resize(n,0);

        int center=0,right=0;
        for (int i=0;i<n; ++i) {
            int mirror = 2*center - i;

            if (i < right)
                palindromeRadii[i] = min(right - i, palindromeRadii[mirror]);

            while (i + palindromeRadii[i] + 1 < n && i - palindromeRadii[i] - 1 >= 0 &&
                   s[i + palindromeRadii[i] + 1] == s[i - palindromeRadii[i] - 1]) {
                 palindromeRadii[i]++;
            }

            if (i + palindromeRadii[i] > right) {
                center = i;
                right = i + palindromeRadii[i];
            }
        }
    }

    bool isPalindrome(int l, int r) {
        int processedL =l*2+1;
        int processedR =r*2+1;

        int center = (processedL + processedR) / 2;
        int radius = (processedR - processedL) / 2;

        return palindromeRadii[center] >= radius;
    }
};

