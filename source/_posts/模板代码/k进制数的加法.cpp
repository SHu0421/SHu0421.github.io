class Solution {
public:
    string addition(int k, string &a, string &b) {
        // Write your code here
        string sum;
        sum.reserve((a.size() > b.size()) ? a.size() : b.size());
    	int index_a = a.size() - 1;
    	int index_b = b.size() - 1;
    	int bit = 0;
    
    	while (index_a >= 0 && index_b >= 0)
    	{
    		char t = a[index_a] - '0' + b[index_b] - '0' + bit;
    		bit = t / k;
    		sum.push_back(t % k + '0');
    		--index_a;
    		--index_b;
    	}
    
    	if (index_a >= 0)
    	{
    		while (index_a >=0)
    		{
    			char t = (a[index_a] - '0' + bit);
    			bit = t / k;
    			sum.push_back(t % k + '0');
    			--index_a;
    		}
    	}	
    
    	if (index_b >= 0)
    	{
    		while (index_b >= 0)
    		{
    			char t = (b[index_b] - '0' + bit);
    			bit = t / k;
    			sum.push_back(t % k + '0');
    			--index_b;
    		}
    	}
    	
    	if (bit != 0)
    		sum.push_back(bit + '0');
    
    	//去除前导0；
    	while (true)
    	{
    		if (sum[sum.size() - 1] == '0')
    			sum.pop_back();
    		else
    			break;
    	}
    	
    	reverse(sum.begin(), sum.end());
    	return sum;
    }
};