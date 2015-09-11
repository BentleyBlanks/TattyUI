#ifndef T2_LIST_H
#define T2_LIST_H

// --!可更换式
// 底层实质为vector
#include <vector>
#include <TattyUI/common/t2Settings.h>

using namespace std;

namespace TattyUI
{
	template <class Type>
	class t2List
	{
	public:
		t2List(){}

        void resize(int size);

		void pushback(Type& object);

		void popback();

		void remove(uint index);

		void clear();

		bool isEmpty() const;

		Type& operator[](uint index);

		int size() const;

	private:
		std::vector<Type> list;
	};

    template <class Type>
    void t2List<Type>::resize(int size)
    {
        list.resize(size);
    }

	template <class Type>
	void t2List<Type>::pushback(Type& object)
	{
		list.push_back(object);
	}

	template <class Type>
	void t2List<Type>::popback()
	{
		list.pop_back();
	}

	template <class Type>
	void t2List<Type>::remove(uint index)
	{
		std::vector<Type>::iterator it;

		if(index < list.size())
		{
			it = list.begin() + index;
			list.erase(it);
		}
		else
		{
			cout << "无法删除标号为:" << index << "号的元素 该标号已越界" << endl;
			cout << "已跳过此危险操作" << endl;
		}
	}

	template <class Type>
	void t2List<Type>::clear()
	{
		list.clear();
	}

	template <class Type>
	bool t2List<Type>::isEmpty() const
	{
		return list.empty();
	}

	template <class Type>
	int t2List<Type>::size() const
	{
		return list.size();
	}

	template <class Type>
	Type& t2List<Type>::operator[](uint index)
	{
		return list[index];
	}
}

#endif