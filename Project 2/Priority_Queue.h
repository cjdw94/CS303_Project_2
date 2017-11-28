#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H


#include <vector>
#include <functional>

template < typename Item_Type, typename Compare = std::less<Item_Type> >

class priority_queue {
public:
	priority_queue() {}
	void push(const Item_Type& item);
	void pop();
	bool empty() const { return the_data.empty(); }
	int size() const { return the_data.size(); }
	const Item_Type& top() const { return the_data.front(); }

private:
	std::vector<Item_Type> the_data;
	Compare comp;
};

template<typename Item_Type, typename Compare>
void priority_queue < Item_Type, Compare > ::push(const Item_Type& item) {
	the_data.push_back(item);
	int child = size() - 1;
	int parent = (child - 1) / 2;
	// Reheap
	while (parent >= 0
		&& comp(the_data[parent], the_data[child])) {
			std::swap(the_data[child], the_data[parent]);
			child = parent;
			parent = (child - 1) / 2;
	}
}

template<typename Item_Type, typename Compare>
void priority_queue<Item_Type, Compare>::pop() {
	if (size() == 1) { the_data.pop_back(); return; }
	std::swap(the_data[0], the_data[size() - 1]);
	the_data.pop_back();
	int parent = 0;
	while (true) {
		int left_child = 2 * parent + 1;
		if (left_child >= size()) break; // out of heap
		int right_child = left_child + 1;
		int max_child = left_child;
		if (right_child < size()
			&& comp(the_data[left_child], the_data[right_child]))
			max_child = right_child;
		if (comp(the_data[parent], the_data[max_child])) {
			std::swap(the_data[max_child], the_data[parent]);
			parent = max_child;
		}
		else break;
	}
}

#endif