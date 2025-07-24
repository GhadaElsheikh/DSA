#include <iostream>
#include <cassert>
#include <climits>

#include <vector> // for debug
#include <algorithm>
#include <sstream>
using namespace std;

struct Node
{
	int data{};
	Node *next{};
	Node(int data) : data(data)
	{
	}
	~Node()
	{
		cout << "Destroy value: " << data << " at address " << this << "\n";
	}
};

class LinkedList
{
private:
	Node *head{};
	Node *tail{};
	int length = 0; // let's maintain how many nodes

	vector<Node *> debug_data; // add/remove nodes you use

	void debug_add_node(Node *node)
	{
		debug_data.push_back(node);
	}
	void debug_remove_node(Node *node)
	{
		auto it = std::find(debug_data.begin(), debug_data.end(), node);
		if (it == debug_data.end())
			cout << "Node does not exist\n";
		else
			debug_data.erase(it);
	}

public:
	// Below 2 deletes prevent copy and assign to avoid this mistake
	LinkedList()
	{
	}
	LinkedList(const LinkedList &) = delete;
	LinkedList &operator=(const LinkedList &another) = delete;

	void debug_print_address()
	{
		for (Node *cur = head; cur; cur = cur->next)
			cout << cur << "," << cur->data << "\t";
		cout << "\n";
	}

	void debug_print_node(Node *node, bool is_seperate = false)
	{
		if (is_seperate)
			cout << "Sep: ";
		if (node == nullptr)
		{
			cout << "nullptr\n";
			return;
		}
		cout << node->data << " ";
		if (node->next == nullptr)
			cout << "X ";
		else
			cout << node->next->data << " ";

		if (node == head)
			cout << "head\n";
		else if (node == tail)
			cout << "tail\n";
		else
			cout << "\n";
	}
	void debug_print_list(string msg = "")
	{
		if (msg != "")
			cout << msg << "\n";
		for (int i = 0; i < (int)debug_data.size(); ++i)
			debug_print_node(debug_data[i]);
		cout << "************\n"
			 << flush;
	}

	string debug_to_string()
	{
		if (length == 0)
			return "";
		ostringstream oss;
		for (Node *cur = head; cur; cur = cur->next)
		{
			oss << cur->data;
			if (cur->next)
				oss << " ";
		}
		return oss.str();
	}

	void debug_verify_data_integrity()
	{
		if (length == 0)
		{
			assert(head == nullptr);
			assert(tail == nullptr);
			return;
		}

		assert(head != nullptr);
		assert(tail != nullptr);
		assert(tail->next == nullptr);

		if (length == 1)
			assert(head == tail);
		else
		{
			assert(head != tail);

			if (length == 2)
				assert(head->next == tail);
			else if (length == 3)
			{
				assert(head->next);
				assert(head->next->next == tail);
			}
		}
		int len = 0;
		Node *prev = nullptr;
		for (Node *cur = head; cur; prev = cur, cur = cur->next, len++)
			assert(len < 10000); // Consider infinite cycle?

		assert(length == len);
		assert(length == (int)debug_data.size());
		assert(prev == tail); // last node is tail
	}

	////////////////////////////////////////////////////////////

	void print()
	{
		for (Node *cur = head; cur; cur = cur->next)
			cout << cur->data << " ";
		cout << "\n";
	}

	// These 2 simple functions just to not forget changing the vector and length
	void delete_node(Node *node)
	{
		debug_remove_node(node);
		--length;
		delete node;
	}

	void add_node(Node *node)
	{
		debug_add_node(node);
		++length;
	}

	void insert_end(int value)
	{
		Node *item = new Node(value);
		add_node(item);

		if (!head)
			head = tail = item;
		else
			tail->next = item, tail = item;

		debug_verify_data_integrity();
	}

	////////////////////////////////////////////////////////////

	// NO length
	bool is_same1(const LinkedList &other)
	{
		// O(n)time - O(1)memory
		Node *my_curr = head;
		Node *other_curr = other.head;
		while (my_curr && other_curr)
		{
			if (my_curr->data != other_curr->data)
				return false;
			if (my_curr->next == nullptr && other_curr->next != nullptr)
				return false;
			if (my_curr->next != nullptr && other_curr->next == nullptr)
				return false;
			my_curr = my_curr->next;
			other_curr = other_curr->next;
		}
		return true;
	}

	// Using length
	bool is_same(const LinkedList &other)
	{
		// O(n)time - O(1)memory
		if (other.length != length)
			return false;
		for (Node *my_curr = head, *other_curr = other.head; my_curr; my_curr = my_curr->next, other_curr = other_curr->next)
		{
			if (my_curr->data != other_curr->data)
				return false;
		}
		return true;
	}
};

void test1()
{
	LinkedList list1;
	LinkedList list2;

	assert(list1.is_same(list2));
	list1.insert_end(6);
	list1.insert_end(10);
	list2.insert_end(6);
	assert(!list1.is_same(list2));
	list2.insert_end(10);
	assert(list1.is_same(list2));
	list1.insert_end(8);
	list1.insert_end(15);
	list2.insert_end(8);
	list2.insert_end(77);
	assert(!list1.is_same(list2));
}

int main()
{
	test1();
	// test2();
	//  test3();

	// must see it, otherwise RTE
	cout << "\n\nNO RTE\n";

	return 0;
}
