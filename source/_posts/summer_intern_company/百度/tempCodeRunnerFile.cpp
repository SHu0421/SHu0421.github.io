         for (int i = 1; i+len-1 <= size;i++){
                unordered_map<int, vector<vector<int> > > hash;
                int j = i + len - 1;
                int tmp = presum[j] - presum[i - 1];
                hash[tmp].push_back({i, j});
                if(hash[tmp].size()>=2){
                    cout<<hash[tmp][0][0]<<" "<<hash[tmp][0][1]<<" "<<hash[tmp][1][0]<<" "<<hash[tmp][1][1]<<endl;
                }
        }