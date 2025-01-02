


struct node{
    node* arr[26];
    bool flag;

    node(){
        flag=false;
        for(int i=0;i<26;i++) arr[i]=NULL;
    }
};

struct Trie{

    node* root;
    Trie() {
        root=new node();
    }
    
    void insert(string s) {
        int n=s.size();
        node* cur=root;
        for(int i=0;i<n;i++){
            if(cur->arr[s[i]-'a']==NULL){
                cur->arr[s[i]-'a']=new node();
            }

            cur=cur->arr[s[i]-'a'];
        }

        cur->flag=1;
    }
    
    bool search(string s) {
        int n=s.size();
        node* cur=root;
        for(int i=0;i<n;i++){
            if(cur->arr[s[i]-'a']==NULL){
                return false;
            }

            cur=cur->arr[s[i]-'a'];
        }

        return cur->flag;
    }
    
    bool prefix(string s) {
        int n=s.size();
        node* cur=root;
        for(int i=0;i<n;i++){
            if(cur->arr[s[i]-'a']==NULL){
                return false;
            }

            cur=cur->arr[s[i]-'a'];
        }

        return 1;
    }
};