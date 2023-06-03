// Потенциальные задачи с интервью

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct ListNode {

	int val;
	ListNode* next;

	ListNode() : val(0), next(nullptr) {}
	ListNode(int val) : val(val), next(nullptr) {}
	ListNode(int val, ListNode* next) : val(val), next(next) {}
};

ListNode* ReverseList(const ListNode* const head)	// Развернуть список (с созданием копии)
{
	const ListNode* iterator = head->next;
	ListNode* last = new ListNode(head->val);

	while (iterator != nullptr) {
		last = new ListNode(iterator->val, last);	// ?
		iterator = iterator->next;
	}

	return last;
}

ListNode* ReverseListNoCopy(ListNode* head)	// Развернуть список (без создания копии)
{
	ListNode* iterator = head;
	ListNode* prev = nullptr;

	ListNode* temp;

	while (iterator != nullptr) {

		temp = iterator->next;

		iterator->next = prev;

		prev = iterator;
		iterator = temp;

	}

	return prev;
}

void outputList(const ListNode const* const head)	// Вывод списка в консоль
{
	const ListNode* it = head;

	while (it != nullptr) {
		cout << it->val << " ";
		it = it->next;
	}
	cout << endl;
}

int32_t binSearch(const std::vector<int>& data, int key)	// Бинарный поиск самого первого вхождения ключа
{
	int32_t left(0), right(data.size() - 1), index(0);
	int elem;

	while (left < right)
	{
		index = (right + left) / 2;
		elem = data[index];

		if (elem > key)
		{
			right = index - 1;
		}
		else if (elem < key)
		{
			left = index + 1;
		}
		else
		{
			for (int32_t i = index - 1; i > 0; --i)
			{
				if (data[i] == key)
					--index;
				else
					break;
			}

			return index;
		}
	}

	if (data[left] == key)
		return left;
	else
		return -1;
}

struct TreeNode {

	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode() : val(0), left(nullptr), right(nullptr) {}
	TreeNode(int val) : val(val), left(nullptr), right(nullptr) {}
	TreeNode(int val, TreeNode* left, TreeNode* right) : val(val), left(left), right(right) {}
};

bool isSameTree(const TreeNode* const p, const TreeNode* const q)
{
	if (p == nullptr && q == nullptr)	// В начале обрабатываем условия прекращения рекурсии
	{
		return true;
	}
	else if ((p != nullptr && q != nullptr && p->val != q->val) ||
		(p == nullptr || q == nullptr))
	{
		return false;
	}

	return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);

}

string markChar(const string& str, const char c)
{
	string res;
	res.reserve(str.size());

	for (int i = 0; i < str.size(); ++i)
	{
		if (str[i] == c)
		{
			res += "\\";
		}

		res += str[i];
	}

	return res;
	//return {};
}

uint32_t setBit(uint32_t num, uint32_t index, uint32_t bitValue)
{
	if ((num >> index) & 1)
	{
		num = num & (bitValue << index);
	}
	else
	{
		num = num | (bitValue << index);
	}

	return num;
}

void outputBitsNum(const uint32_t num)
{
	for (int i = 8 * sizeof(uint32_t) - 1; i >= 0; --i)
	{
		cout << ((num >> i) & 1);
	}
}

int main()
{
	// Задача развернуть список

	/*ListNode* first = new ListNode(12);
	ListNode* second = new ListNode(15);
	first->next = second;
	ListNode* third = new ListNode(127);
	second->next = third;

	outputList(first);
	outputList(ReverseListNoCopy(first));*/


	// Задача найти первое вхождение значения при помощи бинарного поиска

	/*std::vector data = { 1, 2, 3, 4, 5, 6 };
	std::sort(data.begin(), data.end());

	for (auto elem : data)
	{
		cout << elem << " ";
	}
	cout << endl;

	cout << binSearch(data, 0) << endl;
	cout << binSearch(data, 1) << endl;
	cout << binSearch(data, 2) << endl;
	cout << binSearch(data, 3) << endl;
	cout << binSearch(data, 4) << endl;
	cout << binSearch(data, 5) << endl;
	cout << binSearch(data, 6) << endl;
	cout << binSearch(data, 7) << endl;*/


	// Задача сравнить деревья

	TreeNode* first_1 = new TreeNode(13);
	TreeNode* first_2 = new TreeNode(14);
	TreeNode* first = new TreeNode(16);
	first->left = first_1;
	first->right = first_2;

	TreeNode* second_1 = new TreeNode(13);
	TreeNode* second_2 = new TreeNode(14);
	TreeNode* second = new TreeNode(16, second_1, second_2);

	cout << isSameTree(first, second) << endl;

	uint32_t num = 8;
	cout << num << "(";
	outputBitsNum(num);
	cout << ")" << endl;

	num = setBit(num, 3, 0);
	num = setBit(num, 4, 1);
	cout << num << "(";
	outputBitsNum(num);
	cout << ")" << endl;

	return 0;
}