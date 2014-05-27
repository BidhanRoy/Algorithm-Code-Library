/*
 * Author : Bidhan Roy
 * Required Headers : <string>
 * Range 0 to 4999 . 0 euals to empty string ("")
 * Roman numerals are expressed in uppercase
 * If you find any bug contact me : mail2bidhan@gmail.com
 */

string decimalToRoman( int n ){
    if(n<4) return string(n,'I');
    if(n<6) return string(5-n,'I')+"V";
    if(n<9) return "V"+string(n-5,'I');
    if(n<11) return string(10-n,'I')+"X";
    if(n<40) return string(n/10,'X')+decimalToRoman(n%10);
    if(n<60) return string(5-n/10,'X')+'L'+decimalToRoman(n%10);
    if(n<90) return "L"+string(n/10-5,'X')+decimalToRoman(n%10);
    if(n<110) return string(10-n/10,'X')+"C"+decimalToRoman(n%10);
    if(n<400) return string(n/100,'C')+decimalToRoman(n%100);
    if(n<600) return string(5-n/100,'C')+'D'+decimalToRoman(n%100);
    if(n<900) return "D"+string(n/100-5,'C')+decimalToRoman(n%100);
    if(n<1100) return string(10-n/100,'C')+"M"+decimalToRoman(n%100);
    return string(n/1000,'M')+decimalToRoman(n%1000);
}

int romanToDecimal(string str){
	if(str=="") return 0;
	int res=0,j,m=0;
	string :: iterator p=str.end();
	const char *q;
	for(--p;;p--) {
		for(q="IVXLCDM",j=0;*q;q++,j++) if(*p==*q)
			res+=((j>=m)?m=j,1:-1)*(1+j%4/2*9)*(1+j/4*99)*(1+j%2*4);
		if(p==str.begin()) break;
	}
	return res;
}
