#include <iostream>
#define CLEAR system("cls")
#define PAUSE system("pause")
using namespace std;

void menu()
{
	CLEAR;
	cout << "______________________МЕНЮ______________________\n";
	cout << "1.Заполнить бинарное дерево\n";
	cout << "2.Вывести рисунок бинарного дерева на экран\n";
	cout << "3.Вывести слова в алфавитном порядке\n";
	cout << "4.Удалить слова, начинающиеся на гласную букву\n";
	cout << "5.Очистить бинарное дерево\n";
	cout << "6.Выход из программы\n";
	cout << ">";
}

class Binary_Tree
{
public:
	Binary_Tree();
	~Binary_Tree();
	int size();
	int depth();
	void fill(const char* word);
	void show();
	void by_order();
	void delete_words();
	void clear();
	void vowel_words();
private:
	class Branch
	{
	public:
		char* word;
		int level = 0;
		Branch* left;
		Branch* right;
		Branch(const char* word = "", const int level = 0, Branch* left = nullptr, Branch* right = nullptr)
		{
			int length = strlen(word);
			this->word = new char[length + 1];
			for (int i = 0; i < length; i++)
			{
				this->word[i] = word[i];
			}
			this->word[length] = '\0';
			this->level = level;
			this->left = left;
			this->right = right;
		}
		~Branch()
		{
			delete[] word;
			word = nullptr;
		}
	};
	Branch* root;
	Branch* replace(Branch* current, Branch* parent)
	{
		if (current->left != nullptr)
		{
			current->left = replace(current->left, parent);
			return current;
		}
		int length = strlen(current->word);
		delete[] parent->word;
		parent->word = nullptr;
		parent->word = new char[length + 1];
		for (int i = 0; i < length; i++)
		{
			parent->word[i] = current->word[i];
		}
		parent->word[length] = '\0';
		Branch* save = current->right;
		delete current;
		current = nullptr;
		return save;
	}
	Branch* bst_delete(Branch* node, char* word)
	{
		if (node == nullptr)
		{
			return node;
		}
		if (strcmp(word, node->word) < 0)
		{
			node->left = bst_delete(node->left, word);
			return node;
		}
		if (strcmp(word, node->word) > 0)
		{
			node->right = bst_delete(node->right, word);
			return node;
		}
		if ((node->left == nullptr) && (node->right == nullptr))
		{
			if (node == root)
			{
				delete root;
				root = nullptr;
				return root;
			}
			delete node;
			node = nullptr;
			return node;
		}
		if (node->left == nullptr)
		{
			if (node == root)
			{
				Branch* save = root->right;
				delete root;
				root = save;
				root->level--;
				return root;
			}
			Branch* save = node->right;
			delete node;
			node = nullptr;
			low_level(save);
			return save;
		}
		if (node->right == nullptr)
		{
			if (node == root)
			{
				Branch* save = root->left;
				delete root;
				root = save;
				root->level--;
				return root;
			}
			Branch* save = node->left;
			delete node;
			node = nullptr;
			low_level(save);
			return save;
		}
		if (node == root)
		{
			root->right = replace(root->right, root);
			return root;
		}
		node->right = replace(node->right, node);
		return node;
	}
	bool is_vowel(char letter)
	{
		switch (letter)
		{
		case 'A':
		case 'a':
		case 'E':
		case 'e':
		case 'I':
		case 'i':
		case 'O':
		case 'o':
		case 'U':
		case 'u':
		case 'Y':
		case 'y':
			return true;
		default:
			return false;
		}
	}
	void fill_bst(Branch* node, Branch* parent)
	{
		if (strcmp(node->word, parent->word) < 0)
		{
			if (parent->left == nullptr)
			{
				parent->left = node;
				node->level = parent->level + 1;
			}
			else
			{
				fill_bst(node, parent->left);
			}
		}
		else
		{
			if (parent->right == nullptr)
			{
				parent->right = node;
				node->level = parent->level + 1;
			}
			else
			{
				fill_bst(node, parent->right);
			}
		}
	}
	void alphabetical_order(Branch* node)
	{
		if (node->left != nullptr)
		{
			alphabetical_order(node->left);
		}
		cout << node->word << endl;
		if (node->right != nullptr)
		{
			alphabetical_order(node->right);
		}
	}
	void delete_bst_vowel(Branch* node)
	{
		if (node->left != nullptr)
		{
			delete_bst_vowel(node->left);
		}
		if (node->right != nullptr)
		{
			delete_bst_vowel(node->right);
		}
		if (is_vowel(node->word[0]))
		{
			bst_delete(root, node->word);
		}
	}
	void count(Branch* node, int& size)
	{
		if (node == nullptr)
		{
			return;
		}
		count(node->left, size);
		count(node->right, size);
		size++;
	}
	void depth_count(Branch* node, int& depth)
	{
		if (node == nullptr)
		{
			return;
		}
		depth_count(node->left, depth);
		depth_count(node->right, depth);
		if (node->level + 1 > depth)
		{
			depth = node->level + 1;
		}
	}
	void clear_bst(Branch*& node)
	{
		if (node == nullptr)
		{
			return;
		}
		clear_bst(node->left);
		clear_bst(node->right);
		delete node;
		node = nullptr;
	}
	void print_vowel_words(Branch* node)
	{
		if (node->left != nullptr)
		{
			print_vowel_words(node->left);
		}
		if (is_vowel(node->word[0]))
		{
			cout << node->word << endl;
		}
		if (node->right != nullptr)
		{
			print_vowel_words(node->right);
		}
	}
	void count_vowel_words(Branch* node, int& counter)
	{
		if (node->left != nullptr)
		{
			count_vowel_words(node->left, counter);
		}
		if (is_vowel(node->word[0]))
		{
			counter++;
		}
		if (node->right != nullptr)
		{
			count_vowel_words(node->right, counter);
		}
	}
	void show_tree(Branch* node)
	{
		if (node->left != nullptr)
		{
			show_tree(node->left);
		}
		for (int i = 0; i < node->level; i++)
		{
			cout << "\t";
		}
		cout << node->word << endl;
		if (node->right != nullptr)
		{
			show_tree(node->right);
		}
	}
	void low_level(Branch* node)
	{
		if (node->left != nullptr)
		{
			low_level(node->left);
		}
		if (node->right != nullptr)
		{
			low_level(node->right);
		}
		node->level--;
	}
};

Binary_Tree::Binary_Tree()
{
	root = nullptr;
}

Binary_Tree::~Binary_Tree()
{
	clear_bst(root);
}

void Binary_Tree::fill(const char* word)
{
	if (root == nullptr)
	{
		root = new Branch(word);
		root->level = 0;
	}
	else
	{
		Branch* node = new Branch(word);
		fill_bst(node, root);
	}
}

void Binary_Tree::show()
{
	if (root == nullptr)
	{
		cout << "Бинарное дерево пусто...\n";
	}
	else
	{
		cout << "____________________РИСУНОК ДЕРЕВА____________________\n\n\n";
		show_tree(root);
		cout << "\n\nРазмер бинарного дерева составляет: " << this->size() << endl;
		cout << "Глубина дерева составляет: " << this->depth() << endl;
	}
}

void Binary_Tree::by_order()
{
	if (root == nullptr)
	{
		cout << "Бинарное дерево пусто...\n";
	}
	else
	{
		cout << "Актуальное бинарное дерево:\n";
		alphabetical_order(root);
		cout << "Размер бинарного дерева составляет: " << this->size() << endl;
	}
}

int Binary_Tree::size()
{
	int SIZE = 0;
	count(root, SIZE);
	return SIZE;
}

int Binary_Tree::depth()
{
	int depth = 0;
	depth_count(root, depth);
	return depth;
}

void Binary_Tree::delete_words()
{
	if (root == nullptr)
	{
		return;
	}
	else
	{
		int counter = 0;
		count_vowel_words(root, counter);
		if (counter)
		{
			CLEAR;
			cout << "Удаление из бинарного дерева слов, начинающихся с гласной буквы...\n";
			delete_bst_vowel(root);
		}
		else
		{
			return;
		}
	}
}

void Binary_Tree::clear()
{
	clear_bst(root);
}

void Binary_Tree::vowel_words()
{
	if (root == nullptr)
	{
		cout << "Бинарное дерево пусто...\n";
	}
	else
	{
		int counter = 0;
		count_vowel_words(root, counter);
		if (counter)
		{
			cout << "Все слова, начинающиеся на гласную букву:\n";
			print_vowel_words(root);
			cout << "Количество слов: " << counter << endl;
			PAUSE;
		}
		else
		{
			CLEAR;
			cout << "Нет слов, начинающихся с гласной буквы...\n";
		}
	}
}

int main()
{
	setlocale(LC_ALL, "ru");
	Binary_Tree tree;
	int select;
	do
	{
		menu();
		cin >> select;
		switch (select)
		{
		case 1:
		{
			CLEAR;
			/*int number;
			cout << "Сколько слов Вы хотите ввести: ";
			cin >> number;
			for (int i = 0; i < number; i++)
			{
				char* word = new char[255];
				cout << i + 1 << " слово: ";
				cin >> word;
				tree.fill(word);
				delete[] word;
				word = nullptr;
			}*/
			tree.fill("Zetflix");
			tree.fill("Mansur");
			tree.fill("Ford");
			tree.fill("Obarg");
			tree.fill("Elagin");
			tree.fill("Izripov");
			tree.fill("Alfa");
			tree.fill("Nine");
			tree.fill("Potter");
			tree.fill("mans");
			tree.fill("fire");
			tree.fill("omega");
			tree.fill("elephant");
			tree.fill("ibragim");
			tree.fill("antony");
			tree.fill("student");
			tree.fill("query");
			tree.fill("united");
			tree.fill("type");
			tree.fill("yellow");
			tree.fill("www");
			tree.fill("zone");
			CLEAR;
			cout << "Заполнение бинарного дерева...\n";
		}
		break;
		case 2:
		{
			CLEAR;
			tree.show();
		}
		break;
		case 3:
		{
			CLEAR;
			tree.by_order();
		}
		break;
		case 4:
		{
			CLEAR;
			tree.vowel_words();
			tree.delete_words();
		}
		break;
		case 5:
		{
			CLEAR;
			tree.clear();
			cout << "Бинарное дерево пусто...\n";
		}
		break;
		case 6:
		{
			CLEAR;
			cout << "Программа завершена...\n";
			return 0;
		}
		break;
		}
		if (select != 6)
		{
			PAUSE;
		}
	} while (select != 6);
}

// TEST
/*
* 	tree.fill("Zetflix");
	tree.fill("Mansur");
	tree.fill("Ford");
	tree.fill("Obarg");
	tree.fill("Elagin");
	tree.fill("Izripov");
	tree.fill("Alfa");
	tree.fill("Nine");
	tree.fill("Potter");
	tree.fill("mans");
	tree.fill("fire");
	tree.fill("omega");
	tree.fill("elephant");
	tree.fill("ibragim");
	tree.fill("antony");
	tree.fill("student");
	tree.fill("query");
	tree.fill("united");
	tree.fill("type");
	tree.fill("yellow");
	tree.fill("www");
	tree.fill("zone");
*/