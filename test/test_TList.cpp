#include "ArrayList.h"
#include "../gtest/gtest.h"

TEST(TArrayList, can_create_list)
{
	ASSERT_NO_THROW(TArrayList<int> A());
}

TEST(TArrayList, can_copy_list)
{
	TArrayList<int> A(2);
	ASSERT_NO_THROW(TArrayList<int> B(A));
}

TEST(TArrayList, can_create_list_with_positive_size)
{
	ASSERT_NO_THROW(TArrayList<int> A(4));
}

TEST(TArrayList, throws_when_create_list_with_negative_size)
{
	ASSERT_ANY_THROW(TArrayList<int> A(-3));
}

TEST(TArrayList, can_ins_and_get_first)
{
	TArrayList<int> A(2);
	A.InsFirst(2);
	ASSERT_EQ(2, A.GetFirst());
}

TEST(TArrayList, can_ins_and_get_last)
{
	TArrayList<int> A(2);
	A.InsLast(2);
	ASSERT_EQ(2, A.GetLast());
}

TEST(TArrayList, is_full_true)
{
	TArrayList<int> A(1);
	A.InsFirst(3);
	ASSERT_EQ(A.IsFull(), true);
}

TEST(TArrayList, is_full_false)
{
	TArrayList<int> A(2);
	A.InsFirst(2);
	ASSERT_EQ(false, A.IsFull());
}

TEST(TArrayList, is_empty_true)
{
	TArrayList<int> A(2);
	ASSERT_EQ(true, A.IsEmpty());
}

TEST(TArrayList, throws_when_insfirst_inslast_elem_in_full_list)
{
	TArrayList<int> A(1);
	A.InsFirst(2);
	ASSERT_ANY_THROW(A.InsFirst(2));
	ASSERT_ANY_THROW(A.InsLast(2));
}

TEST(TArrayList, throws_when_getfirst_getlast_elem_in_empty_list)
{
	TArrayList<int> A;
	ASSERT_ANY_THROW(A.GetFirst());
	ASSERT_ANY_THROW(A.GetFirst());
}

TEST(TArrayList, can_ins_iterator)
{
	TArrayList<int> A(4);
	A.InsFirst(1);
	A.InsFirst(2);
	A.InsFirst(3);
	TArrayListIter<int> i(A, 1);
	ASSERT_NO_THROW(A.Ins(i, 4));
}

TEST(TArrayList, division_by_k)
{
	TArrayList<int> A(8);
	A.InsFirst(12);
	A.InsFirst(5);
	A.InsFirst(3);
	A.InsFirst(2);
	A.InsFirst(3);
	A.InsFirst(27);
	A.InsFirst(30);

	ASSERT_NO_THROW(cout << A.DivisionByK(3));
}

TEST(TArrayList, can_load_to_file)
{
	TArrayList<int> A(3);
	A.InsFirst(1);
	A.InsFirst(2);
	A.InsFirst(3);
	ASSERT_NO_THROW(A.LoadToFile());
}