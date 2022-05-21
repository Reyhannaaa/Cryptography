#include <bits/stdc++.h>
using namespace std;

unsigned char s_box[256] =
{
	0x63, 0x7C, 0x77, 0x7B, 0xF2, 0x6B, 0x6F, 0xC5, 0x30, 0x01, 0x67, 0x2B, 0xFE, 0xD7, 0xAB, 0x76,
	0xCA, 0x82, 0xC9, 0x7D, 0xFA, 0x59, 0x47, 0xF0, 0xAD, 0xD4, 0xA2, 0xAF, 0x9C, 0xA4, 0x72, 0xC0,
	0xB7, 0xFD, 0x93, 0x26, 0x36, 0x3F, 0xF7, 0xCC, 0x34, 0xA5, 0xE5, 0xF1, 0x71, 0xD8, 0x31, 0x15,
	0x04, 0xC7, 0x23, 0xC3, 0x18, 0x96, 0x05, 0x9A, 0x07, 0x12, 0x80, 0xE2, 0xEB, 0x27, 0xB2, 0x75,
	0x09, 0x83, 0x2C, 0x1A, 0x1B, 0x6E, 0x5A, 0xA0, 0x52, 0x3B, 0xD6, 0xB3, 0x29, 0xE3, 0x2F, 0x84,
	0x53, 0xD1, 0x00, 0xED, 0x20, 0xFC, 0xB1, 0x5B, 0x6A, 0xCB, 0xBE, 0x39, 0x4A, 0x4C, 0x58, 0xCF,
	0xD0, 0xEF, 0xAA, 0xFB, 0x43, 0x4D, 0x33, 0x85, 0x45, 0xF9, 0x02, 0x7F, 0x50, 0x3C, 0x9F, 0xA8,
	0x51, 0xA3, 0x40, 0x8F, 0x92, 0x9D, 0x38, 0xF5, 0xBC, 0xB6, 0xDA, 0x21, 0x10, 0xFF, 0xF3, 0xD2,
	0xCD, 0x0C, 0x13, 0xEC, 0x5F, 0x97, 0x44, 0x17, 0xC4, 0xA7, 0x7E, 0x3D, 0x64, 0x5D, 0x19, 0x73,
	0x60, 0x81, 0x4F, 0xDC, 0x22, 0x2A, 0x90, 0x88, 0x46, 0xEE, 0xB8, 0x14, 0xDE, 0x5E, 0x0B, 0xDB,
	0xE0, 0x32, 0x3A, 0x0A, 0x49, 0x06, 0x24, 0x5C, 0xC2, 0xD3, 0xAC, 0x62, 0x91, 0x95, 0xE4, 0x79,
	0xE7, 0xC8, 0x37, 0x6D, 0x8D, 0xD5, 0x4E, 0xA9, 0x6C, 0x56, 0xF4, 0xEA, 0x65, 0x7A, 0xAE, 0x08,
	0xBA, 0x78, 0x25, 0x2E, 0x1C, 0xA6, 0xB4, 0xC6, 0xE8, 0xDD, 0x74, 0x1F, 0x4B, 0xBD, 0x8B, 0x8A,
	0x70, 0x3E, 0xB5, 0x66, 0x48, 0x03, 0xF6, 0x0E, 0x61, 0x35, 0x57, 0xB9, 0x86, 0xC1, 0x1D, 0x9E,
	0xE1, 0xF8, 0x98, 0x11, 0x69, 0xD9, 0x8E, 0x94, 0x9B, 0x1E, 0x87, 0xE9, 0xCE, 0x55, 0x28, 0xDF,
	0x8C, 0xA1, 0x89, 0x0D, 0xBF, 0xE6, 0x42, 0x68, 0x41, 0x99, 0x2D, 0x0F, 0xB0, 0x54, 0xBB, 0x16
};


void rowsShift(unsigned char * state) {
	unsigned char tmp[16];

tmp[0] = state[0];
tmp[4] = state[4];
tmp[8] = state[8];
tmp[12] = state[12];

tmp[1] = state[5];
tmp[5] = state[9];
tmp[9] = state[13];
tmp[13] = state[1];

tmp[2] = state[10];
tmp[6] = state[14];
tmp[10] = state[2];
tmp[14] = state[6];

tmp[3] = state[15];
tmp[7] = state[3];
tmp[11] = state[7];
tmp[15] = state[11];


	for (int i = 0; i < 16; i++) {
		state[i] = tmp[i];
	}
}

unsigned char gf2pow8(unsigned char c1, unsigned char c2) {
	unsigned char result = 0;
	for(int i = 0; c1 and c2 > 0;i++){
		if (c2 & 1) {
            result ^= c1;
        }
		if (c1 & 0x80){
            //meydane x^4 ...
			c1 = c1 << 1 ;
			c1 ^= 0x11B; 
        }
		else
			c1 <<= 1;
		c2 >>= 1;
	}
	return result;
}


void colsMix(unsigned char * state) {
	unsigned char temp[16];

	temp[0] = (unsigned char)(gf2pow8(state[0], 2) ^ gf2pow8(state[1], 3) ^ state[2] ^ state[3]);
	temp[1] = (unsigned char)(state[0] ^ gf2pow8(state[1], 2) ^ gf2pow8(state[2], 3) ^ state[3]);
	temp[2] = (unsigned char)(state[0] ^ state[1] ^ gf2pow8(state[2], 2) ^ gf2pow8(state[3], 3));
	temp[3] = (unsigned char)(gf2pow8(state[0], 3) ^ state[1] ^ state[2] ^ gf2pow8(state[3], 2));

	temp[4] = (unsigned char)(gf2pow8(state[4], 2) ^ gf2pow8(state[5], 3) ^ state[6] ^ state[7]);
	temp[5] = (unsigned char)(state[4] ^ gf2pow8(state[5], 2) ^ gf2pow8(state[6], 3) ^ state[7]);
	temp[6] = (unsigned char)(state[4] ^ state[5] ^ gf2pow8(state[6], 2) ^ gf2pow8(state[7], 3));
	temp[7] = (unsigned char)(gf2pow8(state[4], 3) ^ state[5] ^ state[6] ^ gf2pow8(state[7], 2));

	temp[8] = (unsigned char)(gf2pow8(state[8], 2) ^ gf2pow8(state[9], 3) ^ state[10] ^ state[11]);
	temp[9] = (unsigned char)(state[8] ^ gf2pow8(state[9], 2) ^ gf2pow8(state[10], 3) ^ state[11]);
	temp[10] = (unsigned char)(state[8] ^ state[9] ^ gf2pow8(state[10], 2) ^ gf2pow8(state[11], 3));
	temp[11] = (unsigned char)(gf2pow8(state[8], 3) ^ state[9] ^ state[10] ^ gf2pow8(state[11], 2));

	temp[12] = (unsigned char)(gf2pow8(state[12], 2) ^ gf2pow8(state[13], 3) ^ state[14] ^ state[15]);
	temp[13] = (unsigned char)(state[12] ^ gf2pow8(state[13], 2) ^ gf2pow8(state[14], 3) ^ state[15]);
	temp[14] = (unsigned char)(state[12] ^ state[13] ^ gf2pow8(state[14], 2) ^ gf2pow8(state[15], 3));
	temp[15] = (unsigned char)(gf2pow8(state[12], 3) ^ state[13] ^ state[14] ^ gf2pow8(state[15], 2));

	for (int i = 0; i < 16; i++) {
		state[i] = temp[i];
	}
}

void Round(unsigned char * state, unsigned char * key) {
	for (int i = 0; i < 16; i++) {
		state[i] = s_box[state[i]];
	}
	rowsShift(state);
	colsMix(state);
for (int i = 0; i < 16; i++) {
		state[i] ^= key[i];
	}
}

void fRound(unsigned char * state, unsigned char * key) {
	for (int i = 0; i < 16; i++) {
		state[i] = s_box[state[i]];
	}
	rowsShift(state);
	for (int i = 0; i < 16; i++) {
		state[i] ^= key[i];
	}
}


unsigned char FRcon(unsigned char r) {
    unsigned char result = 1;
	if (r == 0)
		result = 141;
	else {
    //mohasebe dar meydan
	for (unsigned char i = 1; i < r; i++){
		result = gf2pow8(result, 2);
    }
 }    	
	return result;
}

unsigned char* StrToHex(string str) {
	unordered_map<char, int> hash;
    for(int i=0; i<10; i++)
        hash[i + '0'] = i;
    
    for(int i=0; i<6; i++)
        hash[i + 'a'] = i + 10;
    
	unsigned char* hex = new unsigned char[16];

	for(int i=0; i<16; i++) {
		char evenC = str[i*2];
		char oddC = str[i*2+1];
        //char ha ra b int tabdil mikonim
		int evenInt = hash[evenC];
		int oddInt = hash[oddC];
        //b hex tabdil mikonim
		hex[i] = (16*evenInt) + oddInt;
	}
	return hex;
}

string HexToStr(unsigned char hex[]) {
	unordered_map<char, int> hash;
    for(int i=0; i<10; i++)
        hash[i] = i + '0';
    
    for(int i=0; i<6; i++)
        hash[i + 10] = i + 'a';
    
	string res;
	for(int i=0; i<16; i++) {
		int x = hex[i];
        int b1 = hash[x/16];
        int b2 = hash[x%16];
        res += string(1, b1) + string(1, b2);
	}
	return res;
}

unsigned char* expandKey(unsigned char key[],int n) {

	unsigned char* exp_key = new unsigned char[176];
	for (int i = 0; i < n; i++){ 
		exp_key[i] = key[i];
	}
	
	unsigned char temp[4];
	int cntByte = n;
	int r = 1;
	
	while (cntByte < 176) {
		for (int i = 0; i < 4; i++) 
			temp[i] = exp_key[i + cntByte - 4];
		

		if (cntByte % n == 0) {
            unsigned char t = temp[0];
	        temp[0] = temp[1];
	        temp[1] = temp[2];
	        temp[2] = temp[3];
	        temp[3] = t;

	        temp[0] = s_box[temp[0]];
	        temp[1] = s_box[temp[1]];
	        temp[2] = s_box[temp[2]];
	        temp[3] = s_box[temp[3]];
	        
	
	        temp[0] ^= FRcon(r++);
        }
		

		for (unsigned char a = 0; a < 4; a++) {
			exp_key[cntByte] = exp_key[cntByte - n] ^ temp[a];
			cntByte++;
		}
	}

	return exp_key;
}

string makeSub(string plain_text,int n,int i){
   int minimum = min(n, (i+1)*32);

        string sub_str = plain_text.substr(i*32, minimum);

        minimum = minimum % 32;

		for (int j = 0; minimum != 0 and j < 32-minimum; j++){
			sub_str += "0";
		}
		
	return sub_str;
}

void enc(string plain_text,unsigned char *expkey){
    int n = plain_text.length();
	
    for (int i = 0; i<(n+31)/32; i++){

        string sub_str = makeSub(plain_text,n,i);
	
		unsigned char* text = StrToHex(sub_str);
        unsigned char state[16];
		unsigned char* encryptedtxt = new unsigned char[16];
		
		for (int i = 0; i < 16; i++) 
		state[i] = text[i];
	
	for (int i = 0; i < 16; i++) {
		state[i] ^= expkey[i];
	}

	for (int i = 1; i <= 9; i++) {
	    Round(state,expkey+(16*i));
	}

    fRound(state,expkey+160);
    
	for (int i = 0; i < 16; i++) {
		encryptedtxt[i] = state[i];
	}

		string res = HexToStr(encryptedtxt);
		cout<<res;
	}
}

int main() {
	string key_string;
    string plain_text;

	cin >> key_string;
    cin >> plain_text;

	unsigned char *key = StrToHex(key_string);
	unsigned char *expkey = expandKey(key,16);
	
	enc(plain_text,expkey);

}
