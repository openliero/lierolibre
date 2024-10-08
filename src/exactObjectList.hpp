/*
 * Copyright (c) 2007-2010, Erik Lindroos <gliptic@gmail.com>
 * This software is released under the The BSD-2-Clause License:
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * * Redistributions of source code must retain the above copyright notice,
 *   this list of conditions and the following disclaimer.
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef LIERO_EXACTOBJECTLIST_HPP
#define LIERO_EXACTOBJECTLIST_HPP

#include <cstddef>
#include <cassert>
#include <gvl/containers/pairing_heap.hpp>

struct ExactObjectListBase : gvl::pairing_node<>
{
	bool operator<(ExactObjectListBase const& b) const
	{
		return index < b.index;
	}

	int index;
	bool used;
};

template<typename T, int Limit>
struct ExactObjectList
{
	struct iterator
	{
		iterator(T* cur_)
		: cur(cur_)
		{
			while(!cur->used)
			{
				++cur;
			}
		}

		iterator& operator++()
		{
			do
			{
				++cur;
			}
			while(!cur->used);

			return *this;
		}

		T& operator*()
		{
			assert(cur->used);
			return *cur;
		}

		T* operator->()
		{
			assert(cur->used);
			return cur;
		}

		bool operator!=(iterator b)
		{
			return cur != b.cur;
		}

		T* cur;
	};

	ExactObjectList()
	{
		clear();
	}

	T* getFreeObject()
	{
		/*
		T* ptr = static_cast<T*>(nextFree);
		nextFree = ptr->nextFree;
		*/
		assert(!freeList.empty());
		T* ptr = freeList.unlink_min();
		assert(!ptr->used);
		ptr->used = true;

		/*
		sentinel.prev->next = ptr;
		ptr->prev = sentinel.prev;
		ptr->next = &sentinel;
		sentinel.prev = ptr;
		*/

		++count;

		return ptr;
	}

	T* newObjectReuse()
	{
		T* ret;
		if(freeList.empty())
			ret = &arr[Limit - 1];
		else
			ret = getFreeObject();

		assert(ret->used);
		return ret;
	}

	T* newObject()
	{
		if(freeList.empty())
			return 0;

		T* ret = getFreeObject();
		assert(ret->used);
		return ret;
	}

	iterator begin()
	{
		return iterator(&arr[0]);
	}

	iterator end()
	{
		return iterator(&arr[Limit]);
	}

	void free(T* ptr)
	{
		assert(ptr->used);
		if(ptr->used)
		{
			//ptr->nextFree = nextFree;
			//nextFree = ptr;
			freeList.insert(ptr);
			ptr->used = false;

			assert(count > 0);

			--count;
		}
	}

	void free(iterator i)
	{
		free(&*i);
	}

	void clear()
	{
		count = 0;
		/*
		sentinel.prev = &sentinel;
		sentinel.next = &sentinel;*/

		arr[Limit].used = true; // Sentinel

		for(std::size_t i = 0; i < Limit; ++i)
		{
			//arr[i].nextFree = &arr[i + 1];
			arr[i].used = false;
			arr[i].index = i;
			freeList.insert(&arr[i]);
		}

		//arr[Limit - 1].nextFree = 0;
		//arr[Limit - 1].used = false;
		//nextFree = &arr[0];
	}

	std::size_t size() const
	{
		return count;
	}

	T arr[Limit + 1]; // One sentinel

	//ObjectListBase* nextFree;
	//ObjectListBase sentinel;
	gvl::pairing_heap<T, gvl::default_pairing_tag, std::less<T>, gvl::dummy_delete> freeList;
	std::size_t count;
};

#endif // LIERO_EXACTOBJECTLIST_HPP
