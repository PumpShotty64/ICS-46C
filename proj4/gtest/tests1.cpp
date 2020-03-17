#include "gtest/gtest.h"
#include "MyAVLTree.hpp"
#include "proj4.hpp"
#include <string>
#include <sstream>
#include <iostream>
#include <vector>

namespace{


// NOTE:  these are not intended as exhaustive tests.
// This should get you started testing.

// The four tests marked "CheckPoint" are going to be run
// on your submission for the checkpoint code.
// This is worth one-sixth of your grade on the assignment
// and is due at the time marked "checkpoint"


// None of the "checkpoint" tests require you to have
// AVL functionality OR the counting of words.
// Implementing your tree as a plain binary search
// tree is more than enough to pass these tests.

// Of course, you are expected to implement AVL functionality
// for the full project.

// BE SURE TO FULLY TEST YOUR CODE.
// This means making sure your templating is not hard-coding for 
// a specific type, that every function is called somewhere in 
// your test cases, etc. 
// There will NOT be a project 2 style redo for this;  if your 
//  code does not compile, your score will be a zero. 

TEST(AVLTreeInit, Initialization) {
    MyAVLTree<int, std::string> tree;
    EXPECT_TRUE(tree.size() == 0);
    EXPECT_TRUE(tree.isEmpty());
    EXPECT_FALSE(tree.contains(22));
    EXPECT_THROW(tree.find(22), ElementNotFoundException);
}

TEST(CheckPoint, CheckPoint_FindTheRoot)
{
	MyAVLTree<int, std::string> tree;
	tree.insert(5, "foo");

	EXPECT_TRUE( tree.contains(5) );
}

TEST(CheckPoint, CheckPoint_FindOneHop)
{
	MyAVLTree<int, std::string> tree;
	tree.insert(5, "foo");
	tree.insert(10, "bar");

	EXPECT_TRUE( tree.contains(10) );
}

TEST(CheckPoint, CheckPoint_FindTwoHops)
{
	MyAVLTree<int, std::string> tree;
	tree.insert(5, "foo");
	tree.insert(3, "sna");
	tree.insert(10, "bar");
	tree.insert(12, "twelve");

	EXPECT_TRUE( tree.contains(12) );
}



TEST(CheckPoint, CheckPoint_Add5)
{
	MyAVLTree<int, std::string> tree;
	tree.insert(5, "foo");
	tree.insert(3, "sna");
	tree.insert(10, "bar");
	tree.insert(12, "twelve");
	tree.insert(15, "fifteen");

	EXPECT_TRUE( tree.size() == 5 );
}


TEST(AVLTree, CheckFindAll)
{
	MyAVLTree<int, std::string> tree;
	tree.insert(5, "foo");
	tree.insert(3, "sna");
	tree.insert(10, "bar");
	tree.insert(10, "bar");
	tree.insert(10, "bar");
	tree.insert(10, "bar");
	tree.insert(10, "bar");
	tree.insert(10, "bar");
	tree.insert(12, "twelve");
	tree.insert(15, "fifteen");

    EXPECT_TRUE( tree.contains(5) );
    EXPECT_TRUE( tree.contains(3) );
    EXPECT_TRUE( tree.contains(10) );
    EXPECT_TRUE( tree.contains(12) );
    EXPECT_TRUE( tree.contains(15) );
    EXPECT_FALSE( tree.contains(22) );
    EXPECT_TRUE( tree.find(5) == "foo");
    EXPECT_TRUE( tree.find(3) == "sna" );
    EXPECT_TRUE( tree.find(10) == "bar" );
    EXPECT_TRUE( tree.find(12) == "twelve" );
    EXPECT_TRUE( tree.find(15) == "fifteen" );
	EXPECT_THROW( tree.find(21), ElementNotFoundException);
	EXPECT_TRUE( tree.size() == 5 );
}

TEST(AVLTreeUpdate, RR1)
{
	MyAVLTree<int, std::string> tree;
	tree.insert(5, "foo");
	tree.insert(3, "foo");
	tree.insert(9, "foo");
	tree.insert(7, "sna");
	tree.insert(12, "foo");
	std::vector<int> expected = {3,5,7,9,12};
	std::vector<int> expected2 = {5,3,9,7,12};
	std::vector<int> expected3 = {3,7,12,9,5};
	EXPECT_TRUE(tree.inOrder() == expected );
	EXPECT_TRUE(tree.preOrder() == expected2 );
	EXPECT_TRUE(tree.postOrder() == expected3 );
}

TEST(AVLTreeUpdate, RR2)
{
	MyAVLTree<int, std::string> tree;
	tree.insert(5, "foo");
	tree.insert(3, "foo");
	tree.insert(8, "sna");
	tree.insert(7, "foo");
	tree.insert(9, "foo");
	tree.insert(12, "foo");
	std::vector<int> expected = {3,5,7,8,9,12};
	std::vector<int> expected2 = {8,5,3,7,9,12};
	std::vector<int> expected3 = {3,7,5,12,9,8};
	EXPECT_TRUE(tree.inOrder() == expected );
	EXPECT_TRUE(tree.preOrder() == expected2 );
	EXPECT_TRUE(tree.postOrder() == expected3 );
}

TEST(AVLTreeUpdate, LL1)
{
	MyAVLTree<int, std::string> tree;
	tree.insert(7, "foo");
	tree.insert(3, "foo");
	tree.insert(8, "foo");
	tree.insert(2, "foo");
	tree.insert(1, "foo");
	std::vector<int> expected = {1,2,3,7,8};
	EXPECT_TRUE(tree.inOrder() == expected );
}

TEST(AVLTreeUpdate, LL2)
{
	MyAVLTree<int, std::string> tree;
	tree.insert(7, "foo");
	tree.insert(4, "foo");
	tree.insert(8, "foo");
	tree.insert(5, "foo");
	tree.insert(2, "foo");
	tree.insert(1, "foo");
	std::vector<int> expected = {1,2,4,5,7,8};
	EXPECT_TRUE(tree.inOrder() == expected );
}

TEST(AVLTreeUpdate, RL1)
{
	MyAVLTree<int, std::string> tree;
	tree.insert(5, "foo");
	tree.insert(7, "foo");
	tree.insert(2, "foo");
	tree.insert(1, "foo");
	tree.insert(4, "foo");
	tree.insert(3, "foo");
	std::vector<int> expected = {1,2,3,4,5,7};
	EXPECT_TRUE(tree.inOrder() == expected );
}

TEST(AVLTreeUpdate, RL2)
{
	MyAVLTree<int, std::string> tree;
	tree.insert(5, "foo");
	tree.insert(3, "foo");
	tree.insert(10, "foo");
	tree.insert(12, "foo");
	tree.insert(11, "foo");
	std::vector<int> expected = {3,5,10,11,12};
	EXPECT_TRUE(tree.inOrder() == expected );
}

TEST(AVLTreeUpdate, RL3)
{
	MyAVLTree<int, std::string> tree;
	tree.insert(10, "foo");
	tree.insert(12, "foo");
	tree.insert(5, "foo");
	tree.insert(7, "foo");
	tree.insert(6, "foo");
	std::vector<int> expected = {5,6,7,10,12};
	EXPECT_TRUE(tree.inOrder() == expected );
}

TEST(AVLTreeUpdate, LR1)
{
	MyAVLTree<int, std::string> tree;
	tree.insert(5, "foo");
	tree.insert(3, "foo");
	tree.insert(8, "foo");
	tree.insert(10, "foo");
	tree.insert(6, "foo");
	tree.insert(7, "foo");
	std::vector<int> expected = {3,5,6,7,8,10};
	EXPECT_TRUE(tree.inOrder() == expected );
}

TEST(AVLTreeUpdate, LR2)
{
	MyAVLTree<int, std::string> tree;
	tree.insert(5, "foo");
	tree.insert(3, "foo");
	tree.insert(10, "foo");
	tree.insert(7, "foo");
	tree.insert(8, "foo");
	std::vector<int> expected = {3,5,7,8,10};
	EXPECT_TRUE(tree.inOrder() == expected );
}

TEST(AVLTreeUpdate, LR3)
{
	MyAVLTree<int, std::string> tree;
	tree.insert(10, "foo");
	tree.insert(12, "foo");
	tree.insert(5, "foo");
	tree.insert(3, "foo");
	tree.insert(4, "foo");
	std::vector<int> expected = {3,4,5,10,12};
	EXPECT_TRUE(tree.inOrder() == expected );
}

TEST(AVLTreeUpdate, FinalTest1)
{
	MyAVLTree<int, std::string> tree;
	tree.insert(20, "foo");
	tree.insert(10, "foo");
	tree.insert(18, "foo");
	tree.insert(11, "foo");
	tree.insert(8, "foo");
	tree.insert(9, "foo");
	std::vector<int> expected1 = {8,9,10,11,18,20};
	std::vector<int> expected2 = {10,8,9,18,11,20};
	std::vector<int> expected3 = {9,8,11,20,18,10};
	EXPECT_TRUE( tree.inOrder() == expected1 );
	EXPECT_TRUE( tree.preOrder() == expected2 );
	EXPECT_TRUE( tree.postOrder() == expected3 );
}

TEST(AVLTreeUpdate, FinalTest2)
{
	MyAVLTree<int, std::string> tree;
	tree.insert(20, "foo");
	tree.insert(10, "foo");
	tree.insert(18, "foo");
	tree.insert(11, "foo");
	tree.insert(8, "foo");
	tree.insert(9, "foo");
	tree.insert(5, "foo");
	tree.insert(1, "foo");
	tree.insert(2, "foo");
	tree.insert(4, "foo");
	std::vector<int> expected1 = {1,2,4,5,8,9,10,11,18,20};
	std::vector<int> expected2 = {10,5,2,1,4,8,9,18,11,20};
	std::vector<int> expected3 = {1,4,2,9,8,5,11,20,18,10};
	EXPECT_TRUE( tree.inOrder() == expected1 );
	EXPECT_TRUE( tree.preOrder() == expected2 );
	EXPECT_TRUE( tree.postOrder() == expected3 );
}

TEST(AVLTreeUpdate, FinalTest3)
{
	MyAVLTree<int, std::string> tree;
	tree.insert(20, "foo");
	tree.insert(10, "foo");
	tree.insert(18, "foo");
	tree.insert(11, "foo");
	tree.insert(8, "foo");
	tree.insert(9, "foo");
	tree.insert(5, "foo");
	tree.insert(1, "foo");
	tree.insert(2, "foo");
	tree.insert(4, "foo");
	tree.insert(15, "foo");
	tree.insert(3, "foo");
	tree.insert(16, "foo");
	std::vector<int> expected1 = {1,2,3,4,5,8,9,10,11,15,16,18,20};
	std::vector<int> expected2 = {10,5,2,1,4,3,8,9,18,15,11,16,20};
	std::vector<int> expected3 = {1,3,4,2,9,8,5,11,16,15,20,18,10};
	EXPECT_TRUE( tree.inOrder() == expected1 );
	EXPECT_TRUE( tree.preOrder() == expected2 );
	EXPECT_TRUE( tree.postOrder() == expected3 );
}

TEST(AVLTreeUpdate, FinalTest4)
{
	MyAVLTree<int, std::string> tree;
	tree.insert(20, "foo");
	tree.insert(10, "foo");
	tree.insert(18, "foo");
	tree.insert(11, "foo");
	tree.insert(8, "foo");
	tree.insert(9, "foo");
	tree.insert(5, "foo");
	tree.insert(1, "foo");
	tree.insert(2, "foo");
	tree.insert(4, "foo");
	tree.insert(15, "foo");
	tree.insert(3, "foo");
	tree.insert(16, "foo");
	tree.insert(14, "foo");
	std::vector<int> expected1 = {1,2,3,4,5,8,9,10,11,14,15,16,18,20};
	std::vector<int> expected2 = {10,5,2,1,4,3,8,9,15,11,14,18,16,20};
	std::vector<int> expected3 = {1,3,4,2,9,8,5,14,11,16,20,18,15,10};
	EXPECT_TRUE( tree.inOrder() == expected1 );
	EXPECT_TRUE( tree.preOrder() == expected2 );
	EXPECT_TRUE( tree.postOrder() == expected3 );
}

TEST(PostCheckPoint, InOrderTraversal)
{
	MyAVLTree<int, std::string> tree;
	tree.insert(5, "foo");
	tree.insert(3, "sna");
	tree.insert(10, "bar");
	tree.insert(12, "twelve");
	tree.insert(15, "fifteen");

	std::vector<int> trav = tree.inOrder();
	std::vector<int> expected = {3, 5, 10, 12, 15};
	EXPECT_TRUE( trav == expected );
}



// TEST(PostCheckPoint, JackSparrow)
// {
// 	std::string quote = "I'm dishonest, and a dishonest man you can ";
// 	quote += "always trust to be dishonest. Honestly. It's the honest ";
// 	quote += "ones you want to watch out for, because you can never ";
// 	quote += "predict when they're going to do something incredibly... stupid.";

// 	std::istringstream stream( quote );

// 	MyAVLTree<std::string, unsigned> tree;

// 	countWords(stream, tree);
// 	// std::cout << tree.find("dishonest") << std::endl;
// 	EXPECT_TRUE(tree.find("dishonest") == 3);
// }


// TEST(FunTest, SomebodyToLove)
// {
// 	std::string quote = "Can anybody find me somebody to love? ";
// 				quote +="Ooh, each morning I get up I die a little ";
// 				quote +="Can barely stand on my feet ";
// 				quote +="Take a look in the mirror and cry ";
// 				quote +="Lord, what you're doing to me ";
// 				quote +="I have spent all my years in believing you ";
// 				quote +="But I just can't get no relief, Lord! ";
// 				quote +="Somebody ooh somebody ";
// 				quote +="Can anybody find me somebody to love? ";
// 				quote +="I work hard (he works hard) every day of my life ";
// 				quote +="I work 'til I ache in my bones ";
// 				quote +="At the end ";
// 				quote +="I take home my hard earned pay all on my own ";
// 				quote +="I get down on my knees ";
// 				quote +="And I start to pray ";
// 				quote +="'Til the tears run down from my eyes ";
// 				quote +="Lord, somebody, ooh somebody ";
// 				quote +="can anybody find me somebody to love? ";
// 				quote +="Everyday I try and I try and I try ";
// 				quote +="But everybody wants to put me down ";
// 				quote +="They say I'm going crazy ";
// 				quote +="They say I got a lot of water in my brain ";
// 				quote +="Ah, got no common sense ";
// 				quote +="I got nobody left to believe in ";
// 				quote +="Yeah yeah yeah yeah ";
// 				quote +="Oh, Lord ";
// 				quote +="Ooh somebody, ooh somebody ";
// 				quote +="Can anybody find me somebody to love? ";
// 				quote +="Got no feel, I got no rhythm ";
// 				quote +="I just keep losing my beat ";
// 				quote +="I'm OK, I'm alright ";
// 				quote +="I ain't gonna face no defeat ";
// 				quote +="I just gotta get out of this prison cell ";
// 				quote +="One day I'm gonna be free, Lord! ";
// 				quote +="Find me somebody to love ";
// 				quote +="Find me somebody to love ";
// 				quote +="Find me somebody to love ";
// 				quote +="Find me somebody to love ";
// 				quote +="Find me somebody to love ";
// 				quote +="Find me somebody to love ";
// 				quote +="Find me somebody to love ";
// 				quote +="Find me somebody to love love love ";
// 				quote +="Find me somebody to love ";
// 				quote +="Find me somebody to love ";
// 				quote +="Somebody somebody somebody somebody ";
// 				quote +="Somebody find me ";
// 				quote +="Somebody find me somebody to love ";
// 				quote +="Can anybody find me somebody to love? ";
// 				quote +="Ooh ";
// 				quote +="Find me somebody, somebody somebody, somebody to love ";
// 				quote +="Find me, find me, find me, find me, find me ";
// 				quote +="Ooh, somebody to love  ";
// 				quote +="Ooh ";
// 				quote +="Find me, find me, find me somebody to love  ";
// 				quote +="Anybody, anywhere, anybody find me somebody to love love love! ";
// 				quote +="Somebody find me, find me love";

// 	std::istringstream stream( quote );

// 	MyAVLTree<std::string, unsigned> tree;

// 	countWords(stream, tree);
// 	// std::cout << tree.find("somebody") << std::endl;
// 	EXPECT_EQ(tree.find("somebody"), 36);
// 	EXPECT_EQ(tree.find("find"), 29);
// }

}