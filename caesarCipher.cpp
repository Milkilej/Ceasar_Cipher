#include <iostream>
#include <sstream>
#include <vector>

struct TestCase { std::string name{}; std::ostringstream failures{}; };
template <typename T> void operator | (TestCase& testCase, T&& testBody) {
    testBody(); auto failures = testCase.failures.str();
    if (failures.empty()) std::cout << testCase.name << ": SUCCESS\n";
    else std::cerr << testCase.name << ": FAILURE\n" << failures;
}
void addFailure(std::ostream& os, const char* file, unsigned line, const char* condition) {
    os << file << ":" << line << ": Failed: " << condition << "\n";
}

#define TEST(name) TestCase name{#name}; name | [&, &failures = name.failures]
#define EXPECT(cond) if (cond) {} else addFailure(failures, __FILE__, __LINE__, #cond)
#define ASSERT(cond) if (cond) {} else return addFailure(failures, __FILE__, __LINE__, #cond)

class Encoder{
    std::string input;
    std::string output{};
    int shift; 
    const int pos_a = 97; 
    const int pos_z = 122;
    const int pos_A = 65; 
    const int pos_Z = 90;
    const int pos_0 = 48;
    const int pos_9 = 57;
    
    public:
    char changeChar(char c)
    {
        if(isdigit(c))
        {
            shift %= 10;
            if(c+shift > pos_9)
            {
                    return char(c%+pos_0);
                    }
                    if(c+shift < pos_0)
                    {
                    return char(pos_9-c%pos_0);
                    }
        }else if(isalpha(c)){
            if (isupper(c))
            {
                    if(c+shift > pos_Z)
                    {
                        std::cout<<"print"<<(c%pos_Z)<<std::endl; 
                        std::cout<< c+shift<<std::endl;
                        std::cout<< "result: "<<(c+shift+pos_A)%pos_Z<<std::endl;
                        return char((c+shift)%pos_Z);
                    }
                    if(c+shift < pos_A)
                    {
                        std::cout<<"print"<<(pos_Z-c%pos_A)<<std::endl;
                        return char(pos_Z-c%pos_A);
                    }
            }
            else 
            {
                    if(c+shift > pos_z)
                    {
                    return char(c%pos_z+pos_a);
                    }
                    if(c+shift < pos_a)
                    {
                    return char(pos_z-c%pos_a);
                    }
            }
        }else{
            return c;
        }
        
        return c+shift;
    }
    Encoder(const std::string& _input, const int _shift):input(_input), shift(_shift){};
    std::string getCaesarCypher()
    {
        for(char& c : input)
        {
            output += changeChar(c);
        }
        return output;
    }
};

int main() 
{
    TEST(WhenGivenTextShift30ReturnText)
    {
       std::string text = "a";
        Encoder encoder(text, 30);
        std::cout << encoder.getCaesarCypher() << std::endl;
        int a = encoder.changeChar('a');
        std::cout << a << std::endl;
        EXPECT(encoder.getCaesarCypher()=="d");
        std::string text = "B";
        Encoder encoder(text, 25);
        EXPECT(encoder.getCaesarCypher()=="A");
    };
    TEST(WhenGivenSpaceWithAnyShiftReturnSpace)
    {
        std::string text = " ";
        Encoder encoder(text, 1);
        EXPECT(encoder.getCaesarCypher()==" ");
    };
    TEST(WhenGivenDotWithAnyShiftReturnDot)
    {
        std::string text = ".";
        Encoder encoder(text, 1);
        EXPECT(encoder.getCaesarCypher()==".");
    };
    TEST(WhenGivenNumberOneWithOneShiftReturnResultTwo)
    {
        std::string text = "1";
        Encoder encoder(text, 1);
        EXPECT(encoder.getCaesarCypher()=="2");
    };
    TEST(WhenGivenUpperStringWith1ShiftReturnChangedProperlyString)
    {
        std::string text = "Z";
        Encoder encoder(text, 1);
        EXPECT(encoder.getCaesarCypher()=="A");
    };
    
    TEST(WhenGivenStringWithNegative1ShiftReturnChangedProperlyString)
    {
        std::string text = "a";
        Encoder encoder(text, -1);
        EXPECT(encoder.getCaesarCypher()=="z");
    };
    TEST(WhenGivenStringWith1ShiftReturnChangedProperlyString)
    {
        std::string text = "z";
        Encoder encoder(text, 1);
        EXPECT(encoder.getCaesarCypher()=="a");
    };

    TEST(WhenGivenEmptyStringReturnEmptyString)
    {
        std::string text = "";
        Encoder encoder(text, 0);
        EXPECT(encoder.getCaesarCypher()=="");
    };

    TEST(WhenGivenStringWith0ShiftReturnTheSameString)
    {
        std::string text = "abc";
        Encoder encoder(text, 0);
        EXPECT(encoder.getCaesarCypher()=="abc");
    };

    TEST(WhenGivenCharWithGivenShiftReturnChangedChar)
    {
        std::string text = "a";
        Encoder encoder(text, 1);
        EXPECT(encoder.getCaesarCypher()=="b");
    };

    TEST(stdVectorAddsElement)
    {
        vv.push_back(1);
        EXPECT(not vv.empty());
        EXPECT(vv.size() == 1);
        EXPECT(vv.front() == 2);
        EXPECT(*vv.begin() == 2);
    };
}
