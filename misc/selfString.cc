#include <utility>
#include <stdio.h>
#include <string.h>
 
 
class String
{
    public:
        String() : data_(new char[1])
        {
            data_ = '\0';
        }
 
        String(const char* str)
          : data_(new char[strlen(str) + 1])
        {
            strcpy(data_, str);
        }
 
        String(const String& rhs)
          : data_(new char[rhs.size() + 1])
        {
            strcpy(data_, rhs.c_str());
        }
 
        ~String()
        {
            delete[] data_;
        }
 
        String& operator=(String rhs)
        {
            swap(rhs);
            return *this;
        }
 
        bool operator==(const String &rhs)
        {
            return this == &rhs || 0 == strcmp(data_, rhs.data_);
        }
 
        char operator[](size_t idx)
        {
            return (strlen(data_) < idx) ? '\0' : *(data_ + idx);
        }
 
 
        size_t size() const
        {
            return strlen(data_);
        }
 
        void swap(String& rhs)
        {
            std::swap(data_, rhs.data_);
        }
 
        const char* c_str() const
        {
            return data_;
        }
 
    private:
        char* data_;
};
 
int main()
{
    String s0;
    String s1("helloworld");
    String s2 = s1;
    String s3("hello");
    String s4("helloaorld");
    printf("%s\n", s1.c_str());
    printf("%s\n", s2.c_str());
 
    if (s1 == s1)
    printf("s1 == s1\n");
    else
    printf("s1 != s1\n");
 
    if (s1 == s2)
    printf("s1 == s2\n");
    else
    printf("s1 != s2\n");
 
    if (s3 == s1)
    printf("s1 == s3\n");
    else
    printf("s1 != s3\n");
 
    if (s1 == s4)
    printf("s1 == s4\n");
    else
    printf("s1 != s4\n");
 
    for(size_t i = 0; i <= s3.size(); ++i)
    printf("%c", s3[i]);
 
    printf("%c", s3[s3.size()]);
    printf("\n");
}
