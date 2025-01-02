


class SparseTableMin {
private:
    vector<vector<ll>> st;
    vector<ll> log;
    ll n;

public:
    SparseTableMin(vector<ll> arr) {
        n = arr.size();
        log.resize(n + 1);
        st.assign(n, vector<ll>(log2(n) + 2));

        build_sparse_table(arr);
    }

    void build_sparse_table(vector<ll>& arr) {
        for (int i = 2; i <= n; ++i) {
            log[i] = log[i / 2] + 1;
        }

        for (int i = 0; i < n; ++i) {
            st[i][0] = arr[i];
        }

        for (int j = 1; (1 << j) <= n; ++j) {
            for (int i = 0; (i + (1 << j)) <= n; ++i) {
                st[i][j] = max(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
            }
        }
    }

    ll query(int l, int r) {
        int j = log[r - l + 1];
        return max(st[l][j], st[r - (1 << j) + 1][j]);
    }
};


class SparseTableSum {
private:
    vector<vector<ll>> st;
    vector<ll> log;
    int n;

public:
    SparseTableSum(vector<ll>& arr) {
        n = arr.size();
        log.resize(n + 1);
        st.assign(n, vector<ll>(log2(n) + 1));

        build_sparse_table(arr);
    }

    void build_sparse_table(vector<ll>& arr) {
        // Precompute log values for efficient range queries
        for (int i = 2; i <= n; ++i) {
            log[i] = log[i / 2] + 1;
        }

        // Initialize sparse table with original array values
        for (int i = 0; i < n; ++i) {
            st[i][0] = arr[i];
        }

        // Build sparse table for range sum query
        for (int j = 1; (1 << j) <= n; ++j) {
            for (int i = 0; (i + (1 << j)) <= n; ++i) {
                st[i][j] = st[i][j - 1] + st[i + (1 << (j - 1))][j - 1];
            }
        }
    }

    int query(int l, int r) {
        int sum = 0;
        for (int j = log[r - l + 1]; j >= 0; --j) {
            if ((1 << j) <= r - l + 1) {
                sum += st[l][j];
                l += (1 << j);
            }
        }
        return sum;
    }
};


class SparseTable2D {
private:
    vector<vector<ll>> matrix;
    vector<vector<vector<vector<ll>>>> table;
    ll n, m;
    
    public:
    SparseTable2D(const vector<vector<ll>>& mat) {
        n = mat.size();
        m = mat[0].size();
        matrix = mat;
        
        int K = log2(n) + 1;
        int L = log2(m) + 1;
        
        table.resize(n, vector<vector<vector<ll>>>(m, vector<vector<ll>>(K, vector<ll>(L, INT_MAX))));
        
        build_sparse_table();
    }
    
    void build_sparse_table() {
        // Copy the values of the original matrix to the first element of the table
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                table[i][j][0][0] = matrix[i][j];
            }
        }

        // Building the table for rows
        for (int k = 1; k <= (int)(log2(n)); ++k) {
            for (int i = 0; i + (1 << k) - 1 < n; ++i) {
                for (int j = 0; j < m; ++j) {
                    table[i][j][k][0] = min(
                        table[i][j][k - 1][0],
                        table[i + (1 << (k - 1))][j][k - 1][0]);
                }
            }
        }

        // Building the table for columns
        for (int k = 1; k <= (int)(log2(m)); ++k) {
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j + (1 << k) - 1 < m; ++j) {
                    table[i][j][0][k] = min(
                        table[i][j][0][k - 1],
                        table[i][j + (1 << (k - 1))][0][k - 1]);
                }
            }
        }

        // Building the table for both rows and columns
        for (int k = 1; k <= (int)(log2(n)); ++k) {
            for (int l = 1; l <= (int)(log2(m)); ++l) {
                for (int i = 0; i + (1 << k) - 1 < n; ++i) {
                    for (int j = 0; j + (1 << l) - 1 < m; ++j) {
                        table[i][j][k][l] = min(
                            min(table[i][j][k - 1][l - 1],
                                table[i + (1 << (k - 1))][j][k - 1][l - 1]),
                            min(table[i][j + (1 << (l - 1))][k - 1][l - 1],
                                table[i + (1 << (k - 1))][j + (1 << (l - 1))][k - 1][l - 1]));
                    }
                }
            }
        }
    }

    int query(int x1, int y1, int x2, int y2) {
        // log2(x2-x1+1) gives the power of 2 which is just less than or equal to x2-x1+1
        int k = log2(x2 - x1 + 1);
        int l = log2(y2 - y1 + 1);

        // Lookup the value from the table which is the minimum among the 4 submatrices
        return min(min(table[x1][y1][k][l],
                       table[x2 - (1 << k) + 1][y1][k][l]),
                   min(table[x1][y2 - (1 << l) + 1][k][l],
                       table[x2 - (1 << k) + 1][y2 - (1 << l) + 1][k][l]));
    }
};