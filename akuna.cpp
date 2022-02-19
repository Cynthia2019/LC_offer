//1 Implement String class 
#include <iostream>
#include <ostream>
#include <string.h>

using namespace std; 
class String {
    public: 
        //dufault constructor
        String() : buf(nullptr), size(0) {}; 
        //constructor with param 
        String(char* buffer) {
            //get the size of buffer
            size = strlen(buffer); 
            buf = new char[size + 1]; //allocate these many space for buf
            strcpy(buf, buffer); //safe copy the buffer into this->buf
        }
        //copy constructor 
        String(String& other){
            size = other.size; 
            buf = new char[size + 1]; 
            strcpy(buf, other.buf);
        }
        //Destructor
        ~String() {
            delete buf; 
        }
        //oprator
        // = 
        String& operator= (const String& other) {
            size = strlen(other.buf);
            buf = new char[size + 1]; 
            strcpy(buf, other.buf); 
            return *this; 
        };
        const char* c_str() const {
            return buf; 
        }
        //operator +
        friend String operator+ (const String& obj, const String& other) {
            String s;
            s.size = obj.size + other.size; 
            s.buf = new char[s.size + 1];  
            strcpy(s.buf, obj.buf); 
            strcpy(s.buf + obj.size, other.buf);
            return s; 
        }
        // //output String 
        friend ostream& operator<< (ostream& os, const String& obj) {
            os << obj.c_str(); 
            return os;
        }

        //operator == 
        friend bool operator== (const String& obj, const String& other) {
            if(obj.size != other.size) return false; 
            for(int i = 0; i < obj.size; i++){
                if(obj.buf[i] != other.buf[i]) return false; 
            }
            return true;
        }

        //operation += non friend
        String operator+= (const String& other) {
            char* old = buf; 
            int64_t oldSize = size; 
            size += strlen(other.buf); 
            buf = new char[size + 1]; 
            strcpy(buf, old); 
            cout << "size: " << size << endl;
            strcpy(buf + oldSize, other.buf); 
            return *this;
        }
    private: 
        //char buffer to hold data
        char* buf; 
        //hold size of data
        int64_t size; 
};

int main() {
    String s1;
    char buffer[10] = "hello"; 
    String s2(buffer);
    char c3[10] = " world";
    String s3(c3); 
    cout << s2 << endl;;
    cout << s2 + s3 << endl;
    String s4; 
    s4 = s2 + s3; 
    cout << s4 << endl ;
    String s5(s4); 
    cout << s5 << endl;
    cout << (s4 == s5) << endl;
    s4 += s5; 
    cout << s4 << endl;
}