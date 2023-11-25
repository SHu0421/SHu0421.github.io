// 中文变为阿拉伯数字和阿拉伯数字变为中文
//     1.中文变为阿拉伯数字
//     使用栈，将文字划分为数字和量纲，遇到量纲，那么从栈中弹出与当前量纲小的数字与当前量纲相乘，然后不断累加，知道栈为空或者栈顶量纲比当前量纲大，然后将当前累加到的数压入栈中；最后的结果就是栈中的数求和
    
package problem;

import java.util.Scanner;
import java.util.Stack;

public class Test {

    public static void main(String[] args) {
        String aval = "零一二三四五六七八九";
        String bval = "十百千万亿";
        int[] bnum = {10, 100, 1000, 10000, 100000000};
        Scanner sc = new Scanner(System.in);
        while (sc.hasNext()) {
            long num = 0;
            String str = sc.next();
            char[] arr = str.toCharArray();
            int len = arr.length;
            Stack<Integer> stack = new Stack<Integer>();
            for (int i = 0; i < len; i++) {
                char s = arr[i];
                //跳过零
                if(s == '零')continue;
                //用下标找到对应数字
                int index = bval.indexOf(s);
                //如果不在bval中，即当前字符为数字，直接入栈
                if(index == -1){
                    stack.push(aval.indexOf(s));
                }else{ //当前字符为单位。
                    int tempsum = 0;
                    int val = bnum[index];
                    //如果栈为空则直接入栈
                    if(stack.isEmpty()){
                        stack.push(val);
                        continue;
                    }
                    //如果栈中有比val小的元素则出栈，累加，乘N，再入栈
                    while(!stack.isEmpty() && stack.peek() < val){
                        tempsum += stack.pop();
                    }
                    //判断是否经过乘法处理
                    if(tempsum == 0){
                        stack.push(val);
                    }else{
                        stack.push(tempsum * val);
                    }
                }
            }
            //计算最终的和
            while(!stack.isEmpty()){
                num += stack.pop();
            }
            System.out.println(num);
        }
    }

}

    // 2.阿拉伯数字变为中文
    // 每节和多节都是从后往前进行处理
    // 注意：亿，万节之后如果只有0那么不需要输出0，如果千位为0的话那么需要输出0
    // 10500，一万零五百， 15000一万五千
    
    // 将数组划分为节，然后每节使用一个函数判断， 中文是从后往前进行完善
    // 如果不是第一节，而且当前的数是大于0，而且小于1000的话那么需要加零
    // 如果一个节为0，那么不加零 1 0000 0500； 1 0000 5000 一亿五千还是一亿零五千，一亿五百，还是一亿零五百 
    //可以从后面向前面判断，不用从后往前

    const char *DIGITS_TO_CHINESE[] = {"零","一","二","三","四","五","六","七","八","九"};
    const char *SECTION_Units[] = {"", "万","亿","万亿","亿亿"};
    const char *BIT_UNITS[] = {"", "十","百","千"};

    void SectionNum2Chinese(uint64_t section, std::string& chinese) {
        std::string bit_chinese;
        int bit_index = 0;
        bool has_non_zero_before = false;
        bool added_zero = false;
        //不管是每节，还是节里面的数据，都是从后往前进行添加
        while(section > 0) {
            int bit_value = section % 10;
            if(bit_value == 0) {
                // If there's non zero digit before and "零" hasn't been added.
                // There's only one "零" within one single section.
                if(has_non_zero_before && !added_zero) {
                    added_zero = true;
                    chinese.insert(0, DIGITS_TO_CHINESE[0]);
                }
            } else {
                has_non_zero_before = true;
                // Convert the bit digit to chinese.
                bit_chinese = DIGITS_TO_CHINESE[bit_value];
                // Append bit unit to the bit chinese.
                bit_chinese += BIT_UNITS[bit_index];
                // Append the bit chinese result to the section chinese result to the front.
                chinese.insert(0, bit_chinese);
            }

            bit_index++;
            section = section / 10;
        }
    }
    void Number2Chinese(uint64_t num, std::string& chinese)
    {
        // Special case: if num == 0, then return "零".
        if (num == 0) {
            chinese = "零";
            return;
        }
        int section_index = 0;
        bool need_add_zero = false;
        while (num > 0) {
            // Append "零" to the front if needed.
            if(need_add_zero) {
                chinese.insert(0, DIGITS_TO_CHINESE[0]);
            }

            // Get section value.
            uint64_t section_value = num % 10000;

            // Convert section value to section chinese.
            std::string section_chinese = "";
            SectionNum2Chinese(section_value, section_chinese);

            // Append the section unit to the tail if needed.
            section_chinese += (section_value != 0) ? SECTION_Units[section_index] : SECTION_Units[0];

            // Append the section chinese to the result's front.
            chinese.insert(0, section_chinese);

            // Check whether need to add "零", will add at the beginning of next round if needed.
            need_add_zero = (section_value < 1000) && (section_value > 0);

            num = num / 10000;
            section_index++;
        }
    }


//阿拉伯数字转为英文
//这个和转为中文的区别在于不需要加上0，因此在处理节的时候可以使用递归处理，同时可以从前往后，因为不需要判断加不加0
class Solution {
public:
    string res;
    vector<string> singles = {"", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine"};
    vector<string> teens = {"Ten", "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen"};
    vector<string> tens = {"", "Ten", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"};
    vector<string> thousands = {"", "Thousand", "Million", "Billion"};
    void recursive(int num){
        if(num==0){
            return ;
        }else if(num<10){
            res+=" "+singles[num];
        }else if(num<20){
            res+=" "+teens[num-10];
        }else if(num<100){
            res+=" "+tens[num/10];
            num=num%10;
            recursive(num);
        }else{
            res+=" "+singles[num/100]+" Hundred";
            num=num%100;
            recursive(num);
        }
        return;
    }
    string numberToWords(int num) {
        
        if(num==0){
            return "Zero";
        }
        int i=3;
        for(int j=1000000000; j>0&&i>=0;j/=1000){
            if(num>=j){
                recursive(num/j);
                if(j>1){
                    res+=" "+thousands[i];
                }
                num=num-num/j*j;
            }
            i--;
        }
        i=0;
        while(res[i]==' '){
            i++;
        }//去掉可能多加的0

        return res.substr(i);
    }
};

