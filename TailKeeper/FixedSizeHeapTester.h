// Test code for the FixedSizeHeap class

#ifndef FIXEDSIZEHEAPTESTER_H
#define FIXEDSIZEHEAPTESTER_H

#include "FixedSizeHeap.h"
#include <assert.h>
#include <iostream>

class FixedSizeHeapTester
{
public:
    void Test()
    {
		// Create a heap of capacity 13 and insert 12 elements.
        FixedSizeHeap<int> heap(13);

        heap.Insert(12);
        heap.Insert(20);
        heap.Insert(15);
        heap.Insert(29);
        heap.Insert(23);
        heap.Insert(17);
        heap.Insert(22);
        heap.Insert(35);
        heap.Insert(40);
        heap.Insert(26);
        heap.Insert(51);
        heap.Insert(19);

		// Verify the last index and size
        assert(heap.m_lastIndex == 11);
        assert(heap.EffectiveSize() == 12);

		// Verify that the heap sorted correctly, making 12 the smallest element.
        assert(heap.InspectMinElement() == 12);

		// Compare the internal storage of the heap with the result of manual calculation.
        // NB: extra zero at end for allocated but unused storage.
		int v1[] = {12,  20,  15,  29,  23,  17,  22,  35,  40,  26,  51,  19,  0};
		std::vector<int> expectedArray1(v1, v1 + sizeof(v1)/sizeof(v1[0]));
        assert(heap.m_heap == expectedArray1);

		// Insert one more element and compare to manual calculation again.
        heap.Insert(13);
		int v2[] = {12,  20,  13,  29,  23,  15,  22,  35,  40,  26,  51,  19,  17};
		std::vector<int> expectedArray2(v2, v2 + sizeof(v2)/sizeof(v2[0]));
        assert(heap.m_lastIndex == 12);
        assert(heap.EffectiveSize() == 13);
        assert(heap.m_heap == expectedArray2);

        try
        {
            heap.Insert(22);	// should be full
            assert(false);		// If the Insert statement doesn't trhow an exception, this will.
        }
		catch (const std::length_error& e)
        {
           e;
        }

        assert(heap.EffectiveSize() == 13);

        heap.ReplaceMinElement(7);
        assert(heap.InspectMinElement() == 7);

        heap.ReplaceMinElement(99);
        assert(heap.InspectMinElement() == 13);

#ifdef _DEBUG
		// If we haven't thrown an exception by now, all tests pass.
        std::cout << "All FixedSizeHeap tests pass\n";
#endif
   }
};

#endif