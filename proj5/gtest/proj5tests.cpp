#include <vector>
#include <gtest/gtest.h>
#include "proj5.hpp"
#include "MyPriorityQueue.hpp"
#include "../include/ver.hpp"

namespace{

// As always, this is a STARTING POINT of test cases
	// and is not an exhaustive set of test cases.
	// You should be sure to test EVERY function of 
	// your priority queue as well as the creation of MSTs.l

TEST(PriorityQueueTest, initialization)
{
	MyPriorityQueue<int> mpq;
	EXPECT_TRUE(mpq.isEmpty());
	EXPECT_TRUE(mpq.size() == 0);
	EXPECT_ANY_THROW(mpq.min());
}


TEST(PriorityQueueTest, checkpoint0)
{
	MyPriorityQueue<int> mpq;
	EXPECT_TRUE(mpq.isEmpty());
	mpq.insert(10);
	mpq.insert(15);
	EXPECT_TRUE(mpq.min() == 10);
}

TEST(PriorityQueueTest, checkpoint1)
{
	MyPriorityQueue<int> mpq;
	EXPECT_TRUE(mpq.isEmpty());
	mpq.insert(10);
	mpq.insert(15);
	mpq.insert(9);
	EXPECT_TRUE(mpq.min() == 9);
}

TEST(PriorityQueueTest, checkpoint2)
{
	MyPriorityQueue<int> mpq;
	EXPECT_TRUE(mpq.isEmpty());
	mpq.insert(10);
	mpq.insert(15);
	mpq.insert(9);
	mpq.insert(20);
	EXPECT_TRUE(mpq.min() == 9);
}

TEST(PriorityQueueTest, checkpoint3)
{
	MyPriorityQueue<int> mpq;
	EXPECT_TRUE(mpq.isEmpty());
	mpq.insert(10);
	mpq.insert(15);
	mpq.insert(9);
	mpq.insert(20);
	mpq.insert(5);
	EXPECT_TRUE(mpq.min() == 5);
}

TEST(PriorityQueueTest, checkpoint4)
{
	MyPriorityQueue<int> mpq;
	EXPECT_TRUE(mpq.isEmpty());
	mpq.insert(10);
	mpq.insert(15);
	mpq.insert(9);
	mpq.insert(20);
	mpq.insert(5);
	mpq.insert(3);
	EXPECT_TRUE(mpq.min() == 3);
	EXPECT_TRUE(mpq.size() == 6);
}

TEST(PriorityQueueTest, checksamevalues)
{
	MyPriorityQueue<int> mpq;
	EXPECT_TRUE(mpq.isEmpty());
	mpq.insert(10);
	mpq.insert(15);
	mpq.insert(9);
	mpq.insert(20);
	mpq.insert(5);
	mpq.insert(3);
	mpq.insert(20);
	mpq.insert(15);
	mpq.insert(3);
	mpq.insert(9);
	EXPECT_TRUE(mpq.min() == 3);
	EXPECT_TRUE(mpq.size() == 10);
}

TEST(PriorityQueueTest, removingvalues)
{
	MyPriorityQueue<int> mpq;
	EXPECT_TRUE(mpq.isEmpty());
	mpq.insert(10);
	mpq.insert(15);
	mpq.insert(9);
	mpq.insert(20);
	mpq.insert(5);
	mpq.insert(3);
	mpq.insert(20);
	mpq.insert(15);
	mpq.insert(3);
	mpq.insert(9);
	mpq.extractMin();
	EXPECT_TRUE(mpq.min() == 3);
	mpq.extractMin();
	EXPECT_TRUE(mpq.min() == 5);
	mpq.extractMin();
	EXPECT_TRUE(mpq.min() == 9);
	mpq.extractMin();
	EXPECT_TRUE(mpq.min() == 9);
	mpq.extractMin();
	EXPECT_TRUE(mpq.size() == 5);
	EXPECT_TRUE(mpq.min() == 10);
}

TEST(PriorityQueueTest, finalCheck)
{
	MyPriorityQueue<int> mpq;
	EXPECT_TRUE(mpq.isEmpty());
	mpq.insert(12);
	mpq.insert(12);
	mpq.insert(13);
	mpq.insert(17);
	mpq.insert(9);
	mpq.insert(7);
	mpq.insert(14);
	mpq.insert(3);
	mpq.insert(17);
	EXPECT_TRUE(mpq.min() == 3);
	mpq.extractMin();
	EXPECT_TRUE(mpq.min() == 7);
	mpq.extractMin();
	EXPECT_TRUE(mpq.min() == 9);
	mpq.extractMin();
	EXPECT_TRUE(mpq.min() == 12);
	mpq.extractMin();
	EXPECT_TRUE(mpq.min() == 12);
	mpq.extractMin();
	EXPECT_TRUE(mpq.min() == 13);
	mpq.extractMin();
	EXPECT_TRUE(mpq.min() == 14);
	mpq.extractMin();
	EXPECT_TRUE(mpq.min() == 17);
	mpq.extractMin();
	EXPECT_TRUE(mpq.min() == 17);
	mpq.extractMin();
	EXPECT_TRUE(mpq.isEmpty());
}


TEST(SampleTests, SimplePQ)
{
	MyPriorityQueue<int> mpq;
	mpq.insert(3);
	EXPECT_TRUE(mpq.min() == 3);
}

TEST(SampleTests, MSTn10)
{
	std::vector< std::vector< unsigned>  > gr = { 
		{ 0, 12, 12, 13, 17, 9, 7, 14, 3, 17},
		{ 12, 0, 8, 8, 8, 18, 19, 5, 15, 8},
		{ 12, 8, 0, 12, 15, 19, 17, 12, 9, 8},
		{ 13, 8, 12, 0, 6, 15, 14, 3, 10, 4},
		{ 17, 8, 15, 6, 0, 21, 19, 3, 14, 10},
		{ 9, 18, 19, 15, 21, 0, 11, 18, 10, 11},
		{ 7, 19, 17, 14, 19, 11, 0, 17, 10, 18},
		{ 14, 5, 12, 3, 3, 18, 17, 0, 11, 7},
		{ 3, 15, 9, 10, 14, 10, 10, 11, 0, 14},
		{ 17, 8, 8, 4, 10, 11, 18, 7, 14, 0}
	};

	std::vector<Edge> mst = compute_mst(gr);
	EXPECT_TRUE( verifyMST(mst, gr) );
}
TEST(SampleTests, MSTn20)
{
	std::vector< std::vector< unsigned>  > gr = { 
		{ 0, 8, 14, 10, 9, 8, 7, 6, 3, 12, 6, 10, 11, 9, 13, 5, 8, 8, 9, 13},
		{ 8, 0, 12, 11, 6, 6, 8, 9, 6, 11, 3, 10, 4, 12, 11, 3, 11, 7, 7, 12},
		{ 14, 12, 0, 10, 11, 16, 12, 13, 11, 9, 14, 16, 8, 12, 9, 15, 15, 11, 10, 5},
		{ 10, 11, 10, 0, 6, 14, 3, 13, 11, 10, 9, 9, 13, 16, 11, 11, 6, 10, 10, 10},
		{ 9, 6, 11, 6, 0, 11, 9, 7, 6, 12, 3, 12, 10, 10, 8, 9, 11, 8, 4, 12},
		{ 8, 6, 16, 14, 11, 0, 11, 11, 11, 13, 8, 8, 8, 14, 9, 3, 15, 11, 8, 11},
		{ 7, 8, 12, 3, 9, 11, 0, 13, 10, 11, 11, 6, 10, 14, 8, 8, 9, 7, 11, 7},
		{ 6, 9, 13, 13, 7, 11, 13, 0, 3, 11, 6, 15, 10, 3, 7, 11, 8, 7, 3, 10},
		{ 3, 6, 11, 11, 6, 11, 10, 3, 0, 14, 3, 12, 10, 6, 10, 8, 5, 10, 6, 10},
		{ 12, 11, 9, 10, 12, 13, 11, 11, 14, 0, 12, 10, 7, 14, 12, 14, 14, 4, 8, 7},
		{ 6, 3, 14, 9, 3, 8, 11, 6, 3, 12, 0, 12, 7, 9, 8, 6, 8, 8, 4, 9},
		{ 10, 10, 16, 9, 12, 8, 6, 15, 12, 10, 12, 0, 14, 18, 12, 11, 15, 13, 16, 13},
		{ 11, 4, 8, 13, 10, 8, 10, 10, 10, 7, 7, 14, 0, 13, 11, 7, 7, 3, 7, 13},
		{ 9, 12, 12, 16, 10, 14, 14, 3, 6, 14, 9, 18, 13, 0, 10, 14, 11, 10, 6, 7},
		{ 13, 11, 9, 11, 8, 9, 8, 7, 10, 12, 8, 12, 11, 10, 0, 12, 7, 8, 4, 14},
		{ 5, 3, 15, 11, 9, 3, 8, 11, 8, 14, 6, 11, 7, 14, 12, 0, 13, 10, 10, 14},
		{ 8, 11, 15, 6, 11, 15, 9, 8, 5, 14, 8, 15, 7, 11, 7, 13, 0, 10, 11, 15},
		{ 8, 7, 11, 10, 8, 11, 7, 7, 10, 4, 8, 13, 3, 10, 8, 10, 10, 0, 4, 11},
		{ 9, 7, 10, 10, 4, 8, 11, 3, 6, 8, 4, 16, 7, 6, 4, 10, 11, 4, 0, 13},
		{ 13, 12, 5, 10, 12, 11, 7, 10, 10, 7, 9, 13, 13, 7, 14, 14, 15, 11, 13, 0}
	};

	std::vector<Edge> mst = compute_mst(gr);
	EXPECT_TRUE( verifyMST(mst, gr) );
}


}