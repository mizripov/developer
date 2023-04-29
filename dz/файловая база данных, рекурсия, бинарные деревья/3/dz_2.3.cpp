#include <iostream>
#include <iomanip>
using namespace std;

class Stack
{
public:
	Stack()
	{
		top = nullptr;
		size = 0;
	}
	~Stack()
	{
		clear();
	}
	void push(const double value)
	{
		if (top == nullptr)
		{
			top = new Node(value);
		}
		else
		{
			top = new Node(value, top);
		}
		size++;
	}
	void pop()
	{
		if (top != nullptr)
		{
			Node* save = top->next;
			delete top;
			top = nullptr;
			top = save;
			size--;
		}
	}
	void clear()
	{
		while (size)
		{
			pop();
		}
	}
	bool is_empty()
	{
		return !((bool)size);
	}
	double data()
	{
		return top->value;
	}
private:
	class Node
	{
	public:
		double value;
		Node* next;
		Node(const double value = double(), Node* next = nullptr)
		{
			this->value = value;
			this->next = next;
		}
	};
	Node* top;
	int size;
};

class Parser
{
public:
	Parser();
	~Parser();
	void make(const char* Term);
	void clear();
	void print();
	void calculate(const double a, const double b);
	void size();
	void depth();
private:
	class Node
	{
	public:
		char data[2] = "";
		Node* left;
		Node* right;
		Node(Node* left = nullptr, Node* right = nullptr)
		{
			this->left = left;
			this->right = right;
		}
	};
	Stack stack;
	Node* root;
	Node* make_parser(const char* Term, const int first, const int last)
	{
		int prt, k = 0, MIN = 100, bracket = 0;
		Node* component = new Node();
		if (first == last)
		{
			component->data[0] = Term[first];
			component->data[1] = '\0';
			return component;
		}
		for (int i = first; i <= last; i++)
		{
			if (Term[i] == '(')
			{
				bracket++;
				continue;
			}
			if (Term[i] == ')')
			{
				bracket--;
				continue;
			}
			if (bracket > 0)
			{
				continue;
			}
			prt = priority(Term[i]);
			if (prt <= MIN)
			{
				MIN = prt;
				k = i;
			}
		}
		if ((MIN == 100) && (Term[first] == '(') && (Term[last] == ')'))
		{
			return make_parser(Term, first + 1, last - 1);
		}
		component->data[0] = Term[k];
		component->data[1] = '\0';
		component->left = make_parser(Term, first, k - 1);
		component->right = make_parser(Term, k + 1, last);
		return component;
	}
	bool is_operation(const char symbol)
	{
		switch (symbol)
		{
		case '+':
		case '-':
		case '*':
		case '/':
			return true;
		default:
			return false;
		}
	}
	int priority(const char symbol)
	{
		switch (symbol)
		{
		case '+':
		case '-':
			return 1;
		case '*':
		case '/':
			return 2;
		default:
			return 100;
		}
	}
	int is_variable(const char symbol)
	{
		switch (symbol)
		{
		case 'a':
			return 1;
		case 'b':
			return 2;
		default:
			return 3;
		}
	}
	int count_size(Node* component)
	{
		if (component == 0)
		{
			return 0;
		}
		else
		{
			return count_size(component->left) + 1 + count_size(component->right);
		}
	}
	int count_depth(Node* component)
	{
		int h1 = 0, h2 = 0;
		if (component == nullptr)
		{
			return 0;
		}
		if (component->left)
		{
			h1 = count_depth(component->left);
		}
		if (component->right)
		{
			h2 = count_depth(component->right);
		}
		if (h1 > h2)
		{
			return h1 + 1;
		}
		else
		{
			return h2 + 1;
		}
	}
	void clear_parser(Node*& component)
	{
		if (component != nullptr)
		{
			clear_parser(component->left);
			clear_parser(component->right);
			delete component;
			component = nullptr;
		}
	}
	void pre_order(Node* component)
	{
		if (component != nullptr)
		{
			cout << component->data << " ";
			pre_order(component->left);
			pre_order(component->right);
		}
	}
	void symmetric_order(Node* component)
	{
		if (component != nullptr)
		{
			symmetric_order(component->left);
			cout << component->data << " ";
			symmetric_order(component->right);
		}
	}
	void post_order(Node* component)
	{
		if (component != nullptr)
		{
			post_order(component->left);
			post_order(component->right);
			cout << component->data << " ";
		}
	}
	void calculate_term(Node* component, const double a, const double b)
	{
		if (component != nullptr)
		{
			calculate_term(component->left, a, b);
			calculate_term(component->right, a, b);
			if (!is_operation(component->data[0]))
			{
				switch (is_variable(component->data[0]))
				{
				case 1:
				{
					stack.push(a);
				}
				break;
				case 2:
				{
					stack.push(b);
				}
				break;
				default:
				{
					int value = atof(component->data);
					stack.push(value);
				}
				break;
				}
			}
			else
			{
				double second_operand = stack.data();
				stack.pop();
				double first_operand = stack.data();
				stack.pop();
				switch (component->data[0])
				{
				case '+':
				{
					stack.push(first_operand + second_operand);
				}
				break;
				case '-':
				{
					stack.push(first_operand - second_operand);
				}
				break;
				case '*':
				{
					stack.push(first_operand * second_operand);
				}
				break;
				case '/':
				{
					if (second_operand != 0)
					{
						stack.push(first_operand / second_operand);
					}
					else
					{
						throw exception("На 0 делить нельзя...");
					}
				}
				break;
				}
			}
		}
	}
};

Parser::Parser()
{
	root = nullptr;
}

Parser::~Parser()
{
	clear();
}

void Parser::make(const char* Term)
{
	root = make_parser(Term, 0, strlen(Term) - 1);
}

void Parser::clear()
{
	if (root != nullptr)
	{
		clear_parser(root);
	}
}

void Parser::print()
{
	if (root != nullptr)
	{
		cout << "Прямой обход дерева:\n";
		pre_order(root);
		cout << endl;
		cout << "Симметрический обход дерева:\n";
		symmetric_order(root);
		cout << endl;
		cout << "Обратный обход дерева:\n";
		post_order(root);
		cout << endl << endl;
	}
}

void Parser::calculate(const double a, const double b)
{
	try
	{
		calculate_term(root, a, b);
	}
	catch (const exception& error)
	{
		cout << error.what() << endl;
		return;
	}
	cout << endl << "Значение выражения = " << fixed << setprecision(5) << stack.data() << endl;
}

void Parser::size()
{
	cout << "Количество вершин дерева: " << count_size(root) << endl;
}

void Parser::depth()
{
	cout << "Глубина дерева: " << count_depth(root) << endl;
}

int main()
{
	setlocale(LC_ALL, "ru");
	Parser parser;
	double a, b;
	char Term[] = "(1+a)*(2-3*(7-b))";
	cout << "Выражение, которое необходимо вычислить: " << Term << endl << endl;
	parser.make(Term);
	parser.print();
	cout << "Введите значение параметра a: ";
	cin >> a;
	cout << "Введите значение параметра b: ";
	cin >> b;
	parser.calculate(a, b);
	parser.depth();
	parser.size();
	return 0;
}