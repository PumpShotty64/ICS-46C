#include "gtest/gtest.h"
#include "LLQueue.hpp"
#include "proj2.hpp"
#include <iostream>


namespace{


// NOTE:  these are not intended as exhaustive tests.
	// This should get you started testing.
	// You should make your own additional tests for both queue
	// and for the social network question.
	// VERY IMPORTANT:  if your LLQueue is not templated, or if 
	//		it is not linked-list based, your score for this project
	//		will be zero.  Be sure your LLQueue compiles and runs 
	// 		with non-numeric data types. 

TEST(QueueTest, QueueTest1)
{
	LLQueue<int> a;
	a.enqueue(5);
	EXPECT_TRUE( a.front() == 5 );
}

TEST(QueueTest, QueueTest2)
{
	LLQueue<int> a;
	a.enqueue(5);
	a.enqueue(3);
	EXPECT_TRUE( a.front() == 5 );
}


TEST(QueueTest, QueueTest3)
{
	LLQueue<int> a;
	a.enqueue(5);
	a.enqueue(3);
	a.dequeue();
	EXPECT_TRUE( a.front() == 3 );
}

TEST(QueueTest, QueueTest4)
{
	LLQueue<int> a;
	a.enqueue(5);
	a.enqueue(3);
	EXPECT_EQ(a.size(), 2);
	a.dequeue();
	EXPECT_EQ(a.size(), 1);
}

TEST(QueueTest, QueueTest5)
{
	LLQueue<int> a;
	a.enqueue(5);
	a.enqueue(3);
	EXPECT_FALSE( a.isEmpty() );
	a.dequeue();
	a.dequeue();
	EXPECT_ANY_THROW(a.dequeue());
}

TEST(QueueTest, QueueTest6)
{
	LLQueue<int> a;
	a.enqueue(5);
	a.enqueue(3);
	EXPECT_FALSE( a.isEmpty() );
	a.dequeue();
	a.dequeue();
	EXPECT_ANY_THROW(a.front());
}

TEST(QueueTest, QueueTest67)
{
	LLQueue<int> a;
	std::cout << "QT67 line 1" << std::endl;
	EXPECT_TRUE( a.isEmpty() );
	std::cout << "QT67 line 2" << std::endl;
	EXPECT_ANY_THROW(a.front());
	std::cout << "Watch this" << std::endl; 
}

TEST(QueueTest, QueueTest7)
{
	LLQueue<int> a;
	a.enqueue(5);
	a.enqueue(3);
	EXPECT_FALSE( a.isEmpty() );
	a.dequeue();
	a.enqueue(6);
	EXPECT_EQ( a.front(), 3);
}

TEST(QueueTest, QueueString1)
{
	LLQueue<char> a;
	a.enqueue('b');
	EXPECT_TRUE( a.front() == 'b' );
}

TEST(QueueTest, QueueString2)
{
	LLQueue<char> a;
	a.enqueue('b');
	a.enqueue('a');
	EXPECT_TRUE( a.front() == 'b' );
}


TEST(QueueTest, QueueString3)
{
	LLQueue<char> a;
	a.enqueue('b');
	a.enqueue('a');
	a.dequeue();
	EXPECT_TRUE( a.front() == 'a' );
}


TEST(GraphTest, GraphTest1)
{
	std::vector< std::vector<unsigned> > g1 = {
		{1,2}, {0,3}, {0,3}, {1,2}
	};
	std::vector<unsigned> pathLengths(4);
	std::vector<unsigned> numShortestPaths(4);
	
	countPaths(g1, 0, pathLengths, numShortestPaths);

	std::vector<unsigned> expPathLengths = {0, 1, 1, 2};
	std::vector<unsigned> expNumSP = {1, 1, 1, 2};

	EXPECT_TRUE(pathLengths == expPathLengths && expNumSP == numShortestPaths);

}


TEST(GraphTest, GraphTest2)
{
	std::vector< std::vector<unsigned> > g1 = {
		{1, 2, 4}, {0,3}, {0,3}, {1,2,5}, {0, 5}, {3, 4}
	};
	
	std::vector<unsigned> pathLengths(6);
	std::vector<unsigned> numShortestPaths(6);
	
	countPaths(g1, 0, pathLengths, numShortestPaths);

	std::vector<unsigned> expPathLengths = {0, 1, 1, 2, 1, 2};
	std::vector<unsigned> expNumSP = {1, 1, 1, 2, 1, 1};

	EXPECT_TRUE(pathLengths == expPathLengths && expNumSP == numShortestPaths);
}

TEST(GraphTest, GraphTest3)
{
	std::vector< std::vector<unsigned> > g1 = {
		{1, 2, 4}, {0,3}, {0,3}, {1,2,5,7}, {0, 5, 6}, {3, 4}, {4, 7}, {3, 6},
	};
	
	std::vector<unsigned> pathLengths(8);
	std::vector<unsigned> numShortestPaths(8);
	
	countPaths(g1, 0, pathLengths, numShortestPaths);

	std::vector<unsigned> expPathLengths = {0, 1, 1, 2, 1, 2, 2, 3};
	std::vector<unsigned> expNumSP = {1, 1, 1, 2, 1, 1, 1, 3};

	EXPECT_TRUE(pathLengths == expPathLengths && expNumSP == numShortestPaths);

}

TEST(GraphTest, GraphTest4)
{
	std::vector< std::vector<unsigned> > g1 = {
		{1, 2, 4}, {0,3}, {0,3}, {1,2,5,6,7}, {0, 5}, {3, 4}, {3,7,8}, {3,6,8}, {6,7}
	};
	
	std::vector<unsigned> pathLengths(9);
	std::vector<unsigned> numShortestPaths(9);
	
	countPaths(g1, 0, pathLengths, numShortestPaths);

	std::vector<unsigned> expPathLengths = {0, 1, 1, 2, 1, 2, 3, 3, 4};
	std::vector<unsigned> expNumSP = {1, 1, 1, 2, 1, 1, 2, 2, 4};

	EXPECT_TRUE(pathLengths == expPathLengths && expNumSP == numShortestPaths);
}

TEST(GraphTest, GraphTest5)
{
	std::vector< std::vector<unsigned> > g1 = {
		{1, 2, 4}, {0,3}, {0,3,5}, {1,2,8}, {0, 6}, {2,6,7}, {4,5,7}, {5,6}, {3}
	};
	
	std::vector<unsigned> pathLengths(9);
	std::vector<unsigned> numShortestPaths(9);
	
	countPaths(g1, 0, pathLengths, numShortestPaths);

	std::vector<unsigned> expPathLengths = {0, 1, 1, 2, 1, 2, 2, 3, 3};
	std::vector<unsigned> expNumSP = {1, 1, 1, 2, 1, 1, 1, 2, 2};

	EXPECT_TRUE(pathLengths == expPathLengths && expNumSP == numShortestPaths);
}

TEST(GraphTest, GraphTest6)
{
	std::vector< std::vector<unsigned> > g1 = {
		{1, 2, 4}, {0,3}, {0,3,5}, {1,2,8}, {0, 6}, {2,6,7}, {4,5,7}, {5,6}, {3}
	};
	
	std::vector<unsigned> pathLengths(9);
	std::vector<unsigned> numShortestPaths(9);
	
	countPaths(g1, 5, pathLengths, numShortestPaths);

	std::vector<unsigned> expPathLengths = {2, 3, 1, 2, 2, 0, 1, 1, 3};
	std::vector<unsigned> expNumSP = {1, 2, 1, 1, 1, 1, 1, 1, 1};

	EXPECT_TRUE(pathLengths == expPathLengths && expNumSP == numShortestPaths);
}




} // end namespace
