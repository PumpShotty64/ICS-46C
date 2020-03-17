#include "gtest/gtest.h"
#include "proj1.hpp"
#include "ver.hpp" 
#include <map>
#include <string>
#include <stack>


/*
 
Note that this IS NOT a comprehensive set of test cases.
You should still write additional test cases.

This is to get you started and serve as a sanity check.

 */


namespace{

TEST(SimpleCases, PotPanBib){

    std::map<char, unsigned> puzzle;

    bool p1 = puzzleSolver("POT", "PAN", "BIB", puzzle);
    EXPECT_TRUE( p1 &&  gradeYesAnswer("POT", "PAN", "BIB", puzzle) ) ;
}

TEST(SimpleCases, NeatFind){

    std::map<char, unsigned> puzzle;

    bool p1 = puzzleSolver("UCI", "ALEX", "MIKE", puzzle);
    EXPECT_TRUE( p1 &&  gradeYesAnswer("UCI", "ALEX", "MIKE", puzzle) );
} // end test two, "NeatFind"


TEST(SimpleCases, FirstNo){

    std::map<char, unsigned> puzzle;

    bool p1 = puzzleSolver("LARRY", "CAREER", "LEGEND", puzzle);
    EXPECT_FALSE( p1 );
}

TEST(ComplexCases, TenLetters){

    std::map<char, unsigned> puzzle;

    bool p1 = puzzleSolver("XOXOXOXOXOXOXOXOXO", "XOXOXOXOXOXOXOXOXO", "DADADADADADADADADA", puzzle);
    EXPECT_TRUE( p1 &&  gradeYesAnswer("XOXOXOXOXOXOXOXOXO", "XOXOXOXOXOXOXOXOXO", "DADADADADADADADADA", puzzle) );
}

TEST(ComplexCases, SeadBdsbJjep) {
    std::map<char, unsigned> puzzle;

    bool p1 = puzzleSolver("SEAD", "BDSB", "JJEP", puzzle);
    EXPECT_TRUE( p1 &&  gradeYesAnswer("SEAD", "BDSB", "JJEP", puzzle) );
}

TEST(ComplexCases, AbcdBacefJfboc) {
    std::map<char, unsigned> puzzle;

    bool p1 = puzzleSolver("ABCD", "BACEF", "JFBOC", puzzle);
    EXPECT_TRUE( p1 &&  gradeYesAnswer("ABCD", "BACEF", "JFBOC", puzzle) );
}

TEST(ComplexCases, SendMoreMoney) {
    std::map<char, unsigned> puzzle;

    bool p1 = puzzleSolver("SEND", "MORE", "MONEY", puzzle);
    EXPECT_TRUE( p1 &&  gradeYesAnswer("SEND", "MORE", "MONEY", puzzle) );
}

TEST(ComplexCases, AbbCdcHgda) {
    std::map<char, unsigned> puzzle;

    bool p1 = puzzleSolver("ABB", "CDC", "HGDA", puzzle);
    EXPECT_TRUE( p1 &&  gradeYesAnswer("ABB", "CDC", "HGDA", puzzle) );
}

TEST(ComplexCases, UsaNraTax) {
    std::map<char, unsigned> puzzle;

    bool p1 = puzzleSolver("USA", "NRA", "TAX", puzzle);
    EXPECT_TRUE( p1 &&  gradeYesAnswer("USA", "NRA", "TAX", puzzle) );
}

TEST(ComplexCases, UsaFdrNra) {
    std::map<char, unsigned> puzzle;

    bool p1 = puzzleSolver("USA", "FDR", "NRA", puzzle);
    EXPECT_TRUE( p1 &&  gradeYesAnswer("USA", "FDR", "NRA", puzzle) );
}

TEST(ComplexCases, HocusPocusPresto) {
    std::map<char, unsigned> puzzle;

    bool p1 = puzzleSolver("HOCUS", "POCUS", "PRESTO", puzzle);
    
    EXPECT_TRUE( p1 &&  gradeYesAnswer("HOCUS", "POCUS", "PRESTO", puzzle) );
}



TEST(SolutionChecker, Basic3ValueStack) {
    std::stack<int> numStack;
    numStack.push(1);
    numStack.push(2);
    numStack.push(3);
    EXPECT_TRUE(checkSolution(numStack));
}

TEST(SolutionChecker, Basic3ValueStackTens) {
    std::stack<int> numStack;
    numStack.push(9);
    numStack.push(5);
    numStack.push(4);
    EXPECT_TRUE(checkSolution(numStack));
    EXPECT_EQ(numStack.size(), 1);
}

TEST(SolutionChecker, Basic3ValueStackWithCarry) {
    std::stack<int> numStack;
    numStack.push(9);
    numStack.push(5);
    numStack.push(4);
    EXPECT_TRUE(checkSolution(numStack));
    EXPECT_EQ(numStack.size(), 1);
    numStack.push(5);
    numStack.push(3);
    numStack.push(9);
    EXPECT_TRUE(checkSolution(numStack));
    EXPECT_EQ(numStack.size(), 0);
}

TEST(SolutionChecker, UnevenValues) {
    std::stack<int> numStack;
    numStack.push(9);
    numStack.push(9);
    EXPECT_TRUE(checkSolution(numStack));
}

TEST(SolutionChecker, LongCase) {
    std::stack<int> numStack;
    numStack.push(7);
    numStack.push(5);
    numStack.push(2);
    ASSERT_TRUE(checkSolution(numStack));
    numStack.push(6);
    numStack.push(8);
    numStack.push(5);
    ASSERT_TRUE(checkSolution(numStack));
    numStack.push(5);
    numStack.push(0);
    numStack.push(6);
    ASSERT_TRUE(checkSolution(numStack));
    numStack.push(9);
    numStack.push(1);
    numStack.push(0);
    ASSERT_TRUE(checkSolution(numStack));
    numStack.push(1);
    ASSERT_TRUE(checkSolution(numStack));
}

TEST(PrintMap, MapPrints) {
    std::map<char, unsigned> mapping;
    mapping.insert({'A', 100});
    mapping.insert({'B', 200});
    mapping.insert({'C', 300});
    mapping.insert({'D', 400});
    mapping.insert({'E', 500});
    mapping.insert({'F', 600});
    mapping.insert({'G', 700});
    mapping.insert({'A', 200});
    printMap(mapping);
}

TEST(Map, MapHasValue) {
    std::map<char, unsigned> mapping;
    mapping.insert({'A', 100});
    mapping.insert({'B', 200});
    mapping.insert({'C', 300});
    mapping.insert({'D', 400});
    mapping.insert({'E', 500});
    mapping.insert({'F', 600});
    mapping.insert({'G', 700});
    mapping.insert({'A', 200});
    EXPECT_TRUE(hasMapValue(100, mapping));
    EXPECT_TRUE(hasMapValue(400, mapping));
    EXPECT_FALSE(hasMapValue(444, mapping));
}

TEST(Map, MapHasKey) {
    std::map<char, unsigned> mapping;
    mapping.insert({'A', 100});
    mapping.insert({'B', 200});
    mapping.insert({'C', 300});
    mapping.insert({'D', 400});
    mapping.insert({'E', 500});
    mapping.insert({'F', 600});
    mapping.insert({'G', 700});
    mapping.insert({'A', 200});
    EXPECT_TRUE(hasMapKey('F', mapping));
    EXPECT_TRUE(hasMapKey('A', mapping));
    EXPECT_FALSE(hasMapKey('L', mapping));
}

TEST(PossibleSolutions, MaxSize) {
    std::string a = "SEND";
    std::string b = "MORE";
    std::string c = "MONEY";
    EXPECT_EQ(8, maxSolutions(a,b,c));
}

TEST(FinalCheck, CheckingPartOfProblem) {
    std::map<char, unsigned> mapping;
    std::stack<int> numStack;
    std::string s1 = "SEND";
    std::string s2 = "MORE";
    std::string s3 = "MONEY";
    mapping.insert({'D', 7});
    mapping.insert({'E', 5});
    mapping.insert({'M', 1});
    mapping.insert({'N', 6});
    mapping.insert({'O', 0});
    mapping.insert({'R', 8});
    mapping.insert({'S', 9});
    mapping.insert({'Y', 2});
    EXPECT_TRUE(finalCheck(s1, s2, s3, mapping, numStack));
}

} // end namespace
